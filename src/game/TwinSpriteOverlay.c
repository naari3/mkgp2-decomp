/*
 * TwinSpriteOverlay @ 0x800B1670..0x800B1C88.
 *
 * Two-sprite overlay effect: Update spawns two DrawEffect children and two
 * AnimState instances, registers AddDraw as the draw callback; AddDraw
 * queues Render in the sorted draw list; Render draws the child sprite
 * twice, billboarded towards the camera at two fixed screen offsets.
 */

#include "game/types/Vec3.h"

typedef struct TwinOffsets {
    Vec3 v[3];
} TwinOffsets;

#include "game/types/TwinYaws.h"

typedef float Mtx44[4][4];
typedef float Mtx34[3][4];

extern float AnimState_GetTotalScaleX(void *anim);
extern float AnimState_GetTotalScaleY(void *anim);
extern float AnimState_GetTotalWeight(void *anim);
extern void CObj_ApplyScissor(void *cobj, Vec3 *out);
extern void *CObj_GetProjMatrix_Cached(void *cobj);
extern void CObj_LoadProjMatrix(void *cobj, Vec3 *out);
extern void DbgScene_CopyMatrix3x4Transpose(Mtx34 *dst, Mtx44 *src);
extern void Matrix4_Identity(Mtx44 *m);
extern void Matrix4_PreMultiplyRotX(Mtx44 *dst, Mtx44 *src, float a);
extern void Matrix4_PreMultiplyRotY(Mtx44 *dst, Mtx44 *src, float a);
extern void Mtx44_Scale_PerAxis(Mtx44 *dst, Mtx44 *src, float x, float y, float z);
extern void Mtx44_Translate(Mtx44 *dst, Mtx44 *src, Vec3 *t);
extern void Vec3_Copy(Vec3 *dst, Vec3 *src);
extern float Vec3_HorizontalYawTo(Vec3 *from, Vec3 *to);
extern float Vec3_PitchTo(Vec3 *from, Vec3 *to);
extern void cLNormal3DWrap_Slot_Render(void *slot);
extern void cLNormal3DWrap_Slot_SetMatrixSource(void *slot, Mtx34 *m);
extern void cLNormal3DWrap_Slot_SetRotationQuat(void *slot, float x, float y, float z, float w);
extern void PSMTXMultVec(void *m, Vec3 *src, Vec3 *dst);
extern Vec3 Mtx44_TransformVec3(const float *m, Vec3 v);
extern void clDrawMan_AddSorted_NoDepthBias(void *mgr, void (*fn)(char *), char *obj,
                                            float x, float y, float z, float bias);
extern void *AnimStatePool_Alloc(void *desc);
extern void AnimStatePool_Free(void *anim);
extern unsigned char AnimState_Step(void *anim);
extern void DrawEffect_Free(void *eff);
extern char *DrawEffect_SpawnDirect(void (*fn)(char *));
extern void VfxSlot_BindResource(void *slot, int id);
extern void fn_800AF4F8(char *self);

extern void *g_courseScene3D;
extern void *lbl_806D10AC;
extern TwinYaws lbl_806D5018; /* 8-byte local initializer {yaw0, yaw1} */
extern const float lbl_806D5020;
extern const float lbl_806D5024;
extern const float lbl_806D5028;
extern const float lbl_806D5034;
extern const float lbl_806D5044;
extern const float lbl_806D5098;
extern const float lbl_806D509C;
extern const float lbl_806D50A0;
extern Vec3 TwinSpriteOverlay_AddDraw_rodata_8032948C;
extern TwinOffsets TwinSpriteOverlay_Render_rodata_80329498;
extern float lbl_805DF3D0[];
extern unsigned char TwinSpriteOverlay_Update_data_8041A0E0[];
extern unsigned char TwinSpriteOverlay_Update_data_8041A14C[];

#pragma exceptions on

void TwinSpriteOverlay_Render(char *self) {
    TwinYaws yaws;
    TwinOffsets offsets;
    Mtx44 m;
    Mtx34 m34;
    Vec3 pos;
    Vec3 o;
    Vec3 t;
    Vec3 p;
    Vec3 at;
    Vec3 eye;
    void *wrap;
    float scaleX;
    float scaleY;
    float sx;
    float sy;
    float w;
    float pitch;
    float yaw;
    int i;

    if (*(char **)(self + 0xE0) != 0 && *(void **)(self + 0xD0) != 0) {
        offsets = TwinSpriteOverlay_Render_rodata_80329498;
        yaws = lbl_806D5018;
        wrap = *(void **)(*(char **)(self + 0xE0) + 0x18);
        sx = AnimState_GetTotalScaleX(*(void **)(self + 0xD0));
        sy = AnimState_GetTotalScaleY(*(void **)(self + 0xD0));
        w = AnimState_GetTotalWeight(*(void **)(self + 0xD0));
        w *= *(float *)(self + 0x150);
        scaleX = sx * lbl_806D5098;
        scaleY = sy * lbl_806D5098;
        cLNormal3DWrap_Slot_SetRotationQuat(wrap, lbl_806D5028, lbl_806D5028, lbl_806D5028, w);
        for (i = 0; i < 2; i++) {
            o = offsets.v[i];
            p.x = lbl_806D509C * (o.x - lbl_806D5020);
            p.y = lbl_806D50A0 * (o.y - lbl_806D5024);
            p.z = o.z - lbl_806D5028;
            PSMTXMultVec(CObj_GetProjMatrix_Cached(g_courseScene3D), &p, &p);
            Vec3_Copy(&pos, &p);
            CObj_LoadProjMatrix(g_courseScene3D, &eye);
            CObj_ApplyScissor(g_courseScene3D, &at);
            pitch = Vec3_PitchTo(&at, &eye);
            yaw = Vec3_HorizontalYawTo(&at, &eye);
            Matrix4_Identity(&m);
            Matrix4_PreMultiplyRotY(&m, &m, yaws.y[i]);
            Mtx44_Scale_PerAxis(&m, &m, scaleX, scaleY, lbl_806D5028);
            Matrix4_PreMultiplyRotX(&m, &m, pitch);
            Matrix4_PreMultiplyRotY(&m, &m, yaw);
            t = pos;
            Mtx44_Translate(&m, &m, &t);
            DbgScene_CopyMatrix3x4Transpose(&m34, &m);
            cLNormal3DWrap_Slot_SetMatrixSource(wrap, &m34);
            cLNormal3DWrap_Slot_Render(wrap);
        }
    }
}

void TwinSpriteOverlay_AddDraw(char *self) {
    Vec3 p = TwinSpriteOverlay_AddDraw_rodata_8032948C;
    p = Mtx44_TransformVec3(lbl_805DF3D0, p);
    clDrawMan_AddSorted_NoDepthBias(lbl_806D10AC == 0 ? 0 : lbl_806D10AC,
                                    TwinSpriteOverlay_Render, self, p.x, p.y, p.z,
                                    lbl_806D5034);
}

void TwinSpriteOverlay_Update(char *self) {
    void *anim;
    unsigned char doneA;
    unsigned char doneB;

    switch (*(signed char *)(self + 0xB4)) {
    case 0:
        *(signed char *)(self + 0x14) = 1;
        *(char **)(self + 0xDC) = DrawEffect_SpawnDirect(fn_800AF4F8);
        *(char **)(self + 0xE0) = DrawEffect_SpawnDirect(fn_800AF4F8);
        VfxSlot_BindResource(*(char **)(self + 0xE0) + 0x14, 0x94);
        *(signed char *)(*(char **)(self + 0xDC) + 0x28) = 0;
        *(signed char *)(*(char **)(self + 0xE0) + 0x28) = 0;
        *(void **)(self + 0xCC) = AnimStatePool_Alloc(TwinSpriteOverlay_Update_data_8041A0E0);
        *(void **)(self + 0xD0) = AnimStatePool_Alloc(TwinSpriteOverlay_Update_data_8041A14C);
        *(void (**)(char *))(self + 0x78) = TwinSpriteOverlay_AddDraw;
        *(char **)(self + 0x7C) = self;
        *(signed char *)(self + 0x190) = 0;
        *(float *)(self + 0x150) = lbl_806D5028;
        *(unsigned int *)(self + 0x180) = 3;
        *(unsigned int *)(self + 0x184) = 60;
        (*(signed char *)(self + 0xB4))++;
    case 1:
        break;
    }

    if (*(unsigned int *)(self + 0x180) == 0 &&
        (*(unsigned long long *)(*(char **)(*(char **)(self + 0x11C) + 0x304) + 0x10) &
         0x10000ULL) != 0) {
        *(signed char *)(self + 0x190) = 1;
    }
    if (*(unsigned int *)(self + 0x184) == 0 &&
        (*(unsigned long long *)(*(char **)(*(char **)(self + 0x11C) + 0x304) + 0x10) &
         0x80000000000ULL) == 0) {
        *(signed char *)(self + 0x190) = 1;
    }
    if (*(signed char *)(self + 0x190)) {
        *(float *)(self + 0x150) -= lbl_806D5044;
    }

    anim = *(void **)(self + 0xCC);
    if (anim != 0 && *(void **)(self + 0xD0) != 0) {
        doneA = AnimState_Step(anim);
        doneB = AnimState_Step(*(void **)(self + 0xD0));
        if (doneA || doneB) {
            *(signed char *)(self + 0xC9) = 1;
        }
    } else {
        *(signed char *)(self + 0xC9) = 1;
    }

    if (*(signed char *)(self + 0xC9) || *(float *)(self + 0x150) < lbl_806D5034) {
        if (*(void **)(self + 0xCC) != 0) {
            AnimStatePool_Free(*(void **)(self + 0xCC));
        }
        if (*(void **)(self + 0xD0) != 0) {
            AnimStatePool_Free(*(void **)(self + 0xD0));
        }
        DrawEffect_Free(*(void **)(self + 0xDC));
        DrawEffect_Free(*(void **)(self + 0xE0));
        DrawEffect_Free(self);
    } else {
        if (*(unsigned int *)(self + 0x180) != 0) {
            (*(unsigned int *)(self + 0x180))--;
        }
        if (*(unsigned int *)(self + 0x184) != 0) {
            (*(unsigned int *)(self + 0x184))--;
        }
        if (*(unsigned int *)(self + 0x188) != 0) {
            (*(unsigned int *)(self + 0x188))--;
        }
        if (*(unsigned int *)(self + 0x18C) != 0) {
            (*(unsigned int *)(self + 0x18C))--;
        }
    }
}

#pragma exceptions reset
