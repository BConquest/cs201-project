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

void printGameMenu()
{
	printf("player -> will enter into a game versues a player\n");
	printf("computer -> will enter into a game versues a computer\n");
	printf("\t-> 'easy' -> the computer will play randomly and plays second\n\t-> 'hard' -> the computer uses bfs to find the best move and plays first\n\t>'impossible' -> plays randomly and uses bfs while letting the player go first\n");
	printf("clear -> clears the screen\n");
	printf("done -> takes you back to the main menu\n");
	printf("help -> prints the help message\n");
}

void printStats(struct scoreboard *scores)
{
	printf("====STATS====\n");
	printf("Player Vs. Player: %d\tPlayer Vs. Computer: %d\n", scores->playervplayer, scores->playervcomputer);
	printf("Player-1 wins: %d\tPlayer wins: %d\n", scores->player1wins, scores->playervcomputer - scores->computerwins - scores->computerdraws);
	printf("Player-2 wins: %d\tComputer wins: %d\n", scores->playervplayer - scores->player1wins - scores->playerdraws, scores->computerwins);
	printf("Number of Draws: %d\tAmount of Draws: %d\n", scores->playerdraws, scores->computerdraws);
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
	clearScreen();
	printSettingsMenu();
	char setting[25] = {'\0'};
	int newsetting = 0;

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

int game(struct gameinfo *boardinfo, struct scoreboard *scores)
{
	int winner;
	char person[25];
	printf("game: ");
	scanf("%25s", person);
	if (strncmp(person, "player", 25) == 0)
	{
		winner = player(boardinfo);
		printBoard(boardinfo);
		clearBoard(boardinfo);
		scores->playervplayer = scores->playervplayer + 1;
		if (winner == 0)
		{
			printf("Ran out of space to win\n");
			scores->playerdraws = scores->playerdraws + 1;
		}
		else
		{
			printf("Player %d WON!!\n", winner);
			if (winner == 1)
				scores->player1wins = scores->player1wins + 1;
		}
	}
	else if (strncmp(person, "computer", 25) == 0)
	{
		winner = computer(boardinfo);
		printBoard(boardinfo);
		clearBoard(boardinfo);
		scores->playervcomputer = scores->playervcomputer + 1;
		if (winner == 0)
		{
			printf("Ran out of space to win\n");
			scores->computerdraws = scores->computerdraws + 1;
		}
		else if (winner == 1)
		{
			printf("You have beat the computer. Congrats\n");
		}
		else if (winner == 2)
		{
			printf("The Computer has beaten you.\n");
			scores->computerwins = scores->computerwins + 1;
		}
		else
		{
			printf("Failure\n");
		}
	}
	else if (strncmp(person, "clear", 25) == 0)
	{
		clearScreen();
	}
	else if (strncmp(person, "done", 25) == 0)
	{
		return 1;
	}
	else if (strncmp(person, "stats", 25) == 0)
	{
		printStats(scores);
	}
	else if (strncmp(person, "help", 25) == 0)
	{
		printGameMenu();
	}
	else
	{
		printf("ERROR: '%s' -> not a valid command, try 'help'\n", person);
	}
	return 0;
}
