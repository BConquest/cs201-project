#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

int main(void)
{
	struct gameinfo boardinfo;

	boardinfo.ncols = 7;
	boardinfo.nrows = 6;

	boardinfo.board = (int *) malloc((boardinfo.ncols*boardinfo.nrows) * sizeof(int));
	boardinfo.winamount = 4;
	
	char mode[25] = {'\0'};
	int winner = 0;

	clearBoard(&boardinfo);
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
				winner = player(&boardinfo);	
				printBoard(&boardinfo);
				clearBoard(&boardinfo);
				if(winner == 0)
					printf("Ran out of space to win\n");
				else
					printf("Player %d WON!!\n", winner);
			}
			else if(strcmp(mode, "computer") == 0)
			{
				winner = computer(&boardinfo);
				clearBoard(&boardinfo);
				if(winner == 0)
					printf("Ran out of space to win\n");
				else if(winner == 1)
					printf("You have beat the computer. Congrats\n");
				else if(winner == 2)
					printf("The Computer has beaten you.\n");
				else
					printf("Failure\n");
			}
			else
			{
				printf("Answer must be Player or Computer\n> ");
			}
		}
		else if (strcmp(mode, "settings") == 0)
		{
			settings(&boardinfo);
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
	
	free(boardinfo.board);

        return 0;
}
