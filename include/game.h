#ifndef __board_h__
#define __board_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "./queue.h"

WINDOW *win;

/* Holds info about the current board */
struct gameinfo
{
	int nrows;
	int ncols;
	int winamount;
	int *board;
};

/* Updates the current boardsize */
struct gameinfo changeBoardSize(struct gameinfo *);

/* Prints board X for player 2 and O for player 1 */
void printBoard(struct gameinfo *);

/* Resets the board to be all 0's */
void clearBoard(struct gameinfo *);

/* Clears the screen */
void clearScreen();

/* Main menu screen */
void printMenu();

/* Allows you to change most of the things about the game */
void settings(struct gameinfo *);

/* adds a peice at the bottom of the column*/
/* index, color */
int addPiece(struct gameinfo *, int, int);

/* sees if avaible spot to play is good */
int checkAvailable(struct gameinfo *, int);

int checkHorizontalWin(struct gameinfo *, int);
int checkVerticalWin(struct gameinfo *, int);
int checkUpDiagonal(struct gameinfo *, int);
int checkDownDiagonal(struct gameinfo *, int);
int validatePath(struct gameinfo *);

/* checks to see if their a path between two indexs */
int bfs(struct gameinfo *boardinfo, int, int);
/* checks to see if their a win in the game*/
int checkWin(struct gameinfo *);

/* Is the player state*/
int player(struct gameinfo *);

/* The Computer States */
int easyMode(struct gameinfo *);
int hardMode(struct gameinfo *);
int computer(struct gameinfo *);

#endif
