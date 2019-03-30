#include <ncurses.h>
#include <wiringPi.h>

#define ARD 26
#define LEFT 13
#define RIGHT 19

int main(){
	wiringPiSetupGpio(); //Use gpio numbering
	int ch;

	initscr();
	raw();
	keypad(stdscr,TRUE);
	noecho();
	nodelay(stdscr,TRUE); //ch will be 'ERR' if no character clicked
	
	pinMode(ARD,OUTPUT);
	pinMode(LEFT,OUTPUT);
	pinMode(RIGHT,OUTPUT);
	
	

	printw("Welcome - Press q to Exit\n");

	while((ch = getch()) != 'q'){
		switch(ch){
			case KEY_UP:
				printw("\nUp Arrow");
				digitalWrite(ARD,HIGH);
				break;
			case KEY_DOWN:
				printw("\nDown Arrow");
				digitalWrite(ARD,LOW);
				break;
			case KEY_LEFT:
				printw("\nLeft Arrow");
				digitalWrite(LEFT,HIGH);
				digitalWrite(RIGHT,LOW);
				break;
			case KEY_RIGHT:
				printw("\nRight Arrow");
				digitalWrite(RIGHT,HIGH);
				digitalWrite(LEFT,LOW);
				break;
			default:
				break;
			
			
		}

	}
	
	digitalWrite(ARD,LOW); //Turn off servo
	printw("\n\nBye Now!\n");
	refresh();
	getch();
	endwin();
	return 0;
}
