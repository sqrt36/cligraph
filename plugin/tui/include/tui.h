/*
 * tui.h is part of cligraph.
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
 * tui.h 
 *
 * AUTHOR: Noah Harvey
 *
 * VERSION: v0.0.1
 *
 * DESCRIPTION: declaration file for window functions
 */

/*--TUI LAYOUT----------------------------------------
 * The physical screen shall have the following layout: 
 *
 * --|-----|-- --> menu/toolbar section
 * --|-----|-- 
 *             --> output/interaction(for graph) section
 *         
 * ----------- --> input/command section
 * ----------- 
 * 
 * There shall be 6 "buttons" in the toolbar to switch "screens": 
 * 1. Math - performing mathmatical computations
 * 2. Functions - defining functions and relations
 * 3. Tables - a table editor
 * 4. Graphs - graphing ANYTHING
 * 5. Settings/Menu - contains menu for editing settings for plugins
 * 6. Reserved for Plugins - window where plugins can display custom tui
 *
 * Each screen will be accessed by a menu located in the menu section of the
 * screen. The menus 1-6 are to remain static throughout any given screen. No
 * plugin will have access to these menu items - except screen 6 which only
 * allows plugins to submit a menu object for addition as a sub-menu.
 *
 * Notes on Screen 6 Menu
 * Screen 6 shall display only one custom screen at any given time.
 * While only one screen is to be displayed a plugin is not limited to the
 * number of screens it has access to. The menu for screen 6 will be organized
 * into a single sub-menu for each plugin. The number of menu items per plugin
 * sub-menu is left up to the plugin, however each menu item must correspond to
 * a screen controlled by the plugin.
 *
 *--TUI LAYOUT--------------------------------------*/

#include <ncurses.h>
#include <menu.h>

#ifndef __TUI
#define __TUI

/* screen structure */
typedef struct display
{
	char* dispcntnt; //content to display
	struct curspos_st { int x; int y; } curpos; //position of cursur if it is in screen (default is out of screen or -1,-1). coordinates are taken from top left of window container
} DISPLAY;

/*
 * FUNCTION: starttui
 * 
 * DESCRIPTION: starts running the tui as a thread-safe system
 *
 * PARAMETERS: void* null - absolutely nothing, this exists only for
 * pthread_create()
 *
 * RETURNS: void* - this will be NULL no matter what. errno is set if error
 * occures
 */
void* starttui(void* null);

/*
 * FUNCTION: stoptui
 * 
 * DESCRIPTION: stops running the tui in a gracefull way
 *
 * PARAMETERS: 
 *
 * RETURNS: void - 
 * 
 * NOTES: if there is an error in closing the tui it performs a force kill of
 * the thread that runs it. 
 */
void stoptui();

#endif 
