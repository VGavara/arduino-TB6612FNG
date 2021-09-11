# Motor example 02
This example is similar to the Motor example 01, but this time it spins from zero to max speed using a custom PWM frequency of 40kHz (40000Hz), what improves the motor performance, reduces noise and increases the motor lifetime.

The example is **only valid for SAMD21 based Arduinos**, and requires installing the additional [SAMD21 Turbo PWM](https://github.com/ocrdu/Arduino_SAMD21_turbo_PWM) library, also available through the Arduino IDE library manager.

The example can be modified by specifying custom frequencies in the range of 732 (default SAMD21 Arduino PWM frequency) to 100000 Hz (100kHz, the max TB6612FNG switching frequency).

Lastly, using custom PWM frequencies redefines the available PWM-enabled pins. Instead of using the documentation PWM pins, these pins must be used:
- On Nano 33 IoT Arduinos: pins 4 to 8 and 11 to 13;
- On Arduino Zero: pins 3, 4, and 8 to 13;
- On MKR series Arduinos: pins 2 to 9. 

In order to properly run the example follow these steps:
1. Carefully study the datasheet before wiring the Arduino and driver. Driver datasheet is in the [/docs/datasheets](https://github.com/VGavara/ArduinoTB6612FNG/tree/stable/docs/datasheets) directory.
2. Wire the Arduino and driver as described in the file MotorExample02_WiringDiagram.png. Have in mind that the driver IC has not only one but several VM, PGND, AO1 and AO2 pins. All the pins must be connected. 
3. Make sure the library files are properly installed in the Arduino IDE library path (see [Arduino Libraries](https://www.arduino.cc/en/Hacking/Libraries) for more information).
4. Set the symbols `DOUT1`, `DOUT2` and `PWMOUT` (by default set to 20, 21 and 12) to the values of Arduino outputs connected to driver AIN1, AIN2 and PWMA respectively.
5. Optionally, set the symbol `LED` (by default set to 13) to the value of your Arduino built-in led output.