/* NokoNoko_Render (0x80188B24): draws every visible NokoNoko, blending the secondary animation. */

typedef struct { float x, y, z; } Vec;
typedef struct NokoNoko {
    struct NokoNoko *next;
    char pad04[0xC];
    int model;
    float frame;
    char pad18[0x4];
    Vec pos;
    float yaw;
    char pad2C[0x8];
    int model2;
    float blend;
    float frame2;
} NokoNoko;

extern unsigned char g_nokonokoEnable;
extern NokoNoko *g_nokonokoHead;
extern void *lbl_80677EC8[];
extern const float lbl_806D9318;
extern const float lbl_806D931C;
extern const float lbl_806D9320;
extern unsigned char fn_801379F0(Vec *pos, float r);
extern void Object_SetField8_AndDirty(void *obj, float v);
extern void clNormal3D_Exec(void *obj);
extern void *Archive_GetRootJObj(void *obj);
extern void ObjectTree_BlendOrCopy_Timed(void *obj, void *src, void *dst, void *base, float t);
extern void Object_SetColorAlphaOnly(void *obj, int idx, float a);
extern void Object_SetJObjPositionVec(void *obj, Vec *pos);
extern void Object_SetJObjRotationY(void *obj, float v);
extern void Object_RenderJObjTree(void *obj, int flags);

#pragma exceptions on
void NokoNoko_Render(void) {
    NokoNoko *n;

    if (g_nokonokoEnable == 0) {
        return;
    }
    for (n = g_nokonokoHead; n != 0; n = n->next) {
        if (n->model == -1) {
            continue;
        }
        if (!fn_801379F0(&n->pos, lbl_806D9318)) {
            continue;
        }
        Object_SetField8_AndDirty(lbl_80677EC8[n->model], n->frame);
        clNormal3D_Exec(lbl_80677EC8[n->model]);
        if (n->model2 != -1) {
            Object_SetField8_AndDirty(lbl_80677EC8[n->model2], n->frame2);
            clNormal3D_Exec(lbl_80677EC8[n->model2]);
            ObjectTree_BlendOrCopy_Timed(lbl_80677EC8[n->model], Archive_GetRootJObj(lbl_80677EC8[n->model2]),
                                         Archive_GetRootJObj(lbl_80677EC8[n->model]),
                                         Archive_GetRootJObj(lbl_80677EC8[n->model]), n->blend);
        }
        if (n->model == 3) {
            Object_SetColorAlphaOnly(lbl_80677EC8[n->model], 0, lbl_806D931C - n->frame / lbl_806D9320);
        }
        Object_SetJObjPositionVec(lbl_80677EC8[n->model], &n->pos);
        Object_SetJObjRotationY(lbl_80677EC8[n->model], n->yaw);
        Object_RenderJObjTree(lbl_80677EC8[n->model], 7);
    }
}
#pragma exceptions reset
