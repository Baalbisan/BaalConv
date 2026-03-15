#include <ctype.h>
#include <ncurses.h>
#include <string.h>

int hexToDecimal (char Number){
	if (!isdigit(Number)) {
		Number = tolower(Number);
	}

	switch (Number){
		case '0':
			return 0x0;
		case '1':
			return 0x1;
		case '2':
			return 0x2;
		case '3':
			return 0x3;
		case '4':
			return 0x4;
		case '5':
			return 0x5;
		case '6':
			return 0x6;
		case '7':
			return 0x7;
		case '8':
			return 0x8;
		case '9':
			return 0x9;
		case 'a':
			return 0xA;
		case 'b':
			return 0xB;
		case 'c':
			return 0xC;
		case 'd':
			return 0xD;
		case 'e':
			return 0xE;
		case 'f':
			return 0xF;
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
	for (int i = 0; i < 6; i++){
		if (hexToDecimal(Hexcode[i]) == -1)
			return -1;
	}
	switch (sel) {
		case 'r': {
				return hexToDecimal(Hexcode[0]) * 16 + hexToDecimal(Hexcode[1]);
		}
		case 'g': {
				return hexToDecimal(Hexcode[2]) * 16 + hexToDecimal(Hexcode[3]);
		}
		case 'b': {
				return hexToDecimal(Hexcode[4]) * 16 + hexToDecimal(Hexcode[5]);
		}
		default: {
			return -1;
		}
	}
}

void promptHandler(char prompt[], int *mode){
	int red, green, blue;
	int x, y;
	
	//RGB
	if (strcmp(prompt, "rgb") == 0){
		
		int color_correct_check = 0;
		do{
		
		getyx(stdscr, y, x);
		//Read RGB Values (0-255)
		mvprintw(y+1, 5, "R: ");
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
		
		char color_correct_char;
		int hexcode_correct;
		do{

		do{
			//Read Hexcode
			getyx(stdscr, y, x);
			mvprintw(y, 5, "Enter the Hexcode of your selected color: #");
			getnstr(hexcode, 7);
	
			//Hexcode length check
			if (strlen(hexcode) != 6){
				mvprintw(y+1, 5, "Error: Invalid Hexcode. Try again.\n");
				color_valid = 0;
				continue;
			}

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
		if (convertHexcode(hexcode, 'r') != -1 && convertHexcode(hexcode, 'g') != -1 && convertHexcode(hexcode, 'b') != -1){
			red = convertHexcode(hexcode, 'r');
			if (red < 0 || red > 255){
				color_valid = 0;
				getyx(stdscr, y, x);
				mvprintw(y+1, 5, "Error: Invalid Hexcode. Try again.");
			}
			green = convertHexcode(hexcode, 'g');
			if (green < 0 || green > 255){
				color_valid = 0;
				getyx(stdscr, y, x);
				mvprintw(y+1, 5, "Error: Invalid Hexcode. Try again.");
			}
			blue = convertHexcode(hexcode, 'b');
			if (blue < 0 || blue > 255){
				color_valid = 0;
				getyx(stdscr, y, x);
				mvprintw(y+1, 5, "Error: Invalid Hexcode. Try again.");
			}
		}
		else {
			color_valid = 0;
			getyx(stdscr, y, x);
			mvprintw(y+1, 5, "Error: Invalid Hexcode. Try again.");
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
	else {
		getyx(stdscr, y, x);
		mvprintw(y, 5, "Invalid command entered, Try running ""help"" to see available commands.");
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
