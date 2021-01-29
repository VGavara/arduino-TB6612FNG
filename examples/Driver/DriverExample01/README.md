# Driver example 01
This example is an evolution of the [MotorExample01](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/examples/Motor/MotorExample01): It spins a motor from zero to max speed in clockwise direction. Speed is increased every 50ms so max speed is reached after 12,3s. Once it is reached, motor stops and a digital output, intended to light a led, is set.

However, in this example an Arduino digital output is connected to the the driver STBY input, as can be seen in the [wiring diagram](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/examples/Driver/DriverExample01/DriverExample01_WiringDiagram.png), and the driver standby mode is managed by creating an instance of the `Driver` class: If the driver is set in standby mode, the motor will not rotate.

In order to properly run the example follow these steps:
1. Carefully study the datasheet before wiring the Arduino and driver. Driver datasheet is in the [/docs/datasheets](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/docs/datasheets) directory.
2. Wire the Arduino and driver as described in the file [DriverExample01_WiringDiagram.png]((https://github.com/VGavara/ArduinoTB6612FNG/tree/main/examples/Driver/DriverExample01/DriverExample01_WiringDiagram.png)). Have in mind that the driver IC has not only one but several VM, PGND, AO1 and AO2 pins. All the pins must be connected. 
3. Make sure the library files are properly installed in the Arduino IDE library path (see [Arduino Libraries](https://www.arduino.cc/en/Hacking/Libraries) for more information).
4. Set the symbols `DOUT1`, `DOUT2`, `PWMOUT` and `SBYOUT`(by default set to 20, 21, 19 and 18) to the values of Arduino outputs connected to driver AIN1, AIN2, PWMA and STBY respectively.
5. Optionally, set the symbol `LED` (by default set to 13) to the value of your Arduino built-in led output.