#include "list.h"

list newList_(const char* func, const char* file, size_t line) {
    int i = 0;

    listinfo info = { NULL, NULL, 0 };
    list list = { NULL, NULL, NULL, 0, 0, 0, info };

    list.size = DEFAULTSIZE;

    list.data = (elem_t*)calloc(list.size, sizeof(elem_t));
    list.next = (int*)calloc(list.size, sizeof(int));
    list.prev = (int*)calloc(list.size, sizeof(int));

    info.func = func;
    info.file = file;
    info.line = line;

    list.info = info;

    ListInit(list);

    ListDump(&list);

    return list;
}

void ListDtor(list *q) {
    ASSERT_OK(q);

    for(int i = 0; i < q->size; i++)
        q->data[i] = POISON;

    q->size = 0;
    q->Head = 0;
    q->Tail = 0;

    ListDump(q);
    free(q->data);
//    free(q->getnext);
//    free(q->getprev);

    return;
}