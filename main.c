#include <ctype.h>
#include <ncurses.h>
#include <string.h>

//(rgb * 31 / 255) rounded
int convertColor (int rgb){
	float color_f = ((float)rgb * 31 /255);
	
	int intpart = (int)color_f;
	float decpart = color_f - intpart;

	if (decpart < 0.5) {
		return intpart;
	}
	else {
		return intpart+1;
	}

}

void promptHandler(char prompt[], int x, int y, int *quitorn){
	int red, green, blue;

	if (strcmp(prompt, "rgb") == 0){
		
		int color_correct_check = 0;
		do{

		//Read RGB Values (0-255)
		mvprintw(y+2, 5, "R: ");
		refresh();
		int redcheck = 0;
		do {
			scanw("%d", &red);
			if (red <= 255 && red >= 0)
				redcheck = 1;
			else {
				getyx(stdscr, y, x);
				mvprintw(y+2, x+5, "Error: Invalid Color (must be 0-255)\nTry again: ");
				refresh();
			}
		}while (!redcheck);

		getyx(stdscr, y, x);
		mvprintw(y, 5, "G: ");
		refresh();
		int greencheck = 0;
		do {
			scanw("%d", &green);
			if (red <= 255 && green >= 0)
				greencheck = 1;
			else {
				getyx(stdscr, y, x);
				mvprintw(y+1, x+5, "Error: Invalid Color (must be 0-255)\nTry again: ");
				refresh();
			}
		}while (!greencheck);

		getyx(stdscr, y, x);
		mvprintw(y, 5, "B: ");
		refresh();
		int bluecheck = 0;
		do {
			scanw("%d", &blue);
			if (red <= 255 && blue >= 0)
				bluecheck = 1;
			else {
				getyx(stdscr, y, x);
				mvprintw(y+1, x+5, "Error: Invalid Color (must be 0-255)\nTry again: ");
				refresh();
			}
		}while (!bluecheck);


		//Check if color is correct
		char color_correct_char;
		do{
			getyx(stdscr, y, x);
			mvprintw(y+1, 5, "Color is: R: %d, G: %d, B: %d right?? [Y/N]", red, green, blue);
			refresh();
			color_correct_char = getch();
			color_correct_char = tolower(color_correct_char);
			switch (color_correct_char) {
				case 'y': {
					color_correct_check = 1;
					break;
				}
				case 'n': {
					color_correct_check = 0;
					break;
				}
				default:  {
					break;
				}
			}
		}while (color_correct_char != 'n' || color_correct_char != 'y');


		}while(!color_correct_check);

		//Convert to 15bitrgb
		getyx(stdscr, y, x);
		mvprintw(y+1, 5, "15-bit Color is: R: %d, G: %d, B: %d", convertColor(red), convertColor(green), convertColor(blue));
	}//end rgb
	else if (strcmp(prompt, "help") == 0) {
		getyx(stdscr, y, x);
		mvprintw(y+1, x, "Commands\n\thelp: Show this message\n\tclear: Clear the Terminal\n\tquit: Exit BaalConv\n\trgb: Convert rgb(0-255) to 15-bit rgb");
	}
	else if (strcmp(prompt, "clear") == 0) {
		clear();
	}
	else if (strcmp(prompt, "quit") == 0) {
		*quitorn = 1;
	}
}

int main (){
	int currentx, currenty;
	char prompt[6];

	initscr();
	mvprintw(0, 0,"help to see available commands");

	int quitorn = 0;/*1 to quit*/
	while (!quitorn){
		getyx(stdscr, currenty, currentx);
		attron(A_BLINK);
		mvprintw(currenty+1, 0,"=>");
		refresh();
		attroff(A_BLINK);
		
		//read prompt
		getnstr(prompt, 6);
		promptHandler(prompt, currentx, currenty, &quitorn);
	}

	endwin();
	
	return 0;
}
