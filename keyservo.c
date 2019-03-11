
#include <ncurses.h> //Library for keyboard
#include <wiringPi.h> //Library for wiring

#define servo 18

int main(){
	int c; //temp char variable
	int val = 0; //Starting postion of servo

	initscr(); //Initialization for keyboard stuff
	raw();
	keypad(stdscr,TRUE);
	noecho();

	wiringPiSetupGpio(); //Using the gpio numbering system
	pinMode(servo,PWM_OUTPUT);

	printf("Starting now\n");
	c = getch();
	while(c != '#'){
		switch(c){
			case KEY_LEFT:
				val = 0;
				pwmWrite(servo,val);
				break;
			case KEY_UP:
				val = 10;
				pwmWrite(servo,val);
				break;
			case KEY_RIGHT:
				val = 50;
				pwmWrite(servo,val);
				break;
			case KEY_DOWN:
				val = 100;
				pwmWrite(servo,val);
				break;
			case 'a':
				val = 200;
				pwmWrite(servo,val);
				break;
			case 'A':
				val = 300;
				pwmWrite(servo,val);
				break;
			case 'b':
				val = 400;
				pwmWrite(servo,val);
				break;
			case 'B':
				val = 450;
				pwmWrite(servo,val);
				break;
			case 'c':
				val = 475;
				pwmWrite(servo,val);
				break;
			case 'C':
				val = 500;
				pwmWrite(servo,val);
				break;
			case 'd':
				val = 510;
				pwmWrite(servo,val);
				break;
			case 'D':
				val = 512;
				pwmWrite(servo,val);
				break;
			default:
				printf("Incorrect key");
				break;
			}
		c = getch();
/*
		if(c == KEY_UP){
			val = 100;
			pwmWrite(servo,val);
		} else if (c == KEY_DOWN){
			val=-100;
			pwmWrite(servo,val);
		} else {
			printf("Inccorect key");
		}*/
	}
	printf("Done");
	refresh();
	getch();
	endwin();
	return 0;
}


