#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

typedef struct qnode qnode;

struct qnode
{
    qnode *next;
    qnode *prev;
    int elem;
};

typedef struct
{
    qnode *head;
    qnode *tail;
    size_t size;
} queue;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a queue */
void queue_init(queue *);

/* Cleans up resources */
void queue_destroy(queue *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Adds an element to the end of a queue */
void qpush(queue *, int);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes an element from the front of the queue. */
void qpop(queue *);

/* --------------------------------------------- */
/*               Access to elements              */
/* --------------------------------------------- */

/* Returns the first element of the queue */
int qfront(const queue *);

/* Returns the last element of the queue */
int qback(const queue *);

/* --------------------------------------------- */
/*               Changing elements               */
/* --------------------------------------------- */

/* Swaps the contents of two queues */
void qswap(queue *, queue *);

/* --------------------------------------------- */
/*               Queue information               */
/* --------------------------------------------- */

/* Returns the size of the queue */
size_t qsize(queue *);

/* Returns a positive value if the queue is empty and zero otherwise */
unsigned qempty(const queue *);

#endif