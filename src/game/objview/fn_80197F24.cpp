#include "game/objview/part_render_private.h"
struct Entry {
    clNormal3D *model;
    unsigned char pad[12];
};
struct Particle {
    float scale;
    float growth;
    float alpha;
    unsigned char pad[0x18-0xC];
    Vec3f pos;
    unsigned char rest[0x48-0x24];
};
struct Owner {
    void *vt;
    Entry *items;
    int count;
    clNormal3D *model;
    Particle *particles;
};
extern "C" {
extern const float lbl_806D9648, lbl_806D964C, lbl_806D9650, lbl_806D9654, lbl_806D9658;
}
static inline void DrawParticles(Owner *o, Mtx *view) {
    int i;
    Particle *p;
        GXChannel ch(Archive_GetRootJObj(o->model), HSD_JObjGetDObj(Archive_GetRootJObj(o->model)), 0x40000000, 1);
        Mtx m;
        for (i = 0; i < 60; i++) {
            p = &o->particles[i];
            if (lbl_806D9654 != p->alpha && fn_801379F0(&p->pos, lbl_806D9658)) {
                PSMTXScale(m, p->scale, p->scale, p->scale);
                PSMTXConcat(m, *view, m);
                m[0][3] = p->pos.x;
                m[1][3] = p->pos.y;
                m[2][3] = p->pos.z;
                Object_SetColorAlphaOnly(o->model, 0, p->alpha);
                GXChannel_PushTransform(&ch, m);
            }
        }
}

extern "C" void fn_80197F24(Owner *o) {
    int i;
    Mtx *view;
    Entry *items;
    Vec3f pos;
    Vec3f projected;
    if (o->count != 0) {
        view = CObj_GetProjMatrix_Cached(GetCourseScene3D());
        for (i = 0; i < o->count; i++) {
            items = o->items;
            Object_GetJObjPositionVec(items[i].model, &pos);
            pos.y += lbl_806D9648;
            if (fn_80137718(&pos, &projected, lbl_806D964C)) {
                if (projected.z > lbl_806D9650) {
                    clNormal3D_Exec(items[i].model);
                }
                Object_RenderJObjTree(items[i].model, 7);
            }
        }
        DrawParticles(o, view);
    }
}
