typedef struct Node {
    struct Node *next;
} Node;

void fn_80195CD4(Node *n, Node *item) {
    if (n->next != 0) {
        fn_80195CD4(n->next, item);
    } else {
        n->next = item;
    }
}
