#include <ncurses.h>
#include <wiringPi.h>

#define STBY 4 //Motor Driver, to even start STBY must be on

#define PWMA 8 //Left Motor Controls
#define AIN1 9
#define AIN2 7

#define PWMB 15 //Right Motor Controls
#define BIN1 16
#define BIN2 1

int main(){

	int ch; //Temp char variable for keyboard input

	//Maybe make bool instead
	int arm = 0; //Value 1 for auto mode, value 0 for manual mode 


	wiringPiSetupGpio(); //Use gpio numbering

	pinMode(STBY, OUTPUT); //STBY pin to turn on
	digitalWrite(STBY,HIGH);

	pinMode(PWMA,OUTPUT); //Left Motor
	pinMode(AIN1,OUTPUT);
	pinMode(AIN2,OUTPUT);

	pinMode(PWMB,OUTPUT); //Right Motor
	pinMode(BIN1,OUTPUT);
	pinMode(BIN2,OUTPUT);

	initscr();
	raw;
	keypad(stdscr,TRUE);
	noecho();

	printw("Starting Now: (Press 'q' to quit)\n");

	while((ch = getch()) != 'q'){
		analogWrite(PWMA,0); //Motor A stopped, as no keys pressed
		digitalWrite(AIN1,LOW);
		digitalWrite(AIN2,LOW);

		analogWrite(PWMB,0); //Motor B stopped, as no keys pressed
		digitalWrite(BIN1,LOW);
		digitalWrite(BIN2,LOW);

		switch(ch){ //Case-by-case scenario depending on keys pressed
			case 'w':
				printw("Moving forward\n");
				/*analogWrite(PWMA,255); //Motor A - Full Power
				analogWrite(PWMB,255); //Motor B - Full Power
				digitalWrite(AIN1,HIGH); //Motor A - Rotate CW(Forward)
				digitalWrite(BIN2,HIGH); //Motor B - Rotate CCW(Forward)*/
				break;
			case 's':
				printw("Moving backward\n");
				/*analogWrite(PWMA,255/2); //Motor A - Half Power
				analogWrite(PWMB,255/2); //Motor B - Half Power
				digitalWrite(AIN2,HIGH); //Motor A - Rotate CCW(Backward)
				digitalWrite(BIN1,HIGH); //Motor B - Rotate CW(Backward)*/
				break;
			case 'a':
				printw("Turning left\n");
				/*analogWrite(PWMA,0); //Motor A - Zero Power
				analogWrite(PWMB,255/2); //Motor B - Half Power
				digitalWrite(BIN2,HIGH); //Motor B - Rotate CCW(Forward)*/
				break;
			case 'd':
				printw("Turning right\n");
				/*analogWrite(PWMA,255/2); //Motor A - Half Power
				analogWrite(PWMB,0); //Motor B - Zero Power
				digitalWrite(AIN1,HIGH); //Motor A - Rotate CW (Forward)*/
				break;
			case KEY_UP:
				printw("Autonomous Arm Mode\n");
				arm = 1;
				//Start back at inital positoin then start moving
				break;
			case KEY_DOWN:
				printw("Manual Arm Mode\n");
				arm = 0;
				break;
			case KEY_LEFT:
				if(arm == 0){
					printw("Swinging Left\n");
				} else {
					printw("Can't swing in auto mode\n");
				}
				break;
			case KEY_RIGHT:
				if(arm == 0){
					printw("Swinging Left\n");
				} else {
					printw("Can't swing in auto mode\n");
				}
				break;
			default:
				printw("Invalid Key\n");
				break;
		}
	}
	printw("\nEnding Now!\n");
	refresh();
	getch();
	endwin();
	return 0;
}
