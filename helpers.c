/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include "helpers.h"

/**
 * @file helpers.c contains various functions that help in the
 * implementation of the program. You should put functions you create
 * here unless they logically belong to another module (such as
 * player, board or game
 **/

/**
 * buffer handeling method - clears the input buffer
 **/
void read_rest_of_line(void)
{

	int ch;
	while(ch = getc(stdin), ch!=EOF && ch != '\n')
		; /* gobble each character */

	/* reset the error status of the stream */
	clearerr(stdin);

}

/**
 * method to clear the console - using ANSI codes
 **/
void clear_screen()
{

	/* do not clear if running in marking mode */
	if(marking_mode == FALSE) {
		printf("\x1b[2J\x1b[1;1H");
	}

}

/**
 * method to read an integer from keyboard - provide a prompt for
 * the user, the number of places (i.e. "10" is 2 places), the
 * minimum acceptable value, and the maximum acceptable value.
 **/
int read_integer(char* prompt, int size, int min_value, int max_value)
{

	/* used to store the integer value to return */
	int result;

	/* char array to store user input */
	char input_string[size + EXTRA_CHARS];

	/* pointer used for string to long conversion */
	char* end_pnt;

	/* loop until a valid input is entered */
	BOOLEAN valid_input = FALSE;
	do
	{

		/* display the supplied prompt to user */
		printf("%s ", prompt);

		/**
		 * trap for CTRL-D sequences - in unix based systems
		 * pressing this key combination causes fgets() to 
		 * return NULL - in this circumstance the program is
		 * restarted.
		 **/
		if (fgets(input_string, size + EXTRA_CHARS, stdin) == NULL) {
			read_rest_of_line();
			main();
			exit(EXIT_SUCCESS);

		/* continue if fgets() receives an input other than NULL */
		} else {

			/**
			 * check if the input is too long, by checking for
			 * a new line escape code in the last position of
			 * the char array.
			 **/
			if (input_string[strlen(input_string) - 1] != '\n') {
				valid_input = FALSE;
				printf("Input was too long!\n");
				read_rest_of_line();

			} else {

				/**
				 * replace the new line escape code with an
				 * ASCII nul value.
				 **/
				input_string[strlen(input_string) - 1] = '\0';

				/* convert the input to a integer value */
				result = (int) strtol(input_string, &end_pnt, 10);

				/* check to see that the input was actually numeric */
				if (strcmp(end_pnt, "") != 0) {
					valid_input = FALSE;
					printf("Input was not numeric!\n");

				/* make sure the input is within bounds */
				} else if(result < min_value || result > max_value) {
					valid_input = FALSE;
					printf("Input was not within range!\n");

				/* if everything is okay, the input is accepted */
				} else {
					valid_input = TRUE;
				}
			}
		}
	} while (valid_input == FALSE);

	/* return the integer value */
	return result;

}

/**
 * reads a string value from keyboard - provide the on-screen prompt,
 * a pointer to the destination string, and the number of characters
 * the string may contain (maximum).
 **/
int read_string(char* prompt, char* destination_string, int size)
{

	/* array of chars for the input */
	char input_string[size + EXTRA_CHARS];

	/* loop until a valid input is entered */
	BOOLEAN valid_input = FALSE;
	do
	{

		/* display prompt to user */
		printf("%s ", prompt);

		/**
		 * check for CTRL-D sequences - see read_integer() comments
		 * for more information.
		 **/
		if (fgets(input_string, size + EXTRA_CHARS, stdin) == NULL) {
			read_rest_of_line();
			main();
			exit(EXIT_SUCCESS);

		} else {

			/**
			 * ensure the input is not longer than the maximum allowable
			 * length, by checking for a new-line escape sequence at
			 * the end of the char array.
			 **/
			if (input_string[strlen(input_string) - 1] != '\n') {
				valid_input = FALSE;
				printf("Input was too long!\n");
				read_rest_of_line();

			/* input is valid */
			} else {
				valid_input = TRUE;
			}
		}
	} while (valid_input == FALSE);

	/* replace the new-line escape sequence with an ASCII nul character */
	input_string[strlen(input_string) - 1] = '\0';

	/* copy the string into the destination string */
	strcpy(destination_string, input_string);

	return SUCCESS;
}

/**
 * halt the program execution, waiting for user to press the
 * [ENTER] key - must provide an on screen prompt.
 **/
void wait_for_user(char* prompt)
{

	/**
	 * char array to store user input - its not actually
	 * used and the buffer will be cleared as soon as
	 * the [ENTER] key is pressed.
	 **/
	char input_string[EXTRA_CHARS];

	/* display the prompt to user */
	printf("%s%s ", prompt, " press [ENTER]");

	/**
	 * check for a CTRL-D escape sequence - see read_integer() comments
	 * for more information.
	 **/
	if (fgets(input_string, EXTRA_CHARS, stdin) == NULL) {
		read_rest_of_line();
		main();
		exit(EXIT_SUCCESS);

	/* no validation is required, just clear the input buffer */
	} else {
		if (input_string[strlen(input_string) - 1] != '\n') {
			read_rest_of_line();
		}
	}

}

/**
 * toggles the global variable to enable or disable marking mode,
 * which when enabled, disables animation and screen clearing.
 **/
void toggle_marking_mode()
{

	if (marking_mode == TRUE) {
		marking_mode = FALSE;
	} else {
		marking_mode = TRUE;
	}

}

