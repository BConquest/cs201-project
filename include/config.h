#ifndef __config_h__
#define __config_h__

/* defines colors */
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

/* must be alpha-numeric 1 leter no escape sequences*/
char player1;
char player2;

/* Set if screen should be cleared(1) or not (0) values other than this will break stuff*/
int computer_stats;
int screen_clear;

/* stets all the variables */
void setConfig();
#endif