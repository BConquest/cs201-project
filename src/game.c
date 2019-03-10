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

	if(j > boardinfo->ncols || j < 0)
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
/*
int checkHorizontalWin(struct gameinfo *boardinfo, int index)
{
        int i = 1, count = 0;
        for(; i < boardinfo->winamount; i++)
                if(boardinfo->board[index+i] == boardinfo->board[index])
                        count++;
                else
                        return 0;
        return count;
}

int checkVerticalWin(struct gameinfo *boardinfo, int index)
{
        int i = 1, count = 0;
        for(; i < boardinfo->winamount; i++)
                if(boardinfo->board[index-(i*boardinfo->ncols)] == boardinfo->board[index])
                        count++;
                else
                        return 0;
        return count;
}

int checkUpDiagonalWin(struct gameinfo *boardinfo, int index)
{
        int i = 1, count = 0;
        for(; i < boardinfo->winamount; i++)
                if(boardinfo->board[index-(i*boardinfo->ncols)+i] == boardinfo->board[index])
                        count++;
                else
                        return 0;
        return count;
}

int checkDownDiagonalWin(struct gameinfo *boardinfo, int index)
{
	int i = 1, count = 0;
	for(; i < boardinfo->winamount; i++)
        return count;
}

int checkWin(struct gameinfo *boardinfo)
{
        int index = (boardinfo->ncols * boardinfo->nrows) - 1;
	int ncols = boardinfo->ncols;
	int nrows = boardinfo->nrows;
	int winamount = boardinfo->winamount;
        for(; index >= 0; index--)
        {
                if(boardinfo->board[index] == 0)
                        continue;
                if(((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount)
                        if(checkHorizontalWin(boardinfo, index) >= (winamount-1))
                                return boardinfo->board[index];
                if((index - ((winamount - 1) * ncols)) >= 0)
                        if(checkVerticalWin(boardinfo, index) >= (winamount-1))
                                return boardinfo->board[index];
                if((((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount) ||
                   (index - ((winamount - 1) * ncols)) >= 0)
                        if(checkUpDiagonalWin(boardinfo, index) >= (winamount-1))
                                return boardinfo->board[index];
                if((((index+winamount)%ncols) == 0 || ((index+winamount)%ncols) >= winamount) ||
                   (index + ((winamount-1) * ncols)) <= ncols*nrows)
                        if(checkDownDiagonalWin(boardinfo, index) >= (winamount-1))
                                return boardinfo->board[index];
        }

        return 0;
}
*/

int dfs(struct gameinfo *boardinfo,int index)
{
	if(boardinfo->board[index] == 0) return 0;

	int visited[boardinfo->nrows*boardinfo->ncols];
	struct stackNode* root = NULL;
	int currLength = 0;

	push(&root, index);
	visited[index] = 1;	
	while(!isEmpty(root))
	{
		int newIndex = pop(&root);
		printf("%d\t", newIndex);
		int neighbors[8] = {0,0,0,0,0,0,0,0};
		
		if(newIndex += 1 < (boardinfo->ncols*boardinfo->nrows))
			if(boardinfo->board[index] == boardinfo->board[newIndex])
				neighbors[0] = newIndex + 1;
		
		if(newIndex -= 1 >= 0)
			if(boardinfo->board[index] == boardinfo->board[newIndex])
				neighbors[1] = newIndex - 1;
		
		if((newIndex += boardinfo->ncols) < boardinfo->ncols)
			if(boardinfo->board[index] == boardinfo->board[newIndex])
				neighbors[2] = (newIndex += boardinfo->ncols);
		
		if((newIndex -= boardinfo->ncols) > -1)
			if(boardinfo->board[index] == boardinfo->board[newIndex])
				neighbors[3] = (newIndex += boardinfo->ncols);
		
		if((newIndex -= (boardinfo->ncols-1) >= 0))
			if(boardinfo->board[index] == boardinfo->board[newIndex])
				neighbors[4] = (newIndex += boardinfo->ncols);

		for(int nindex = 0; nindex < 8; nindex++)
			if(neighbors[nindex] != 0 && visited[neighbors[nindex]] == 0)
			{
				push(&root, neighbors[nindex]);
				visited[neighbors[nindex]] = 1;
			}
	}
	printf("\n");
	free(root);
	printf("%d", currLength);
	return currLength;
}

int checkWin(struct gameinfo *boardinfo)
{
	for(int i = 0; i < boardinfo->ncols*boardinfo->nrows; i++)
	{
		if (dfs(boardinfo, i) >= boardinfo->winamount)
			return boardinfo->board[i];
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
	return rand() % boardinfo->ncols;
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
