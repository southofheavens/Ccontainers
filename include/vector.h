#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

typedef struct
{
    void **elems;
    size_t capacity;
    size_t size;
    size_t elem_size;
} vector;

typedef void **vec_iterator;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a vector */
/* Takes as arguments a pointer to the vector and the element type size */
void vector_init(vector *, const size_t);

/* Cleans up resources */
/* Takes a pointer to a vector as an argument */
void vector_destroy(vector *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Adds an element to the end of a vector */
/* Takes as arguments a pointer to a vector and the variable we want to add */
/* The variable we want to add must be lvalue (have an address) */
#define vpush_back(vec,el) _vpush_back(vec,&(el))
void _vpush_back(vector *, const void *);

/* Inserts an element into a vector before the iterator */
/* Takes as arguments a pointer to a vector, an iterator, and the variable we want to add */
/* The variable we want to add must be lvalue (have an address) */
#define vinsert(vec,it,el) _vinsert(vec,it,&(el))
void _vinsert(vector *, const vec_iterator, const void *);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes the last element of a vector */
/* Takes a pointer to a vector as an argument */
void vpop_back(vector *);

/* Removes the vector element located at the iterator */
/* Takes a pointer to a vector and an iterator as arguments */
void verase(vector *, vec_iterator);

/* --------------------------------------------- */
/*            Changing the size/capacity         */
/* --------------------------------------------- */

/* Changes the size of a vector */
/* Takes as arguments a pointer to a vector, a new size, and a variable whose value */
/* will be used by default if the new size is larger than the current size of the vector */
/* Variable must be lvalue (have an address) */
#define vresize(vec,new_size,el) _vresize(vec,new_size,&(el))
void _vresize(vector *, const size_t, const void *);

/* Clears the vector but does not change the capacity */
/* Takes a pointer to a vector as an argument */
void vclear(vector *);

/* Reserves memory for vector elements */
/* Takes as arguments a pointer to a vector and a new capacity */
void reserve(vector *, const size_t);

/* --------------------------------------------- */
/*               Access to elements              */
/* --------------------------------------------- */

/* Returns a value to a vector element at index */
/* Takes as arguments a pointer to a vector, an index, and a return type (the type of */
/* elements stored in the vector) */
#define vat(vec,ind,type) (*((type *)_vat(vec,ind)))
void *_vat(const vector *, const size_t);

/* Returns the first element of the vector */
/* Takes as arguments a pointer to a vector, and a return type (the type of elements */
/* stored in the vector) */
#define vfront(vec,type) (*((type *)_vfront(vec)))
void *_vfront(const vector *);

/* Returns the last element of the vector */
/* Takes as arguments a pointer to a vector, and a return type (the type of elements */
/* stored in the vector) */
#define vback(vec,type) (*((type *)_vback(vec)))
void *_vback(const vector *);

/* --------------------------------------------- */
/*               Changing elements               */
/* --------------------------------------------- */

/* Changes the value of a vector at an index */
/* Takes as arguments a pointer to a vector, an index, and a variable whose value will be */
/* used as the new value of the variable located at the specified index */
/* Variable must be lvalue (have an address) */
#define vset(vec,ind,el) _vset(vec,ind,&(el))
void _vset(vector *, const size_t, const void *);

/* Changes the value of the element pointed to by the iterator */
/* Takes as arguments a pointer to a vector, an iterator, and a variable whose value will be */
/* used as the new value of the variable pointed to by the iterator */
/* Variable must be lvalue (have an address) */
#define vset_it(vec,it,el) _vset_it(vec,it,&(el))
void _vset_it(vector *, vec_iterator, const void *);

/* Replaces the contents of a vector with arg3, repeating it arg2 times */
/* Takes as arguments a pointer to a vector, the number of elements, and a variable */
/* whose value will be used to fill the vector */
/* Variable must be lvalue (have an address) */
#define vassign_single(vec,count,el) _vassign_single(vec,count,&(el))
void _vassign_single(vector *, const size_t, const void *);

/* Replaces the contents of a vector with elements from a half-open range ("[a,b)") */
/* specified by iterators */
/* Takes as arguments a pointer to a vector and two iterators begin and end */
void vassign_range(vector *, const vec_iterator, const vec_iterator);

/* Swaps the contents of two vectors */
/* Takes pointers to vectors as arguments */
void vswap(vector *, vector *);

/* --------------------------------------------- */
/*             Working with iterators            */
/* --------------------------------------------- */

/* Returns an iterator pointing to the first element of the vector */
/* Takes a pointer to a vector as an argument */
vec_iterator vbegin(const vector *);

/* Returns an iterator pointing to the element following the last one */
/* Takes a pointer to a vector as an argument */
vec_iterator vend(const vector *);

/* Moves the iterator by the specified number of elements */
/* Takes as arguments an iterator and the number of shifts (a negative number means */
/* we move backwards, a positive number means we move forward) */
void vadvance(vec_iterator *, const int);

/* Returns the value of the element pointed to by the iterator (dereference iterator) */
/* Takes as arguments an iterator and a return type (the type of the element the iterator */
/* points to) */
#define vderef(it, type) *((type *)_vderef(it))
void *_vderef(const vec_iterator);

/* --------------------------------------------- */
/*              Vector information               */
/* --------------------------------------------- */

/* Returns the size of the vector */
/* Takes a pointer to a vector as an argument */
size_t vsize(const vector *);

/* Returns the capacity of a vector */
/* Takes a pointer to a vector as an argument */
size_t capacity(const vector *);

/* Returns a positive value if the vector is empty and zero otherwise */
/* Takes a pointer to a vector as an argument */
unsigned vempty(const vector *);

/* --------------------------------------------- */
/*               Sorting / search                */
/* --------------------------------------------- */

/* Sorts a vector */
/* Takes a pointer to a vector and a comparator as arguments */
void vsort(vector *, int (*)(const void *, const void *));

/* Finds an element in a vector */
/* Takes as arguments a pointer to a vector, an element and a comparator */
/* Variable must be lvalue (have an address) */
#define vfind(vec,el,comp) _vfind(vec, &(el), comp)
vec_iterator _vfind(const vector *, const void *, int (*)(const void*, const void*));

/* --------------------------------------------- */
/*              Auxiliary functions              */
/* --------------------------------------------- */

/* Reallocates memory for void **elems */
/* Takes as arguments a pointer to a vector and a new capacity */
static void vrealloc(vector *, const size_t);

#endif 