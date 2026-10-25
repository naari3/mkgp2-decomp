typedef struct Entry {
    void *obj;
    unsigned char pad[0xc];
} Entry;

typedef struct ObjList {
    void *vt;
    Entry *items;
    int count;
    void *child;
    void *buf;
} ObjList;

extern char lbl_804963A4[];
extern char lbl_80490FE0[];
extern const char lbl_8037DC04[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void fn_8016C394(int id);
extern void DebugPrintf(const char *fmt, ...);

ObjList *fn_801986D8(ObjList *self, short flag) {
    int i;
    if (self != 0) {
        self->vt = lbl_804963A4;
        if (self->count != 0) {
            for (i = 0; i < self->count; i++) {
                Object_DtorWithGXSync(self->items[i].obj, 1);
            }
            MemoryManager_Free(self->items);
        }
        Object_DtorWithGXSync(self->child, 1);
        MemoryManager_Free(self->buf);
        fn_8016C394(0x2d);
        DebugPrintf(lbl_8037DC04);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
