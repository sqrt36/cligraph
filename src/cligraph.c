/*
 * cligraph.c is part of cligraph.
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
 * cligraph.c 
 *
 * AUTHOR: Noah Harvey
 *
 * VERSION: v0.0.1
 *
 * DESCRIPTION: main source file for cligraph
 */

#include <stdio.h>

#include "stringmath.h"
#include "parsemath.h"

int main(int argc, char const *argv[])
{
	char tststr[100];	
	printf("expression:\n");
	scanf("%s",tststr);
	printf("indpvar:\n");
	double val[100]; 
	scanf("%lf",val);
	
	char* tmp = expndexpr(tststr);
	double value = getvalue(tmp,*val);

	printf("value is: %f\n", value);
	return 0;
}
