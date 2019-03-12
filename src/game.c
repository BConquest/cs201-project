#include "../include/game.h"

void printBoard(struct gameinfo *boardinfo)
{
	int index = 0;
	for(; index < boardinfo->nrows*boardinfo->ncols; index++)
	{
		if(index % boardinfo->ncols == 0)
			printf("\n");
		if(boardinfo->board[index] == 0)
			printf("_ ");
		else if(boardinfo->board[index] == 1)
			printf("O ");
		else if(boardinfo->board[index] == 2)
			printf("X ");
		else
			printf("E ");
	}
	printf("\n");
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
		printf("%d ", max);
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
	printf("\n");
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
	printf("\n");
	//system("clear");
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
                        printf("player %d move > ", i);
                        scanf("%d", &add);
                        while(addPiece(boardinfo, add-1, i) == 0)
                        {
                                printBoard(boardinfo);
                                puts("Can't add piece there > ");
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
			if(dfs(boardinfo, index, index+boardinfo->winamount-1) >= boardinfo->winamount)
				highest[index] = dfs(boardinfo, index, index+boardinfo->winamount-1);
		
		if(index-(boardinfo->ncols*(boardinfo->winamount - 1)) > -1)
			if(dfs(boardinfo, index, index-(boardinfo->ncols*(boardinfo->winamount-1))) >= boardinfo->winamount)
				highest[index] = dfs(boardinfo, index, index-(boardinfo->ncols*(boardinfo->winamount-1)));
		
		if(index-(((boardinfo->winamount-2)*boardinfo->ncols)+(boardinfo->winamount)) > -1)
			if(dfs(boardinfo, index, (index-(((boardinfo->winamount-2)*boardinfo->ncols)+(boardinfo->winamount))))
		           >= boardinfo->winamount)
				highest[index] = dfs(boardinfo, index, (index-(((boardinfo->winamount-2)*boardinfo->ncols)+(boardinfo->winamount))));

		if(index-(((boardinfo->winamount)*boardinfo->ncols)-(boardinfo->winamount)) > -1)
			if(dfs(boardinfo, index, (index-(((boardinfo->winamount)*boardinfo->ncols)-(boardinfo->winamount))))
			   >= boardinfo->winamount)
				highest[index] = dfs(boardinfo, index, (index-(((boardinfo->winamount)*boardinfo->ncols)-(boardinfo->winamount))));
	}
	
	int k = 1;
	while (k < boardinfo->nrows*boardinfo->ncols)
	{
		int x = highest[k];
		int j = k - 1;
		while (j >= 0 && highest[j] > x)
		{
			highest[j+1] = highest[j];
			j = j -1;
		}
		highest[j+1] = x;
		k = k + 1;
	}

	for(int i = 0; i <boardinfo->ncols*boardinfo->nrows; i++)
		printf("%d ", highest[i]);

	return easyMode(boardinfo);
}

int computer(struct gameinfo *boardinfo)
{
	char mode[25] = {'\0'};
        int playCounter = 0, playerwin = 0, add = 0;
	printf("Hardness (easy, hard, impossible): ");
	scanf("%s", mode);

        while(playCounter < (boardinfo->nrows * boardinfo->ncols))
        {
                clearScreen();
		printBoard(boardinfo);
		do
		{
			printf("Column to place peice in: ");
			scanf("%d", &add);
		} while(addPiece(boardinfo, add-1, 1) == 0);
		printf("Computer is moving...\n");
		clearScreen();
		printf("Computer moved\n");
		if (strcmp(mode, "easy") == 0)
		{
			addPiece(boardinfo, easyMode(boardinfo), 2);
			playCounter++;
		}
		if (strcmp(mode, "hard") == 0)
		{
			addPiece(boardinfo, hardMode(boardinfo), 2);
			playCounter++;
		}
		if (strcmp(mode, "impossible") == 0)
		{
			addPiece(boardinfo, hardMode(boardinfo), 2);
			addPiece(boardinfo, hardMode(boardinfo), 2);
			playCounter += 2;
		}
		printBoard(boardinfo);
		playerwin = checkWin(boardinfo);
		if(playerwin != 0)
			return playerwin;
        }
        return 0;
}

void printMenu()
{
        printf("game -> lets you choose to play a game between a person and a computer\n");
        printf("settings -> lets you changes game settings such as board size, and amount to win\n");
        printf("clear -> clears the screen\n");
        printf("help -> displays this help menu, also works in all the other sub menues\n");
        printf("quit -> quits the game\n");
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
		printf("setting: ");
                scanf("%s", setting);
                if(strcmp(setting, "width") == 0)
                {
                        do
                        {
                                newsetting = boardinfo->ncols;
                                printf("Current Width: %d\nNew Width: ", boardinfo->ncols);
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
				printf("Current Height: %d\nNew Height: ", boardinfo->nrows);
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
				printf("Current Amount to win: %d\nNew Amount to win: ", boardinfo->winamount);
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
                        printf("width: %d\n", boardinfo->ncols);
                        printf("height: %d\n", boardinfo->nrows);
			printf("amount to win: %d\n", boardinfo->winamount);
                }
                else if(strcmp(setting, "help") == 0)
                {
                        printf("Current commands are: \n");
                        printf("width -> sets the new width of the game board\n\thas to be above 0\n");
                        printf("height -> sets the new height of the game board\n\thas to be above 0\n");
                        printf("amount -> changes the amount you need to win\n\thas to be above 0\n");
                        printf("clear -> clears the screen");
                        printf("print -> prints current board size\n");
                        printf("done -> saves settings and returns to main menu\n");
                        printf("help -> prints the message\n");
                }
        }
}
