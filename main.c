#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>
#include <math.h>

#define VEC_INIT_SIZE 10

int comp(const void *f, const void *s)
{
    return (*(int *)f - *(int *)s);
}

int main() 
{
    vector vector_int;
    vector_init(&vector_int, sizeof(int));

    int insert_elem;

    insert_elem = 5;
    vpush_back(&vector_int, insert_elem);
    insert_elem = 10;
    vpush_back(&vector_int,insert_elem);
    insert_elem = 15;
    vpush_back(&vector_int,insert_elem);

    int search_elem;
    search_elem = 10;
    vec_iterator it = vfind(&vector_int,search_elem,comp);

    if (it != vend(&vector_int)) {
        printf("элемент найден\n");
    }

    vector_destroy(&vector_int);
    return 0;
}