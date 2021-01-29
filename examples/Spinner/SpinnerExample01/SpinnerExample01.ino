#include <tb6612fng.h>

#define DOUT1 20  // Arduino digital IO
#define DOUT2 21  // Arduino digital IO
#define PWMOUT 19 // Arduino digital IO with PWM feature
#define LED 13    // Arduino digital IO connected to the builtin led

Motor *motor;
Spinner *spinner;
SpinPoint spinMap[2];

// Callback function for the spinner event of spin point updated
// This function will be invoked whenever a new speed is set to the motor.
// The function argument spinPoint will contain both the new speed
// and the elapsed time (milliseconds) from the spin start.
void spinUpdated(const SpinPoint *spinPoint)
{
    // Uncomment this block to get info by the console
    // Serial.print("Spin updated. ");
    // Serial.print("Speed: ");
    // Serial.print(spinPoint->speed);
    // Serial.print(" Elapsed time: ");
    // Serial.println(spinPoint->time);

    // Blink the led
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
}

// Callback function for the spinner event of spin finished
// This function will be invoked when the last point of the spin map was reached
// The function argument spinPoint will contain both the last speed
// and the elapsed time (milliseconds) from the spin start.
// Note that the elapsed time will be the real elapsed time,
// that could be higher to that set in the spin map last point.
void spinFinished(const SpinPoint *spinPoint)
{
    // Uncomment this block to get info by the console
    // Serial.println("Spin finished");

    // Stop the motor and light the led
    motor->stop();
    digitalWrite(LED, HIGH);
}

void setup()
{
    // Uncomment this block to get info by the console
    // Note that the program will not start until the console was opened
    // Serial.begin(115200);
    // while (!Serial) { };
    // Serial.println("Program starting");

    // Initialize the led output
    pinMode(LED, OUTPUT);

    // Create a Motor object instance
    // (pinMap pins are initialized by the Motor class)
    PinMap pinMap;
    pinMap.in1 = DOUT1;
    pinMap.in2 = DOUT2;
    pinMap.pwm = PWMOUT;
    motor = new Motor(&pinMap);

    // Create a spinner object instance associated to motor
    // using two callback functions: spinUpdated and spinFinished
    spinner = new Spinner(motor, spinUpdated, spinFinished);

    // Define the spin map
    // The first map point (time = 0) states an initial speed of 100
    spinMap[0].time = 0;
    spinMap[0].speed = 100;
    // The last map point states a final speed of 200, 10000 milliseconds after start spinning
    spinMap[1].time = 10000;
    spinMap[1].speed = 200;

    // Start spinning the motor in clockwise direction
    spinner->start(Clockwise, spinMap);
}

void loop()
{
    // Spin the motor
    spinner->spin();
}
