#include "../include/win.h"

int checkHorizontalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks the horizontal winning */
	int i = 0, count = 0, newIndex = index;
	for (; i <= boardinfo->winamount; i++)
	{
		int col = newIndex % boardinfo->ncols;
		if(boardinfo->board[newIndex] == boardinfo->board[index]) 
			count += 1;
		else
			return 0;
		
		if(col == 0) return count;
		newIndex = index - i;
	}
	return count;
}

int checkVerticalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Vertical winning */
	int i = 0, count = 0, newIndex = index;
	for (; i <= boardinfo->winamount; i++)
	{
		if(boardinfo->board[newIndex] == boardinfo->board[index])
			count += 1;
		else
			return 0;
		
		if(newIndex < boardinfo->ncols) return count;
		newIndex = index - (i * boardinfo->ncols);
	}
	return count;
}

int checkLeftDiagonalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Up diagonal winning */
	int i = 0, count = 0, newIndex = index;
	for (; i <= boardinfo->winamount; i++)
	{
		printf("Checking %d<%d> - %d<%d> == %d\n", index, boardinfo->board[index], newIndex, boardinfo->board[index], count);
		if(boardinfo->board[newIndex] == boardinfo->board[index])
			count += 1;
		else
			return 0;

		int col = newIndex % boardinfo->ncols;
		if(col == 0 || newIndex < boardinfo->ncols) return count;
		newIndex = index - ((i * boardinfo->ncols) + i);
	}
	return count;
}

int checkRightDiagonalWin(struct gameinfo *boardinfo, int index)
{
	/* Checks Down Diagonal winning */
	int i = 1, count = 0, newIndex = index;
	if (boardinfo->board[newIndex] == boardinfo->board[index]) count++;
	for (; i <= boardinfo->winamount; i++)
	{
		if (index - (i * boardinfo->ncols) - i >= (-1 - boardinfo->ncols))
		{
			newIndex = index - (i * boardinfo->ncols) - i;
		}
		else
		{
			return 0;
		}
		if (boardinfo->board[newIndex] == boardinfo->board[index])
		{
			count+=1;
		}
		else
		{
			return 0;
		}
	}
	return count;
}

int checkWin(struct gameinfo *boardinfo)
{
	int winamount = boardinfo->winamount;
	for (int index = boardinfo->ncols * boardinfo->nrows - 1; index > -1; index--)
	{
		if (boardinfo->board[index] == 0)
			continue;
		/* Only check 4 directions because checking 8 would be arbitray since
		 * it would be checking the same spots but in different directions going forward and backwards
		 * if it wasnt a win */
		/*
		if (checkHorizontalWin(boardinfo, index) >= (winamount + 1))
		{
			return boardinfo->board[index];
		}

		if (checkVerticalWin(boardinfo, index) >= (winamount + 1))
		{
			return boardinfo->board[index];
		}*/


		if (checkLeftDiagonalWin(boardinfo, index) >= (winamount + 1))
		{
			printf("LD: %d %d", index, checkLeftDiagonalWin(boardinfo, index));
			return boardinfo->board[index];
		}

		/* checking to make sure board wrap around does not happen 
		if (((index - boardinfo->winamount) % boardinfo->ncols) < boardinfo->winamount || (index - boardinfo->winamount) % boardinfo->ncols == (boardinfo->ncols - 1))
		{
			if (checkLeftDiagonalWin(boardinfo, index) >= (winamount-2))
			{
				printf("RD: %d", index);
				return boardinfo->board[index];
			}
		}*/
	}

	return 0;
}