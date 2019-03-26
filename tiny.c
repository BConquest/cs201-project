#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

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

	int height, width;
	initscr();
	getmaxyx(stdscr, height, width);

	clearBoard(&boardinfo);
	clear();

	win = newwin(height, width, 1, 1);

	scrollok(win, TRUE);
	echo();

	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();

	printMenu();

	while (strncmp(mode, "quit", 25) != 0)
	{
		mode[0] = '\0';
		wprintw(win, "main menu: ");
		wrefresh(win);
		int tested = wscanw(win, "%25s", mode);
		while (strncmp(mode, "game", 25) == 0 && tested == 1)
		{
			wprintw(win, "game: ");
			wrefresh(win);
			wscanw(win, "%25s", person);
			if (strncmp(person, "player", 25) == 0)
			{
				winner = player(&boardinfo);
				printBoard(&boardinfo);
				clearBoard(&boardinfo);
				scores.playervplayer = scores.playervplayer + 1;
				if (winner == 0)
				{
					wprintw(win, "Ran out of space to win\n");
					wrefresh(win);
					scores.playerdraws = scores.playerdraws + 1;
				}
				else
				{
					wprintw(win, "Player %d WON!!\n", winner);
					wrefresh(win);
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
					wprintw(win, "Ran out of space to win\n");
					scores.computerdraws = scores.computerdraws + 1;
				}
				else if (winner == 1)
				{
					wprintw(win, "You have beat the computer. Congrats\n");
				}
				else if (winner == 2)
				{
					wprintw(win, "The Computer has beaten you.\n");
					scores.computerwins = scores.computerwins + 1;
				}
				else
				{
					wprintw(win, "Failure\n");
				}
				wrefresh(win);
			}
			else if (strncmp(person, "clear", 25) == 0)
			{
				clearScreen();
			}
			else if (strncmp(person, "done", 25) == 0)
			{
				mode[0] = '\0';
			}
			else if (strncmp(person, "help", 25) == 0)
			{
				wprintw(win, "player -> will enter into a game versues a player\n");
				wprintw(win, "computer -> will enter into a game versues a computer\n");
				wprintw(win, "\t-> 'easy' -> the computer will play randomly and plays second\n\t-> 'hard' -> the computer uses bfs to find the best move and plays first\n\t>'impossible' -> plays randomly and uses bfs while letting the player go first\n");
				wprintw(win, "clear -> clears the screen\n");
				wprintw(win, "done -> takes you back to the main menu\n");
				wprintw(win, "help -> prints the help message\n");
			}
			else
			{
				wprintw(win, "ERROR: '%s' -> not a valid command, try 'help'\n", person);
				wrefresh(win);
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
			wprintw(win, "ERROR: '%s' -> not a valid command, try 'help'\n", mode);
		}
	}

	free(boardinfo.board);
	delwin(win);
	endwin();
	return 0;
}
