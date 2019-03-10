CC = gcc

tiny:
	$(CC) tiny.c src/game.c src/stack.c -o cnct -O2 -Wall -Wextra -pedantic

debug:
	$(CC) tiny.c src/game.c src/stack.c -o cnct -O2 -Wall -Wextra -pedantic -g
