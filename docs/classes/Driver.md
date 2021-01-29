# Class Driver. Reference.
The class `Driver`, together with the class `Motor`, can be considered the lowest abstraction level classes of the library. They offer the basic driver operations.

# Table of contents
- [Functions](#functions)
  * [Constructor](#constructor)
  * [Constructor (2)](#constructor-2)
  * [standBy()](#standby)
  * [standBy() (2)](standby-2)

# Functions

## Constructor
Initializes a new `Driver` object instance, setting the driver in non-standBy mode.
```C++
Driver(pin_size_t stbyPin)
```

### Arguments
* `stbyPin`: Arduino digital output connected to the driver STBY input.

### Notes
* The class constructor will initialize the mapped Arduino pin mode by calling `pinMode`.

### Example
```C++
#include <tb6612fng>

// Define digital IO id
const pin_size_t DSTBY = 5;

// Create a Driver object instance using the Arduino digital output 5 
// for managing the driver standby and set the driver in non-standby mode
Driver driver(DSTBY);
```

## Constructor (2)
Initializes a new `Driver` object instance, allowing the user choosing the initial standby mode
```C++
Driver(pin_size_t stbyPin, bool standbyOn)
```

### Arguments
* `stbyPin`: Arduino digital output connected to the driver STBY input.
* `standbyOn`: Boolean value indicating if the driver is initially set in standby mode by the constructor.

### Notes
* The class constructor will initialize the mapped Arduino pin mode by calling `pinMode`.

### Example
```C++
#include <tb6612fng>

// Define digital IO id
const pin_size_t DSTBY = 5;

// Create a Driver object instance using the Arduino digital output 5 
// for managing the driver standby and set the driver in non-standby mode
Driver driver(DSTBY, false);
```

## standBy()
Manages the driver standBy mode
```C++
void standBy(bool standByOn)
```

### Arguments
* `standByOn`: `true` for setting the driver in standBy mode, else `false`;

### Example
```C++
#include <tb6612fng>

// Define digital IO id
const pin_size_t DSTBY = 5;

// Create a Driver object instance using the Arduino digital output 5 
// for managing the driver standby and set the driver in non-standby mode
Driver driver(DSTBY);

// Set the driver in standby mode
driver.standBy(true);
```

## standBy() (2)
Returns the driver standby mode.
```C++
bool standBy()
```

### Returns
`true` if the Arduino digital output is setting the driver in standby mode (ie, it is in low status), else `false`.

### Example
```C++
#include <tb6612fng>

// Define digital IO id
const pin_size_t DSTBY = 5;

// Create a Driver object instance using the Arduino digital output 5 
// for managing the driver standby and set the driver in non-standby mode
Driver driver(DSTBY, false);

// A falsy return value is expected
bool isStandby = driver.standBy();
```
