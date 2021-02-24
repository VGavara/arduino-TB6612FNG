# Spinner example 04
This example makes a motor spinning down from 40% of its max speed (engine speed 26214 in a scale of 0-65535) to zero in counter-clockwise direction. However, when a speed of 5000 in a scale of 0-65535 is reached the spin operation is aborted. The led blinks every time the engine speed is updated until aborting the spinning, staying the led off since there are not updates on the motor speed. Aborting the operation doesn't stop the motor, but it keeps it rotating in the last spin speed reached.

In order to properly run the example follow these steps:
1. Carefully study the datasheet before wiring the Arduino and driver. Driver datasheet is in the [/docs/datasheets](https://github.com/VGavara/ArduinoTB6612FNG/tree/main/docs/datasheets) directory.
2. Wire the Arduino and driver as described in the file SpinnerExample04_WiringDiagram.png. Have in mind that the driver IC has not only one but several VM, PGND, AO1 and AO2 pins. All the pins must be connected. 
3. Make sure the library files are properly installed in the Arduino IDE library path (see [Arduino Libraries](https://www.arduino.cc/en/Hacking/Libraries) for more information).
4. Set the symbols `DOUT1`, `DOUT2` and `PWMOUT` (by default set to 20, 21 and 19) to the values of Arduino outputs connected to driver AIN1, AIN2 and PWMA respectively.
5. Optionally, set the symbol `LED` (by default set to 13) to the value of your Arduino built-in led output.