#ifndef __io_h__
#define __io_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./game.h"

/* Prints the gameboard of the game passed to it */
void printBoard(struct gameinfo *);

/* Prints help menus for each of the menus*/
void printMenu();
void printSettingsMenu();
void printGameMenu();

/* Prints Stats for the current session */
void printStats(struct scoreboard *);

/* Inits board to be cleared */
void clearBoard(struct gameinfo *);

/* Clears the console */
void clearScreen();

/* Functions below return 1 when finished */
int settings(struct gameinfo *);
int game(struct gameinfo *, struct scoreboard *);

#endif