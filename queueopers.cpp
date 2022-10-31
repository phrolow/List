#include "list.h"

void add(list *q, elem_t a) {
    ASSERT_OK(q);

    if(!(q->happy)) {
        insert(q, a, q->Tail);
        return;
    }

    if((q->Tail + 1) % q->size == q->Head) {
        resize(q, q->size * 2);
    }

    q->data[q->Tail] = a;

    q->free = q->next[q->Tail];

    q->next[q->Tail] = 0;

    q->prev[q->Tail] = (q->Tail - 1) % q->size;

    q->next[q->prev[q->Tail]] = q->Tail;

    q->Tail = (q->Tail + 1) % q->size;

    RETURN;
}

void addInHead(list *q, elem_t a) {
    ASSERT_OK(q);

    int oldHead = 0;

    if(!(q->happy)) {
        insert(q, a, 1);
        return;
    }

    if((q->Head - 1) % q->size == q->Tail) {
        resize(q, q->size * 2);
    }

    oldHead = q->Head;

    q->Head = (q->Head - 1) % q->size;

    q->data[q->Head] = a;

    q->prev[oldHead] = q->Head;

    q->next[q->Head] = oldHead;

    q->prev[q->Head] = 0;

    q->happy = 0;

    RETURN;
}

