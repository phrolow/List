#include "list.h"

void add(list *q, elem_t a) {
    ASSERT_OK(q);

    if((q->t + 1) % q->size == q->h) {
        resize(q, q->size * 2);
    }

    q->data[q->t] = a;

    q->t = (q->t + 1) % q->size;

    RETURN;
}

elem_t get(list *q) {
    ASSERT_OK(q);

    elem_t res = q->data[q->h];

    q->data[q->h] = POISON;
    q->h = (q->h + 1) % q->size;

    RETURN res;
}

void resize(list *q, size_t newSize) {
    ASSERT_OK(q);

    size_t i;

    q->data = (char*)realloc(q->data, newSize * sizeof(elem_t));

    if(q->t < q->size / 2) {
        for (i = q->size; i < q->size + q->t; i++) {
            q->data[i] = q->data[i - q->size];
            q->data[i - q->size] = POISON;
        }

        q->t = i;
    }
    else {
        for (i = newSize; i > q->h + newSize - q->size; --i) {
            q->data[i] = q->data[i - newSize + q->size];
            q->data[i - newSize + q->size] = POISON;
        }

        q->h = i;
    }

    q->size = newSize;

    RETURN;
}

void insert(list *q, elem_t a, size_t num) {
    ASSERT_OK(q);



    RETURN;
}