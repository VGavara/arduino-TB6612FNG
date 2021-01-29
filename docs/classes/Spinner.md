# Class Spinner. Reference.

# Table of contents
- [Overview](#overview)
  * [Spin points and maps](#spin-points-and-maps)
  * [How Spinner works](#how-spinner-works)
- [Functions](#functions)
  * [Constructor](#constructor)
  * [Constructor (2)](#constructor-2)
  * [abort()](#abort--)
  * [spin()](#spin--)
  * [start()](#start--)
- [Enums](#enums)
  * [Direction](#direction)
- [Types](#types)
  * [SpinnerCB](#spinnercb)
- [Structs](#structs)
  * [SpinPoint](#pinmap)

# Overview
The class `Spinner` builds upon the class `Motor`, adding acceleration features to it. 

By acceleration must be understood a constant or variable speed change in a given period of time, therefore including an speed increase (commonly known as acceleration) or decrease (commonly known as decceleration).

In the current release, the `Spinner` class supports a linear (ie constant) acceleration in a single period of time. As an example, such kind of acceleration could be described as *start now increasing the motor speed from 100 to 200 in 10000ms*.

Since `Spinner` is based in the class `Motor` a reading of its documentations is recommended.

## Spin points and maps
A spinning, or acceleration, can be described as a sequence of duples `speed-time` in a given period. For instance, if we are spinning (accelerating) a motor from 100 to 200 in 10000ms, the first duple in the spinning would be `(speed:100, time:0)` whereas the last one would be `(speed:200, time:10000)`. The duple `speed-time` is what this library names `spinPoint`.

A sequence of `spinPoint`'s would describe a more or less complex spinning process. We could describe a spinning as we did in the paragraph above (spin from 100 to 200 in 10000ms) but we could also make it more complex, adding more spin *stages*. So, for instance, we could define a spinning starting from speed 100 to reach speed 200 in 10000ms (as before) but then lowering speed from 200 to 1 in 5000ms. In that way our motor would accelerate and then deccelerate until virtually stopping.

An `spinMap` is a sorted list of `spinPoint`'s that define a more or less complex spinning process. The `spinPoint`'s in a `spinMap` can be considered as stages, or milestones, in the spinning process. As an example of `spinMap`, the previous simplest spinning process could be described as `[(speed:100, time:0),(speed:200, time:10000)]` whereas the more complex one could be described as `[(speed:100, time:0),(speed:200, time:10000),(speed:1, time:15000)]`.

### Spin map integrity
When an spin map is assigned to a spinning process, an integrity check is done before start spinning. If the integrity check fails, the spinning start fails and the `start()` function returns `NULL`, as explained below. The rules for creating valid spin maps are:

1. A map must have at least two spin points.
2. The first map point must have its time set to zero.
3. The elapsed time of an spin point cannot be lower than the preceding point time.


## How Spinner works
The `Spinner` class way of working is based on periodic calculations to state the motor speed regarding the elapsed time that has passed since the spin start.

To maximize compatibility it doesn't use internal timers, so the user is responsible of calling the `Spinner.spin()` (exposed below) periodically. Some ways of doing it are:

- Calling it in the main program loop: This is the recommended way, since it guarantees the maximum spin resolution and minimizes the program complexity.
- Calling it by defining a user timer.
- Calling it by using alternative approaches, as using `Tick` libraries.

`Spinner` status check is based on two callback functions that are called when the motor speed changes and when the spin process finishes. However, its usage is optional and the spin status can be also checked by the result returned by `Spinner.spin()`.

# Functions

## Constructor
Creates an acceleration/deceleration controller, an spinner, for TB6612FNG driven motors.
```C++
Spinner(Motor *motor)
```

### Arguments
* `*motor`: Pointer to a `Motor` class representing the motor that is being spinned.

### Example
```C++
#include <tb6612fng>

// Define digital IO ids
const pin_size_t D2 = 2;
const pin_size_t D3 = 3;
const pin_size_t D4 = 4;
const pin_size_t D5 = 5;

// Define the pin mapping for interfacing the driver motor A
PinMap pinMap;
pinMap.in1 = D2; //Digital output D2 is connected to driver AIN1 input
pinMap.in2 = D3; //Digital output D3 is connected to driver AIN2 input
pinMap.pwm = D4; //Digital output D4 is connected to driver PWMA input

// Create a Motor object instance using the above pin map
Motor motor(&pinMap);

// Create a spinner for the driver motor A, no callback functions are being used
Spinner spinner(&motor);
```

## Constructor (2)
Creates an acceleration/deceleration controller, an spinner, for TB6612FNG driven motors and manages the events of speed updates and spin finish by calling callback functions.
```C++
Spinner(Motor *motor, SpinnerCB spinUpdated, SpinnerCB spinFinished)
```

### Arguments
* `*motor`: Pointer to a `Motor` class representing the motor that is being spinned.
* `spinUpdated`: Pointer to a `SpinnerCB` callback function for the event of motor speed updated. The function will receive as argument a pointer to a constant `SpinPoint` struct with the last speed set to the motor and the elapsed time, in milliseconds, since the spin start. See `SpinnerCB` type documentation for more info.
* `spinFinished`: Pointer to a `SpinnerCB` callback function for the event of spin finished. The function will receive as argument a pointer to a constant `SpinPoint` struct with the final spinning speed and the spin process duration, in milliseconds. See `SpinnerCB` type documentation for more info.

### Example
```C++
#include <tb6612fng>

// Callback function for the spinner event of spin point updated
// This function will be invoked whenever a new speed is set to the motor.
// The function argument spinPoint will contain both the new speed
// and the elapsed time (milliseconds) from the spin start.
void spinUpdated(const SpinPoint *spinPoint)
{
  Serial.print("Spin updated. ");
  Serial.print("Speed: ");
  Serial.print(spinPoint->speed);
  Serial.print(" Elapsed time: ");
  Serial.println(spinPoint->time);
}

// Callback function for the spinner event of spin finished
// This function will be invoked when the last point of the spin map was reached
// The function argument spinPoint will contain both the last speed
// and the elapsed time (milliseconds) from the spin start.
// Note that the elapsed time will be the real elapsed time,
// that could be higher to that set in the spin map last point.
void spinFinished(const SpinPoint *spinPoint)
{
  Serial.print("Spin finished");
  Serial.print("Final speed: ");
  Serial.print(spinPoint->speed);
  Serial.print(" Overall spin ellapsed time: ");
  Serial.println(spinPoint->time);
}

// Define digital IO ids
const pin_size_t D2 = 2;
const pin_size_t D3 = 3;
const pin_size_t D4 = 4;
const pin_size_t D5 = 5;

// Define the pin mapping for interfacing the driver motor A
PinMap pinMap;
pinMap.in1 = D2; //Digital output D2 is connected to driver AIN1 input
pinMap.in2 = D3; //Digital output D3 is connected to driver AIN2 input
pinMap.pwm = D4; //Digital output D4 is connected to driver PWMA input

// Create a Motor object instance using the above pin map
Motor motor(&pinMap);

// Create a spinner for the driver motor A. Manage the spin status with callback functions
Spinner spinner(&motor, spinUpdated, spinFinished);
```

## abort()
Aborts an spin operation, keeping the motor rotating at the last speed reached by the aborted spin operation.
```C++
const SpinPoint *abort()
``` 

### Return value
Pointer to a `SpinPoint` struct containing the last reached spin map point, or `NULL` if no spin operation was aborted.

### Notes
* `abort()` doesn't call the callback function associated to the event of a spin process finished.

### Example
```C++
SpinPoint currentSpinPoint = spinner.abort();
if (currentSpinPoint) {
  Serial.print("Spin operation aborted.");
  Serial.print(" Current speed: ");
  Serial.print(spinPoint->speed);
  Serial.print(" Elapsed time: ");
  Serial.println(spinPoint->time);
}
else {
  Serial.print("No spin operation aborted");
}
```

## spin()
Updates a running spin operation.
```C++
const SpinPoint *spin()
```

### Return value
Pointer to a read-only `SpinPoint` struct with the current motor speed and the elapsed time since the spinning start, or `NULL` if no spinning is in progress. 

See struct `SpinMap` documentation for further information.

### Notes
* This function must be called periodically. To achieve the smoothest spin, a call periodicity equal to 1 millisecond is recommended.

### Example 1
```C++
// Scenario in which no callbacks are used and the spin status is checked
// by the value returned by spinner.spin(). spinner.spin() should be called
// once per millisecond to optimally drive the spinning process 
SpinPoint currentSpinPoint = spinner.spin();
if (currentSpinPoint) {
    Serial.print("Current spin speed: ");
    Serial.print(spinPoint->speed);
    Serial.print(" Current spin speed elapsed time: ");
    Serial.println(spinPoint->time);
}
else {
    Serial.print("No spin operation in progress");
}
```

### Example 2
```C++
// Scenario in which callback functions are used: Just call spinner.spin()
// at least once per millisecond to optimally drive the spinning process
spinner.spin();
```

## start()
Starts a motor lineal acceleration/deceleration.
```C++
const SpinPoint *start(Direction direction, SpinPoint spinMap[])
```

### Arguments
* `direction`: Rotation direction. See enum `Direction` to check the possible values.
* `spinMap`: Spin map containing only two points: the start and end spin points. See struct `SpinMap` documentation for further information.

### Return value
Pointer to a read-only `SpinPoint` struct with the initial motor speed, or `NULL` if the spinning start failed due to a wrong spin map definition. See "Spin points and maps" section to get further information about map definition. See struct `SpinMap` documentation for further information.

### Notes
* Only maps with two spin points are supported in this version. The first spin point must have the speed value set to the initial spin speed and the time value set to zero, the second and last spin point must have the speed value set to the final spin speed and the time value set to the spin ellapsed time.
* Starting a spin operation will abort a previous running spinning operation.

### Example
```C++
// Declare a spin map of two elements
SpinPoint spinMap[2];

// Define the spin map
// The first map point (time = 0) states an initial speed of 100
spinMap[0].time = 0;
spinMap[0].speed = 100;
// The last map point states a final speed of 200, 10000 milliseconds after start spinning
spinMap[1].time = 10000;
spinMap[1].speed = 200;

// Start spinning the motor in clockwise direction
spinner->start(Clockwise, spinMap);
```

# Enums

## Direction
Defines the rotation directions of a motor.

```C++
enum Direction
{
    Clockwise = 1,
    CounterClockwise = -1
}
```

# Types

## SpinnerCB
Signature for the callback function that will be invoked by the class if initialized with the right constructor.

```C++
typedef void (*SpinnerCB)(const SpinPoint *spinPoint);
```

### Callback function arguments
* `spinPoint`: Pointer to constant (read-only) `SpinPoint` struct. The specific content depends on the callback (see Constructor 2 documentation).

### Callback function return value
`void`

# Structs

## SpinPoint
Represents a duple speed-time in a spinning process, ie, the motor speed (from 0 to 255) *time* milliseconds after starting an spinning process.

```C++
struct SpinPoint
{
    uint8_t speed;
    uint16_t time;
};
```

* Field `speed` represents the motor speed in a scale from 0 to 255.
* Field `time` represents the elapsed time, from 1 to 65535 milliseconds, after start spinning in which `speed` is reached.
