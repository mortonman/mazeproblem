#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdbool.h>
#include <assert.h>
#include "location.h"

//predeclaration
struct locationstacknode;
	
/*
This file represents two data structures:  a "locationstack" and "locationstacknode".

The struct(s) in question implements a simple stack of location objects. There
is no templating functionality; only location objects are allowed.  It can
grow and shrink dynamically as necessary.

The functions stack_push(), stack_pop(), and stack_get_top() provide
standard stack functionality.  **NOTE** that in the event of an unsatisfied
precondition when calling these functions, the program should crash using
assert() from <assert.h>!!  stack_is_empty() checks if the stack is empty,
and stack_is_on() tells you if the given location is on the stack.

The stack should be implemented with a linked list, however the head of
the list should represent the top of the stack (i.e., the side you insert
and remove from).  However, stack_print() should print the stack from
bottom to top.  This will require a tricky solution, think carefully.
*/

struct locationstack 
{
    struct locationstacknode *top; //default value must be NULL
};
/*
Purpose: to create a locationstack.
Returns: A pointer to a struct locationstack with top set to NULL.
*/
struct locationstack *locationstack_create();
/*
Purpose: insert a locationstacknode on the top of the locationstack.
Precondition: A non-NULL pointer to a locationstack.
Postcondition: The locationstack's top is set to a new locationstacknode 
with location loc and its next pointer is set to the old top.
Variables: 
struct locationstack *stack	a pointer to the stack that the new node is being pushed onto
struct location loc		the loc to be assigned to the new locationstacknode
*/
void locationstack_push(struct locationstack *stack, struct location loc);
/*
Purpose: remove the locationstacknode on the top of the locationstack.
Precondition: A non-NULL pointer to a locationstack. With a non-NULL top.
Postcondition: The node on the top of the stack is free'd and the next node is set 
to be the new top. 
with location loc and its next pointer is set to the old top.
Variables: 
struct locationstack *stack	a pointer to the stack that the new node is being popped from
*/
void locationstack_pop(struct locationstack *stack);
/*
Purpose: get the location of the top node on the the locationstack.
Precondition: A non-NULL pointer to a locationstack.
Variables: 
struct locationstack stack	the stack that the new node is being pushed onto
Returns: the location of the top variable of the stack.
*/
const struct location locationstack_get_top(struct locationstack stack);
/*
Purpose: check if the stack is empty.
Precondition: A non-NULL pointer to a locationstack.
Variables: 
struct locationstack stack	the stack that is being checked
Returns: true if top is NULL, otherwise false.
*/
bool locationstack_is_empty(struct locationstack stack);
/*
Purpose: check if a location is on the stack.
Precondition: A non-NULL pointer to a locationstack.
Variables: 
struct locationstack stack	the stack that is being checked
struct location loc		the location which is being searched for
Returns: true if the node is on the stack, otherwise false.
*/
bool locationstack_is_on(struct locationstack stack, struct location loc);
/*
Purpose: print the locations on the stack from bottom to top.
Precondition: A non-NULL pointer to a locationstack. 
Postcondition: the location of each node in the stack is printed
along with the direction moved between each location.
Variables: 
struct locationstack stack	the stack to be printed
*/
void locationstack_print(struct locationstack stack);
/*
Purpose: free the stack and its nodes.
Precondition: A pointer to a previously malloced locationstack. 
Postcondition: the stack will be free'd along with any nodes.
Variables: 
struct locationstack *stack	the stack pointer to be free'd
*/
void locationstack_destroy(struct locationstack *stack);

/*
This struct represents a single node on a locationstack.  The next pointer
points to the node below it on the stack (or NULL, if the node is on the
bottom of the stack).

You must use locationstacknode_create() and locationstacknode_destroy()
to create and destroy instances of the struct, including in implementations
of locationstack-related functions.

Getter/setter functions are self-explanatory.
*/

struct locationstacknode
{
    struct location loc;
    struct locationstacknode *next;
};

/*
Purpose: to create a locationstacknode.
Variables:
const struct location loc 	the location for the locationstacknode
struct locationstacknode *next	a pointer to the next locationstacknode
Returns: A pointer to a struct locationstacknode with the location and next pointer passed to the function.
*/
struct locationstacknode *locationstacknode_create(const struct location loc, struct locationstacknode *next);
/*
Purpose: to free a locationstacknode.
Precondition: a previously malloc'd locationstacknode.
Postcondition: the locationstacknode is free'd
Variables:
struct locationstacknode *node	a the node to be free'd
*/
void locationstacknode_destroy(struct locationstacknode *node);
/*
Purpose: get the location from a locationstacknode.
Precondition: a locationstacknode with an itialized location.
Variables:
struct locationstacknode node	the node that the location will be taken from
Returns: the location from the locationstacknode.
*/
const struct location locationstacknode_get_location(struct locationstacknode node);
/*
Purpose: get the next locationstacknode of a locationstacknode.
Precondition: a locationstacknode with an itialized next pointer.
Variables:
struct locationstacknode node	the node that the location will be taken from
Returns: the location from the locationstacknode.
*/
struct locationstacknode* locationstacknode_get_next(struct locationstacknode node);
/*
Purpose: set the next next pointer of a locationstacknode to a given value.
Precondition: A non-NULL pointer to a locationstacknode.
Postcondition: the next pointer of the firstlocationstacknode is set equal to the delta_next pointer.
Variables:
struct locationstacknode *node 		a pointer to the node
struct locationstacknode *delta_next
*/
void locationstacknode_set_next(struct locationstacknode *node, struct locationstacknode *delta_next);

#endif
