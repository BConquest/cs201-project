#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/io.h"
#include "./include/game.h"
#include "./include/config.h"

int main(void)
{
	setConfig();
	clearScreen();

	struct gameinfo boardinfo;
	struct scoreboard scores;

	initGameInfo(&boardinfo, &scores);

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
		else if (strncmp(mode, "settings", 25) == 0 && tested == 1)
		{
			clearScreen();
			printSettingsMenu();
			while (settings(&boardinfo) != 1);
		}
		else if (strncmp(mode, "clear", 25) == 0 && tested == 1)
		{
			clearScreen();
		}
		else if (strncmp(mode, "help", 25) == 0 && tested == 1)
		{
			printMenu();
		}
		else if (strncmp(mode, "quit", 25) == 0 && tested == 1)
		{
			return 1;
		}
		else
		{
			printf("ERROR: '%s' -> not a valid command, try 'help'\n", mode);
		}
	}
	free(boardinfo.board);
	return 0;
}
