/*Notes:
 *Add check for wiringpi setup
 *
 *
 */

//Libraries
#include <ncurses.h>	//For keyboard commands
#include <wiringPi.h>	//For GPIO pins
#include <stdio.h>		//Standard C
#include <softPwm.h>	//For alternative PWM port

//Constants
#define STBY 21 //Motor Driver, to even start STBY must be on
#define PWMA 2 //Left Motor Controls
#define AIN1 3
#define AIN2 4
#define BIN1 14 //Right Motor Controls
#define BIN2 15
#define PWMB 25

#define SERVO 18
#define OFFSET 3
#define MAX_MS 10-OFFSET
#define MIN_MS 20+OFFSET

#define PULSE 12



//Functions
long map(long value, long fromLow, long fromHigh, long toLow, long toHigh){
	return (toHigh-toLow)*(value-fromLow)/(fromHigh-fromLow)+toLow;
}

void servoWrite(int angle){ //Uses angle to move servo (0-180)
	if(angle > 180){
		angle = 180;
	}
	if(angle < 0){
		angle = 0;
	}
	softPwmWrite(SERVO,map(angle,0,180,MIN_MS,MAX_MS));
}

void servoWriteMS(int ms){ //Uses ms pulse to move servo (10-20)
	if(ms > MAX_MS){
		ms = MAX_MS;
	}
	if(ms < MIN_MS){
		ms = MIN_MS;
	}
	softPwmWrite(SERVO,ms);
}

void rotateServo(){
}

void tempFunction(){
	for(int i =15;i<MAX_MS;i++){  //make servo rotate from minimum angle to maximum angle
		servoWriteMS(i);
		delay(100);
	}
	delay(500);
	for(int i=MAX_MS;i>MIN_MS;i--){  //make servo rotate from maximum angle to minimum angle
		servoWriteMS(i);
		delay(100);
	}
	for(int i =MIN_MS;i<15;i++){
		servoWriteMS(i);
		delay(100);
	}
	delay(5000);
}

int main(){
	//Setting Up
	if(wiringPiSetupGpio() == -1){ //Check to see if failed
		printw("Failed\n");
		return 1;
	}

	int ch; //Used to save a temp character variable
	int pwmVal = 100; //Value for max PWM range**
	int delayTime = 35;

	int pos = 90;
	int posMS = (MAX_MS+MIN_MS)/2;
	int autoMode = 0; //1 for auto, 0 for manual
	int pulse = 0; //1 for on, 0 for off
	int count;

	//Three main components of the car - Setup the car with everything off
	pinMode(STBY, OUTPUT); //STBY pin used to turn the car on (1-On/0-Off)
 	digitalWrite(STBY,HIGH);

	softPwmCreate(PWMA,0,pwmVal); //Make a PWM port for Left Motor
	softPwmWrite(PWMA,0);
	pinMode(AIN1,OUTPUT); //Setup Left Motor to Output
	pinMode(AIN2,OUTPUT);

	softPwmCreate(PWMB,0,pwmVal); //Make a PWM port for Right Motor
	softPwmWrite(PWMB,0);
	pinMode(BIN1,OUTPUT); //Setup Right Motor to Output
	pinMode(BIN2,OUTPUT);

	initscr(); //Intilaizing keypressing
	raw();
	keypad(stdscr,TRUE);
	noecho();
	nodelay(stdscr,TRUE); //ch will be 'ERR' if no character clicked


	//Finish Setting Up
	printw("Starting Now - Press 'q' to Quit\n");
	while((ch = getch()) != 'q'){
		if(ch == 'w'){ //Going forward
			softPwmWrite(PWMA,pwmVal*2);
			softPwmWrite(PWMB,pwmVal*2);
			digitalWrite(AIN2,HIGH);
			digitalWrite(BIN1,HIGH);
		} else if(ch == 's'){ //Going backward
			softPwmWrite(PWMA,pwmVal*0.75);
			softPwmWrite(PWMB,pwmVal*0.75);
			digitalWrite(AIN1,HIGH);
			digitalWrite(BIN2,HIGH);
		} else if(ch == 'd'){ //Turning right
			softPwmWrite(PWMA,pwmVal*0.75);
			digitalWrite(AIN2,HIGH);
		} else if(ch == 'a'){ //Turning left
			softPwmWrite(PWMB,pwmVal*0.75);
			digitalWrite(BIN1,HIGH);
		} else if (ch == KEY_UP){ //Turn to auto mode
			autoMode = 1;
			tempFunction();
		} else if (ch == KEY_DOWN){ //Turn to manual mode
			autoMode = 0;
		} else if (ch == KEY_LEFT){
			if(autoMode == 0){
				servoWrite(pos);
				pos-=1;
			} else {
				printw("In auto mode right now\n");
			}
		} else if (ch == KEY_RIGHT && autoMode == 0){
			if(autoMode == 0){
				///TESTING
				
				tempFunction();

				servoWriteMS(posMS);
				posMS+=0.5;
				printw("It works with val: %d or %d\n", pos, posMS);
			} else {
				printw("In auto mode right now\n");
			}
		} else if (ch == 'c'){ //Turn pulse on
			pulse = 1;
		} else if (ch == ERR){
			softPwmWrite(PWMA,0); //Turn Everything Off
			digitalWrite(AIN1,LOW);
			digitalWrite(AIN2,LOW);
			softPwmWrite(PWMB,0);
			digitalWrite(BIN1,LOW);
			digitalWrite(BIN2,LOW);
		} else { //Invalid Key
			printw("Invalid Key\n");
		}
		//delay(delayTime); //Intead of delay use delay during servo

		if(autoMode == 1){ //Use auto rotate function
		//	autoRotate();
		}

		if(pulse == 1){	//Use pulse function
			digitalWrite(PULSE,HIGH);
			count = 3000; //Will track count
		}
	}


	
	//While loop has been exited
	servoWrite(90); //Turn the servo back into original posistion
	digitalWrite(STBY,LOW); //Turn the car off
	printw("\nBye Now!\n"); //Deintialize keypressing
	refresh();
	getch();
	endwin();
	return 0;
}
