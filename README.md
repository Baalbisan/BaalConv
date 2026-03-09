A color code converter, written in C, made to convert colors from hex/rgb(255) to 15-bit rgb. Made for quick color conversion when designing gba sprites.

# INSTALLATION:
1. Clone the repository by running:
```
git clone https://github.com/Baalbisan/BaalConv.git
```

2. Compile the code:
    1. Using Clang:
```clang main.c -o baalconv -lncurses```

    2. Using GCC:
```gcc main.c -lncurses -o baalconv```

# USAGE:
From the directory in which you installed BaalConv run:
```
./baalconv
```

Commands can be viewed by typing "help" in the TUI

# KNOWN BUGS:
- hex too short breaks shit, possible infiniloop
    1. REPLICATE: hex and type a code shorter than 6 digits (#ABCDEF)
        - dev notes: it doesn't have to do with leftover getnstrs needing to be fulfilled. It for some reason gets trapped in a loop that repeats reading, needs more debugging

# CHANGES:
   - Quit not working fixed (09/03/2026)
