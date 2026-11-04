#include "game/objview/part_render_private.h"
struct Particle {
    unsigned char active;
    unsigned char pad[3];
    float x, y, depth, alpha;
    unsigned char rest[0x24 - 0x14];
};
struct Owner {
    void *vt;
    clNormal3D *model;
    void *item;
    Particle *particles;
};
extern "C" {
extern const float lbl_806D95E8, lbl_806D95EC, lbl_806D95F0, lbl_806D95F4;
}
extern "C" void fn_80197130(Owner *o) {
    Particle *p;
    int i;
    Mtx *view;
    float width;
    float height;
    void *scene = GetCourseScene3D();
    if (scene != 0) {
        view = CObj_GetProjMatrix_Cached(scene);
        float angle;
        float aspect;
        Vec3f pos;
        Scene3D_GetCameraPos(scene, &angle, &aspect);
        height = tan(lbl_806D95E8 * (lbl_806D95EC * angle));
        width = height * aspect;
        GXChannel ch(Archive_GetRootJObj(o->model), HSD_JObjGetDObj(Archive_GetRootJObj(o->model)), 0x40000000, 1);
        Mtx m;
        for (i = 0; i < 50; i++) {
            p = &o->particles[i];
            if (p->active != 0 && lbl_806D95F0 != p->alpha) {
                float y = -p->depth * height;
                float x = p->depth * width;
                pos.x = p->x * (-x - x) + x;
                pos.y = p->y * (-y - y) + y;
                pos.z = p->depth;
                PSMTXMultVec(*view, &pos, &pos);
                PSMTXScale(m, lbl_806D95F4, lbl_806D95F4, lbl_806D95F4);
                PSMTXConcat(m, *view, m);
                float z, py, px;
                px = pos.x; py = pos.y; z = pos.z;
                m[0][3] = px; m[1][3] = py; m[2][3] = z;
                Object_SetColorAlphaOnly(o->model, 0, p->alpha);
                GXChannel_PushTransform(&ch, m);
            }
        }
    }
}
