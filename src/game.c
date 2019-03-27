#include "../include/game.h"
//#include "../include/config.h"

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
	int i = 1, count = 0, newIndex = index;
	for (; i <= boardinfo->winamount; i++)
	{
		if (boardinfo->board[newIndex] == boardinfo->board[index])
			count++;
		if (index + i > boardinfo->nrows * boardinfo->ncols)
			return 0;
		else
			newIndex = index + i;
	}
	return count;
}

int checkVerticalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Vertical winning */
	int i = 1, count = 0, newIndex = index;
	for (; i <= boardinfo->winamount; i++)
	{
		if (boardinfo->board[newIndex] == boardinfo->board[index])
			count++;
		if (index - (i * boardinfo->ncols) < (-1 - boardinfo->ncols))
			return 0;
		else
			newIndex = index - (i * boardinfo->ncols);
	}
	return count;
}

int checkRightDiagonalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Up diagonal winning */
	int i = 1, count = 0, newIndex = index;
	for (; i <= boardinfo->winamount; i++)
	{
		if (boardinfo->board[newIndex] == boardinfo->board[index])
			count++;
		if (index - (i * boardinfo->ncols) + i > -1)
			newIndex = index - (i * boardinfo->ncols) + i;
		else
			return 0;
	}
	return count;
}

int checkLeftDiagonalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Down Diagonal winning */
	int i = 1, count = 0, newIndex = index;
	for (; i <= boardinfo->winamount; i++)
	{
		if (boardinfo->board[newIndex] == boardinfo->board[index])
			count++;
		if (index - (i * boardinfo->ncols) - i >= (-1 - boardinfo->ncols))
			newIndex = index - (i * boardinfo->ncols) - i;
		else
			return 0;
	}
	return count;
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

		/* Checking to make sure that it wont go out of bounds or wrap around the board*/
		if ((((index + boardinfo->winamount) % boardinfo->ncols >= boardinfo->winamount || (index + boardinfo->winamount) % boardinfo->ncols == 0)))
		{
			if (checkHorizontalWin(boardinfo, index) >= (winamount))
			{
				return boardinfo->board[index];
			}
		}
		/* Dont wrap around because it will be out of bounds instead of wrapping to bottom */
		if (checkVerticalWin(boardinfo, index) >= (winamount))
		{
			return boardinfo->board[index];
		}

		/* Checkiung to make sure that it wont go out of bounds or wrap around the board*/
		if ((index + boardinfo->winamount) % boardinfo->ncols >= boardinfo->winamount || (index + boardinfo->winamount) % boardinfo->ncols == 0)
		{
			if (checkRightDiagonalWin(boardinfo, index) >= (winamount))
				return boardinfo->board[index];
		}

		/* checking to make sure board wrap around does not happen */
		if (((index - boardinfo->winamount) % boardinfo->ncols) < boardinfo->winamount || (index - boardinfo->winamount) % boardinfo->ncols == (boardinfo->ncols - 1))
		{
			if (checkLeftDiagonalWin(boardinfo, index) >= (winamount))
				return boardinfo->board[index];
		}
	}

	return 0;
}

int bfs(struct gameinfo *boardinfo, int index, int solution, int color)
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

	while ((searchQueue->stack1 != NULL || searchQueue->stack2 != NULL) /*&& depth < boardinfo->winamount + 1*/)
	{
		temp = dequeue(searchQueue);
		depth = dequeue(depthQueue);
		visited[temp] = 1;
		if (depth > max)
			max = depth;
		int test;

		/* Searches to the right */
		test = temp + 1;
		if (test < boardinfo->ncols * boardinfo->nrows)
		{
			if (boardinfo->board[test] == color && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		/* Searches to the right */
		test = temp - 1;
		if (test > -1)
		{
			if (boardinfo->board[test] == color && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		/* Searches top wards */
		test = temp - boardinfo->ncols;
		if (test > -1)
		{
			if (boardinfo->board[test] == color && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - boardinfo->ncols + 1;
		if (test > -1)
		{
			if (boardinfo->board[test] == color && (visited[test] != 1))
			{
				enqueue(depthQueue, depth + 1);
				enqueue(searchQueue, test);
			}
		}

		test = temp - boardinfo->ncols - 1;
		if (test > -1)
		{
			if (boardinfo->board[test] == color && (visited[test] != 1))
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
	printf("%d -> bfs -> %d\n", index, solution);
	return max;
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
		int test = scanf("%d", &moveIndex);
		while (test != 1)
		{
			printf("Not a Number\nPlease enter a number >");
			test = scanf("%d", &moveIndex);
		}
		while (checkAvailable(boardinfo, moveIndex - 1) == 0)
		{
			printf("That Place is not available to playing");
			printf("\nPlayer %d move >", firstplayer);
			test = scanf("%d", &moveIndex);
			while (test != 1)
			{
				printf("Not a Number\nPlease enter a number >");
				test = scanf("%d", &moveIndex);
			}
		}
		addPiece(boardinfo, moveIndex - 1, firstplayer);
		int winner = validatePath(boardinfo);
		if (winner != 0)
			return winner;

		playCount += 1;
		if (playCount >= boardinfo->ncols * boardinfo->nrows)
			return 0;

		clearScreen();
		printBoard(boardinfo);
		printf("Player %d move > ", secondplayer);
		test = scanf("%d", &moveIndex);
		while (test != 1)
		{
			printf("Not a number\nEnter a number >");
			test = scanf("%d", &moveIndex);
		}
		while (checkAvailable(boardinfo, moveIndex - 1) == 0)
		{
			printf("That place is not available try somewhere else >");
			printf("\nPlayer %d move > ", secondplayer);
			test = scanf("%d", &moveIndex);
			while (test != 1)
			{
				printf("Not a number\nPlease eneter a number > ");
				test = scanf("%d", &moveIndex);
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
	/* Randomly chooses a column and checks if it is available */
	int placement = rand() % boardinfo->ncols;
	while (checkAvailable(boardinfo, placement) == 0)
		placement = rand() % boardinfo->ncols;
	return placement;
}

int hardMode(struct gameinfo *boardinfo)
{
	int positions[boardinfo->ncols];

	for (int i = 0; i < boardinfo->ncols; i++)
	{
		int index = (boardinfo->nrows - 1) * boardinfo->ncols + i;

		for (; index > (boardinfo->ncols - 1); index -= boardinfo->ncols)
			if (boardinfo->board[index] == 0)
				break;
		printf("column %d: %d\n", i, index);

		/*initilize array index to 0 before compating it*/
		int temp;
		positions[i] = 0;
		/*Horizontal Checking if computer can win and then if the person has a higher chance*/
		if ((((index + boardinfo->winamount) % boardinfo->ncols >= boardinfo->winamount || (index + boardinfo->winamount) % boardinfo->ncols == 0)))
		{
			temp = bfs(boardinfo, index, index + boardinfo->winamount - 1, 2);
			if (temp > positions[i])
				positions[i] = temp;
		}
		if ((((index + boardinfo->winamount) % boardinfo->ncols >= boardinfo->winamount || (index + boardinfo->winamount) % boardinfo->ncols == 0)))
		{
			temp = bfs(boardinfo, index, index + boardinfo->winamount - 1, 1);
			if (temp > positions[i])
				positions[i] = temp;
		}
		if (((index - boardinfo->winamount) % boardinfo->ncols) < boardinfo->winamount || (index - boardinfo->winamount) % boardinfo->ncols == (boardinfo->ncols - 1))
		{
			temp = bfs(boardinfo, (index - boardinfo->winamount) - 1, index, 2);
			if (temp > positions[i])
				positions[i] = temp;
		}
		if (((index - boardinfo->winamount) % boardinfo->ncols) < boardinfo->winamount || (index - boardinfo->winamount) % boardinfo->ncols == (boardinfo->ncols - 1))
		{
			temp = bfs(boardinfo, (index - boardinfo->winamount) - 1, index, 1);
			if (temp > positions[i])
				positions[i] = temp;
		}

		/*Vertical Checking if computer can win and then checks to see if player has a chance */
		if ((index - ((boardinfo->winamount - 1) * boardinfo->ncols)) > -1)
		{
			temp = bfs(boardinfo, index, (index - ((boardinfo->winamount - 1) * boardinfo->ncols)), 2);
			if (temp > positions[i])
				positions[i] = temp;
		}
		if ((index - ((boardinfo->winamount - 1) * boardinfo->ncols)) > -1)
		{
			temp = bfs(boardinfo, index, (index - ((boardinfo->winamount - 1) * boardinfo->ncols)), 1);
			if (temp > positions[i])
				positions[i] = temp;
		}
	}

	for (int i = 0; i < boardinfo->ncols; i++)
	{
		printf("%d -> ", i);
	}
	printf("\n");
	for (int i = 0; i < boardinfo->ncols; i++)
	{
		printf("%d -> ", positions[i]);
	}
	printf("\n");

	int tempMax = 0;
	int moveIndex = 0;
	for (int i = 0; i < boardinfo->ncols; i++)
	{
		if (checkAvailable(boardinfo, i) == 1)
		{
			if (positions[i] > tempMax)
			{
				tempMax = positions[i];
				moveIndex = i;
			}
		}
	}
	return moveIndex;
}

int computer(struct gameinfo *boardinfo)
{
	char mode[25] = {'\0'};
	int imode = 0;
	int playCounter = 0, playerwin = 0, add = 0;
	printf("Hardness (easy, hard, impossible): ");

	scanf("%s", mode);

	while (strncmp(mode, "easy", 25) != 0 &&
		   strncmp(mode, "hard", 25) != 0 &&
		   strncmp(mode, "impossible", 25) != 0)
	{
		printf("Not an option\n");
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
			printf("Column to place peice in: ");

			int test = scanf("%d", &add);
			while (test != 1)
			{
				printf("Error not a number, please input a number: ");
				test = scanf("%d", &add);
			}
		} while (addPiece(boardinfo, add - 1, 1) == 0);

		playerwin = validatePath(boardinfo);
		if (playerwin != 0)
			return playerwin;

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