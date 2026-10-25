typedef struct Node {
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

extern void MemoryManager_TimedFree(void *p);

List *fn_8017A614(List *self, short flag) {
    if (self) {
        Node *p = self->head;
        while (p) {
            Node *next = p->next;
            if (p) {
                MemoryManager_TimedFree(p);
            }
            p = next;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
