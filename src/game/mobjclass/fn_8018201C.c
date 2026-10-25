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
extern void *HSD_TExpCnst(void *val, int comp, int ctype, void **list);
extern void *HSD_TExpTev(void **list);
extern void HSD_TExpColorOp(void *tev, int a, int b, int c, int d);
extern void HSD_TExpColorIn(void *tev, int a, void *b, int c, void *d, int e, void *f, int g, void *h);
extern void HSD_TExpAlphaOp(void *tev, int a, int b, int c, int d);
extern void HSD_TExpAlphaIn(void *tev, int a, void *b, int c, void *d, int e, void *f, int g, void *h);

void *fn_8018201C(MObjView *mobj, void *arg, void **list) {
    void *t = hsdMObj.setupTev(mobj, arg, list);
    void *c1 = HSD_TExpCnst(&mobj->color[0], 1, 0, list);
    void *c2 = HSD_TExpCnst(&mobj->color[3], 6, 0, list);
    void *tev = HSD_TExpTev(list);
    HSD_TExpColorOp(tev, 0, 0, 0, 1);
    HSD_TExpColorIn(tev, 1, t, 7, 0, 5, c2, 1, c1);
    HSD_TExpAlphaOp(tev, 1, 0, 0, 1);
    HSD_TExpAlphaIn(tev, 5, t, 7, 0, 5, c2, 5, t);
    return tev;
}
