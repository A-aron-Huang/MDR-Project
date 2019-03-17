/*Notes:
 *Add check for wiringpi setup
 *
 *
 */



#include <ncurses.h>
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define STBY 21 //Motor Driver, to even start STBY must be on

#define PWMA 2 //Left Motor Controls
#define AIN1 3
#define AIN2 4

#define BIN1 14 //Right Motor Controls
#define BIN2 15
#define PWMB 18

int main(){
	int ch; //Used to save a temp character variable
	int pwmVal = 100; //Value for max PWM range**
	/*int stby; //Troubleshooting values
	int pwma;
	int ain1;
	int ain2;*/

	int delayTime = 35;

	wiringPiSetupGpio(); //Use pin numbering

	//Three main components of the car - Setup the car with everything off
	pinMode(STBY, OUTPUT); //STBY pin used to turn the car on (1-On/0-Off)
 	digitalWrite(STBY,HIGH);

	softPwmCreate(PWMA,0,pwmVal); //Left Motor
	pinMode(AIN1,OUTPUT);
	pinMode(AIN2,OUTPUT);
	softPwmWrite(PWMA,0);

	softPwmCreate(PWMB,0,pwmVal); //Right Motor
	pinMode(BIN1,OUTPUT);
	pinMode(BIN2,OUTPUT);
	softPwmWrite(BIN2,0);

	initscr(); //Intilaizing keypressing
	raw();
	keypad(stdscr,TRUE);
	noecho();
	nodelay(stdscr,TRUE); //ch will be 'ERR' if no character clicked
	
	printw("Starting Now - Press 'q' to Quit\n");
	while((ch = getch()) != 'r'){
	/*	softPwmWrite(PWMA,0); //Everything starts off
		digitalWrite(AIN1,LOW);
		digitalWrite(AIN2,LOW);
		softPwmWrite(PWMB,0);
		digitalWrite(BIN1,LOW);
		digitalWrite(BIN2,LOW);*/
		
		if(ch == 'w'){ //Going forward
			softPwmWrite(PWMA,pwmVal*2);
			softPwmWrite(PWMB,pwmVal*2);
			digitalWrite(AIN2,HIGH);
			digitalWrite(BIN1,HIGH);
		} else if(ch == 's'){ //Going backward
			softPwmWrite(PWMA,pwmVal/4*3);
			softPwmWrite(PWMB,pwmVal/4*3);
			digitalWrite(AIN1,HIGH);
			digitalWrite(BIN2,HIGH);
		} else if(ch == 'd'){ //Turning right
			softPwmWrite(PWMA,pwmVal);
			digitalWrite(AIN2,HIGH);
		} else if(ch == 'a'){ //Turning left
			softPwmWrite(PWMB,pwmVal);
			digitalWrite(BIN1,HIGH);
		} else if (ch == ERR){
			softPwmWrite(PWMA,0); //Everything starts off
			digitalWrite(AIN1,LOW);
			digitalWrite(AIN2,LOW);
			softPwmWrite(PWMB,0);
			digitalWrite(BIN1,LOW);
			digitalWrite(BIN2,LOW);		
		} else if(ch == 'e'){ //Turning forward-right
			softPwmWrite(PWMA,pwmVal);
			digitalWrite(AIN2,HIGH);
			softPwmWrite(PWMB,pwmVal/4*3);
			digitalWrite(BIN1,HIGH);
		} else if(ch == 'q'){ //Turning forward-left
			softPwmWrite(PWMA,pwmVal/4*3);
			digitalWrite(AIN2,HIGH);
			softPwmWrite(PWMB,pwmVal);
			digitalWrite(BIN1,HIGH);
		} else { //Invalid Key
			printw("Invalid Key\n");
		}
		
		
		delay(delayTime);

		
		
	}
	//While loop has been exited
	digitalWrite(STBY,LOW); //Turn the car off
	printw("\nBye Now!\n"); //Deintialize keypressing
	refresh();
	getch();
	endwin();
	return 0;
}
