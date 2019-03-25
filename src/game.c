#include "../include/game.h"
#include "../include/config.h"

void printBoard(struct gameinfo *boardinfo)
{
	int index = 0;

	/* Colors are inverted so that they are more visible */
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);

	for (; index < boardinfo->nrows * boardinfo->ncols; index++)
	{
		if (index % boardinfo->ncols == 0)
			wprintw(win, "\n");

		if (boardinfo->board[index] == 0)
		{
			wattron(win, COLOR_PAIR(3));
			wprintw(win, "_ ");
			wattroff(win, COLOR_PAIR(3));
		}
		else if (boardinfo->board[index] == 1)
		{
			wattron(win, COLOR_PAIR(1));
			wprintw(win, "%c ", player1);
			wattroff(win, COLOR_PAIR(1));
		}
		else if (boardinfo->board[index] == 2)
		{
			wattron(win, COLOR_PAIR(2));
			wprintw(win, "%c ", player2);
			wattroff(win, COLOR_PAIR(2));
		}
		else
			wprintw(win, "E ");
	}
	wprintw(win, "\n");
	wrefresh(win);
}

void clearBoard(struct gameinfo *boardinfo)
{
	int index = 0;
	for (; index < boardinfo->nrows * boardinfo->ncols; index++)
		boardinfo->board[index] = 0;
}

int addPiece(struct gameinfo *boardinfo, int j, int colour)
{
	/* Checks to see if that is a valid place to place */
	if (j >= boardinfo->ncols || j < 0)
		return 0;

	/* Calculates the current index bassed on a column number */
	int index = (boardinfo->nrows - 1) * boardinfo->ncols + j;

	/* Loops through the column to finding a free space */
	for (; index > (boardinfo->ncols - 1); index -= boardinfo->ncols)
		if (boardinfo->board[index] == 0)
			break;

	/* if last space is filled returns error else places peice */
	if (index < boardinfo->ncols && boardinfo->board[index] != 0)
		return 0;
	else
		boardinfo->board[index] = colour;

	return 1;
}

int checkAvailable(struct gameinfo *boardinfo, int j)
{
	/* Does the same thing as add Piece without adding the peice */
	if (j >= boardinfo->ncols || j < 0)
		return 0;

	int index = (boardinfo->nrows - 1) * boardinfo->ncols + j;

	for (; index > (boardinfo->ncols - 1); index -= boardinfo->ncols)
		if (boardinfo->board[index] == 0)
			break;

	if (index < boardinfo->ncols && boardinfo->board[index] != 0)
		return 0;

	return 1;
}

int checkHorizontalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks the horizontal winning */
	int i = 1, count = 0;
	for (; i < boardinfo->winamount; i++)
	{
		if (index + i < boardinfo->nrows * boardinfo->ncols)
		{
			if (boardinfo->board[index + i] == boardinfo->board[index])
				count++;
			else
				return 0;
		}
	}
	return 0;
}

int checkVerticalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Vertical winning */
	int i = 1, count = 0;
	for (; i < boardinfo->winamount; i++)
	{
		if (index - (i * boardinfo->ncols) > -1)
		{
			if (boardinfo->board[index - (i * boardinfo->ncols)] == boardinfo->board[index])
				count++;
			else
				return 0;
		}
	}
	return 0;
}

int checkUpDiagonalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Up diagonal winning */
	int i = 1, count = 0;
	for (; i < boardinfo->winamount; i++)
	{
		if (index - (i * boardinfo->ncols) + i > -1)
		{
			if (boardinfo->board[index - (i * boardinfo->ncols) + i] == boardinfo->board[index])
				count++;
			else
				return 0;
		}
	}
	return 0;
}

int checkDownDiagonalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Down Diagonal winning */
	int i = 1, count = 0;
	for (; i < boardinfo->winamount; i++)
	{
		if (index + (i * boardinfo->ncols) + i < boardinfo->nrows * boardinfo->ncols)
		{
			if (boardinfo->board[index + (i * boardinfo->ncols) + i] == boardinfo->board[index])
				count++;
			else
				return 0;
		}
	}
	return 0;
}

int validatePath(struct gameinfo *boardinfo)
{
	int winamount = boardinfo->winamount;
	for (int index = boardinfo->ncols * boardinfo->nrows - 1; index > -1; index--)
	{
		if (boardinfo->board[index] == 0)
			continue;

		/* Only check 4 directions because checking 8 would be arbitray since
		 * it would be checking the same peices going forward and backwards
		 * if it wasnt a win */
		if (checkHorizontalWin(boardinfo, index) >= (winamount - 1))
			return boardinfo->board[index];
		if (checkVerticalWin(boardinfo, index) >= (winamount - 1))
			return boardinfo->board[index];
		if (checkUpDiagonalWin(boardinfo, index) >= (winamount - 1))
			return boardinfo->board[index];
		if (checkDownDiagonalWin(boardinfo, index) >= (winamount - 1))
			return boardinfo->board[index];
	}

	return 0;
}

int dfs(struct gameinfo *boardinfo, int index, int solution)
{
	struct queue *searchQueue = malloc(sizeof(struct queue));
	struct queue *depthQueue = malloc(sizeof(struct queue));
	int visited[boardinfo->nrows * boardinfo->ncols];
	int depth = 0;
	int temp = 0;
	int max = -1;

	for (int i = 0; i < boardinfo->nrows * boardinfo->ncols; i++)
		visited[i] = 0;

	searchQueue->stack1 = NULL;
	searchQueue->stack2 = NULL;
	depthQueue->stack1 = NULL;
	depthQueue->stack2 = NULL;

	enqueue(searchQueue, index);
	enqueue(depthQueue, depth);

	while ((searchQueue->stack1 != NULL || searchQueue->stack2 != NULL) && depth < boardinfo->winamount + 1)
	{
		temp = dequeue(searchQueue);
		depth = dequeue(depthQueue);
		visited[temp] = 1;
		if (depth > max)
			max = depth;
		int test;

		test = temp + 1;
		if (test < boardinfo->ncols * boardinfo->nrows)
		{
			if (boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - 1;
		if (test > -1)
		{
			if (boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - boardinfo->ncols;
		if (test > -1)
		{
			if (boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - boardinfo->ncols + 1;
		if (test > -1)
		{
			if (boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - boardinfo->ncols - 1;
		if (test > -1)
		{
			if (boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		if (temp == solution)
		{
			free(depthQueue);
			free(searchQueue);
			return (boardinfo->winamount);
		}
	}
	free(depthQueue);
	free(searchQueue);
	return max;
}

int checkWin(struct gameinfo *boardinfo)
{
	int index = boardinfo->ncols * boardinfo->nrows - 1;
	for (; index > -1; index--)
	{
		if (boardinfo->board[index] == 0)
			continue;
		if ((((index + boardinfo->winamount) % boardinfo->ncols) >= boardinfo->winamount) || (((index + boardinfo->winamount) % boardinfo->ncols) == 0))
			if (dfs(boardinfo, index, index + boardinfo->winamount - 1) >= 1 /*boardinfo->winamount*/)
				return boardinfo->board[index];
		if (index - (boardinfo->ncols * (boardinfo->winamount - 1)) > -1)
			if (dfs(boardinfo, index, index - (boardinfo->ncols * (boardinfo->winamount - 1))) >= 1 /*boardinfo->winamount*/)
				return boardinfo->board[index];
		if (index - (((boardinfo->winamount - 2) * boardinfo->ncols) + (boardinfo->winamount)) > -1)
			if (dfs(boardinfo, index, (index - (((boardinfo->winamount - 2) * boardinfo->ncols) + (boardinfo->winamount)))) >= 1 /*boardinfo->winamount*/)
				return boardinfo->board[index];
		if (index + (boardinfo->winamount - 1 * boardinfo->ncols) + boardinfo->winamount - 1 < boardinfo->nrows * boardinfo->ncols)
			if (dfs(boardinfo, index, (index - (((boardinfo->winamount) * boardinfo->ncols) - (boardinfo->winamount)))) >= 1 /*boardinfo->winamount*/)
				return boardinfo->board[index];
	}
	return 0;
}

void clearScreen()
{
	if (DEBUG == 0)
		wprintw(win, "\n");
	else
		wclear(win);
}

int player(struct gameinfo *boardinfo)
{
	int firstplayer = rand() % 2 + 1;
	int secondplayer = firstplayer == 1 ? 2 : 1;
	int moveIndex = 0, playCount = 0;

	wprintw(win, "Player %d will go first.\n", firstplayer);
	wprintw(win, "Type the number of the column that you want to play in\n");
	while (playCount < boardinfo->ncols * boardinfo->nrows)
	{
		clearScreen();
		printBoard(boardinfo);
		wprintw(win, "Player %d move > ", firstplayer);
		int test = wscanw(win, "%d", &moveIndex);
		while (test != 1)
		{
			wprintw(win, "Not a Number\nPlease enter a number >");
			test = wscanw(win, "%d", &moveIndex);
		}
		while (checkAvailable(boardinfo, moveIndex - 1) == 0)
		{
			wprintw(win, "That Place is not available to playing");
			wprintw(win, "\nPlayer %d move >", firstplayer);
			test = wscanw(win, "%d", &moveIndex);
			while (test != 1)
			{
				wprintw(win, "Not a Number\nPlease enter a number >");
				test = wscanw(win, "%d", &moveIndex);
			}
		}
		addPiece(boardinfo, moveIndex - 1, firstplayer);
		int winner = validatePath(boardinfo);
		if (winner != 0)
			return winner;

		playCount += 1;

		clearScreen();
		printBoard(boardinfo);
		wprintw(win, "Player %d move > ", secondplayer);
		test = wscanw(win, "%d", &moveIndex);
		while (test != 1)
		{
			wprintw(win, "Not a number\nEnter a number >");
			test = wscanw(win, "%d", &moveIndex);
		}
		while (checkAvailable(boardinfo, moveIndex - 1) == 0)
		{
			wprintw(win, "That place is not available try somewhere else >");
			wprintw(win, "\nPlayer %d move > ", secondplayer);
			test = wscanw(win, "%d", &moveIndex);
			while (test != 1)
			{
				wprintw(win, "Not a number\nPlease eneter a number > ");
				test = wscanw(win, "%d", &moveIndex);
			}
		}
		addPiece(boardinfo, moveIndex - 1, secondplayer);
		winner = validatePath(boardinfo);
		if (winner != 0)
			return winner;
		playCount += 1;
	}
	return 0;
}

int easyMode(struct gameinfo *boardinfo)
{
	int placement = rand() % boardinfo->ncols;
	while (checkAvailable(boardinfo, placement) == 0)
		placement = rand() % boardinfo->ncols;
	return placement;
}

int hardMode(struct gameinfo *boardinfo)
{
	int highest[boardinfo->ncols * boardinfo->nrows - 1];
	int index = boardinfo->ncols * boardinfo->nrows - 1;
	for (int i = 0; i < boardinfo->ncols * boardinfo->nrows; i++)
		highest[i] = 0;

	for (; index > -1; index--)
	{
		if (boardinfo->board[index] == 0)
			continue;
		if ((((index + boardinfo->winamount) % boardinfo->ncols) >= boardinfo->winamount) ||
			(((index + boardinfo->winamount) % boardinfo->ncols) == 0))
			highest[index] = dfs(boardinfo, index, index + boardinfo->winamount - 1);

		if (index - (boardinfo->ncols * (boardinfo->winamount - 1)) > -1)
			highest[index] = dfs(boardinfo, index, index - (boardinfo->ncols * (boardinfo->winamount - 1)));

		if (index - (((boardinfo->winamount - 2) * boardinfo->ncols) + (boardinfo->winamount)) > -1)
			highest[index] = dfs(boardinfo, index, (index - (((boardinfo->winamount - 2) * boardinfo->ncols) + (boardinfo->winamount))));

		if (index - (((boardinfo->winamount) * boardinfo->ncols) - (boardinfo->winamount)) > -1)
			highest[index] = dfs(boardinfo, index, (index - (((boardinfo->winamount) * boardinfo->ncols) - (boardinfo->winamount))));
	}

	int k = 1;
	while (k < boardinfo->nrows * boardinfo->ncols)
	{
		int x = highest[k];
		int j = k - 1;
		while (j >= 0 && highest[j] < x)
		{
			highest[j + 1] = highest[j];
			j = j - 1;
		}
		highest[j + 1] = x;
		k = k + 1;
	}

	int temp = highest[0];
	int highestIndex = 0;
	while (checkAvailable(boardinfo, temp) == 0)
	{
		highestIndex++;
		temp = highest[highestIndex];
	}
	return temp % boardinfo->ncols;
}

int computer(struct gameinfo *boardinfo)
{
	char mode[25] = {'\0'};
	int imode = 0;
	int playCounter = 0, playerwin = 0, add = 0;
	wprintw(win, "Hardness (easy, hard, impossible): ");
	wrefresh(win);
	wscanw(win, "%s", mode);

	while (strcmp(mode, "easy") != 0 &&
		   strcmp(mode, "hard") != 0 &&
		   strcmp(mode, "impossible") != 0)
	{
		wprintw(win, "Not an option\n");
		wrefresh(win);
		wscanw(win, "%s", mode);
	}
	if (strcmp(mode, "easy") == 0)
		imode = 0;
	else if (strcmp(mode, "hard") == 0)
		imode = 1;
	else if (strcmp(mode, "impossible") == 0)
		imode = 2;

	while (playCounter < (boardinfo->nrows * boardinfo->ncols))
	{
		clearScreen();
		printBoard(boardinfo);
		do
		{
			wprintw(win, "Column to place peice in: ");
			wrefresh(win);
			int test = wscanw(win, "%d", &add);
			while (test != 1)
			{
				wprintw(win, "Error not a number, please input a number: ");
				test = wscanw(win, "%d", &add);
			}
		} while (addPiece(boardinfo, add - 1, 1) == 0);

		playerwin = validatePath(boardinfo);
		if (playerwin != 0)
			return playerwin;

		wprintw(win, "Computer is moving...\n");
		wrefresh(win);
		playCounter++;

		switch (imode)
		{
		case 0:
			addPiece(boardinfo, easyMode(boardinfo), 2);
			playerwin = validatePath(boardinfo);
			if (playerwin != 0)
				return playerwin;
			playCounter++;
			break;
		case 1:
			addPiece(boardinfo, hardMode(boardinfo), 2);
			playerwin = validatePath(boardinfo);
			if (playerwin != 0)
				return playerwin;
			playCounter++;
			break;
		case 2:
			addPiece(boardinfo, easyMode(boardinfo), 2);
			addPiece(boardinfo, hardMode(boardinfo), 2);
			playerwin = validatePath(boardinfo);
			if (playerwin != 0)
				return playerwin;
			playCounter += 2;
			break;
		}
	}
	return 0;
}

void printMenu()
{
	wprintw(win, "game -> lets you choose to play a game between a person and a computer\n");
	wprintw(win, "settings -> lets you changes game settings such as board size, and amount to win\n");
	wprintw(win, "clear -> clears the screen\n");
	wprintw(win, "help -> displays this help menu, also works in all the other sub menues\n");
	wprintw(win, "quit -> quits the game\n");
	wrefresh(win);
}

struct gameinfo changeBoardSize(struct gameinfo *boardinfo)
{
	struct gameinfo newinfo;

	newinfo.ncols = boardinfo->ncols;
	newinfo.nrows = boardinfo->nrows;
	newinfo.winamount = boardinfo->winamount;

	free(boardinfo->board);
	newinfo.board = malloc((boardinfo->ncols * boardinfo->nrows) * sizeof(int));

	return newinfo;
}

void settings(struct gameinfo *boardinfo)
{
	char setting[25] = {'\0'};
	int newsetting = 0;

	clearScreen();
	while (strcmp(setting, "done") != 0)
	{
		setting[0] = '\0';
		wprintw(win, "setting: ");
		wrefresh(win);
		wscanw(win, "%s", setting);
		if (strcmp(setting, "width") == 0)
		{
			do
			{
				newsetting = boardinfo->ncols;
				wprintw(win, "Current Width: %d\nNew Width: ", boardinfo->ncols);
				wrefresh(win);
				int test = wscanw(win, "%d", &newsetting);
				while (test != 1)
				{
					wprintw(win, "That is not a valid number, please input a non-zero positive integer: ");
					test = wscanw(win, "%d", &newsetting);
				}
			} while (newsetting <= 0);
			boardinfo->ncols = newsetting;
			*boardinfo = changeBoardSize(boardinfo);
			clearBoard(boardinfo);
		}
		else if (strcmp(setting, "height") == 0)
		{
			do
			{
				newsetting = boardinfo->nrows;
				wprintw(win, "Current Height: %d\nNew Height: ", boardinfo->nrows);
				wrefresh(win);
				int test = wscanw(win, "%d", &newsetting);
				while (test != 1)
				{
					wprintw(win, "That is not a valid number, please input a non-zero positive integer: ");
					test = wscanw(win, "%d", &newsetting);
				}
			} while (newsetting <= 0);
			boardinfo->nrows = newsetting;
			*boardinfo = changeBoardSize(boardinfo);
			clearBoard(boardinfo);
		}
		else if (strcmp(setting, "amount") == 0)
		{
			do
			{
				newsetting = boardinfo->winamount;
				wprintw(win, "Current Amount to win: %d\nNew Amount to win: ", boardinfo->winamount);
				wrefresh(win);
				int test = wscanw(win, "%d", &newsetting);
				while (test != 1)
				{
					wprintw(win, "That is not a valid number, please input a non-zero positive integer: ");
					test = wscanw(win, "%d", &newsetting);
				}
			} while (newsetting < 0);
			boardinfo->winamount = newsetting;
		}
		else if (strcmp(setting, "clear") == 0)
		{
			clearScreen();
		}
		else if (strcmp(setting, "print") == 0)
		{
			printBoard(boardinfo);
			wprintw(win, "width: %d\n", boardinfo->ncols);
			wprintw(win, "height: %d\n", boardinfo->nrows);
			wprintw(win, "amount to win: %d\n", boardinfo->winamount);
			wrefresh(win);
		}
		else if (strcmp(setting, "help") == 0)
		{
			wprintw(win, "Current commands are: \n");
			wprintw(win, "width -> sets the new width of the game board\n\thas to be above 0\n");
			wprintw(win, "height -> sets the new height of the game board\n\thas to be above 0\n");
			wprintw(win, "amount -> changes the amount you need to win\n\thas to be above 0\n");
			wprintw(win, "clear -> clears the screen");
			wprintw(win, "print -> prints current board size\n");
			wprintw(win, "done -> saves settings and returns to main menu\n");
			wprintw(win, "help -> prints the message\n");
			wrefresh(win);
		}
		else
		{
			wprintw(win, "ERROR: '%s' is not a command try 'help'\n", setting);
			wrefresh(win);
		}
	}
}
