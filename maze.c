#include "maze.h"

struct maze* maze_create(struct location *init_valid_locations,
                        int valid_location_count,
                        struct location init_location_start,
                        struct location init_location_end){
	struct maze *new_maze = (struct maze *)malloc(sizeof(struct maze));
	new_maze->valid_locations = init_valid_locations;
	new_maze->valid_location_count = valid_location_count;
	new_maze->location_start = init_location_start;
	new_maze->location_end = init_location_end;
	return new_maze;
}

void maze_destroy(struct maze *maze){

	free(maze->valid_locations);
	free(maze);
}

struct location maze_get_start(struct maze maze){
	return maze.location_start;
}

bool maze_is_valid(struct maze maze, struct location loc){
	for(int i = 0; i < maze.valid_location_count; i++){
		if(loc_isequal(*(maze.valid_locations+i),loc)) return true;
	}
	return false;
}

bool maze_is_end(struct maze maze, struct location loc){
	if(loc_isequal(maze.location_end, loc)) return true;
	return false;
}
