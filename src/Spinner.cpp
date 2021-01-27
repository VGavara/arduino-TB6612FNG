// Spinner.cpp
// Implementation of the Spinner class
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Spinner.h"
#include "math.h"

// Public functions definition

/**
 * Creates an acceleration/deceleration controller
 * for TB6612FNG driven motors
 * @constructor
 * @param {Motor*} motor - Pointer to a Motor object instance
 */
Spinner::Spinner(Motor *motor) : Spinner(motor, NULL, NULL){};

/**
 * Creates an acceleration/deceleration controller
 * for TB6612FNG driven motors and use callbacks for handling its events
 * @constructor
 * @param {Motor*} motor - Pointer to a Motor object instance
 * @param {SpinnerCB} spinUpdated -Callback function for handling the spin updated event
 * @param {SpinnerCB} spinFinished - Callback function for handling the spin finished event
 */
Spinner::Spinner(Motor *motor, SpinnerCB spinUpdated, SpinnerCB spinFinished) : motor_(motor), spinUpdatedCB_(spinUpdated), spinFinishedCB_(spinFinished)
{
    map_ = NULL;
}

/**
 * Starts a motor lineal acceleration/deceleration defined by two spin points
 * @param {Direction} direction - Motor rotation direction
 * @param {SpinPoint[]} spinMap - Spin map containing just two points: the start and end spin points
 * @returns {const SpinPoint*} Pointer to a constant SpinPoint struct 
 *  containing the first spin map point or null if the start operation cannot be executed
 */
const SpinPoint *Spinner::start(Direction direction, SpinPoint spinMap[])
{
    // This map has only two points
    mapSize_ = 2;

    // Check the spinMap integrity
    if (!checkSpinMap_(spinMap, mapSize_))
        return NULL;

    // Initialize the plan variables
    map_ = spinMap;
    spinDirection_ = direction;

    // Start executing the plan
    spinStartTime_ = millis();
    currentSpinPoint_.time = 0;
    currentSpinPoint_.speed = map_[0].speed;
    updateSpeed_(motor_, spinDirection_, &currentSpinPoint_, spinUpdatedCB_);

    return &currentSpinPoint_;
}

/**
 * Updates a running spin operation
 * @returns {const SpinPoint*} Pointer to a constant SpinPoint struct 
 *  containing the last reached spin map point, or null if no spin operation is in progress.
 */
const SpinPoint *Spinner::spin()
{
    unsigned short currentmapPointIndex;

    // If there's no map, there's no spin in progress: quit
    if (map_ == NULL)
        return NULL;

    // Get the elapsed time since the spin start
    unsigned long spinElapsedTime = getElapsedTime_(spinStartTime_);
    if (spinElapsedTime == currentSpinPoint_.time)
    {
        // No elapsed time since the last spin update
        // Return the last spin point and quit
        return &currentSpinPoint_;
    }

    // Get the index of the current map point
    currentmapPointIndex = refreshSpinCourse_(map_, mapSize_, spinElapsedTime);

    // Set the new speed
    byte newSpeed;
    if (currentmapPointIndex == mapSize_ - 1)
    {
        // The spin is beyond the latest map point: the operation is finished
        // and the current speed is the latest map point speed
        newSpeed = map_[currentmapPointIndex].speed;
    }
    else
    {
        // The spin is between two map poins: Get the current intermediate point speed
        newSpeed = getLinePointY_(map_[currentmapPointIndex].time,
                                  map_[currentmapPointIndex].speed,
                                  map_[currentmapPointIndex + 1].time,
                                  map_[currentmapPointIndex + 1].speed,
                                  spinElapsedTime);
    }

    // If the new speed is different to that previously set,
    // update the motor speed and call the spinUpdate callback (if defined)
    if (newSpeed != currentSpinPoint_.speed)
    {
        // The new point speed is different to the lastest set: Update it
        currentSpinPoint_.speed = newSpeed;
        currentSpinPoint_.time = spinElapsedTime;
        updateSpeed_(motor_, spinDirection_, &currentSpinPoint_, spinUpdatedCB_);
    }

    // If the map is completed, drop it and call the spin Finished callback (if defined)
    if (currentmapPointIndex == mapSize_ - 1)
    {
        if (spinFinishedCB_)
        {
            currentSpinPoint_.speed = newSpeed;
            currentSpinPoint_.time = spinElapsedTime;
            spinFinishedCB_(&currentSpinPoint_);
        }
        map_ = NULL;
    }

    return &currentSpinPoint_;
}

/**
 * Aborts a spin operation, keeping the motor rotating 
 * at the last speed reached by the aborted spin operation.
 * @returns Pointer to a SpinPoint struct containing the last reached spin map point, 
 *  or null if no spin operation was aborted.
 */
const SpinPoint *Spinner::abort()
{
    // If there's no map, there's no spin in progress: quit
    if (map_ == NULL)
        return NULL;

    // Drop the spin map and return the last spin point set
    map_ = NULL;
    return &currentSpinPoint_;
}

// Private functions definition

/**
 * Checks the integrity of a spin map
 * @param {SpinPoint[]} spinMap - Spin map
 * @param {uint16_t} mapSize_ - Spin map items
 * @returns {bool} True if the spin map passes the integrity checks
 */
bool Spinner::checkSpinMap_(SpinPoint spinMap[], unsigned short mapSize_)
{
#ifdef TB6612FNG_OMIT_SPINMAP_INTEGRITY_CHECK
    return true;
#else
    // Maps with less than two points are not allowed
    if (mapSize_ < 2)
        return false;

    // First map point must set its time set to zero
    if (spinMap[0].time != 0)
        return false;

    // Every map point time must be higher than its predecessor's
    uint32_t previousSpinTime = spinMap[0].time;
    for (int i = 1; i < mapSize_; i++)
    {
        if (spinMap[i].time <= previousSpinTime)
            return false;
        previousSpinTime = spinMap[i].time;
    }

    // All tests successfully passed
    return true;
#endif
}

/**
 * Gets the elapsed time, in milliseconds, since a given past time
 * @param {unsigned long} pastTime - Past time, in milliseconds
 * @returns {unsigned long} Ellapsed time between now and pastTime
 */
unsigned long Spinner::getElapsedTime_(unsigned long pastTime)
{
    unsigned long now = millis();
    if (now < pastTime)
    {
        // Arduino ellapsed time counter has overflowed
        return 4294967295 - pastTime + now;
    }
    else
        return now - pastTime;
}

/**
 * Updates the motor speed and calls the spin update callback function (if defined)
 * @param {Motor*} motor - Motor object reference
 * @param {Direction} direction - Motor rotation direction
 * @param {SpinPoint*} spinPoint - Reference to spin point whose speed must be set
 * @param {SpinnerCB} spinUpdatedCB - Pointer to speed updated callback function
 */
void Spinner::updateSpeed_(Motor *motor, Direction spinDirection, SpinPoint *spinPoint, SpinnerCB spinUpdatedCB)
{
    motor->run(spinDirection, spinPoint->speed);
    if (spinUpdatedCB != NULL)
        spinUpdatedCB(spinPoint);
}

/**
 * Returns the last reached spin map point given an elapsed time since the spin start
 * @param {SpinPoint*} map - Spin map, or array of spin points
 * @param {unsigned short} mapCount - Size of the spin map, ie, number of map points stored in the spin map
 * @param {unsigned long} elapsedTime - Elapsed time, in milliseconds, since the spin start
 * @returns {unsigned short} Index of the next map spin point
 */
unsigned short Spinner::refreshSpinCourse_(SpinPoint map[], unsigned short mapCount, unsigned long elapsedTime)
{
    unsigned short mapPoint = 0;
    while (mapPoint < mapCount && elapsedTime > map[mapPoint].time)
    {
        mapPoint++;
    }
    return mapPoint < mapCount ? mapPoint - 1 : mapCount - 1;
}

/**
 * Returns the Y coordinate of a point in a line given its X coordinate
 * @param {unsigned int} x1 - X coordinate of the line point 1
 * @param {unsigned int} y1 - Y coordinate of the line point 1
 * @param {unsigned int} x2 - X coordinate of the line point 2
 * @param {unsigned int} y2 - Y coordinate of the line point 2
 * @param {unsigned int} x - X coordinate of the line point whose Y coordinate must be obtained
 * @return {unsigned int} Y coordinate of the line point with X coordinate equal to x
 */
unsigned int Spinner::getLinePointY_(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x)
{
    return y1 + round(((double)x / (x2 - x1)) * (y2 - y1));
}