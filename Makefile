CC = gcc

LIBS = src/config.c src/game.c src/stack.c src/io.c src/win.c src/quicksort.c
DEBUGFLAGS = -Wall -Wextra -pedantic -g


all:
	$(CC) tiny.c $(LIBS) -o cnct

debug:
	$(CC) tiny.c $(LIBS) -o cnct $(DEBUGFLAGS)

clean:
	rm cnct