typedef struct ObjView {
    void *vt;
    void *child;
    void *item;
    void *buf;
} ObjView;

extern char lbl_8049637C[];
extern char lbl_80490FE0[];
extern const char lbl_8037DB28[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void fn_80123B48(void *item, int flag);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);

ObjView *fn_80197C84(ObjView *self, short flag) {
    if (self != 0) {
        self->vt = lbl_8049637C;
        Object_DtorWithGXSync(self->child, 1);
        fn_80123B48(self->item, 1);
        MemoryManager_Free(self->buf);
        DebugPrintf(lbl_8037DB28);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
