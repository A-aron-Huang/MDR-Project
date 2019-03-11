#include <ncurses.h>

int main(){
	int ch;

	initscr();
	raw();
	keypad(stdscr,TRUE);
	noecho();

	printw("Welcome - Press # to Exit\n");

	while((ch = getch()) != '#'){
		switch(ch){
			case KEY_UP: printw("\nUp Arrow");
			break;
			case KEY_DOWN: printw("\nDown Arrow");
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
