#include "list.h"

list newList_(const char* func, const char* file, size_t line) {
    listinfo info = { NULL, NULL, 0 };
    list list = { NULL, 0, 0, 0, info };

    list.size = DEFAULTSIZE;
    list.data = (elem_t*)calloc(list.size, sizeof(elem_t));
    list.h = 1;
    list.t = 1;

    info.func = func;
    info.file = file;
    info.line = line;

    list.info = info;

    for(size_t i = 0; i < DEFAULTSIZE; i++) {
        list.data[i] = POISON;
    }

    ListDump(&list);

    return list;
}

void ListDtor(list *q) {
    ASSERT_OK(q);

    for(size_t i = 0; i < q->size; i++)
        q->data[i] = POISON;

    q->size = 0;
    q->h = 0;
    q->t = 0;

    ListDump(q);
    free(q->data);

    return;
}