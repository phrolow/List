#include "list.h"

FILE    *DOTFILE = NULL,
        *HTML = NULL;

int main(int argc, char *argv[]) {
    atexit( CloseLogs );

    DOTFILE = fopen(DOTPATH, "w");
    HTML = fopen(HTMLPATH, "w");

    list q0 = newList();

    ListTailInsert(&q0, 'A');
    ListTailInsert(&q0, 'B');
    ListTailInsert(&q0, 'C');
    ListTailInsert(&q0, 'D');
    ListTailInsert(&q0, 'E');
    ListHeadInsert(&q0, 'F');
    ListDelete(&q0, 1);
    ListInsertAfter(&q0, 'G', 1);
    ListPhInsertBefore(&q0, 'G', 1);

    ListGraphDump(&q0);

    ListDtor(&q0);
}