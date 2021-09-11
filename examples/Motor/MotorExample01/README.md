# Motor example 01
This example makes a motor spinning from zero to max speed in clockwise direction. Speed is increased every 50ms so max speed is reached after 12,3s. Once it is reached, motor stops and a digital output, intended to light a led, is set.

In order to properly run the example follow these steps:
1. Carefully study the datasheet before wiring the Arduino and driver. Driver datasheet is in the [/docs/datasheets](https://github.com/VGavara/ArduinoTB6612FNG/tree/stable/docs/datasheets) directory.
2. Wire the Arduino and driver as described in the file MotorExample01_WiringDiagram.png. Have in mind that the driver IC has not only one but several VM, PGND, AO1 and AO2 pins. All the pins must be connected. 
3. Make sure the library files are properly installed in the Arduino IDE library path (see [Arduino Libraries](https://www.arduino.cc/en/Hacking/Libraries) for more information).
4. Set the symbols `DOUT1`, `DOUT2` and `PWMOUT` (by default set to 1, 2 and 3) to the values of Arduino outputs connected to driver AIN1, AIN2 and PWMA respectively.
5. Optionally, set the symbol `LED` (by default set to 13) to the value of your Arduino built-in led output.