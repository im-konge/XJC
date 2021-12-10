CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
SOURCE = matice.c main.c
EXE = main

ALL:
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE)

r: run
run: 
	./$(EXE)