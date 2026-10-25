typedef struct Node {
    struct Node *next;
} Node;

void fn_80195F54(Node *n, Node *item) {
    if (n->next != 0) {
        fn_80195F54(n->next, item);
    } else {
        n->next = item;
    }
}
