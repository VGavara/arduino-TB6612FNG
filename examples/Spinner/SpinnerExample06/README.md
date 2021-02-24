# Spinner example 06
This example makes a motor spinning up from 40% of its max speed (engine speed 26214 in a scale of 0-65535) to 80% of its max speed (engine speed 52428 in a scale of 0-65535) in clockwise direction. Spinning up process takes 10s (10000ms) and, once it is completed, the led blinks and motor spins down from its current speed to full stopped in 30s (30000ms). Once it's fully stopped, the led is light.

Though performing the same operation that [SpinnerExample05](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/examples/Spinner/SpinnerExample05), this example introduces the usage of SAMD21 custom PWM frequency stating a working frequency of 40kHz instead of 732Hz (default PWM frequency on SAMD21 based Arduinos). 

This example is **only compatible with SAMD21 based Arduinos (Nano 33 IoT, Zero and MKR series)**. Have also in mind that using SAMD21 custom PWM frequency implies using a set of PWM-enabled outputs different to the default PWM-enabled outputs. Specifically, the PWM-enabled outputs are:
- On Nano 33 IoT Arduinos: pins 4 to 8 and 11 to 13.
- On Arduino Zero: pins 3, 4, and 8 to 13.
- On MKR series Arduinos: pins 2 to 9. 

In order to properly run the example follow these steps:
1. Carefully study the datasheet before wiring the Arduino and driver. Driver datasheet is in the [/docs/datasheets](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/docs/datasheets) directory.
2. Wire the Arduino and driver as described in the file SpinnerExample06_WiringDiagram.png. Have in mind that the driver IC has not only one but several VM, PGND, AO1 and AO2 pins. All the pins must be connected. 
3. Make sure the library files are properly installed in the Arduino IDE library path (see [Arduino Libraries](https://www.arduino.cc/en/Hacking/Libraries) for more information).
4. Set the symbols `DOUT1`, `DOUT2` and `PWMOUT` (by default set to 20, 21 and 12) to the values of Arduino outputs connected to driver AIN1, AIN2 and PWMA respectively.
5. Optionally, set the symbol `LED` (by default set to 13) to the value of your Arduino built-in led output.
