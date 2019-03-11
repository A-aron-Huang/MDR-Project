#include <ncurses.h>
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define STBY 21 //Motor Driver, to even start STBY must be on

#define PWMA 15 //Left Motor Controls
#define AIN1 3
#define AIN2 4

int main(){
	int ch;
	
	
	
	int stby;
	int pwma;
	int ain1;
	int ain2;

	int val = 100;

	wiringPiSetupGpio(); //Use pin numbering

	pinMode(STBY, OUTPUT); //STBY pin to turn on
 	digitalWrite(STBY,HIGH);

	pinMode(AIN1,OUTPUT);
	pinMode(AIN2,OUTPUT);

	//Testing with soft PWM - works with gpio 18
	softPwmCreate(PWMA,0,100);
	softPwmWrite(PWMA,0);
	
	
	
	initscr();
	raw();
	keypad(stdscr,TRUE);
	noecho();

	printw("Welcome - Press 'q' to Quit\n");

	while((ch = getch()) != 'q'){
//		switch(ch){ //Case-by-case scenario depending on keys pressed
			/*case 'w':
				softPwmWrite(PWMA,0); //Motor A stopped, as no keys pressed
				digitalWrite(AIN1,LOW);
				digitalWrite(AIN2,LOW);
				printf("Done Setting Up\n");
				delay(100);

				printf("Should be going forward now\n");
				digitalWrite(STBY,HIGH);
				digitalWrite(AIN1,HIGH);
				softPwmWrite(PWMA,50);
				//pwmWrite(PWMA,1000);
				//analogWrite(PWMA,1000);
				delay(5000);
				break;
			default:
				printw("Invalid Key\n");
				break;*/
				digitalWrite(STBY,HIGH);
				softPwmWrite(PWMA,100);

if(ch == 'w'){
digitalWrite(AIN1,HIGH);
delay(30);
}
else if(ch == 's'){


digitalWrite(AIN2,HIGH);
delay(30);
}

digitalWrite(AIN1,LOW);
digitalWrite(AIN2,LOW);
//ch = getch();
ch = 'b';

		}

	digitalWrite(STBY,LOW);
	printw("\n\nBye Now!\n");
	refresh();
	getch();
	endwin();
	return 0;
}
