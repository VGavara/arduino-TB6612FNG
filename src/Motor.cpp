// Motor.cpp
// Implementation of the Motor class
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Motor.h"

// Public functions

/**
 * Creates a motor controlled by a TB6612FNG driver
 * @constructor
 * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
 */
Motor::Motor(PinMap *pinMap)
{
    // Copy the IO mapping
    pinMap_.in1 = pinMap->in1;
    pinMap_.in2 = pinMap->in2;
    pinMap_.pwm = pinMap->pwm;

    // Initialize the arduino pins
    pinMode(pinMap_.in1, OUTPUT);
    pinMode(pinMap_.in2, OUTPUT);
    pinMode(pinMap_.pwm, OUTPUT);
}

/**
 * Runs the motor in a given direction at a given speed
 * @param {Direction} direction - Motor rotation direction
 * @param {uint8_t} speed - Motor rotation spped, from 1 to 255
 */
void Motor::run(Direction direction, uint8_t speed)
{
    // Set rotation direction
    direction == Direction::Clockwise ? rotateCW_(&pinMap_) : rotateCCW_(&pinMap_);

    // Set speed
    setRotationSpeed_(&pinMap_, speed);
}

/**
 * Stops the motor
 */
void Motor::stop()
{
    stopRotation_(&pinMap_);
}

/**
 * Short-brakes the motor
 */
void Motor::brake()
{
    brakeRotation_(&pinMap_);
}

/**
 * Sets clockwise rotation
 * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
 */
void Motor::rotateCW_(PinMap *pinMap)
{
    digitalWrite(pinMap->in1, HIGH);
    digitalWrite(pinMap->in2, LOW);
}

/**
 * Sets counter-clockwise rotation
 * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
 */
void Motor::rotateCCW_(PinMap *pinMap)
{
    digitalWrite(pinMap->in1, LOW);
    digitalWrite(pinMap->in2, HIGH);
}

/**
 * Sets a PWM duty cycle to make the motor rotate
 * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
 * @param {uint8_t} speed - Motor rotation speed, as PWM duty cycle
 */
void Motor::setRotationSpeed_(PinMap *pinMap, uint8_t speed)
{
    // If the speed value is in range, set it as PWM duty cycle
    // Zero value is equivalent to performing a braking, so that
    // value is not acceptable in this function
    if (speed > 0 && speed <= 255)
        analogWrite(pinMap->pwm, speed);
}

/**
 * Sets the motor in a idle state
 * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
 */
void Motor::stopRotation_(PinMap *pinMap)
{
    digitalWrite(pinMap->in1, LOW);
    digitalWrite(pinMap->in2, LOW);
    analogWrite(pinMap->pwm, 255);
}

/**
 * Brakes the motor
 * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
 */
void Motor::brakeRotation_(PinMap *pinMap)
{
    analogWrite(pinMap->pwm, 0);
    digitalWrite(pinMap->in1, HIGH);
    digitalWrite(pinMap->in2, HIGH);
}