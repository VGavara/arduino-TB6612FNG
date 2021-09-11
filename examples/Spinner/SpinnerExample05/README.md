# Spinner example 05
This example makes a motor spinning up from 40% of its max speed (engine speed 26214 in a scale of 0-65535) to 80% of its max speed (engine speed 52428 in a scale of 0-65535) in clockwise direction. Spinning up process takes 10s (10000ms) and, once it is completed, the led blinks and motor spins down from its current speed to full stopped in 30s (30000ms). Once it's fully stopped, the led is light.

Though performing the same operation that [SpinnerExample02](https://github.com/VGavara/ArduinoTB6612FNG/tree/stable/examples/Spinner/SpinnerExample02) and [SpinnerExample03](https://github.com/VGavara/ArduinoTB6612FNG/tree/stable/examples/Spinner/SpinnerExample03), this code uses the multiple points map feature released in version 0.2.0 of the library, simplifying the code.

In order to properly run the example follow these steps:
1. Carefully study the datasheet before wiring the Arduino and driver. Driver datasheet is in the [/docs/datasheets](https://github.com/VGavara/ArduinoTB6612FNG/tree/stable/docs/datasheets) directory.
2. Wire the Arduino and driver as described in the file SpinnerExample05_WiringDiagram.png. Have in mind that the driver IC has not only one but several VM, PGND, AO1 and AO2 pins. All the pins must be connected. 
3. Make sure the library files are properly installed in the Arduino IDE library path (see [Arduino Libraries](https://www.arduino.cc/en/Hacking/Libraries) for more information).
4. Set the symbols `DOUT1`, `DOUT2` and `PWMOUT` (by default set to 20, 21 and 19) to the values of Arduino outputs connected to driver AIN1, AIN2 and PWMA respectively.
5. Optionally, set the symbol `LED` (by default set to 13) to the value of your Arduino built-in led output.
