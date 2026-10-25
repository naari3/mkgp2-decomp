typedef struct Obj {
    void *vt;
} Obj;

extern char lbl_80495E8C[];
extern char lbl_80490FE0[];
extern void MemoryManager_TimedFree(void *p);

Obj *fn_8018E4B4(Obj *self, short flag) {
    if (self != 0) {
        self->vt = lbl_80495E8C;
        if (self != 0) {
            self->vt = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
