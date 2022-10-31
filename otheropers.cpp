#include "list.h"

void ListDelete(list *list, int logindex) {
    ASSERT_OK(list);

    return ListPhDelete(list, physindex(list, logindex));
}

void ListPhDelete(list *list, int physindex) {
    ASSERT_OK(list);

    int next = 0,
        prev = 0;

    next = getnext(list, physindex);
    prev = getprev(list, physindex);

    list->next[prev] = next;
    list->prev[physindex] = -1;
    list->data[physindex] = POISON;
    list->next[physindex] = getfree(list);
    list->prev[next] = prev;

    list->free = physindex;

    list->happy = 0;

    RETURN;
}

int ListIndexFirst(list *list, elem_t a) {
    ASSERT_OK(list);

    int next = 0;

    do {
        next = list->next[next];
    } while(list->data[next] != a && next);

    if(next == 0)
        next = -1;

    return next;
}

int ListPhIndexFirst(list *list, elem_t a) {
    ASSERT_OK(list);

    return physindex(list, ListIndexFirst(list, a));
}

void ListInit(list *list) {
    ASSERT_OK(list);

    size_t i = 0;

    list->data[0] = POISON;
    list->Head = 1;
    list->Tail = 1;

    for(i = 1; i < list->size; i++) {
        list->data[i] = POISON;
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->next[i] = 0;

    list->free = 0;

    list->happy = 1;

    RETURN;
}

void resize(list *q, size_t newsize) {
    ASSERT_OK(q);

    elem_t *newdata = NULL;
    int i = 0,
        next = 0,
        oldsize = 0;

    newdata = (elem_t*)calloc(newsize, sizeof(elem_t));

    newdata[0] = POISON;

    do {
        next = q->next[next];
        newdata[++i] = q->data[next];
    } while(q->next[next]);

    oldsize = i;

    q->next = (int*)realloc(q->next, q->size * sizeof(int));
    q->prev = (int*)realloc(q->prev, q->size * sizeof(int));

    q->Head = 1;

    for(i = 1; i < oldsize; i++) {
        q->next[i] = i + 1;
        q->prev[i] = i - 1;
    }

    q->next[i] = 0;
    q->Tail = i;
    q->free = oldsize;

    for(i = oldsize; i < newsize; i++) {
        newdata[i] = POISON;
        q->next[i] = i + 1;
        q->prev[i] = -1;
    }

    q->next[i] = 0;

    q->size = newsize;
    q->happy = 1;
    q->data = newdata;

    RETURN;
}