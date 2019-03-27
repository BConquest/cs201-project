#ifndef __io_h__
#define __io_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./game.h"

void printBoard(struct gameinfo *);
void printMenu();
void printSettingsMenu();
void printGameMenu();
void printStats(struct scoreboard *);

/* Inits board to be cleared */
void clearBoard(struct gameinfo *);

/* Clears the console */
void clearScreen();

/* Functions below return 1 when finished */
int settings(struct gameinfo *);
int game(struct gameinfo *, struct scoreboard *);

#endif