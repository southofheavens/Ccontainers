#include <vector.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <utility.h>

#define VEC_INIT_CAPACITY 8

void vector_init(vector *vec, const size_t type_size)
{
    check_null_pointers("vector_init: a null pointer was "
        "received as an argument", 1, vec);

    vec->elems = NULL;
    vec->capacity = 0;
    vec->size = 0;
    vec->type_size = type_size;
}

void vector_destroy(vector *vec)
{
    check_null_pointers("vector_destroy: a null pointer was "
        "received as an argument", 1, vec);

    size_t i;
    for (i = 0; i < vec->size; ++i) {
        free(vec->elems[i]);
    }
    
    if (vec->elems) {
        free(vec->elems);
    }
}

void _vpush_back(vector *vec, const void *elem)
{
    check_null_pointers("vpush_back: a null pointer was "
        "received as an argument", 2, vec, elem);

    if (!(vec->elems))
    {
        vec->capacity = VEC_INIT_CAPACITY;
        vec->elems = malloc(vec->capacity * sizeof(void *));
        check_null_pointers("bad alloc", 1, vec->elems);

        vec->elems[vec->size] = malloc(vec->type_size);
        check_null_pointers("bad alloc", 1, vec->elems[vec->size]);

        memcpy(vec->elems[vec->size], elem, vec->type_size);
        vec->size += 1;
    }
    else
    {
        if (vec->size == vec->capacity)
        {
            vec->capacity *= 2;
            vrealloc(vec, vec->capacity);
        }

        vec->elems[vec->size] = malloc(vec->type_size);
        check_null_pointers("bad alloc", 1, vec->elems[vec->size]);

        memcpy(vec->elems[vec->size], elem, vec->type_size);
        vec->size += 1;
    }
}

void _vinsert(vector *vec, const vec_iterator it, const void *elem)
{
    check_null_pointers("vinsert: a null pointer was " 
        "received as an argument", 2, vec, elem);

    /* vec->elems is begin iterator, vec->elems+vec->size is end iterator */
    if (it && (it < vec->elems || it > vec->elems+vec->size))
    {
        fprintf(stderr, "vinsert: invalid iterator");
        exit(EXIT_FAILURE);
    }
    if (it == NULL || it == vec->elems+vec->size)
    {
        _vpush_back(vec, elem);
        return;
    }

    vec_iterator it_copy = it;
    if (vec->size == vec->capacity)
    {
        size_t iter_pos = it - vec->elems;
        vec->capacity *= 2;
        vrealloc(vec, vec->capacity);
        it_copy = vec->elems + iter_pos;
    }

    size_t i;
    for (i = vec->size; i > it_copy - vec->elems; --i) {
        vec->elems[i] = vec->elems[i-1];
    }

    *it_copy = malloc(vec->type_size);
    check_null_pointers("bad alloc", 1, *it_copy);

    memcpy(*it_copy, elem, vec->type_size);
    vec->size++;
}

void vpop_back(vector *vec)
{
    check_null_pointers("vpop_back: a null pointer was "
        "received as an argument", 1, vec);

    if (vec->size > 0) {        
        vec->size--;
    }
    else
    {
        fprintf(stderr, "vpop_back: vector is empty");
        exit(EXIT_FAILURE);
    }
}

void verase(vector *vec, vec_iterator it)
{
    check_null_pointers("verase: a null pointer was " 
        "received as an argument", 2, vec, it);

    /* vec->elems is begin iterator, vec->elems+vec->size is end iterator */    
    if (it < vec->elems || it >= vec->elems+vec->size)
    {
        fprintf(stderr, "verase: invalid iterator");
        exit(EXIT_FAILURE);
    }       

    size_t i;
    for (i = it - vec->elems; i < vec->size - 1; ++i) {
        vec->elems[i] = vec->elems[i+1];
    }
    vec->size--;
}

void _vresize(vector *vec, const size_t new_size, const void *default_value)
{
    check_null_pointers("vresize: a null pointer was " 
        "received as an argument", 2, vec, default_value);

    if (new_size > vec->capacity)
    {
        vec->capacity = new_size;
        vrealloc(vec, vec->capacity);
    }
    size_t i;
    for (i = vec->size; i < new_size; ++i) 
    {
        vec->elems[i] = malloc(vec->type_size);
        memcpy(vec->elems[i],default_value,vec->type_size); 
    }
    vec->size = new_size;
}

void vclear(vector *vec)
{
    check_null_pointers("vclear: a null pointer was " 
        "received as an argument", 1, vec);

    vec->size = 0;
}

void reserve(vector *vec, const size_t new_capacity)
{
    check_null_pointers("reserve: a null pointer was "
        "received as an argument", 1, vec);

    if (new_capacity > vec->capacity)
    {
        vec->capacity = new_capacity;
        vrealloc(vec, vec->capacity);
    }
}

void *_vat(const vector *vec, const size_t index)
{
    check_null_pointers("vat: a null pointer was " 
        "received as an argument", 1, vec);
    
    if (!(vec->elems) || index >= vec->size)
    {
        fprintf(stderr, "vat: index out of range");
        exit(EXIT_FAILURE);
    }

    return (vec->elems)[index];
}

void *_vfront(const vector *vec)
{
    check_null_pointers("vfront: a null pointer was "
        "received as an argument", 1, vec);

    if (!(vec->elems) || vec->size == 0)
    {
        fprintf(stderr, "vfront: vector is empty");
        exit(EXIT_FAILURE);
    }

    return vec->elems[0];
}

void *_vback(const vector *vec)
{
    check_null_pointers("vback: a null pointer was "
        "received as an argument", 1, vec);

    if (!(vec->elems) || vec->size == 0)
    {
        fprintf(stderr, "vback: vector is empty");
        exit(EXIT_FAILURE);
    }

    return vec->elems[vec->size - 1];
}

void _vset(vector *vec, const size_t index, const void *val)
{
    check_null_pointers("vset: a null pointer was " 
        "received as an argument", 2, vec, val);

    if (!(vec->elems) || index >= vec->size)
    {
        fprintf(stderr, "vset: index out of range");
        exit(EXIT_FAILURE);
    }

    memcpy(vec->elems[index], val, vec->type_size);
}

void _vset_it(vector *vec, vec_iterator it, const void *val)
{
    check_null_pointers("vset_it: a null pointer was "
        "received as an argument", 3, vec, it, val);
    
    memcpy(*it, val, vec->type_size);
}

void _vassign_single(vector *vec, const size_t count, const void *val)
{
    check_null_pointers("vassign_single: a null pointer was "
        "received as an argument", 2, vec, val);
    
    size_t i, vec_size;
    if (count >= vec->size)
    {
        reserve(vec, count);
        for (i = 0; i < vec->size; ++i) {
            memcpy(vec->elems[i], val, vec->type_size);
        }
        for (i = 0, vec_size = vec->size; i < count - vec_size; ++i) {
            _vpush_back(vec, val);
        }
    }
    else
    {
        vec->size = count;
        for (i = 0; i < count; ++i) {
            memcpy(vec->elems[i], val, vec->type_size);
        }
    }
}

void vassign_range(vector *vec, const vec_iterator begin, const vec_iterator end)
{
    check_null_pointers("vassign_range: a null pointer was " 
        "received as an argument", 3, vec, begin, end);

    /* vit is a begin iterator for the vector to be filled */
    /* b is a copy of the begin iterator from the half-open range */
    /* the copy is needed because the iterator from the arguments is */
    /* constant and we cannot apply vadvance to it */
    vec_iterator vit, b; 
    vit = vec->elems; /* begin iterator */
    b = begin;

    /* Number of elements in a half-open range begin-end */
    size_t elems_count;
    elems_count = 0;
    bool vector_is_over = false;

    while (b != end)
    {
        if (vit == (vec->elems+vec->size) || vector_is_over) 
        {
            vector_is_over = true;
            _vpush_back(vec,*b); 
        }
        else {
            memcpy(*vit, *b, vec->type_size); 
        }
        if (vit != vec->elems+vec->size || !vector_is_over) {
            vit += 1; /* vadvance */
        }
        b += 1; /* vadvance */
        elems_count++;
    }
    if (vec->size > elems_count) {
        vec->size = elems_count;
    }
}

void vswap(vector *vec1, vector *vec2) 
{
    check_null_pointers("vswap: a null pointer was " 
        "received as an argument", 2, vec1, vec2);

    vector temp = *vec1;
    *vec1 = *vec2;
    *vec2 = temp;
}

vec_iterator vbegin(const vector *vec)
{
    check_null_pointers("vbegin: a null pointer was "
        "received as an argument", 1, vec);

    return vec->elems;
}

vec_iterator vend(const vector *vec)
{
    check_null_pointers("vend: a null pointer was "
        "received as an argument", 1, vec);

    return vec->elems + vec->size;
}

void vadvance(vec_iterator *it, const int count)
{
    check_null_pointers("vadvance: a null pointer was " 
        "received as an argument", 1, it);

    (*it) = (*it) + count;
}

void *_vderef(const vec_iterator it)
{
    check_null_pointers("vderef: a null pointer was "
        "received as an agrument", 1, it);
    
    return *it;
}

size_t vsize(const vector *vec)
{
    check_null_pointers("vsize: a null pointer was " 
        "received as an argument", 1, vec);

    return vec->size;
}

size_t capacity(const vector *vec)
{
    check_null_pointers("capacity: a null pointer was " 
        "received as an argument", 1, vec);
    
    return vec->capacity;
}

unsigned vempty(const vector *vec)
{
    check_null_pointers("vempty: a null pointer was " 
        "received as an argument", 1, vec);

    return (vec->size == 0 ? 1 : 0);
}

void vsort(vector *vec, int (*comp)(const void *, const void *))
{
    check_null_pointers("vsort: a null pointer was " 
        "received as an argument", 2, vec, comp);

    if (vec->elems) {
        qsort(vec->elems,vec->size,sizeof(void *),comp);
    }
}

vec_iterator _vfind(const vector *vec, const void *elem, 
    int (*comp)(const void *, const void *))
{
    check_null_pointers("vfind: a null pointer was "
        "received as an argument", 3, vec, elem, comp);

    vec_iterator it;
    for (it = vec->elems; it != vec->elems+vec->size; it+=1)
    {
        if (comp(*it,elem)) {
            return it;
        }
    }
    return it;
}

static void vrealloc(vector *vec, const size_t new_capacity)
{
    vec->capacity = new_capacity;
    vec->elems = realloc(vec->elems, sizeof(void *) * vec->capacity);
    check_null_pointers("bad alloc", 1, vec->elems);
}
