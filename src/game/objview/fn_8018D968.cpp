typedef float Mtx[3][4];
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct HSD_JObj HSD_JObj;
typedef struct HSD_DObj HSD_DObj;
typedef struct HSD_CObj HSD_CObj;

struct GXChannel {
    GXChannel(HSD_JObj *jobj, HSD_DObj *dobj, unsigned int flags, int n);
    ~GXChannel();
    unsigned char pad[0x14];
};

struct Particle {
    unsigned char type;
    unsigned char pad1[3];
    Vec3 pos;
    unsigned char pad10[4];
    float scale;
    unsigned char pad18[0xc];
    float offset;
    float alpha;
};

struct Owner {
    unsigned char pad0[8];
    int enabled;
    void **models;
    Particle *parts;
};

extern "C" {
extern HSD_CObj *HSD_CObjGetCurrent(void);
extern Mtx *HSD_CObjGetInvViewingMtxPtr(HSD_CObj *cobj);
extern void PSMTXCopy(const Mtx src, Mtx dst);
extern HSD_JObj *Archive_GetRootJObj(void *model);
extern HSD_DObj *HSD_JObjGetDObj(HSD_JObj *jobj);
extern unsigned char fn_801379F0(Vec3 *pos, float radius);
extern void PSMTXScale(Mtx m, float x, float y, float z);
extern void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
extern void Object_SetColorAlphaOnly(void *model, int idx, float alpha);
extern void GXChannel_PushTransform(GXChannel *ch, Mtx m);
extern const float lbl_806D93F0;
extern const float lbl_806D93F4;
}

extern "C" void fn_8018D968(Owner *o) {
    HSD_CObj *cobj;
    Mtx inv;
    Mtx m;
    Mtx sc;
    int i;
    int j;
    Particle *p;

    if (o->enabled == 0) return;
    cobj = HSD_CObjGetCurrent();
    if (cobj == 0) return;
    PSMTXCopy(*HSD_CObjGetInvViewingMtxPtr(cobj), inv);
    inv[0][3] = lbl_806D93F0;
    inv[1][3] = lbl_806D93F0;
    inv[2][3] = lbl_806D93F0;
    for (i = 0; i < 3; i++) {
        GXChannel ch(Archive_GetRootJObj(o->models[i]), HSD_JObjGetDObj(Archive_GetRootJObj(o->models[i])), 0x40000000, 1);
        for (j = 0; j < 60; j++) {
            p = &o->parts[j];
            if (p->type == i && fn_801379F0(&p->pos, lbl_806D93F4)) {
                PSMTXScale(sc, p->scale, p->scale, p->scale);
                PSMTXConcat(sc, inv, m);
                m[0][3] = p->offset * inv[0][0] + p->pos.x;
                m[1][3] = p->pos.y;
                m[2][3] = p->offset * inv[2][0] + p->pos.z;
                Object_SetColorAlphaOnly(o->models[i], 0, p->alpha);
                GXChannel_PushTransform(&ch, m);
            }
        }
    }
}
