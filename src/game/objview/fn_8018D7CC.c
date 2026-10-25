typedef struct Holder {
    void *child;
} Holder;

extern void Object_DtorWithGXSync(void *obj, int flag);
extern void MemoryManager_TimedFree(void *p);

Holder *fn_8018D7CC(Holder *self, short flag) {
    if (self != 0) {
        if (self->child != 0) {
            Object_DtorWithGXSync(self->child, 1);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
