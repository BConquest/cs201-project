CC = gcc

tiny:
	$(CC) tiny.c game.c -o cnct -O2 -Wall -Wextra -pedantic -lncures

debug:
	$(CC) tiny.c game.c -o cnct -O2 -Wall -Wextra -pedantic -g
