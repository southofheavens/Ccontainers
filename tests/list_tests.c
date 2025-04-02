#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"

#define LIST_INIT_SIZE 10

/* --------------------------------------------------------------------------- */

/* comparator for sorting (ascending) */
const int comp_asc(const void *f, const void *s)
{
    return (*(int *)f - *(int *)s);
}

/* comparator for sorting (descending) */
const int comp_desc(const void *f, const void *s)
{
    return (*(int *)s - *(int *)f);
}

/* --------------------------------------------------------------------------- */
/* -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- */
/* --------------------------------------------------------------------------- */

void adding_and_deleting_elements_tests(void)
{
    list lst;
    list_init(&lst);

    lpush_back(&lst,4);
    lpush_back(&lst,5);
    lpush_back(&lst,6);
    lpush_front(&lst,3);
    lpush_front(&lst,2);
    lpush_front(&lst,1);

    list_iterator it;
    size_t i;
    i = 1;
    for (it = lbegin(&lst); it != lend(&lst); ladvance(&it,1)) {
        assert(lderef(it) == i++);
    }

    lpop_back(&lst);
    lpop_front(&lst);

    i = 2;
    for (it = lbegin(&lst); it != lend(&lst); ladvance(&it,1)) {
        assert(lderef(it) == i++);
    }

    it = lbegin(&lst);
    ladvance(&it,2);
    linsert(&lst,it,100);
    linsert(&lst,it,200);

    it = lbegin(&lst);
    assert(lderef(it) == 2);
    ladvance(&it,1);
    assert(lderef(it) == 3);
    ladvance(&it,1);
    assert(lderef(it) == 100);
    ladvance(&it,1);
    assert(lderef(it) == 200);
    ladvance(&it,1);
    assert(lderef(it) == 4);
    ladvance(&it,1);
    assert(lderef(it) == 5);
    ladvance(&it,1);
    assert(it == lend(&lst));

    it = lfind(&lst,100);
    if (it != lend(&lst)) {
        lerase(&lst,it);
    }

    it = lfind(&lst,200);
    if (it != lend(&lst)) {
        lerase(&lst,it);
    }

    it = lbegin(&lst);
    linsert(&lst,it,1);

    it = lend(&lst);
    linsert(&lst,it,6);

    i = 1;
    for (it = lbegin(&lst); it != lend(&lst); ladvance(&it,1)) {
        assert(lderef(it) == i++);
    }

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void changing_the_size_tests(void)
{
    list lst;
    list_init(&lst);

    size_t i;
    for (i = 0; i < LIST_INIT_SIZE; ++i) {
        lpush_back(&lst,i);
    }

    assert(lsize(&lst) == 10);

    lresize(&lst,12);
    assert(lsize(&lst) == 12);

    list_iterator it;
    it = lend(&lst);
    ladvance(&it,-1);
    assert(lderef(it) == 0);
    ladvance(&it,-1);
    assert(lderef(it) == 0);
    ladvance(&it,-1);
    assert(lderef(it) == 9);

    lresize(&lst,8);
    assert(lsize(&lst) == 8);

    size_t list_size;
    list_size = lsize(&lst);
    for (i = 0; i < list_size; ++i) 
    {
        assert(lderef(lbegin(&lst)) == i);
        lpop_front(&lst);
    }

    assert(lsize(&lst) == 0);
    assert(lempty(&lst));

    lresize(&lst, LIST_INIT_SIZE);
    assert(lsize(&lst) == LIST_INIT_SIZE); 

    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i)
    {
        assert(lderef(it) == 0);    
        ladvance(&it,1);
    }

    lclear(&lst);
    assert(lsize(&lst) == 0);   //
    assert(lempty(&lst));

    lpush_back(&lst,5);
    lpush_front(&lst,-5);
    assert(lsize(&lst) == 2);

    lclear(&lst);
    assert(lsize(&lst) == 0);
    assert(lempty(&lst));

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void access_to_elements_tests(void)
{
    list lst;
    list_init(&lst);

    lpush_back(&lst,100);
    lpush_front(&lst,50);
    lpush_back(&lst,150);

    assert(lfront(&lst) == 50);
    assert(lback(&lst) == 150);

    lpop_back(&lst);

    assert(lfront(&lst) == 50);
    assert(lback(&lst) == 100);

    lpop_back(&lst);

    assert(lfront(&lst) == 50);
    assert(lback(&lst) == 50);

    lpop_back(&lst);

    assert(lempty(&lst));

    list_iterator it;
    it = lbegin(&lst);
    linsert(&lst,it,5);

    assert(lfront(&lst) == 5);
    assert(lback(&lst) == 5);

    lpop_back(&lst);

    assert(lempty(&lst));

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void changing_elements_tests(void)
{
    list lst;
    list_init(&lst);

    size_t i;
    for (i = 0; i < LIST_INIT_SIZE; ++i) {
        lpush_back(&lst, i);
    }
    /* Now the lst looks like this: 0 1 2 3 4 5 6 7 8 9 */

    list_iterator it;
    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i) 
    {
        lset(it, pow(i,2));
        ladvance(&it,1);
    }
    /* And now the lst looks like this: 0 1 4 9 16 25 36 49 64 81 */

    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i) 
    {
        assert(lderef(it) == pow(i,2));
        ladvance(&it,1);
    }

    lassign_single(&lst, LIST_INIT_SIZE / 2, 5);
    /* And now: 5 5 5 5 5 */

    assert(lsize(&lst) == LIST_INIT_SIZE / 2);

    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i) 
    {
        assert(lderef(it) == 5);
        ladvance(&it,1);
    }

    int val;
    val = 6;
    size_t list_size;
    list_size = lsize(&lst);
    for (i = 0; i < list_size; ++i) {
        lpush_back(&lst, val++);
    }
    /* And now: 5 5 5 5 5 6 7 8 9 10 */

    assert(lsize(&lst) == LIST_INIT_SIZE);

    val = 6;
    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i)
    {
        if (i < 5) {
            assert(lderef(it) == 5);
        }
        else {
            assert(lderef(it) == val++);
        }
        ladvance(&it,1);
    }

    list_size = lsize(&lst);
    for (i = 0; i < list_size / 2; ++i) {
        lpop_front(&lst);
    }
    /* And now: 6 7 8 9 10 */

    assert(lsize(&lst) == LIST_INIT_SIZE / 2);
    val = 6;
    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i) 
    {
        assert(lderef(it) == val++);
        ladvance(&it,1);
    }

    list lst2;
    list_init(&lst2);

    lassign_range(&lst2, lbegin(&lst), lend(&lst));
    /* Now the lst2 looks like this: 6 7 8 9 10 */

    assert(lsize(&lst2) == lsize(&lst));
    val = 6;
    it = lbegin(&lst2);
    for (i = 0; i < lsize(&lst2); ++i) 
    {
        assert(lderef(it) == val++);
        ladvance(&it,1);
    }

    val = 5;
    list_size = lsize(&lst2);
    for (i = 0; i < list_size; ++i) {
        lpush_front(&lst2, val--);
    }
    /* And now the lst2 looks like this: 1 2 3 4 5 6 7 8 9 10 */

    assert(lsize(&lst2) == LIST_INIT_SIZE);
    val = 1;
    it = lbegin(&lst2);
    for (i = 0; i < lsize(&lst2); ++i)
    {
        assert(lderef(it) == val++);
        ladvance(&it,1);
    }

    lswap(&lst,&lst2);
    /* Now the lst looks like this: 1 2 3 4 5 6 7 8 9 10 */
    /* And the lst2 looks like this: 6 7 8 9 10 */

    assert(lsize(&lst) == LIST_INIT_SIZE);
    assert(lsize(&lst2) == LIST_INIT_SIZE / 2);

    val = 1;
    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i)
    {
        assert(lderef(it) == val++);
        ladvance(&it,1);
    }

    val = 6;
    it = lbegin(&lst2);
    for (i = 0; i < lsize(&lst2); ++i)
    {
        assert(lderef(it) == val++);
        ladvance(&it,1);
    }

    lswap(&lst,&lst2);
    /* Bring it all back */

    lassign_single(&lst,0,100); /* equivalent to lclear */
    assert(lempty(&lst)); 

    lassign_range(&lst, lbegin(&lst2), lend(&lst2));
    /* Now the lst looks like this: 1 2 3 4 5 6 7 8 9 10 */
    /* And the lst2 looks like this: 1 2 3 4 5 6 7 8 9 10 */

    assert(lsize(&lst) == LIST_INIT_SIZE);
    assert(lsize(&lst) == lsize(&lst2));

    val = 1;
    it = lbegin(&lst);
    list_iterator it2;
    it2 = lbegin(&lst2);
    for (i = 0; i < lsize(&lst); ++i)
    {
        assert(lderef(it) == val);
        assert(lderef(it2) == val++);
        ladvance(&it,1);
        ladvance(&it2,1);
    }

    list_destroy(&lst2);
    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void working_with_iterators_tests(void)
{
    list lst;
    list_init(&lst);

    /* lst is empty */
    assert(lbegin(&lst) == lend(&lst));

    lpush_back(&lst,1);

    /* lst is not empty */
    assert(lbegin(&lst) != lend(&lst));

    lpop_back(&lst);

    /* lst is empty again */
    assert(lbegin(&lst) == lend(&lst));

    lpush_front(&lst,1);

    /* lst is not empty again */
    assert(lbegin(&lst) != lend(&lst));

    lpop_front(&lst);

    /* lst is empty again... */
    assert(lbegin(&lst) == lend(&lst));

    size_t i;
    for (i = 0; i < LIST_INIT_SIZE; ++i) {
        lpush_back(&lst,i);
    }
    /* Now the list looks like: 0 1 2 3 4 5 6 7 8 9 */

    list_iterator it;
    it = lbegin(&lst);
    ladvance(&it,lsize(&lst));

    assert(it == lend(&lst));

    ladvance(&it,-1);

    assert(lderef(it) == 9);

    ladvance(&it,-5);

    assert(lderef(it) == 4);

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void sorting_tests(void)
{
    srand(time(NULL));
    int min = -100;
    int max = 100;

    list lst;
    list_init(&lst);

    size_t i;
    for (i = 0; i < LIST_INIT_SIZE; ++i) {
        lpush_back(&lst, (rand() % (max - min + 1)) + min);
    }

    /* Sorted the list in ascending order */
    lsort(&lst, comp_asc);

    list_iterator it, it2;
    it = lbegin(&lst);
    it2 = lbegin(&lst);
    ladvance(&it2,1);
    for (i = 0; i < lsize(&lst) - 1; ++i)
    {
        assert(lderef(it) <= lderef(it2));
        ladvance(&it,1);
        ladvance(&it2,1);
    }

    /* Sorted the list in descending order */
    lsort(&lst, comp_desc);

    it = lbegin(&lst);
    it2 = lbegin(&lst);
    ladvance(&it2,1);
    for (i = 0; i < lsize(&lst) - 1; ++i)
    {
        assert(lderef(it) >= lderef(it2));
        ladvance(&it,1);
        ladvance(&it2,1);
    }

    lclear(&lst);

    /* Let's see what happens if the list is empty */
    lsort(&lst,comp_asc);

    lpush_back(&lst,2);

    /* Let's see what happens if there is one element in the list */
    lsort(&lst,comp_asc);

    lpush_back(&lst,1);

    /* Let's see what happens if there are two elements in the list */
    lsort(&lst,comp_asc);

    it = lbegin(&lst);
    it2 = lbegin(&lst);
    ladvance(&it2,1);

    assert(lderef(it) <= lderef(it2));

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

int main(void)
{
    printf(GREEN "RUNNING LIST TESTS" RED "\n");

    adding_and_deleting_elements_tests();
    changing_the_size_tests();
    access_to_elements_tests();
    changing_elements_tests();
    working_with_iterators_tests();
    sorting_tests();

    printf(GREEN "ALL TESTS WITH LIST PASSED SUCCESSFULLY" RED "\n");
    return EXIT_SUCCESS;
}
