typedef struct MObjView {
    unsigned char base[0x20];
    unsigned char color[4];
} MObjView;

typedef struct MObjClassView {
    unsigned char base[0x40];
    int (*load)(MObjView *, void *);
    void *(*setupTev)(MObjView *, void *, void **);
    unsigned char tail[0xC];
} MObjClassView;

extern MObjClassView hsdMObj;

int fn_80182138(MObjView *mobj, void *desc) {
    int r = hsdMObj.load(mobj, desc);
    if (r != 0) {
        return r;
    }
    mobj->color[0] = 0;
    mobj->color[1] = 0;
    mobj->color[2] = 0;
    mobj->color[3] = 0xFF;
    return 0;
}
