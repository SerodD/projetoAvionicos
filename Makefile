all: main

main: main.c coord.c com.c graphics.c sound.c sound.c general.h
	gcc -g -Wall -std=gnu99 -pedantic -o main coord.c com.c graphics.c sound.c sound.c -lrt -lpthread -lg2 -lvlcs -lm