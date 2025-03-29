#include <stack.h>
#include <stdlib.h>
#include <memory.h>
#include <utility.h>

void stack_init(stack *st, const size_t elem_size)
{
    check_null_pointers("stack_init: a null pointer was "
        "received as an argument", 1, st);

    st->size = 0;
    st->top = NULL;
    st->elem_size = elem_size;
}

void stack_destroy(stack *st)
{
    check_null_pointers("stack_destroy: a null pointer was "
        "received as an argument", 1, st);

    snode *curr = st->top;
    while (curr != NULL)
    {
        snode *next = curr->next;
        free(curr->elem);
        free(curr);
        curr = next;
    }
}

void _spush(stack *st, const void *elem)
{
    check_null_pointers("spush: a null pointer was "
        "received as an argument", 2, st, elem);

    snode *new_node = (snode *)malloc(sizeof(snode));
    check_null_pointers("bad alloc", 1, new_node);

    new_node->elem = malloc(st->elem_size);
    check_null_pointers("bad alloc", 1, new_node->elem);

    memcpy(new_node->elem,elem,st->elem_size);
    new_node->next = st->top;
    st->top = new_node;
    st->size++;
}

void spop(stack *st)
{
    check_null_pointers("spop: a null pointer was "
        "received as an argument", 1, st);
    
    snode *del_node = st->top;
    if (del_node == NULL)
    {
        fprintf(stderr, "spop: stack is empty");
        exit(EXIT_FAILURE);
    }
    st->top = del_node->next;
    free(del_node->elem);
    free(del_node);
    st->size--;
}

void *_top(const stack *st)
{
    check_null_pointers("top: a null pointer was "
        "received as an argument", 1, st);

    if (st->top == NULL)
    {
        fprintf(stderr, "top: stack is empty");
        exit(EXIT_FAILURE);
    }
    return st->top->elem;
}

void sswap(stack *f, stack *s)
{
    check_null_pointers("sswap: a null pointer was "
        "received as an argument", 2, f, s);

    stack temp = *f;
    *f = *s;
    *s = temp;
}

size_t ssize(const stack *st)
{
    check_null_pointers("ssize: a null pointer was "
        "received as an argument", 1, st);

    return st->size;
}

unsigned sempty(const stack *st)
{
    check_null_pointers("sempty: a null pointer was "
        "received as an argument", 1, st);
    
    return (st->size == 0 ? 1 : 0);
}