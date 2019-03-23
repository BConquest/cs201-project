CC = gcc

tiny:
	$(CC) tiny.c src/game.c src/queue.c src/stack.c -o cnct -lncurses

debug:
	$(CC) tiny.c src/game.c src/queue.c src/stack.c -o cnct -O2 -Wall -Wextra -pedantic -lncurses -g
