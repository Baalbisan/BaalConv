// hex.c
//
// Written By: Baalbisan
//
// Last Modified: 02/04/2026

#include <ctype.h>

short hexToDecimal (char Number){
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

short convertHexcodeTo24bitRGB (char Hexcode[], char sel){
    for (int i = 0; i < 6; i++){
        if (hexToDecimal(Hexcode[i]) == -1){
            return -1;
        }
    }
    
    switch (sel){
        case 'r':{
            return hexToDecimal(Hexcode[0]) * 16 + hexToDecimal(Hexcode[1]);
        }
        case 'g':{
            return hexToDecimal(Hexcode[2]) * 16 + hexToDecimal(Hexcode[3]);
        }
        case 'b':{
            return hexToDecimal(Hexcode[4]) * 16 + hexToDecimal(Hexcode[5]);
        }
        default:{
            return -1;
        }
    }
}
