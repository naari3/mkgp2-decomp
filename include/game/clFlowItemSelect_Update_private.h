#ifndef GAME_CLFLOWITEMSELECT_UPDATE_PRIVATE_H
#define GAME_CLFLOWITEMSELECT_UPDATE_PRIVATE_H
#include "game/SpritePairOwner.h"
struct ItemSelectRoll {
    unsigned char locked, pad01[7];
    int item, timer;
    struct Entry { int item, weight; } *entries;
    int count;
    int fallback[5];
};
struct ItemSelectGroup { Sprite *sprite; };
struct ItemSelectFlow {
    char pad00[0x10];
    int intro, field14, ticks, mode;
    float brightness;
    char pad24[0x80-0x24];
    ItemSelectGroup *groups[5];
    int handle;
    char pad98[0xdc-0x98];
    ItemSelectRoll *rolls[3];
    void *child;
};
extern "C" {
void RumbleUpdate(void);
void UI_PlaySeDecide(void);
void SpriteAnimParamBlock_Reload(void *, int);
void SpriteAnimParamBlock_SetKey(void *, int, int);
void SpriteGroup_CreateOrInit(void *, const char *, int, float, float);
int Rand15(void);
int Item_GetDescriptorField0(int, void *);
int Item_GetDescriptorFieldC(int);
int Item_GetDescriptorField8(int);
void fn_801699D8(int, int);
void fn_8023CDA8(void *);
void SetScreenBrightness(float);
void fn_801B7EF8(void);
void *ItemDisplay_GetOrCreate(void);
void ItemDisplay_Update(void *);
void fn_801CB818(ItemSelectFlow *);
extern const char clFlowItemSelect_Update_data_806CFE18[4];
extern const float lbl_806D9DBC, lbl_806D9DD0, lbl_806D9DD4, lbl_806D9DD8, lbl_806D9DDC, lbl_806D9DE0, lbl_806D9DE4, lbl_806D9DE8, lbl_806D9DEC, lbl_806D9DF0, lbl_806D9DF4, lbl_806D9DB0, lbl_806D9DF8;
}
#endif
