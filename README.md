A color code converter, written in C, utilizing the ncurses library, made to convert colors from hex/24-bit rgb to 15-bit rgb. Made for quick color conversion when designing gba sprites.

# INSTALLATION
- Download and decompress the source code from the latest stable release or alternatively, clone the repository by running:
```
git clone https://github.com/Baalbisan/BaalConv.git
```
- Compile using make  
```
make
```
*NOTE: you will need to have the Gnu Compiler Collection installed as this is what the makefile uses.*
- Add bash(or zsh) alias  
*In ~/.bashrc (or ~/.zshrc)*
```
alias baalconv='/path/to/where/you/installed/baalconv'
```
  
  *NOTE: If your terminal does not support colors use the `--no-color` flag*
- Update bash/zsh
```
source ~/.bashrc
```

# USAGE
From any directory run:
```
baalconv
```  

Available commands can be viewed by typing "help" in the TUI.

# KNOWN BUGS
None at the moment !  
**Feel free to submit any issues you might encounter.**
# CHANGES (V2.0.0)
- Added full color support.
- Added command line arguments.

### ncurses
Ncurses is licensed under the Gnu Lesser General Public License version 2.1 (LGPL-2.1).
The license itself is included in the acknowledgments directory.
