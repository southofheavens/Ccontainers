#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct lnode lnode;

struct lnode    
{
    lnode *prev;
    lnode *next;
    void *elem;
};

typedef struct
{
    lnode *head;
    lnode *end;       /* element that follows tail */
    size_t size;
    size_t type_size;
} list;

typedef lnode * list_iterator;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a list */
/* Takes as arguments a pointer to the list and the element type size */
void list_init(list *, const size_t);

/* Cleans up resources */
/* Takes a pointer to a list as an argument */
void list_destroy(list *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Adds an element to the end of the list */
/* Takes as arguments a pointer to a list and a variable whose value we want to */
/* add to the list */
/* Variable must be lvalue (have an address) */
#define lpush_back(lst,var) _lpush_back(lst,&(var))
void _lpush_back(list *, const void *);

/* Adds an element to the beginning of the list */
/* Takes as arguments a pointer to a list and a variable whose value we want to */
/* add to the list */
/* Variable must be lvalue (have an address) */
#define lpush_front(lst,var) _lpush_front(lst,&(var))
void _lpush_front(list *, const void *);

/* Inserts an element into a list before the iterator */
/* Takes as arguments a pointer to a list, an iterator, and a variable whose value */
/* we want to add to the list */
/* Variable must be lvalue (have an address) */
#define linsert(lst,it,el) _linsert(lst,it,&(el))
void _linsert(list *, const list_iterator, const void *);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes the last element of a list */
/* Takes a pointer to a list as an argument */
void lpop_back(list *);

/* Removes the first element of a list */
/* Takes a pointer to a list as an argument */
void lpop_front(list *);

/* Removes the list element located at the iterator */
/* Takes a pointer to a list and an iterator as arguments */
void lerase(list *, list_iterator);

/* --------------------------------------------- */
/*               Changing the size               */
/* --------------------------------------------- */

/* Changes the size of a list */
/* Takes as arguments a pointer to a list, a new size, and a variable whose value */
/* will be used by default if the new size is larger than the current size of the list */
/* Variable must be lvalue (have an address) */
#define lresize(lst,new_size,var) _lresize(lst,new_size,&(var))
void _lresize(list *, const size_t, const void *);

/* Clears the list */
/* Takes a pointer to a list as an argument */
void lclear(list *);

/* --------------------------------------------- */
/*               Access to elements              */
/* --------------------------------------------- */

/* Returns the first element of the list */
/* Takes as arguments a pointer to a list, and a return type (the type of */
/* elements stored in the list) */
#define lfront(lst,type) (*((type *)_lfront(lst)))
void *_lfront(const list *);

/* Returns the last element of the list */
/* Takes as arguments a pointer to a list, and a return type (the type of */
/* elements stored in the list) */
#define lback(lst,type) (*((type *)_lback(lst)))
void *_lback(const list *);

/* --------------------------------------------- */
/*               Changing elements               */
/* --------------------------------------------- */

/* Replaces the value of the element pointed to by the iterator */
/* Takes as arguments a pointer to a list, an iterator, and a variable whose value will be */
/* used as the new value of the variable pointed to by the iterator */
/* Variable must be lvalue (have an address) */
#define lset(lst,it,var) _lset(lst,it,&(var))
void _lset(list *, list_iterator, const void *);

/* Replaces the contents of a list with arg3, repeating it arg2 times */
/* Takes as arguments a pointer to a list, the number of elements, and a variable */
/* whose value will be used to fill the list */
/* Variable must be lvalue (have an address) */
#define lassign_single(lst,count,var) _lassign_single(lst,count,&(var))
void _lassign_single(list *, const size_t, const void *);

/* Replaces the contents of a list with elements from a half-open range ("[a,b)") */
/* specified by iterators */
/* Takes as arguments a pointer to a vector and two iterators begin and end */
void lassign_range(list *, const list_iterator, const list_iterator);

/* Swaps the contents of two lists */
/* Takes pointers to lists as arguments */
void lswap(list *, list *);

/* --------------------------------------------- */
/*             Working with iterators            */
/* --------------------------------------------- */

/* Returns an iterator pointing to the first element of the list */
/* Takes a pointer to a list as an argument */
list_iterator lbegin(const list *);

/* Returns an iterator pointing to the element following the last one */
/* Takes a pointer to a list as an argument */
list_iterator lend(const list *);

/* Moves the iterator by the specified number of elements */
/* Takes as arguments a pointer to an iterator and the number of shifts (a negative */
/* number means we move backwards, a positive number means we move forward) */
void ladvance(list_iterator *, const int);

/* Returns the value of the element pointed to by the iterator (dereference iterator) */
/* Takes as arguments an iterator and a return type (the type of the element the iterator */
/* points to) */
#define lderef(it,type) (*((type *)_lderef(it)))
void *_lderef(const list_iterator);

/* --------------------------------------------- */
/*               List information                */
/* --------------------------------------------- */

/* Returns the size of the list */
/* Takes a pointer to a list as an argument */
size_t lsize(const list *);

/* Returns a positive value if the vector is empty and zero otherwise */
/* Takes a pointer to a list as an argument */
unsigned lempty(const list *); 

/* --------------------------------------------- */
/*               Sorting / search                */
/* --------------------------------------------- */

/* Sorts a list */
/* Takes a pointer to a list and a comparator as arguments */
void lsort(list *, int (*)(const void *, const void *));

/* Searches for an element in a list and returns an iterator pointing to the first */
/* occurrence of the element */
/* Takes as arguments a pointer to a list, a variable whose value we want to search for, */
/* and a comparator */
/* Variable must be lvalue (have an address) */
#define lfind(lst,var,comp) _lfind(lst,&(var),comp)
list_iterator _lfind(const list *, const void *, int (*)(const void *, const void *)); 

/* --------------------------------------------- */
/*              Auxiliary functions              */
/* --------------------------------------------- */

/* Helper recursive function for sorting a list */
static lnode *merge_sort(lnode *, int (*)(const void *, const void *));

/* Takes pointers to the beginning of lists and merges them into a single sorted list */
static lnode *merge(lnode *, lnode *, int (*)(const void *, const void *));

/* Takes a pointer to the head of the list, returns a pointer to the center element */
static lnode *get_middle(lnode *);

#endif