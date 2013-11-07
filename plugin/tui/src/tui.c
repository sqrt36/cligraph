/*
 * tui.c is part of cligraph.
 * 
 * cligraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * cligraph is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with cligraph.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * tui.c 
 *
 * AUTHOR: Noah Harvey
 * 
 * EMAIL: noah.harvey247 @gmail.com
 *
 * DESCRIPTION: definition file for prototypes in window.h
 */

/** TODO
 * - Restructure the keyboard controller to handle keyevents more efficiently
 * - Make the keyboard controller memory safe
 * - Make the keyboard controller thread safe
 */

#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pthread.h>

#include "dbg.h"
#include "keyboard.h"
#include "tui.h"
#include "winmgr.h"

/* thread for keyboard controller */
pthread_t kbthread;

//--starttui()------------------------------

//helper function for starttui
/* initializes all window structures for screen display*/
int __init_winstructs()
{
	int error_code = 0;

	//initialize menus 
	error_run(!__init_menubar(), error_code = 1);
	//initialize command bar
	error_run(!__init_CMDBAR(), error_code = 2);
	//initialize display window
	error_run(!__init_DISPWIN(), error_code = 3);

	return 0;

	error:
		return error_code;
}

//the default action to take place when a key is pressed
//default action is to print the key pressed to the current window
int default_event()
{
	waddch(CURRWIN,curr_key); 
}

//helper function for __add_default_keys
/* sets up the keyevent list */
void initkeyevents()
{
	size_t i;
	for (i = 0; i < NEVENTS; i++)
	addkeyevent(i,&default_event);
}

//helper function for starttui
/* sets up the default key events */
int __add_default_keys()
{
	initkeyevents();

	//--default events------------------------------
	//ESC closes the tui
	check(!addkeyevent(ESC_KEY, (event_func_type)stoptui),"failed to add event for key: %i",ESC_KEY); 

	//ENTER closes
	//check(!addkeyevent(ENTER_KEY, (event_func_type)exec_cmd),"failed to add event for key: %i",ENTER_KEY);

	//we want backspacing
	//check_expr(addkeyevent(KEY_BACKSPACE,(event_func_type)stoptui),0,"failed to add key event");

	//--END default events---------------------------
	return 0;

	error:
		return 1;
}

/* sets up and starts running the tui */
void* starttui(void* null)
{
	//vars
	int error_code = 0;

	//init screen
	initscr();

	//create window structs
	check_expr(__init_winstructs(),0,"Failed to create windows. aborting");

	//move the cursor to the CMDBAR
	wmove(CMDBAR,1,0);

	//display the windows
	doupdate();

	//start the keyboard controller
	log_attempt("Starting keyboard controller");
	error_run(!(error_code = pthread_create(&kbthread,NULL,(void* (*)(void*))startkeyctlr,CMDBAR)), log_failure("Could not start keyboard controller: %i",error_code));
	log_success();

	//add default key events
	__add_default_keys();

	//wait for keyboard controller thread to end
	pthread_join(kbthread,NULL);

	return NULL;
	error: 
		stoptui();
		return NULL;
}

//--END starttui()---------------------------

//--stoptui()------------------------------

/* stops running the tui interface */
int stoptui()
{
	debug("stopping tui...");
	stopkeyctlr();
	__free_winstructs();	
	endwin();
	return 0;
}

//--END stoptui()---------------------------