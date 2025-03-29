#ifndef MAP_H
#define MAP_H

#include <stdio.h>

typedef enum
{
    RED,
    BLACK
} tnode_colors;

typedef struct
{
    int first;
    int second;
} pair;

typedef struct tnode tnode;

struct tnode
{
    tnode *parent;      /* pointer to the parent */
    tnode *left;        /* pointer to the left child */
    tnode *right;       /* pointer to the right child */
    tnode_colors color; /* node color */
    pair kv;            /* node storing key and value */
};

typedef struct
{
    tnode *root;
    tnode *end;         /* The next node after the last node in the tree */
    size_t size;
} map;

typedef tnode * map_iterator;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a vector */
void map_init(map *);

/* Cleans up resources */
void map_destroy(map *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Inserts a key-value pair into the map */
void minsert(map *, pair);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes a node from the map */
void merase(map *, map_iterator);

/* --------------------------------------------- */
/*                Changing the size              */
/* --------------------------------------------- */

/* Clears the map */
void mclear(map *);

/* --------------------------------------------- */
/*                Other functions                */
/* --------------------------------------------- */

/* Returns the number of map elements */
size_t msize(map *);

/* Returns an iterator pointing to the first element of the map */
map_iterator mbegin(map *);

/* Returns an iterator pointing to the element following the last one */
map_iterator mend(map *);

/* Moves the iterator by the specified number of elements */
void madvance(map_iterator *, int);

/* Prints a tree */
void print_tree(map *);

/* Searches the map for a node corresponding to the specified key and returns it */
map_iterator mfind(map *, int);

/* Returns the key-value pair of the node pointed to by the iterator (dereference iterator) */
pair mderef(const map_iterator);

/* --------------------------------------------- */
/*              Auxiliary functions              */
/* --------------------------------------------- */

/* Initializes a node */
static void tnode_init(tnode *, int, int);

/* Helper function for cleaning resources occupied by tree elements */
static void remove_map_recoursive(tnode *);

/* Function to rebalance the tree after inserting an element */
static void rebalance_after_insert(map *, tnode *);

/* Function to rebalance the tree after erasing an element */
static void rebalance_after_erase(map *, tnode *);

/* Removing red node with 0 children */
static void erase_case1(map *, tnode *);

/* Removing a red or black node with 2 children */
static void erase_case2(map *, tnode *);

/* Removing a black node with 0 children */
static void erase_case3(map *, tnode *);

/* Removing a black node with 1 child */
static void erase_case4(map *, tnode *);

/* Left rotate of the tree */
static void left_rotate(map *, tnode *);

/* Right rotate of the tree */
static void right_rotate(map *, tnode *);

/* Helper function for prints a tree */
static void print_tree_helper(tnode *, unsigned);

/* Moves the iterator to the next larger element */
static void next_node(map_iterator *);

/* Moves the iterator to the next smaller element */
static void prev_node(map_iterator *);

/* -------------------------------------------------------------------------------- */
/*  These two functions are required for the mend(map *) function to work correctly */
/*                Using the end element stored in the map structure and             */
/*                     these two functions we can do the following:                 */
/* -------------------------------------------------------------------------------- */
/* map_iterator it = mend(my_map);                                                  */
/* madvance(&it,-1);                                                                */
/* -------------------------------------------------------------------------------- */
/*        After this, the iterator it points to the last element of our map.        */
/* -------------------------------------------------------------------------------- */

/* Assign the "end" element to the right node of the last element */
static void add_end(map *);

/* Remove the "end" element to the right node of the last element */
static void remove_end(map *);

#endif