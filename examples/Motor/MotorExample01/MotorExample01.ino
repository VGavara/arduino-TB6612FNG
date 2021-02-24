// MotorExample01.ino
// Usage example of the class Motor defined by the Arduino TB6612FNG Toshiba driver Library
// Copyright (c) Vicente Gavara. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <tb6612fng.h>

#define DOUT1 2  // Arduino digital IO
#define DOUT2 3  // Arduino digital IO
#define PWMOUT 4 // Arduino digital IO with PWM feature
#define LED 13   // Arduino digital IO connected to the builtin led

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
}

void loop()
{
    if (speed > 0)
    {
        // Run the motor clockwise at current speed
        motor->run(Direction::Clockwise, speed * 255);

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
