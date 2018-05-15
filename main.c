#define _GNU_SOURCE
#include "stack.h"
#include "maze.h"
/*
The maze solver implementation goes in this file.

However, there is a special rule:  you are not allowed to directly access
or modify any of the elements of any struct you create.  In other words,
the following code is against the rules:

struct location *x = create_location(5, 5);
x.row = 6;

Your algorithm must make use only of the functions you have written in
your *.c files.
*/

void main(int argc, char *argv[]){



	if(argc <2){
		printf("Please provide a valid input file. \n");
		return;
	}

	FILE *input_file = fopen(argv[1],"r"); 
	if(!input_file){
		printf("Please provide a valid input file. \n");
		return;
	}

	//vars for creating maze
	int valid_location_count = 0;
	struct location *valid_locations;
	struct location location_start;
	struct location location_end;

	//vars for reading file
	char *line = (char *)malloc(sizeof(char)); 
	size_t size = 1;
	bool array_finished = false;
	bool start_assigned = false;
	int row,col;
	struct location *new_loc;
	int loc_count = 0;
	
	while(getline(&line, &size, input_file) != -1){ //reading file to end
		if(valid_location_count == 0){
			sscanf(line,"%i", &valid_location_count);
			valid_locations = (struct location *)malloc(sizeof(struct location)*valid_location_count);
		}else if(*line == 10){// if it is the line break between the list of locations and the start and end locations, then the array of valid locations is done.
			array_finished = true;
		}else if(!array_finished){ //if the array isn't finished scan for another loc in the array.
			sscanf(line,"%i%i", &row,&col);
			new_loc = loc_create(row, col); 
			*(valid_locations+loc_count) = *new_loc;
			loc_destroy(new_loc);
			loc_count++;
		}else{ //if the array is finished
			sscanf(line,"%i%i", &row,&col);
			if(!start_assigned){ 
				new_loc = loc_create(row, col); 
				location_start = *new_loc;
				loc_destroy(new_loc);
				start_assigned = true;
			}else{
				new_loc = loc_create(row, col); 
				location_end = *new_loc;
				loc_destroy(new_loc);
			}
		}
	}
	free(line);
	fclose(input_file); 
	//create the maze
	struct maze *input_maze = maze_create(valid_locations, valid_location_count, location_start, location_end);
	//create the stack
	struct locationstack *stack = locationstack_create();
	locationstack_push(stack, maze_get_start(*input_maze));
	struct location top = locationstack_get_top(*stack);
	struct location *probe = loc_create(0,0);	
	*probe = top;
	loc_start(probe);
	while(!maze_is_end(*input_maze, top)){// if we have not reached the end of the maze
		struct location *neighbor;
		while(loc_isequal(top,*probe) && !loc_isdone(*probe)){ // search for a valid neighbor
			neighbor = loc_neighbor(probe);
			if(maze_is_valid(*input_maze, *neighbor) && !locationstack_is_on(*stack, *neighbor)){ // if the neighbor is valid
				locationstack_pop(stack); // remove old node with unstarted loc
				locationstack_push(stack, *probe);
				loc_start(neighbor);
				locationstack_push(stack, *neighbor);
				*probe = locationstack_get_top(*stack);
			}
			loc_destroy(neighbor);

		}
		if(loc_isequal(top,*probe)){ // if the location currently on top of the stack had no valid neighbors 
			locationstack_pop(stack);
			if(locationstack_is_empty(*stack)) break;
			*probe = locationstack_get_top(*stack);
		}

		top = locationstack_get_top(*stack);
	}
	loc_destroy(probe);
	locationstack_print(*stack);
	maze_destroy(input_maze);
	locationstack_destroy(stack);
}
