typedef struct ObjView {
    void *vt;
    void *child;
    void *buf0;
    void *buf1;
} ObjView;

extern char lbl_80495FA4[];
extern char lbl_80490FE0[];
extern const char lbl_8037D950[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);

ObjView *fn_80196758(ObjView *self, short flag) {
    if (self != 0) {
        self->vt = lbl_80495FA4;
        Object_DtorWithGXSync(self->child, 1);
        MemoryManager_Free(self->buf0);
        MemoryManager_Free(self->buf1);
        DebugPrintf(lbl_8037D950);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
