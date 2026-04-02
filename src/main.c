#include <ncurses.h>
#include "./conv/rgb.h"
#include "./conv/hex.h"
#include "./functional/functional.h"

int main (){
	int currentx, currenty;
	short mode = 2;
	char prompt[6];

	initscr();
	mvprintw(0, 0,"Type the command help to see available commands.");
	
	do{
		if (mode == 1){
			attron(A_BLINK);
			mvprintw(0, 0,"=>");
			refresh();
			attroff(A_BLINK);
		
			//read prompt
			getnstr(prompt, 6);
			promptHandler(prompt, &mode);
			if (mode != 0)
				mode = 2;
		}
		else if (mode == 2){
			getyx(stdscr, currenty, currentx);
			attron(A_BLINK);
			mvprintw(currenty+1, 0,"=>");
			refresh();
			attroff(A_BLINK);
		
			//read prompt
			getnstr(prompt, 6);
			promptHandler(prompt, &mode);
		}
	}while(mode != 0);
	
	endwin();
	return 0;
}
