// tb6612fng.h
// Library for controlling Toshiba TB6612FNG dual DC motor driver
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef tb6612fng_h
#define tb6612fng_h

#include <Arduino.h>

// Rotation directions
enum Direction
{
    Clockwise = 1,
    CounterClockwise = -1
};

// Arduino output to driver input pin mapping
typedef struct
{
    pin_size_t in1;
    pin_size_t in2;
    pin_size_t pwm;
    pin_size_t stby;
} PinMap;

// Interfaces a motor controlled by a TB6612FNG driver
class Motor
{
public:
    // Summary: Initializes the Motor class
    // Param pinMap: Mapping of motor inputs and Arduino pins
    // Note: Set pinMap.stby to 0 to disable driver standby management
    // Note: The mapped Arduino pins will be initialized by this function
    Motor(PinMap *pinMap);

    // Summary: Runs the motor in a given direction at a given speed
    // Param direction: Rotation direction
    // Param speed: Rotation speed, from 1 to 255
    // Note: Standby mode will be switched off if this function is invoked
    void run(Direction direction, uint8_t speed);

    // Summary: Stops the motor
    // Note: Stopping just cuts the motor power supply,
    //  therefore doesn't cancel the motor inertial rotation.
    //  Use Brake() if you want to cancel the inertial rotation.
    void stop();

    // Summary: Short-brakes the motor
    // Note: Short-braking cancels the inertial motor rotation,
    //  therefore is an energy consuming process
    void brake();

    // Summary: Sets the driver in standby mode
    // Note: This function does nothing if the class constructor
    //  was called with io_map.stby set to 0
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