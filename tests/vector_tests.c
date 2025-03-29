#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"

#define VEC_INIT_SIZE 10

/* --------------------------------------------------------------------------- */

/* comparator for sorting (ascending) */
int comp_asc(const void *f, const void *s)
{
    return (*(int *)f - *(int *)s);
}

/* comparator for sorting (descending) */
int comp_desc(const void *f, const void *s)
{
    return (*(int *)s - *(int *)f);
}

/* --------------------------------------------------------------------------- */
/* -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- */
/* --------------------------------------------------------------------------- */

void general_adding_and_deleting_elements_tests(void)
{
    vector vec;
    vector_init(&vec,sizeof(int));

    int some_element;

    some_element = 4;
    vpush_back(&vec,some_element);
    some_element = 5;
    vpush_back(&vec,some_element);
    some_element = 6;
    vpush_back(&vec,some_element);
    
    /* Analogue of push_front */
    vec_iterator it;

    it = vbegin(&vec);
    some_element = 3;
    vinsert(&vec,it,some_element);
    
    it = vbegin(&vec);
    some_element = 2;
    vinsert(&vec,it,some_element);

    it = vbegin(&vec);
    some_element = 1;
    vinsert(&vec,it,some_element);

    size_t i;
    i = 1;
    for (it = vbegin(&vec); it != vend(&vec); vadvance(&it,1)) {
        assert(vderef(it,int) == i++);
    }

    vpop_back(&vec);
    /* Analogue of pop_front */
    it = vbegin(&vec);
    verase(&vec,it);

    i = 2;
    for (it = vbegin(&vec); it != vend(&vec); vadvance(&it,1)) {
        assert(vderef(it,int) == i++);
    }

    it = vbegin(&vec);
    vadvance(&it,2);
    some_element = 100;
    vinsert(&vec,it,some_element);
    it = vbegin(&vec);
    vadvance(&it,3);
    some_element = 200;
    vinsert(&vec,it,some_element);

    /* Now the lst looks like this: 2 3 100 200 4 5 */
    it = vbegin(&vec);
    assert(vderef(it,int) == 2);
    vadvance(&it,1);
    assert(vderef(it,int) == 3);
    vadvance(&it,1);
    assert(vderef(it,int) == 100);
    vadvance(&it,1);
    assert(vderef(it,int) == 200);
    vadvance(&it,1);
    assert(vderef(it,int) == 4);
    vadvance(&it,1);
    assert(vderef(it,int) == 5);
    vadvance(&it,1);
    assert(it == vend(&vec));

    int find_elem;
    find_elem = 100;
    it = vfind(&vec,find_elem,comp_asc);
    if (it != vend(&vec)) {
        verase(&vec,it);
    }

    find_elem = 200;
    it = vfind(&vec,find_elem,comp_asc);
    if (it != vend(&vec)) {
        verase(&vec,it);
    }

    int insert_elem;

    it = vbegin(&vec);
    insert_elem = 1;
    vinsert(&vec,it,insert_elem);

    it = vend(&vec);
    insert_elem = 6;
    vinsert(&vec,it,insert_elem);

    size_t j;
    for (j = 0; j < vsize(&vec); ++j) {
        printf("%d\n",vat(&vec,j,int));
    }
    i = 1;
    for (it = vbegin(&vec); it != vend(&vec); vadvance(&it,1)) {
        assert(vderef(it,int) == i++);
    }

    vector_destroy(&vec);
}

/* --------------------------------------------------------------------------- */

// void changing_the_size_and_capacity_tests(void)
// {
//     vector vec;
//     vector_init(&vec);

//     /* Size */

//     size_t i;
//     for (i = 0; i < VEC_INIT_SIZE; ++i) {
//         vpush_back(&vec,i);
//     }

//     assert(vsize(&vec) == 10);

//     vresize(&vec,12);
//     assert(vsize(&vec) == 12);

//     vec_iterator it;
//     it = vend(&vec);
//     vadvance(&it,-1);
//     assert(vderef(it) == 0);
//     vadvance(&it,-1);
//     assert(vderef(it) == 0);
//     vadvance(&it,-1);
//     assert(vderef(it) == 9);

//     vresize(&vec,8);
//     assert(vsize(&vec) == 8);

//     size_t vec_size;
//     vec_size = vsize(&vec);
//     for (i = 0; i < vec_size; ++i)
//     {
//         assert(vderef(vbegin(&vec)) == i);
//         verase(&vec,vbegin(&vec));
//     }

//     assert(vempty(&vec));

//     vresize(&vec, VEC_INIT_SIZE);
//     assert(vsize(&vec) == VEC_INIT_SIZE);

//     it = vbegin(&vec);
//     for (i = 0; i < vsize(&vec); ++i)
//     {
//         assert(vderef(it) == 0);
//         vadvance(&it,1);
//     }

//     vclear(&vec);
//     assert(vempty(&vec));

//     vpush_back(&vec,5);
//     it = vbegin(&vec);
//     vinsert(&vec,it,-5);
//     assert(vsize(&vec) == 2);

//     vclear(&vec);
//     assert(vempty(&vec));

//     /* Capacity */

//     size_t curr_capacity = capacity(&vec);
//     for (i = 0; i < curr_capacity; ++i) {
//         vpush_back(&vec,i);
//     }

//     assert(curr_capacity == capacity(&vec));
    
//     vpush_back(&vec,100);

//     /* Now after adding an element the capacity should be twice as big */
//     /* as curr_capacity */
//     assert(capacity(&vec) == 2*curr_capacity);

//     reserve(&vec,curr_capacity);
//     /* After this, the vector capacity should not change, since it */
//     /* is greater than the requested capacity. */

//     assert(capacity(&vec) != curr_capacity);

//     reserve(&vec,4*curr_capacity);
//     /* But after this, the vector capacity must change, since it is */
//     /* less than the requested capacity. */

//     assert(capacity(&vec) == 4*curr_capacity);

//     vector_destroy(&vec);
// }

// /* --------------------------------------------------------------------------- */

// void access_to_elements_tests(void)
// {
//     vector vec;
//     vector_init(&vec);

//     vpush_back(&vec,50);
//     vpush_back(&vec,100);
//     vpush_back(&vec,150);

//     assert(vfront(&vec) == 50);
//     assert(vback(&vec) == 150);

//     vpop_back(&vec);

//     assert(vfront(&vec) == 50);
//     assert(vback(&vec) == 100);

//     vpop_back(&vec);

//     assert(vfront(&vec) == 50);
//     assert(vback(&vec) == 50);

//     vpop_back(&vec);

//     assert(vempty(&vec));

//     vec_iterator it;
//     it = vbegin(&vec);
//     vinsert(&vec,it,5);

//     assert(vfront(&vec) == 5);
//     assert(vback(&vec) == 5);

//     vpop_back(&vec);

//     assert(vempty(&vec));

//     size_t i;
//     for (i = 0; i < VEC_INIT_SIZE; ++i) {
//         vpush_back(&vec,pow(i,2));
//     }

//     for (i = 0; i < vsize(&vec); ++i) {
//         assert(vat(&vec,i) == pow(i,2));
//     }

//     int *pelems = data(&vec);

//     for (i = 0; i < vsize(&vec); ++i) {
//         assert(vat(&vec,i) == pelems[i]);
//     }

//     vector_destroy(&vec);
// }

// /* --------------------------------------------------------------------------- */

// void changing_elements_tests(void)
// {
//     vector vec;
//     vector_init(&vec);

//     size_t i;
//     for (i = 0; i < VEC_INIT_SIZE; ++i) {
//         vpush_back(&vec, i);
//     }
//     /* Now the vec looks like this: 0 1 2 3 4 5 6 7 8 9 */

//     vec_iterator it;
//     it = vbegin(&vec);
//     for (i = 0; i < vsize(&vec); ++i) 
//     {
//         vset_it(it,pow(i,2));
//         vadvance(&it,1);
//     }
//     /* And now the vec looks like this: 0 1 4 9 16 25 36 49 64 81 */

//     it = vbegin(&vec);
//     for (i = 0; i < vsize(&vec); ++i)
//     {
//         assert(vderef(it) == pow(i,2));
//         vadvance(&it,1);
//     }

//     for (i = 0; i < vsize(&vec); ++i) {
//         vset(&vec, i, pow(i,3));
//     }
//     /* And now the vec look like this: 0 1 8 27 64 125 216 343 512 729 */

//     for (i = 0; i < vsize(&vec); ++i) {
//         assert(vat(&vec,i) == pow(i,3));
//     }

//     vassign_single(&vec, VEC_INIT_SIZE / 2, 5);
//     /* And now: 5 5 5 5 5 */

//     assert(vsize(&vec) == VEC_INIT_SIZE / 2);

//     for (i = 0; i < vsize(&vec); ++i) {
//         assert(vat(&vec,i) == 5);
//     }

//     int val;
//     val = 6;
//     size_t vec_size;
//     vec_size = vsize(&vec);
//     for (i = 0; i < vec_size; ++i) {
//         vpush_back(&vec, val++);
//     }
//     /* And now: 5 5 5 5 5 6 7 8 9 10 */

//     assert(vsize(&vec) == VEC_INIT_SIZE);

//     val = 6;
//     for (i = 0; i < vsize(&vec); ++i)
//     {
//         if (i < 5) {
//             assert(vat(&vec,i) == 5);
//         }
//         else {
//             assert(vat(&vec,i) == val++);
//         }
//     }

//     vec_size = vsize(&vec);
//     for (i = 0; i < vec_size / 2; ++i)
//     {
//         it = vbegin(&vec);
//         verase(&vec,it);
//     }
//     /* And now: 6 7 8 9 10 */

//     val = 6;
//     for (i = 0; i < vsize(&vec); ++i) {
//         assert(vat(&vec,i) == val++);
//     }

//     vector vec2;
//     vector_init(&vec2);

//     vassign_range(&vec2, vbegin(&vec), vend(&vec));
//     /* Now the vec2 looks like this: 6 7 8 9 10 */

//     assert(vsize(&vec2) == vsize(&vec));
//     val = 6;
//     for (i = 0; i < vsize(&vec2); ++i) {
//         assert(vat(&vec2,i) == val++);
//     }

//     val = 5;
//     vec_size = vsize(&vec2);
//     for (i = 0; i < vec_size; ++i)
//     {
//         it = vbegin(&vec2);
//         vinsert(&vec2, it, val--);
//     }
//     /* And now the vec2 looks like this: 1 2 3 4 5 6 7 8 9 10 */

//     assert(vsize(&vec2) == VEC_INIT_SIZE);

//     val = 1;
//     for (i = 0; i < vsize(&vec2); ++i) {
//         assert(vat(&vec2,i) == val++);
//     }

//     vswap(&vec,&vec2);
//     /* Now the vec looks like this: 1 2 3 4 5 6 7 8 9 10 */
//     /* And the vec2 looks like this: 6 7 8 9 10 */

//     assert(vsize(&vec) == VEC_INIT_SIZE);
//     assert(vsize(&vec2) == VEC_INIT_SIZE / 2);

//     val = 1;
//     it = vbegin(&vec);
//     for (i = 0; i < vsize(&vec); ++i)
//     {
//         assert(vderef(it) == val++);
//         vadvance(&it,1);
//     }

//     val = 6;
//     it = vbegin(&vec2);
//     for (i = 0; i < vsize(&vec2); ++i)
//     {
//         assert(vderef(it) == val++);
//         vadvance(&it,1);
//     }

//     vswap(&vec,&vec2);
//     /* Bring it all back */

//     vassign_single(&vec,0,100); /* equivalent to lclear */
//     assert(vempty(&vec));

//     vassign_range(&vec, vbegin(&vec2), vend(&vec2));
//     /* Now the lst looks like this: 1 2 3 4 5 6 7 8 9 10 */
//     /* And the lst2 looks like this: 1 2 3 4 5 6 7 8 9 10 */

//     assert(vsize(&vec) == VEC_INIT_SIZE);
//     assert(vsize(&vec) == vsize(&vec2));

//     val = 1;
//     it = vbegin(&vec);
//     vec_iterator it2;
//     it2 = vbegin(&vec2);
//     for (i = 0; i < vsize(&vec); ++i)
//     {
//         assert(vderef(it) == val);
//         assert(vderef(it2) == val++);
//         vadvance(&it,1);
//         vadvance(&it2,1);
//     }

//     vector_destroy(&vec2);
//     vector_destroy(&vec);
// }

/* --------------------------------------------------------------------------- */

int main(void)
{
    printf(GREEN "RUNNING VECTOR TESTS" RED "\n");

    general_adding_and_deleting_elements_tests();
    // general_changing_the_size_and_capacity_tests();
    // general_access_to_elements_tests();
    // general_changing_elements_tests();

    printf(GREEN "ALL TESTS WITH VECTOR PASSED SUCCESSFULLY" RED "\n");
    return EXIT_SUCCESS;
}
