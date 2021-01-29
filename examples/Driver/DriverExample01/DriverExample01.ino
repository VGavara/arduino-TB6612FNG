// DriverExample01.ino
// Usage example of the class Driver defined by the Arduino TB6612FNG Toshiba driver Library
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <tb6612fng.h>

#define DOUT1 20  // Arduino digital IO
#define DOUT2 21  // Arduino digital IO
#define PWMOUT 19 // Arduino digital IO with PWM feature
#define SBYOUT 18 // Arduino digital IO with PWM feature
#define LED 13    // Arduino digital IO connected to the builtin led

Driver *driver;
Motor *motor;
uint8_t speed;

void setup()
{
    // Declare and initialize the pin mapping
    // for interfacing the driver motor A
    PinMap pinMap;

    pinMap.in1 = DOUT1;  // Arduino DOUT1 output is connected to driver AIN1 input
    pinMap.in2 = DOUT2;  // Arduino DOUT2 output is connected to driver AIN2 input
    pinMap.pwm = PWMOUT; // Arduino PWMOUT output is connected to driver PWMA input

    // Create a Motor object instance
    motor = new Motor(&pinMap);

    // Initialize the led output
    // No need of initializing the mapped pins
    // since they are initialized by the Motor constructor
    pinMode(LED, OUTPUT);

    // Initialize the variable
    // that will store the motor speed
    speed = 1;

    // Create a Driver object instance defining the Arduino digital output SBYOUT
    // as connected to the driver STBY input. By default this constructor
    // will initially disable the driver standby mode
    driver = new Driver((pin_size_t)SBYOUT);

    if (!driver->standBy())
    {
        // Set the variable standBy to true if you want to set the driver in standby mode.
        // In standby mode the motor will not run.
        // Set the variable standBy to false to disable the driver standby mode
        // and thus allow the motor running.
        bool standBy = true;

        driver->standBy(standBy);
    }
}

void loop()
{
    if (speed > 0)
    {
        // Run the motor clockwise at current speed
        motor->run(Direction::Clockwise, speed);

        // Perform a delay of 50ms
        delay(50);

        // Increase the speed value.
        // speed variable will overflow to 0
        // after increasing it 255 times
        // ie, after 255*50ms = 12,3 secs.
        speed++;
    }
    else
    {
        // Speed is 0: Stop the motor
        motor->stop();

        // Light the led to indicate that the process is finished
        digitalWrite(LED, HIGH);
    }
}
