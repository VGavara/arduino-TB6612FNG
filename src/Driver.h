// Driver.h
// Header file for Driver class
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef DRIVER_H
#define DRIVER_H

#include <Arduino.h>

/**
 * Represents a TB6612FNG driver
 * @class
 */
class Driver
{
public:
    /**
     * Creates a TB6612FNG driver
     * @constructor
     * @param {pin_size_t} stbyPin - Arduino digital output connected to the driver STBY input
     * @note The pin mode will be initialized by the class constructor
     * @note The driver WILL BE automatically set in NON standby mode
     */
    Driver(pin_size_t stbyPin);

    /**
     * Creates a TB6612FNG driver
     * @constructor
     * @param {pin_size_t} stbyPin - Arduino digital output connected to the driver STBY input
     * @param {bool} standbyOn - Boolean value indicating if the driver is set in standby mode by the constructor
     * @note The pin mode will be initialized by the class constructor
     */
    Driver(pin_size_t stbyPin, bool standbyOn);

    /**
     * Manages the driver standby mode
     * @param {bool} standByOn - True to set the driver in standby mode, else false
     */
    void standBy(bool standByOn);

    /**
     * Returns the driver standby mode
     * @returns True if the driver is in standby mode, else false
     */
    bool standBy();

private:
    pin_size_t stbyPin_;
};

#endif