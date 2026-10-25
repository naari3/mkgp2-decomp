typedef struct ObjView {
    void *vt;
    void *child;
    void *buf;
} ObjView;

extern char lbl_80495C0C[];
extern char lbl_80490FE0[];
extern const char lbl_803773F8[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);

ObjView *fn_80187B54(ObjView *self, short flag) {
    if (self != 0) {
        self->vt = lbl_80495C0C;
        if (self->child != 0) {
            Object_DtorWithGXSync(self->child, 1);
        }
        if (self->buf != 0) {
            MemoryManager_Free(self->buf);
        }
        DebugPrintf(lbl_803773F8);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
