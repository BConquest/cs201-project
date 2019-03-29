#ifndef __win_h__
#define __win_h__

#include "./game.h"
/* These functions take 2 inputs
 * 1) The board
 * 2) The index it starts at 
 */
int checkHorizontalWin(struct gameinfo *, int); /* Checks to the right */
int checkVerticalWin(struct gameinfo *, int); /* Checks upwards */
int checkRightDiagonalWin(struct gameinfo *, int); /* Checks up and to the right */
int checkLeftDiagonalWin(struct gameinfo *, int); /* Checks up and to the left */

int checkWin(struct gameinfo *);
#endif