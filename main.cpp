#include "list.h"

int main(int argc, char *argv[]) {
    list q0;

    q0 = newList();
    add(&q0, 'A');
    add(&q0, 'A');
    add(&q0, 'A');
    add(&q0, 'A');
    add(&q0, 'A');
    get(&q0);
    ListDtor(&q0);
}