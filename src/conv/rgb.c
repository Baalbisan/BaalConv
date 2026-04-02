// rgb.c
//
// Written By: Baalbisan
//
// Last Modified: 02/04/2026

//rgb * 31 / 255 rounded
short convertTo15bitRGB (short rgb){
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
