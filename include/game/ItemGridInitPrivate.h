#ifndef ITEM_GRID_INIT_PRIVATE_H
#define ITEM_GRID_INIT_PRIVATE_H
#include "game/FlowScene.h"
struct GridInitState {
    void *groups[7];
    int handle;
    TextManager *texts[3][4];
    int selected, timer, phase;
    unsigned char done, automatic, pad5e[2];
    int itemIndices[3], resources[3];
};
extern "C" {
void PreloadResource(int);
int SpriteHandle_CreateDefault(ResCtrl *, int);
void SpriteHandle_SetActiveFlag(int, int);
void SpriteHandle_RecomputeCull(int);
extern unsigned char g_playerData[];
extern int g_characterId;
unsigned char fn_8023D860(int);
int fn_8023D7A8(int);
int fn_8023D844(int,int);
int PlayerData_ResolveUnlockedIdByIndex(void *, int);
int Item_GetDescriptorField0(int,int);
extern const float lbl_806DB8DC, lbl_806DB940, lbl_806DB8CC, lbl_806DB8A0;
extern const char lbl_806DB8F8[4];
extern int ItemGridState_Init_rodata_803DC174[3];
}
#endif
