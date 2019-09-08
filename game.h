/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "player.h"
#include "time.h"
#include "board.h"
#include "helpers.h"

/**
 * global defined in helpers.h
 **/
extern BOOLEAN marking_mode;

/**
 * the various possibilities when we check for a winner
 **/
enum game_state
{
	/**
	 * there was no winner (the game is still in progress
	 * - set to -1 so the other values increment from 0
	 **/
	G_NO_WINNER=-1,
	/**
	 * the game was a draw - there are no valid moves that can be made
	 **/
	G_DRAW,
	/**
	 * the red token won the game
	 **/
	G_RED,
	/**
	 * the white token won the game
	 **/
	G_WHITE
};

/**
 * manages the game loop. See the documentation in the .c file for full
 * details. 
 **/
struct player * play_game(struct player *, struct player*);

/**
 * tests to see if the game has been won. A win is defined as four 
 * tokens in a row in any direction, however you should not wrap 
 * around the board.
 **/
enum game_state test_for_winner(
		enum cell_contents board[][BOARDWIDTH]);

/**
 * handles a user taking a turn - asks for column to drop token into
 * and validates the move. 
 **/
void human_take_turn (enum cell_contents board[][BOARDWIDTH], struct player * human);

/**
 * handles the computer turn - uses a random number generator to select
 * a column and then validate the move.
 **/
void computer_take_turn (enum cell_contents board[][BOARDWIDTH], struct player * computer);

/**
 * used to validate a move - called by both computer_take_turn() and
 * human_take_turn().
 **/
BOOLEAN make_move (enum cell_contents board[][BOARDWIDTH], struct player * current_player, int column);

/* prototype for usleep function */
int usleep(useconds_t);
