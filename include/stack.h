#ifndef STACK_H
#define STACK_H

#include <stdio.h>

typedef struct snode snode;

struct snode
{
    void *elem;
    snode *next;
};

typedef struct
{
    snode *top;
    size_t size;
    size_t elem_size;
} stack;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a stack */
/* Takes as arguments a pointer to the stack and the size of the element */
void stack_init(stack *, const size_t);

/* Cleans up resources */
/* Takes a stack pointer as an argument */
void stack_destroy(stack *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Adds an element to the stack. To push an item onto the stack, */
/* it must be an lvalue (have an address) */
#define spush(st,el) _spush(st,&(el))
void _spush(stack *, const void *);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes an element from top of the stack */
void spop(stack *);

/* --------------------------------------------- */
/*               Access to elements              */
/* --------------------------------------------- */

/* Returns the element from the top of the stack */
/* takes as arguments a pointer to the stack and an element type */
#define top(st,type) (*((type *)_top(st)))
void *_top(const stack *);

/* --------------------------------------------- */
/*               Changing elements               */
/* --------------------------------------------- */

/* Swaps the contents of two stacks */
void sswap(stack *, stack *);

/* --------------------------------------------- */
/*               Stack information               */
/* --------------------------------------------- */

/* Returns the size of the stack */
size_t ssize(const stack *);

/* Returns a positive value if the stack is empty and zero otherwise */
unsigned sempty(const stack *);

#endif