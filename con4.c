/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include "con4.h"

/**
 * @mainpage COSC1076 - Assignment 1 documentation.
 *
 * This is the main html documentation of assignment 1 for COSC1076 -
 * Advanced Programming Techniques for semester 2, 2015. You will find
 * here a description of the functions that you need to implement for
 * your assignment.
 *
 * Please note that this should not be your first stop when starting
 * your assignment. Please read the assignment 1 specifications that
 * are available on blackboard before reading this documentation. The
 * purpose of this documentation is to clarify the actual individual
 * requirements.
 *
 * This site presents you with the documentation for each function
 * that you need to implement broken down by the file that they exist
 * in. Please go to the <b>Files</b> tab and click on the file you wish to
 * get more information about and then click on that file. An
 * explanation of each function implemented in that file will be
 * displayed.
 **/

/**
 * @file con4.c contains the main function which is the entry point into the 
 * application and manages the main memory.
 **/

/**
 * the entry point into the game. You should display the main menu and 
 * respond to user requests.
 *
 * The main menu should look like this: 
 * Welcome to connect 4
 *  \n\--------------------
 * 1. Play Game
 * 2. Display High Scores
 * 3. Quit
 * Please enter your choice:
 *
 * This menu should also be redisplayed when the program returns from 
 * running an option.
 **/
int main(void)
{

	/* stores the selected menu item */
	int response;

	/* the scoreboard for keeping track of winners */
	scoreboard scores;

	/* the two players and a pointer to who won the last game */
	struct player human_player, computer_player, *winner;

	/* keeps track of if a score has been added to the scoreboard */
	BOOLEAN new_high_score = FALSE;

	/* seed the randomising function */
	srand(time(0));

	/**
	 * with each of the comments below, insert the code that performs 
	 * this function 
	 */

	/* initialise the scoreboard */
	init_scoreboard(scores);

	/*display menu and get menu choice until the user chooses to quit */
	while (1) {

		/* display menu and retreive user response */
		response = run_menu();

		/* process menu selection */
		switch (response) {
			case 1:
				/* play a game option */
				winner = play_game(&human_player, &computer_player);

				/* check if score should be added to scoreboard */
				new_high_score = add_to_scoreboard(scores, winner);

				break;

			case 2:
				/* display the scoreboard option */
				display_scores(scores);
				break;

			case 3:
				/* quit the program option */
				printf("%s%s\n\n", "Goodbye!", EXIT_COLOURS);
				return EXIT_SUCCESS;
				break;

			case 4:
				/* enable / disable marking mode */
				toggle_marking_mode();
				break;

		}
	}
}

/**
 * displays the main menu of the program
 * prompts the user for their selection
 * and returns the integer selection
 */
int run_menu(void)
{

	/* stores the users selection */
	int response;

	clear_screen();

	/* show the main menu */
	printf("%s", RESET_COLOURS);
	printf("%s\n", "---------------------------------------");
	printf("%s%s%s%s%s%s%s\n", BOARD_COLOURS,"          WELCOME TO ", BLINK_ON, "CONNECT 4", BLINK_OFF,"         ", RESET_COLOURS);
	printf("%s\n", "---------------------------------------");
	printf("%s\n", " 1. Play Game");
	printf("%s\n", " 2. Display High Scores");
	printf("%s\n\n", " 3. Quit");
	printf("%s", " 4. Turn Marking Mode ");

	/* indicate if marking mode is on or off */
	if (marking_mode == TRUE) {
		printf("Off\n\n");
	} else {
		printf("On\n\n");
	}

	/* get selection from user */
	response = read_integer("Please enter your choice:", 1, 1, 4);

	return response;

}

