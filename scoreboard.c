/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include "scoreboard.h"

/**
 * @param board the scoreboard to initialise
 **/
void init_scoreboard(scoreboard board)
{

	/* set all names to an empty string, and counters to 0 */
	int i;
	for (i = 0; i < SCOREBOARDSIZE; ++i) {
		strcpy(board[i].name, "");
		board[i].counters = 0;
	}

}

/** For this requirement, you will need to display the scores in the
 * order they are scored in the scoreboard array. 
 *
 * The display should look as follows: 
 * Player               |Score
 * --------------------------------------------- 
 * Barney               |17 
 * Magi                 |15 
 * Red                  |10 
 * Computer             |8 
 * Computer             |7 
 * Computer             |6 
 * Paul                 |4 
 * Fred                 |4 
 * Muaddib              |4
 * Zafiqa               |4
 * 
 * @param board the scoreboard to display
 **/
void display_scores(const scoreboard board)
{

	/* used to loop through the scoreboard */
	int i;

	clear_screen();

	/* print the scoreboard header */
	printf("\nPlayer               |Score\n");
	printf("---------------------------------------------\n");

	/* print each scoreboard entry */
	for (i = 0; i < SCOREBOARDSIZE; ++i) {

		/* don't show empty entries */
		if (board[i].counters == 0) {
			printf("                     |\n");
		
		/* print real entries */
		} else {
			printf("%-20s %s %-2d\n", board[i].name, "|", board[i].counters);
		}

	}

	/* print the scoreboard footer */
	printf("---------------------------------------------\n");

	/* wait for user to continue */
	wait_for_user("To return to the main menu, ");

}

/** When the game ends, you need to return the appropriate game state
 * back to main. You will then need to insert the winner's score
 * sorted in order by the number of counters that they played in the
 * game. You should only store the top ten scores and so when a new score
 * is entered on a full scoreboard, the lowest score simply drops off the
 * bottom of the board.  
 * 
 * Both scoreboard and score are typedefs (aliases) of other types.
 *
 * Scoreboard is defined as: typedef struct player
 *
 * scoreboard[SCOREBOARDSIZE]; and score is defined as: 
 *
 * typedef struct player score; 
 *
 * In other words, a scoreboard is an array of struct player of
 * SCOREBOARDSIZE (10) and a score is another name of a player struct.
 * This has been done so we can reuse the type and it simplifies the
 * maintenance of the code.
 * 
 * @param board the scoreboard to add the score to @param sc the score
 * to add to the scoreboard
 **/ 
BOOLEAN add_to_scoreboard(scoreboard board, const score * sc) 
{

	/* used to loop through the scoreboard */
	int i;

	/**
	 * used to store the appropriate position in the
	 * scoreboard - if one is acheived.
	 **/
	int position = -1;

	/**
	 * determine the position to place the new
	 * entry into the scoreboard (if any).
	 **/
	for (i = (SCOREBOARDSIZE - 1); i >= 0; --i) {
		if (sc->counters > board[i].counters) {
			position = i;
		}
	}

	/**
	 * if a valid position is found, move all array
	 * entries down by one position from that position.
	 **/
	if (position >= 0) {
		for (i = (SCOREBOARDSIZE - 1); i >= 0; --i) {
			if (i > position)
				board[i] = board[i - 1];
		}

		/* place the new score into position on the board */
		board[position] = *sc;

		/* return true to indicate a position on the leader board */
		return TRUE;

	/* return fales if no position on the leader board */
	} else {
		return FALSE; 

	}

}

