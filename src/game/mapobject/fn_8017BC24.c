typedef struct LNode {
    struct LNode *next;
} LNode;

void fn_8017BC24(LNode *list, LNode *n) {
    if (list->next != 0) {
        fn_8017BC24(list->next, n);
    } else {
        list->next = n;
    }
}
