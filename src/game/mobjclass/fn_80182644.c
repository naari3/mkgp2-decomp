typedef struct FlagObj {
    void *parent;
    unsigned int flags;
} FlagObj;

void fn_80182644(FlagObj *obj, unsigned int flags) {
    if (obj == 0) {
        return;
    }
    if (flags & 3) {
        obj->flags &= ~3;
    }
    if (flags & 0x6000) {
        obj->flags &= ~0x6000;
    }
    obj->flags |= flags;
}
