#include "../include/game.h"

void initGameInfo(struct gameinfo *boardinfo, struct scoreboard *scores)
{
	boardinfo->ncols = 7;
	boardinfo->nrows = 6;

	boardinfo->board = malloc((boardinfo->ncols * boardinfo->nrows) * sizeof(int));
	boardinfo->winamount = 4;

	scores->playervplayer = 0;
	scores->player1wins = 0;
	scores->playerdraws = 0;
	scores->playervcomputer = 0;
	scores->computerwins = 0;
	scores->computerdraws = 0;
}

int addPiece(struct gameinfo *boardinfo, int col, int colour)
{
	/* Checks to see if that is a valid place to place */
	if (col >= boardinfo->ncols || col < 0)
		return 0;

	/* Calculates the current index bassed on a column number */
	int index = (boardinfo->nrows - 1) * boardinfo->ncols + col;

	/* Loops through the column to finding a free space bottom up to save time*/
	for (; index > (boardinfo->ncols - 1); index -= boardinfo->ncols)
		if (boardinfo->board[index] == 0)
			break;

	/* if last space is filled returns error else places piece */
	if (index < boardinfo->ncols && boardinfo->board[index] != 0)
		return 0;
	else
		boardinfo->board[index] = colour;

	return 1;
}

int checkAvailable(struct gameinfo *boardinfo, int col)
{
	/* Checks to make sure that j is not out of bounds */
	if (col >= boardinfo->ncols || col < 0)
		return 0;

	int index = (boardinfo->nrows - 1) * boardinfo->ncols + col;

	/* Loops through the column to finding a free space bottom up to save time*/
	for (; index > (boardinfo->ncols - 1); index -= boardinfo->ncols)
		if (boardinfo->board[index] == 0)
			break;

	/* When the index is at the top of the line checks to see if that spot is filled */
	if (index < boardinfo->ncols && boardinfo->board[index] != 0)
		return 0;

	return 1;
}

int dfs(struct gameinfo *boardinfo, int index, int color)
{
	//All the Stacks that are used for Depth first search
	struct stackNode *searchStack = NULL;
	push(&searchStack, index);
	struct stackNode *depthStack = NULL;
	push(&depthStack, 0);
	// Stores the direction so that the depth doesnt just get insanely high
	struct stackNode *directionStack = NULL;
	push(&directionStack, 0);

	int boardarea = boardinfo->nrows * boardinfo->ncols;

	int maxdepth = 0;

	//Array to hold if cell has been visited or not
	int *visited;
	visited = malloc(boardarea * sizeof(int));
	for (int i = 0; i < boardarea; i++)
		visited[i] = 0;

	while (!isEmpty(searchStack))
	{
		int currSearch = pop(&searchStack);
		int depth = pop(&depthStack);
		int dir = pop(&directionStack);
		if (visited[currSearch] == 0)
		{
			if (depth > maxdepth)
				maxdepth = depth;
			if (depth == boardinfo->winamount)
			{
				/* Make sure that there are no memory leaks */
				while (!isEmpty(searchStack))
				{
					pop(&searchStack);
				}
				while (!isEmpty(depthStack))
				{
					pop(&depthStack);
				}
				while (!isEmpty(directionStack))
				{
					pop(&directionStack);
				}
				free(visited);
				return boardinfo->winamount;
			}

			visited[currSearch] = 1;
			int test = 0;

			/* Gets Neighbor to the right of the current cell*/
			test = currSearch + 1;
			if (test < boardarea && (currSearch % boardinfo->ncols != boardinfo->ncols - 1))
			{
				if (boardinfo->board[test] == color)
				{
					push(&searchStack, test);
					push(&directionStack, 1);
					if (dir == 1)
						push(&depthStack, depth + 1);
					else
						push(&depthStack, 1);
				}
			}
			/* Gets Neighbor to the left of the current cell*/
			test = currSearch - 1;
			if (test > -1 && (currSearch % boardinfo->ncols != 0))
			{
				if (boardinfo->board[test] == color)
				{
					push(&searchStack, test);
					push(&directionStack, 2);
					if (dir == 2)
						push(&depthStack, depth + 1);
					else
						push(&depthStack, 1);
				}
			}

			/* Gets neighbor  on the bottom of the current cell */
			test = currSearch + (boardinfo->nrows + 1);
			if (test < boardarea)
			{
				if (boardinfo->board[test] == color)
				{
					push(&searchStack, test);
					push(&directionStack, 3);
					if (dir == 3)
						push(&depthStack, depth + 1);
					else
						push(&depthStack, 1);
				}
			}
			/* Gets the neighbor to the bottom right of the currect cell */
			test = currSearch + boardinfo->nrows + 2;
			if (test < boardarea && (currSearch % boardinfo->ncols) != boardinfo->ncols - 1)
			{
				if (boardinfo->board[test] == color)
				{
					push(&searchStack, test);
					push(&directionStack, 4);
					if (dir == 4)
						push(&depthStack, depth + 1);
					else
						push(&depthStack, 1);
				}
			}
			/* Gets neighbor to the bottom left of the current cell */
			test = currSearch + boardinfo->ncols - 1;
			if (test < boardarea && (currSearch % boardinfo->ncols != 0))
			{
				if (boardinfo->board[test] == color)
				{
					push(&searchStack, test);
					push(&directionStack, 5);
					if (dir == 5)
						push(&depthStack, depth + 1);
					else
						push(&depthStack, 1);
				}
			}
			/* Gets neighbor to the top left of the current cell */
			test = currSearch - boardinfo->ncols - 1;
			if (test > -1 && (currSearch % boardinfo->ncols != 0))
			{
				if (boardinfo->board[test] == color)
				{
					push(&searchStack, test);
					push(&directionStack, 6);
					if (dir == 6)
						push(&depthStack, depth + 1);
					else
						push(&depthStack, 1);
				}
			}
			/* Gets neighbor to the top right of the current cell */
			test = currSearch - (boardinfo->ncols - 1);
			if (test > -1 && (currSearch % boardinfo->ncols != 0))
			{
				if (boardinfo->board[test] == color)
				{
					push(&searchStack, test);
					push(&directionStack, 7);
					if (dir == 7)
						push(&depthStack, depth + 1);
					else
						push(&depthStack, 1);
				}
			}
		}
	}
	/* Make sure that there are no memory leaks */
	while (!isEmpty(searchStack))
	{
		pop(&searchStack);
	}
	while (!isEmpty(depthStack))
	{
		pop(&depthStack);
	}
	while (!isEmpty(directionStack))
	{
		pop(&directionStack);
	}
	free(visited);
	return maxdepth;
}

int player(struct gameinfo *boardinfo)
{
	int firstplayer = rand() % 2 + 1;
	int secondplayer = firstplayer == 1 ? 2 : 1;
	int moveIndex = 0, playCount = 0;

	printf("Player %d will go first.\n", firstplayer);
	printf("Type the number of the column that you want to play in\n");
	while (playCount < boardinfo->ncols * boardinfo->nrows)
	{
		clearScreen();
		printBoard(boardinfo);
		printf("Player %d move > ", firstplayer);
		getchar();
		int test = scanf("%d", &moveIndex);
		while (test != 1)
		{
			printf("Not a Number\nPlease enter a number >");
			getchar();
			test = scanf("%d", &moveIndex);
		}
		while (checkAvailable(boardinfo, moveIndex - 1) == 0)
		{
			printf("That Place is not available to playing");
			printf("\nPlayer %d move >", firstplayer);
			getchar();
			test = scanf("%d", &moveIndex);
			while (test != 1)
			{
				printf("Not a Number\nPlease enter a number >");
				getchar();
				test = scanf("%d", &moveIndex);
			}
		}
		addPiece(boardinfo, moveIndex - 1, firstplayer);
		int winner = checkWin(boardinfo);
		if (winner != 0)
			return winner;

		playCount += 1;
		if (playCount >= boardinfo->ncols * boardinfo->nrows)
			return 0;

		clearScreen();
		printBoard(boardinfo);
		printf("Player %d move > ", secondplayer);
		getchar();
		test = scanf("%d", &moveIndex);
		while (test != 1)
		{
			printf("Not a number\nEnter a number >");
			getchar();
			test = scanf("%d", &moveIndex);
		}
		while (checkAvailable(boardinfo, moveIndex - 1) == 0)
		{
			printf("That place is not available try somewhere else >");
			printf("\nPlayer %d move > ", secondplayer);
			getchar();
			test = scanf("%d", &moveIndex);
			while (test != 1)
			{
				printf("Not a number\nPlease eneter a number > ");
				getchar();
				test = scanf("%d", &moveIndex);
			}
		}
		addPiece(boardinfo, moveIndex - 1, secondplayer);
		winner = checkWin(boardinfo);
		if (winner != 0)
			return winner;
		playCount += 1;
	}
	return 0;
}

int easyMode(struct gameinfo *boardinfo)
{
	/* Randomly chooses a column and checks if it is available */
	int placement = rand() % boardinfo->ncols;
	while (checkAvailable(boardinfo, placement) == 0)
		placement = rand() % boardinfo->ncols;
	return placement;
}

int hardMode(struct gameinfo *boardinfo)
{
	int positions[boardinfo->ncols];
	int cols[boardinfo->ncols];

	for (int i = 0; i < boardinfo->ncols; i++)
		positions[i] = 0;

	for (int i = 0; i < boardinfo->ncols; i++)
	{
		if (computer_stats == 1)
			printf("finding available space in column %d\n", i);
		int index = (boardinfo->nrows - 1) * boardinfo->ncols + i;
		int temp = 0;
		for (; index > (boardinfo->ncols - 1); index -= boardinfo->ncols)
		{
			if (boardinfo->board[index] == 0)
				break;
		}
		if (computer_stats == 1)
			printf("Finding best move for computer\n");
			
		temp = dfs(boardinfo, index, 2);
		if (temp > positions[i])
			positions[i] = temp;

		if (computer_stats == 1)
			printf("Seeing if player can do better\n");
		temp = dfs(boardinfo, index, 1);
		if (temp > positions[i])
			positions[i] = temp;
	}

	for (int i = 0; i < boardinfo->ncols; i++)
	{
		cols[i] = i;
	}
	if (computer_stats == 1)
		printf("Sorting the moves\n");
	quickSort(positions, cols, 0, boardinfo->ncols - 1);
	/*Quick sort the array so that finding the b est summed move is easist. */
	//for (int i = boardinfo->ncols - 1; i > -1; i--)
	//{
	//	printf("%d(%d)->", cols[i], positions[i]);
	//}
	//printf("\n");
	if (computer_stats == 1)
		printf("Finding best Move\n");
	for (int i = boardinfo->ncols - 1; i > -1; i--)
	{
		if (checkAvailable(boardinfo, cols[i]) == 1)
		{
			return cols[i];
		}
	}
	printf("ERROR: HARDMODE -> failed\n");
	return easyMode(boardinfo);
}

int computer(struct gameinfo *boardinfo)
{
	char mode[25] = {'\0'};
	int imode = 0;
	int playCounter = 0, playerwin = 0, add = 0;
	printf("Hardness (easy, hard, impossible): ");
	getchar();
	scanf("%s", mode);

	while (strncmp(mode, "easy", 25) != 0 &&
		   strncmp(mode, "hard", 25) != 0 &&
		   strncmp(mode, "impossible", 25) != 0)
	{
		printf("Not an option\n");
		getchar();
		scanf("%s", mode);
	}
	if (strncmp(mode, "easy", 25) == 0)
		imode = 0;
	else if (strncmp(mode, "hard", 25) == 0)
		imode = 1;
	else if (strncmp(mode, "impossible", 25) == 0)
		imode = 2;

	while (playCounter < (boardinfo->nrows * boardinfo->ncols))
	{
		clearScreen();
		printBoard(boardinfo);
		do
		{
			printf("Column to place piece in: ");
			getchar();
			int test = scanf("%d", &add);
			while (test != 1)
			{
				printf("Error not a number, please input a number: ");
				getchar();
				test = scanf("%d", &add);
			}
		} while (addPiece(boardinfo, add - 1, 1) == 0);

		playerwin = checkWin(boardinfo);
		if (playerwin != 0)
			return playerwin;

		playCounter++;

		switch (imode)
		{
		case 0:
			addPiece(boardinfo, easyMode(boardinfo), 2);
			playerwin = checkWin(boardinfo);
			if (playerwin != 0)
				return playerwin;
			playCounter++;
			break;
		case 1:
			addPiece(boardinfo, hardMode(boardinfo), 2);
			playerwin = checkWin(boardinfo);
			if (playerwin != 0)
				return playerwin;
			playCounter++;
			break;
		case 2:
			addPiece(boardinfo, easyMode(boardinfo), 2);
			addPiece(boardinfo, hardMode(boardinfo), 2);
			playerwin = checkWin(boardinfo);
			if (playerwin != 0)
				return playerwin;
			playCounter += 2;
			break;
		}
	}
	return 0;
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