/***********************************************************************
 * Advanced Programming Techniques
 * Semester 2 2015 
 * Jeremy John Mercer
 * Start up code provided by Paul Miller
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "helpers.h"
#include "scoreboard.h"
#include "player.h"
#include "game.h"
#include "bool.h"
/**
 * @file con4.h simply puts together all the other header files for 
 * inclusion in @ref con4.c
 **/
#define MIN_MENU_ITEM 1
#define MAX_MENU_ITEM 3

/**
 * global to track if marking mode is on or off -
 * marking mode disables clearing of the console and animation
 **/
BOOLEAN marking_mode = FALSE;

/**
 * displays the main menu, and handels menu selection from users
 **/
int run_menu(void);
