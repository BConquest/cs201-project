#ifndef __board_h__
#define __board_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./queue.h"

/* Holds info about the current board */
struct gameinfo
{
	int nrows;
	int ncols;
	int winamount;
	int *board;
};

struct scoreboard
{
	int playervplayer;
	int player1wins;
	int playerdraws;
	int playervcomputer;
	int computerwins;
	int computerdraws;
};

/* Included later since structs above are needed */
#include "./io.h"
#include "./win.h"
#include "./quicksort.h"

/* Updates the current boardsize */
struct gameinfo changeBoardSize(struct gameinfo *);

/* adds a peice at the bottom of the column*/
/* index, color */
int addPiece(struct gameinfo *, int, int);

/* sees if avaible spot to play is good returns */
int checkAvailable(struct gameinfo *, int);

/* checks to see if their a path between two indexs */
int bfs(struct gameinfo *boardinfo, int, int, int);

/* Is the player state*/
int player(struct gameinfo *);

/* The Computer States */
int easyMode(struct gameinfo *);
int hardMode(struct gameinfo *);
int computer(struct gameinfo *);

#endif
