A color code converter, written in C, utilizing the ncurses library, made to convert colors from hex/24-bit rgb to 15-bit rgb. Made for quick color conversion when designing gba sprites.

# INSTALLATION
- Clone the repository by running:
```
git clone https://github.com/Baalbisan/BaalConv.git
```  
- Compile using make  
```
make
```
*NOTE: you will need to have the Gnu Compiler Collection installed as this is what the makefile uses.*

# USAGE
From the directory in which you installed BaalConv run:
```
./baalconv
```

Available commands can be viewed by typing "help" in the TUI

# KNOWN BUGS
- if wrong color is entered selecting n is broken
    - *REPLICATE:* hex -> random hexcode -> n doesn't work  
    or color -> random color -> n doesn't work  
    **Feel free to submit any issues you might encounter.**
# CHANGES
- Issue {#1} resolved (inval hexcodes accepted if in an even position).
- Minor visual bug straightened out.
