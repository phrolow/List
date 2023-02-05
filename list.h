#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define DEBUG

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define _LOCATION_ __PRETTY_FUNCTION__, __FILE__, __LINE__
#define Head next[0]
#define Tail prev[0]
#define ASSERT_OK(list)                                                            \
    ListDump(list);                                                               \
                                                                                \
    if(ListCheck(list)) {                                                         \
        abort();                                                                \
    }

#define CHECK(cond, err) (cond) ? 0 : (err)

#define RETURN                                                                  \
    ASSERT_OK(list);                                                               \
                                                                                \
    return

#define newList() newList_(_LOCATION_)
#define ListDump(list) ListDump_(list, _LOCATION_)
#define ListCheck(list) ListCheck_(list, _LOCATION_)

typedef char elem_t;
typedef int err_t;
typedef struct ListInfo {
    const char  *func,
            *file;
    size_t line;
} listinfo;
typedef struct List {
    elem_t  *data;
    int  *next,
            *prev;
    size_t size;
    int happy,
            free;
    listinfo info;
} list;

enum Error {
    ALL_RIGHT = 0b0,
    NULL_DATA = 0b1,
    BAD_SIZE = 0b10,
};

const size_t        BIG_SIZE = 0x100000,
        DEFAULTSIZE = 4;
const elem_t        POISON = 0;
const char* const   DOTPATH = "graphdump";
const char* const   HTMLPATH = "log.html";
const char* const   PNGPATH = "graph.png";
const char* const   DOT = "C:\\Users\\Russi\\Downloads\\windows_10_msbuild_Release_graphviz-6.0.2-win32\\Graphviz\\bin\\dot.exe";

const char* const   COLOR_NODE = "#8FBC8F";
const char* const   COLOR_FREE_NODE = "#808000";
const char* const   COLOR_ZERO_NODE = "#4682B4";
const char* const   COLOR_HTF = "#FFDAB9";
const char* const   COLOR_PARAM = "#FFC0CB";

extern int NGDUMP;

void add(list *q, elem_t a);

elem_t get(list *q);

void resize(list *list, size_t newSize);

void del(list *q, int num);

void insert(list *q, elem_t a, int num);

list newList_(const char* func, const char* file, size_t line);

void ListDtor(list *list);

void ListDump_(struct List *list, const char *func, const char *file, size_t line);

void ListGraphDump(list *list);

err_t ListCheck_(struct List *list, const char* func, const char* file, size_t line);

int physindex(list *list, int logindex);

int getprev(list *list, int physindex);

int getnext(list *list, int physindex);

int isfree(list *list, int physindex);

int getfree(list *list);

int putfree(list *list);

int gethead(list *list);

int gettail(list *list);

elem_t *ListFirst(list *list);

elem_t *ListLast(list *list);

elem_t *ListNext(list *list);

elem_t *ListPrev(list *list);

void ListHeadInsert(list *list, elem_t a);

void ListTailInsert(list *list, elem_t a);

void ListInsertAfter(list *list, elem_t a, int logindex);

void ListInsertBefore(list *list, elem_t a, int logindex);

void ListPhInsertAfter(list *list, elem_t a, int physindex);

void ListPhInsertBefore(list *list, elem_t a, int physindex);

void ListDelete(list *list, int logindex);

void ListPhDelete(list *list, int physindex);

int ListIndexFirst(list *list, elem_t a);

int ListPhIndexFirst(list *list, elem_t a);

void ListInit(list *list);

void linearize(list *list);

void perror_(int err, const char* file, const char* func, size_t line);

void CleanLogs();

#endif