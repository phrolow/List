#include "list.h"

err_t ListCheck_(list *list, const char* func, const char* file, size_t line) {
    err_t err = ALL_RIGHT;

    err |= CHECK(list->data, NULL_DATA);

    err |= CHECK(list->size < BIG_SIZE && list->size > 0, BAD_SIZE);

    perror_(err, file, func, line);

    return err;
}