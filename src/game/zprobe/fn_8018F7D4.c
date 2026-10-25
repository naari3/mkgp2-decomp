typedef struct Node {
    struct Node *next;
} Node;

void fn_8018F7D4(Node *n, Node *item) {
    if (n->next != 0) {
        fn_8018F7D4(n->next, item);
    } else {
        n->next = item;
    }
}
