baalconv: ./src/main.c
	gcc ./src/main.c ./src/functional/functional.c ./src/conv/hex.c ./src/conv/rgb.c -o baalconv -lncurses
