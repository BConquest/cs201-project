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

void clearBoard(struct gameinfo *);
void clearScreen();

void settings(struct gameinfo *);
int game(struct gameinfo *, struct scoreboard *);

#endif