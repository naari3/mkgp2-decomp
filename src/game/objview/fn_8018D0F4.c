typedef struct Joint {
    char pad0[8];
    struct Joint *next;
    void *parent;
    struct Joint *child;
    unsigned int flags;
    char pad18[0x18];
    float scaleY;
} Joint;
typedef struct Obj { void *vt; void **models; int count; float angle; } Obj;
extern const float lbl_806D93C0, lbl_806D93C4, lbl_806D93C8, lbl_806D93CC;
extern char lbl_806D93D0[7], lbl_806D93D8[5];
extern float LUT_Sin12Bit(float);
extern float fn_80186960(float);
extern float fn_8018D638(float);
extern Joint *Archive_GetRootJObj(void *);
extern void __assert(char *, int, char *);
extern void HSD_JObjSetMtxDirtySub(Joint *);
static inline unsigned char IsDirty(Joint *j) {
    unsigned int flags;
    unsigned char dirty;
    if (!j) __assert(lbl_806D93D0, 0x25d, lbl_806D93D8);
    flags = j->flags;
    dirty = 0;
    if (!(flags & 0x800000) && (flags & 0x40)) dirty = 1;
    return dirty;
}
static inline void SetScaleY(Joint *j, float y) {
    if (!j) __assert(lbl_806D93D0, 0x333, lbl_806D93D8);
    j->scaleY = y;
    if (!(j->flags & 0x2000000)) {
        if (j && !IsDirty(j)) HSD_JObjSetMtxDirtySub(j);
    }
}
static inline Joint *Child(Joint *j) { if (j) return j->child; return 0; }
static inline Joint *Next(Joint *j) { if (j) return j->next; return 0; }
void fn_8018D0F4(Obj *o) {
    float a, odd, even;
    int i, n;
    Joint *j, *root;
    if (o->models == 0 || o->count == 0) return;
    a=o->angle + lbl_806D93C0;
    o->angle=a;
    a=o->angle;
    if (a >= lbl_806D93C4) o->angle = a - lbl_806D93C4;
    odd = lbl_806D93C8 * fn_8018D638(LUT_Sin12Bit(lbl_806D93CC * o->angle)) + lbl_806D93C0;
    even = lbl_806D93C8 * fn_8018D638(fn_80186960(lbl_806D93CC * o->angle)) + lbl_806D93C0;
    for (i=0; i<o->count; i++) {
        if (o->models[i]) {
            n=0;
            root=Archive_GetRootJObj(o->models[i]);
            for (j=Child(root); j; j=Next(j)) {
                if (n & 1) SetScaleY(j, odd);
                else SetScaleY(j, even);
                n++;
            }
        }
    }
}
