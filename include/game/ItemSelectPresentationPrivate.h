#ifndef GAME_ITEMSELECTPRESENTATIONPRIVATE_H
#define GAME_ITEMSELECTPRESENTATIONPRIVATE_H
#include "game/ItemSelectRefillPrivate.h"
#include "game/SpriteAnimTraversal_private.h"
struct ItemSelectPresentation {
    RefillGroup *groups[7];
    int handle;
    TextManager *texts[3][4];
    int selected, timer, phase;
    unsigned char done, automatic, pad5e[2];
    int itemIndices[3];
    int resources[3];
};
extern "C" {
void SpriteGroup_CreateOrInit(void *, const char *, int, float, float);
unsigned char fn_8019FF8C(RefillSprite *, int, SpriteAnimSample *);
void fn_801F93EC(TextManager *, float, float);
void TexMgr_SetTexture(TextManager *, const char *, ...);
int Item_GetDescriptorFieldC(int); int Item_GetDescriptorField8(int);
const char *fn_8023DAA8(int); const char *Item_GetLocalizedAsset(int, int);
extern const float lbl_806DB888, lbl_806DB894, lbl_806DB8A8, lbl_806DB8CC;
extern const float lbl_806DB8DC, lbl_806DB910, lbl_806DB918;
extern const float lbl_806DB940, lbl_806DB944, lbl_806DB948, lbl_806DB94C;
extern const float lbl_806DB950, lbl_806DB954, lbl_806DB958, lbl_806DB95C, lbl_806DB960;
extern const float lbl_806DB964, lbl_806DB968, lbl_806DB96C;
extern const char lbl_806D073C[4], lbl_806D0740[4], lbl_806D0744[4];
extern const char lbl_806D0748[4], lbl_806D074C[4], lbl_806D0750[4], lbl_806D0754[4];
extern float lbl_806D0738;
}
static inline void PresentationScale(RefillSprite *sprite, float scale) {
    sprite->sx = scale;
    sprite->sy = scale;
}
static inline void PresentationParams(ItemSelectPresentation *self) {
    if (self->groups[2]) {
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[2], 0x1424, self->resources[0]);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[2], 0x1423, self->resources[1]);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[2], 0x1425, self->resources[2]);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[2], 0x192b, 0x192c);
    }
}
#endif
