#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define nrows 7
#define ncols 6

int board[nrows][ncols];

void printBoard()
{
	int x, y;
        for(x = 0; x < nrows; x++) 
	{
                for(y = 0; y < ncols; y++)
		{
                       if(board[x][y] == 0)
			       printf("_ ");
		       else if(board[x][y] == 1)
			       printf("O ");
		       else if(board[x][y] == 2)
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
			board[x][y] = 0;
}

int addPiece(int j, int colour) {
	int y;
        
	if (j >= ncols) return 0;
        
	for(y = nrows - 1; y > 0; y--)
                if(board[y][j] == 0) break;
        
	if(y == 0 && board[y][j] != 0)
                return 0; 
	else 
	{
                board[y][j] = colour;
		return 1;
        }
}

int checkHorizontalWin(int winamount, int x, int y)
{
	int i, count = 0;
	for(i = 1; i < winamount; i++)
		if(board[x][y+i] == board[x][y])
			count++;
                else
			return 0;
	return count;
}

int checkVerticalWin(int winamount, int x, int y)
{
	int i, count = 0;
	for(i = 1; i < winamount; i++)
		if(board[x+i][y] == board[x][y])
			count++;
		else
			return 0;
	return count;
}

int checkUpDiagonalWin(int winamount, int x, int y)
{
	int i, count = 0;
	for(i = 1; i < winamount; i++)
		if(board[x-i][y+i] == board[x][y])
			count++;
		else
			return 0;
	return count;
}

int checkDownDiagonalWin(int winamount, int x, int y)
{
	int i, count = 0;
	for(i = 1; i < winamount; i++)
		if(board[x+i][y+i] == board[x][y])
			count++;
		else
			return 0;
	return count;
}

int checkWin(int winamount)
{
	int x, y; 
	for(x = nrows-1; x > -1; x--)
        {
                for(y = 0; y < ncols; y++)
                {
                        if (board[x][y] == 0)
				continue;
                        
			if(y + (winamount-1) < ncols)
				if(checkHorizontalWin(winamount, x, y) >= (winamount-1))
					return board[x][y];
			
                        if(x + (winamount-1) < nrows)
				if(checkVerticalWin(winamount, x, y) >= (winamount-1))
					return board[x][y];
			
			if(x - (winamount-1) > -1 && y + (winamount-1) < ncols)
				if(checkUpDiagonalWin(winamount, x, y) >= (winamount-1))
					return board[x][y];
			
			if(x + (winamount-1) < nrows && y + (winamount-1) < ncols)
				if(checkDownDiagonalWin(winamount, x, y) >= (winamount-1))
					return board[x][y];
                }
        }
	return 0;
}

void clearScreen()
{
	system("clear");
}

int player(int winamount)
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
			} while(addPiece((add-1), i) == 0);
			playerwin = checkWin(winamount);
			if(playerwin != 0)
				return playerwin;
		}
	}
	return 0;
}

int getBestMove(int winamount)
{
	int x, y;
	for(x = 0; x < ncols; x++)
	{
		for(y = 0; y < nrows; y++)
		{
			if(board[x][y] == 0)
				continue;
			int i = 0;
			if(y + (winamount-1) < ncols)
				i = checkVerticalWin(winamount, x, y);
			printf("should be %d\n", i);
		}
	}
	return rand() % ncols;
}

int computer(int winamount)
{
	int playCounter = 0, playerwin = 0, add = 0;
	while(playCounter < (nrows * ncols))
	{
		//clearScreen();
		printBoard();
		do
		{
			printf("Player move > ");
			scanf("%d", &add);
		} while(addPiece((add-1), 1) == 0);
		clearScreen();
		playCounter++;
		printf("Computer Moving..\n");
		addPiece(getBestMove(winamount), 2);
		playerwin = checkWin(winamount);
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
	int winamount = 4;
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
				winner = player(winamount);	
				clearBoard();
				if(winner == 0)
					printf("Ran out of space to win\n");
				else
					printf("Player %d WON!!\n", winner);
			}
			else if(strcmp(mode, "computer") == 0 || mode[0] == 'c')
			{
				winner = computer(winamount);
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
			printf("width         -> %d\n", ncols);
			printf("height        -> %d\n", nrows);
			printf("amount to win -> %d\n", winamount);
			printf("new height > ");
			scanf("%d", &winner);
			//nrows = winner;
			printf("new width > ");
			scanf("%d", &winner);
			//ncols = winner;
			printf("new amount to win > ");
			scanf("%d", &winamount);
		}
        }

        return 0;
}
