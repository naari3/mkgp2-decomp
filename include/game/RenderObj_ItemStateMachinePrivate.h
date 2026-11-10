#ifndef RENDEROBJ_ITEMSTATEMACHINE_PRIVATE_H
#define RENDEROBJ_ITEMSTATEMACHINE_PRIVATE_H
#include "sysdolphin/baselib/jobj.h"
typedef float Mtx[3][4];
#include "game/types/Vec3f.h"
struct RenderFlags { char pad[0x10]; unsigned long long bits; };
struct RenderVisibility { char pad[0x14]; unsigned char a, b; };
struct RenderOverlay { char pad[4]; unsigned char active; char pad5[3]; float x, y; };
/* Partial view inferred from the assigned function and neighbouring driver TUs. */
struct RenderItemState {
    void * root; /* +0x0 */
    char pad004[0x8];
    void * output; /* +0xC */
    void * primary; /* +0x10 */
    void * secondary; /* +0x14 */
    void * accessory; /* +0x18 */
    char pad01c[0x4];
    void * effect; /* +0x20 */
    void * animations[49]; /* +0x24 */
    char pad0e8[0x20];
    HSD_JObj * bounceJoint; /* +0x108 */
    HSD_JObj * leftJoint; /* +0x10C */
    HSD_JObj * rightJoint; /* +0x110 */
    char pad114[0x1C];
    HSD_JObj * face0; /* +0x130 */
    HSD_JObj * face1; /* +0x134 */
    HSD_JObj * face2; /* +0x138 */
    char pad13c[0x14];
    HSD_JObj * effectJoint; /* +0x150 */
    HSD_JObj * bindingJoint; /* +0x154 */
    char pad158[0x10];
    void * field168; /* +0x168 */
    char pad16c[0x4];
    float field170; /* +0x170 */
    char pad174[0x8];
    float (*worldMatrix)[4];
    float matrix[3][4]; /* +0x180 */
    char pad1b0[0x8];
    int countdown; /* +0x1B8 */
    char pad1bc[0x4];
    float steering; /* +0x1C0 */
    float smoothSteering; /* +0x1C4 */
    float turnBlend; /* +0x1C8 */
    float frameStep; /* +0x1CC */
    float blendStep; /* +0x1D0 */
    float stateBlend; /* +0x1D4 */
    float returnBlendStep; /* +0x1D8 */
    float returnBlend; /* +0x1DC */
    float frame; /* +0x1E0 */
    float frameEnd; /* +0x1E4 */
    int active; /* +0x1E8 */
    int previousState; /* +0x1EC */
    int state; /* +0x1F0 */
    char pad1f4[0x4];
    int character; /* +0x1F8 */
    char pad1fc[0x8];
    unsigned char stateDone; /* +0x204 */
    unsigned char cleanup; /* +0x205 */
    char pad206[0x96];
    void * itemDisplay; /* +0x29C */
    char pad2a0[0x4];
    int animIndex; /* +0x2A4 */
    signed char face; /* +0x2A8 */
    signed char lastFace; /* +0x2A9 */
    char pad2aa[0x7];
    unsigned char field2b1; /* +0x2B1 */
    unsigned char field2b2; /* +0x2B2 */
    char pad2b3[0xD];
    int item; /* +0x2C0 */
    char pad2c4[0xC];
    unsigned char hasSecondary; /* +0x2D0 */
    char pad2d1[0x3];
    float turnTransition; /* +0x2D4 */
    int turnBank; /* +0x2D8 */
    void * slots[10]; /* +0x2DC */
    RenderFlags * flags; /* +0x304 */
    char pad308[0x4];
    void * tireFx; /* +0x30C */
    char pad310[0x8];
    float bouncePhase; /* +0x318 */
    float sway; /* +0x31C */
    float swayPhase; /* +0x320 */
    float leftY; /* +0x324 */
    float rightY; /* +0x328 */
    void * itemEffects; /* +0x32C */
    char pad330[0x8];
    Vec3f velocity; /* +0x338 */
    RenderVisibility * visibility; /* +0x344 */
    char pad348[0x14];
    void * field35c; /* +0x35C */
    RenderOverlay * overlay; /* +0x360 */
    char pad364[0x4];
    unsigned char freezeAnim; /* +0x368 */
    char pad369[0xB];
    int field374; /* +0x374 */
    void * field378; /* +0x378 */
    float idleFrameStep; /* +0x37C */
    void * field380; /* +0x380 */
};
#endif
