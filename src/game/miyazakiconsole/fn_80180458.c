typedef struct Item {
    char name[0x24];
    struct Item *next;
} Item;

typedef struct Menu {
    char pad[0x30];
    Item *head;
    Item *tail;
    int count;
    int cursor;
} Menu;

extern void MemoryManager_TimedFree(void *p);

void fn_80180458(Menu *m) {
    if (m->head != 0) {
        Item *p = m->head;
        while (p != 0) {
            Item *next = p->next;
            if (p) {
                MemoryManager_TimedFree(p);
            }
            p = next;
        }
    }
    m->head = 0;
    m->tail = 0;
    m->count = 0;
    m->cursor = 0;
}
