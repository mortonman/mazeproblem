#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
This file represents the "location" struct.

It also provides several functions which you can use to operate on and
interact with location structs.  If we were programming in OOP in C++
or Java, these would be member functions, but since we are in C they
simply take a pointer to a location struct.

You have access to a function which iterates over the neighbors of a
location.  Two locations are neighbors if and only if their rows are
the same and columns differ by one, or if their columns are the same
and their rows differ by one.  Here's how you can print out all the
neighbors of a location called loc:

loc_start(loc);
while(!loc_isdone(loc))
{
    struct location *neighbor = loc_neighbor(loc);
    loc_print(neighbor);
}

What do these functions do?  loc_start initializes the iteration
capability of a location.  Calling loc_neighbor() on a location that
has not been initialized should fail.  loc_neighbor does three things:
creates a copy of the object passed, modifies it so that it matches the
next location in sequence, advances the iterator state of the initial
object, and finally returns the newly created location.  loc_isdone()
will tell you whether all neighbors of a location have been iterated
over.

The order of neighbor iteration is very important!  You should first
visit the neighbor to the right, then down, then left, then up.  Thus,
loc_neighbor() should never return the same location that was passed
to it (a location is never a neighbor to itself).

A location object keeps track of what iteration it is on with the states
RIGHT, DOWN, LEFT, UP, DONE, which are defined as an enum.

Two locations are equal if and only if their row and column values are
equal regardless of their iteration states.  Thus, you must use
the dedicated function loc_isequal() to compare two locations instead
if directly comparing the structs.  The iteration state of a location
should not be printed in loc_print(), and when a location is read in
from a file, only row and column data is affected.

Construction should initialize data members to reasonable values.
When you are finished with a location object you must call
loc_destroy() on it to deallocate memory.  The values of data members
should not affect the behavior of this function.
*/

struct location
{
    int row, col;
    unsigned int next_direction;
};

enum { RIGHT, DOWN, LEFT, UP, DONE };
/*
Purpose: To create a location with the given row and col values.
Variables:
int row,col		the row and column values for the new location
Returns: a pointer a location struct with the row and col values passed to the function and a next_direction value of 5.
*/
struct location* loc_create(int row, int col);
/*
Purpose: To set the next_direction value of a location to 0.
Precondition: A non-null pointer to a struct location.
Postcondition: The location's next_direction value is set to 0.
struct location *loc	the loc that's to have it's next_direction value set to 0
*/
void loc_start(struct location *loc);
/*
Purpose: To create a location that neighbors another location.
Precondition: A non-null pointer to a struct location. The location must have a next_direction value from 0 to 4.
Variables:
struct location *loc	the loc that's neighbor is to be found
Returns: A pointer to a neighbor location, if there are no neighbors left, returns NULL.
*/
struct location* loc_neighbor(struct location *loc);
/*
Purpose: To create a location that neighbors another location.
Precondition: A struct location with an initialized next_direction variable.
Variables:
struct location loc	the loc that is to be checked
Returns: If loc.next_direction is equal to 4, returns true, else returns false.
*/
bool loc_isdone(struct location loc);
/*
Purpose: To create a location that neighbors another location.
Precondition: A struct location with an initialized next_direction variable.
Variables:
struct location loc1	the first location to be compared
struct location loc2	the second location to be compared
Returns: If the row and col variables of the two locations are equal, returns true, else returns false.
*/
bool loc_isequal(struct location loc1, struct location loc2);
/*
Purpose: To free a struct location pointer.
Precondition: A previously malloc'd location pointer.
Postcondition: The location pointer to be free'd
struct location *loc	the location to be free'd
*/
void loc_destroy(struct location *loc);

#endif
