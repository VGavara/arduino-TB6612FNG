// Spinner.h
// Header file for Spinner class
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SPINNER_H
#define SPINNER_H

#include "Motor.h"

/**
 * Spin point
 * @typedef {struct} SpinPoint
 * @property {uint16_t}} speed - Spin speed, from 0 (0%) to 65535 (100%)
 * @property {uint16_t} time - Elapsed time from the spin start, from 0 to 65535 milliseconds, in which speed must be reached
 * @example A spinPoint with value {20,100} indicates that, after 100 milliseconds of start spinning, a speed of 20 must be reached
 */
struct SpinPoint
{
    uint16_t speed;
    uint16_t time;
};

/**
 * Spinner callback type
 * @typedef {(*)(const SpinPoint *)} SpinnerCB
 */
typedef void (*SpinnerCB)(const SpinPoint *);

/**
 * Controller for Toshiba TB6612FNG driven motors supporting acceleration/deleration features
 * @class
 */
class Spinner
{
public:
    /**
     * Creates an acceleration/deceleration controller for TB6612FNG driven motors
     * @constructor
     * @param {Motor*} motor - Pointer to a Motor object instance
     */
    Spinner(Motor *motor);

    /**
     * Creates an acceleration/deceleration controller for TB6612FNG driven motors and use callbacks for handling its events
     * @constructor
     * @param {Motor*} motor - Pointer to a Motor object instance
     * @param {SpinnerCB} spinUpdated -Callback function for handling the spin updated event
     * @param {SpinnerCB} spinFinished - Callback function for handling the spin finished event
     */
    Spinner(Motor *motor, SpinnerCB spinUpdated, SpinnerCB spinFinished);

    /**
     * Starts a motor lineal acceleration/deceleration defined by a map with only two points
     * @param {Direction} direction - Motor rotation direction
     * @param {SpinPoint[]} spinMap - Spin map containing just two points: the start and end spin points
     * @returns {const SpinPoint*} Pointer to a constant SpinPoint struct containing the first spin map point or null if the start operation cannot be executed
     * @note Starting a spin operation will abort a previous running spinning operation
     */
    const SpinPoint *start(Direction direction, SpinPoint spinMap[]);

    /**
     * Starts a motor lineal acceleration/deceleration defined by a map with multiple points
     * @param {Direction} direction - Motor rotation direction
     * @param {SpinPoint[]} spinMap - Spin map containing a list of spin points
     * @param {uint8_t} spinMapSize - Number of spin points contained in the spin map
     * @returns {const SpinPoint*} Pointer to a constant SpinPoint struct containing the first spin map point or null if the start operation cannot be executed
     * @note Starting a spin operation will abort a previous running spinning operation
     */
    const SpinPoint *start(Direction direction, SpinPoint spinMap[], uint8_t spinMapSize);

    /**
     * Updates a running spin operation
     * @returns {const SpinPoint*} Pointer to a constant SpinPoint struct containing the last reached spin map point, or null if no spin operation is in progress.
     * @note This function must be called periodically. To achieve a smooth spin, a call periodicity lower or equal to 1 millisecond is recommended.
     */
    const SpinPoint *spin();

    /**
     * Aborts a spin operation, keeping the motor rotating at the last speed reached by the aborted spin operation.
     * @returns Pointer to a SpinPoint struct containing the last reached spin map point, or null if no spin operation was aborted.
     */
    const SpinPoint *abort();

private:
    Motor *motor_;

    SpinPoint *map_;
    uint8_t mapSize_;

    Direction spinDirection_;
    unsigned long spinStartTime_;
    SpinPoint currentSpinPoint_;

    uint8_t currentMapPointIndex_;

    SpinnerCB spinUpdatedCB_, spinFinishedCB_;

    bool checkSpinMap_(SpinPoint[], uint8_t);
    unsigned long getElapsedTime_(unsigned long);
    void updateSpeed_(Motor *, Direction, SpinPoint *, SpinnerCB);
    uint8_t refreshSpinCourse_(SpinPoint *, uint8_t, unsigned long);
    uint16_t getLinePointY_(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
};

#endif