#include <tb6612fng.h>

#define DOUT1 20  // Arduino digital IO
#define DOUT2 21  // Arduino digital IO
#define PWMOUT 19 // Arduino digital IO with PWM feature
#define LED 13    // Arduino digital IO connected to the builtin led

Motor *motor;
Spinner *spinner;
SpinPoint spinUpMap[2], spinDownMap[2];
const SpinPoint *currentSpinPoint;
bool spinningDown;

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

    // Create a spinner object instance associated to motor not using callback functions
    spinner = new Spinner(motor);

    // Define the spin up map for accelerating the motor
    // The first map point (time = 0) states an initial speed of 100
    spinUpMap[0].time = 0;
    spinUpMap[0].speed = 100;
    // The last map point states a final speed of 200, 10000 milliseconds after start spinning
    spinUpMap[1].time = 10000;
    spinUpMap[1].speed = 200;

    // Define the spin down map for decelerating the motor
    // The first map point (time = 0) states the last spinUpMap speed
    spinDownMap[0].time = 0;
    spinDownMap[0].speed = spinUpMap[1].speed;
    // The last map point states a final speed of 0 (motor stoped), 30000 milliseconds after start spinning
    spinDownMap[1].time = 30000;
    spinDownMap[1].speed = 0;

    // Start spinning up the motor in clockwise direction
    spinner->start(Clockwise, spinUpMap);
    spinningDown = false;
}

void loop()
{
    // Spin the motor
    currentSpinPoint = spinner->spin();

    if (currentSpinPoint == NULL)
    {
        // No spin process running
        if (spinningDown)
        {
            // The spindown process has concluded
            // Light the led
            digitalWrite(LED, HIGH);
        }
        else
        {
            // The spinup process has concluded
            // Blink the led
            digitalWrite(LED, HIGH);
            delay(50);
            digitalWrite(LED, LOW);

            // Start spinning down the motor in clockwise direction
            spinner->start(Clockwise, spinDownMap);
            spinningDown = true;
        }
    }
}
