CC = gcc
SRC = ./src/main.c \
	  ./src/functional/functional.c \
	  ./src/conv/hex.c \
	  ./src/conv/rgb.c

baalconv: $(SRC)
	$(CC) $(SRC) -o baalconv -lncurses
