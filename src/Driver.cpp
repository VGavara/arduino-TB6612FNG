// Driver.cpp
// Implementation of the Driver class
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Driver.h"

// Public functions

/**
 * Creates a TB6612FNG driver
 * @constructor
 * @param {pin_size_t} stbyPin - Arduino digital output connected to the driver STBY input
 */
Driver::Driver(pin_size_t stbyPin) : Driver(stbyPin, false) {}

/**
 * Creates a TB6612FNG driver
 * @constructor
 * @param {pin_size_t} stbyPin - Arduino digital output connected to the driver STBY input
 * @param {bool} standbyOn - Boolean value indicating if the driver is set in standby mode by the constructor
 */
Driver::Driver(pin_size_t stbyPin, bool standByOn) : stbyPin_(stbyPin)
{
    // Initialize the arduino pin
    pinMode(stbyPin_, OUTPUT);

    // Set the standby mode
    Driver::standBy(standByOn);
}

/**
 * Manages the driver standby mode
 * @param {bool} standByOn - True to set the driver in standby mode, else false
 */
void Driver::standBy(bool standByOn)
{
    // Set the right outpuy value
    digitalWrite(stbyPin_, (standByOn ? LOW : HIGH));
}

/**
 * Returns the driver standby mode
 * @returns True if the driver is in standby mode, else false
 */
bool Driver::standBy()
{
    // Set the right outpu value
    return (digitalRead(stbyPin_) == LOW);
}
