# ArduinoTB6612FNG


## Summary
Arduino C++ library for controlling a Toshiba TB6612FNG dual DC motor driver throught the Arduino digital outputs.


## Toshiba TB6612FNG
Toshiba TB6612FNG is a motor driver capable of controlling two DC motors up to 15V max at 1200mA avg. You can find the controller datasheet in the ./doc directory.


## Arduino Library
This C++ library contains a set of classes for controlling the above driver by interfacing it through the Arduino digital outputs.


## Repository structure
### doc
The directory /doc contains documents related to the library, as for instance the TB6612FNG datasheet.

### examples
The directory /examples contains usage examples of each class. It is a good place for getting a quick idea regarding what this library can do for you.

### src
The directory /src contains the library source code.


## Library reference

### Classes

#### Motor
The class `Motor` can be considered the lowest abstraction level class of the library, offering the basic driver operations.

##### Constructor
Initializes a new Motor object instance.
```C++
Motor(PinMap *pinMap)
```
###### Arguments
* `*pinMap`: Pointer to a `PinMap` struct defining the pin mapping between the Arduino and the driver.
###### Notes
* The class constructor will initialize the mapped Arduino pin modes by calling `pinMode`.
###### Example
```C++
// Define digital IO ids on a Arduino NANO 33
const pin_size_t D2 = 2;
const pin_size_t D3 = 3;
const pin_size_t D4 = 4;
const pin_size_t D5 = 5;

// Define the pin mapping for interfacing the driver motor A
PinMap pinMap;
pinMap.in1 = D2; //Digital output D2 is connected to driver AIN1 input
pinMap.in2 = D3; //Digital output D3 is connected to driver AIN2 input
pinMap.pwm = D4; //Digital output D4 is connected to driver PWMA input
pinMap.stby = D5; //Digital output D5 is connected to driver STBY input

Motor motor(&pinMap);
```

##### brake
Performs a motor soft-brake to prevent it rotating.
```C++
void brake()
```
###### Notes
* Read carefully the driver datasheet regarding the electric/electronic implications and requirements of abrupt changes in motor rotation speeds.
###### Example
```C++
// Perform a soft-braking to get an instantaneous rotation stop 
// and preventing the motor rotation
motor.brake();
```

##### run
Makes the motor rotate in a given direction at a given speed
```C++
void run(Direction direction, uint8_t speed)
``` 
###### Arguments
* `direction`: Rotation direction. See enum `Direction` to check the possible values.
* `speed`: Rotation speed, from 1 to 255.
###### Notes
* Calling this function cancels the driver standby mode (if active).
###### Example
```C++
// Make the motor rotate clockwise at full speed
motor.run(Direction::Clockwise, 255);
```

##### standBy
Sets the driver in standby mode.
```C++
void standBy()
``` 
###### Notes
* This function does nothing if the driver STBY input is not mapped. See the `PinMap` struct documentation to get more information.
* The driver standby mode is cancelled if the `run` function is invoked.
###### Example
```C++
// Set the motor driver in standby mode in order to save energy
motor.standby();
```
##### stop
Cuts the energy supply to the motor, allowing it rotating idle.
```C++
void stop()
```
###### Notes
* Read carefully the driver datasheet regarding the electric/electronic implications and requirements of abrupt changes in motor rotation speeds.
###### Example
```C++
// Stop the motor but let it rotating idle
motor.stop();
```


### Enums

#### Direction
Defines the rotation directions of a motor:

```C++
enum Direction
{
    Clockwise = 1,
    CounterClockwise = -1
}
```


### Structs

#### PinMap
Stores the pin mapping, ie, the pin duples that interconnect the Arduino and the TB6612FNG driver.

```C++
typedef struct
{
    pin_size_t in1;
    pin_size_t in2;
    pin_size_t pwm;
    pin_size_t stby;
} PinMap;
```

* Field `in1` must be set to the pin id of the arduino digital output connected to the driver input AIN1 (pin 21) if interfacing the motor A, or input BIN1 (pin 17) if interfacing the motor B.
* Field `in2` must be set to the pin id of the arduino digital output connected to the driver input AIN2 (pin 22) if interfacing the motor A, or input BIN2 (pin 16) if interfacing the motor B.
* Field `pwm` must be set to the pin id of the arduino digital output, PWM capable, connected to the driver pin PWMA (pin 23) if interfacing the motor A, or pin PWMB (pin 15) if interfacing the motor B.
* Field `stby` must be optinally set in case that the driver standby mode was managed from the Arduino. In that case, it must be set to the pin id of the arduino digital output connected to the driver input STBY (pin 19). If the standby mode is not being managed from the Arduino, set this field to 0.


## Misc information
* The library follows the coding style defined by the [Google ++ Style Guide](https://google.github.io/styleguide/cppguide.htm).