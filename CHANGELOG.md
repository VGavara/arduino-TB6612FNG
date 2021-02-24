# Arduino TB6612FNG library changelog

- [Version 0](#version-0)
  * [Release 0.3.0](##release-v0.3.0)
  * [Release 0.2.0](##release-v0.2.0)
  * [Release 0.1.0](##release-v0.1.0)
  * [Release 0.0.1](##release-v0.0.1)

# Version 0

## Release v0.3.0
### New features
- `Motor` class: 
  * Support to custom PWM frequency on SAMD21 based hardware.
  * Support to 16-bit speed resolution.
- `Spinner` class: Support to 16-bit speed resolution on spin maps.
 
### Improved features
- Documentation improved:
  * Index document in `Spinner` examples.
  * "At a glance" and "Getting started" sections added to root README.md.

### Fixed problems
None relevant.

### Deprecated
- `Motor` class: 8-bit resolution speeds with a range of 0-255 no longer supported.
- `Spinner` class: 8-bit resolution speeds with a range of 0-255 no longer supported.
- 
## Release v0.2.0
### New features
- `Spinner`class: Support to linear maps with more than one, single stage.

### Improved features
- Documentation improved:
  * Index document in `Spinner` examples.
  * "At a glance" and "Getting started" sections added to root README.md .

### Fixed problems
- Spinner documentation fixed.
- Driver documentation fixed.

### Deprecated
None

## Release v0.1.0
### New features
- New class `Driver` for managing driver specific features as the driver standby mode.
- New class `Spinner` for managing motor acceleration/deceleration. Only lineal acceleration is supported by now.

### Improved features
- Code documentation migrated to JSDoc.
- Project documentation restructured: code reference is stored in specific files, thus reducing the /README.md size.

### Fixed problems
No fixed problems.

### Deprecated
The standby management through the `Motor` class is deprecated. Library users must follow these guidelines:
- Remove any reference to `Motor::standby()` function and manage the driver standby status through the `standBy()` functions of the `Driver` class.
- Remove any reference to `PinMap.stby` struct member.

## Release v0.0.1
- Initial release containing the `Motor` class plus an example.
