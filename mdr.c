/* Notes:
 *
 *
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

//LED Light up
#define LED1 25
#define LED2 8
#define LED3 9
#define LED4 11

//Camera
#define TAKE 19 //Outputs into pin 26
#define SEND 20 //Outputs into pin 16


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

void pulseCounter(int delayTime, int *LEDcount) { //Subtract a specified time in ms from a counter
    *LEDcount-=delayTime;
    if(*LEDcount < 0) {
        digitalWrite(LED1,LOW);
		digitalWrite(LED2,LOW);
		digitalWrite(LED3,LOW);
		digitalWrite(LED4,LOW);
        *LEDcount = 0;
    }
}

void cameraCounter(int delayTime, int *cameraCount){
	*cameraCount-=delayTime;
	if(*cameraCount<0){
		digitalWrite(TAKE,LOW);
		digitalWrite(SEND,LOW);
		*cameraCount = 0;
	}
}

//Start of Code
int main() {
    //Key Board Variables
    int ch; //Used to save a temp character variable

    //Car Variables
    int pwmVal = 100; //Value for max PWM range**
    int delayTime = 35;

    //LED Variable
    int LEDCount = 0;

	//Camera Variable
	int cameraCount = 0;

    //Servo Variables
    int pos = 80; //Starting position of car, should be 90 prob offset
	int rotateVal = 2; //Rotates how many times per activation
	int servoDelay = 13; //ms delay

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
	servoWrite(pos);

    //Setting Up Pulse
    pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
	digitalWrite(LED1,LOW);
	digitalWrite(LED2,LOW);
	digitalWrite(LED3,LOW);
	digitalWrite(LED4,LOW);

	//Setting up the Camera
	pinMode(SEND,OUTPUT);
	digitalWrite(SEND,LOW);
	pinMode(TAKE,OUTPUT);
	digitalWrite(TAKE,LOW);

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
    printw("Down key - Stop Rotating Rrm\n");
	printw("Left Key - Rotate Left\n");
	printw("Right Key - Rotate Right\n");
	printw("\nCamera/Pulse:\n");;
	printw("C - Take a picture (Wait 4 seconds)\n");
	printw("X - Send a picture\n");
	printw("\nOthers:\n");
	printw("P - Party Bus\n");
    printw("Space - Exit Program\n\n");
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
				if(ch == ' '){
					break;
				}
                servoWrite(pos);
                pos = pos + rotateVal;
                if(pos >= 180 || pos <= 0) { //Flips in opposite direction
                    rotateVal = -1*rotateVal;
                }
                pulseCounter(servoDelay,&LEDCount);
				cameraCounter(servoDelay,&cameraCount);
                delay(servoDelay);
            }
		} else if (ch == KEY_RIGHT){
			if(pos > 10){
				pos-=7;
				servoWrite(pos);
			}
		} else if (ch == KEY_LEFT){
			if(pos < 170){
				pos+=7;
				servoWrite(pos);
			}
		} else if (ch == 'c') { //Capture
			cameraCount = 3000;
			digitalWrite(TAKE,HIGH);
		} else if (ch == 'x'){	//Send
			cameraCount = 3000;
			digitalWrite(SEND,HIGH);
        } else if (ch == 'p') {
            LEDCount = 5000;
            digitalWrite(LED1,HIGH);
			digitalWrite(LED2,HIGH);
			digitalWrite(LED3,HIGH);
			digitalWrite(LED4,HIGH);
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

		cameraCounter(delayTime,&cameraCount);
        pulseCounter(delayTime,&LEDCount);
        delay(delayTime);
    }
    //While loop has been exited
    servoWrite(80); //Go back to original position
    digitalWrite(STBY,LOW); //Turn the car off
    printw("\nTurning Off!\n"); //Deintialize keypressing
	delay(500);
    refresh();
    getch();
    endwin();
    return 0;
}
