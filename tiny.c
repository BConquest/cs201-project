#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/game.h"
#include "./include/stack.h"

int main(void)
{
	struct gameinfo boardinfo;

	boardinfo.ncols = 7;
	boardinfo.nrows = 6;

	boardinfo.board = malloc((boardinfo.ncols*boardinfo.nrows) * sizeof(int));
	boardinfo.winamount = 4;
	
	char mode[25] = {'\0'};
	char person[25] = {'\0'};
	int winner = 0;

	clearBoard(&boardinfo);
	clearScreen();	
	printMenu();

        while (strcmp(mode, "quit") != 0)
        {
		mode[0] = '\0';
		printf("main menu: ");
		scanf("%s", mode);
		while(strcmp(mode, "game") == 0)
		{
			printf("Player or Computer > ");
			scanf("%s", person);
			if(strcmp(person, "player") == 0)
			{
				winner = player(&boardinfo);	
				printBoard(&boardinfo);
				clearBoard(&boardinfo);
				if(winner == 0)
					printf("Ran out of space to win\n");
				else
					printf("Player %d WON!!\n", winner);
			}
			else if(strcmp(person, "computer") == 0)
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
			else if (strcmp(person,"clear") == 0)
			{
				clearScreen();
			}
			else if (strcmp(person, "done") == 0)
			{
				mode[0] = '\0';
			}
			else
			{
				printf("Answer must be Player or Computer\n");
			}
		}
		if (strcmp(mode, "settings") == 0)
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
