#include <ncurses.h>
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define SERVO 18

long map(long value, long fromLow,long fromHigh, long toLow, long toHigh){
	return (toHigh-toLow)*(value-fromLow)/(fromHigh-fromLow)+toLow;
}

void servoWrite(int angle){
	if(angle > 180){
		angle = 180;
	}
	if(angle < 0){
		angle = 0;
	}
	softPwmWrite(SERVO,map(angle,0,180,7,23));
}

int main(){
	wiringPiSetupGpio(); //Use pin numbering
	softPwmCreate(SERVO,0,200);
	int ch;
	int pos = 90;
	servoWrite(90);
	
	initscr(); //Intilaizing keypressing
	raw();
	keypad(stdscr,TRUE);
	noecho();
	nodelay(stdscr,TRUE); //ch will be 'ERR' if no character clicked
	
	printw("Starting Now - Press 'q' to Quit\n");
	while((ch = getch()) != 'q'){
	if(ch == KEY_RIGHT){ //Turning left
		while((ch = getch()) == KEY_RIGHT){
			if(pos > 2){
				pos-=2;
			}
			servoWrite(pos);
		}
	} else if(ch == KEY_LEFT){ //Turning right
		while((ch = getch()) == KEY_LEFT){
			if(pos < 178){
				pos+=2;
			}
			servoWrite(pos);
		}
	} else if(ch == KEY_UP){ //Auto mode
		//need add method to stop
	} else if(ch == KEY_DOWN){ //Manual mode
		//Prob add boolean
	} else if (ch == ERR){
		//nothing
	
	} else { //Invalid Key
		printw("Invalid Key\n");
	}
		
		
	delay(5);
}

		
		
	
	printw("\nBye Now!\n"); //Deintialize keypressing
	refresh();
	getch();
	endwin();
	return 0;
}
