#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include <ncurses.h>

#define STBY 21 //Motor Driver, to even start STBY must be on

#define PWMA 2 //Left Motor Controls
#define AIN1 3
#define AIN2 4

int main(){

	int ch; //Temp char variable for keyboard input

	int stby;
	int pwma;
	int ain1;
	int ain2;


	wiringPiSetupGpio(); //Use gpio numbering

	pinMode(STBY, OUTPUT); //STBY pin to turn on
	digitalWrite(STBY,HIGH);

	pinMode(PWMA,OUTPUT); //Left Motor
	pinMode(AIN1,OUTPUT);
	pinMode(AIN2,OUTPUT);

	initscr();
	raw;
	keypad(stdscr,TRUE);
	noecho();

	printw("Starting Now: (Press 'q' to quit)\n");

	while((ch = getch()) != 'q'){
		softPwmWrite(PWMA,0); //Motor A stopped, as no keys pressed
		digitalWrite(AIN1,LOW);
		digitalWrite(AIN2,LOW);
		printw("Done Setting Up\n");
		delay(100);

		printw("Should be going forward now\n");
		digitalWrite(STBY,HIGH);
		softPwmWrite(PWMA,100);
		digitalWrite(AIN1,HIGH);
		delay(5000);

		stby=digitalRead(STBY);
		pwma=analogRead(PWMA);
		ain1=digitalRead(AIN1);
		ain2=digitalRead(AIN2);
		
	}
	printw("\nEnding Now!\n");
	refresh();
	getch();
	endwin();
	return 0;
}
