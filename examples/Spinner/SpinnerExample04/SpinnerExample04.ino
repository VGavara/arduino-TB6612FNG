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
    // Blink the led
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);

    if (spinPoint->speed == 5000)
    {
        spinner->abort();
    }
}

void setup()
{
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
    // using just one callback function for the event of spin updated
    spinner = new Spinner(motor, spinUpdated, NULL);

    // Define the spin up map for accelerating the motor
    // The first map point (time = 0) states an initial speed of 26214 (40% of max speed)
    spinMap[0].time = 0;
    spinMap[0].speed = 26214;
    // The last map point states a final speed of 0, 10000 milliseconds after start spinning
    spinMap[1].time = 20000;
    spinMap[1].speed = 0;

    // Start spinning up the motor in counter-clockwise direction
    spinner->start(CounterClockwise, spinMap);
}

void loop()
{
    // Spin the motor
    spinner->spin();
}
