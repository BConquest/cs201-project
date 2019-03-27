CC = gcc

tiny:
	$(CC) tiny.c src/game.c src/queue.c src/stack.c src/io.c -o cnct

debug:
	$(CC) tiny.c src/game.c src/queue.c src/stack.c src/io.c -o cnct -Wall -Wextra -pedantic -g
