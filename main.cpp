#include "list.h"

int NGDUMP;

int main(int argc, char *argv[]) {
    CleanLogs();
    NGDUMP = 0;

    list q0;

    q0 = newList();
    ListGraphDump(&q0);
    ListDtor(&q0);
}