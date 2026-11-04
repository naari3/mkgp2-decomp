#include "game/ItemSelectRefillPrivate.h"
void *operator new(unsigned long);
void operator delete(void *) throw();
extern "C" {
void SpriteGroup_CreateOrInit(void *, const void *, int, float, float);
void SpriteHandle_SetCornerAlpha(int, int);
unsigned char fn_801D6F30(void *, int, int);
void TexMgr_SetTexture(TextManager *, const char *, ...);
void fn_801F8E90(TextManager *);
extern const int lbl_806D0728, lbl_806D072C, lbl_806D0730, lbl_806D0734;
extern const int lbl_806D075C, lbl_806D0760, lbl_806D0764, lbl_806D0768;
extern const int lbl_806D076C, lbl_806D0770, lbl_806D0774, lbl_806D0778;
extern const float lbl_806DB888, lbl_806DB8A0;
extern const float lbl_806DB8E4, lbl_806DB8E8, lbl_806DB8EC, lbl_806DB8F0, lbl_806DB8F4;
extern const float lbl_806DB8FC, lbl_806DB900, lbl_806DB904, lbl_806DB908, lbl_806DB90C, lbl_806DB910;
extern const char lbl_806DB8F8[2];
}
static inline RefillSprite *GroupSprite(void *group) { return ((RefillGroup *)group)->sprite; }
static inline int CharacterOrder(int id) {
    if (id == 0) return 0;
    if (id == 1) return 1;
    if (id == 8) return 2;
    if (id == 11) return 3;
    if (id == 3) return 4;
    if (id == 7) return 5;
    if (id == 10) return 6;
    if (id == 12) return 7;
    if (id == 9) return 8;
    if (id == 5) return 9;
    if (id == 2) return 10;
    if (id == 6) return 11;
    if (id == 4) return 12;
    return 0;
}
extern "C" void fn_80238980(ItemSelectState *self) {
    SpriteGroup_CreateOrInit(&self->groups[8], &lbl_806D075C, 1, lbl_806DB8E4, lbl_806DB8E8);
    SpriteGroup_CreateOrInit(&self->groups[7], &lbl_806D0760, 1, lbl_806DB8EC, lbl_806DB8E8);
    GroupSprite(self->groups[8])->layer = 6;
    GroupSprite(self->groups[7])->layer = 6;
    SpriteHandle_SetCornerAlpha(self->sprites[3], 255);
    SpriteHandle_SetActiveFlag(self->sprites[3], 1);
    RefillChoice *choice = (RefillChoice *)self->iconArray;
    SpriteGroup_CreateOrInit(&choice->groups[1], &lbl_806D0728, 1, lbl_806DB888, lbl_806DB888);
    SpriteGroup_CreateOrInit(&choice->groups[2], &lbl_806D072C, 1, lbl_806DB888, lbl_806DB888);
    SpriteGroup_CreateOrInit(&choice->groups[3], &lbl_806D0730, 1, lbl_806DB888, lbl_806DB888);
    SpriteGroup_CreateOrInit(&choice->groups[0], &lbl_806D0734, 0, lbl_806DB8F0, lbl_806DB8F4);
    choice->groups[1]->sprite->layer = 6;
    choice->groups[2]->sprite->layer = 6;
    choice->groups[3]->sprite->layer = 6;
    choice->groups[0]->sprite->layer = 6;
    if (fn_801D6F30(g_playerData, 63, 0) == 1) {
        SpriteAnimParamBlock_SetAnimParamCached(choice->groups[1], 0x13b9, 0x13be);
        choice->resource = 0x13be;
    }
    choice->groups[0]->sprite->alpha = lbl_806DB888;
    int i;
    RefillChoice *cursor = choice;
    for (i = 0; i < 4; ++i, cursor = (RefillChoice *)((char *)cursor + 4)) {
        cursor->text[0] = new TextManager;
        TexMgr_SetTexture(cursor->text[0], lbl_806DB8F8);
        *(float *)(cursor->text[0]->data + 0x22c) = lbl_806DB8A0;
        fn_801F8E90(cursor->text[0]);
    }
    choice->phase = 0;
    choice->active = 1;
    self->resultCode = 0;
    self->phase = 4;
    SpriteGroup_CreateOrInit(&self->groups[1], &lbl_806D0764, 0, lbl_806DB888, lbl_806DB8FC);
    SpriteGroup_CreateOrInit(&self->groups[2], &lbl_806D0768, 0, lbl_806DB900, lbl_806DB904);
    SpriteGroup_CreateOrInit(&self->groups[6], &lbl_806D076C, 0, lbl_806DB908, lbl_806DB90C);
    SpriteGroup_CreateOrInit(&self->groups[3], &lbl_806D0770, 0, lbl_806DB8F0, lbl_806DB8F4);
    SpriteGroup_CreateOrInit(&self->groups[4], &lbl_806D0774, 0, lbl_806DB8F0, lbl_806DB8F4);
    SpriteGroup_CreateOrInit(&self->groups[5], &lbl_806D0778, 0, lbl_806DB8F0, lbl_806DB8F4);
    int character = CharacterOrder(g_characterId) * 3;
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[2], 0x17bc, character + 0x17bc);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[2], 0x17bd, character + 0x17bd);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[2], 0x17be, character + 0x17be);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[4], 0x17e4, 0x17e5);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[5], 0x17e4, 0x17e6);
    GroupSprite(self->groups[1])->layer = 5;
    GroupSprite(self->groups[2])->layer = 5;
    GroupSprite(self->groups[3])->layer = 5;
    GroupSprite(self->groups[4])->layer = 5;
    GroupSprite(self->groups[5])->layer = 5;
    RefillSprite *sprite = GroupSprite(self->groups[3]);
    sprite->sx = lbl_806DB910; sprite->sy = lbl_806DB910;
    sprite = GroupSprite(self->groups[4]);
    sprite->sx = lbl_806DB910; sprite->sy = lbl_806DB910;
    sprite = GroupSprite(self->groups[5]);
    sprite->sx = lbl_806DB910; sprite->sy = lbl_806DB910;
}
