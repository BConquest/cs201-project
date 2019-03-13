#include "../include/game.h"

void printBoard(struct gameinfo *boardinfo)
{
	int index = 0;

	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);

	for(; index < boardinfo->nrows*boardinfo->ncols; index++)
	{
		if(index % boardinfo->ncols == 0)
			printw("\n");

		if(boardinfo->board[index] == 0)
		{
			attron(COLOR_PAIR(3));
			printw("_ ");
			attroff(COLOR_PAIR(3));
		}
		else if(boardinfo->board[index] == 1)
		{
			attron(COLOR_PAIR(1));
			printw("O ");
			attroff(COLOR_PAIR(1));
		}
		else if(boardinfo->board[index] == 2)
		{
			attron(COLOR_PAIR(2));
			printw("X ");
			attroff(COLOR_PAIR(2));
		}
		else
			printw("E ");
	}
	printw("\n");
	refresh();
}

void clearBoard(struct gameinfo *boardinfo)
{
	int index = 0;
	for(; index < boardinfo->nrows*boardinfo->ncols; index++)
		boardinfo->board[index] = 0;
}

int addPiece(struct gameinfo *boardinfo, int j, int colour)
{
	int index = (boardinfo->nrows-1)*boardinfo->ncols + j;

	
	if(j >= boardinfo->ncols || j < 0)
		return 0;

	for(;index > (boardinfo->ncols-1); index-=boardinfo->ncols)
		if(boardinfo->board[index] == 0)
			break;

	if(index < boardinfo->ncols && boardinfo->board[index] != 0)
		return 0;
	else
		boardinfo->board[index] = colour;

	return 1;
}

int checkAvailable(struct gameinfo *boardinfo, int j)
{
	int index = (boardinfo->nrows-1)*boardinfo->ncols + j;

	
	if(j >= boardinfo->ncols || j < 0)
		return 0;

	for(;index > (boardinfo->ncols-1); index-=boardinfo->ncols)
		if(boardinfo->board[index] == 0)
			break;

	if(index < boardinfo->ncols && boardinfo->board[index] != 0)
		return 0;

	return 1;
}

int dfs(struct gameinfo *boardinfo, int index, int solution)
{
	struct queue *searchQueue = malloc(sizeof(struct queue));
	struct queue *depthQueue = malloc(sizeof(struct queue));
	int visited[boardinfo->nrows*boardinfo->ncols];
	int depth = 0;
	int temp = 0;
	int max = -1;

	for(int i = 0; i < boardinfo->nrows*boardinfo->ncols; i++)
		visited[i] = 0;

	searchQueue->stack1 = NULL;
	searchQueue->stack2 = NULL;
	depthQueue->stack1 = NULL;
	depthQueue->stack2 = NULL;

	enqueue(searchQueue, index);
	enqueue(depthQueue, depth);

	while((searchQueue->stack1 != NULL || searchQueue->stack2 != NULL) && depth < boardinfo->winamount + 1)
	{
		temp = dequeue(searchQueue);
		depth = dequeue(depthQueue);
		visited[temp] = 1;
		if(depth > max)
			max = depth;
		int test;
		
		test = temp + 1;
		if(test < boardinfo->ncols*boardinfo->nrows)
		{
			if(boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth+1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - boardinfo->ncols;
		if(test > -1)
		{
			if(boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth+1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - boardinfo->ncols + 1;
		if(test > -1)
		{
			if(boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth+1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - boardinfo->ncols - 1;
		if(test > -1)
		{
			if(boardinfo->board[test] == boardinfo->board[index] && (visited[test] != 1))
			{
				enqueue(depthQueue, depth+1);
				enqueue(searchQueue, test);
			}
		}
		
		if(temp == solution)
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
	int index = boardinfo->ncols*boardinfo->nrows - 1;
	for(; index > -1; index--)
	{
		if(boardinfo->board[index] == 0)
			continue;
		if((((index+boardinfo->winamount)%boardinfo->ncols) >= boardinfo->winamount) ||
		   (((index+boardinfo->winamount)%boardinfo->ncols) == 0))
			if(dfs(boardinfo, index, index+boardinfo->winamount-1) >= boardinfo->winamount)
				return boardinfo->board[index];
		
		if(index-(boardinfo->ncols*(boardinfo->winamount - 1)) > -1)
			if(dfs(boardinfo, index, index-(boardinfo->ncols*(boardinfo->winamount-1))) >= boardinfo->winamount)
				return boardinfo->board[index];
		
		if(index-(((boardinfo->winamount-2)*boardinfo->ncols)+(boardinfo->winamount)) > -1)
			if(dfs(boardinfo, index, (index-(((boardinfo->winamount-2)*boardinfo->ncols)+(boardinfo->winamount))))
		           >= boardinfo->winamount)
				return boardinfo->board[index];

		if(index-(((boardinfo->winamount)*boardinfo->ncols)-(boardinfo->winamount)) > -1)
			if(dfs(boardinfo, index, (index-(((boardinfo->winamount)*boardinfo->ncols)-(boardinfo->winamount))))
			   >= boardinfo->winamount)
				return boardinfo->board[index];
	}
	return 0;
}

void clearScreen()
{
	clear();
}

int player(struct gameinfo *boardinfo)
{
        int playCounter = 0, playerwin = 0, add = 0;
        while(playCounter < (boardinfo->nrows * boardinfo->ncols))
        {
                for(int i = 1; i < 3; i++)
                {
                        clearScreen();
                        printBoard(boardinfo);
                        printw("player %d move > ", i);
			refresh();
                        scanf("%d", &add);
                        while(addPiece(boardinfo, add-1, i) == 0)
                        {
                                printBoard(boardinfo);
                                printw("Can't add piece there > ");
				refresh();
                                scanf("%d", &add);
                                clearScreen();
                        }
                        playCounter++;
                        playerwin = checkWin(boardinfo);
                        if(playerwin != 0)
                                return playerwin;
                }
        }
        return 0;
}

int easyMode(struct gameinfo *boardinfo)
{
        return rand() % boardinfo->ncols;
}

int hardMode(struct gameinfo *boardinfo)
{
	int highest[boardinfo->ncols*boardinfo->nrows - 1];
	int index = boardinfo->ncols*boardinfo->nrows - 1;
	for(int i = 0; i <boardinfo->ncols*boardinfo->nrows; i++)
		highest[i] = 0;

	for(; index > -1; index--)
	{
		if(boardinfo->board[index] == 0)
			continue;
		if((((index+boardinfo->winamount)%boardinfo->ncols) >= boardinfo->winamount) ||
		   (((index+boardinfo->winamount)%boardinfo->ncols) == 0))
			highest[index] = dfs(boardinfo, index, index+boardinfo->winamount-1);

		
		if(index-(boardinfo->ncols*(boardinfo->winamount - 1)) > -1)
			highest[index] = dfs(boardinfo, index, index-(boardinfo->ncols*(boardinfo->winamount-1)));
		
		if(index-(((boardinfo->winamount-2)*boardinfo->ncols)+(boardinfo->winamount)) > -1)
			highest[index] = dfs(boardinfo, index, (index-(((boardinfo->winamount-2)*boardinfo->ncols)+(boardinfo->winamount))));

		if(index-(((boardinfo->winamount)*boardinfo->ncols)-(boardinfo->winamount)) > -1)
			highest[index] = dfs(boardinfo, index, (index-(((boardinfo->winamount)*boardinfo->ncols)-(boardinfo->winamount))));
	}
	
	int k = 1;
	while (k < boardinfo->nrows*boardinfo->ncols)
	{
		int x = highest[k];
		int j = k - 1;
		while (j >= 0 && highest[j] < x)
		{
			highest[j+1] = highest[j];
			j = j -1;
		}
		highest[j+1] = x;
		k = k + 1;
	}

	int temp = highest[0];
	int l = 0;
	while(checkAvailable(boardinfo, temp) == 0)
	{
		l++;
		temp = highest[l];
	}
	return temp % boardinfo->ncols;
}

int computer(struct gameinfo *boardinfo)
{
	char mode[25] = {'\0'};
        int playCounter = 0, playerwin = 0, add = 0;
	printw("Hardness (easy, hard, impossible): ");
	refresh();
	scanf("%s", mode);

	while(strcmp(mode, "easy") != 0 &&
	      strcmp(mode, "hard") != 0 &&
	      strcmp(mode, "impossible") != 0)
	      {
		      printw("Not an option\n");
		      refresh();
		      scanf("%s", mode);
	      }
        while(playCounter < (boardinfo->nrows * boardinfo->ncols))
        {
                clearScreen();
		printBoard(boardinfo);
		do
		{
			printw("Column to place peice in: ");
			refresh();
			scanf("%d", &add);
		} while(addPiece(boardinfo, add-1, 1) == 0);
		printw("Computer is moving...\n");
		refresh();
		if (strcmp(mode, "easy") == 0)
		{
			addPiece(boardinfo, easyMode(boardinfo), 2);
			playCounter++;
			playerwin = checkWin(boardinfo);
		}
		if (strcmp(mode, "hard") == 0)
		{
			addPiece(boardinfo, hardMode(boardinfo), 2);
			playCounter++;
			playerwin = checkWin(boardinfo);
		}
		if (strcmp(mode, "impossible") == 0)
		{
			addPiece(boardinfo, hardMode(boardinfo), 2);
			addPiece(boardinfo, easyMode(boardinfo), 2);
			playCounter += 2;
			playerwin = checkWin(boardinfo);
		}
		if(playerwin != 0)
			return playerwin;
		clearScreen();
		printw("Computer moved\n");
		refresh();
		printBoard(boardinfo);
		playerwin = checkWin(boardinfo);
		if(playerwin != 0)
			return playerwin;
        }
        return 0;
}

void printMenu()
{
        printw("game -> lets you choose to play a game between a person and a computer\n");
        printw("settings -> lets you changes game settings such as board size, and amount to win\n");
        printw("clear -> clears the screen\n");
        printw("help -> displays this help menu, also works in all the other sub menues\n");
        printw("quit -> quits the game\n");
	refresh();
}

struct gameinfo changeBoardSize(struct gameinfo *boardinfo)
{
	struct gameinfo newinfo;

	newinfo.ncols = boardinfo->ncols;
	newinfo.nrows = boardinfo->nrows;
	newinfo.winamount = boardinfo->winamount;

	free(boardinfo->board);
	newinfo.board = malloc((boardinfo->ncols*boardinfo->nrows)*sizeof(int));
	
	return newinfo;
}

void settings(struct gameinfo *boardinfo)
{
        char setting[25] = {'\0'};
        int newsetting = 0;

        clearScreen();
        while(strcmp(setting, "done") != 0)
        {
                setting[0] = '\0';
		printw("setting: ");
		refresh();
                scanf("%s", setting);
                if(strcmp(setting, "width") == 0)
                {
                        do
                        {
                                newsetting = boardinfo->ncols;
                                printw("Current Width: %d\nNew Width: ", boardinfo->ncols);
                                refresh();
				scanf("%d", &newsetting);
                        } while(newsetting < 0);
                        boardinfo->ncols = newsetting;
			*boardinfo = changeBoardSize(boardinfo);
                }
                else if(strcmp(setting, "height") == 0)
                {
                        do
                        {
                                newsetting = boardinfo->nrows;
				printw("Current Height: %d\nNew Height: ", boardinfo->nrows);
                                refresh();
				scanf("%d", &newsetting);
                        } while(newsetting < 0);
                        boardinfo->nrows = newsetting;
                        *boardinfo = changeBoardSize(boardinfo);
                }
                else if(strcmp(setting, "amount") == 0)
                {
                        do
                        {
                                newsetting = boardinfo->winamount;
				printw("Current Amount to win: %d\nNew Amount to win: ", boardinfo->winamount);
                                refresh();
				scanf("%d",  &newsetting);
                        } while(newsetting < 0);
                        boardinfo->winamount = newsetting;
                }
                else if(strcmp(setting, "clear") == 0)
                {
                        clearScreen();
                }
                else if(strcmp(setting, "print") == 0)
                {
                        printBoard(boardinfo);
                        printw("width: %d\n", boardinfo->ncols);
                        printw("height: %d\n", boardinfo->nrows);
			printw("amount to win: %d\n", boardinfo->winamount);
			refresh();
		}
                else if(strcmp(setting, "help") == 0)
                {
                        printw("Current commands are: \n");
                        printw("width -> sets the new width of the game board\n\thas to be above 0\n");
                        printw("height -> sets the new height of the game board\n\thas to be above 0\n");
                        printw("amount -> changes the amount you need to win\n\thas to be above 0\n");
                        printw("clear -> clears the screen");
                        printw("print -> prints current board size\n");
                        printw("done -> saves settings and returns to main menu\n");
                        printw("help -> prints the message\n");
			refresh();
	        }
        }
}
