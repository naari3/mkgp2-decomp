typedef struct ObjView {
    void *vt;
    void *child;
} ObjView;

extern char lbl_80495DDC[];
extern char lbl_80490FE0[];
extern const char lbl_80377E80[];
extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);

ObjView *fn_8018CF34(ObjView *self, short flag) {
    if (self != 0) {
        self->vt = lbl_80495DDC;
        if (self->child != 0) {
            Object_DtorWithGXSync(self->child, 1);
        }
        DebugPrintf(lbl_80377E80);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
