#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define _LOCATION_ __PRETTY_FUNCTION__, __FILE__, __LINE__
#define ASSERT_OK(q)                                                            \
    ListDump(q);                                                               \
                                                                                \
    if(ListCheck(q)) {                                                         \
        abort();                                                                \
    }

#define CHECK(cond, err) (cond) ? 0 : (err)

#define RETURN                                                                  \
    ASSERT_OK(q);                                                               \
                                                                                \
    return

#define newList() newList_(_LOCATION_)
#define ListDump(list) ListDump_(list, _LOCATION_)
#define ListCheck(list) ListCheck_(list, _LOCATION_)

typedef char elem_t;
typedef struct ListInfo {
    const char  *func,
                *file;
    size_t line;
} listinfo;
typedef struct List {
    elem_t* data,
            next,
            prev;
    size_t size;
    int good;
    listinfo info;
} list;

enum Error {
    ALL_RIGHT = 0b0,
    NULL_DATA = 0b1,
    BAD_SIZE = 0b10,
};

const size_t        BIG_SIZE = 4294967296,
                    DEFAULTSIZE = 4;
const elem_t        POISON = 0;
const char* const   LOGPATH = "log.txt";

void add(list *q, elem_t a);

elem_t get(list *q);

void resize(list *t, size_t newSize);

void insert(list *q, elem_t a, size_t num);

list newList_(const char* func, const char* file, size_t line);

void ListDtor(list *q);

void ListDump_(struct List *list, const char *func, const char *file, size_t line);

int ListCheck_(struct List *list, const char* func, const char* file, size_t line);

void perror_(int err, const char* file, const char* func, size_t line);

void CleanLogs();

#endif