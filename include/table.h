/* This file name is part of sofware name.

sofware name is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

sofware name is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with sofware name.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * table.h 
 *
 * AUTHOR: Noah Harvey
 *
 * VERSION: v0.0.1
 *
 * DESCRIPTION: defines the table and functions thereof
 *
 */

#ifndef __TABLE
#define __TABLE

//structure that holds all the data cells of a table
struct table
{
	int x_size;
	int y_size;
	int* cells;
};

/*
 * FUNCTION: init_table
 * 
 * PARAMETERS: int x_size, int y_size
 *
 * RETURNS: struct table* - a blank table
 * 
 * DESCRIPTION: creates and initiates a table pointer that has all data cell values to 0
 * 
 * ERROR CODES: NULL pointer (if any error occurs)
 */
struct table* init_table(int x_size, int y_size);

/*
 * FUNCTION: set_cell
 * 
 * PARAMETERS: table* tble, int cell_value, int x, int y
 *
 * RETURNS: int - error code 
 * 
 * DESCRIPTION: sets the data value at the given index
 *
 * ERROR CODES: -1 - no error; 0 - table pointer is invalid; 1 - x and/or y is an
 * invalid index
 */
int set_cell(struct table* tble, int cell_value, int x, int y);

/*
 * FUNCTION: get_cell
 * 
 * PARAMETERS: struct table* tble, int x, int y
 *
 * RETURNS: int - integer value of the cell
 * 
 * DESCRIPTION: returns a cell at the given index
 *
 * ERROR CODES: 0 - tble is invalid pointer; 1 < x or y is invalid index;
 */
int get_cell(struct table* tble, int x, int y);

#endif 
