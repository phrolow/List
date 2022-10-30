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

elem_t get(list *q) {
    ASSERT_OK(q);

    elem_t res = q->data[q->Head];

    q->data[q->Head] = POISON;

    q->next[q->Head] = 0;

    q->next[q->prev[q->Head]] = q->Head;

    q->prev[q->Head] = -1;

    q->Head = (q->Head + 1) % q->size;

    q->prev[q->Head] = 0;

    RETURN res;
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

    RETURN;
}

void resize(list *q, size_t newsize) {
    ASSERT_OK(q);

    elem_t *newdata = NULL;
    int i = 0,
        next = 0,
        oldsize = 0;

    newdata = (elem_t*)calloc(newsize, sizeof(elem_t));

    newdata[0] = POISON;

    do {
        next = q->next[next];
        newdata[++i] = q->data[next];
    } while(next);

    oldsize = ++i;

    q->next = (int*)realloc(q->next, q->size * sizeof(int));
    q->prev = (int*)realloc(q->prev, q->size * sizeof(int));

    for(i = 1; i < oldsize; i++) {
        q->next[i] = i + 1;
        q->prev[i] = i - 1;
    }

    q->next[i] = 0;
    q->prev[0] = i + 1;
    q->free = i + 1;

    for(i = oldsize; i < newsize; i++) {
        q->next[i] = i + 1;
        q->prev[i] = -1;
    }

    q->next[0] = 1;
    q->next[newsize - 1] = 0;

    q->size = newsize;
    q->happy = 1;
    q->data = newdata;

    RETURN;
}

void del(list *q, int num) {
    ASSERT_OK(q);

    assert(q->size < num);

    int anchor = 0,
        next = 0,
        prev = 0;

    anchor = q->Head;

    for(int i = 0; i < num; i++) {
        anchor = q->next[anchor];
    }

    next = q->next[anchor];
    prev = q->prev[anchor];

    q->prev[next] = prev;
    q->next[prev] = next;

    q->next[anchor] = q->free;
    q->prev[anchor] = -1;

    q->data[anchor] = POISON;
    q->free = anchor;

    q->happy = 0;

    RETURN;
}

void insert(list *q, elem_t a, int num) {
    ASSERT_OK(q);

    assert(q->size > num);

    int anchor = 0,
        current = 0,
        next = 0;

    anchor = q->Head;

    for(int i = 0; i < num; i++) {
        anchor = q->next[anchor];
    }

    current = q->free;
    next = q->next[anchor];

    q->free = q->next[q->free];

    q->next[anchor] = current;
    q->next[current] = next;

    q->prev[current] = anchor;
    q->prev[next] = current;

    q->data[anchor] = a;

    q->happy = 0;

    RETURN;
}