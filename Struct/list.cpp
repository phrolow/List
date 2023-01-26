#include "../list.h"

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

    ListInit(&list);

    ListDump(&list);

    return list;
}

void ListDtor(list *list) {
    ASSERT_OK(list);

    for(int i = 0; i < list->size; i++)
        list->data[i] = POISON;

    list->size = 0;
    list->Head = 0;
    list->Tail = 0;

    ListDump(list);
    free(list->data);
//    free(list->getnext);
//    free(list->getprev);

    return;
}