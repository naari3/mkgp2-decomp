#include "game/types/HSD_JObj.h"
typedef struct Obj { void *vt; void **models; int count; float angle; } Obj;
extern char lbl_806D93D0[7], lbl_806D93D8[5];
extern float LUT_Sin12Bit(float);
extern float fn_80186960(float);
extern float fn_8018D638(float);
extern HSD_JObj *Archive_GetRootJObj(void *);
extern void __assert(char *, int, char *);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *);
static inline unsigned char IsDirty(HSD_JObj *j) {
    unsigned int flags;
    unsigned char dirty;
    if (!j) __assert(lbl_806D93D0, 0x25d, lbl_806D93D8);
    flags = j->flags;
    dirty = 0;
    if (!(flags & 0x800000) && (flags & 0x40)) dirty = 1;
    return dirty;
}
static inline void SetScaleY(HSD_JObj *j, float y) {
    if (!j) __assert(lbl_806D93D0, 0x333, lbl_806D93D8);
    j->scale.y = y;
    if (!(j->flags & 0x2000000)) {
        if (j && !IsDirty(j)) HSD_JObjSetMtxDirtySub(j);
    }
}
static inline HSD_JObj *Child(HSD_JObj *j) { if (j == 0) return 0; return j->child; }
static inline HSD_JObj *Next(HSD_JObj *j) { if (j == 0) return 0; return j->next; }
void fn_8018D0F4(Obj *o) {
    float a, odd, even;
    int i, n;
    HSD_JObj *j, *root;
    if (o->models == 0 || o->count == 0) return;
    o->angle += 1.0f;
    a=o->angle;
    if (a >= 60.0f) o->angle = a - 60.0f;
    odd = 0.3f * fn_8018D638(LUT_Sin12Bit(3.0f * o->angle)) + 1.0f;
    even = 0.3f * fn_8018D638(fn_80186960(3.0f * o->angle)) + 1.0f;
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
