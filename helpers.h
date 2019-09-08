/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"

/**
 * @file helpers.h contains the datastructures used for various helper 
 * functioons and their function prototypes
 **/
#ifndef HELPERS_H
#define HELPERS_H
#define EXTRA_CHARS 2

/* indicate that the global variable marking_mode exists */
extern BOOLEAN marking_mode;

/**
 * the possible values that can be returned from custom input handling 
 * functions
 **/
enum input_result
{
	/**
	 * the input was valid
	 **/
	SUCCESS,
	/**
	 * the input was not valld
	 **/
	FAILURE,
	/**
	 * the user requested to return to the menu either by pressing enter on
	 * an empty line or pressing ctrl-d on an empty line
	 **/
	RTM=-1
};

/**
 * call this function whenever you detect buffer overflow but only call this
 * function when this has happened.
 **/
void read_rest_of_line(void);

/**
 * prints the ANSI code to clear the screen.
 **/
void clear_screen(void);

/**
 * reads an integer value from keyboard - provide the on-screen prompt,
 * the number of decimals to be read (i.e. "10" = 2), the minimum
 * acceptable value, and the maximum acceptable value.
 **/
int read_integer(char* prompt, int size, int min_value, int max_value);

/**
 * reads a string value from keyboard - provide the on-screen prompt,
 * a pointer to the destination string where the captured value will
 * be stored, and the number of characters the string may contain
 * (maximum).
 **/
int read_string(char* prompt, char* destination_string, int size);

/**
 * halts program execution, waiting for user to press the [ENTER]
 * key - must provide an on screen prompt.
 **/
void wait_for_user(char* prompt);

/**
 * toggles the global variable to enable or disable marking
 * mode - which when enabled, disables animation and
 * screen clearing.
 **/
void toggle_marking_mode(void);

/* defined in con4.c */
int main(void);

#endif
