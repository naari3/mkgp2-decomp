typedef struct ResPreloader {
    void *vtable;
    int count;
    int arg;
} ResPreloader;

extern char lbl_8049BC20[];
extern void *lbl_8039FCD0[];
extern void PreloadResource(void *path);

ResPreloader *fn_801DAB7C(ResPreloader *self, int arg) {
    int i;

    self->vtable = lbl_8049BC20;
    self->count = 4;
    self->arg = arg;
    for (i = 0; i < self->count; i++) {
        PreloadResource(lbl_8039FCD0[i]);
    }
    return self;
}
