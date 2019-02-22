/*
--- General Sentax On How to Use ---

1 2 3
4 n 5 -- Positions of neighbor cells
6 7 8

struct vertex
{
	int x;
	int y;
};

struct
{
	struct vertex edge[4];
	int colour;
} board[8][6];

board[0][0].edge[0] = (struct vertex){ 1,0 }; //vertext at 0,0 has an edge to 1,0
*/

#ifndef __board_h__
#define __board_h__

typedef struct vertex {} vertex;

typedef struct board {} board;

void addPeice(int, int, int, board **);
void printboard(board **);

int checkWin(int, int, board **);

#endif
