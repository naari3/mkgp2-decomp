typedef struct SprFile {
    unsigned char pad[0x18];
    unsigned int frames;
    unsigned int params;
} SprFile;

extern void fn_801A0BE0(SprFile *f, unsigned int frames);

int fn_801A0D90(SprFile *f, unsigned int params) {
    if (f == 0) {
        return 0;
    }
    f->frames += (unsigned int)f;
    if (params != 0) {
        f->params = params;
    } else {
        f->params += (unsigned int)f;
    }
    fn_801A0BE0(f, f->frames);
    return 1;
}
