/* Item object manager: draw every active item slot and its ground shadow. */
#include "game/types/Vec3.h"

extern void DbgScene_CopyMatrix3x4Transpose(float (*dst)[4], float (*src)[4]);
#ifdef __MWERKS__
extern float Item_ProbeForwardGroundPitch(Vec3 pos, float yaw, float a, float b);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeForwardGroundPitch(Vec3 *, float, float, float);
static inline float Item_ProbeForwardGroundPitch_ByValue(Vec3 pos, float yaw, float a, float b) { return Item_ProbeForwardGroundPitch(&pos, yaw, a, b); }
#define Item_ProbeForwardGroundPitch Item_ProbeForwardGroundPitch_ByValue
#endif
#ifdef __MWERKS__
extern float Item_ProbeLateralGroundPitch(Vec3 pos, float yaw, float a, float b);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeLateralGroundPitch(Vec3 *, float, float, float);
static inline float Item_ProbeLateralGroundPitch_ByValue(Vec3 pos, float yaw, float a, float b) { return Item_ProbeLateralGroundPitch(&pos, yaw, a, b); }
#define Item_ProbeLateralGroundPitch Item_ProbeLateralGroundPitch_ByValue
#endif
extern void Matrix4_Identity(float (*m)[4]);
extern void Matrix4_PreMultiplyRotX(float (*dst)[4], float (*src)[4], float a);
extern void Matrix4_PreMultiplyRotZ(float (*dst)[4], float (*src)[4], float a);
extern void Mtx44_Scale_Uniform(float (*dst)[4], float (*src)[4], float s);
#ifdef __MWERKS__
extern void Mtx44_Translate(float (*dst)[4], float (*src)[4], Vec3 v);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_Translate(float (*dst)[4], float (*src)[4], Vec3 *);
static inline void Mtx44_Translate_ByValue(float (*dst)[4], float (*src)[4], Vec3 v) { Mtx44_Translate(dst, src, &v); }
#define Mtx44_Translate Mtx44_Translate_ByValue
#endif
extern void Object_BindMatrixSource(void *obj, float (*m)[4], int flag);
extern void Object_DriveAnimMatrix(void *obj);
extern void Object_RenderJObjTree(void *obj, int mask);
extern void Object_SetColorRGBA(void *obj, int mode, float r, float g, float b, float a);
extern void SpriteSlot_RegisterDraw(unsigned char *slot);
extern int Terrain_ApplyCup2FlagPatch(int flags);
extern int Terrain_FlagsToTypeId(int flags);
extern unsigned char Terrain_GetGroundHeightWithPenetration(Vec3 *pos, float *height, int *hit, int *flags, float depth);
extern unsigned char fn_801375D8(Vec3 *pos, float radius);

extern const float lbl_806D5AB0; /* -pi/2 */

#include "game/types/ItemSlot.h"

typedef struct ItemObjectManager {
    ItemSlot slots[256];
    void *shadowObj;
} ItemObjectManager;

/* Inline copy of ItemObject_GetGroundTypeAt. */
static inline signed char ItemObject_GetGroundTypeAt(Vec3 pos, float *height, int hit)
{
    int flags;

    if (!Terrain_GetGroundHeightWithPenetration(&pos, height, &hit, &flags, 10.0f)) {
        return 0;
    }
    flags = Terrain_ApplyCup2FlagPatch(flags);
    return (signed char)Terrain_FlagsToTypeId(flags);
}

/* Ground pitch along the slot's forward and lateral axes. */
static inline float ProbeForward(ItemSlot *slot)
{
    return Item_ProbeForwardGroundPitch(slot->pos, 0.0f, 5.0f, 0.0f);
}

static inline float ProbeLateral(ItemSlot *slot)
{
    return Item_ProbeLateralGroundPitch(slot->pos, 0.0f, 5.0f, 0.0f);
}

/* Draw the shared shadow object under a slot, tilted to the ground. */
static inline void DrawShadow(ItemObjectManager *mgr, ItemSlot *slot, float scale, float alpha, float fwd, float lat)
{
    float m[4][4];
    float mtx[3][4];

    slot->pos.y += 1.0f;
    Object_BindMatrixSource(mgr->shadowObj, mtx, 0);
    Matrix4_Identity(m);
    Matrix4_PreMultiplyRotX(m, m, lbl_806D5AB0);
    Mtx44_Scale_Uniform(m, m, scale);
    Matrix4_PreMultiplyRotZ(m, m, lat);
    Matrix4_PreMultiplyRotX(m, m, fwd);
    Mtx44_Translate(m, m, slot->pos);
    DbgScene_CopyMatrix3x4Transpose(mtx, m);
    Object_DriveAnimMatrix(mgr->shadowObj);
    Object_SetColorRGBA(mgr->shadowObj, 0, 0.0f, 0.0f, 0.0f, alpha * (0.5f * slot->alpha));
    Object_RenderJObjTree(mgr->shadowObj, 7);
}

#pragma exceptions on
void ItemObjectManager_RenderImpl(ItemObjectManager *mgr)
{
    ItemSlot *slot = mgr->slots;
    int i;
    float fwd;
    float lat;
    float scale;
    float alpha;
    float y;

    for (i = 0; i < 256; i++, slot++) {
        if (!slot->active) {
            continue;
        }
        if (slot->sprite[0] & 1) {
            slot->visible = 1;
        } else {
            slot->visible = fn_801375D8(&slot->pos, slot->radius);
        }
        if (slot->visible) {
            if (slot->draw) {
                if (slot->drawArg) {
                    slot->draw(slot->drawArg);
                } else {
                    slot->draw(slot->sprite);
                }
            } else {
                SpriteSlot_RegisterDraw(slot->sprite);
            }
        }
        if (mgr->shadowObj != 0 && slot->visible && slot->shadow && slot->shadowEnabled) {
            y = slot->pos.y;
            if (ItemObject_GetGroundTypeAt(slot->pos, &slot->pos.y, 0)) {
                scale = 0.5f * slot->radius * ((200.0f - (y - slot->pos.y)) / 200.0f);
                if (0.0f < scale) {
                    alpha = 1.0f - 0.005f * (y - slot->pos.y);
                    if (0.0f < alpha) {
                        fwd = ProbeForward(slot);
                        lat = ProbeLateral(slot);
                        DrawShadow(mgr, slot, scale, alpha, fwd, lat);
                    }
                }
            }
        }
    }
}
#pragma exceptions reset
