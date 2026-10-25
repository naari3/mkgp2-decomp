typedef struct Table {
    void **items;
    int count;
} Table;

extern unsigned char fn_80123480(void *item, void *key);

int fn_8019032C(Table *t, void *key) {
    int i;
    if (t->count == 0) {
        return -1;
    }
    for (i = 0; i < t->count; i++) {
        if (t->items[i] != 0 && fn_80123480(t->items[i], key)) {
            return i;
        }
    }
    return -1;
}
