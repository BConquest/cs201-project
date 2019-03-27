#include "../include/io.h"
#include "../include/config.h"

void printBoard(struct gameinfo *boardinfo)
{
	int index = 0;

	for (; index < boardinfo->nrows * boardinfo->ncols; index++)
	{
		if (index % boardinfo->ncols == 0)
			printf("\n");

		if (boardinfo->board[index] == 0)
		{
			printf("_ ");
		}
		else if (boardinfo->board[index] == 1)
		{
			printf(ANSI_COLOR_RED "%c " ANSI_COLOR_RESET, player1);
		}
		else if (boardinfo->board[index] == 2)
		{
			printf(ANSI_COLOR_BLUE "%c " ANSI_COLOR_RESET, player2);
		}
		else
			printf("E ");
	}
	printf("\n");
	
}

void printMenu()
{
	printf("game -> lets you choose to play a game between a person and a computer\n");
	printf("settings -> lets you changes game settings such as board size, and amount to win\n");
	printf("clear -> clears the screen\n");
	printf("help -> displays this help menu, also works in all the other sub menues\n");
	printf("quit -> quits the game\n");
}

void printSettingsMenu()
{
	printf("Current commands are: \n");
	printf("width -> sets the new width of the game board\n\thas to be above 0\n");
	printf("height -> sets the new height of the game board\n\thas to be above 0\n");
	printf("amount -> changes the amount you need to win\n\thas to be above 0 and smaller than both height and width\n");
	printf("clear -> clears the screen\n");
	printf("print -> prints current board size\n");
	printf("done -> saves settings and returns to main menu\n");
	printf("help -> prints the message\n");
}

void clearBoard(struct gameinfo *boardinfo)
{
	int index = 0;
	for (; index < boardinfo->nrows * boardinfo->ncols; index++)
		boardinfo->board[index] = 0;
}

void clearScreen()
{
	if (DEBUG == 0)
		printf("\n");
	else
		system("clear");
}

void settings(struct gameinfo *boardinfo)
{
	char setting[25] = {'\0'};
	int newsetting = 0;

	clearScreen();
	while (strncmp(setting, "done", 25) != 0)
	{
		setting[0] = '\0';
		printf("setting: ");
		
		scanf("%s", setting);
		if (strncmp(setting, "width", 25) == 0)
		{
			do
			{
				newsetting = boardinfo->ncols;
				printf("Current Width: %d\nNew Width: ", boardinfo->ncols);
				
				int test = scanf("%d", &newsetting);
				while (test != 1)
				{
					printf("That is not a valid number, please input a non-zero positive integer: ");
					test = scanf("%d", &newsetting);
				}
				while (newsetting < boardinfo->winamount)
				{
					printf("That number is to small, please input a nuber larger than the winamount %d\nnew width: ", boardinfo->winamount);
					test = scanf("%d", &newsetting);
					
					while (test != 1)
					{
						printf("That is not a valid number, please input a non-zero positive integer: ");
						test = scanf("%d", &newsetting);
					}
				}
			} while (newsetting <= 0 && (newsetting < boardinfo->winamount));
			boardinfo->ncols = newsetting;
			*boardinfo = changeBoardSize(boardinfo);
			clearBoard(boardinfo);
		}
		else if (strncmp(setting, "height", 25) == 0)
		{
			do
			{
				newsetting = boardinfo->ncols;
				printf("Current height: %d\nNew height: ", boardinfo->nrows);
				
				int test = scanf("%d", &newsetting);
				while (test != 1)
				{
					printf("That is not a valid number, please input a non-zero positive integer: ");
					test = scanf("%d", &newsetting);
					
				}
				while (newsetting < boardinfo->winamount)
				{
					printf("That number is to small, please input a nuber larger than the winamount %d\nnew height: ", boardinfo->winamount);
					test = scanf("%d", &newsetting);
					
					while (test != 1)
					{
						printf("That is not a valid number, please input a non-zero positive integer: ");
						test = scanf("%d", &newsetting);
						
					}
				}
			} while (newsetting <= 0 && (newsetting < boardinfo->winamount));
			boardinfo->ncols = newsetting;
			*boardinfo = changeBoardSize(boardinfo);
			clearBoard(boardinfo);
		}
		else if (strncmp(setting, "amount", 25) == 0)
		{
			do
			{
				printf("Current Amount to win: %d\nNew Amount to win: ", boardinfo->winamount);
				
				int test = scanf("%d", &newsetting);
				while (test != 1)
				{
					printf("That is not a valid number, please input a non-zero positive integer: ");
					test = scanf("%d", &newsetting);
				}
				while (newsetting > boardinfo->nrows || newsetting > boardinfo->ncols)
				{
					printf("That number is to small, please input a nuber smaller than boath board width and height of %d x %d\nnew amount: ", boardinfo->ncols, boardinfo->nrows);
					test = scanf("%d", &newsetting);
					
					while (test != 1)
					{
						printf("That is not a valid number, please input a non-zero positive integer: ");
						test = scanf("%d", &newsetting);
						
					}
				}
			} while (newsetting < 0);
			boardinfo->winamount = newsetting;
		}
		else if (strncmp(setting, "clear", 25) == 0)
		{
			clearScreen();
		}
		else if (strncmp(setting, "print", 25) == 0)
		{
			printBoard(boardinfo);
			printf("width: %d\n", boardinfo->ncols);
			printf("height: %d\n", boardinfo->nrows);
			printf("amount to win: %d\n", boardinfo->winamount);
			
		}
		else if (strncmp(setting, "help", 25) == 0)
		{
            printSettingsMenu();
		}
		else
		{
			printf("ERROR: '%s' is not a command try 'help'\n", setting);
		}
	}
}
