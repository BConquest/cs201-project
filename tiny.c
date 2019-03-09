#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nrows = 6;
int ncols = 7;

void printBoard(int *board)
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

void clearBoard(int *board)
{
	int index = 0;
	for(; index < nrows*ncols; index++)
		board[index] = 0;
}

int addPiece(int* board, int j, int colour) {
	
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

int checkHorizontalWin(int* board, int winamount, int index)
{
	int i = 1, count = 0;
	for(; i < winamount; i++)
		if(board[index+i] == board[index])
			count++;
                else
			return 0;
	return count;
}

int checkVerticalWin(int* board, int winamount, int index)
{
	int i = 1, count = 0;
	for(; i < winamount; i++)
		if(board[index-(i*ncols)] == board[index])
			count++;
		else
			return 0;
	return count;
}

int checkUpDiagonalWin(int* board, int winamount, int index)
{
	int i = 1, count = 0;
	for(; i < winamount; i++)
		if(board[index-(i*ncols)+i] == board[index])
			count++;
		else
			return 0;
	return count;
}

int checkDownDiagonalWin(int* board, int winamount, int index)
{
	index += board[0] + winamount - winamount - board[0];
	printf("\n");
	return 0;
}

int checkWin(int* board, int winamount)
{
	int index = (ncols * nrows) - 1;
	for(; index >= 0; index--)
	{
		if(board[index] == 0)
			continue;
		if(((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount)
			if(checkHorizontalWin(board, winamount, index) >= (winamount-1))
				return board[index];
		if((index - ((winamount - 1) * ncols)) >= 0)
			if(checkVerticalWin(board, winamount, index) >= (winamount-1))
				return board[index];
		if((((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount) ||
		   (index - ((winamount - 1) * ncols)) >= 0)
			if(checkUpDiagonalWin(board, winamount, index) >= (winamount-1))
				return board[index];
		if((((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount) ||
		   (index + ((winamount-1) * ncols)) <= ncols*nrows)
			if(checkDownDiagonalWin(board, winamount, index) >= (winamount-1))
				return board[index];
	}

	return 0;
}

void clearScreen()
{
	//printf("\n");
	system("clear");
}

int player(int* board, int winamount)
{
	int playCounter = 0, playerwin = 0, add = 0;
	while(playCounter < (nrows * ncols))
	{
		for(int i = 1; i < 3; i++)
		{
			clearScreen();
			printBoard(board);
			printf("player %d move > ", i);
			scanf("%d", &add);
			while(addPiece(board, add-1, i) == 0)
			{
				printBoard(board);
				printf("Can't add piece there > ");
				scanf("%d", &add);
				clearScreen();
			}	
			playCounter++;
			playerwin = checkWin(board, winamount);
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

int computer(int* board, int winamount)
{
	int playCounter = 0, playerwin = 0, add = 0;
	while(playCounter < (nrows * ncols))
	{
		//clearScreen();
		printBoard(board);
		do
		{
			printf("Player move > ");
			scanf("%d", &add);
		} while(addPiece(board, add, 1) == 0);
		clearScreen();
		playCounter++;
		printf("Computer Moving..\n");
		addPiece(board, getBestMove(winamount), 2);
		playerwin = checkWin(board, winamount);
		if(playerwin != 0)
			return playerwin;
	}
	return 0;
}

void printMenu()
{
	printf("game -> lets you choose to play a game between a person and a computer\n");
	printf("settings -> lets you changes game settings such as board size, and amount to win\n");
	printf("clear -> clears the screen\n");
	printf("help -> displays this help menu, also works in all the other sub menues\n");
	printf("quit -> quits the game\n");
}

void settings(int *board, int winamount)
{
	char setting[25];
	int newsetting = 0;

	clearScreen();
	while(strcmp(setting, "done") != 0)
	{
		printf("setting: ");
		scanf("%s", setting);
		if(strcmp(setting, "width") == 0)
		{
			do
			{
				newsetting = ncols;
				printf("Current Width: %d\nNew Width: ", ncols);
				scanf("%d", &newsetting);
			} while(newsetting < 0);
			ncols = newsetting;
		}
		else if(strcmp(setting, "rows") == 0)
		{
			do
			{
				printf("Current Height: %d\nNew Height: ", nrows);
				scanf("%d", &newsetting);
			} while(newsetting < 0);
			nrows = newsetting;
		}
		else if(strcmp(setting, "amount") == 0)
		{
			do
			{
				printf("Current Amount to win: %d\nNew Amount to win: ", winamount);
				scanf("%d",  &newsetting);
			} while(newsetting < 0);
			winamount = newsetting;
		}
		else if(strcmp(setting, "clear") == 0)
		{
			clearScreen();
		}
		else if(strcmp(setting, "print") == 0)
		{
			printBoard(board);
			printf("width: %d\n", ncols);
			printf("height: %d\n", nrows);
		}
		else if(strcmp(setting, "help") == 0)
		{
			printf("Current commands are: \n");
			printf("width -> sets the new width of the game board\n\thas to be above 0\n");
			printf("height -> sets the new height of the game board\n\thas to be above 0\n");
			printf("amount -> changes the amount you need to win\n\thas to be above 0\n");
			printf("clear -> clears the screen");
			printf("print -> prints current board size\n");
			printf("done -> saves settings and returns to main menu\n");
			printf("help -> prints the message\n");
		}
	}
}

int main(void)
{
	int* board = (int *) malloc((ncols*nrows)* sizeof(int));
	int winamount = 4;
	char mode[25];
	int winner;

	clearBoard(board);
	clearScreen();	
	printMenu();

        while (strcmp(mode, "quit") != 0)
        {
		printf("main menu: ");
		scanf("%s", mode);
		if(strcmp(mode, "game") == 0)
		{
			printf("Player or Computer > ");
			scanf("%s", mode);
			if(strcmp(mode, "player") == 0)
			{
				winner = player(board, winamount);	
				printBoard(board);
				clearBoard(board);
				if(winner == 0)
					printf("Ran out of space to win\n");
				else
					printf("Player %d WON!!\n", winner);
			}
			else if(strcmp(mode, "computer") == 0)
			{
				winner = computer(board, winamount);
				clearBoard(board);
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
		else if (strcmp(mode, "settings") == 0)
		{
			settings(board, winamount);
		}
		else if (strcmp(mode, "clear") == 0)
		{
			clearScreen();
		}
		else if (strcmp(mode, "help") == 0)
		{
			printMenu();
		}
        }
	
	free(board);
        return 0;
}
