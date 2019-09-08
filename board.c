/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include "board.h"
#include "player.h"

/**
 * @file board.c contains implementations of functions related to the game 
 * board.
 **/

/**
 * @param board the board to reset the contents of
 **/
void initialise_board(enum cell_contents board[][BOARDWIDTH])
{
	int i;
	int j;
	for (i = 0; i < BOARDHEIGHT; ++i) {
		for (j = 0; j < BOARDWIDTH; ++j) {

			/**
			 * sets each board location to empty
			 **/
			board[i][j] = C_EMPTY;
		}
	}
}

/**
 * In this requirement you are required to display the game board. 
 * The game board should be displayed as shown on the first page of the 
 * assignment specification. 
 * @param board the board to display
 **/
void display_board(enum cell_contents board[][BOARDWIDTH])
{
	int i;
	int j;

	printf("\n\nThis is the current state of the board:\n\n");

	/* start board colours and print the column rows */
	printf(BOARD_COLOURS);
	printf(" 1 | 2 | 3 | 4 | 5 | 6 | 7 |");
	printf(RESET_COLOURS);
	printf("\n");
	printf(BOARD_COLOURS);
	printf("----------------------------");
	printf(RESET_COLOURS);
	printf("\n");

	for (i = 0; i < BOARDHEIGHT; ++i) {
		for (j = 0; j < BOARDWIDTH; ++j) {
			printf(BOARD_COLOURS);

			 /* empty slot */
			if (board[i][j] == C_EMPTY) {
				printf("   |");
			}

			/* red non-blinking token */
			else if (board[i][j] == C_RED) {
				printf(" ");
				printf(RED_TOKEN);
				printf(" |");

			/* white non-blinking token */
			} else if (board[i][j] == C_WHITE) {
				printf(" ");
				printf(WHITE_TOKEN);
				printf(" |");

			/* red blinking token (winning row) */
			} else if (board[i][j] == C_RED_WIN) {
				printf(" ");
				printf(RED_TOKEN_BLINK);
				printf(" |");

	 		/* white blinking token (winning row) */
			} else if (board[i][j] == C_WHITE_WIN) {
				printf(" ");
				printf(WHITE_TOKEN_BLINK);
				printf(" |");
			}
			if ((j + 1) == BOARDWIDTH) {
				printf(RESET_COLOURS);
			}
		}

		/* board footer */
		printf("\n");
		printf(BOARD_COLOURS);
		printf("----------------------------");
		printf(RESET_COLOURS);
		printf("\n");
	}

	printf(RESET_COLOURS);

}


