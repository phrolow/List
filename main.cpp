#include "list.h"

int NGDUMP;

int main(int argc, char *argv[]) {
    CleanLogs();
    NGDUMP = 0;
    list q0 = newList();
    ListTailInsert(&q0, 10);
    ListHeadInsert(&q0, 20);
    ListGraphDump(&q0);
    Linearize(&q0);
    ListTailInsert(&q0, 10);
    ListHeadInsert(&q0, 10);
    ListTailInsert(&q0, 10);
    ListInsertAfter(&q0, 2, 2);
    ListGraphDump(&q0);
    Linearize(&q0);
    ListGraphDump(&q0);
    ListDtor(&q0);
}