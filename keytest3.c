/*Notes:
 *Similar to keytest but uses while instead if else
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
 	digitalWrite(STBY,LOW);

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
	nodelay(stdscr,TRUE);

	printw("Starting Now - Press 'q' to Quit\n");
	while((ch = getch()) != 'q'){
		digitalWrite(STBY,HIGH); //Turn the car on

		while(ch == 'w'&& ch != ERR){ //Going forward
			softPwmWrite(PWMA,pwmVal*2);
			digitalWrite(AIN2,HIGH);
			softPwmWrite(PWMB,pwmVal*2);
			digitalWrite(BIN1,HIGH);
			while(ch != ERR){
				delay(delayTime);
				ch = getch();
			}
		}

		while(ch == 's' && ch != ERR){ //Going backward
			softPwmWrite(PWMA,pwmVal/4*3);
			digitalWrite(AIN1,HIGH);
			softPwmWrite(PWMB,pwmVal/4*3);
			digitalWrite(BIN2,HIGH);
			while(ch != ERR){
				delay(delayTime);
				ch = getch();
			}
		}

		while(ch == 'a' && ch != ERR){ //Going left
			softPwmWrite(PWMA,pwmVal/2);
			digitalWrite(AIN1,HIGH);
			while(ch != ERR){
				delay(delayTime);
				ch = getch();
			}
		}

		while(ch == 'd' && ch != ERR){ //Going right
			softPwmWrite(PWMB,pwmVal/2);
			digitalWrite(BIN2,HIGH);
			while(ch != ERR){
				delay(delayTime);
				ch = getch();
			}
		}


		//Wait for next key input, by turning motors off after no key press
		softPwmWrite(PWMA,0);
		digitalWrite(AIN1,LOW);
		digitalWrite(AIN2,LOW);
		softPwmWrite(PWMB,0);
		digitalWrite(BIN1,LOW);
		digitalWrite(BIN2,LOW);
		//ch = getch();
		ch = 'b';



	}
	//While loop has been exited
	digitalWrite(STBY,LOW); //Turn the car off
	printw("\nBye Now!\n"); //Deintialize keypressing
	refresh();
	getch();
	endwin();
	return 0;
}
