/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include "player.h"

/**
 * @param human the human player to initialise
 **/
enum input_result get_human_player(struct player* human)
{
	/* placeholder return value. You should prompt the user 
	 * for their name and then initialise all other values in the
	 * player struct to sensible values.
	 */

	clear_screen();

	/* get the users name */
	read_string("Please enter your name: ", human->name, NAMELEN);

	/* randomly select a token colour */
	human->thiscolor = random_colour(TRUE);

	/* set their token counter to 0 */
	human->counters = 0;

	/* set the player type to human */
	human->type = HUMAN;

	/* indicate which colour token they have been allocated */
	printf("\n%s is: ", human->name);
	if (human->thiscolor == C_RED) {
		printf(RED_TOKEN);
		printf(" Red Tokens\n");
	} else {
		printf(WHITE_TOKEN);
		printf(" White Tokens\n");
	}

	return SUCCESS;

}

/**
 * @param computer the computer player to initialise
 **/
enum input_result get_computer_player(struct player * computer)
{
	/* initialise all variables that are part of the struct to sensible 
	 * values */

	/* set the computer players name */
	strcpy(computer->name, "Computer");

	/* allocate the opposite colour to the human player */
	computer->thiscolor = random_colour(FALSE);

	/* set the computers token counter to 0 */
	computer->counters = 0;

	/* set the player type to computer */
	computer->type = COMPUTER;

	/* indicate which colour token the computer has been allocated */
	printf("\nComputer is: ");
	if (computer->thiscolor == C_RED) {
		printf(RED_TOKEN);
		printf(" Red Tokens\n");
	} else {
		printf(WHITE_TOKEN);
		printf(" White Tokens\n");
	}

	return SUCCESS;

}

/**
 * In this requirement, you need to handle the taking of a turn - either
 * of a human or a computer player.
 *
 * For the human player, you will need to allow the user to enter the 
 * column they wish to place a token in. You will need to validate what 
 * the user enters, then place a token correctly in that column so that
 * it occupies the cell closest to the bottom of the board array for that 
 * column.
 *
 * For the computer player, you will need to randomly generate a column 
 * number to place a token in and if that column is full, generate a 
 * different column number until a column number with some free space has 
 * been found.
 *
 * @param current the current player
 * @param board the game board that we will attempt to insert a token into
 * @return enum @ref input_result indicating the state of user input (in 
 * case this run involved user input
 **/
enum input_result take_turn(struct player * current,
		enum cell_contents board[][BOARDWIDTH])
{

	/**
	 * check what type of player, and redirect to the
	 * appropriate method.
	 **/
	if (current->type == HUMAN) {
		human_take_turn(board, current);
	} else {
		computer_take_turn(board, current);
	}

	return SUCCESS;

}

/**
 * used to generate a random colour for players, the passed boolean value
 * inidcates if this is the first random selection - if so, the second
 * call to this function (with boolean value being false) will return
 * the opposite value without performing another randomisation.
 **/
color random_colour(BOOLEAN first_choice)
{
	
	/* generate a random integer between 0 and 9 */
	int random_number = rand() % 10;

	/* static variable to store the result */
	static color last_choice;

	/* if instructed to randomise a colour */
	if (first_choice == TRUE) {

		/* allocate red for values 4 and below */
		if (random_number >= 4) {
			last_choice = C_RED;
			return C_RED;

		/* allocate white for values 5 and above */
		} else {
			last_choice = C_WHITE;
			return C_WHITE;
		}

	/**
	 * otherwise do not randomise a colour, use
	 * the opposite colour from last randomisation.
	 **/
	} else {
		if (last_choice == C_RED) {
			return C_WHITE;
		} else {
			return C_RED;
		}
	}

}

