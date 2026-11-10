#include "game/types/c_region.h"
C_REGION_BEGIN
/* JumpDistanceMode_InitTimerDisplay @ 0x80213A64: jump-distance timer
 * display constructor. Builds seven digit/label sprites from one local
 * ResCtrl descriptor, resetting it between sprites. */
/* Observed timer display constructor and local ResCtrl lifetime.
 * The empty inline destructor has no normal-path work; its weak EH copy
 * resolves to the existing strong dtor_80082960 at final link. */
C_REGION_END
#pragma cplusplus on
#pragma exceptions on
typedef unsigned char u8;
struct ResCtrl {
    int resourceId;
    char pad04[0x10-4];
    u8 visible;
    char pad11[3];
    float x, y, z;
    char pad20[0x2c-0x20];
    float scaleX, scaleY;
    char pad34[0x58-0x34];
    ResCtrl();
    ~ResCtrl() {}
};
extern "C" void *SpriteHandle_CreateDefault(ResCtrl *, int);
extern "C" void fn_80121E10(ResCtrl *);
extern const float lbl_806DAD70;
extern const float lbl_806DAD7C;
extern const float lbl_806DAE10;
extern const float JumpDistanceMode_rodata_803C3CF0[];
struct JumpTimer {
    int state;
    int value;
    u8 active;
    char pad09[3];
    float elapsed;
    void *sprites[7];
    JumpTimer(int);
};
/* fakematch (pragma): natural code is the same body without the pragma;
 * without it CW sinks the tens digit past the fn_80121E10 reset call. */
#pragma opt_propagation off
JumpTimer::JumpTimer(int input) {
    state = 0;
    value = input;
    active = 0;
    elapsed = lbl_806DAD7C;
    ResCtrl desc;
    desc.resourceId = 0x1b72;
    desc.visible = 1;
    desc.x = JumpDistanceMode_rodata_803C3CF0[0];
    desc.y = JumpDistanceMode_rodata_803C3CF0[1];
    desc.z = lbl_806DAD70;
    sprites[0] = SpriteHandle_CreateDefault(&desc, 4);
    fn_80121E10(&desc);
    desc.resourceId = 0x1ecd;
    desc.visible = 1;
    desc.x = JumpDistanceMode_rodata_803C3CF0[2];
    desc.y = JumpDistanceMode_rodata_803C3CF0[3];
    desc.z = lbl_806DAD70;
    sprites[1] = SpriteHandle_CreateDefault(&desc, 4);
    desc.visible = 1;
    desc.x = JumpDistanceMode_rodata_803C3CF0[4];
    desc.y = JumpDistanceMode_rodata_803C3CF0[5];
    desc.z = lbl_806DAD70;
    sprites[2] = SpriteHandle_CreateDefault(&desc, 4);
    fn_80121E10(&desc);
    desc.resourceId = 0x1b73;
    desc.visible = 1;
    desc.x = JumpDistanceMode_rodata_803C3CF0[6];
    desc.y = JumpDistanceMode_rodata_803C3CF0[7];
    desc.z = lbl_806DAD70;
    sprites[3] = SpriteHandle_CreateDefault(&desc, 4);
    int digit = (input / 100) % 10;
    fn_80121E10(&desc);
    int id = 0x1ecd;
    if (digit != 0) id = digit + 0x1b73;
    desc.resourceId = id;
    desc.visible = 1;
    desc.x = JumpDistanceMode_rodata_803C3CF0[8];
    desc.y = JumpDistanceMode_rodata_803C3CF0[9];
    desc.z = lbl_806DAD70;
    desc.scaleY = desc.scaleX = lbl_806DAE10;
    sprites[4] = SpriteHandle_CreateDefault(&desc, 4);
    int tens = (input / 10) % 10;
    fn_80121E10(&desc);
    desc.resourceId = tens + 0x1b73;
    desc.visible = 1;
    desc.x = JumpDistanceMode_rodata_803C3CF0[10];
    desc.y = JumpDistanceMode_rodata_803C3CF0[11];
    desc.z = lbl_806DAD70;
    desc.scaleY = desc.scaleX = lbl_806DAE10;
    sprites[5] = SpriteHandle_CreateDefault(&desc, 4);
    fn_80121E10(&desc);
    desc.resourceId = input % 10 + 0x1b73;
    desc.visible = 1;
    desc.x = JumpDistanceMode_rodata_803C3CF0[12];
    desc.y = JumpDistanceMode_rodata_803C3CF0[13];
    desc.z = lbl_806DAD70;
    desc.scaleY = desc.scaleX = lbl_806DAE10;
    sprites[6] = SpriteHandle_CreateDefault(&desc, 4);
}
#pragma opt_propagation reset
#pragma exceptions reset
#pragma cplusplus reset
