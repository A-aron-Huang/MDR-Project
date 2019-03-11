#include <ncurses.h>
#include <wiringPi.h>

int main(){
	int ch;

	initscr();
	raw();
	keypad(stdscr,TRUE);
	noecho();

	printw("Welcome - Press # to Exit\n");

	wiringPiSetupGpio(); //Using the gpio numbering system
	pinMode(18,PWM_OUTPUT);
    int val = 0;


	while((ch = getch()) != '#'){
		switch(ch){
			case KEY_UP: printw("\nUp Arrow");
					val++;
                        pwmWrite(18,val);
			break;
			case KEY_DOWN: printw("\nDown Arrow");
                        val--;
                        pwmWrite(18,val);
			break;
			default:
				{
				printw("\nThe pressed key is ");
				attron(A_BOLD);
				printw("%c",ch);
				attroff(A_BOLD);
			}
		}
	}
	printw("\n\nBye Now!\n");
	refresh();
	getch();
	endwin();
	return 0;
}
