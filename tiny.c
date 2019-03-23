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
	

	int height, width;
	initscr();
	getmaxyx(stdscr, height, width);
	
	clearBoard(&boardinfo);
	clear();
	
	win = newwin(height, width, 1, 1);

	scrollok(win, TRUE);
	echo();

	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();
	
	printMenu();
	
	int tested;

        while (strcmp(mode, "quit") != 0)
        {
		mode[0] = '\0';
		wprintw(win,"main menu: ");
		wrefresh(win);
		tested = wscanw(win, "%s", mode);
		while(strcmp(mode, "game") == 0 && tested == 1)
		{
			wprintw(win,"Player or Computer > ");
			wrefresh(win);
			wscanw(win, "%s", person);
			if(strcmp(person, "player") == 0)
			{
				winner = player(&boardinfo);	
				printBoard(&boardinfo);
				clearBoard(&boardinfo);
				if(winner == 0)
				{
					wprintw(win,"Ran out of space to win\n");
					wrefresh(win);
				}
				else
				{
					wprintw(win,"Player %d WON!!\n", winner);
					wrefresh(win);
				}
			}
			else if(strcmp(person, "computer") == 0)
			{
				winner = computer(&boardinfo);
				printBoard(&boardinfo);
				clearBoard(&boardinfo);
				if(winner == 0)
					wprintw(win,"Ran out of space to win\n");
				else if(winner == 1)
					wprintw(win,"You have beat the computer. Congrats\n");
				else if(winner == 2)
					wprintw(win,"The Computer has beaten you.\n");
				else
					wprintw(win,"Failure\n");
				wrefresh(win);
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
				wprintw(win,"Answer must be Player or Computer\n");
				wrefresh(win);
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
