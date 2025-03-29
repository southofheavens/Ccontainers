#include <queue.h>
#include <stdlib.h>
#include <utility.h>

void queue_init(queue *qu)
{
    check_null_pointers("queue_init: a null pointer was " 
        "received as an argument", 1, qu);

    qu->head = NULL;
    qu->tail = NULL;
    qu->size = 0;
}

void queue_destroy(queue *qu)
{
    check_null_pointers("queue_destroy: a null pointer was " 
        "received as an argument", 1, qu);
    
    qnode *curr = qu->tail;
    while (curr != NULL)
    {
        qnode *next = curr->next;
        free(curr);
        curr = next;
    }
}

void qpush(queue *qu, int elem)
{
    check_null_pointers("qpush: a null pointer was " 
        "received as an argument", 1, qu);
    
    if (qu->size == 0)
    {
        qu->head = qu->tail = (qnode *)malloc(sizeof(qnode));
        check_null_pointers("bad alloc", 1, qu->head);
    
        qu->tail->elem = elem;
        qu->tail->prev = NULL;
        qu->tail->next = NULL;
    }
    else
    {
        qnode *new_tail = (qnode *)malloc(sizeof(qnode));
        check_null_pointers("bad alloc", 1, new_tail);

        new_tail->elem = elem;
        new_tail->prev = NULL;
        new_tail->next = qu->tail;
        qu->tail->prev = new_tail;
        qu->tail = new_tail;
    }
    qu->size++;
}

void qpop(queue *qu)
{
    check_null_pointers("qpop: a null pointer was " 
        "received as an argument", 1, qu);

    if (qu->size == 0)
    {
        fprintf(stderr, "qpop: queue is empty");
        exit(EXIT_FAILURE);
    }

    if (qu->size == 1)
    {
        free(qu->head);
        qu->head = qu->tail = NULL;
    }
    else
    {
        qnode *prev_head = qu->head->prev;
        free(qu->head);
        qu->head = prev_head;
    }
    qu->size--;
}

int qfront(const queue *qu)
{
    check_null_pointers("qfront: a null pointer was " 
        "received as an argument", 1, qu);

    if (qu->size == 0)
    {
        fprintf(stderr, "qfront: queue is empty");
        exit(EXIT_FAILURE);
    }

    return qu->head->elem;
}

int qback(const queue *qu)
{
    check_null_pointers("qback: a null pointer was " 
        "received as an argument", 1, qu);
    
    if (qu->size == 0)
    {
        fprintf(stderr, "qback: queue is empty");
        exit(EXIT_FAILURE);
    }

    return qu->tail->elem;
}

void qswap(queue *f, queue *s)
{
    check_null_pointers("qswap: a null pointer was " 
        "received as an argument", 2, f, s);

    queue temp = *f;
    *f = *s;
    *s = temp;
}

size_t qsize(queue *qu)
{
    check_null_pointers("qsize: a null pointer was " 
        "received as an argument", 1, qu);

    return qu->size;
}

unsigned qempty(const queue *qu)
{
    check_null_pointers("qempty: a null pointer was " 
        "received as an argument", 1, qu);

    return (qu->size == 0 ? 1 : 0);
}