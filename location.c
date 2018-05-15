#include "location.h"

/*
Add your implementation of the functions in "location.h" here.
*/

struct location* loc_create(int row, int col){
	struct location *new_loc = (struct location*)malloc(sizeof(struct location));
	new_loc->row = row;
	new_loc->col = col;
	new_loc->next_direction = 5;
	return new_loc;
}

void loc_start(struct location *loc){
	loc->next_direction = 0;
}

struct location* loc_neighbor(struct location *loc){
	struct location *neighbor_loc = loc_create(loc->row,loc->col);
	switch(loc->next_direction){
	case RIGHT:
		neighbor_loc->col++;
		break;
	case DOWN:
		neighbor_loc->row++;
		break;
	case LEFT:
		neighbor_loc->col--;
		break;
	case UP:
		neighbor_loc->row--;
		break;
	default:
		free(neighbor_loc);
		return NULL;
	}
	loc->next_direction++;
	neighbor_loc->next_direction = 5;
	return neighbor_loc;
}

bool loc_isdone(struct location loc){
	if(loc.next_direction == 4) return true;
	return false;
}

bool loc_isequal(struct location loc1, struct location loc2){
	if(loc1.row == loc2.row && loc1.col == loc2.col) return true;
	return false;
}

void loc_destroy(struct location *loc){
	free(loc);
}
