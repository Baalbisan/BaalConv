// main.c
//
// Written By: Baalbisan
//
// Last Modifed: 05/04/2026

#include <ncurses.h>
#include "./conv/rgb.h"
#include "./conv/hex.h"
#include "./functional/functional.h"

int main (int argc, char* argv[]){
    int currentx, currenty;
	char mode = 2;
	char prompt[6];
    char color_mode = 1;

    if (argc > 1){
        switch (flagHandler(argv, &color_mode)){
            case -1:
                return 0;
                break;
            default:
                break;
        }
    }
    
    initscr();
    start_color();
    use_default_colors();

    if (!has_colors()){
        printf("Your terminal does not support colors!\nFIX: run baalconv --no-color.\n\tIf you have an alias, edit ~/.bashrc(or~/.zshrc) and change alias baalconv='path/to/where/you/installed/baalconv --no-color'\n\tUpdate your env. source ~/.bashrc(or ~/.zshrc)\n");
        return 0;
    }
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_CYAN, -1);
    init_pair(4, COLOR_BLUE, -1);


	mvprintw(0, 0,"Type the command help to see available commands.");
    if (color_mode == 0){
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
    }
    else if (color_mode == 1){
        do{
	        if (mode == 1){
		        attron(A_BLINK);
                attron(COLOR_PAIR(1));
    	    	mvprintw(0, 0,"=>");
	    	    refresh();
    	    	attroff(A_BLINK);
                attron(COLOR_PAIR(1));
		
		    	//read prompt
    			getnstr(prompt, 6);
        		promptHandler(prompt, &mode);
	        	if (mode != 0)
		        	mode = 2;
        	}
	        else if (mode == 2){
		        getyx(stdscr, currenty, currentx);
			    attron(A_BLINK);
                attron(COLOR_PAIR(1));
    	    	mvprintw(currenty+1, 0,"=>");
	    	    refresh();
		    	attroff(A_BLINK);
                attroff(COLOR_PAIR(1));
		
    	    	//read prompt
	    	    getnstr(prompt, 6);
    	    	promptHandler(prompt, &mode);
	    	}
        }while(mode != 0);
    }
	
	endwin();
	return 0;
}
