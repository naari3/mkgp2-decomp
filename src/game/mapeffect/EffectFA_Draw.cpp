#include "game/EffectFA_private.h"

struct EffectJointMatrix : HSD_JObj {
    float matrix[3][4];
};
extern "C" {
extern char lbl_806D8C18[7], lbl_806D8C20[5];
extern char EffectFA_Draw_rodata_8036E054[];
extern const float lbl_806D8C2C;
void Object_SetJObjPositionVec(clNormal3D *, Vec3f *);
void Object_SetJObjRotationY(clNormal3D *, float);
void Object_SetJObjScaleXYZ(clNormal3D *, float, float, float);
void Object_SetColorAlphaOnly(clNormal3D *, int, float);
void Object_SetField8_AndDirty(clNormal3D *, float);
void clNormal3D_Exec(clNormal3D *);
void Object_RenderJObjTree(clNormal3D *, int);
void HSD_JObjSetupMatrixSub(HSD_JObj *);
void fn_80182204(HSD_JObj *, int);
}
static inline unsigned char MatrixIsDirty(HSD_JObj *j) {
    if (!j) __assert(lbl_806D8C18, 0x25d, lbl_806D8C20);
    unsigned char result = 0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) result = 1;
    return result;
}
static inline void SetupMatrix(HSD_JObj *j) {
    if (!j) return;
    if (MatrixIsDirty(j)) HSD_JObjSetupMatrixSub(j);
}
static inline float (*GetMatrix(HSD_JObj *j))[4] {
    if (!j) __assert(lbl_806D8C18, 0x47c, lbl_806D8C20);
    SetupMatrix(j);
    return ((EffectJointMatrix *)j)->matrix;
}
static inline void Dirty(HSD_JObj *j) {
    if (j && !MatrixIsDirty(j)) HSD_JObjSetMtxDirtySub(j);
}
static inline void SetPosition(HSD_JObj *j, const Vec3f *v) {
    if (!j) __assert(lbl_806D8C18, 0x3a9, lbl_806D8C20);
    j->translate = *v;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void SetScaleX(HSD_JObj *j, float f) {
    if (!j) __assert(lbl_806D8C18, 0x325, lbl_806D8C20);
    ((float *)j)[0x2c/4] = f;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void SetScaleY(HSD_JObj *j, float f) {
    if (!j) __assert(lbl_806D8C18, 0x333, lbl_806D8C20);
    ((float *)j)[0x30/4] = f;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void SetScaleZ(HSD_JObj *j, float f) {
    if (!j) __assert(lbl_806D8C18, 0x341, lbl_806D8C20);
    ((float *)j)[0x34/4] = f;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
static inline void SetRotationZ(HSD_JObj *j, float f) {
    if (!j) __assert(lbl_806D8C18, 0x2cc, lbl_806D8C20);
    if (j->flags & 0x20000) __assert(lbl_806D8C18, 0x2cd, EffectFA_Draw_rodata_8036E054);
    j->rotZ = f;
    if (!(j->flags & 0x2000000)) Dirty(j);
}
extern "C" void fn_8016F158(MapEffectFA *self) {
    if (self->state == 0) return;
    Object_SetJObjPositionVec(lbl_806D15D0, &self->position);
    Object_SetJObjRotationY(lbl_806D15D0, self->yaw);
    Object_SetJObjScaleXYZ(lbl_806D15D0, self->radius, self->radius, self->radius);
    Object_SetColorAlphaOnly(lbl_806D15D0, 0, self->alpha);
    Object_SetField8_AndDirty(lbl_806D15D0, self->phase);
    clNormal3D_Exec(lbl_806D15D0);
    Object_RenderJObjTree(lbl_806D15D0, 7);
    float (*matrix)[4] = GetMatrix(lbl_806D15D4);
    Vec3f position;
    position.x = matrix[0][3];
    position.y = matrix[1][3];
    position.z = matrix[2][3];
    for (int i = 0; i < 6; i++) {
        MapEffectPart *p = &self->parts[i];
        if (p->joint && !(p->x <= lbl_806D8C28)) {
            float alphaFactor = self->alpha;
            float partAlpha = lbl_806D8C2C * p->x;
            int alpha = partAlpha * alphaFactor;
            float scale = self->radius * p->scale;
            SetPosition(p->joint, &position);
            SetScaleX(p->joint, scale);
            SetScaleY(p->joint, scale);
            SetScaleZ(p->joint, scale);
            SetRotationZ(p->joint, p->y);
            fn_80182204(p->joint, alpha);
            HSD_JObjDispAll(p->joint, 0, 7, 0);
        }
    }
}
