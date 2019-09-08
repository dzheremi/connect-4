/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include "game.h"

/**
 * @file game.c contains the functions that relate to the management of
 * the game.
 **/

/**
 * This requirement requires you to understand a little more about pointers.
 * We want you to understand that all pointers just point to another memory
 * address whether they are a single pointer, a pointer to a pointer, etc.
 * 
 * In this example, we want you to swap the pointers for two players. 
 * This will be called from \ref play_game with a call such as 
 * swap(&current, &other) and at the end of this function, current and
 * other's pointers will be swapped.
 * For example, if current points to the human player and other points to 
 * the computer player, at the end of this function, the player they point 
 * to will have been swapped. 
 * 
 * @param current the current player who has just completed their turn
 * @param other the next player whose turn it will be
 **/
static void swap_players(struct player ** current, struct player ** other)
{
	/* implement a classic swap using a temporary pointer */
	struct player* temp = *other;
	*other = *current;
	*current = temp;
}

/**
 * This is the heart of the game.
 * 
 * Firstly, you need to initialise the game by calling functions written 
 * for requirement 3. The rest of this function is then managing the game 
 * loop.
 *
 * Each player takes a turn to drop a token into a column on the game 
 * board. The task that needs to be performed will be different depending 
 * on whether this is a human or a computer player.
 *
 * Regardless of the player type, you will need to display the board as it 
 * was before the player makes their move. If the current player is a 
 * computer player, we just need to select a column at random and drop a
 * token into that column. If there is no room, try another column.
 *
 * If the current player is a human player, your program will need to ask 
 * the user what column they wish to drop a token in. This input should be 
 * validated to check that it is numeric and within the range of allowed 
 * columns.
 * 
 * Once a valid move has been entered, your program should update the 
 * gameboard. It should then check if the game has been won lost or drawn 
 * by calling and the change the current player.
 *
 * This function also checks if the game has been won, lost or drawn by 
 * calling \ref test_for_winner(), and if the game is over, returns the 
 * winner to main or NULL if the game was a draw.

 * @param human a pointer to details about the human player
 * @param computer a pointer to details about the computer player
 **/
struct player * play_game(struct player * human , 
		struct player* computer)
{
	/* declaration that allocates the board for the game */
	enum cell_contents board[BOARDHEIGHT][BOARDWIDTH];

	/**
	 * used to store the current game state:
	 * 	winner
	 * 	no winner
	 * 	draw
	 **/
	enum game_state winner = G_NO_WINNER;

	/* pointer to winning player */
	struct player* winning_player;

	/* initialise (clear) the game board */
	initialise_board(board);

	/* get player names and randomly allocate token colours */
	get_human_player(human);
	get_computer_player(computer);

	/**
	 * if the human player is not white, perform a pointer swap
	 * (computer goes first)
	 **/
	if (human->thiscolor != C_WHITE) {
		swap_players(&human, &computer);
	}

	/* indicate who goes first and wait for user */
	printf("\n%s takes the first turn...\n\n", human->name);
	wait_for_user("To begin the game, ");


	clear_screen();

	/* play the game while there is no winner */
	while(winner == G_NO_WINNER){

		clear_screen();

		/* handle the user taking their turn */
		if (human->type == HUMAN) {

			display_board(board);

			/* show score and allocated token below the board */
			if (human->thiscolor == C_RED) {
				printf("\n\nYOUR TOKENS: %s      SCORE: %d\n\n", RED_TOKEN, human->counters);
			} else {
				printf("\n\nYOUR TOKENS: %s      SCORE: %d\n\n", WHITE_TOKEN, human->counters);
			}
		}

		/* process player taking their turn */
		take_turn(human, board);

		/* check for a winner */
		winner = test_for_winner(board);

		/* swap players if there is no winner yet */
		if (winner == G_NO_WINNER)
			swap_players(&human, &computer);

	}

	clear_screen();

	display_board(board);

	/* output the results of the game */

	/* red wins */
	if (winner == G_RED) {

		/* check if red is human or computer player */
		if (human->thiscolor == C_RED && human->type == HUMAN) {
			printf("\n\nCongratulations! You have beat the computer!\n\n");
		} else {
			printf("\n\nThe computer has defeated you!\n\n");
		}

		/* point winning_player to the winner */
		winning_player = human;

	/* white wins */
	} else if (winner == G_WHITE) {

		/* check if white is human or computer player */
		if (human->thiscolor == C_WHITE && human->type == HUMAN) {
			printf("\n\nCongratulations! You have beat the computer!\n\n");
		} else {
			printf("\n\nThe computer has defeated you!\n\n");
		}

		/* point winning_player to the winner */
		winning_player = human;

	/* the game is a draw */
	} else {
		printf("\n\nThere are no more possible moves, this game is a draw!\n\n");
		winning_player = NULL;
	}

	wait_for_user("To return to the main menu, ");

	/* return the pointer to the winning player */
	return winning_player;
}

/**
 * In this requirement you are required to test what the game's current 
 * state is.
 * Possible game states are defined by the game_state enumeration:
 * enum game_state
 * {
 *    G_NO_WINNER=-1,
 *    G_DRAW,
 *    G_RED,
 *    G_WHITE
 * };
 *
 * Most of these states should be self-explanatory but let's go through 
 * their meaning.
 * 
 *    &bull; G_NO_WINNER: the game is still in progress and therefore there
 *    is no winner yet.
 * 
 *    &bull; G_DRAW: neither player has won the game but there are no more 
 *    spaces left for a player to make a move.
 *    
 *    &bull; G_RED / G_WHITE: the player whose token is the specified 
 *    colour has won the game.
 *
 * Your task in this function is to iterate over the 2-dimensional array 
 * (the board) looking for four in a row in any direction – if you find 
 * this, return the appropriate value of either G_RED or G_WHITE.
 *
 * Next, test for a draw. If none of these cases hold, return G_NO_WINNER.
 * @param board the gameboard to test for a winner
 **/
enum game_state test_for_winner(
		enum cell_contents board[][BOARDWIDTH])
{
	/**
	 * default return value  - delete this comment and the return statement
	 * below and replace them with the game logic for deciding whether a 
	 * game has been won and who the winner is
	 **/

	/* variables used for looping through the game board */
	int i;
	int j;

	/* game state is to be returned, set to no winner by default */
	enum game_state winner = G_NO_WINNER;

	/* used to ensure there are still possible moves on the board */
	BOOLEAN still_space = FALSE;

	/* check for 4 in a row horizontally */
	for (i = 0; i < BOARDHEIGHT; ++i) {
		for (j = 0; j < (BOARDWIDTH - 3); ++j) {

			if (board[i][j] == board[i][j + 1]) {
				if (board[i][j] == board[i][j + 2]) {
					if (board[i][j] == board[i][j + 3]) {

						if (board[i][j] == C_RED) {

							/* red tokens wins */
							winner = G_RED;

							/* make the winning token blink */
							board[i][j] = C_RED_WIN;
							board[i][j + 1] = C_RED_WIN;
							board[i][j + 2] = C_RED_WIN;
							board[i][j + 3] = C_RED_WIN;


						} else if (board[i][j] == C_WHITE) {

							/* white tokens win */
							winner = G_WHITE;

							/* make the winning tokens blink */
							board[i][j] = C_WHITE_WIN;
							board[i][j + 1] = C_WHITE_WIN;
							board[i][j + 2] = C_WHITE_WIN;
							board[i][j + 3] = C_WHITE_WIN;
						}
					}
				}
			}
		}
	}

	/* check for 4 in a row vertically */
	for (i = 0; i < (BOARDHEIGHT - 3); ++i) {
		for (j = 0; j < BOARDWIDTH; ++j) {

			if (board[i][j] == board[i + 1][j]) {
				if (board[i][j] == board[i + 2][j]) {
					if (board[i][j] == board[i + 3][j]) {

						if (board[i][j] == C_RED) {

							/* red tokens win */
							winner = G_RED;

							/* make the winning tokens blink */
							board[i][j] = C_RED_WIN;
							board[i + 1][j] = C_RED_WIN;
							board[i + 2][j] = C_RED_WIN;
							board[i + 3][j] = C_RED_WIN;

						} else if (board[i][j] == C_WHITE) {

							/* white tokens win */
							winner = G_WHITE;

							/* make the winning tokens blink */
							board[i][j] = C_WHITE_WIN;
							board[i + 1][j] = C_WHITE_WIN;
							board[i + 2][j] = C_WHITE_WIN;
							board[i + 3][j] = C_WHITE_WIN;
						}
					}
				}
			}
		}
	}

	/* check for 4 in a row diagonally - top left to bottom right */
	for (i = 0; i < (BOARDHEIGHT - 3); ++i) {
		for (j = 0; j < (BOARDWIDTH - 3); ++j) {

			if (board[i][j] == board[i + 1][j + 1]) {
				if (board[i][j] == board[i + 2][j + 2]) {
					if (board[i][j] == board[i + 3][j + 3]) {

					       if (board[i][j] == C_RED) {

						       /* red tokens win */
						       winner = G_RED;

						       /* make the winning tokens blink */
						       board[i][j] = C_RED_WIN;
						       board[i + 1][j + 1] = C_RED_WIN;
						       board[i + 2][j + 2] = C_RED_WIN;
						       board[i + 3][j + 3] = C_RED_WIN;

					       } else if (board[i][j] == C_WHITE) {

						       /* white tokens win */
						       winner = G_WHITE;

						       /* make the winning token blink */
						       board[i][j] = C_WHITE_WIN;
						       board[i + 1][j + 1] = C_WHITE_WIN;
						       board[i + 2][j + 2] = C_WHITE_WIN;
						       board[i + 3][j + 3] = C_WHITE_WIN;
					       }
					}
				}
			}
		}
	}

	/* check for 4 in a row diagonally - bottom left to top right */
	for (i = (BOARDHEIGHT - 1); i > (BOARDHEIGHT - 3); --i) {
		for (j = 0; j < (BOARDWIDTH - 3); ++j) {

			if (board[i][j] == board[i - 1][j + 1]) {
				if (board[i][j] == board[i - 2][j + 2]) {
					if (board[i][j] == board[i - 3][j + 3]) {

						if (board[i][j] == C_RED) {
							
							/* red tokens win */
							winner = G_RED;

							/* make the winning tokens blink */
							board[i][j] = C_RED_WIN;
							board[i - 1][j + 1] = C_RED_WIN;
							board[i - 2][j + 2] = C_RED_WIN;
							board[i - 3][j + 3] = C_RED_WIN;

						} else if (board[i][j] == C_WHITE) {

							/* white tokens win */
							winner = G_WHITE;

							/* make the winning tokens blink */
							board[i][j] = C_WHITE_WIN;
							board[i - 1][j + 1] = C_WHITE_WIN;
							board[i - 2][j + 2] = C_WHITE_WIN;
							board[i - 3][j + 3] = C_WHITE_WIN;
						}
					}
				}
			}
		}
	}

	/**
	 * check for a draw, by checking if there is any space
	 * left on the board
	 **/
	for (i = 0; i < BOARDHEIGHT; ++i) {
		for (j = 0; j < BOARDWIDTH; ++j) {

			if (board[i][j] == C_EMPTY) {
				still_space = TRUE;
			}

		}
	}
	if (still_space == FALSE)
		winner = G_DRAW;
	
	/* return the game state */
	return winner;

}

/**
 * method used to handle a user taking their turn - must provide the game board
 * array and a pointer to the player.
 **/
void human_take_turn(enum cell_contents board[][BOARDWIDTH], struct player * human)
{

	/* the column the user selects to place their token into */
	int column;

	/* used to store if a valid move had been entered */
	BOOLEAN valid_move = FALSE;

	/* loop until the user makes a valid move */
	do {

		/* read the column from user */
		column = read_integer("Enter a column to drop your token into:", 1, 1, 7);

		/* check if the move is valid */
		valid_move = make_move(board, human, --column);

		/* prompt if move is not valid */
		if (valid_move == FALSE) {
			printf("\n\nThat move is not valid, please try again!\n\n");
		}

	} while (valid_move == FALSE);

	/* increment the number of moves made by the user */
	human->counters++;

}

/**
 * method used to handle the computer taking its turn - must provide the game
 * board array and a pointer to the player.
 **/
void computer_take_turn(enum cell_contents board[][BOARDWIDTH], struct player * computer)
{

	/**
	 * generate a random number between 0 and 6 - the column to drop
	 * the token into.
	 **/
	int random_number = rand() % BOARDWIDTH;

	/* used to determine if a valid move has been made */
	BOOLEAN found_position = FALSE;

	/* loop until a valid move has been made */
	do {

		/* check the validity of the current move */
		found_position = make_move(board, computer, random_number);

		/* if the move is invalid, generate a new random number */
		if (found_position == FALSE) {
			random_number = rand() % BOARDWIDTH;
		}

	} while (found_position == FALSE);

	/* increment the number of moves made by the computer */
	computer->counters++;

}

/**
 * method used to make a move, by providing the game board, the current player,
 * and the column to drop the token into.
 **/
BOOLEAN make_move(enum cell_contents board[][BOARDWIDTH], struct player * current_player, int column)
{

	/* used to determine if a valid move is being made */
	BOOLEAN valid_move = FALSE;

	int i;
	int j;

	/* this is needed to animate the token dropping to position */
	BOOLEAN first = TRUE;

	/**
	 * loop throw each row of the provided column and check that it
	 * has space for a token.
	 **/
	for (i = (BOARDHEIGHT - 1); i < BOARDHEIGHT && i >= 0; --i) {
		if (board[i][column] == C_EMPTY) {

			/**
			 * i will be the existing height of the current column,
			 * this loop will animate the dropping of the token
			 * into position.
			 **/
			for (j = 0; j <= i; ++j) {

				/**
				 * as the token drops down, remove it from the cell
				 * above on the first itiration only.
				 **/
				if (first == TRUE) {
					first = FALSE;
				} else {
					board[j - 1][column] = C_EMPTY;
				}

				/* place the token into the cell */
				board[j][column] = current_player->thiscolor;

				/* only animate if marking mode flag is off */
				if (marking_mode == FALSE) {

					/**
					 * sleep, clear, and redisplay the board
					 * before next itiration.
					 **/
					usleep(100000);
					clear_screen();
					display_board(board);
				}
			}

			/**
			 * once the token is in position, set the move as valid
			 * and break the loop.
			 **/
			valid_move = TRUE;
			break;
		}
	}

	/* return the outcome of the attempted move. */
	return valid_move;

}

