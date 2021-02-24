# Arduino TB6612FNG library
![License:](https://img.shields.io/github/license/vgavara/ArduinoTB6612FNG)
![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/VGavara/ArduinoTB6612FNG?include_prereleases)

# Table of contents
- [Overview](#overview)
- [At a glance](#at-a-glance)
  * [Driver class](#driver-class)
  * [Motor class](#motor-class)
  * [Spinner class](#spinner-class)
- [Getting started](#getting-started)
- [Repository structure](#repository-structure)
- [Contributions to the project](#contributions-to-the-project)
- [Attributions and references](#attributions-and-references)

# Overview
C++ library for controlling a Toshiba TB6612FNG motor driver throught the Arduino digital outputs. 

The Toshiba TB6612FNG is a motor driver capable of controlling two DC motors up to 15V (max) at 1200mA (avg). You can find the controller datasheet in the docs [datasheet](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/docs/datasheets) directory.

This C++ library contains a set of classes for controlling the above driver by interfacing it through the Arduino digital outputs:
- The `Motor` class offers basic control on every of the two brushed DC motors the driver can handle.
- The `Driver` class offers basic control on the whole driver (basically managing its standby mode).
- The `Spinner` class adds acceleration/decceleration features to the `Motor` class.

# At a glance

## Driver class
```C++
#include <tb6612fng>

// Digital IO 5 is connected to driver STBY input
const pin_size_t DSTBY = 5;

Driver driver(DSTBY);
driver.standBy(true);

if(driver.standBy())
   driver.standBy(false); 
```
## Motor class
```C++
#include <tb6612fng>

PinMap pinMap;
pinMap.in1 = 2; //Digital output 2 is connected to driver AIN1/BIN1 input
pinMap.in2 = 3; //Digital output 3 is connected to driver AIN2/BIN2 input
pinMap.pwm = 4; //Digital output 4 is connected to driver PWMA/PWMB input

// Use a custom PWM frequency of 40kHz (only valid for SAMD21 based Arduinos).
// Omit the second argument for using default PWM frequency.
Motor motor(&pinMap, 40000);

uint8_t speed = 65535;
motor.run(Clockwise, speed);

delay(50);

motor.brake();
```

## Spinner class
```C++
#include <tb6612fng>

Spinner *spinner;
SpinPoint spinMap[2];

void spinUpdated(const SpinPoint *spinPoint)
{
    // This code will run every time the motor speed changes
}

void spinFinished(const SpinPoint *spinPoint)
{
    // This code will run when the spin process finished
}

void setup()
{
    PinMap pinMap;
    pinMap.in1 = 2; //Digital output 2 is connected to driver AIN1/BIN1 input
    pinMap.in2 = 3; //Digital output 3 is connected to driver AIN2/BIN2 input
    pinMap.pwm = 4; //Digital output 4 is connected to driver PWMA/PWMB input
    
    spiner = new Spinner(new Motor(&pinMap), spinUpdated, spinFinished);
    
    spinMap[0].time = 0;
    spinMap[0].speed = 21845;   // Initial speed (21845/65535 = 33% of max speed)
    spinMap[1].time = 10000;
    spinMap[1].speed = 43690;   // Intermediate speed after 10 seconds (66% of max speed)
    spinMap[2].time = 40000;
    spinMap[2].speed = 0;       // Final speed after 40 seconds (stopped)

    spinner->start(Clockwise, spinMap);
}

void loop()
{
    // Spin the motor
    spinner->spin();

    // Do other stuff, spin() doesn't block the loop
}
```

# Getting started
First, download the library source files from the [latest release available](https://github.com/VGavara/ArduinoTB6612FNG/releases/latest) and install them locally by following the tutorial [Installing Additional Arduino Libraries](https://www.arduino.cc/en/guide/libraries), specifically as explained in the sections "Importing a .zip library" or "Manual installation".

Once installed locally, you can download and test any of the examples contained in the [examples](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/examples) directory. Every example contains hardware wiring information to help you connecting your Arduino and TB6612FNG driver.

Finally, you can get detailed information of every class by reading the references contained in the directory [docs/classes](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/docs/classes).

# Repository structure
This repository is structured in these directories:
- [/docs](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/docs): It contains the library documentation, as classes references and datasheets.
- [/examples](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/examples): It contains usage examples of each class. It is a good place for getting a quick idea regarding what this library can do for you.
- [/src](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/src): It contains the library source code.

# Contributions to the project
In case you were interested in participating in this project, read [CONTRIBUTING.md](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/CONTRIBUTING.md) for further information.

# Attributions and references
* The documentation badges are generated by [shields.io](https://img.shields.io).
* The tables of contents are generated with the [Online GitHub Wiki TOC generator](https://ecotrust-canada.github.io/markdown-toc/).
* The library follows the coding style defined by the [Google ++ Style Guide](https://google.github.io/styleguide/cppguide.html).
