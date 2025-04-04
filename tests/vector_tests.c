#include <vector.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"

#define VEC_INIT_SIZE 10

/* --------------------------------------------------------------------------- */

/* comparator for searching element in a vector that stores int values */
int comp_find_int(const void *f, const void *s)
{
    return (*(int *)f == *(int *)s ? 1 : 0);
}

/* comparator for sorting a vector that stores int values (ascending) */
int comp_asc_int(const void *f, const void *s)
{
    void **first_elem_pointer = (void **)f;
    void **second_elem_pointer = (void **)s;

    return (vderef(first_elem_pointer, int) - vderef(second_elem_pointer, int));
}

/* comparator for sorting a vector that stores int values (descending) */
int comp_desc_int(const void *f, const void *s)
{
    void **first_elem_pointer = (void **)f;
    void **second_elem_pointer = (void **)s;

    return (vderef(second_elem_pointer, int) - vderef(first_elem_pointer, int));
}

/* comparator for searching element in a vector that stores char * values */
int comp_find_str(const void *f, const void *s)
{
    return ((strcmp(*(char **)f, *(char **)s)) == 0 ? 1 : 0);
}

/* comparator for sorting a vector that stores char * values (ascending) */
int comp_asc_str(const void *f, const void *s)
{
    void **first_elem_pointer = (void **)f;
    void **second_elem_pointer = (void **)s;
    
    return strcmp(vderef(first_elem_pointer, char *), vderef(second_elem_pointer, char *));
}

/* comparator for sorting a vector that stores char * values (descending) */
int comp_desc_str(const void *f, const void *s)
{
    void **first_elem_pointer = (void **)f;
    void **second_elem_pointer = (void **)s;
    int result_of_strcmp = strcmp(vderef(first_elem_pointer, char *), 
        vderef(second_elem_pointer, char *));

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

    /* Now the vec looks like this: 2 3 100 200 4 5 */
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
    it = vfind(&vec,find_elem,comp_find_int);
    if (it != vend(&vec)) {
        verase(&vec,it);
    }

    find_elem = 200;
    it = vfind(&vec,find_elem,comp_find_int);
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

    i = 1;
    for (it = vbegin(&vec); it != vend(&vec); vadvance(&it,1)) {
        assert(vderef(it,int) == i++);
    }

    vector_destroy(&vec);
}

/* --------------------------------------------------------------------------- */

void general_changing_the_size_and_capacity_tests(void)
{
    vector vec;
    vector_init(&vec, sizeof(int));

    /* Size */

    size_t i;
    for (i = 0; i < VEC_INIT_SIZE; ++i) {
        vpush_back(&vec,i);
    }

    assert(vsize(&vec) == 10);

    int default_value;
    default_value = 0;

    vresize(&vec,12,default_value);
    assert(vsize(&vec) == 12);

    vec_iterator it;
    it = vend(&vec);

    vadvance(&it,-1);
    assert(vderef(it,int) == 0);

    vadvance(&it,-1);
    assert(vderef(it,int) == 0);

    vadvance(&it,-1);
    assert(vderef(it,int) == 9);
    
    vresize(&vec,8,default_value);
    assert(vsize(&vec) == 8);

    size_t vec_size;
    vec_size = vsize(&vec);
    for (i = 0; i < vec_size; ++i)
    {
        assert(vderef(vbegin(&vec),int) == i);
        verase(&vec,vbegin(&vec));
    }

    assert(vempty(&vec));

    vresize(&vec, VEC_INIT_SIZE, default_value);
    assert(vsize(&vec) == VEC_INIT_SIZE);

    it = vbegin(&vec);
    for (i = 0; i < vsize(&vec); ++i)
    {
        assert(vderef(it,int) == 0);
        vadvance(&it,1);
    }

    vclear(&vec);
    assert(vempty(&vec));

    int insert_elem;
    insert_elem = 5;
    vpush_back(&vec,insert_elem);
    it = vbegin(&vec);
    insert_elem = -5;
    vinsert(&vec,it,insert_elem);
    assert(vsize(&vec) == 2);

    vclear(&vec);
    assert(vempty(&vec));

    /* Capacity */

    size_t curr_capacity = capacity(&vec);
    for (i = 0; i < curr_capacity; ++i) {
        vpush_back(&vec,i);
    }

    assert(curr_capacity == capacity(&vec));
    
    insert_elem = 100;
    vpush_back(&vec,insert_elem);

    /* Now after adding an element the capacity should be twice as big */
    /* as curr_capacity */
    assert(capacity(&vec) == 2*curr_capacity);

    reserve(&vec,curr_capacity);
    /* After this, the vector capacity should not change, since it */
    /* is greater than the requested capacity. */

    assert(capacity(&vec) != curr_capacity);

    reserve(&vec,4*curr_capacity);
    /* But after this, the vector capacity must change, since it is */
    /* less than the requested capacity. */

    assert(capacity(&vec) == 4*curr_capacity);

    vector_destroy(&vec);
}

/* --------------------------------------------------------------------------- */

void general_access_to_elements_tests(void)
{
    vector vec;
    vector_init(&vec,sizeof(int));

    int insert_elem;
    insert_elem = 50;
    vpush_back(&vec,insert_elem);
    insert_elem = 100;
    vpush_back(&vec,insert_elem);
    insert_elem = 150;
    vpush_back(&vec,insert_elem);

    assert(vfront(&vec,int) == 50);
    assert(vback(&vec,int) == 150);

    vpop_back(&vec);

    assert(vfront(&vec,int) == 50);
    assert(vback(&vec,int) == 100);

    vpop_back(&vec);

    assert(vfront(&vec,int) == 50);
    assert(vback(&vec,int) == 50);

    vpop_back(&vec);

    assert(vempty(&vec));

    vec_iterator it;
    it = vbegin(&vec);
    insert_elem = 5;
    vinsert(&vec,it,insert_elem);

    assert(vfront(&vec,int) == 5);
    assert(vback(&vec,int) == 5);

    vpop_back(&vec);

    assert(vempty(&vec));

    size_t i;
    for (i = 0; i < VEC_INIT_SIZE; ++i) 
    {
        insert_elem = pow(i,2);
        vpush_back(&vec,insert_elem);
    }

    for (i = 0; i < vsize(&vec); ++i) {
        assert(vat(&vec,i,int) == pow(i,2));
    }

    vector_destroy(&vec);
}

/* --------------------------------------------------------------------------- */

void general_changing_elements_tests(void)
{
    vector vec;
    vector_init(&vec, sizeof(int));

    size_t i;
    for (i = 0; i < VEC_INIT_SIZE; ++i) {
        vpush_back(&vec, i);
    }
    /* Now the vec looks like this: 0 1 2 3 4 5 6 7 8 9 */

    vec_iterator it;
    it = vbegin(&vec);
    int insert_elem;
    for (i = 0; i < vsize(&vec); ++i) 
    {
        insert_elem = pow(i,2);
        vset_it(&vec,it,insert_elem);
        vadvance(&it,1);
    }
    /* And now the vec looks like this: 0 1 4 9 16 25 36 49 64 81 */

    it = vbegin(&vec);
    for (i = 0; i < vsize(&vec); ++i)
    {
        assert(vderef(it,int) == pow(i,2));
        vadvance(&it,1);
    }

    for (i = 0; i < vsize(&vec); ++i) 
    {
        insert_elem = pow(i,3);
        vset(&vec, i, insert_elem);
    }
    /* And now the vec look like this: 0 1 8 27 64 125 216 343 512 729 */

    for (i = 0; i < vsize(&vec); ++i) {
        assert(vat(&vec,i,int) == pow(i,3));
    }

    int assign_elem;
    assign_elem = 5;
    vassign_single(&vec, VEC_INIT_SIZE / 2, assign_elem);
    /* And now: 5 5 5 5 5 */

    assert(vsize(&vec) == VEC_INIT_SIZE / 2);

    for (i = 0; i < vsize(&vec); ++i) {
        assert(vat(&vec,i,int) == 5);
    }

    int val;
    val = 6;
    size_t vec_size;
    vec_size = vsize(&vec);
    for (i = 0; i < vec_size; ++i) 
    {
        vpush_back(&vec, val);
        val++;
    }
    /* And now: 5 5 5 5 5 6 7 8 9 10 */

    assert(vsize(&vec) == VEC_INIT_SIZE);

    val = 6;
    for (i = 0; i < vsize(&vec); ++i)
    {
        if (i < 5) {
            assert(vat(&vec,i,int) == 5);
        }
        else {
            assert(vat(&vec,i,int) == val++);
        }
    }

    vec_size = vsize(&vec);
    for (i = 0; i < vec_size / 2; ++i)
    {
        it = vbegin(&vec);
        verase(&vec,it);
    }
    /* And now: 6 7 8 9 10 */

    val = 6;
    for (i = 0; i < vsize(&vec); ++i) {
        assert(vat(&vec,i,int) == val++);
    }

    vector vec2;
    vector_init(&vec2,sizeof(int));

    vassign_range(&vec2, vbegin(&vec), vend(&vec));
    /* Now the vec2 looks like this: 6 7 8 9 10 */

    assert(vsize(&vec2) == vsize(&vec));
    val = 6;
    for (i = 0; i < vsize(&vec2); ++i) {
        assert(vat(&vec2,i,int) == val++);
    }

    val = 5;
    vec_size = vsize(&vec2);
    for (i = 0; i < vec_size; ++i)
    {
        it = vbegin(&vec2); 
        vinsert(&vec2, it, val);
        val--;
    }
    /* And now the vec2 looks like this: 1 2 3 4 5 6 7 8 9 10 */

    assert(vsize(&vec2) == VEC_INIT_SIZE);

    val = 1;
    for (i = 0; i < vsize(&vec2); ++i) {
        assert(vat(&vec2,i,int) == val++);
    }

    vswap(&vec,&vec2);
    /* Now the vec looks like this: 1 2 3 4 5 6 7 8 9 10 */
    /* And the vec2 looks like this: 6 7 8 9 10 */

    assert(vsize(&vec) == VEC_INIT_SIZE);
    assert(vsize(&vec2) == VEC_INIT_SIZE / 2);

    val = 1;
    it = vbegin(&vec);
    for (i = 0; i < vsize(&vec); ++i)
    {
        assert(vderef(it,int) == val++);
        vadvance(&it,1);
    }

    val = 6;
    it = vbegin(&vec2);
    for (i = 0; i < vsize(&vec2); ++i)
    {
        assert(vderef(it,int) == val++);
        vadvance(&it,1);
    }

    vswap(&vec,&vec2);
    /* Bring it all back */

    assign_elem = 100;
    vassign_single(&vec,0,assign_elem); /* equivalent to lclear */
    assert(vempty(&vec));

    vassign_range(&vec, vbegin(&vec2), vend(&vec2));
    /* Now the vec looks like this: 1 2 3 4 5 6 7 8 9 10 */
    /* And the vec2 looks like this: 1 2 3 4 5 6 7 8 9 10 */

    assert(vsize(&vec) == VEC_INIT_SIZE);
    assert(vsize(&vec) == vsize(&vec2));

    val = 1;
    it = vbegin(&vec);
    vec_iterator it2;
    it2 = vbegin(&vec2);
    for (i = 0; i < vsize(&vec); ++i)
    {
        assert(vderef(it,int) == val);
        assert(vderef(it2,int) == val++);
        vadvance(&it,1);
        vadvance(&it2,1);
    }

    int find_elem = 4;
    vec_iterator assign_it_begin;
    assign_it_begin = vfind(&vec,find_elem,comp_find_int);
    
    find_elem = 9;
    vec_iterator assign_it_end;
    assign_it_end = vfind(&vec,find_elem,comp_find_int);

    vassign_range(&vec2, assign_it_begin, assign_it_end);
    /* Now the vec2 looks like this: 4 5 6 7 8 */

    assert(vsize(&vec2) == assign_it_end - assign_it_begin);

    val = 4;
    for (i = 0; i < vsize(&vec2); ++i) {
        assert(vat(&vec2,i,int) == val++);
    }

    assign_elem = 15;
    vassign_single(&vec, vsize(&vec) / 2, assign_elem);
    /* Now the vec looks like this: 15 15 15 15 15 */

    assert(vsize(&vec) == VEC_INIT_SIZE / 2);

    for (i = 0; i < vsize(&vec); ++i) {
        assert(vat(&vec,i,int) == assign_elem);
    }

    vassign_range(&vec2, vbegin(&vec), vend(&vec));
    /* Now the vec2 looks like this: 15 15 15 15 15 */

    assert(vsize(&vec2) == vsize(&vec));

    for (i = 0; i < vsize(&vec2); ++i) {
        assert(vat(&vec2,i,int) == assign_elem);
    }

    assign_elem = 25;
    vassign_single(&vec, vsize(&vec) * 6, assign_elem);
    /* Now the vec looks like this: 25 25 25 ... 25 (thirty times) */

    assert(vsize(&vec) == VEC_INIT_SIZE * 3);

    for (i = 0; i < vsize(&vec); ++i) {
        assert(vat(&vec,i,int) == assign_elem);
    }

    vassign_range(&vec2, vbegin(&vec), vend(&vec));
    /* Now the vec2 looks like this: 25 25 25 ... 25 (thirty times) */

    assert(vsize(&vec2) == vsize(&vec));

    for (i = 0; i < vsize(&vec2); ++i) {
        assert(vat(&vec2,i,int) == assign_elem);
    }

    vector_destroy(&vec2);
    vector_destroy(&vec);
}

/* --------------------------------------------------------------------------- */

#define ASSIGN_INIT_SIZE_1 100
#define ASSIGN_INIT_SIZE_2 1000
#define ASSIGN_INIT_SIZE_3 10000

void general_vassign_tests(void)
{
    vector vec1;
    vector_init(&vec1,sizeof(int));

    int assign_elem;
    assign_elem = 5;

    vassign_single(&vec1, ASSIGN_INIT_SIZE_2, assign_elem);
    assert(vsize(&vec1) == ASSIGN_INIT_SIZE_2);

    vassign_single(&vec1, ASSIGN_INIT_SIZE_1, assign_elem);
    assert(vsize(&vec1) == ASSIGN_INIT_SIZE_1);

    vassign_single(&vec1, ASSIGN_INIT_SIZE_3, assign_elem);
    assert(vsize(&vec1) == ASSIGN_INIT_SIZE_3);

    vassign_single(&vec1, 0, assign_elem);
    assert(vempty(&vec1));

    vector vec2;
    vector_init(&vec2,sizeof(int));

    vassign_single(&vec1, ASSIGN_INIT_SIZE_2, assign_elem);
    vassign_range(&vec2, vbegin(&vec1), vend(&vec1));
    assert(vsize(&vec2) == ASSIGN_INIT_SIZE_2);

    vassign_single(&vec1, ASSIGN_INIT_SIZE_1, assign_elem);
    vassign_range(&vec2, vbegin(&vec1), vend(&vec1));
    assert(vsize(&vec2) == ASSIGN_INIT_SIZE_1);

    vassign_single(&vec1, ASSIGN_INIT_SIZE_3, assign_elem);
    vassign_range(&vec2, vbegin(&vec1), vend(&vec1));
    assert(vsize(&vec2) == ASSIGN_INIT_SIZE_3);

    vassign_single(&vec1, 0, assign_elem);
    vassign_range(&vec2, vbegin(&vec1), vend(&vec1));
    assert(vempty(&vec2));

    vassign_single(&vec1, ASSIGN_INIT_SIZE_3, assign_elem);
    vassign_range(&vec2, vbegin(&vec1), vend(&vec1));
    assert(vsize(&vec2) == ASSIGN_INIT_SIZE_3);

    vector_destroy(&vec2);
    vector_destroy(&vec1);
}

/* --------------------------------------------------------------------------- */

#define SOME_WORDS_ARRAY_LENGTH      15
#define LEXICOGRAPHICALLY_FIRST_WORD "Apple"
#define LEXICOGRAPHICALLY_LAST_WORD  "Zombie"

void string_vector_tests(void)
{
    char *some_words[SOME_WORDS_ARRAY_LENGTH] = 
    {
        "House", "River", "Happy", "Table", "Music", 
        "Light", "Green", "Water", "Friend", "Book", 
        "Apple", "Watch", "Zombie", "Chair", "Umbrella"
    };

    vector str_vector;
    vector_init(&str_vector,sizeof(char *));

    size_t i;
    for (i = 0; i < SOME_WORDS_ARRAY_LENGTH; ++i) {
        vpush_back(&str_vector,some_words[i]);
    }

    assert(vsize(&str_vector) == SOME_WORDS_ARRAY_LENGTH);

    for (i = 0; i < vsize(&str_vector); ++i) {
        assert(strcmp(some_words[i],vat(&str_vector,i,char *)) == 0);
    }

    vec_iterator it;

    char *find_elem = "Friend";
    it = vfind(&str_vector, find_elem, comp_find_str);
    assert(it != vend(&str_vector));

    char *find_elem2 = "Elephant";
    it = vfind(&str_vector, find_elem2, comp_find_str);
    assert(it == vend(&str_vector));

    vsort(&str_vector, comp_asc_str);
    
    assert(strcmp(vfront(&str_vector,char *), LEXICOGRAPHICALLY_FIRST_WORD) == 0);
    assert(strcmp(vback(&str_vector,char *), LEXICOGRAPHICALLY_LAST_WORD) == 0);

    vsort(&str_vector, comp_desc_str);

    assert(strcmp(vfront(&str_vector,char *), LEXICOGRAPHICALLY_LAST_WORD) == 0);
    assert(strcmp(vback(&str_vector,char *), LEXICOGRAPHICALLY_FIRST_WORD) == 0);

    it = vbegin(&str_vector);
    vadvance(&it,2);
    assert(strcmp(vderef(it,char *), "Watch") == 0);

    char *assign_elem = "ASSIGN";
    vassign_single(&str_vector,VEC_INIT_SIZE,assign_elem);

    char *insert_elem = "INSERT";
    vset(&str_vector,5,insert_elem);

    for (i = 0; i < vsize(&str_vector); ++i) 
    {
        if (i != 5) {
            assert(strcmp(vat(&str_vector,i,char *), assign_elem) == 0);
        }
        else {
            assert(strcmp(vat(&str_vector,i,char *), insert_elem) == 0);
        }
    }

    vector_destroy(&str_vector);
}

/* --------------------------------------------------------------------------- */

#define MATRIX_INIT_SIZE 3

void vec_vector_tests(void)
{
    vector vec_vector;
    vector_init(&vec_vector, sizeof(vector));

    size_t i;
    int val;

    vector first_row;
    vector_init(&first_row, sizeof(int));
    val = 1;
    for (i = 0; i < MATRIX_INIT_SIZE; ++i, ++val) {
        vpush_back(&first_row, val);
    }

    vector second_row;
    vector_init(&second_row, sizeof(int));
    val = 4;
    for (i = 0; i < MATRIX_INIT_SIZE; ++i, ++val) {
        vpush_back(&second_row, val);
    }

    vector third_row;
    vector_init(&third_row, sizeof(int));
    val = 7;
    for (i = 0; i < MATRIX_INIT_SIZE; ++i, ++val) {
        vpush_back(&third_row, val);
    }

    vpush_back(&vec_vector, first_row);
    vpush_back(&vec_vector, second_row);
    vpush_back(&vec_vector, third_row);

    /* Now matrix looks like */
    /* 1 2 3 */
    /* 4 5 6 */
    /* 7 8 9 */

    /* --------------- */

    size_t j;
    val = 1;
    for (i = 0; i < vsize(&vec_vector); ++i)
    {
        vector curr_row;
        curr_row = vat(&vec_vector, i, vector);
        for (j = 0; j < vsize(&curr_row); ++j, ++val) {
            assert(vat(&curr_row,j,int) == val);
        }
    }

    vector_destroy(&third_row);
    vector_destroy(&second_row);
    vector_destroy(&first_row);
    vector_destroy(&vec_vector);
}

/* --------------------------------------------------------------------------- */

int main(void)
{
    printf(GREEN "RUNNING VECTOR TESTS" RED "\n");

    general_adding_and_deleting_elements_tests();
    general_changing_the_size_and_capacity_tests();
    general_access_to_elements_tests();
    general_changing_elements_tests();
    general_vassign_tests();
    string_vector_tests();
    vec_vector_tests();

    printf(GREEN "ALL TESTS WITH VECTOR PASSED SUCCESSFULLY" RED "\n");
    return EXIT_SUCCESS;
}
