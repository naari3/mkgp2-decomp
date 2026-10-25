typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct MObjHolder {
    unsigned char pad[8];
    void *mobj;
} MObjHolder;

typedef struct Light {
    void *vt;
    Vec3 pos;
    float scale;
    MObjHolder *mat;
} Light;

typedef struct Cam {
    unsigned char pad[0x10];
    float a;
    unsigned char pad14[4];
    float b;
} Cam;

extern float lbl_80495E30[4];
extern const float lbl_806D93E8;
extern const float lbl_806D93EC;
extern void PSMTXInverse(float (*src)[4], float (*dst)[4]);
extern void PSMTXMultVec(float (*m)[4], Vec3 *src, Vec3 *dst);
extern void *HSD_MObjGetTObj(void *mobj);
extern void fn_80182A5C(void *tobj, float u, float v);

static inline void *GetMObj(MObjHolder *h) {
    if (h != 0) {
        return h->mobj;
    }
    return 0;
}

void fn_8018D6F0(Light *o, Cam *cam, float (*m)[4]) {
    float inv[3][4];
    float *R;
    if (cam == 0 || m == 0) {
        return;
    }
    PSMTXInverse(m, inv);
    R = lbl_80495E30;
    if (o->mat == 0) {
        return;
    }
    o->pos.x = lbl_806D93E8;
    o->pos.y = lbl_806D93E8;
    o->pos.z = R[0];
    PSMTXMultVec(inv, &o->pos, &o->pos);
    o->scale = cam->b * -R[0] / cam->a / lbl_806D93EC;
    fn_80182A5C(HSD_MObjGetTObj(GetMObj(o->mat)), R[2], R[3]);
}
