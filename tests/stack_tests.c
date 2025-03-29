#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"

#define STACK_INIT_SIZE 5

typedef struct
{
    int first;
    int second;
} pair;

/* --------------------------------------------------------------------------- */

void stack_general_tests(void)
{
    stack int_stack;
    stack_init(&int_stack, sizeof(int));

    size_t i;
    for (i = 0; i < STACK_INIT_SIZE; ++i) {
        spush(&int_stack, i);
    }

    assert(ssize(&int_stack) == STACK_INIT_SIZE);

    int j;
    for (j = (int)ssize(&int_stack) - 1; j >= 0 ; --j)
    {
        assert(top(&int_stack, int) == j);
        spop(&int_stack);
    }

    assert(sempty(&int_stack));

    i = 100;
    spush(&int_stack, i);

    assert(ssize(&int_stack) == 1);
    assert(top(&int_stack, int) == 100);

    spop(&int_stack);

    assert(sempty(&int_stack));

    stack_destroy(&int_stack);
}

/* --------------------------------------------------------------------------- */

void stack_struct_pair_tests(void )
{
    stack pair_stack;
    stack_init(&pair_stack, sizeof(pair));

    pair p = {1,2};
    spush(&pair_stack,p);

    p = (pair){3,4};
    spush(&pair_stack,p);

    p = (pair){5,6};
    spush(&pair_stack,p);

    /* --------------- */

    assert(((top(&pair_stack, pair))).first == 5);
    assert(((top(&pair_stack, pair))).second == 6);

    spop(&pair_stack);

    assert(((top(&pair_stack, pair))).first == 3);
    assert(((top(&pair_stack, pair))).second == 4);

    spop(&pair_stack);

    assert(((top(&pair_stack, pair))).first == 1);
    assert(((top(&pair_stack, pair))).second == 2);

    spop(&pair_stack);

    assert(sempty(&pair_stack));

    stack_destroy(&pair_stack);
}

/* --------------------------------------------------------------------------- */

#define LENGTH_OF_THE_LONGEST_WORD 8  /* length of the word "universe" */
#define LENGTH_OF_THE_FINAL_STRING 25
#define COUNT_OF_WORDS             4

void stack_string_tests(void)
{
    stack string_stack;
    stack_init(&string_stack, sizeof(char *));

    /* Hello world and universe */
    char *u = "universe";
    char *a = "and";
    char *w = "world";
    char *h = "Hello";

    /* I know it's bad to do this, but in this case, for the sake of example, */
    /* I can do it this way, because I know that the sum of the lengths of */
    /* all words + spaces + the ending character = 25. */
    char final_phrase[LENGTH_OF_THE_FINAL_STRING]; 

    spush(&string_stack, u);
    spush(&string_stack, a);
    spush(&string_stack, w);
    spush(&string_stack, h);

    size_t i;
    for (i = 0; i < COUNT_OF_WORDS; ++i)
    {
        strcat(final_phrase, top(&string_stack, char *));
        if (i != COUNT_OF_WORDS - 1) {
            strcat(final_phrase, " ");
        }
        spop(&string_stack);
    }

    assert(sempty(&string_stack));

    assert(strcmp(final_phrase, "Hello world and universe") == 0);

    stack_destroy(&string_stack);
}

/* --------------------------------------------------------------------------- */

int main(void)
{
    printf(GREEN "RUNNING STACK TESTS" RED "\n");

    stack_general_tests();
    stack_struct_pair_tests();
    stack_string_tests();

    printf(GREEN "ALL TESTS WITH STACK PASSED SUCCESSFULLY" RED "\n");
    return EXIT_SUCCESS;
}
