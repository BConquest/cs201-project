#include "../include/win.h"

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