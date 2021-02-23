// Motor.cpp
// Implementation of the Motor class
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Motor.h"
#include <math.h>

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

    // Initialize the TurboPWM
    samd21PWM_ = NULL;
}

#if defined(__SAMD21G18A__)
/**
 * Creates a motor controlled by a TB6612FNG driver 
 * and operated with a custom PWM frequency (SAMD21 processors)
 * @constructor
 * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
 * @param {uint32_t} customPWMFrequency - Custom PWM frequency, in Hertzs
 * @note The mapped Arduino pins will be initialized by this function
 */
Motor::Motor(PinMap *pinMap, uint32_t customPWMFrequency) : Motor(pinMap)
{
    // Get a SAMD21 PWM manager
    samd21PWM_ = getSAMD21PWMManager_(customPWMFrequency, pinMap->pwm);
}
#endif

/**
 * Runs the motor in a given direction at a given speed
 * @param {Direction} direction - Motor rotation direction
 * @param {uint16_t} speed - Motor rotation spped, from 1 to 65535
 */
void Motor::run(Direction direction, uint16_t speed)
{
    direction == Direction::Clockwise ? rotateCW_(&pinMap_) : rotateCCW_(&pinMap_);
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
 * @param {uint16_t} speed - Motor rotation speed, as PWM duty cycle
 */
void Motor::setRotationSpeed_(PinMap *pinMap, uint16_t speed)
{
    // If the speed value is in range, set it as PWM duty cycle
    // Zero value is equivalent to performing a braking, so that
    // value is not acceptable in this function
    if (speed > 0)
    {
#if defined(__SAMD21G18A__)
        // Set speed
        if (samd21PWM_)
            samd21PWM_->analogWrite(pinMap->pwm, scaleSpeed_(speed, 1000));
        else
            analogWrite(pinMap->pwm, scaleSpeed_(speed, 255));
#else
        analogWrite(pinMap->pwm, scaleSpeed_(speed, 255));
#endif
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

/**
 * Scales a 16-bit speed value
 * @param {uint16_t} speed - Speed to scale
 * @param {uint16_t} maxScaleValue - Max scale value
 * @returns {uint16_t} Scaled speed value
 */
uint16_t Motor::scaleSpeed_(uint16_t speed, uint16_t maxScaleValue)
{
    return round(speed * (maxScaleValue / 65535.0));
}

#if defined(__SAMD21G18A__)

/**
 * States if a SAMD21 custom PWM frequency is in the range managed by the library
 * @param {uint32_t} frequency - Custom frequency value
 * @returns True if the custom frequency is a valid value
 */
bool Motor::pwmFrequencyInRange_(uint32_t frequency)
{
    // Custom frequency ranges from 732Hz to 100kHz
    return (frequency >= 732 && frequency <= 100000);
}

/**
 * Returns the SAMD21 timer associated to a given PWM pin
 * @param {pin_size_t} pwmPin - PWM pin
 * @returns {uint8_t} Associated timer (0, 1 or 2) or -1 if the pin is not a PWM timer associated pin
 */
uint8_t Motor::getSAMD21Timer_(pin_size_t pwmPin)
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

/**
 * Returns the optimal SAMD21 PER register value for a custom PWM frequency
 * @param {uint32_t} frequency - Custom PWM frequency
 * @returns {uint16_t} SAMD21 PER register that allows getting the closest frequency to that set as parameter
 */
uint16_t Motor::getSAMD21PER_(uint32_t frequency)
{
    // Calculate the PER value together with its ceil and floor values
    float PER = 24000000.0 / frequency;
    uint16_t PERCeil = ceil(PER);
    uint16_t PERFloor = floor(PER);

    // If PER ceil and floor matches, that's the optimal PER value
    if (PERCeil == PERFloor)
        return PERCeil;

    // If ceil and floor don't match, the optimal PER value
    // is that giving the closest frequency to the desired frequency
    float ceilFrequency = 24000000.0 / PERCeil;
    float floorFrequency = 24000000.0 / PERFloor;
    if (abs(frequency - ceilFrequency) < abs(frequency - floorFrequency))
        return PERCeil;
    return PERFloor;
}

/**
 * Initializes a SAMD21 TurboPWM custom PWM manager object instance
 * @param {uint32_t} frequency - Custom PWM frequency
 * @param {pin_size_t} pwmPin - Pin used as PWM signal output
 * @returns Pointer to a TurboPWM object instance, or NULL if error
 */
TurboPWM *Motor::getSAMD21PWMManager_(uint32_t frequency, pin_size_t pwmPin)
{
    int timer;
    if (!pwmFrequencyInRange_(frequency) || (timer = getSAMD21Timer_(pwmPin)) < 0)
        // Frequency out of range or PWM pin not associated to timer
        return NULL;

    TurboPWM *turboPWM = new TurboPWM();

    // Configure a timer with source frequency 48Mhz...
    turboPWM->setClockDivider(1, false);
    // ...using the timer defined by the chosen PWM output pin,
    // with prescaler set to constant 1
    // and PER calculated from the desired PWM frequency
    // generating a double-slope PWM signal
    uint16_t PER = getSAMD21PER_(frequency);
    turboPWM->timer(timer, 1, PER, false);

    return turboPWM;
}
#endif