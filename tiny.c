#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

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
	clear();
	initscr();

	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();

	printMenu();

        while (strcmp(mode, "quit") != 0)
        {
		mode[0] = '\0';
		printw("main menu: ");
		refresh();
		scanf("%s", mode);
		while(strcmp(mode, "game") == 0)
		{
			printw("Player or Computer > ");
			refresh();
			scanf("%s", person);
			if(strcmp(person, "player") == 0)
			{
				winner = player(&boardinfo);	
				printBoard(&boardinfo);
				clearBoard(&boardinfo);
				if(winner == 0)
				{
					printw("Ran out of space to win\n");
					refresh();
				}
				else
				{
					printw("Player %d WON!!\n", winner);
					refresh();
				}
			}
			else if(strcmp(person, "computer") == 0)
			{
				winner = computer(&boardinfo);
				clearBoard(&boardinfo);
				if(winner == 0)
					printw("Ran out of space to win\n");
				else if(winner == 1)
					printw("You have beat the computer. Congrats\n");
				else if(winner == 2)
					printw("The Computer has beaten you.\n");
				else
					printw("Failure\n");
				refresh();
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
				printw("Answer must be Player or Computer\n");
				refresh();
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
	endwin();
	return 0;
}
