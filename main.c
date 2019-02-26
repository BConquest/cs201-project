/*
        struct peice
                int colour;
                mabye neighbors

        peice board[][];
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nrows 6
#define ncols 7

struct peice
{
        int colour;
} board[nrows][ncols];

void printBoard()
{
        for(int x = 0; x < nrows; x++)
        {
                for(int y = 0; y < ncols; y++)
                {
                        printf("%d ", board[x][y].colour);
                }
                printf("\n");
        }
}

int addPeice(int j, int colour)
{
        if(j >= ncols) return 0;
	int y;
        for(y = nrows - 1; y > 0; y--)
        {
                if(board[y][j].colour == 0)
                        break;
        }
        if(y == 0 && board[y][j].colour != 0)
        {
                return 0;
        }
        else
        {
                board[y][j].colour = colour;
		return 1;
        }
}

void checkWin()
{
        for(int x = 0; x < nrows; x++)
        {
                for(int y = 0; y < ncols; y++)
                {
                        int colour = board[x][y].colour;
                        if (colour == 0) continue;
                        int count = 0;
                        if(y + 3 < ncols)
                        {
                                if (board[x][y + 1].colour == colour) count += 1;
                                if (board[x][y + 2].colour == colour) count += 1;
                                if (board[x][y + 3].colour == colour) count += 1;
                                if (count == 3) printf("WINS1\n");
                        }
                        if(y - 3 > -1)
                        {
                                if (board[x][y - 1].colour == colour) count += 1;
                                if (board[x][y - 2].colour == colour) count += 1;
                                if (board[x][y - 3].colour == colour) count += 1;
                                if (count == 3) printf("WINS2\n");
                        }
                        if(x + 3 < nrows)
                        {
                                if (board[x + 1][y].colour == colour) count += 1;
                                if (board[x + 2][y].colour == colour) count += 1;
                                if (board[x + 3][y].colour == colour) count += 1;
                                if (count == 3) printf("WINV1\n");
                        }
                        if(x - 3 > -1)
                        {
                                if (board[x - 1][y].colour == colour) count += 1;
                                if (board[x - 2][y].colour == colour) count += 1;
                                if (board[x - 3][y].colour == colour) count += 1;
                                if (count == 3) printf("WINV2\n");
                        }
                        /*
                        if(x + 3 < nrows && y + 3 < ncols)
                        {
                                if (board[x + 1][y + 1].colour == colour) count += 1;
                                if (board[x + 2][y + 2].colour == colour) count += 1;
                                if (board[x + 3][y + 3].colour == colour) count += 1;
                                if (count == 3) printf("WIND1\n");
                        }
                        if(x - 3 > -1 && y - 3 > -1)
                        {
                                if (board[x - 1][y - 1].colour == colour) count += 1;
                                if (board[x - 2][y - 2].colour == colour) count += 1;
                                if (board[x - 3][y - 3].colour == colour) count += 1;
                                if (count == 3) printf("WIND2\n");
                        }*/
                }
        }
}

void clear()
{
	printf("\e[1;1H\e[2J");
}

int main(void)
{
        for(int x = 0; x < nrows; x++)
        {
                for(int y = 0; y < ncols; y++)
                {
                        board[x][y].colour = 0;
                }
        }

        char mode[25];
	char input[25];
	printf("Player or Computer: \n> ");
        scanf("%s", mode);
        while (strcmp(mode, "quit") != 0)
        {
		if(strcmp(mode, "player") == 0)
		{
			int winflag = 0;
			while(winflag == 0)
			{
				clear();
				int add;
				printBoard();
label:
				printf("Player 1 > ");
				scanf("%d", &add);
				if(addPeice(add, 1) == 0)
				{
					printf("Can't add piece there\n");
					goto label;
				}
				printBoard();
label2:
				printf("Player 2 > ");
				scanf("%d", &add);
				if(addPeice(add, 2) == 0)
				{
					printf("Can't add peice there\n");
					goto label2;
				}
				addPeice(add, 2);
				printBoard();
			}
		}
		else if(strcmp(input, "computer") == 0)
		{
		}
		else
		{
			printf("Answer must be Player or Computer\n> ");
		}
                scanf("%s", mode);
        }

        return 0;
}
