#include <ncurses.h>

int main(){
	int ch;

	initscr();
	raw();
	keypad(stdscr,TRUE);
	noecho();

	printf("Starting Now: (Press 'q' to quit)\n");

	while((ch = getch()) != 'q'){
		switch(ch){
			case 'w':
				printw("Moving forward\n"); //
				break;
			case 's':
				printw("Moving backward\n");
				break;
			case 'a':
				printw("Turning left\n");
				break;
			case 'd':
				printw("Turning right\n");
				break;
			case KEY_LEFT:
				printw("Swinging left\n");
				break;
			case KEY_RIGHT:
				printw("Swinging right\n");
				break;
			case KEY_UP:
				printw("Auto mode\n");
				break;
			case KEY_DOWN:
				printw("Manual mode\n");
				break;
			default:
				printw("Invalid key\n");
				break;
		}
	}

	printw("\n\nBye Now!\n");
	refresh();
	getch();
	endwin();
	return 0;
}
