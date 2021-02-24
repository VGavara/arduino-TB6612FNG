# Class Motor. Reference.
The class `Motor`, together with the class `Driver`, can be considered the lowest abstraction level classes of the library. They offer the basic driver operations.

# Table of contents
- [Functions](#functions)
  * [Constructor](#constructor)
  * [brake()](#brake--)
  * [run()](#run--)
  * [stop()](#stop--)
- [Enums](#enums)
  * [Direction](#direction)
- [Structs](#structs)
  * [PinMap](#pinmap)

# Functions

## Constructor
Initializes a new `Motor` object instance.
```C++
Motor(PinMap *pinMap)
```

### Arguments
* `*pinMap`: Pointer to a `PinMap` struct defining the pin mapping between the Arduino and the driver.

### Notes
* The class constructor will initialize the mapped Arduino pin modes by calling `pinMode`.

### Example
```C++
#include <tb6612fng>

// Define digital IO ids
const pin_size_t D2 = 2;
const pin_size_t D3 = 3;
const pin_size_t D4 = 4;

// Define the pin mapping for interfacing the driver motor A
PinMap pinMap;
pinMap.in1 = D2; //Digital output D2 is connected to driver AIN1 input
pinMap.in2 = D3; //Digital output D3 is connected to driver AIN2 input
pinMap.pwm = D4; //Digital output D4 is connected to driver PWMA input

// Create a Motor object instance using the above pin map
Motor motor(&pinMap);
```

## brake()
Performs a motor soft-brake to prevent it rotating.
```C++
void brake()
```

### Notes
* Read carefully the driver datasheet regarding the electric/electronic implications and requirements of abrupt changes in motor rotation speeds.

### Example
```C++
// Perform a soft-braking preventing the motor rotation
motor.brake();
```

## run()
Makes the motor rotate in a given direction at a given speed.
```C++
void run(Direction direction, uint16_t speed)
``` 
### Arguments
* `direction`: Rotation direction. See enum `Direction` to check the possible values.
* `speed`: Rotation speed, from 1 to 65535.

### Example
```C++
// Make the motor rotate clockwise at full speed
motor.run(Direction::Clockwise, 65535);
```

## stop()
Cuts the energy supply to the motor, allowing it rotating idle.
```C++
void stop()
```

### Notes
* Read carefully the driver datasheet regarding the electric/electronic implications and requirements of abrupt changes in motor rotation speeds.

### Example
```C++
// Stop the motor but let it rotating idle
motor.stop();
```


# Enums

## Direction
Defines the rotation directions of a motor:

```C++
enum Direction
{
    Clockwise = 1,
    CounterClockwise = -1
}
```


# Structs

## PinMap
Stores the pin mapping, ie, the pin duples that interconnect the Arduino and the TB6612FNG driver.

```C++
typedef struct
{
    pin_size_t in1;
    pin_size_t in2;
    pin_size_t pwm;
} PinMap;
```

* Field `in1` must be set to the pin id of the arduino digital output connected to the driver input AIN1 (pin 21) if interfacing the motor A, or input BIN1 (pin 17) if interfacing the motor B.
* Field `in2` must be set to the pin id of the arduino digital output connected to the driver input AIN2 (pin 22) if interfacing the motor A, or input BIN2 (pin 16) if interfacing the motor B.
* Field `pwm` must be set to the pin id of the arduino digital output, PWM capable, connected to the driver pin PWMA (pin 23) if interfacing the motor A, or pin PWMB (pin 15) if interfacing the motor B.
