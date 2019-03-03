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
	int x, y;
        for(x = 0; x < nrows; x++) 
	{
                for(y = 0; y < ncols; y++)
		{
                       if(board[x][y].colour == 0)
			       printf("_ ");
		       else if(board[x][y].colour == 1)
			       printf("O ");
		       else if(board[x][y].colour == 2)
			       printf("X ");
		       else
			       printf("E");
		}
                printf("\n");
        }
}

void clearBoard()
{
	int x, y;
	for(x = 0; x < nrows; x++)
		for(y = 0; y < ncols; y++)
			board[x][y].colour = 0;
}

int addPiece(int j, int colour) {
	int y;
        
	if (j >= ncols) return 0;
        
	for(y = nrows - 1; y > 0; y--)
                if(board[y][j].colour == 0) break;
        
	if(y == 0 && board[y][j].colour != 0)
                return 0; 
	else 
	{
                board[y][j].colour = colour;
		return 1;
        }
}


int checkWin()
{
	int x, y, i, count;        
	for(x = 0; x < nrows; x++)
        {
                for(y = 0; y < ncols; y++)
                {
                        if (board[x][y].colour == 0) continue;
                        count = 0;
			if(y + 3 < ncols)
			{
				for(i = 1; i < 4; i++)
					if(board[x][y+i].colour == board[x][y].colour) count++;
				if(count >= 3) return board[x][y].colour;
			}
			count = 0;
                        if(x + 3 < nrows)
			{
				for(i = 1; i < 4; i++)
					if(board[x+i][y].colour == board[x][y].colour) count++;
				if(count >= 3) return board[x][y].colour;
			}
			count = 0;
			if(x - 3 > -1 && y + 3 < ncols)
			{
				for(i = 1; i < 4; i++)
					if(board[x-i][y+i].colour == board[x][y].colour) count++;
				if(count >= 3) return board[x][y].colour;
			}
			count = 0;
			if(x + 3 < nrows && y + 3 < ncols)
			{
				for(i = 1; i < 4; i++)
					if(board[x+i][y+i].colour == board[x][y].colour) count++;
				if(count >= 3) return board[x][y].colour;
			}
                }
        }
	return 0;
}

void clearScreen()
{
	system("clear");
}

int player()
{
	int playCounter = 0, playerwin = 0, add = 0;
	while(playCounter < (nrows * ncols))
	{
		clearScreen();
		for(int i = 1; i < 3; i++)
		{
			do
			{
				printBoard();
				printf("Player %d move > ", i);
				scanf("%d", &add);
				clearScreen();
				playCounter++;
			} while(addPiece(add, i) == 0);
			playerwin = checkWin();
			if(playerwin != 0)
				return playerwin;
		}
	}
	return 0;
}

int computer()
{
	int playCounter = 0, playerwin = 0, add = 0;
	while(playCounter < (nrows * ncols))
	{
		clearScreen();
		printBoard();
		do
		{
			printf("Player move > ");
			scanf("%d", &add);
		} while(addPiece(add, 1) == 0);
		clearScreen();
		playCounter++;
		printf("Computer Moving..\n");
		addPiece(rand() % ncols, 2);
		playerwin = checkWin();
		if(playerwin != 0)
			return playerwin;
	}
	return 0;
}

void printMenu()
{
	printf("game will let you select either player or computer to play against\n");
	printf("size will let you set custom sizes\n");
	printf("quit will exit the game\n");
	printf("> ");
}

int main(void)
{
	char mode[25];
	int winner;

	clearBoard();
	clearScreen();	

        while (strcmp(mode, "quit") != 0)
        {
		printMenu();
		scanf("%s", mode);
		if(strcmp(mode, "game") == 0)
		{
			printf("Player or Computer > ");
			scanf("%s", mode);
			if(strcmp(mode, "player") == 0 || mode[0] == 'p')
			{
				winner = player();	
				clearBoard();
				if(winner == 0)
					printf("Ran out of space to win\n");
				else
					printf("Player %d WON!!\n", winner);
			}
			else if(strcmp(mode, "computer") == 0 || mode[0] == 'c')
			{
				winner = computer();
				clearBoard();
				if(winner == 0)
					printf("Ran out of space to win\n");
				else
				{
					if(winner == 1)
						printf("You have beat the computer. Congrats\n");
					else
						printf("The Computer has beaten you.\n");
				}
			}
			else
			{
				printf("Answer must be Player or Computer\n> ");
			}
		}
		else if (strcmp(mode, "size") == 0)
		{
			printf("coloumns -> %d\n", ncols);
			printf("height   -> %d\n", nrows);
			printf("new height > ");
			scanf("%d", &winner);
			//nrows = winner;
			printf("new width > ");
			scanf("%d", &winner);
			//ncols = winner;
		}
        }

        return 0;
}
