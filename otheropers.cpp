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
    list->Tail = 0;

    for(i = 1; i < list->size; i++) {
        list->data[i] = POISON;
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->next[i - 1] = 0;

    list->free = 1;

    list->happy = 1;

    RETURN;
}

void resize(list *list, size_t newsize) {
    ASSERT_OK(list);

    elem_t *newdata = NULL;
    int i = 0,
        next = 0,
        oldsize = 0;

    newdata = (elem_t*)calloc(newsize, sizeof(elem_t));

    newdata[0] = POISON;

    do {
        next = list->next[next];
        newdata[++i] = list->data[next];
    } while(next);

    oldsize = i;

    list->next = (int*)realloc(list->next, newsize * sizeof(int));
    list->prev = (int*)realloc(list->prev, newsize * sizeof(int));

    list->Head = 1;

    for(i = 1; i < oldsize; i++) {
        list->next[i] = i + 1;
        list->prev[i] = i - 1;
    }

    list->next[--i] = 0;
    list->Tail = i;
    list->free = oldsize;

    for(i = oldsize; i < newsize; i++) {
        newdata[i] = POISON;
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->next[i - 1] = 0;

    list->size = newsize;
    list->happy = 1;
    list->data = newdata;

    RETURN;
}