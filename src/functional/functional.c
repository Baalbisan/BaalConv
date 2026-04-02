// functional.c
//
// Written By: Baalbisan
//
// Last Modified: 02/04/2026

#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include <stdbool.h>
#include "../conv/hex.h"
#include "../conv/rgb.h"

void returnError (short errorcode){
    switch (errorcode){
        short y,x;
        getyx(stdscr, y, x);
        case '1':{
            mvprintw(y+1, x+5, "Error: Invalid Color (must be 24-bit [value in range 0-255])\n\tTry again:");
        }
        case '2':{
            mvprintw(y+1, 5, "Error: Invalid Hexcode. Try again.\n");
        }
    }
    refresh();
}

void printHelp (short *y, short *x){
    getyx(stdscr, *y, *x);
    mvprintw(*y, 5, "Commands\n\thelp: Show this message\n\tclear: Clear the Terminal\n\tquit: Exit BaalConv\n\trgb: Convert rgb(0-255) to 15-bit rgb\n\thex: Convert hexcode to 15-bit rgb");
    refresh();
}

void printConvertedColor (short red, short green, short blue){
    short y,x;
    getyx(stdscr, y, x);
    mvprintw(y+1, 5, "15-bit Color is: R: %d, G: %d, B: %d", convertTo15bitRGB(red), convertTo15bitRGB(green), convertTo15bitRGB(blue));
    refresh();
}

void readAndCheck24bitColorValid (short *color, char colorc){
    short y,x;
    getyx(stdscr, y, x);
    mvprintw(y, 5, "%c: ", toupper(colorc));
    refresh();

    bool colorcheck = false;
    while (!colorcheck){
        scanw("%hi", color);
        if (*color <= 255 && *color >= 0)
            colorcheck = true;
        else{
            returnError(1);
        }
    }
}

void readAndCheckHexcodeValid (char hexcode[7], short *red, short *green, short *blue, short *y, short *x){
    bool hexcode_val_check = false;
    while (!hexcode_val_check){
        // read hexcode
        getyx(stdscr, *y, *x);
        mvprintw(*y, 5, "Enter the Hexcode of your selected color: #");
        getnstr(hexcode, 6);

        // check hexcode
        if (strlen(hexcode) != 6){
            returnError(2);
        }
        else {
            //check each value
            *red = convertHexcodeTo24bitRGB(hexcode, 'r');
            *green = convertHexcodeTo24bitRGB(hexcode, 'g');
            *blue = convertHexcodeTo24bitRGB(hexcode, 'b');

            if (*red != -1 && *green != -1 && *blue != -1){
                if ( (*red < 0 || *red > 255) || (*green < 0 || *green > 255) || (*blue < 0 || *blue > 255) ){
                    returnError(2);
                }
            }
            else {
                returnError(2);
            }
        }
    }
}

void promptHandler (char prompt[], short *mode){
    short red, green, blue;
    short x,y;

    if (strcmp(prompt, "rgb") == 0){
        bool color_correct_check = false;

        do {
            readAndCheck24bitColorValid(&red, 'r');
            readAndCheck24bitColorValid(&green, 'g');
            readAndCheck24bitColorValid(&blue, 'b');

            //Check if color entered is correct
            bool color_cor_char_check = false;
            while (!color_cor_char_check){
                getyx(stdscr, y, x);
                mvprintw(y+1, 5, "Color is R: %hi, G: %hi, B: %hi, right? [Y/N]", red, green, blue);
                switch ( tolower(getch()) ){
                    case '\n':
                    case 'y':{
                        color_correct_check = true;
                        color_cor_char_check = true;
                        break;
                    }
                    case 'n':{
                        color_correct_check = false;
                        color_cor_char_check = true;
                        break;
                    }
                    default:
                        color_cor_char_check = false;
                        break;
                }
            }
        }while (!color_correct_check);

        printConvertedColor(red, green, blue);
    }
    else if (strcmp(prompt, "hex") == 0){
        char hexcode[7];
        bool hex_corect_check = false;
        do{
            readAndCheckHexcodeValid(hexcode, &red, &green, &blue, &y, &x);

            //Check if hexcode entered is correct
            bool hex_cor_char_check = false;
            while (!hex_cor_char_check){
                getyx(stdscr, y, x);
                mvprintw(y=1, 5, "Hexcode is #%s, right? [Y/N]", hexcode);
                switch ( tolower(getch()) ){
                    case '\n':
                    case 'y':{
                        hex_corect_check = true;
                        hex_cor_char_check = true;
                        break;
                    }
                    case 'n':{
                        hex_corect_check = false;
                        hex_cor_char_check = true;
                    }
                    default:
                        hex_cor_char_check = false;
                        break;
                }
            }
        }while (!hex_corect_check);

        printConvertedColor(red, green, blue);
    }
    else if (strcmp(prompt, "help") == 0){
        printHelp(&y, &x);
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
        mvprintw(y, 5, "Invalid command entered, try running ""help"" to see available commands.");
        refresh();
    }
}
