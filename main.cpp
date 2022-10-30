#include "list.h"

int NGDUMP;

int main(int argc, char *argv[]) {
    CleanLogs();
    NGDUMP = 0;

    list q0;

    q0 = newList();
    add(&q0, 'A');
    add(&q0, 'A');
    add(&q0, 'A');
    add(&q0, 'A');
    add(&q0, 'A');
    get(&q0);
    ListGraphDump(&q0);
    ListDtor(&q0);
}