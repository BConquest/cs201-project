CC = gcc

tiny:
	$(CC) tiny.c src/config.c src/game.c src/stack.c src/io.c src/win.c src/quicksort.c src/queue.c -o cnct

debug:
	$(CC) tiny.c src/config.c src/game.c src/stack.c src/io.c src/win.c src/quicksort.c src/queue.c -o cnct -Wall -Wextra -pedantic -g
