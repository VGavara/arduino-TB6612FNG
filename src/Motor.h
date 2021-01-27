// Motor.h
// Header file for Motor class
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

/**
 * Rotation directions
 * @enum
 */
enum Direction
{
    Clockwise = 1,
    CounterClockwise = -1
};

/**
 * Arduino output to driver input pin mapping
 * @typedef {struct} PinMap
 * @property {pin_size_t}} in1 - Arduino pin id connected to driver's AIN1/BIN1 input
 * @property {pin_size_t}} in2 - Arduino pin id connected to driver's AIN2/BIN2 input
 * @property {pin_size_t}} pwm - Arduino pin id connected to driver's PWMA/PWMB input
 * @property {pin_size_t}} stby - Arduino pin id connected to driver's STBY input
 */
typedef struct
{
    pin_size_t in1;
    pin_size_t in2;
    pin_size_t pwm;
    pin_size_t stby;
} PinMap;

/**
 * Represents a motor controlled by a TB6612FNG driver
 * @class
 */
class Motor
{
public:
    /**
     * Creates a motor controlled by a TB6612FNG driver
     * @constructor
     * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
     * @note Set pinMap.stby to 0 to disable driver standby management
     * @note The mapped Arduino pins will be initialized by this function
     */
    Motor(PinMap *pinMap);

    /**
     * Runs the motor in a given direction at a given speed
     * @param {Direction} direction - Motor rotation direction
     * @param {uint8_t} speed - Motor rotation spped, from 1 to 255
     * @note Standby mode will be switched off if this function is invoked
     * @note Spinning will be aborted if this function is invoked
     */
    void run(Direction direction, uint8_t speed);

    /**
     * Stops the motor
     * @note Spinning will be aborted if this function is invoked
     */
    void stop();

    /**
     * Short-brakes the motor
     * @note Spinning will be aborted if this function is invoked
     */
    void brake();

    /**
     * Sets the motor driver in standby mode
     * @note This function does nothing if the class constructor was called with pinMap.stby set to 0
     */
    void standBy();

private:
    PinMap pinMap_;

    void rotateCW_(PinMap *pinMap);
    void rotateCCW_(PinMap *pinMap);
    void setStandBy_(PinMap *pinMap);
    void clearStandBy_(PinMap *pinMap);
    void setRotationSpeed_(PinMap *pinMap, uint8_t speed);
    void stopRotation_(PinMap *pinMap);
    void brakeRotation_(PinMap *pinMap);
};

#endif