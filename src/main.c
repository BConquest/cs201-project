#include <curses.h>
#include <stdio.h>

#include "board.h"

int main(void)
{	
	board* connect[8][6];
	*connect->width = 8;
	*connect->height = 8;

	addPeice(1, 0, 0, connect);
       	printboard(connect);	
	return 0;
}
