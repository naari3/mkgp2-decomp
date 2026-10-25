typedef float Mtx[3][4];
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct HSD_JObj HSD_JObj;
typedef struct HSD_DObj HSD_DObj;

struct GXChannel {
    GXChannel(HSD_JObj *jobj, HSD_DObj *dobj, unsigned int flags, int n);
    ~GXChannel();
    unsigned char pad[0x14];
};

struct Effect {
    float active;
    Vec3 pos;
    float rx;
    float ry;
    float rz;
    float x1c;
    float alpha;
    unsigned char pad24[0x48 - 0x24];
};

struct Owner {
    unsigned char pad0[4];
    void *model;
    unsigned char pad8[4];
    Effect *effects;
};

extern "C" {
extern HSD_JObj *Archive_GetRootJObj(void *model);
extern HSD_DObj *HSD_JObjGetDObj(HSD_JObj *jobj);
extern unsigned char fn_801379F0(Vec3 *pos, float radius);
extern void PSMTXScale(Mtx m, float x, float y, float z);
extern void PSMTXRotRad(Mtx m, char axis, float rad);
extern void PSMTXConcat(Mtx a, Mtx b, Mtx ab);
extern void Object_SetColorAlphaOnly(void *model, int idx, float alpha);
extern void GXChannel_PushTransform(GXChannel *ch, Mtx m);
extern const float lbl_806D9560;
extern const float lbl_806D9564;
extern const float lbl_806D9568;
}

extern "C" void fn_80196028(Owner *o) {
    GXChannel ch(Archive_GetRootJObj(o->model), HSD_JObjGetDObj(Archive_GetRootJObj(o->model)), 0x40000000, 1);
    Effect *e;
    Mtx tmp;
    Mtx m;

    for (e = o->effects; e < o->effects + 70; e++) {
        if (lbl_806D9560 != e->active && fn_801379F0(&e->pos, lbl_806D9564)) {
            PSMTXScale(m, lbl_806D9568, lbl_806D9568, lbl_806D9568);
            PSMTXRotRad(tmp, 'Z', e->rz);
            PSMTXConcat(m, tmp, m);
            PSMTXRotRad(tmp, 'X', e->rx);
            PSMTXConcat(m, tmp, m);
            PSMTXRotRad(tmp, 'Y', e->ry);
            PSMTXConcat(m, tmp, m);
            m[0][3] = e->pos.x;
            m[1][3] = e->pos.y;
            m[2][3] = e->pos.z;
            Object_SetColorAlphaOnly(o->model, 0, e->alpha);
            GXChannel_PushTransform(&ch, m);
        }
    }
}
