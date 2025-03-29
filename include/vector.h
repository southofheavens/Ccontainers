#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <utility.h>

typedef struct
{
    void **elems;
    size_t capacity;
    size_t size;
    size_t elem_size;
} vector;

typedef void ** vec_iterator;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a vector */
/* Takes as arguments a pointer to the vector and the size of the element */
void vector_init(vector *, size_t);

/* Cleans up resources */
void vector_destroy(vector *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Adds an element to the end of a vector */
#define vpush_back(vec,el) _vpush_back(vec,&(el))

void _vpush_back(vector *, void *);

/* Inserts an element into a vector before the iterator */
#define vinsert(vec,it,el) _vinsert(vec,it,&(el))

void _vinsert(vector *, const vec_iterator, void *);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes the last element of a vector */
void vpop_back(vector *);

/* Removes the vector element located at the iterator */
void verase(vector *, vec_iterator);

/* --------------------------------------------- */
/*            Changing the size/capacity         */
/* --------------------------------------------- */

/* Changes the size of a vector */
void vresize(vector *, size_t);

/* Clears the vector but does not change the capacity */
void vclear(vector *);

/* Reserves memory for vector elements */
void reserve(vector *, size_t);

/* --------------------------------------------- */
/*               Access to elements              */
/* --------------------------------------------- */

/* Returns a value to a vector element at index */
#define vat(vec,ind,type) (*((type *)_vat(vec,ind)))

void *_vat(const vector *, size_t);

/* Returns the first element of the vector */
#define vfront(vec,type) (*((type *)_vfront(vec)))

void *_vfront(const vector *);

/* Returns the last element of the vector */
#define vback(vec,type) (*((type *)_vback(vec)))

void *_vback(const vector *);

/* Returns a pointer to the first element of the vector */
void **data(const vector *);

/* --------------------------------------------- */
/*               Changing elements               */
/* --------------------------------------------- */

/* Changes the value of a vector at an index */
#define vset(vec,ind,el) _vset(vec,ind,&(el))

void _vset(vector *, size_t, void *);

/* Replaces the value of the element pointed to by the iterator */
#define vset_it(it, el) _vset_it(it, &(el))

void _vset_it(vector *, vec_iterator, void *);

/* Replaces the contents of a vector with arg3, repeating it arg2 times */
#define vassign_single(vec,count,el) _vassign_single(vec,count,&(el))

void _vassign_single(vector *, size_t, void *);

/* Replaces the contents of a vector with elements from a half-open range ("[a,b)") specified by iterators */
void vassign_range(vector *, const vec_iterator, const vec_iterator);

/* Swaps the contents of two vectors */
void vswap(vector *, vector *);

/* --------------------------------------------- */
/*             Working with iterators            */
/* --------------------------------------------- */

/* Returns an iterator pointing to the first element of the vector */
vec_iterator vbegin(const vector *);

/* Returns an iterator pointing to the element following the last one */
vec_iterator vend(const vector *);

/* Moves the iterator by the specified number of elements */
void vadvance(vec_iterator *, int);

/* Returns the value of the element pointed to by the iterator (dereference iterator) */
#define vderef(it, type) *((type *)_vderef(it))

void *_vderef(vec_iterator);

/* --------------------------------------------- */
/*              Vector information               */
/* --------------------------------------------- */

/* Returns the size of the vector */
size_t vsize(const vector *);

/* Returns the capacity of a vector */
size_t capacity(const vector *);

/* Returns a positive value if the vector is empty and zero otherwise */
unsigned vempty(const vector *);

/* --------------------------------------------- */
/*               Sorting / search                */
/* --------------------------------------------- */

/* Sorts a vector */
void vsort(vector *, int (*)(const void *, const void *));

/* Takes as arguments a pointer to a vector, an element, an element type, and a comparator */
#define vfind(vec,el,comp) _vfind(vec, &(el), comp)

vec_iterator _vfind(const vector *, void *, int (*)(const void*, const void*));

/* --------------------------------------------- */
/*              Auxiliary functions              */
/* --------------------------------------------- */

/* Reallocates memory for int *elems */
/* Takes the new capacity of the vector as an argument */
static void vrealloc(vector *, size_t);

#endif 