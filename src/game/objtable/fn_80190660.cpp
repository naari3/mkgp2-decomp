extern "C" {
void fn_80123B48(void *item, int flag);
void MemoryManager_Free(void *p);
}

struct Table {
    void **items;
    int count;
    ~Table() {
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                if (items[i] != 0) {
                    fn_80123B48(items[i], 1);
                    items[i] = 0;
                }
            }
            MemoryManager_Free(items);
        }
        items = 0;
        count = 0;
    }
};

extern Table *lbl_806D16A8;

extern "C" void fn_80190660(void) {
    if (lbl_806D16A8 != 0) {
        delete lbl_806D16A8;
        lbl_806D16A8 = 0;
    }
}
