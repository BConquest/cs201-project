#include <stdio.h>

typedef struct vertex
{
	int x;
	int y;
} vertex;

typedef struct board
{
	vertex edge[8];
	int colour;
	int width;
	int height;
} board;

void addPeice(int color, int x, int y,board *connect)
{
	connect[x][y]->colour = color;
	return;
}

void printBoard(board *connect)
{
	int x = connect->width;
	int y = connect->height;
	int i,j;

	for(i = 0; i < x; i++)
	{
		for(j = 0; j < y; j++)
		{
			printf("%d", &board[x][y]->colour);
		}
		printf("\n");
	}
}

int checkWin(int x, int y, board *connect)
{
	return 0;
}
