#ifndef __board_h__
#define __board_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct gameinfo
{
	int nrows;
	int ncols;
	int winamount;
	int *board;
};


struct gameinfo changeBoardSize(struct gameinfo *);

void printBoard(struct gameinfo *);
void clearBoard(struct gameinfo *);
void clearScreen();
void printMenu();
void settings(struct gameinfo *);


int addPiece(struct gameinfo *, int, int);

int checkHorizontalWin(struct gameinfo *, int);
int checkVericalWin(struct gameinfo *, int);
int checkUpDiagonalWin(struct gameinfo *, int);
int checkDownDiagonalWin(int);
int checkWin(struct gameinfo *);

int player(struct gameinfo *);

int getBestMove(struct gameinfo *);
int computer(struct gameinfo *);

#endif
