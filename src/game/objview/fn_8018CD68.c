typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct HSD_JObj {
    unsigned char pad[0x8];
    struct HSD_JObj *next;
    struct HSD_JObj *parent;
    struct HSD_JObj *child;
    unsigned char pad2[0x38 - 0x14];
    Vec3 translate;
} HSD_JObj;
typedef struct Obj {
    void *vt;
    void *gobj;
    HSD_JObj *jobj;
} Obj;

extern char lbl_806D93A8[7];
extern char lbl_806D93B0[5];
extern const float lbl_806D93B8;
extern void __assert(const char *, int, const char *);
extern unsigned char fn_801379F0(Vec3 *, float);
extern void Object_RenderJObjEx(void *, HSD_JObj *, int);

static inline HSD_JObj *JObjGetChild(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}

static inline HSD_JObj *JObjGetNext(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline void JObjGetTranslation(HSD_JObj *jobj, Vec3 *t) {
    if (!jobj) {
        __assert(lbl_806D93A8, 0x3e4, lbl_806D93B0);
    }
    t->x = jobj->translate.x;
    t->y = jobj->translate.y;
    t->z = jobj->translate.z;
}

void fn_8018CD68(Obj *o) {
    HSD_JObj *jobj;
    Vec3 v;

    if (o->gobj == 0 || o->jobj == 0) {
        return;
    }
    for (jobj = JObjGetChild(o->jobj); jobj != 0; jobj = JObjGetNext(jobj)) {
        JObjGetTranslation(jobj, &v);
        if (fn_801379F0(&v, lbl_806D93B8)) {
            Object_RenderJObjEx(o->gobj, jobj, 7);
        }
    }
}
