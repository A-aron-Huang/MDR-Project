#include <ncurses.h>
#include <wiringPi.h>

#define ARD 26
#define LEFT 5
#define RIGHT 6
#define PULSE 19

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
		if(ch == KEY_UP){
			printw("\nUp Arrow");
			digitalWrite(ARD,HIGH);
		} else if (ch == KEY_DOWN){
			printw("\nDown Arrow");
			digitalWrite(ARD,LOW);
		} else if (ch == KEY_LEFT){
			//printw("\nLeft Arrow");
				digitalWrite(LEFT,HIGH);
		} else if (ch == KEY_RIGHT){
			//printw("\nRight Arrow");
				digitalWrite(RIGHT,HIGH);
		} else if (ch == 'c'){
			digitalWrite(PULSE,HIGH);
		} else {
			digitalWrite(LEFT,LOW);
			digitalWrite(RIGHT,LOW);
			digitalWrite(PULSE,LOW);
		
		}
		delay(10);
			
	}
	
	digitalWrite(ARD,LOW); //Turn off servo
	printw("\n\nBye Now!\n");
	refresh();
	getch();
	endwin();
	return 0;
}
