#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"

#define LIST_INIT_SIZE 10

/* --------------------------------------------------------------------------- */

/* comparator for searching element in a list that stores int values */
int comp_find_int(const void *f, const void *s)
{
    return (*(int *)f == *(int *)s ? 1 : 0);
}

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

/* comparator for searching element in a list that stores char * values */
int comp_find_str(const void *f, const void *s)
{
    return ((strcmp(*(char **)f, *(char **)s)) == 0 ? 1 : 0);
}

/* comparator for sorting a list that stores char * values (ascending) */
int comp_asc_str(const void *f, const void *s)
{   
    return strcmp(*(char **)f, *(char **)s);
}

/* comparator for sorting a list that stores char * values (descending) */
int comp_desc_str(const void *f, const void *s)
{
    int result_of_strcmp = strcmp(*(char **)f, *(char **)s);

    if (result_of_strcmp > 0) {
        return -1;
    }
    else if (result_of_strcmp < 0) {
        return 1;
    }
    return 0;
}

/* --------------------------------------------------------------------------- */
/* -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- */
/* --------------------------------------------------------------------------- */

void general_adding_and_deleting_elements_tests(void)
{
    list lst;
    list_init(&lst, sizeof(int));

    int insert_element;

    insert_element = 4;
    lpush_back(&lst,insert_element);

    insert_element = 5;
    lpush_back(&lst,insert_element);

    insert_element = 6;
    lpush_back(&lst,insert_element);

    insert_element = 3;
    lpush_front(&lst,insert_element);

    insert_element = 2;
    lpush_front(&lst,insert_element);

    insert_element = 1;
    lpush_front(&lst,insert_element);

    list_iterator it;
    size_t i;
    i = 1;
    for (it = lbegin(&lst); it != lend(&lst); ladvance(&it,1)) {
        assert(lderef(it,int) == i++);
    }

    lpop_back(&lst);
    lpop_front(&lst);

    i = 2;
    for (it = lbegin(&lst); it != lend(&lst); ladvance(&it,1)) {
        assert(lderef(it,int) == i++);
    }

    it = lbegin(&lst);
    ladvance(&it,2);

    insert_element = 100;
    linsert(&lst,it,insert_element);

    insert_element = 200;
    linsert(&lst,it,insert_element);

    it = lbegin(&lst);
    assert(lderef(it,int) == 2);
    ladvance(&it,1);
    assert(lderef(it,int) == 3);
    ladvance(&it,1);
    assert(lderef(it,int) == 100);
    ladvance(&it,1);
    assert(lderef(it,int) == 200);
    ladvance(&it,1);
    assert(lderef(it,int) == 4);
    ladvance(&it,1);
    assert(lderef(it,int) == 5);
    ladvance(&it,1);
    assert(it == lend(&lst));

    int find_elem;
    find_elem = 100;
    it = lfind(&lst,find_elem,comp_find_int);
    if (it != lend(&lst)) {
        lerase(&lst,it);
    }

    find_elem = 200;
    it = lfind(&lst,find_elem,comp_find_int);
    if (it != lend(&lst)) {
        lerase(&lst,it);
    }

    it = lbegin(&lst);
    insert_element = 1;
    linsert(&lst,it,insert_element);

    it = lend(&lst);
    insert_element = 6;
    linsert(&lst,it,insert_element);

    i = 1;
    for (it = lbegin(&lst); it != lend(&lst); ladvance(&it,1)) {
        assert(lderef(it,int) == i++);
    }

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void general_changing_the_size_tests(void)
{
    list lst;
    list_init(&lst, sizeof(int));

    size_t i;
    for (i = 0; i < LIST_INIT_SIZE; ++i) {
        lpush_back(&lst,i);
    }

    assert(lsize(&lst) == 10);

    int default_elem;
    default_elem = 0;
    lresize(&lst,12,default_elem);
    assert(lsize(&lst) == 12);

    list_iterator it;
    it = lend(&lst);
    ladvance(&it,-1);
    assert(lderef(it,int) == 0);
    ladvance(&it,-1);
    assert(lderef(it,int) == 0);
    ladvance(&it,-1);
    assert(lderef(it,int) == 9);

    lresize(&lst,8,default_elem);
    assert(lsize(&lst) == 8);

    size_t list_size;
    list_size = lsize(&lst);
    for (i = 0; i < list_size; ++i) 
    {
        assert(lderef(lbegin(&lst),int) == i);
        lpop_front(&lst);
    }

    assert(lsize(&lst) == 0);
    assert(lempty(&lst));

    lresize(&lst, LIST_INIT_SIZE, default_elem);
    assert(lsize(&lst) == LIST_INIT_SIZE); 

    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i)
    {
        assert(lderef(it,int) == 0);    
        ladvance(&it,1);
    }

    lclear(&lst);
    assert(lsize(&lst) == 0);   //
    assert(lempty(&lst));

    int insert_elem;
    insert_elem = 5;
    lpush_back(&lst,insert_elem);
    insert_elem = -5;
    lpush_front(&lst,insert_elem);
    assert(lsize(&lst) == 2);

    lclear(&lst);
    assert(lsize(&lst) == 0);
    assert(lempty(&lst));

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void general_access_to_elements_tests(void)
{
    list lst;
    list_init(&lst, sizeof(int));

    int insert_elem;

    insert_elem = 100;
    lpush_back(&lst,insert_elem);

    insert_elem = 50;
    lpush_front(&lst,insert_elem);

    insert_elem = 150;
    lpush_back(&lst,insert_elem);

    assert(lfront(&lst,int) == 50);
    assert(lback(&lst,int) == 150);

    lpop_back(&lst);

    assert(lfront(&lst,int) == 50);
    assert(lback(&lst,int) == 100);

    lpop_back(&lst);

    assert(lfront(&lst,int) == 50);
    assert(lback(&lst,int) == 50);

    lpop_back(&lst);

    assert(lempty(&lst));

    list_iterator it;
    it = lbegin(&lst);

    insert_elem = 5;
    linsert(&lst,it,insert_elem);

    assert(lfront(&lst,int) == 5);
    assert(lback(&lst,int) == 5);

    lpop_back(&lst);

    assert(lempty(&lst));

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void general_changing_elements_tests(void)
{
    list lst;
    list_init(&lst, sizeof(int));

    size_t i;
    for (i = 0; i < LIST_INIT_SIZE; ++i) {
        lpush_back(&lst, i);
    }
    /* Now the lst looks like this: 0 1 2 3 4 5 6 7 8 9 */

    int insert_elem;
    list_iterator it;
    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i) 
    {
        insert_elem = pow(i,2);
        lset(&lst, it, insert_elem);
        ladvance(&it,1);
    }
    /* And now the lst looks like this: 0 1 4 9 16 25 36 49 64 81 */

    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i) 
    {
        assert(lderef(it,int) == pow(i,2));
        ladvance(&it,1);
    }

    int assign_elem;
    assign_elem = 5;
    lassign_single(&lst, LIST_INIT_SIZE / 2, assign_elem);
    /* And now: 5 5 5 5 5 */

    assert(lsize(&lst) == LIST_INIT_SIZE / 2);

    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i) 
    {
        assert(lderef(it,int) == 5);
        ladvance(&it,1);
    }

    int val;
    val = 6;
    size_t list_size;
    list_size = lsize(&lst);
    for (i = 0; i < list_size; ++i, ++val) {
        lpush_back(&lst, val);
    }
    /* And now: 5 5 5 5 5 6 7 8 9 10 */

    assert(lsize(&lst) == LIST_INIT_SIZE);

    val = 6;
    it = lbegin(&lst);
    for (i = 0; i < lsize(&lst); ++i)
    {
        if (i < 5) {
            assert(lderef(it,int) == 5);
        }
        else {
            assert(lderef(it,int) == val++);
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
        assert(lderef(it,int) == val++);
        ladvance(&it,1);
    }

    list lst2;
    list_init(&lst2, sizeof(int));

    lassign_range(&lst2, lbegin(&lst), lend(&lst));
    /* Now the lst2 looks like this: 6 7 8 9 10 */

    assert(lsize(&lst2) == lsize(&lst));
    val = 6;
    it = lbegin(&lst2);
    for (i = 0; i < lsize(&lst2); ++i) 
    {
        assert(lderef(it,int) == val++);
        ladvance(&it,1);
    }

    val = 5;
    list_size = lsize(&lst2);
    for (i = 0; i < list_size; ++i, --val) {
        lpush_front(&lst2, val);
    }
    /* And now the lst2 looks like this: 1 2 3 4 5 6 7 8 9 10 */

    assert(lsize(&lst2) == LIST_INIT_SIZE);
    val = 1;
    it = lbegin(&lst2);
    for (i = 0; i < lsize(&lst2); ++i)
    {
        assert(lderef(it,int) == val++);
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
        assert(lderef(it,int) == val++);
        ladvance(&it,1);
    }

    val = 6;
    it = lbegin(&lst2);
    for (i = 0; i < lsize(&lst2); ++i)
    {
        assert(lderef(it,int) == val++);
        ladvance(&it,1);
    }

    lswap(&lst,&lst2);
    /* Bring it all back */

    assign_elem = 100;
    lassign_single(&lst,0,assign_elem); /* equivalent to lclear */
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
        assert(lderef(it,int) == val);
        assert(lderef(it2,int) == val++);
        ladvance(&it,1);
        ladvance(&it2,1);
    }

    list_destroy(&lst2);
    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void general_working_with_iterators_tests(void)
{
    list lst;
    list_init(&lst,sizeof(int));

    /* lst is empty */
    assert(lbegin(&lst) == lend(&lst));

    int insert_elem;

    insert_elem = 1;
    lpush_back(&lst,insert_elem);

    /* lst is not empty */
    assert(lbegin(&lst) != lend(&lst));

    lpop_back(&lst);

    /* lst is empty again */
    assert(lbegin(&lst) == lend(&lst));

    insert_elem = 1;
    lpush_front(&lst,insert_elem);

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

    assert(lderef(it,int) == 9);

    ladvance(&it,-5);

    assert(lderef(it,int) == 4);

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

void general_sorting_tests(void)
{
    srand(time(NULL));
    int min = -100;
    int max = 100;

    list lst;
    list_init(&lst, sizeof(int));

    size_t i;
    int insert_elem;
    for (i = 0; i < LIST_INIT_SIZE; ++i) 
    {
        insert_elem = (rand() % (max - min + 1)) + min;
        lpush_back(&lst, insert_elem);
    }

    /* Sorted the list in ascending order */
    lsort(&lst, comp_asc);

    list_iterator it, it2;
    it = lbegin(&lst);
    it2 = lbegin(&lst);
    ladvance(&it2,1);
    for (i = 0; i < lsize(&lst) - 1; ++i)
    {
        assert(lderef(it,int) <= lderef(it2,int));
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
        assert(lderef(it,int) >= lderef(it2,int));
        ladvance(&it,1);
        ladvance(&it2,1);
    }

    lclear(&lst);

    /* Let's see what happens if the list is empty */
    lsort(&lst,comp_asc);

    insert_elem = 2;
    lpush_back(&lst,insert_elem);

    /* Let's see what happens if there is one element in the list */
    lsort(&lst,comp_asc);

    insert_elem = 1;
    lpush_back(&lst,insert_elem);

    /* Let's see what happens if there are two elements in the list */
    lsort(&lst,comp_asc);

    it = lbegin(&lst);
    it2 = lbegin(&lst);
    ladvance(&it2,1);

    assert(lderef(it,int) <= lderef(it2,int));

    list_destroy(&lst);
}

/* --------------------------------------------------------------------------- */

#define ASSIGN_INIT_SIZE_1 100
#define ASSIGN_INIT_SIZE_2 1000
#define ASSIGN_INIT_SIZE_3 10000

void general_assign_tests(void)
{
    list lst1;
    list_init(&lst1,sizeof(int));

    int assign_elem;
    assign_elem = 5;

    lassign_single(&lst1, ASSIGN_INIT_SIZE_2, assign_elem);
    assert(lsize(&lst1) == ASSIGN_INIT_SIZE_2);

    lassign_single(&lst1, ASSIGN_INIT_SIZE_1, assign_elem);
    assert(lsize(&lst1) == ASSIGN_INIT_SIZE_1);

    lassign_single(&lst1, ASSIGN_INIT_SIZE_3, assign_elem);
    assert(lsize(&lst1) == ASSIGN_INIT_SIZE_3);

    lassign_single(&lst1, 0, assign_elem);
    assert(lempty(&lst1));

    list lst2;
    list_init(&lst2,sizeof(int));

    lassign_single(&lst1, ASSIGN_INIT_SIZE_2, assign_elem);
    lassign_range(&lst2, lbegin(&lst1), lend(&lst1));
    assert(lsize(&lst2) == ASSIGN_INIT_SIZE_2);

    lassign_single(&lst1, ASSIGN_INIT_SIZE_1, assign_elem);
    lassign_range(&lst2, lbegin(&lst1), lend(&lst1));
    assert(lsize(&lst2) == ASSIGN_INIT_SIZE_1);

    lassign_single(&lst1, ASSIGN_INIT_SIZE_3, assign_elem);
    lassign_range(&lst2, lbegin(&lst1), lend(&lst1));
    assert(lsize(&lst2) == ASSIGN_INIT_SIZE_3);

    lassign_single(&lst1, 0, assign_elem);
    lassign_range(&lst2, lbegin(&lst1), lend(&lst1));
    assert(lempty(&lst2));

    lassign_single(&lst1, ASSIGN_INIT_SIZE_3, assign_elem);
    lassign_range(&lst2, lbegin(&lst1), lend(&lst1));
    assert(lsize(&lst2) == ASSIGN_INIT_SIZE_3);

    list_destroy(&lst2);
    list_destroy(&lst1);
}

/* --------------------------------------------------------------------------- */

#define SOME_WORDS_ARRAY_LENGTH      15
#define LEXICOGRAPHICALLY_FIRST_WORD "Apple"
#define LEXICOGRAPHICALLY_LAST_WORD  "Zombie"

void string_list_tests(void)
{
    char *some_words[SOME_WORDS_ARRAY_LENGTH] = 
    {
        "House", "River", "Happy", "Table", "Music", 
        "Light", "Green", "Water", "Friend", "Book", 
        "Apple", "Watch", "Zombie", "Chair", "Umbrella"
    };

    list string_list;
    list_init(&string_list,sizeof(char *));

    size_t i;
    for (i = 0; i < SOME_WORDS_ARRAY_LENGTH; ++i) {
        lpush_back(&string_list,some_words[i]);
    }

    assert(lsize(&string_list) == SOME_WORDS_ARRAY_LENGTH);

    list_iterator it;
    it = lbegin(&string_list);
    for (i = 0; i < lsize(&string_list); ++i) 
    {
        assert(strcmp(some_words[i],lderef(it,char *)) == 0);
        ladvance(&it,1);
    }

    char *find_elem = "Friend";
    it = lfind(&string_list, find_elem, comp_find_str);
    assert(it != lend(&string_list));

    char *find_elem2 = "Elephant";
    it = lfind(&string_list, find_elem2, comp_find_str);
    assert(it == lend(&string_list));

    lsort(&string_list, comp_asc_str);
    
    assert(strcmp(lfront(&string_list,char *), LEXICOGRAPHICALLY_FIRST_WORD) == 0);
    assert(strcmp(lback(&string_list,char *), LEXICOGRAPHICALLY_LAST_WORD) == 0);

    lsort(&string_list, comp_desc_str);

    assert(strcmp(lfront(&string_list,char *), LEXICOGRAPHICALLY_LAST_WORD) == 0);
    assert(strcmp(lback(&string_list,char *), LEXICOGRAPHICALLY_FIRST_WORD) == 0);

    it = lbegin(&string_list);
    ladvance(&it,2);
    assert(strcmp(lderef(it,char *), "Watch") == 0);

    char *assign_elem = "ASSIGN";
    lassign_single(&string_list,LIST_INIT_SIZE,assign_elem);

    char *insert_elem = "INSERT";
    it = lbegin(&string_list);
    ladvance(&it,5);
    lset(&string_list,it,insert_elem);

    it = lbegin(&string_list);
    for (i = 0; i < lsize(&string_list); ++i) 
    {
        if (i != 5) {
            assert(strcmp(lderef(it,char *), assign_elem) == 0);
        }
        else {
            assert(strcmp(lderef(it,char* ), insert_elem) == 0);
        }
        ladvance(&it,1);
    }

    list_destroy(&string_list);
}

/* --------------------------------------------------------------------------- */

#define MATRIX_INIT_SIZE 3

void lst_list_tests(void)
{
    list lst_list;
    list_init(&lst_list,sizeof(list));

    size_t i;
    int val;

    list first_row;
    list_init(&first_row,sizeof(int));
    val = 1;
    for (i = 0; i < MATRIX_INIT_SIZE; ++i, ++val) {
        lpush_back(&first_row,val);
    }

    list second_row;
    list_init(&second_row,sizeof(int));
    for (i = 0; i < MATRIX_INIT_SIZE; ++i, ++val) {
        lpush_back(&second_row,val);
    }

    list third_row;
    list_init(&third_row,sizeof(int));
    for (i = 0; i < MATRIX_INIT_SIZE; ++i, ++val) {
        lpush_back(&third_row,val);
    }

    lpush_back(&lst_list, first_row);
    lpush_back(&lst_list, second_row);
    lpush_back(&lst_list, third_row);

    /* Now matrix looks like */
    /* 1 2 3 */
    /* 4 5 6 */
    /* 7 8 9 */

    /* --------------- */

    size_t j;
    val = 1;
    list_iterator it_row, it_col;
    it_row = lbegin(&lst_list);
    for (it_row = lbegin(&lst_list); it_row != lend(&lst_list); ladvance(&it_row,1))
    {
        list curr_row;
        curr_row = lderef(it_row,list);
        for (it_col = lbegin(&curr_row); it_col != lend(&curr_row); ladvance(&it_col,1)) {
            assert(lderef(it_col,int) == val++);
        }
    }

    list_destroy(&third_row);
    list_destroy(&second_row);
    list_destroy(&first_row);
    list_destroy(&lst_list);
}

/* --------------------------------------------------------------------------- */

int main(void)
{
    printf(GREEN "RUNNING LIST TESTS" RED "\n");

    general_adding_and_deleting_elements_tests();
    general_changing_the_size_tests();
    general_access_to_elements_tests();
    general_changing_elements_tests();
    general_working_with_iterators_tests();
    general_sorting_tests();
    general_assign_tests();
    string_list_tests();
    lst_list_tests();

    printf(GREEN "ALL TESTS WITH LIST PASSED SUCCESSFULLY" RED "\n");
    return EXIT_SUCCESS;
}
