typedef struct ObjView {
    void *vt;
    void *child;
    unsigned char pad[0x10];
    void *buf;
} ObjView;

extern char lbl_80495DB4[];
extern char lbl_80490FE0[];
extern const char lbl_80377B74[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_Free(void *p);
extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);

ObjView *fn_8018A66C(ObjView *self, short flag) {
    if (self != 0) {
        self->vt = lbl_80495DB4;
        if (self->child != 0) {
            Object_DtorWithGXSync(self->child, 1);
        }
        if (self->buf != 0) {
            MemoryManager_Free(self->buf);
        }
        DebugPrintf(lbl_80377B74);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
