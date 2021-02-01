// Motor.h
// Header file for Motor class
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#if defined(__SAMD21G18A__)
#include <SAMD21turboPWM.h>
#endif

#if defined(__SAMD21G18A__)
#if defined(ARDUINO_SAMD_NANO_33_IOT)
// PWM pins associated to each timer in a Arduino SAMD Nano 33
const uint8_t kSam32TimerPinMap[3][4] = {{5, 6, 8, 12}, {4, 7, 0, 0}, {11, 13, 0, 0}};
#elif defined(ARDUINO_SAMD_ZERO)
// PWM pins associated to each timer in a Arduino SAMD Zero
const uint8_t kSam32TimerPinMap[3][4] = {{3, 4, 10, 12}, {8, 9, 0, 0}, {11, 13, 0, 0}};
#else
// PWM pins associated to each timer in a Arduino SAMD MKR series
const uint8_t kSam32TimerPinMap[3][4] = {{4, 5, 6, 7}, {2, 3, 0, 0}, {8, 9, 0, 0}};
#endif
#endif

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
 */
typedef struct
{
    pin_size_t in1;
    pin_size_t in2;
    pin_size_t pwm;
} PinMap;

#if defined(__SAMD21G18A__)
/**
 * SAMD21 timer configuration for custom PWM frequency
 * @typedef {struct} SAMD21CustomPWM
 * @property {uint16_t}} clockDivider - Main clock divider
 * @property {uint16_t}} tccPrescaler - TCCx prescaler
 * @property {uint32_t}} resolution - Resolution (steps)
 */
typedef struct
{
    uint16_t clockDivider;
    uint16_t tccPrescaler;
    uint32_t resolution;
} SAMD21CustomPWM;
#endif

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
     * @note The mapped Arduino pins will be initialized by this function
     */
    Motor(PinMap *pinMap);

#if defined(__SAMD21G18A__)
    /**
     * Creates a motor controlled by a TB6612FNG driver 
     * with custom PWM frequency for SAMD21 processors
     * @constructor
     * @param {PinMap*} pinMap - Mapping of motor inputs and Arduino pins
     * @param {SAMD21CustomPWM*} customPWM - SAMD21 custom PWM timer configuration
     * @note The mapped Arduino pins will be initialized by this function
     */
    Motor(PinMap *pinMap, SAMD21CustomPWM *customPWM);
#endif

    /**
     * Runs the motor in a given direction at a given speed
     * @param {Direction} direction - Motor rotation direction
     * @param {uint8_t} speed - Motor rotation spped, from 1 to 255
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

private:
    PinMap pinMap_;
    bool customPWM_ = false;

    void rotateCW_(PinMap *pinMap);
    void rotateCCW_(PinMap *pinMap);
    void setRotationSpeed_(PinMap *pinMap, uint8_t speed);
    void stopRotation_(PinMap *pinMap);
    void brakeRotation_(PinMap *pinMap);

#if defined(__SAMD21G18A__)
    TurboPWM samd21PWM_;
    int8_t getSAMD21Timer_(pin_size_t pwmPin);
#endif
};

#endif