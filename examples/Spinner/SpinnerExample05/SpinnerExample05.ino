#include <tb6612fng.h>

#define DOUT1 20  // Arduino digital IO
#define DOUT2 21  // Arduino digital IO
#define PWMOUT 19 // Arduino digital IO with PWM feature
#define LED 13    // Arduino digital IO connected to the builtin led

Motor *motor;
Spinner *spinner;
SpinPoint spinMap[3];

// Callback function for the spinner event of spin point updated
// This function will be invoked whenever a new speed is set to the motor.
// The function argument spinPoint will contain both the new speed
// and the elapsed time (milliseconds) from the spin start.
void spinUpdated(const SpinPoint *spinPoint)
{
    if (spinPoint->speed == spinMap[1].speed)
    {
        // We have completed the first map stage (acceleration)
        // and the spinner starts deccelerating (second stage)
        // Blink the led
        digitalWrite(LED, HIGH);
        delay(50);
        digitalWrite(LED, LOW);
    }
}

// Callback function for the spinner event of spin finished
// This function will be invoked when the last point of the spin map was reached
// The function argument spinPoint will contain both the last speed
// and the elapsed time (milliseconds) from the spin start.
// Note that the elapsed time will be the real elapsed time,
// that could be higher to that set in the spin map last point.
void spinFinished(const SpinPoint *spinPoint)
{
    // The spin process has concluded
    // Light the led
    digitalWrite(LED, HIGH);
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
    // using only one callback function for handling the event of spin finished
    spinner = new Spinner(motor, spinUpdated, spinFinished);

    // Define the spin up map for accelerating and then deccelerating the motor
    // The first map point (time = 0) states an initial speed of 100
    spinMap[0].time = 0;
    spinMap[0].speed = 100;
    // The intermediate map point states a speed of 200, 10000 milliseconds after start spinning
    spinMap[1].time = 10000;
    spinMap[1].speed = 200;
    // The last map point states a final speed of 0 (motor stoped), 40000 milliseconds after start spinning
    spinMap[2].time = 40000;
    spinMap[2].speed = 0;

    // Start spinning up the motor in clockwise direction
    spinner->start(Clockwise, spinMap, 3);
}

void loop()
{
    // Spin the motor
    spinner->spin();
}
