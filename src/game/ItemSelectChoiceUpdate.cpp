#include "game/ItemSelectChoiceUpdatePrivate.h"
#include "game/singleton.h"

extern "C" {
// Shared item-selection palette and default item IDs.
const int lbl_803DC0C0[15][3] = {
    {0, 0, 0},
    {96, 255, 0},
    {200, 64, 0},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
    {0, 96, 255},
};
const int lbl_803DC174[3] = {6, 1, 0};
const int lbl_803DC180[6][10] = {
    {6, 2, 1, 0, 11, 8, 10, 9, 13, 12},
    {7, 3, 4, 5, 22, 23, 44, 27, 43, 59},
    {42, 15, 30, 14, 41, 45, 19, 25, 29, 20},
    {38, 40, 39, 58, 28, 32, 21, 36, 26, 17},
    {24, 31, 35, 34, 33, 18, 37, 16, 47, 51},
    {46, 54, 48, 50, 53, 57, 55, 56, 49, 52},
};
}
static const float choiceX[11] = {102.0f, 144.0f, 185.0f, 227.0f, 269.0f, 310.0f, 352.0f, 394.0f, 435.0f, 477.0f, 532.0f};
static const float choiceY[6] = {230.0f, 261.0f, 292.0f, 323.0f, 354.0f, 385.0f};
static const int choiceResources[3] = {0x1424, 0x1423, 0x1425};

struct ChoiceInput { char pad00[0x14]; int dir, held; };
struct ChoicePoint { float x, y; char rest[0x28]; };
extern "C" {
extern ChoiceInput *g_pInputState;
extern const float lbl_806DB888, lbl_806DB894, lbl_806DB8A4, lbl_806DB8A8, lbl_806DB920;
void fn_8019FF6C(RefillSprite *, int);
void fn_8019FF8C(RefillSprite *, int, ChoicePoint *);
void fn_801F93EC(TextManager *, float, float);
const char *fn_8023DAA8(int);
const char *Item_GetLocalizedAsset(int, int);
void TexMgr_SetTexture(TextManager *, const char *, ...);
void fn_801FE36C();
unsigned char Sprite_AdvanceAnim(RefillSprite *, float);
}
static inline unsigned char ChoiceOccupied(RefillChoice *self) {
    unsigned char occupied = 0;
    if (self->slots[0][0] == self->column && self->slots[0][1] == self->row) occupied = 1;
    else if (self->slots[1][0] == self->column && self->slots[1][1] == self->row) occupied = 1;
    return occupied;
}
extern "C" void fn_8023AC14(RefillChoice *self) {
    if (!self->active) return;
    if (self->count >= 3) return;
    int horizontal = 0;
    int vertical = 0;
    if (self->selected) {
        if (++self->timer == 15) {
            horizontal = 1;
            SpriteAnimParamBlock_Reload(self->groups[1], 0x51);
            fn_8019FF6C(self->groups[1]->sprite, 1);
            SpriteAnimParamBlock_SetAnimParamCached(self->groups[1], 0x17e4, self->count + 0x17e4);
            self->resource = 0x13b9;
            self->selected = 0;
        }
        self->phase = 0;
    } else {
        ChoiceInput *input = SINGLETON_INSTANCE(g_pInputState);
        horizontal = input->dir;
        if (input->held == 3) {
            do {
                ++self->row;
                if (self->row >= 6) self->row = 0;
            } while (ChoiceOccupied(self) == 1);
            unsigned char *player = g_playerData;
            self->done = player[ChoiceItem(self) + 0xa8];
            int resource = (short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(player,
                ChoiceItem(self)), 0);
            if (!self->done) resource = 0x1422;
            SpriteAnimParamBlock_SetAnimParamCached(self->groups[1], self->resource, resource);
            fn_8019FF6C(self->groups[1]->sprite, 1);
            self->resource = resource;
            vertical = 1;
        }
        if (horizontal + vertical) fn_801FE36C();
    }
    fn_8023AA0C(self, horizontal);
    if (self->done == 1) {
        if (++self->phase >= 40) {
            if (self->phase == 40) {
                unsigned char *player = g_playerData;
                ChoicePoint pos;
                fn_8019FF8C(self->groups[0]->sprite, 0x1ecd, &pos);
                fn_801F93EC(self->text[0], pos.x, pos.y);
                fn_8019FF8C(self->groups[0]->sprite, 0x1ecf, &pos);
                fn_801F93EC(self->text[1], pos.x, pos.y);
                fn_8019FF8C(self->groups[0]->sprite, 0x1ed1, &pos);
                fn_801F93EC(self->text[2], pos.x, pos.y);
                fn_8019FF8C(self->groups[0]->sprite, 0x1ed3, &pos);
                fn_801F93EC(self->text[3], pos.x, pos.y);
                int descriptor = PlayerData_ResolveUnlockedIdByIndex(player,
                    ChoiceItem(self));
                TexMgr_SetTexture(self->text[0], fn_8023DAA8(descriptor));
                TexMgr_SetTexture(self->text[1], Item_GetLocalizedAsset(descriptor, 0));
                TexMgr_SetTexture(self->text[2], Item_GetLocalizedAsset(descriptor, 1));
                TexMgr_SetTexture(self->text[3], Item_GetLocalizedAsset(descriptor, 2));
                SpriteAnimParamBlock_SetAnimParamCached(self->groups[0], 0x1ecf, 0x1ecd);
                SpriteAnimParamBlock_SetAnimParamCached(self->groups[0], 0x1ed1, 0x1ecd);
                SpriteAnimParamBlock_SetAnimParamCached(self->groups[0], 0x1ed3, 0x1ecd);
            }
            if (self->phase >= 45) self->phase = 45;
            float fade = (self->phase - lbl_806DB8A4) / lbl_806DB920;
            self->groups[0]->sprite->alpha = fade;
            int alpha = lbl_806DB894 * fade;
            unsigned int color = 0xffffff00;
            color = (color & ~0xffU) + (alpha & 0xff);
            *(unsigned int *)(self->text[0]->data + 0x20) = color;
            *(unsigned int *)(self->text[1]->data + 0x20) = color;
            *(unsigned int *)(self->text[2]->data + 0x20) = color;
            *(unsigned int *)(self->text[3]->data + 0x20) = color;
            *(unsigned int *)(self->text[0]->data + 0x20) = 0xe0202000 | (alpha & 0xff);
        }
    }
    if (self->groups[0] && (horizontal != 0 || vertical != 0)) {
        if (self->row > 2) SpriteAnimParamBlock_Reload(self->groups[0], 0x1a4);
        else SpriteAnimParamBlock_Reload(self->groups[0], 0x1a3);
        self->phase = 0;
        self->groups[0]->sprite->alpha = lbl_806DB888;
        *(unsigned int *)(self->text[0]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->text[1]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->text[2]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->text[3]->data + 0x20) = 0xffffff00;
    }
    RefillChoice *cursor;
    const float *xs;
    const float *ys;
    int i;
    cursor = self;
    ys = choiceY;
    xs = choiceX;
    for (i = 0; i < 4; ++i, cursor = (RefillChoice *)((char *)cursor + 4)) {
        if (cursor->groups[0]) {
            RefillSprite *sprite = cursor->groups[0]->sprite;
            float y = ys[self->row];
            float x = xs[self->column];
            sprite->x = x;
            sprite->y = y;
            Sprite_AdvanceAnim(cursor->groups[0]->sprite, lbl_806DB8A8);
        }
    }
}
