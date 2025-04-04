#include <utility.h>
#include <list.h>
#include <stdlib.h>
#include <memory.h>

void list_init(list *lst, size_t type_size)
{
    check_null_pointers("list_init: a null pointer was "
        "received as an argument", 1, lst);

    lst->end = (lnode *)malloc(sizeof(lnode));
    check_null_pointers("bad alloc", 1, lst->end);

    lst->head = lst->end;
    lst->end->prev = NULL;
    lst->end->next = NULL;
    lst->size = 0;
    lst->type_size = type_size;
}

void list_destroy(list *lst)
{
    check_null_pointers("list_destroy: a null pointer was "
        "received as an argument", 1, lst);

    lnode *next;
    while (lst->head)
    {
        next = lst->head->next;
        free(lst->head->elem);
        free(lst->head);
        lst->head = next;
    }
}

void _lpush_back(list *lst, const void *elem)
{
    check_null_pointers("lpush_back: a null pointer was "
        "received as an argument", 2, lst, elem);

    if (lst->size == 0)
    {
        lst->head = (lnode *)malloc(sizeof(lnode));
        check_null_pointers("bad alloc", 1, lst->head);

        lst->head->elem = malloc(lst->type_size);
        check_null_pointers("bad alloc", 1, lst->head->elem);

        memcpy(lst->head->elem, elem, lst->type_size);
        lst->head->prev = NULL;
        lst->head->next = lst->end;
        lst->end->prev = lst->head;
    }
    else
    {
        lnode *new_node = (lnode *)malloc(sizeof(lnode));
        check_null_pointers("bad alloc", 1, new_node);

        new_node->elem = malloc(lst->type_size);
        check_null_pointers("bad alloc", 1, new_node->elem);

        memcpy(new_node->elem, elem, lst->type_size);
        new_node->prev = lst->end->prev;
        new_node->next = lst->end;
        lst->end->prev->next = new_node;
        lst->end->prev = new_node;
    }
    lst->size++;
}

void _lpush_front(list *lst, const void *elem)
{
    check_null_pointers("lpush_front: a null pointer was "
        "received as an argument", 2, lst, elem);

    if (lst->size == 0)
    {
        _lpush_back(lst,elem);
        return;
    }
    else
    {
        lnode *new_head = (lnode *)malloc(sizeof(lnode));
        check_null_pointers("bad alloc", 1, new_head);

        new_head->elem = malloc(lst->type_size);
        check_null_pointers("bad alloc", 1, new_head->elem);

        memcpy(new_head->elem, elem, lst->type_size);
        new_head->prev = NULL;
        new_head->next = lst->head;
        lst->head->prev = new_head;
        lst->head = new_head;
    }
    lst->size++;
}

void _linsert(list *lst, const list_iterator it, const void *elem)
{
    check_null_pointers("linsert: a null pointer was "
        "received as an argument", 3, lst, it, elem);

    if (it == lst->head) {
        _lpush_front(lst,elem);
    }
    else if (it == lst->end) {
        _lpush_back(lst,elem);
    }
    else
    {
        lnode *new_node = (lnode *)malloc(sizeof(lnode));
        check_null_pointers("bad alloc", 1, new_node);

        new_node->elem = malloc(lst->type_size);
        check_null_pointers("bad alloc", 1, new_node->elem);

        memcpy(new_node->elem, elem, lst->type_size);
        new_node->prev = it->prev;
        new_node->next = it;
        it->prev->next = new_node;
        it->prev = new_node;
        lst->size++;
    }
}

void lpop_back(list *lst)
{
    check_null_pointers("lpop_back: a null pointer was "
        "received as an argument", 1, lst);

    if (lst->size == 0)
    {
        fprintf(stderr, "lpop_back: list is empty");
        exit(EXIT_FAILURE);
    }
    lnode *del_prev = lst->end->prev->prev; 
    free(lst->end->prev->elem);
    free(lst->end->prev);
    if (del_prev)
    {
        del_prev->next = lst->end;
        lst->end->prev = del_prev;
    }
    else 
    {
        lst->head = lst->end;
        lst->end->prev = NULL;
    }
    lst->size--;
}

void lpop_front(list *lst)
{
    check_null_pointers("lpop_front: a null pointer was "
        "received as an argument", 1, lst);

    if (lst->size == 0)
    {
        fprintf(stderr, "lpop_front: list is empty");
        exit(EXIT_FAILURE);
    }
    lnode *del_next = lst->head->next;
    free(lst->head->elem);
    free(lst->head);
    if (del_next != lst->end)
    {
        lst->head = del_next;
        lst->head->prev = NULL;
    }
    else 
    {
        lst->head = lst->end;
        lst->end->prev = NULL;
    }
    lst->size--;
}

void lerase(list *lst, list_iterator it)
{
    check_null_pointers("lerase: a null pointer was "
        "received as an argument", 2, lst, it);

    if (it == lst->head) {
        lpop_front(lst);
    }
    else if (it == lst->end->prev) {
        lpop_back(lst);
    }
    else
    {
        lnode *del_prev = it->prev;
        del_prev->next = it->next;
        it->next->prev = del_prev;
        free(it->elem);
        free(it);
        lst->size--;
    }
}

void _lresize(list *lst, const size_t new_size, const void* default_value)
{
    check_null_pointers("lresize: a null pointer was "
        "received as an argument", 1, lst);

    size_t i;
    size_t old_size;
    old_size = lst->size;
    if (new_size > old_size) 
    {
        for (i = 0; i < new_size - old_size; ++i) {
            _lpush_back(lst,default_value);
        }
    }
    else if (new_size < old_size)
    {
        size_t i;
        lnode *prev_node, *curr_node;
        curr_node = lst->end->prev;
        for (i = 0; i < old_size - new_size; ++i) 
        {
            prev_node = curr_node->prev;
            free(curr_node->elem);
            free(curr_node);
            curr_node = prev_node;
        }
        curr_node->next = lst->end;
        lst->end->prev = curr_node;
        lst->size = new_size;
    }
}

void lclear(list *lst)
{
    check_null_pointers("lclear: a null pointer was "
        "received as an argument", 1, lst);

    if (lst->size > 0)
    {
        lst->end->prev->next = NULL;
        lst->end->prev = NULL;
        lnode *next;
        while (lst->head)
        {
            next = lst->head->next;
            free(lst->head->elem);
            free(lst->head);
            lst->head = next;
        }
        lst->head = lst->end;
        lst->size = 0;
    }
}

void *_lfront(const list *lst)
{
    check_null_pointers("lfront: a null pointer was " 
        "received as an argument", 1, lst);

    if (lst->head == lst->end) 
    {
        fprintf(stderr, "lfront: list is empty");
        exit(EXIT_FAILURE);
    }

    return lst->head->elem;
}

void *_lback(const list *lst)
{
    check_null_pointers("lback: a null pointer was " 
        "received as an argument", 1, lst);

    if (lst->head == lst->end) 
    {
        fprintf(stderr, "lback: list is empty");
        exit(EXIT_FAILURE);
    }

    return lst->end->prev->elem;
}

void _lset(list *lst, list_iterator it, const void *new_val)
{
    check_null_pointers("lset: a null pointer was "
        "received as an argument", 3, lst, it, new_val);

    memcpy(it->elem, new_val, lst->type_size);
}

void _lassign_single(list *lst, const size_t count, const void *var)
{
    check_null_pointers("lassign_single: a null pointer was "
        "received as an argument", 2, lst, var);
    
    size_t i, list_size;
    list_iterator it;

    if (count >= lst->size)
    {
        for (it = lst->head; it != lst->end; it = it->next) {
            memcpy(it->elem, var, lst->type_size);
        }
        for (i = 0, list_size = lst->size; i < count - list_size; ++i) {
            _lpush_back(lst, var);
        }
    }
    else
    {
        lnode *prev_node, *curr_node;
        curr_node = lst->end->prev;
        for (i = 0, list_size = lst->size; i < list_size - count; ++i) 
        {
            prev_node = curr_node->prev;
            free(curr_node->elem);
            free(curr_node);
            curr_node = prev_node;
        }
        if (count != 0) {
            curr_node->next = lst->end;
        }
        else {
            lst->head = lst->end;
        }
        lst->end->prev = curr_node;
        lst->size = count;
        for (it = lst->head; it != lst->end; it = it->next) {
            memcpy(it->elem, var, lst->type_size);
        }
    }
}

void lassign_range(list *lst, const list_iterator begin, const list_iterator end)
{
    check_null_pointers("lassign_range: a null pointer was "
        "received as an argument", 3, lst, begin, end);

    /* lit is a begin iterator for the list to be filled */
    /* b is a copy of the begin iterator from the half-open range */
    /* the copy is needed because the iterator from the arguments is */
    /* constant and we cannot apply ladvance to it */
    list_iterator lit, b; 
    lit = lst->head;
    b = begin;

    /* Number of elements in a half-open range begin-end */
    size_t elems_count;
    elems_count = 0;

    while (b != end)
    {
        if (lit == lst->end) {
            _lpush_back(lst,b->elem);
        }
        else {
            memcpy(lit->elem, b->elem, lst->type_size);
        }
        if (lit != lst->end) {
            lit = lit->next;
        }
        b = b->next;
        elems_count++;
    }
    if (lst->size > elems_count)
    {
        size_t i, ls;
        i = 0;
        ls = lst->size;

        lnode *prev_node, *curr_node;
        curr_node = lst->end->prev;
        for (i = 0; i < ls - elems_count; ++i) 
        {
            prev_node = curr_node->prev;
            free(curr_node->elem);
            free(curr_node);
            curr_node = prev_node;
        }
        if (elems_count != 0) {
            curr_node->next = lst->end;
        }
        else {
            lst->head = lst->end;
        }
        lst->end->prev = curr_node;
        lst->size = elems_count;
    }
}

void lswap(list *lst1, list *lst2)
{
    check_null_pointers("lswap: a null pointer was "
        "received as an argument", 2, lst1, lst2);

    list temp = *lst1;
    *lst1 = *lst2;
    *lst2 = temp;
}

list_iterator lbegin(const list *lst)
{
    check_null_pointers("lbegin: a null pointer was "
        "received as an argument", 1, lst);

    return lst->head;
}

list_iterator lend(const list *lst)
{
    check_null_pointers("lend: a null pointer was "
        "received as an argument", 1, lst);

    return lst->end;
}

void ladvance(list_iterator *it, const int count)
{
    check_null_pointers("ladvance: a null pointer was "
        "received as an argument", 1, it);

    size_t i;
    if (count > 0)
    {
        for (i = 0; i < count; ++i) {
            *it = (*it)->next;
        }
    }
    else if (count < 0)
    {
        for (i = 0; i < abs(count); ++i) {
            *it = (*it)->prev;
        }
    }
}

void *_lderef(const list_iterator it)
{
    check_null_pointers("lderef: a null pointer was "
        "received as an argument", 1, it);
    
    return it->elem;
}

size_t lsize(const list *lst)
{
    check_null_pointers("lsize: a null pointer was "
        "received as an argument", 1, lst);

    return lst->size;
}

unsigned lempty(const list *lst)
{
    check_null_pointers("lempty: a null pointer was "
        "received as an argument", 1, lst);

    return (lst->head == lst->end);
}

void lsort(list *lst, int (*comp)(const void *f, const void *s))
{
    check_null_pointers("lsort: a null pointer was "
        "received as an argument", 2, lst, comp);

    if (lst->size == 0) { 
        return; 
    }
    /* "drop" the end for correct operation of functions */
    lst->end->prev->next = NULL;
    lst->head = merge_sort(lst->head, comp);

    lnode *curr = lst->head;
    while (curr->next)
    {
        curr->next->prev = curr;
        curr = curr->next;
    }
    curr->next = lst->end;
    lst->end->prev = curr;
    lst->head->prev = NULL;
}

list_iterator _lfind(const list *lst, const void *elem, 
    int (*comp)(const void *, const void *))
{
    check_null_pointers("lfind: a null pointer was "
        "received as an argument", 2, lst, elem);
    
    list_iterator it;
    for (it = lst->head; it != lst->end; it = it->next) 
    {
        if (comp(it->elem,elem) == 1) {
            return it;
        }
    }
    return it;
}

static lnode *merge_sort(lnode *head, int (*comp)(const void *f, const void *s))
{
    lnode *first_half_end = get_middle(head);

    if (first_half_end->next == NULL) {
        return merge(head, NULL, comp);
    }
    else
    {
        lnode *first_half = head;
        lnode *second_half = first_half_end->next;
        /* "break" the list */
        first_half_end->next = NULL;

        lnode *left = merge_sort(first_half, comp);
        lnode *right = merge_sort(second_half, comp);
        return merge(left,right,comp);
    }
}

static lnode *merge(lnode *first_head, lnode *second_head, 
    int (*comp)(const void *f, const void *s))
{
    lnode *head, *prev, *curr;
    head = NULL;
    while (first_head || second_head)
    {
        if (first_head)
        {
            if (second_head)
            {
                if (comp(first_head->elem,second_head->elem) <= 0)
                {
                    curr = first_head;
                    first_head = first_head->next;
                }
                else
                {
                    curr = second_head;
                    second_head = second_head->next;
                }
            }
            else 
            {
                curr = first_head;
                if (head == NULL)
                {
                    head = curr;
                    break;
                }
                else
                {
                    prev->next = curr;
                    break;
                }
            }
        }
        else
        {
            curr = second_head;
            if (head == NULL)
            {
                head = curr;
                break;
            }
            else
            {
                prev->next = curr;
                break;
            }
        }
        
        if (head == NULL) 
        {
            head = curr;
            prev = head;
        }
        else
        {
            prev->next = curr;
            prev = prev->next;
        }
    }

    return head;
}

static lnode *get_middle(lnode *head)
{
    lnode *slow, *fast;
    slow = head;
    fast = head;

    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
