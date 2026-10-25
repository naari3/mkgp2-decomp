/* RisingTextSprite_Update (0x800B4804): screen-space text sprite (id 0x91)
 * that rises from the screen centre while growing, then is freed once it
 * leaves the top of the 640x480 view. Speed and growth come from the
 * tunable globals in .sdata. Screen coords are unprojected through the
 * course scene's cached projection matrix. */
#include "game/DrawEffectAccess.h"

extern unsigned int lbl_806CF2F8; /* boost frames */
extern float lbl_806CF2FC;        /* -25.0 start velocity */
extern float lbl_806CF300;        /* 2.0 boost accel */
extern float lbl_806CF304;        /* 0.4 accel */
extern float lbl_806CF308;        /* 1.5 boost growth */
extern float lbl_806CF30C;        /* 15.0 max scale */
extern float lbl_806D14B0;        /* growth */
extern const float lbl_806D5020; /* 320.0 */
extern const float lbl_806D5024; /* 240.0 */
extern const float lbl_806D5028; /* 1.0 */
extern const float lbl_806D5034; /* 0.0 */
extern const float lbl_806D506C; /* 0.02 */
extern const float lbl_806D509C; /* 0.0021 */
extern const float lbl_806D50A0; /* -0.0021 */
extern const float lbl_806D5160; /* 720.0 */
extern void *g_courseScene3D;
extern void SpriteSlot_InitLoop(void *slot, int id);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);
extern void SpriteSlot_Container_Free(unsigned char *self);
extern void *CObj_GetProjMatrix_Cached(void *scene);
extern void PSMTXMultVec(void *m, Vec *src, Vec *dst);

static inline void ScreenToWorld(Vec *out, Vec screen)
{
    Vec v;
    v.x = lbl_806D509C * (screen.x - lbl_806D5020);
    v.y = lbl_806D50A0 * (screen.y - lbl_806D5024);
    v.z = screen.z - lbl_806D5028;
    PSMTXMultVec(CObj_GetProjMatrix_Cached(g_courseScene3D), &v, &v);
    Vec3_Copy(out, &v);
}

void RisingTextSprite_Update(unsigned char *self)
{
    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitLoop(SLOT(self), 0x91);
        U8(0x14) = 1;
        SpriteSlot_SetAnimFrameAndApplyScale(SLOT(self), 3, lbl_806D5034);
        GetSpawnPosition(V(0xA0), lbl_806D5020, lbl_806D5024, lbl_806D5034);
        F(0xBC) = lbl_806CF2FC;
        F(0xC4) = lbl_806D5034;
        U32(0xF0) = lbl_806CF2F8;
        S8(0xC8) = 1;
    case 1:
        if (U32(0xF0) != 0) {
            F(0xBC) += lbl_806CF300;
        } else {
            F(0xBC) += lbl_806CF304;
        }
        F(0xA4) += F(0xBC);
        if (U32(0xF0) != 0) {
            F(0xC4) += lbl_806CF308;
        } else {
            F(0xC4) += lbl_806D14B0;
        }
        if (lbl_806CF30C < F(0xC4)) {
            F(0xC4) = lbl_806CF30C;
        }
        if (lbl_806D5160 < F(0xA4)) {
            SpriteSlot_Container_Free(self);
            return;
        }
        break;
    }

    {
        Vec pos;
        float sc;
        ScreenToWorld(&pos, *V(0xA0));
        sc = lbl_806D506C * F(0xC4);
        SpriteSlot_SetTransform(SLOT(self), pos, *V(0xAC), sc);
    }
    if (U32(0xF0) != 0) U32(0xF0)--;
    if (U32(0xF4) != 0) U32(0xF4)--;
    if (U32(0xF8) != 0) U32(0xF8)--;
    if (U32(0xFC) != 0) U32(0xFC)--;
}
