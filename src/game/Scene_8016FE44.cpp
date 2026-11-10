/* Native reconstruction of fn_8016FE44. */
#include "game/Scene_8016FE44_private.h"

extern "C" {
extern char lbl_806D8C98[7], lbl_806D8CA0[5];
void __assert(char *, int, char *);
unsigned char fn_801379F0(float *, float);
void HSD_JObjSetFlags(RenderJoint *, unsigned int);
void HSD_JObjClearFlags(RenderJoint *, unsigned int);
void fn_801824D8(RenderJoint *, unsigned int);
void Object_SetJObjPositionX(clNormal3D *, float);
void Object_SetJObjPositionY(clNormal3D *, float);
void Object_SetJObjField40(clNormal3D *, float);
void Object_SetJObjRotationX(clNormal3D *, float);
void Object_SetJObjRotationY(clNormal3D *, float);
void Object_SetJObjRotationZ(clNormal3D *, float);
void Object_RenderJObjTree(clNormal3D *, int);
#ifdef __MWERKS__
void Object_SetColorAlphaOnly(clNormal3D *, float, int);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void Object_SetColorAlphaOnly(clNormal3D *, int, float);
static inline void Object_SetColorAlphaOnly_Reordered(clNormal3D *a0, float a1, int a2) { Object_SetColorAlphaOnly(a0, a2, a1); }
#define Object_SetColorAlphaOnly Object_SetColorAlphaOnly_Reordered
#endif
}
static inline RenderJoint *Child(RenderJoint *j) {
    if (j == 0) {
        return 0;
    }
    return j->child;
}
static inline RenderJoint *Next(RenderJoint *j) {
    if (j == 0) {
        return 0;
    }
    return j->next;
}
static inline void Check(RenderJoint *j, int line) {
    if (!j) __assert(lbl_806D8C98, line, lbl_806D8CA0);
}
#define Clamp01(value) ((value) < 0.0f ? 0.0f : ((value) > 1.0f ? 1.0f : (value)))
static inline void ApplyTransform(SparkRender *s, RenderJoint *j) {
    Check(j, 0x3F1);
    Object_SetJObjPositionX(s->modelB, j->x);
    Check(j, 0x3FD);
    Object_SetJObjPositionY(s->modelB, j->y);
    Check(j, 0x409);
    Object_SetJObjField40(s->modelB, j->z);
    Check(j, 0x2EC);
    Object_SetJObjRotationX(s->modelB, j->rx);
    Check(j, 0x2FA);
    Object_SetJObjRotationY(s->modelB, j->ry);
    Check(j, 0x308);
    Object_SetJObjRotationZ(s->modelB, j->rz);
    Check(j, 0x3F1);
    Object_SetJObjPositionX(s->modelA, j->x);
    Check(j, 0x3FD);
    Object_SetJObjPositionY(s->modelA, j->y);
    Check(j, 0x409);
    Object_SetJObjField40(s->modelA, j->z);
    Check(j, 0x2EC);
    Object_SetJObjRotationX(s->modelA, j->rx);
    Check(j, 0x2FA);
    Object_SetJObjRotationY(s->modelA, j->ry);
    Check(j, 0x308);
    Object_SetJObjRotationZ(s->modelA, j->rz);
}
static inline void SetAlpha(clNormal3D *m, unsigned char alpha) {
    Object_SetColorAlphaOnly(m, (float)alpha / 255.0f, 0);
}
void SparkRender::Draw() {
    if (this->modelB == 0 || this->modelA == 0) return;
    for (int i=0; i<5; i++) {
        CourseSpark *spark = &this->sparks[i];
        if (spark->active) {
            RenderJoint *j = Child(this->root);
            for (int n=0; n<spark->index; n++) j=Next(j);
            Check(j, 0x3E4);
            float pos[3];
            pos[0]=j->x; pos[1]=j->y; pos[2]=j->z;
            if (fn_801379F0(pos, 2200.0f)) {
                for (int k=0; k<4; k++) HSD_JObjSetFlags(this->joints[k], 0x10);
                int alphaA, alphaB;
                RenderJoint *a, *b;
                switch (spark->index & 3) {
                case 0: a=this->joints[0]; b=this->joints[1]; break;
                case 1: a=this->joints[2]; b=this->joints[3]; break;
                case 2: a=this->joints[0]; b=this->joints[2]; break;
                case 3: a=this->joints[3]; b=this->joints[1]; break;
                default: a=0; b=0; break;
                }
                alphaA=(int)(255.0f - 255.0f * Clamp01((float)(spark->timer-5)/60.0f));
                alphaB=(int)(255.0f - 255.0f * Clamp01((float)(spark->timer-10)/60.0f));
                if ((unsigned char)alphaA) {
                    fn_801824D8(a, alphaA);
                    HSD_JObjClearFlags(a, 0x10);
                }
                if ((unsigned char)alphaB && spark->timer>5) {
                    fn_801824D8(b, alphaB);
                    HSD_JObjClearFlags(b, 0x10);
                }
                if (j) ApplyTransform(this,j);
                Object_RenderJObjTree(this->modelB,7);
                int alpha = (unsigned char)alphaA > (unsigned char)alphaB ? alphaA : alphaB;
                float opacity = (float)(unsigned char)alpha / 255.0f;
                Object_SetColorAlphaOnly(this->modelA, opacity, 0);
                Object_RenderJObjTree(this->modelA,7);
            }
        }
    }
}
