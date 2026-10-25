typedef struct ObjView {
    void *vt;
    void *child;
} ObjView;

extern char lbl_80495F54[];
extern char lbl_80490FE0[];
extern const char lbl_8037D824[];
extern void fn_801957AC(void *obj, int flag);
extern void MemoryManager_TimedFree(void *p);
extern void DebugPrintf(const char *fmt, ...);

ObjView *fn_8019571C(ObjView *self, short flag) {
    if (self != 0) {
        self->vt = lbl_80495F54;
        if (self->child != 0) {
            fn_801957AC(self->child, 1);
        }
        DebugPrintf(lbl_8037D824);
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
