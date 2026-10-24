typedef struct SmallObj {
    void *vtbl;
} SmallObj;

extern char lbl_803FDF40[];
extern char lbl_803FDF28[];
extern void MemoryManager_TimedFree(void *);

SmallObj *SmallObj_Dtor_VtableA(SmallObj *self, short flags) {
    if (self != 0) {
        self->vtbl = lbl_803FDF40;
        if (self != 0) {
            self->vtbl = lbl_803FDF28;
        }
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
