// tb6612fng.cpp
// Library for controlling Toshiba TB6612FNG dual DC motor driver
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "tb6612fng.h"

// Public functions

Motor::Motor(PinMap *pinMap)
{
    // Copy the IO mapping
    pinMap_.in1 = pinMap->in1;
    pinMap_.in2 = pinMap->in2;
    pinMap_.pwm = pinMap->pwm;
    pinMap_.stby = pinMap->stby;

    // Initialize the arduino pins
    pinMode(pinMap_.in1, OUTPUT);
    pinMode(pinMap_.in2, OUTPUT);
    pinMode(pinMap_.pwm, OUTPUT);
    if (pinMap_.stby)
        pinMode(pinMap_.stby, OUTPUT);
}

void Motor::run(Direction direction, uint8_t speed)
{
    // Clear standby mode
    clearStandBy_(&pinMap_);

    // Set rotation direction
    direction == Direction::Clockwise ? rotateCW_(&pinMap_) : rotateCCW_(&pinMap_);

    // Set speed
    setRotationSpeed_(&pinMap_, speed);
}

void Motor::stop()
{
    stopRotation_(&pinMap_);
}

void Motor::brake()
{
    brakeRotation_(&pinMap_);
}

void Motor::standBy()
{
    setStandBy_(&pinMap_);
}

// Private functions

// Set Clockwise rotation
void Motor::rotateCW_(PinMap *pinMap)
{
    digitalWrite(pinMap->in1, HIGH);
    digitalWrite(pinMap->in2, LOW);
}

// Set CounterClockwise rotation
void Motor::rotateCCW_(PinMap *pinMap)
{
    digitalWrite(pinMap->in1, LOW);
    digitalWrite(pinMap->in2, HIGH);
}

// Sets the driver in standby mode
void Motor::setStandBy_(PinMap *pinMap)
{
    // If the standby pin is configured, reset it
    if (pinMap->stby)
        digitalWrite(pinMap->stby, LOW);
}

// Sets the driver in normal (non-standby) mode
void Motor::clearStandBy_(PinMap *pinMap)
{
    // If the standby pin is configured, set it
    if (pinMap->stby)
        digitalWrite(pinMap->stby, HIGH);
}

// Sets a PWM duty cycle to make the motor rotate
void Motor::setRotationSpeed_(PinMap *pinMap, uint8_t speed)
{
    // If the speed value is in range, set it as PWM duty cycle
    // Zero value is equivalent to performing a braking, so that
    // value is not acceptable in this function
    if (speed > 0 && speed <= 255)
        analogWrite(pinMap->pwm, speed);
}

// Sets the motor in a idle state.
// That means that the motor could still rotate due to inertia.
void Motor::stopRotation_(PinMap *pinMap)
{
    digitalWrite(pinMap->in1, LOW);
    digitalWrite(pinMap->in2, LOW);
    analogWrite(pinMap->pwm, 255);
}

// Brakes the motor
// Note that braking implies cancelling the inertial motor rotation,
// and therefore is an energy consuming process
void Motor::brakeRotation_(PinMap *pinMap)
{
    analogWrite(pinMap->pwm, 0);
    digitalWrite(pinMap->in1, HIGH);
    digitalWrite(pinMap->in2, HIGH);
}