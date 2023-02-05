#include "../list.h"

elem_t *ListFirst(list *list) {
    ASSERT_OK(list);

    return list->data + gethead(list);
}

elem_t *ListLast(list *list) {
    ASSERT_OK(list);

    return list->data + gettail(list);
}

elem_t *ListNext(list *list, int physindex) {
    ASSERT_OK(list);

    return list->data + getnext(list, physindex);
}

elem_t *ListPrev(list *list, int physindex) {
    ASSERT_OK(list);

    return list->data + getprev(list, physindex);
}