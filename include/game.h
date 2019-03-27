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


#include "./io.h"

/* Updates the current boardsize */
struct gameinfo changeBoardSize(struct gameinfo *);

/* adds a peice at the bottom of the column*/
/* index, color */
int addPiece(struct gameinfo *, int, int);

/* sees if avaible spot to play is good */
int checkAvailable(struct gameinfo *, int);

int checkHorizontalWin(struct gameinfo *, int);
int checkVerticalWin(struct gameinfo *, int);
int checkLeftDiagonalWin(struct gameinfo *, int);
int checkRightDiagonalWin(struct gameinfo *, int);
int validatePath(struct gameinfo *);

/* checks to see if their a path between two indexs */
int bfs(struct gameinfo *boardinfo, int, int, int);
/* checks to see if their a win in the game*/
int checkWin(struct gameinfo *);

/* Is the player state*/
int player(struct gameinfo *);

/* The Computer States */
int easyMode(struct gameinfo *);
int hardMode(struct gameinfo *);
int computer(struct gameinfo *);

#endif
