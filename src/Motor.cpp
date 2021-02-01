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

#if defined(__SAMD21G18A__)
/**
 * Creates a motor controlled by a TB6612FNG driver 
 * with custom PWM frequency for SAMD21 processors
 * @constructor
 * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
 * @param {SAMD21CustomPWM*} customPWM - SAMD21 PWM timer configuration
 * @note The mapped Arduino pins will be initialized by this function
 */
Motor::Motor(PinMap *pinMap, SAMD21CustomPWM *customPWM) : Motor(pinMap)
{
    int timer = getSAMD21Timer_(pinMap->pwm);
    if (timer >= 0)
    {
        // PWM pin is associated to a timer: Initialize it
        samd21PWM_.setClockDivider(customPWM->clockDivider, false);
        samd21PWM_.timer(timer, customPWM->tccPrescaler, customPWM->resolution, false);
        customPWM_ = true;
    }
}
#endif

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
    {
        if (customPWM_)
        {
            // Set speed in custom PWM
#if defined(__SAMD21G18A__)
            // Speed must be scaled to 1000
            samd21PWM_.analogWrite(pinMap->pwm, round(speed * 3.92156862745098));
#endif
        }
        else
            analogWrite(pinMap->pwm, speed);
    }
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

#if defined(__SAMD21G18A__)
/**
 * Returns the SAMD21 timer associated to a given PWM pin
 * @param {pin_size_t} pwmPin - PWM pin
 * @returns {int} Associated timer (0, 1 or 2) or -1 if the pin is not a PWM timer associated pin
 */
int8_t Motor::getSAMD21Timer_(pin_size_t pwmPin)
{
    if (pwmPin != 0)
    {
        for (int timer = 0; timer < 3; timer++)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                if (kSam32TimerPinMap[timer][pin] == pwmPin)
                    return timer;
            }
        }
    }

    return -1;
}
#endif