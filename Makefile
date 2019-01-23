all: main

main: main.c coord.c com.c graphics.c sound.c sound.c general.h
	gcc -g -ansi -Wall -std=gnu99 -pedantic -o main main.c coord.c com.c graphics.c sound.c  ILS.c -lm -lrt -lpthread -lg2 -lvlc
