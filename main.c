#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include "./hex.h"

int hexToDecimal (char Number){
	if (!isdigit(Number)) {
		Number = tolower(Number);
	}

	switch (Number){
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'a':
			return HEX_A;
		case 'b':
			return HEX_B;
		case 'c':
			return HEX_C;
		case 'd':
			return HEX_D;
		case 'e':
			return HEX_E;
		case 'f':
			return HEX_F;
		default:{
			return -1;
			break;
		}
	}
}

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

int convertHexcode (char Hexcode[], char sel){
	if (sel == 'r'){
		return hexToDecimal(Hexcode[0]) * 16 + hexToDecimal(Hexcode[1]);
	}
	else if (sel == 'g'){
		return hexToDecimal(Hexcode[2]) * 16 + hexToDecimal(Hexcode[3]);
	}
	else if (sel == 'b'){
		return hexToDecimal(Hexcode[4]) * 16 + hexToDecimal(Hexcode[5]);
	}
	else {
		return -1;
	}
}

void promptHandler(char prompt[], int *mode){
	int red, green, blue;
	int x, y;
	getyx(stdscr, y, x);
	
	//RGB
	if (strcmp(prompt, "rgb") == 0){
		
		int color_correct_check = 0;
		do{

		//Read RGB Values (0-255)
		mvprintw(y, 5, "R: ");
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
			break;
		}while (color_correct_char != 'n' || color_correct_char != 'y');

		}while(!color_correct_check);

		//Convert to 15bitrgb
		getyx(stdscr, y, x);
		mvprintw(y+1, 5, "15-bit Color is: R: %d, G: %d, B: %d", convertColor(red), convertColor(green), convertColor(blue));
	}//end rgb
	 //
	 //
	 //HEX
	else if (strcmp(prompt, "hex") == 0){
		char hexcode[7];
		int color_valid;

		do{
		
		color_valid = 1;
		//Read Hexcode
		getyx(stdscr, y, x);
		mvprintw(y, 5, "Enter the Hexcode of your selected color: #");
		getnstr(hexcode, 7);

		//Hexcode length check
		if (strlen(hexcode) != 6){
			mvprintw(y+2, 5, "Error: Invalid Hexcode. Try again.");
			color_valid = 0;
		}		
		
		//Check if Hexcode is correct
		char color_correct_char;
		int hexcode_correct;
		do{
			if (color_valid == 0){
				break;
			}

			do{
				getyx(stdscr, y, x);
				mvprintw(y, 5, "Color is: %s right?? [Y/N]", hexcode);
				refresh();
				color_correct_char = getch();
				color_correct_char = tolower(color_correct_char);
				switch (color_correct_char) {
					case 'y': {
						hexcode_correct = 1;
						break;
					}
					case 'n': {
						hexcode_correct = 0;
						break;
        				}
					default:
						  break;
				}
				break;
			}while(color_correct_char != 'n' || color_correct_char != 'y');
		}while(!hexcode_correct);

		//Check each color value
			red = convertHexcode(hexcode, 'r');
			if (red < 0 || red > 255){
				color_valid = 0;
				mvprintw(y, 5, "Error: Invalid Hexcode. Try again.");
			}
			green = convertHexcode(hexcode, 'g');
			if (green < 0 || green > 255){
				color_valid = 0;
			}
			blue = convertHexcode(hexcode, 'b');
			if (blue < 0 || blue > 255){
				color_valid = 0;
			}

		//Convert to 15-bit rgb
		getyx(stdscr, y, x);
		mvprintw(y+2, 5, "15-bit Color is: R: %d, G: %d, B: %d", convertColor(red), convertColor(green), convertColor(blue));


		}while(!color_valid);
	}//end hex
	 //
	 //NON-COMPLEX-PROMPTS
	else if (strcmp(prompt, "help") == 0){
		getyx(stdscr, y, x);
		mvprintw(y+1, x, "Commands\n\thelp: Show this message\n\tclear: Clear the Terminal\n\tquit: Exit BaalConv\n\trgb: Convert rgb(0-255) to 15-bit rgb\n\thex: Convert hexcode to 15-bit rgb");
	}
	else if (strcmp(prompt, "clear") == 0){
		clear();
		*mode = 1;
	}
	else if (strcmp(prompt, "quit") == 0){
		*mode = 0;
	}
}

int main (){
	int currentx, currenty;
	int mode = 2;
	char prompt[6];

	initscr();
	mvprintw(0, 0,"help to see available commands");
	
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
