CC = gcc

tiny:
	$(CC) tiny.c src/game.c src/stack2.c src/io.c src/win.c src/quicksort.c -o cnct

debug:
	$(CC) tiny.c src/game.c src/stack2.c src/io.c src/win.c src/quicksort.c -o cnct -Wall -Wextra -pedantic -g
