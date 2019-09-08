/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include <string.h>
#include <stdio.h>
#include "bool.h"

/**
 * @file board.h contains data definitions that relate to the game board.
 **/

#ifndef BOARD_H
#define BOARD_H
/**
 * how many token in a row do we need for a win?
 **/
#define NUM_IN_ROW 4
/**
 * how wide is the board? 
 **/
#define BOARDWIDTH 7
/**
 * how tall is the board? 
 **/
#define BOARDHEIGHT 6

/**
 * the minimum column number in the game
 **/
#define MINCOLUMN 1
/**
 * the maximum column number in the game
 **/
#define MAXCOLUMN BOARDWIDTH

/**
 * defines the possible contents of each cell of the board
 **/
enum cell_contents
{
	/** the cell does not contain a token **/
	C_EMPTY, 
	/** the cell contains a red token **/
	C_RED, 
	/** the cell contains a white token **/
	C_WHITE,
	C_RED_WIN,
	C_WHITE_WIN
};


/**
 * the code used to print a red game token
 * and a blinking red game token to indicate winning row
 **/
#define RED_TOKEN "\x1b[1;31mO\x1b[1;33m"
#define RED_TOKEN_BLINK "\x1b[1;5m\x1b[1;31mO\x1b[1;33m\x1b[1;25m"

/**
 * the code used to print a white token
 * and a blinking white game toekn to indicate winning row
 **/
#define WHITE_TOKEN "\x1b[1;37mO\x1b[1;33m"
#define WHITE_TOKEN_BLINK "\x1b[1;5m\x1b[1;37mO\x1b[1;33m\x1b[1;25m"

/**
 * the colours for the game board
 **/
#define BOARD_COLOURS "\x1b[1;44m\x1b[1;33m"

/**
 * the standard application colours
 **/
#define RESET_COLOURS "\x1b[1;40m\x1b[1;33m"

/**
 * resets terminal colours back to default (used on exit)
 **/
#define EXIT_COLOURS "\x1b[1;0m"

/**
 * toggles text to blink in supported terminals
 **/
#define BLINK_ON "\x1b[1;5m"
#define BLINK_OFF "\x1b[1;25m"

/**
 * forward declaration of player struct so that we can refer to it in this 
 * file - we don't want to #include @ref player.h as that would cause circular
 * dependencies.
 **/
struct player;

/**
 * we give cell contents an alias of color as that is what it defines. 
 **/
typedef enum cell_contents color;

/**
 * initialises the board to being an empty board
 **/
void initialise_board(enum cell_contents[][BOARDWIDTH]);

/**
 * displays the current board to the screen
 **/
void display_board(enum cell_contents[][BOARDWIDTH]);

#endif
