#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define nrows 6
#define ncols 7

int board[nrows * ncols];

void printBoard()
{
	int index = 0;
        for(; index < nrows*ncols; index++) 
	{
                if(index % ncols == 0)
			printf("\n");
		if(board[index] == 0)
			printf("_ ");
		else if(board[index] == 1)
			printf("O ");
		else if(board[index] == 2)
			printf("X ");
		else
			printf("E");
        }
	printf("\n");
}

void clearBoard()
{
	int index = 0;
	for(; index < nrows*ncols; index++)
		board[index] = 0;
}

int addPiece(int j, int colour) {
	
	int index = (nrows-1)*ncols + j;

	if (j > ncols || j < 0 ) return 0;
	
	for(;index > (ncols-1);index-=ncols)
		if(board[index] == 0) break;
	
	if(index < ncols && board[index] != 0)
		return 0;
	else
	{
		board[index] = colour;
		return 1;
	}
}

int checkHorizontalWin(int winamount, int index)
{
	int i = 1, count = 0;
	for(; i < winamount; i++)
		if(board[index+i] == board[index])
			count++;
                else
			return 0;
	return count;
}

int checkVerticalWin(int winamount, int index)
{
	int i = 1, count = 0;
	for(; i < winamount; i++)
		if(board[index-(i*ncols)] == board[index])
			count++;
		else
			return 0;
	return count;
}

int checkUpDiagonalWin(int winamount, int index)
{
	int i = 1, count = 0;
	for(; i < winamount; i++)
		if(board[index-(i*ncols)+i] == board[index])
			count++;
		else
			return 0;
	return count;
}

int checkDownDiagonalWin(int winamount, int index)
{
	printf("%d \n", index);
	return 0;
}

int checkWin(int winamount)
{
	int index = (ncols * nrows) - 1;
	for(; index >= 0; index--)
	{
		if(board[index] == 0)
			continue;
		if(((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount)
			if(checkHorizontalWin(winamount, index) >= (winamount-1))
				return board[index];
		if((index - ((winamount - 1) * ncols)) >= 0)
			if(checkVerticalWin(winamount, index) >= (winamount-1))
				return board[index];
		if((((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount) ||
		   (index - ((winamount - 1) * ncols)) >= 0)
			if(checkUpDiagonalWin(winamount, index) >= (winamount-1))
				return board[index];
		if((((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount) ||
		   (index + ((winamount-1) * ncols)) <= ncols*nrows)
			if(checkDownDiagonalWin(winamount, index) >= (winamount-1))
				return board[index];
	}

	return 0;
}

void clearScreen()
{
	//printf("\n");
	system("clear");
}

int player(int winamount)
{
	int playCounter = 0, playerwin = 0, add = 0;
	while(playCounter < (nrows * ncols))
	{
		for(int i = 1; i < 3; i++)
		{
			clearScreen();
			printBoard();
			printf("player %d move > ", i);
			scanf("%d", &add);
			while(addPiece(add-1, i) == 0)
			{
				printBoard();
				printf("Can't add piece there > ");
				scanf("%d", &add);
				clearScreen();
			}	
			playCounter++;
			playerwin = checkWin(winamount);
			if(playerwin != 0)
				return playerwin;			
		}
	}
	return 0;
}

int getBestMove(int winamount)
{
	return rand() % ncols + winamount - winamount;
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
		} while(addPiece(add, 1) == 0);
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
				printBoard();
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
