// functional.h
//
// Written By: Baalbisan
//
// Last Modified: 15/04/2026

void returnError (short errorcode);

void printHelp (short *y, short *x, char color_mode);

void printConvertedColor (short red, short green, short blue);

void readAndCheck24bitColorValid (short *color, char colorc);

void readAndCheckHexcodeValid (char hexcode[7], short *red, short *green, short *blue, short *y, short *x);

void promptHandler (char prompt[], char *mode, char color_mode);

void printFlagsHelp (void);

int flagHandler (char* argv[], char *color_mode);
