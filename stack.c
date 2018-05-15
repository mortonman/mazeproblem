#include "stack.h"

struct locationstack *locationstack_create(){
	struct locationstack *new_stack = (struct locationstack *)malloc(sizeof(struct locationstack));
	new_stack->top = NULL;
	return new_stack;
}

void locationstack_push(struct locationstack *stack, struct location loc){
	assert(stack != NULL);
	stack->top = locationstacknode_create(loc, stack->top);
}

void locationstack_pop(struct locationstack *stack){
	assert(stack != NULL);
	assert(stack->top != NULL);
	struct locationstacknode *node_to_be_freed = stack->top;
	stack->top = stack->top->next;
	locationstacknode_destroy(node_to_be_freed);
}

const struct location locationstack_get_top(struct locationstack stack){
	assert(stack.top != NULL);
	return locationstacknode_get_location(*(stack.top));
}

bool locationstack_is_empty(struct locationstack stack){
	if(!stack.top) return true;
	return false;
}

bool locationstack_is_on(struct locationstack stack, struct location loc){
	struct locationstacknode *probe = stack.top;
	while(probe != NULL){
		if(loc_isequal(loc, locationstacknode_get_location(*probe))) return true;
		probe = probe->next;
	}
	return false;
}

void locationstack_print(struct locationstack stack){
	if(stack.top == NULL){
		printf("There is no valid solution to this maze.\n");
		return;
	}
	int counter= 0;
	struct locationstacknode *probe = stack.top;
	while(probe != NULL){
		counter++;
		probe = locationstacknode_get_next(*probe);	
	}
	struct location *locs_to_be_printed = (struct location*)malloc(sizeof(struct location)*counter);
	int number_of_locs = counter;
	counter--;
	probe = stack.top;
	while(probe != NULL){
		*(locs_to_be_printed+counter) = locationstacknode_get_location(*probe);
		counter--;
		probe = locationstacknode_get_next(*probe);
	}
	printf("START AT ");
	for(int i= 0; i<number_of_locs; i++){
		printf("\t%i %i \n", (locs_to_be_printed+i)->row,(locs_to_be_printed+i)->col);
		if(i<number_of_locs-1){
			printf("MOVE "); 
			if((locs_to_be_printed+i)->next_direction == RIGHT+1){
				printf("RIGHT");
			}else if((locs_to_be_printed+i)->next_direction == DOWN+1){
				printf("DOWN");
			}else if((locs_to_be_printed+i)->next_direction == LEFT+1){
				printf("LEFT");
			}else if((locs_to_be_printed+i)->next_direction == UP+1){
				printf("UP");
			}
			printf(" TO ");
		}
	}
	printf("FINISHED\n");
	loc_destroy(locs_to_be_printed);
}

void locationstack_destroy(struct locationstack *stack){
	struct locationstacknode* probe = stack->top;
	while(probe != NULL){
		struct locationstacknode *node_to_be_freed = probe;
		probe = locationstacknode_get_next(*probe);
		locationstacknode_destroy(node_to_be_freed);
	}
	free(stack);
	
}

struct locationstacknode *locationstacknode_create(const struct location loc, struct locationstacknode *next){
	struct locationstacknode *new_node = (struct locationstacknode *)malloc(sizeof(struct locationstacknode));
	new_node->loc = loc;
	new_node->next = next;
	return new_node;
}

void locationstacknode_destroy(struct locationstacknode *node){
	free(node);
}

const struct location locationstacknode_get_location(struct locationstacknode node){
	return node.loc;
}

struct locationstacknode* locationstacknode_get_next(struct locationstacknode node){
	return node.next;
}

void locationstacknode_set_next(struct locationstacknode *node, struct locationstacknode *delta_next){
	node->next = delta_next;
}
