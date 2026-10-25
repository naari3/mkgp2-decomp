typedef struct Inner Inner;
extern void fn_8017AD54(Inner *p, short flag);
extern void MemoryManager_TimedFree(void *p);

typedef struct Outer {
    void *x0;
    Inner *inner;
} Outer;

Outer *fn_8017ACF4(Outer *self, short flag) {
    if (self) {
        if (self->inner) {
            fn_8017AD54(self->inner, 1);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
