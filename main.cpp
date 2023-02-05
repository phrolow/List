#include "list.h"

int NGDUMP;

int main(int argc, char *argv[]) {
    CleanLogs();
    NGDUMP = 0;
    list q0 = newList();
    ListTailInsert(&q0, 'V');
    ListTailInsert(&q0, 'F');
    ListGraphDump(&q0);
    ListTailInsert(&q0, 'C');
    ListGraphDump(&q0);
    ListDtor(&q0);
}