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

void promptHandler(char prompt[4], int x, int y, int *quitorn){
	int red, green, blue;

	if (strcmp(prompt, "rgb") == 0){
		
		//Read RGB Values (0-255)
		mvprintw(y+1, x+5, "R: ");
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
		mvprintw(y, x+5, "G: ");
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
		mvprintw(y, x+5, "B: ");
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
		int color_correct_check = 0;
		char color_correct_char;
		do{
			getyx(stdscr, y, x);
			mvprintw(y+1, x+5, "Color is: R: %d, G: %d, B: %d right?? [Y/N]", red, green, blue);
			refresh();
			color_correct_char = getch();
			switch (color_correct_char) {
				case 'Y': {
					color_correct_check = 1;
					break;
				}
				case 'N': {
					color_correct_check = 0;
					break;
				}
				default:  {
					break;
				}
			}
		}while (!color_correct_check);

		//Convert to 15bitrgb
		getyx(stdscr, y, x);
		mvprintw(y+1, 5, "15-bit Color is: R: %d, G: %d, B: %d", convertColor(red), convertColor(green), convertColor(blue));
		getch();
	}//end rgb
	else if (strcmp(prompt, "quit") == 0) {
		*quitorn = 1;
	}
}

int main (){
	int currentx, currenty;
	char prompt[4];

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
		getnstr(prompt, 4);
		promptHandler(prompt, currentx, currenty, &quitorn);
	}

	endwin();
	
	return 0;
}
