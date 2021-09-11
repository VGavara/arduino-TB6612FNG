# Spinner example 01
This example makes a motor spinning from 40% of its max speed (engine speed 26214 in a scale of 0-65535) to 80% of its max speed (engine speed 52428 in a scale of 0-65535) in clockwise direction. Spin process takes 10s (10000ms) and once it is completed, motor stops and a digital output, intended to light a led, is set.

The example is easily comparable with [MotorExample01](https://github.com/VGavara/ArduinoTB6612FNG/tree/stable/examples/Motor/MotorExample01), that implements a custom spinning not using the `Spinner` class.

In order to properly run the example follow these steps:
1. Carefully study the datasheet before wiring the Arduino and driver. Driver datasheet is in the [/docs/datasheets](https://github.com/VGavara/ArduinoTB6612FNG/tree/stable/docs/datasheets) directory.
2. Wire the Arduino and driver as described in the file SpinnerExample01_WiringDiagram.png. Have in mind that the driver IC has not only one but several VM, PGND, AO1 and AO2 pins. All the pins must be connected. 
3. Make sure the library files are properly installed in the Arduino IDE library path (see [Arduino Libraries](https://www.arduino.cc/en/Hacking/Libraries) for more information).
4. Set the symbols `DOUT1`, `DOUT2` and `PWMOUT` (by default set to 20, 21 and 19) to the values of Arduino outputs connected to driver AIN1, AIN2 and PWMA respectively.
5. Optionally, set the symbol `LED` (by default set to 13) to the value of your Arduino built-in led output.
6. Optinally, uncomment the code addressed to send process information by the serial port. In that case, have in mind that the spinning process **will not start** if a serial peer (as the Arduino IDE serial monitor) doesn't open the port.