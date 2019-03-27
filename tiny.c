#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/io.h"
#include "./include/game.h"

#include "./include/stack.h"

struct scoreboard
{
	int playervplayer;
	int player1wins;
	int playerdraws;
	int playervcomputer;
	int computerwins;
	int computerdraws;
};

int main(void)
{
	clearScreen();

	struct gameinfo boardinfo;
	struct scoreboard scores;

	boardinfo.ncols = 7;
	boardinfo.nrows = 6;

	boardinfo.board = malloc((boardinfo.ncols * boardinfo.nrows) * sizeof(int));
	boardinfo.winamount = 4;

	scores.playervplayer = 0;
	scores.player1wins = 0;
	scores.playerdraws = 0;
	scores.playervcomputer = 0;
	scores.computerwins = 0;
	scores.computerdraws = 0;

	char mode[25] = {'\0'};
	char person[25] = {'\0'};
	int winner = 0;

	clearBoard(&boardinfo);
	printMenu();
	while (strncmp(mode, "quit", 25) != 0)
	{
		mode[0] = '\0';
		printf( "main menu: ");
		int tested = scanf("%25s", mode);
		while (strncmp(mode, "game", 25) == 0 && tested == 1)
		{
			printf( "game: ");
			scanf("%25s", person);
			if (strncmp(person, "player", 25) == 0)
			{
				winner = player(&boardinfo);
				printBoard(&boardinfo);
				clearBoard(&boardinfo);
				scores.playervplayer = scores.playervplayer + 1;
				if (winner == 0)
				{
					printf( "Ran out of space to win\n");
					scores.playerdraws = scores.playerdraws + 1;
				}
				else
				{
					printf( "Player %d WON!!\n", winner);
					if(winner == 1)
						scores.player1wins = scores.player1wins + 1;
				}
			}
			else if (strncmp(person, "computer", 25) == 0)
			{
				winner = computer(&boardinfo);
				printBoard(&boardinfo);
				clearBoard(&boardinfo);
				scores.playervcomputer = scores.playervcomputer + 1;
				if (winner == 0)
				{
					printf( "Ran out of space to win\n");
					scores.computerdraws = scores.computerdraws + 1;
				}
				else if (winner == 1)
				{
					printf( "You have beat the computer. Congrats\n");
				}
				else if (winner == 2)
				{
					printf( "The Computer has beaten you.\n");
					scores.computerwins = scores.computerwins + 1;
				}
				else
				{
					printf( "Failure\n");
				}
			}
			else if (strncmp(person, "clear", 25) == 0)
			{
				clearScreen();
			}
			else if (strncmp(person, "done", 25) == 0)
			{
				strncpy(mode, "clear", 25);
			}
			else if (strncmp(person, "stats", 25) == 0)
			{
				printf( "====STATS====\n");
				printf( "Player Vs. Player: %d\n", scores.playervplayer);
				printf( "Player1 wins: %d\n", scores.player1wins);
				printf( "Player2 wins: %d\n", scores.playervplayer - scores.player1wins - scores.playerdraws);
				printf( "Amount of Draws: %d\n", scores.playerdraws);
				printf( "Player Vs. Computer: %d\n", scores.playervcomputer);
				printf( "Player wins: %d\n", scores.playervcomputer - scores.computerwins - scores.computerdraws);
				printf( "Computer wins: %d\n", scores.computerwins);
				printf( "Amount of Draws: %d\n", scores.computerdraws);
			}
			else if (strncmp(person, "help", 25) == 0)
			{
				printf( "player -> will enter into a game versues a player\n");
				printf( "computer -> will enter into a game versues a computer\n");
				printf( "\t-> 'easy' -> the computer will play randomly and plays second\n\t-> 'hard' -> the computer uses bfs to find the best move and plays first\n\t>'impossible' -> plays randomly and uses bfs while letting the player go first\n");
				printf( "clear -> clears the screen\n");
				printf( "done -> takes you back to the main menu\n");
				printf( "help -> prints the help message\n");
			}
			else
			{
				printf( "ERROR: '%s' -> not a valid command, try 'help'\n", person);
			}
		}
		if (strcmp(mode, "settings") == 0 && tested == 1)
		{
			settings(&boardinfo);
		}
		else if (strcmp(mode, "clear") == 0 && tested == 1)
		{
			clearScreen();
		}
		else if (strcmp(mode, "help") == 0 && tested == 1)
		{
			printMenu();
		}
		else
		{
			printf( "ERROR: '%s' -> not a valid command, try 'help'\n", mode);
		}
	}
	free(boardinfo.board);
	return 0;
}
