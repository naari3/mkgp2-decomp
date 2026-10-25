extern "C" {
unsigned long strlen(const char *);
}

struct Item {
    char name[0x24];
    Item *next;
    Item() {
        name[0] = 0;
        next = 0;
    }
};

struct Menu {
    char pad[0x30];
    Item *head;
    Item *tail;
    unsigned int count;
    int cursor;
};

extern "C" void fn_801804CC(Menu *m, const char *name) {
    Item *it = new Item;
    unsigned long i;
    if (it == 0) {
        return;
    }
    i = 0;
    if (name != 0) {
        unsigned long len = strlen(name);
        for (i = 0; i < len && i < 0x20; i++) {
            it->name[i] = name[i];
        }
    }
    it->name[i] = 0;
    if (m->count == 0) {
        m->head = it;
        m->tail = it;
    } else {
        m->tail->next = it;
        m->tail = it;
    }
    m->count++;
}
