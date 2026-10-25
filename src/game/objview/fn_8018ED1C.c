typedef struct ObjView {
    void *vt;
    void *child0;
    void *child1;
    void *pad;
    void *buf0;
    void *buf1;
} ObjView;

extern char lbl_80495EB4[];
extern char lbl_80490FE0[];
extern const char lbl_803781A4[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);

ObjView *fn_8018ED1C(ObjView *self, short flag) {
    if (self != 0) {
        self->vt = lbl_80495EB4;
        if (self->child0 != 0) {
            Object_DtorWithGXSync(self->child0, 1);
        }
        if (self->child1 != 0) {
            Object_DtorWithGXSync(self->child1, 1);
        }
        if (self->buf0 != 0) {
            MemoryManager_Free(self->buf0);
        }
        if (self->buf1 != 0) {
            MemoryManager_Free(self->buf1);
        }
        DebugPrintf(lbl_803781A4);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
