#include "game/singleton.h"
#include "game/ItemSelectRefillPrivate.h"
void *operator new(unsigned long);
void operator delete(void *) throw();
struct RefillInput { char pad00[0x18]; int held; };
struct RefillSingleton { char opaque[0x5c]; RefillSingleton(); };
extern "C" {
extern RefillInput *g_pInputState;
extern RefillSingleton *lbl_806D1A88;
extern const float lbl_806DB888, lbl_806DB894, lbl_806DB89C, lbl_806DB8A0, lbl_806DB8A8;
extern const float lbl_806DB8CC, lbl_806DB8D4, lbl_806DB8DC, lbl_806DB8E8;
extern const float lbl_806DB914, lbl_806DB918, lbl_806DB91C, lbl_806DB920;
void SpriteHandle_SetCornerAlpha(int, int);
void fn_8011F804(int, float, float);
void SpriteAnimHandle_Destroy(void *, int);
void fn_801FE300();
void fn_801FE324();
void fn_80232284(RefillSingleton *, float);
void fn_8023AC14(RefillChoice *);
unsigned char Sprite_AdvanceAnim(RefillSprite *, float);
void SpriteHandle_RecomputeCull(int);
}
static inline int GridItem(const int (*items)[10], int column, int row) {
    int character = g_characterId;
    if (character < 0) character = 0;
    if (character >= 13) character = 0;
    if (column >= 10) return fn_8023D844(character, row);
    int offset = row * sizeof(items[0]) + column * sizeof(items[0][0]);
    return *(const int *)((const char *)items + offset);
}
static inline void SelectChoice(RefillChoice *choice, int slot, const RefillLayout *layout, const int *resources) {
    unsigned char *playerData = g_playerData;
    choice->selected = 1;
    choice->timer = 0;
    SpriteAnimParamBlock_Reload(choice->groups[1], slot + 0x4e);
    int resource = (short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(playerData,
        GridItem(layout->items, choice->column, choice->row)), 0);
    SpriteAnimParamBlock_SetAnimParamCached(choice->groups[1], resources[slot], resource);
    SpriteAnimParamBlock_SetAnimParamCached(choice->groups[1], 0x13b9, resource);
    choice->slots[slot][0] = choice->column;
    choice->slots[slot][1] = choice->row;
    choice->count = slot + 1;
    choice->phase = 0;
}
#pragma fp_contract off
static inline float SlideX(int offset, float x) {
    float slide = lbl_806DB8D4 * (offset * lbl_806DB918);
    return slide + x;
}
#pragma fp_contract reset
static inline RefillSingleton *GetRefillSingleton() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new RefillSingleton);
}
static inline RefillSprite *GroupSprite(void *group) { return ((RefillGroup *)group)->sprite; }
extern "C" void fn_80238D9C(ItemSelectState *self) {
    int row;
    int i;
    const RefillLayout *layout = &lbl_803DC0C0;
    if (self->doneFlag == 1) return;
    RefillInput *input = SINGLETON_INSTANCE(g_pInputState);
    void *playerData = g_playerData;
    switch (self->phase) {
    case 0: break;
    case 2: break;
    case 1: {
        if (self->resultCode >= 8 && self->resultCode <= 15) {
            float fade = (self->resultCode - 8) / lbl_806DB914;
            if (fade < lbl_806DB888) fade = lbl_806DB888;
            int alpha = lbl_806DB894 * fade;
            SpriteHandle_SetCornerAlpha(self->sprites[1], alpha);
            SpriteHandle_SetCornerAlpha(self->sprites[2], alpha);
            SpriteHandle_SetActiveFlag(self->sprites[1], 1);
            SpriteHandle_SetActiveFlag(self->sprites[2], 1);
            unsigned int color = -256;
            color = (color & ~0xffU) | (alpha & 0xff);
            *(unsigned int *)(self->auxBuffer->data + 0x20) = color;
        }
        if (self->resultCode < 25) {
            const float *ys = layout->y;
            for (row = 0; row < 6; ++row) {
                float y = ys[row];
                const float *xs = layout->x;
                for (i = 0; i < 11; ++i) {
                    int offset = 8 - (self->resultCode - (row + i));
                    if (offset > 8) offset = 8;
                    if (offset < 0) offset = 0;
                    fn_8011F804(self->itemSprites[row * 11 + i],
                        SlideX(offset, xs[i]), y);
                }
            }
        }
        if (self->resultCode >= 15) {
            if (self->groups[0]) {
                SpriteAnimHandle_Destroy(self->groups[0], 1);
                self->groups[0] = 0;
            }
            SpriteHandle_SetActiveFlag(self->sprites[0], 1);
        }
        if (self->resultCode >= 25) {
            self->shownFlag = 1;
            self->phase = 2;
        }
        break;
    }
    case 3:
        self->field148 = lbl_806DB91C * (self->resultCode / lbl_806DB920);
        if (self->resultCode >= 5) self->phase = 2;
        SpriteHandle_SetCornerAlpha(self->sprites[4], (unsigned char)self->field148);
        break;
    case 4:
        self->field148 = lbl_806DB91C * (lbl_806DB8CC - self->resultCode / lbl_806DB920);
        if (self->resultCode >= 5) {
            self->field148 = 0;
            self->phase = 5;
            SpriteHandle_SetActiveFlag(self->sprites[4], 0);
        }
        SpriteHandle_SetCornerAlpha(self->sprites[4], (unsigned char)self->field148);
        break;
    case 5: {
        if (input->held == 1) {
            RefillChoice *choice = (RefillChoice *)self->iconArray;
            if (choice->selected == 0 && choice->done == 1) {
                i = choice->column;
                row = choice->row;
                struct SlotsView { char padding[0x15c]; int slots[3][3]; };
                SlotsView *view = (SlotsView *)self;
                view->slots[self->field14c][0] = i;
                view->slots[self->field14c][1] = row;
                view->slots[self->field14c][2] = GridItem(layout->items, i, row);
                SelectChoice((RefillChoice *)self->iconArray, self->field14c, layout, layout->resources);
                int item = Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(playerData,
                    view->slots[self->field14c][2]), 0);
                SpriteAnimParamBlock_SetAnimParamCached(self->groups[self->field14c + 3], 0x13b9, item);
                RefillSprite *sprite = GroupSprite(self->groups[self->field14c + 3]);
                sprite->x = layout->x[i];
                sprite->y = layout->y[row];
                SpriteHandle_SetActiveFlag(self->itemSprites[row * 11 + i], 0);
                int resource = 0x1424;
                if (self->field14c == 1) resource = 0x1423;
                if (self->field14c == 2) resource = 0x1425;
                SpriteAnimParamBlock_SetAnimParamCached(self->groups[6], resource, item);
                ++self->field14c;
                if (self->field14c > 2) fn_801FE300();
                fn_801FE324();
            }
        }
        if (self->field14c > 2) {
            self->phase = 6;
            self->resultCode = 0;
        }
        break;
    }
    case 6:
        fn_80232284(GetRefillSingleton(), lbl_806DB8A0);
        if (self->resultCode == 90) self->doneFlag = 1;
        break;
    }
    ++self->resultCode;
    fn_8023AC14((RefillChoice *)self->iconArray);
    if (self->groups[8]) {
        GroupSprite(self->groups[8])->y = lbl_806DB89C * ((RefillChoice *)self->iconArray)->row + lbl_806DB8E8;
        GroupSprite(self->groups[7])->y = lbl_806DB89C * ((RefillChoice *)self->iconArray)->row + lbl_806DB8E8;
    }
    fn_8011F804(self->sprites[3], lbl_806DB8DC, layout->y[((RefillChoice *)self->iconArray)->row]);
    ItemSelectState *cursor;
    for (i = 0, cursor = self; i < 9; ++i, cursor = (ItemSelectState *)((char *)cursor + 4)) {
        if (cursor->groups[0]) Sprite_AdvanceAnim(GroupSprite(cursor->groups[0]), lbl_806DB8A8);
    }
    for (i = 0, cursor = self; i < 66; ++i, cursor = (ItemSelectState *)((char *)cursor + 4))
        SpriteHandle_RecomputeCull(cursor->itemSprites[0]);
    for (i = 0, cursor = self; i < 5; ++i, cursor = (ItemSelectState *)((char *)cursor + 4))
        SpriteHandle_RecomputeCull(cursor->sprites[0]);
}
