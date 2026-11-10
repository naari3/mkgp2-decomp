/*
 * clFlowItemSelect_CommitSlotAnim (0x801CB620, 0x1F8): rebuild the item
 * slot's sprite animation keys from the item descriptor, recolour the slot's
 * four labels, and pin each label to its layout anchor (evaluated at the
 * anim's end time, then the anim time is restored).
 */

typedef struct Sprite Sprite;
typedef struct TextManager TextManager;

#include "game/types/SpriteAnimParamBlock.h"

typedef struct TextColorView {
    char pad00[0x20];
    unsigned int color; /* 0x20 */
} TextColorView;

typedef struct ItemSelectSlotLabels {
    TextColorView *label[4];
} ItemSelectSlotLabels;

typedef struct clFlowItemSelect {
    char pad00[0x80];
    SpriteAnimParamBlock *anim[6];      /* 0x80 */
    ItemSelectSlotLabels labels[1];     /* 0x98 (per slot) */
} clFlowItemSelect;

/* Sprite node record filled by fn_8019FF8C (position first). */
#include "game/types/SpriteNodeInfo.h"

extern int Item_GetDescriptorField0(int item, unsigned char *outAlias);
extern int Item_GetDescriptorField8(int item);
extern int Item_GetDescriptorFieldC(int item);
extern void SpriteAnimParamBlock_Reload(SpriteAnimParamBlock *block, int arg);
extern void SpriteAnimParamBlock_SetAnimParamCached(SpriteAnimParamBlock *block, int oldParam, int newParam);
extern void SpriteAnimParamBlock_SetKey(SpriteAnimParamBlock *block, int key, int param);
extern void Sprite_SetAnimTime(Sprite *sprite, float time);
extern float fn_8019FEBC(Sprite *sprite);
extern float fn_8019FED8(Sprite *sprite);
extern unsigned char fn_8019FF8C(Sprite *sprite, int key, SpriteNodeInfo *out);
extern void fn_801A0550(Sprite *sprite);
extern void fn_801F93EC(TextColorView *text, float x, float y);

#pragma use_lmw_stmw on
#pragma exceptions on

void clFlowItemSelect_CommitSlotAnim(clFlowItemSelect *self, int slot, int item)
{
    Sprite *sprite;
    float savedTime;
    SpriteNodeInfo pos;
    int n;
    int i;

    SpriteAnimParamBlock_Reload(self->anim[slot], 0x53);
    fn_801A0550(self->anim[slot]->sprite);
    SpriteAnimParamBlock_SetKey(self->anim[slot], 0x13B9, Item_GetDescriptorField0(item, 0));
    n = Item_GetDescriptorFieldC(item);
    SpriteAnimParamBlock_SetKey(self->anim[slot], 0x1E1D, n < 0 ? -1 : n + 0x1E1D);
    n = Item_GetDescriptorField8(item);
    SpriteAnimParamBlock_SetKey(self->anim[slot], 0x17A4, n < 0 ? -1 : n + 0x17A3);

    for (i = 0; i < 4; i++) {
        self->labels[slot].label[i]->color = 0xFFFFFF00;
    }
    self->labels[slot].label[0]->color = 0xE0202000;

    savedTime = fn_8019FED8(self->anim[slot]->sprite);
    sprite = self->anim[slot]->sprite;
    Sprite_SetAnimTime(sprite, fn_8019FEBC(sprite));

    fn_8019FF8C(self->anim[slot]->sprite, 0x1ECD, &pos);
    fn_801F93EC(self->labels[slot].label[0], pos.x, pos.y);
    fn_8019FF8C(self->anim[slot]->sprite, 0x1ECF, &pos);
    fn_801F93EC(self->labels[slot].label[1], pos.x, pos.y);
    fn_8019FF8C(self->anim[slot]->sprite, 0x1ED1, &pos);
    fn_801F93EC(self->labels[slot].label[2], pos.x, pos.y);
    fn_8019FF8C(self->anim[slot]->sprite, 0x1ED3, &pos);
    fn_801F93EC(self->labels[slot].label[3], pos.x, pos.y);

    Sprite_SetAnimTime(self->anim[slot]->sprite, savedTime);
    SpriteAnimParamBlock_SetAnimParamCached(self->anim[slot], 0x1ECF, 0x1ECD);
    SpriteAnimParamBlock_SetAnimParamCached(self->anim[slot], 0x1ED1, 0x1ECD);
    SpriteAnimParamBlock_SetAnimParamCached(self->anim[slot], 0x1ED3, 0x1ECD);
}

#pragma exceptions reset
#pragma use_lmw_stmw reset
