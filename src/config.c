#include "../include/config.h"
void setConfig()
{
	player1 = 'O'; //Player 1s peice must be a character no escape sequences
	player2 = 'X';

	computer_stats = 1; //displays what the computer is doing turn off for small boards because it might slow down slower terminals
	screen_clear = 1;  //clears the screen when set to 1 else prints a new line
}
