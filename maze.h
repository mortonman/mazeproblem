#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdbool.h>
#include "location.h"

/*
This file represents the "maze" struct.

A maze object consists of a starting location, an ending location, and a list
of valid locations.  It does not contain any functions which might help you
solve the maze.

The list of valid locations should be stored as an array, and its length
kept in the variable valid_location_count.

The function maze_destroy() should free any memory being used by invoking
location_destroy() on each valid location in the list.

maze_get_start() can be used to retrieve the starting location for the maze.

maze_is_end() can be used to check if a given location matches the end
location for the maze.

maze_is_valid() tells you if a given location exists in the list of valid
locations.

location_start and location_end are the starting and ending locations of
the maze, respectively.
*/

struct maze
{
    struct location *valid_locations;
    int valid_location_count;
    struct location location_start, location_end;
};
/*
Purpose: To malloc and create a maze.
Returns: A pointer to a maze with the values passed to the function.
*/
struct maze* maze_create(struct location *init_valid_locations,
                        int valid_location_count,
                        struct location init_location_start,
                        struct location init_location_end);
/*
Purpose: To free a maze and its components.
Precondition: A previously malloc'd maze with a previously malloc'd location array.
Postcondition: The maze and its location array are free'd.
Variables:
struct maze *maze	the maze to be free'd
*/
void maze_destroy(struct maze *maze);
/*
Purpose: To get the start location of a maze.
Precondition: A maze with a valid start location.
Variables:
struct maze maze	the maze from which the start location will be taken.
Returns: the locatoin_start of the maze.
*/
struct location maze_get_start(struct maze maze);
/*
Purpose: Checks if a locatoin is in the maze.
Variables:
struct maze maze	the maze from which the location array will be taken.
struct location loc	the location that is to be searched for in the maze.
Returns: true if the location is in the maze, otherwise false.
*/
bool maze_is_valid(struct maze maze, struct location loc);
/*
Purpose: Checks if a locatoin is equal to the end of the maze.
Variables:
struct maze maze	the maze from which the end location will be taken.
struct location loc	the location that is to be compared the the mazes end.
Returns: true if the location equal to the maze's end location, otherwise false.
*/
bool maze_is_end(struct maze maze, struct location loc);

#endif
