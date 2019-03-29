CC = gcc

LIBS = src/config.c src/game.c src/stack.c src/io.c src/win.c src/quicksort.c

all:
	$(CC) tiny.c $(LIBS) src/queue.c -o cnct

debug:
	$(CC) tiny.c $(LIBS) -o cnct -Wall -Wextra -pedantic -g

clean:
	rm cnct