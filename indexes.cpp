#include "list.h"

int physindex(list *list, int logindex) {
    ASSERT_OK(list);

    if(list->happy)
        return logindex + (gethead(list) - 1);

    int pi = 0;

    for(int i = 0; i < logindex; i++) {
        pi = list->next[pi];
    }

    return pi;
}

int getnext(list *list, int physindex) {
    ASSERT_OK(list);

    if(physindex < 1 || physindex >= list->size)
        return -1;

    return list->next[physindex];
}

int getprev(list *list, int physindex) {
    ASSERT_OK(list);

    if(physindex < 1 || physindex >= list->size)
        return -1;

    return list->prev[physindex];
}

int isfree(list *list, int physindex) {
    ASSERT_OK(list);

    if(list->prev[physindex] == -1)
        return 1;

    return 0;
}

int getfree(list *list) {
    ASSERT_OK(list);

    return list->free;
}

int putfree(list *list) {
    ASSERT_OK(list);

    int free = 0;

    if(getnext(list, getfree(list)) == 0) {
        resize(list, list->size * 2);
    }

    free = getfree(list);

    list->free = list->next[free];

    return free;
}

int gethead(list *list) {
    ASSERT_OK(list);

    return list->Head;
}

int gettail(list *list) {
    ASSERT_OK(list);

    return list->Tail;
}