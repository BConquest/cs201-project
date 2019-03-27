#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/io.h"
#include "./include/game.h"

#include "./include/stack.h"

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

	clearBoard(&boardinfo);
	printMenu();
	while (strncmp(mode, "quit", 25) != 0)
	{
		mode[0] = '\0';
		printf("main menu: ");
		int tested = scanf("%25s", mode);
		if (strncmp(mode, "game", 25) == 0 && tested == 1)
		{
			clearScreen();
			printGameMenu();
			while(game(&boardinfo, &scores) != 1);
		}
		else if (strcmp(mode, "settings") == 0 && tested == 1)
		{
			clearScreen();
			printSettingsMenu();
			while (settings(&boardinfo) != 1);
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
			printf("ERROR: '%s' -> not a valid command, try 'help'\n", mode);
		}
	}
	free(boardinfo.board);
	return 0;
}
