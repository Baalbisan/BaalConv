A color code converter, written in C, made to convert colors from hex/rgb(255) to 15-bit rgb. Made for quick color conversion when designing gba sprites.

# INSTALLATION
1. Clone the repository by running:
```
git clone https://github.com/Baalbisan/BaalConv.git
```

2. Compile the code:
    1. Using Clang:
```clang main.c -o baalconv -lncurses```

    2. Using GCC:
```gcc main.c -lncurses -o baalconv```

# USAGE
From the directory in which you installed BaalConv run:
```
./baalconv
```

Available commands can be viewed by typing "help" in the TUI

# KNOWN BUGS
- None at the moment!
Feel free to submit any issues you might encounter.
# CHANGES
- Hexcode too short issue fixed (09/03/2026)
