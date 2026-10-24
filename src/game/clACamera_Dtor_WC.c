typedef struct clACamera {
    void *vtbl;
} clACamera;

extern char lbl_80419EF8[];
extern void Object_DtorTree_56b8(void *, short);
extern void MemoryManager_TimedFree(void *);

clACamera *clACamera_Dtor_WC(clACamera *self, short flags) {
    if (self != 0) {
        self->vtbl = lbl_80419EF8;
        Object_DtorTree_56b8(self, 0);
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
