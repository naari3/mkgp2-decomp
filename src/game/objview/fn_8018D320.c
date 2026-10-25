typedef struct ObjList {
    void *vt;
    void **items;
    int count;
} ObjList;

extern char lbl_80495E18[];
extern char lbl_80490FE0[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);

ObjList *fn_8018D320(ObjList *self, short flag) {
    int i;
    if (self != 0) {
        self->vt = lbl_80495E18;
        if (self->count > 0) {
            for (i = 0; i < self->count; i++) {
                Object_DtorWithGXSync(self->items[i], 1);
            }
            MemoryManager_Free(self->items);
        }
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
