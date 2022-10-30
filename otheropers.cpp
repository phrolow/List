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