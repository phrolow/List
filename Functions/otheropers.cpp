#include "../list.h"

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
    list->Head = 0;
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

void Resize(list *list, size_t new_size) {
    ASSERT_OK(list);

    elem_t *new_data = (elem_t *) calloc(new_size, sizeof(elem_t));

    int next = 0,
            num_filled = 0,
            i = 0;

    do {
        new_data[num_filled++] = list->data[next];

        next = list->next[next];
    } while (next);

    i = num_filled;

    while (i < new_size) {
        new_data[i++] = POISON;
    }

    for(i = 0; i < num_filled; i++) {
        list->next[i] = i + 1;
        list->prev[i] = i - 1;
    }

    list->next[i - 1] = 0;
    list->prev[0] = i - 1;

    for(; i < new_size; i++) {
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    i--;

    list->next[i] = 0;
    list->Tail = num_filled - 1;

    free(list->data);
    list->data = new_data;

    list->size = new_size;
    list->happy = 1;

    RETURN;
}

void Linearize(list *list) {
    ASSERT_OK(list);

    elem_t *new_data = (elem_t *) calloc(list->size, sizeof(elem_t));

    int next = 0,
        num_filled = 0,
        i = 0,
        size = list->size;

    do {
        new_data[num_filled++] = list->data[next];

        next = list->next[next];
    } while (next);

    i = num_filled;

    while (i < size) {
        new_data[i++] = POISON;
    }

    for(i = 0; i < num_filled; i++) {
        list->next[i] = i + 1;
        list->prev[i] = i - 1;
    }

    list->next[i - 1] = 0;
    list->prev[0] = i - 1;

    for(; i < size; i++) {
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    i--;

    list->next[i] = 0;
    list->Tail = num_filled - 1;

    free(list->data);
    list->data = new_data;

    list->happy = 1;

    RETURN;
}