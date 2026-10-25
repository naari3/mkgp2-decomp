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
extern void *fn_802DF044(void *val, int comp, int ctype, void **list);
extern void *fn_802DEF84(void **list);
extern void fn_802DF164(void *tev, int a, int b, int c, int d);
extern void fn_802DF8EC(void *tev, int a, void *b, int c, void *d, int e, void *f, int g, void *h);
extern void fn_802DF24C(void *tev, int a, int b, int c, int d);
extern void fn_802DFDEC(void *tev, int a, void *b, int c, void *d, int e, void *f, int g, void *h);

void *fn_8018201C(MObjView *mobj, void *arg, void **list) {
    void *t = hsdMObj.setupTev(mobj, arg, list);
    void *c1 = fn_802DF044(&mobj->color[0], 1, 0, list);
    void *c2 = fn_802DF044(&mobj->color[3], 6, 0, list);
    void *tev = fn_802DEF84(list);
    fn_802DF164(tev, 0, 0, 0, 1);
    fn_802DF8EC(tev, 1, t, 7, 0, 5, c2, 1, c1);
    fn_802DF24C(tev, 1, 0, 0, 1);
    fn_802DFDEC(tev, 5, t, 7, 0, 5, c2, 5, t);
    return tev;
}
