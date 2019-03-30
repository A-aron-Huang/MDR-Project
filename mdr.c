/* Notes:
 * Final Project Code
 * Check pulsing
 *
 */


#include <ncurses.h>	//Used to set up keyboard commands
#include <wiringPi.h>	//Used to setup GPIO pins
#include <stdio.h>		//Used just in general
#include <softPwm.h>	//Used as alternative PWM

//Assigned Car Pins
#define STBY 21 //Motor Driver, to even start STBY must be on
#define PWMA 2 //Left Motor Controls
#define AIN1 3
#define AIN2 4
#define BIN1 14 //Right Motor Controls
#define BIN2 15
#define PWMB 23

//Servo Values From Data Sheet
#define OFFSET_MS 3 //Define the unit of servo pulse offset: 0.3ms
#define SERVO_MIN_MS 10-OFFSET_MS //define the pulse duration for minimum angle of servo
#define SERVO_MAX_MS 20+OFFSET_MS //define the pulse duration for maximum angle of servo
#define SERVO 18 //define the GPIO number connected to servo

//Pulse Pin for Camera
#define PULSE 25

//Formulas
long map(long value,long fromLow,long fromHigh,long toLow,long toHigh) {
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}

void servoWrite(int angle) { //Specify a certain rotation angle (0-180) for the servo
    if(angle > 180)
        angle = 180;
    if(angle < 0)
        angle = 0;
    softPwmWrite(SERVO,map(angle,0,180,SERVO_MIN_MS,SERVO_MAX_MS));
}

void pulseCount(int delayTime, int *count) { //Subtract a specified time in ms from a counter
    *count-=delayTime;
    if(*count < 0) {
        digitalWrite(PULSE,LOW);
        *count = 0;
    }
}

//Start of Code
int main() {
    //Key Board Variables
    int ch; //Used to save a temp character variable

    //Car Variables
    int pwmVal = 100; //Value for max PWM range**
    int delayTime = 35;

    //Pulse Variable
    int count = 0;

    //Servo Variables
    int rotateVal = 2; //Used to rotate car back and forth
    int pos = 90; //Starting position of car
    servoWrite(pos);

    //Setting Up Wiring of Board
    wiringPiSetupGpio();

    //Three Main Components of The cCar - Setup the car with everything off
    pinMode(STBY, OUTPUT); //STBY pin used to turn the car on (1-On/0-Off)
    digitalWrite(STBY,HIGH);

    softPwmCreate(PWMA,0,pwmVal); //Left Motor
    softPwmWrite(PWMA,0);
    pinMode(AIN1,OUTPUT);
    pinMode(AIN2,OUTPUT);

    softPwmCreate(PWMB,0,pwmVal); //Right Motor
    softPwmWrite(BIN2,0);
    pinMode(BIN1,OUTPUT);
    pinMode(BIN2,OUTPUT);

    //Setting Up servo with period of 2000us - Datasheet
    softPwmCreate(SERVO,  0, 200); //Servo

    //Setting Up Pulse
    pinMode(PULSE,OUTPUT);
    digitalWrite(PULSE,LOW);

    initscr(); //Intilaizing keypressing
    raw();
    keypad(stdscr,TRUE);
    noecho();
    nodelay(stdscr,TRUE); //ch will be 'ERR' if no character clicked

    printw("Starting Now - Press 'Space' to Quit\n\n");
    printw("Movement Keys:\n");
    printw("W - Move Foward\n");
	printw("S - Move Backward\n");
	printw("A - Turn Left\n");
	printw("D - Turn Right\n");
	printw("Q - Turn Forward-Left\n");
	printw("E - Turn Forward-Right\n");
	printw("\nServo Keys:\n");
    printw("Up Key - Rotate the Servo Arm\n");
    printw("Down key - Stop roatating arm\n");
	printw("\nCamera/Pulse\n");
	printw("P - Take a picture\n");
	printw("\nOthers\n");
    printw("Space - Exit Program\n");
    while((ch = getch()) != ' ') {
        if(ch == 'w') { //Going forward
            softPwmWrite(PWMA,pwmVal);
            softPwmWrite(PWMB,pwmVal);
            digitalWrite(AIN2,HIGH);
            digitalWrite(BIN1,HIGH);
        } else if(ch == 's') { //Going backward
            softPwmWrite(PWMA,pwmVal*0.75);
            softPwmWrite(PWMB,pwmVal*0.75);
            digitalWrite(AIN1,HIGH);
            digitalWrite(BIN2,HIGH);
        } else if(ch == 'd') { //Turning right
            softPwmWrite(PWMA,pwmVal);
            digitalWrite(AIN2,HIGH);
        } else if(ch == 'a') { //Turning left
            softPwmWrite(PWMB,pwmVal);
            digitalWrite(BIN1,HIGH);
        } else if(ch == 'q') { //Turing Forward left
            softPwmWrite(PWMB,pwmVal);
            softPwmWrite(PWMA,pwmVal*0.75);
            digitalWrite(BIN1,HIGH);
            digitalWrite(AIN2,HIGH);
        } else if(ch == 'e') { //Turning Forward right
            softPwmWrite(PWMA,pwmVal);
            softPwmWrite(PWMB,pwmVal*0.75);
            digitalWrite(AIN2,HIGH);
            digitalWrite(BIN1,HIGH);
        } else if(ch == KEY_UP) {
            while((ch = getch()) != KEY_DOWN) {
                servoWrite(pos);
                pos = pos + rotateVal;
                if(pos >= 180 || pos <= 0) { //Flips in opposite direction
                    rotateVal = -1*rotateVal;
                }
                pulseCount(20,&count);
                delay(20);
            }
        } else if (ch == 'p') {
            count = 3000;
            digitalWrite(PULSE,HIGH);
        } else if (ch == ERR) {
            softPwmWrite(PWMA,0); //Everything starts off
            digitalWrite(AIN1,LOW);
            digitalWrite(AIN2,LOW);
            softPwmWrite(PWMB,0);
            digitalWrite(BIN1,LOW);
            digitalWrite(BIN2,LOW);
        } else {
            printw("Invalid Key\n");
        }

        pulseCount(delayTime,&count);
        delay(delayTime);
    }
    //While loop has been exited
    servoWrite(90); //Go back to original position
    digitalWrite(STBY,LOW); //Turn the car off
    printw("\nTurning Off!\n"); //Deintialize keypressing
    refresh();
    getch();
    endwin();
    return 0;
}
