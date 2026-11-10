/* Item-select scene: item grid choice cursor, three-item selection and the
   result presentation. One original TU (0x802386E0..0x8023B1A8, merged from ten
   over-split files): every table and string below is in its .rodata pool
   (0x803DC0C0..0x803DC318), reached off one section anchor. Split apart, the
   anchor offsets turn into separate lis/addi pairs, and a pointer past the end
   of a sized array gets a worst-case alias (optimizer/Alias.c make_alias), so
   fn_80238D9C and the ctor only match with the data owned here. */
#include "game/types/size_t.h"
#include "game/singleton.h"
#include "game/ItemSelectState.h"
#include "game/SpriteAnimTraversal_private.h"

void *operator new(size_t);
void operator delete(void *) throw();

#include "game/types/RefillSprite.h"
#include "game/types/RefillGroup.h"
#include "game/types/RefillChoice.h"
struct ItemSelectPresentation {
    RefillGroup *groups[7];
    int handle;
    TextManager *texts[3][4];
    int selected, timer, phase;
    unsigned char done, automatic, pad5e[2];
    int itemIndices[3];
    int resources[3];
};
struct ResCtrl {
    int resId; int field4, mode, fieldc; unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4]; int tail[5];
    ResCtrl(); ~ResCtrl() {}
};
#include "game/types/PlayerData.h"
struct ItemSelectInput { char pad00[0x14]; int dir, held; };
struct RefillSingleton { char opaque[0x5c]; RefillSingleton(); };

extern "C" {
// Shared item-selection palette and default item IDs.
const int ItemSelectState_rodata_803DC0C0[15][3] = {
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
const int ItemGridState_Init_rodata_803DC174[3] = {6, 1, 0};
const int ItemSelectState_rodata_803DC180[6][10] = {
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
extern "C" const char lbl_803DC2C0[] = "clFlowItem";
extern "C" const char sdata_806D0728_rodata_803DC2CC[] = "clFlowProcess";
/* "Choose three items" */
static const char selectMessage[] = "\x83\x41\x83\x43\x83\x65\x83\x80\x82\xf0\x82\x52\x82\xc2\x91\x49\x82\xf1\x82\xc5\x89\xba\x82\xb3\x82\xa2";
static const char selectMessageEn[] = "3 items will be selected";

extern "C" {
extern unsigned char g_playerData[];
extern int g_characterId;
extern unsigned char lbl_806D1264[3];
extern ItemSelectInput *g_pInputState;
extern RefillSingleton *lbl_806D1A88;
void fn_8023AA0C(RefillChoice *, int);
void fn_8023AC14(RefillChoice *);
int fn_8023D844(int, int);
unsigned char fn_8023D860(int);
int fn_8023D7A8(int);
int PlayerData_ResolveUnlockedIdByIndex(void *, int);
int Item_GetDescriptorField0(int, void *);
int Item_GetDescriptorFieldC(int);
int Item_GetDescriptorField8(int);
const char *fn_8023DAA8(int);
const char *Item_GetLocalizedAsset(int, int);
void SpriteAnimParamBlock_Reload(void *, int);
void SpriteAnimParamBlock_SetAnimParamCached(void *, int, int);
void SpriteGroup_CreateOrInit(void *, const void *, int, float, float);
void SpriteAnimHandle_Destroy(void *, int);
void PreloadResource(int);
void fn_80121E10(ResCtrl *);
unsigned int SpriteHandle_CreateDefault(ResCtrl *, int);
void SpriteHandle_SetActiveFlag(int, int);
void SpriteHandle_SetCornerAlpha(int, int);
void SpriteHandle_RecomputeCull(int);
void SpriteHandle_Destroy(unsigned int);
int Sprite_AdvanceAnim(RefillSprite *, float);
void fn_8011F804(int, float, float);
void fn_80120A08(int);
void fn_8019FF6C(RefillSprite *, int);
unsigned char fn_8019FF8C(RefillSprite *, int, void *);
unsigned char fn_801D6F30(void *, int, int);
int isJapanese();
void TexMgr_SetTexture(TextManager *, const char *, ...);
void fn_801F93EC(TextManager *, float, float);
void fn_801F8E90(TextManager *);
void fn_801FE300();
void fn_801FE324();
void fn_801FE348();
void fn_801FE36C();
void fn_801FE390();
void fn_80232284(RefillSingleton *, float);
void fn_8023F1C8(void *);
extern const int ItemSelectState_data_806D0728, ItemSelectState_data_806D072C, ItemSelectState_data_806D0730, ItemSelectState_data_806D0734;
extern const char ItemSelectState_data_806D073C[4], ItemSelectState_data_806D0740[4], ItemSelectState_data_806D0744[4];
extern const char ItemSelectState_data_806D0748[4], ItemSelectState_data_806D074C[4], ItemSelectState_data_806D0750[4], ItemSelectState_data_806D0754[4];
extern const int ItemSelectState_data_806D075C, ItemSelectState_data_806D0760, ItemSelectState_data_806D0764, ItemSelectState_data_806D0768;
extern const int ItemSelectState_data_806D076C, ItemSelectState_data_806D0770, ItemSelectState_data_806D0774, ItemSelectState_data_806D0778;
extern float ItemSelectState_data_806D0738;
extern const float lbl_806DB888, lbl_806DB88C, lbl_806DB890, lbl_806DB894, lbl_806DB89C;
extern const float lbl_806DB8A0, lbl_806DB8A4, lbl_806DB8A8, lbl_806DB8CC, lbl_806DB8D4;
extern const float lbl_806DB8D8, lbl_806DB8DC, lbl_806DB8E0, lbl_806DB8E4, lbl_806DB8E8;
extern const float lbl_806DB8EC, lbl_806DB8F0, lbl_806DB8F4, lbl_806DB8FC, lbl_806DB900;
extern const float lbl_806DB904, lbl_806DB908, lbl_806DB90C, lbl_806DB910, lbl_806DB914;
extern const float lbl_806DB918, lbl_806DB91C, lbl_806DB920, lbl_806DB924, lbl_806DB928;
extern const float lbl_806DB92C, lbl_806DB930, lbl_806DB934, lbl_806DB938, lbl_806DB93C;
extern const float lbl_806DB940, lbl_806DB944, lbl_806DB948, lbl_806DB94C, lbl_806DB950;
extern const float lbl_806DB954, lbl_806DB958, lbl_806DB95C, lbl_806DB960, lbl_806DB964;
extern const float lbl_806DB968;
extern const char lbl_806DB8F8[4];
}

static inline int ChoiceColumn(const RefillChoice *choice) { return choice->column; }
static inline RefillSprite *GroupSprite(void *group) { return ((RefillGroup *)group)->sprite; }
static inline int RefillItem(int column, int row) {
    int character = g_characterId;
    if (character < 0) character = 0;
    if (character >= 13) character = 0;
    if (column >= 10) return fn_8023D844(character, row);
    const int (*items)[10] = ItemSelectState_rodata_803DC180;
    return items[row][column];
}
static inline void CompleteChoice(RefillChoice *choice, int slot, const int *resources, void *playerData) {

        if (choice->selected == 1) fn_8023AA0C(choice, 1);
        while (true) {
            if (choice->done == 1) break;
            fn_8023AA0C(choice, 1);
        }
        choice->selected = 1;
        choice->timer = 0;
        SpriteAnimParamBlock_Reload(choice->groups[1], slot + 0x4e);
        int resource = (short) Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(playerData,
            RefillItem(choice->column, choice->row)), 0);
        SpriteAnimParamBlock_SetAnimParamCached(choice->groups[1], resources[slot], resource);
        SpriteAnimParamBlock_SetAnimParamCached(choice->groups[1], 0x13b9, resource);
        choice->slots[slot][0] = choice->column;
        choice->slots[slot][1] = choice->row;
        choice->count = slot + 1;
        choice->phase = 0;
        choice->done = 0;
}
static inline void SetRefillPosition(RefillSprite *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}
extern "C" void fn_802386E0(ItemSelectState *self) {
    void *playerData;
    while (self->field14c < 3) {
        int slot = self->field14c;
        CompleteChoice((RefillChoice *)self->iconArray, slot, choiceResources, playerData = g_playerData);
        RefillChoice *choice;
        choice = (RefillChoice *)self->iconArray;
        int column = ChoiceColumn(choice);
        int row = choice->row;
        int *slots = (int *)self;
        slots[self->field14c * 3 + 0x57] = column;
        slots[self->field14c * 3 + 0x58] = row;
        slots[self->field14c * 3 + 0x59] = RefillItem(column, row);
        int item = Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(playerData,
            slots[self->field14c * 3 + 0x59]), 0);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[self->field14c + 3], 0x13b9, item);
        SetRefillPosition(((RefillGroup *)self->groups[self->field14c + 3])->sprite,
            choiceX[column], choiceY[row]);
        SpriteHandle_SetActiveFlag(self->itemSprites[row * 11 + column], 0);
        int oldResource = 0x1424;
        if (self->field14c == 1) oldResource = 0x1423;
        if (self->field14c == 2) oldResource = 0x1425;
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[6], oldResource, item);
        ++self->field14c;
    }
}
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
    SpriteGroup_CreateOrInit(&self->groups[8], &ItemSelectState_data_806D075C, 1, lbl_806DB8E4, lbl_806DB8E8);
    SpriteGroup_CreateOrInit(&self->groups[7], &ItemSelectState_data_806D0760, 1, lbl_806DB8EC, lbl_806DB8E8);
    GroupSprite(self->groups[8])->layer = 6;
    GroupSprite(self->groups[7])->layer = 6;
    SpriteHandle_SetCornerAlpha(self->sprites[3], 255);
    SpriteHandle_SetActiveFlag(self->sprites[3], 1);
    RefillChoice *choice = (RefillChoice *)self->iconArray;
    SpriteGroup_CreateOrInit(&choice->groups[1], &ItemSelectState_data_806D0728, 1, lbl_806DB888, lbl_806DB888);
    SpriteGroup_CreateOrInit(&choice->groups[2], &ItemSelectState_data_806D072C, 1, lbl_806DB888, lbl_806DB888);
    SpriteGroup_CreateOrInit(&choice->groups[3], &ItemSelectState_data_806D0730, 1, lbl_806DB888, lbl_806DB888);
    SpriteGroup_CreateOrInit(&choice->groups[0], &ItemSelectState_data_806D0734, 0, lbl_806DB8F0, lbl_806DB8F4);
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
    SpriteGroup_CreateOrInit(&self->groups[1], &ItemSelectState_data_806D0764, 0, lbl_806DB888, lbl_806DB8FC);
    SpriteGroup_CreateOrInit(&self->groups[2], &ItemSelectState_data_806D0768, 0, lbl_806DB900, lbl_806DB904);
    SpriteGroup_CreateOrInit(&self->groups[6], &ItemSelectState_data_806D076C, 0, lbl_806DB908, lbl_806DB90C);
    SpriteGroup_CreateOrInit(&self->groups[3], &ItemSelectState_data_806D0770, 0, lbl_806DB8F0, lbl_806DB8F4);
    SpriteGroup_CreateOrInit(&self->groups[4], &ItemSelectState_data_806D0774, 0, lbl_806DB8F0, lbl_806DB8F4);
    SpriteGroup_CreateOrInit(&self->groups[5], &ItemSelectState_data_806D0778, 0, lbl_806DB8F0, lbl_806DB8F4);
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
static inline int GridItem(const int (*items)[10], int column, int row) {
    int character = g_characterId;
    if (character < 0) character = 0;
    if (character >= 13) character = 0;
    if (column >= 10) return fn_8023D844(character, row);
    return items[row][column];
}
static inline void SelectChoice(RefillChoice *choice, int slot, const int *resources) {
    unsigned char *playerData = g_playerData;
    choice->selected = 1;
    choice->timer = 0;
    SpriteAnimParamBlock_Reload(choice->groups[1], slot + 0x4e);
    int resource = (short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(playerData,
        GridItem(ItemSelectState_rodata_803DC180, choice->column, choice->row)), 0);
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
static inline void ApplyFade(ItemSelectState *self, float fade) {
    int alpha = 255.0f * fade;
    SpriteHandle_SetCornerAlpha(self->sprites[1], alpha);
    SpriteHandle_SetCornerAlpha(self->sprites[2], alpha);
    SpriteHandle_SetActiveFlag(self->sprites[1], 1);
    SpriteHandle_SetActiveFlag(self->sprites[2], 1);
    unsigned int color = -256;
    color = (color & ~0xffU) | (alpha & 0xff);
    *(unsigned int *)(self->auxBuffer->data + 0x20) = color;
}
extern "C" void fn_80238D9C(ItemSelectState *self) {
    int row;
    int i;
    int k;
    int m;
    int q;
    if (self->doneFlag == 1) return;
    ItemSelectInput *input = SINGLETON_INSTANCE(g_pInputState);
    void *playerData = g_playerData;
    switch (self->phase) {
    case 0: break;
    case 2: break;
    case 1: {
        if (self->resultCode >= 8 && self->resultCode <= 15) {
            float fade = (self->resultCode - 8) / 7.0f;
            if (fade < 0.0f) fade = 0.0f;
            ApplyFade(self, fade);
        }
        if (self->resultCode < 25) {
            const float *ys = choiceY;
            for (row = 0; row < 6; ++row) {
                float y = ys[row];
                const float *xs = choiceX;
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
                i = ChoiceColumn(choice);
                row = choice->row;
                struct SlotsView { char padding[0x15c]; int slots[3][3]; };
                SlotsView *view = (SlotsView *)self;
                view->slots[self->field14c][0] = i;
                view->slots[self->field14c][1] = row;
                view->slots[self->field14c][2] = GridItem(ItemSelectState_rodata_803DC180, i, row);
                SelectChoice((RefillChoice *)self->iconArray, self->field14c, choiceResources);
                int item = Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(playerData,
                    view->slots[self->field14c][2]), 0);
                SpriteAnimParamBlock_SetAnimParamCached(self->groups[self->field14c + 3], 0x13b9, item);
                RefillSprite *sprite = GroupSprite(self->groups[self->field14c + 3]);
                sprite->x = choiceX[i];
                sprite->y = choiceY[row];
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
    fn_8011F804(self->sprites[3], lbl_806DB8DC, choiceY[((RefillChoice *)self->iconArray)->row]);
    /* the sprite-advance loops were written out here: separate counters
       declared last (k, m, q) give the target's saved-register order */
    for (k = 0; k < 9; ++k) {
        if (self->groups[k]) Sprite_AdvanceAnim(GroupSprite(self->groups[k]), lbl_806DB8A8);
    }
    for (m = 0; m < 66; ++m)
        SpriteHandle_RecomputeCull(self->itemSprites[m]);
    for (q = 0; q < 5; ++q)
        SpriteHandle_RecomputeCull(self->sprites[q]);
}
/* fakematch (permuter-style, manual): the target reloads selectedItemId0 for the
   first Resolve call, which a read through a pointer to the {row,col,id} slots gives.
   Natural code was probably:
     g_playerData.selected[0]=selectedItemId0; ... selected[2]=selectedItemId2; */
static inline void setSel(PlayerData *p,const int *a){p->selected[0]=a[0];p->selected[1]=a[3];p->selected[2]=a[6];}
static inline int characterId() {
 int id=g_characterId; if(id<0) id=0; if(id>=13) id=0; return id;
}
ItemSelectState::~ItemSelectState() {
    PlayerData *player=(PlayerData *)g_playerData;
    setSel((PlayerData *)g_playerData,&selectedItemId0);
    lbl_806D1264[0]=PlayerData_ResolveUnlockedIdByIndex(g_playerData,selectedItemId0);
    lbl_806D1264[1]=PlayerData_ResolveUnlockedIdByIndex(g_playerData,selectedItemId1);
    lbl_806D1264[2]=PlayerData_ResolveUnlockedIdByIndex(g_playerData,selectedItemId2);
    if(iconArray) {delete iconArray;iconArray=0;}
    if(auxBuffer) {delete auxBuffer;auxBuffer=0;}
    for(int i=0;i<9;i++) if(groups[i]) {SpriteAnimHandle_Destroy(groups[i],1);groups[i]=0;}
    for(int i=0;i<66;i++) {
        SpriteHandle_Destroy(itemSprites[i]);
        int character=characterId();
        int index;
        if(i%11>=10) index=fn_8023D844(character,i/11);
        else index=ItemSelectState_rodata_803DC180[i/11][i%11];
        fn_80120A08(Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(player,index),0));
    }
    for(int i=0;i<5;i++) SpriteHandle_Destroy(sprites[i]);
    fn_80120A08(0x17bb);fn_80120A08(0x1d23);fn_80120A08(0x17ed);fn_80120A08(0x1e3d);
}
static inline int portraitIndex() {
 if(g_characterId==0)return 0;
 else if(g_characterId==1)return 1;
 else if(g_characterId==8)return 2;
 else if(g_characterId==11)return 3;
 else if(g_characterId==3)return 4;
 else if(g_characterId==7)return 5;
 else if(g_characterId==10)return 6;
 else if(g_characterId==12)return 7;
 else if(g_characterId==9)return 8;
 else if(g_characterId==5)return 9;
 else if(g_characterId==2)return 10;
 else if(g_characterId==6)return 11;
 else if(g_characterId==4)return 12;
 else return 0;
}
static inline unsigned int MakeCell(unsigned int resource,const float *y) {
 ResCtrl cell;
 cell.resId=resource;cell.flag=1;cell.x=lbl_806DB8F0;cell.y=*y;cell.z=lbl_806DB8CC;
 cell.colors[0]=0xc3cdf0ff;cell.colors[1]=0xc3cdf0ff;cell.colors[2]=0xc3cdf0ff;cell.colors[3]=0xc3cdf0ff;
 cell.scaleX=lbl_806DB910;cell.scaleY=lbl_806DB910;
 return SpriteHandle_CreateDefault(&cell,6);
}
ItemSelectState::ItemSelectState() {

 iconArray=0;auxBuffer=0;field148=0;field14c=0;resultCode=0;phase=0;doneFlag=0;shownFlag=0;
 for(int i=0;i<9;i++)groups[i]=0;
 for(int i=0;i<66;i++)itemSprites[i]=-1;
 for(int i=0;i<5;i++)sprites[i]=-1;
 selectedItemId0=-1;selectedItemId1=-1;selectedItemId2=-1;
 PreloadResource(0x17bb);PreloadResource(0x1d23);PreloadResource(0x17ed);PreloadResource(0x1e3d);
 ResCtrl res;
 res.resId=0x17bb;res.flag=1;res.x=lbl_806DB88C;res.y=lbl_806DB890;res.z=lbl_806DB8CC;
 sprites[0]=SpriteHandle_CreateDefault(&res,5);
 fn_80121E10(&res);
 res.resId=portraitIndex()+0x1d23;res.flag=1;res.x=lbl_806DB900;res.y=lbl_806DB924;res.z=lbl_806DB8CC;
 sprites[1]=SpriteHandle_CreateDefault(&res,6);
 for(int i=0;i<5;i++){SpriteHandle_SetActiveFlag(sprites[i],0);SpriteHandle_RecomputeCull(sprites[i]);}
 auxBuffer=new TextManager;
 if(!isJapanese())TexMgr_SetTexture(auxBuffer,selectMessage);
 else {*(float *)(auxBuffer->data+0x22c)=lbl_806DB928;TexMgr_SetTexture(auxBuffer,selectMessageEn);}
 *(int *)(auxBuffer->data+0x18)=1;
 fn_801F93EC(auxBuffer,lbl_806DB92C,lbl_806DB930);fn_801F8E90(auxBuffer);
 *(unsigned int *)(auxBuffer->data+0x20)=0xffffff00;
 unsigned int *table; float *ys; unsigned char *player; int row; int col;
 table=(unsigned int *)ItemSelectState_rodata_803DC180;
 ys=(float *)choiceY;
 player=g_playerData;
 for(row=0;row<6;row++,table+=10,ys++) {
 for(col=0;col<11;col++){
   int idx=row*11+col;
   long character=g_characterId;
   unsigned int resource=0x1422;
   if(character<0)character=0;if(character>=13)character=0;
   int index;
   if(col>=10)index=fn_8023D844(character,row);else index=table[col];
   if(player[index+0xa8]==1)resource=Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(player,index),0);
   itemSprites[idx]=MakeCell(resource,ys);
 }
 }
 fn_80121E10(&res);
 res.tail[1]=1;res.tail[2]=1;res.tail[3]=1;
 res.resId=0x1e3d;res.flag=1;res.x=lbl_806DB8DC;res.y=lbl_806DB934;res.z=1.0f;
 res.scaleX=lbl_806DB938;res.scaleY=1.0f;
 sprites[3]=SpriteHandle_CreateDefault(&res,6);
 fn_80121E10(&res);
 res.resId=0x17ed;res.flag=1;res.x=lbl_806DB900;res.y=lbl_806DB93C;res.z=lbl_806DB8CC;
 sprites[2]=SpriteHandle_CreateDefault(&res,6);
 {ResCtrl last;
 last.mode=2;last.width=lbl_806DB8D4;last.height=lbl_806DB8D8;last.flag=1;
 last.x=lbl_806DB8DC;last.y=lbl_806DB8E0;last.z=lbl_806DB8CC;
 last.colors[0]=0;last.colors[1]=0;last.colors[2]=0;last.colors[3]=0;
 sprites[4]=SpriteHandle_CreateDefault(&last,6);
 SpriteHandle_SetActiveFlag(sprites[4],0);SpriteHandle_RecomputeCull(sprites[4]);
 iconArray=new IconPack;}
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
extern "C" void fn_80239D6C(ItemSelectPresentation *self) {
    SpriteGroup_CreateOrInit(&self->groups[0], ItemSelectState_data_806D073C, 0, lbl_806DB8DC, lbl_806DB940);
    SpriteGroup_CreateOrInit(&self->groups[1], ItemSelectState_data_806D0740, 0, lbl_806DB944, lbl_806DB948);
    SpriteGroup_CreateOrInit(&self->groups[2], ItemSelectState_data_806D0744, 0, lbl_806DB94C, lbl_806DB948);
    SpriteGroup_CreateOrInit(&self->groups[3], ItemSelectState_data_806D0748, 0, lbl_806DB950, lbl_806DB954);
    SpriteGroup_CreateOrInit(&self->groups[4], ItemSelectState_data_806D074C, 0, lbl_806DB8DC, lbl_806DB954);
    SpriteGroup_CreateOrInit(&self->groups[5], ItemSelectState_data_806D0750, 0, lbl_806DB958, lbl_806DB954);
    SpriteGroup_CreateOrInit(&self->groups[6], ItemSelectState_data_806D0754, 1, lbl_806DB95C, lbl_806DB960);
    self->groups[0]->sprite->layer = 6;
    self->groups[1]->sprite->layer = 6;
    self->groups[2]->sprite->layer = 6;
    self->groups[3]->sprite->layer = 6;
    self->groups[4]->sprite->layer = 6;
    self->groups[5]->sprite->layer = 6;
    self->groups[6]->sprite->layer = 6;
    PresentationScale(self->groups[2]->sprite, lbl_806DB964);
    PresentationScale(self->groups[6]->sprite, lbl_806DB910);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[3], 0x13b9, self->resources[0]);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[4], 0x13b9, self->resources[1]);
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[5], 0x13b9, self->resources[2]);
    SpriteAnimSample pos;
    unsigned char *player = g_playerData;
    for (int i = 0; i < 3; i++) {
        int group = i + 3;
        self->groups[group]->sprite->alpha = lbl_806DB888;
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x13b9, self->resources[i]);
        int item = PlayerData_ResolveUnlockedIdByIndex(player, self->itemIndices[i]);
        int field = Item_GetDescriptorFieldC(item);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x1e1d, field < 0 ? -1 : field + 0x1e1d);
        field = Item_GetDescriptorField8(item);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x17a4, field < 0 ? -1 : field + 0x17a3);
        fn_8019FF8C(self->groups[group]->sprite, 0x1ecd, &pos);
        fn_801F93EC(self->texts[i][0], pos.x, pos.y);
        fn_8019FF8C(self->groups[group]->sprite, 0x1ecf, &pos);
        fn_801F93EC(self->texts[i][1], pos.x, pos.y);
        fn_8019FF8C(self->groups[group]->sprite, 0x1ed1, &pos);
        fn_801F93EC(self->texts[i][2], pos.x, pos.y);
        fn_8019FF8C(self->groups[group]->sprite, 0x1ed3, &pos);
        fn_801F93EC(self->texts[i][3], pos.x, pos.y);
        TexMgr_SetTexture(self->texts[i][0], fn_8023DAA8(item));
        TexMgr_SetTexture(self->texts[i][1], Item_GetLocalizedAsset(item, 0));
        TexMgr_SetTexture(self->texts[i][2], Item_GetLocalizedAsset(item, 1));
        TexMgr_SetTexture(self->texts[i][3], Item_GetLocalizedAsset(item, 2));
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x1ecf, 0x1ecd);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x1ed1, 0x1ecd);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[group], 0x1ed3, 0x1ecd);
        *(unsigned int *)(self->texts[i][0]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->texts[i][1]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->texts[i][2]->data + 0x20) = 0xffffff00;
        *(unsigned int *)(self->texts[i][3]->data + 0x20) = 0xffffff00;
    }
    PresentationParams(self);
    self->timer = 0;
    self->phase = 1;
}
static inline void SetTextAlpha(ItemSelectPresentation *self, int alpha) {
    unsigned char a = alpha;
    unsigned int color = 0xffffff00 | a;
    unsigned int title = 0xe0202000 | a;
    for (int i = 0; i < 3; i++) {
        *(unsigned int *)(self->texts[i][0]->data + 0x20) = title;
        *(unsigned int *)(self->texts[i][1]->data + 0x20) = color;
        *(unsigned int *)(self->texts[i][2]->data + 0x20) = color;
        *(unsigned int *)(self->texts[i][3]->data + 0x20) = color;
    }
}
extern "C" void fn_8023A148(ItemSelectPresentation *self) {
    ItemSelectInput *input = SINGLETON_INSTANCE(g_pInputState);
    switch (self->phase) {
    case 0: break;
    case 1:
        if (self->timer == 6) {
            fn_8023F1C8(self->groups[0]);
            SpriteHandle_SetActiveFlag(self->handle, 1);
        }
        if (self->timer < 6) {
            float alpha = (float)((self->timer - 2) / 3);
            if (alpha < 0.0f) alpha = 0.0f;
            self->groups[1]->sprite->alpha = alpha;
            self->groups[2]->sprite->alpha = alpha;
        }
        if (self->timer >= 15) {
            self->groups[6]->sprite->alpha = 1.0f;
            self->phase = 2;
        }
        break;
    case 2: {
        float alpha = self->groups[3]->sprite->alpha;
        int textAlpha = (int)(255.0f * alpha);
        int direction = SINGLETON_INSTANCE(g_pInputState)->dir;
        if (self->automatic) {
            alpha = 0.0f;
            direction = 1;
            textAlpha = 0;
        }
        if (direction) {
            int previous = self->selected;
            self->selected += direction;
            if (self->selected < 0) self->selected = 0;
            if (self->selected > 1) self->selected = 1;
            if (previous != self->selected) fn_801FE390();
            int other = (~self->selected) & 1;
            SpriteAnimParamBlock_Reload(self->groups[self->selected + 1], 0x1a8);
            SpriteAnimParamBlock_Reload(self->groups[other + 1], 0x1a7);
            PresentationScale(self->groups[self->selected + 1]->sprite, 1.0f);
            PresentationScale(self->groups[other + 1]->sprite, lbl_806DB964);
            PresentationParams(self);
            if (self->selected == 0) self->groups[6]->sprite->field1c = 0.0f;
            else self->groups[6]->sprite->field1c = lbl_806DB968 * ItemSelectState_data_806D0738;
        }
        if (self->selected == 0) {
            alpha -= 0.1f;
            if (alpha < 0.0f) alpha = 0.0f;
        } else {
            alpha += 0.1f;
            if (alpha > 1.0f) alpha = 1.0f;
        }
        if (!self->automatic) {
            self->groups[3]->sprite->alpha = alpha;
            self->groups[4]->sprite->alpha = alpha;
            self->groups[5]->sprite->alpha = alpha;
            SetTextAlpha(self, textAlpha);
        }
        if (input->held == 1 || self->automatic == 1) {
            fn_801FE348();
            SpriteAnimParamBlock_Reload(self->groups[self->selected + 1], 0x59);
            if (self->selected == 1) PresentationParams(self);
            self->timer = 0;
            self->phase = 3;
        }
        break;
    }
    case 3:
        if (self->timer >= 7 && self->timer <= 15 && self->selected == 1) {
            int alpha = (int)(255.0f * (1.0f - (self->timer - 7) * lbl_806DB918));
            unsigned char current = *(unsigned int *)(self->texts[0][0]->data + 0x20);
            if ((unsigned char)alpha > current) alpha = current;
            SetTextAlpha(self, alpha);
        }
        if (self->timer == 15) {
            SpriteAnimParamBlock_Reload(self->groups[0], 0x48);
            PresentationParams(self);
            SpriteHandle_SetActiveFlag(self->handle, 0);
        }
        if (self->timer == 22) {
            self->groups[0]->sprite->alpha = 0.0f;
            self->groups[1]->sprite->alpha = 0.0f;
            self->groups[2]->sprite->alpha = 0.0f;
            self->groups[3]->sprite->alpha = 0.0f;
            self->groups[4]->sprite->alpha = 0.0f;
            self->groups[5]->sprite->alpha = 0.0f;
            self->groups[6]->sprite->alpha = 0.0f;
            SpriteHandle_SetActiveFlag(self->handle, 0);
            self->done = 1;
            self->phase = -1;
        }
        break;
    }
    self->timer++;
    for (int i = 0; i < 7; i++) {
        if (self->groups[i]) Sprite_AdvanceAnim(self->groups[i]->sprite, lbl_806DB8A8);
    }
    SpriteHandle_RecomputeCull(self->handle);
}
#include "game/types/GridInitState.h"
#pragma use_lmw_stmw on
static inline void InitializeGridItem(GridInitState *self, unsigned char *player, int *ids, int i) {
    int id;
    unsigned char found;
    if(fn_8023D860(*(int *)(player+0x18c+i*4))==1) {
        int character=g_characterId;
        id=fn_8023D844(character,fn_8023D7A8(*(int *)(player+0x18c+i*4)));
        if(player[id+0xa8]==0) {
            int j;
            const int *p=ItemGridState_Init_rodata_803DC174;
            for(j=0;j<3;++p,++j) {
                int candidate;
                candidate=*p;
                found=0;
                for (int k=0;k<3;++k) {
                    if (candidate==ids[k]) { found=1; break; }
                }
                if (!found) {id=ItemGridState_Init_rodata_803DC174[j];break;}
            }
        }
    } else id=*(int *)(player+0x18c+i*4);
    ids[i]=id;
    self->itemIndices[i]=id;
    self->resources[i]=Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(player,id),0);
}
extern "C" GridInitState *ItemGridState_Init(GridInitState *self) {
    int row;
    int col;
    self->selected=0;
    self->phase=0;
    self->done=0;
    self->automatic=0;
    self->groups[0]=0; self->groups[1]=0; self->groups[2]=0;
    self->groups[3]=0; self->groups[4]=0; self->groups[5]=0; self->groups[6]=0;
    PreloadResource(0x192a); PreloadResource(0x192c);
    ResCtrl resource;
    resource.resId=0x192a;
    resource.flag=1;
    resource.x=lbl_806DB8DC; resource.y=lbl_806DB940; resource.z=lbl_806DB8CC;
    self->handle=SpriteHandle_CreateDefault(&resource,6);
    SpriteHandle_SetActiveFlag(self->handle,0);
    SpriteHandle_RecomputeCull(self->handle);

    for (row=0;row<3;++row) {
        for (col=0;col<4;++col) {
            self->texts[row][col]=new TextManager;
            TexMgr_SetTexture(self->texts[row][col],lbl_806DB8F8);
            *(float *)(self->texts[row][col]->data+0x22c)=lbl_806DB8A0;
        }
    }

    int ids[3];
    int i;
    unsigned char *player=g_playerData;
    ids[0]=*(int *)(player+0x18c); ids[1]=*(int *)(player+0x190); ids[2]=*(int *)(player+0x194);
    for(i=0;i<3;++i) {
        InitializeGridItem(self,player,ids,i);
    }
    return self;
}
#pragma use_lmw_stmw reset
static inline int ChoiceItem(RefillChoice *self) {
    int character = g_characterId;
    int row = self->row;
    int column = self->column;
    if (character < 0) character = 0;
    if (character >= 13) character = 0;
    if (column >= 10) return fn_8023D844(character, row);
    return ItemSelectState_rodata_803DC180[row][column];
}
static inline unsigned char ChoiceOccupied(RefillChoice *self) {
    unsigned char occupied = 0;
    for (int i = 0; i < 2; i++) {
        if (self->slots[i][0] == self->column && self->slots[i][1] == self->row) {
            occupied = 1;
            break;
        }
    }
    return occupied;
}
#pragma auto_inline off
extern "C" void fn_8023AA0C(RefillChoice *self, int step) {
    if (step) {
        unsigned char *player = g_playerData;
        unsigned char occupied;
        do {
            self->column += step;
            if (self->column < 0) { self->column = 10; --self->row; }
            if (self->column > 10) { self->column = 0; ++self->row; }
            if (self->row < 0) self->row = 5;
            if (self->row > 5) self->row = 0;
            occupied = ChoiceOccupied(self);
        } while (occupied == 1);
        self->done = player[ChoiceItem(self) + 0xa8];
        int resource = (short)Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(player,
            ChoiceItem(self)), 0);
        if (!self->done) resource = 0x1422;
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[1], self->resource, resource);
        fn_8019FF6C(self->groups[1]->sprite, 1);
        self->resource = resource;
    }
}
#pragma auto_inline reset

struct ChoicePoint { float x, y; char rest[0x28]; };
static inline unsigned char *ChoicePlayerData() {
    unsigned char *player = g_playerData;
    return player;
}
static inline int ChoiceAdvanceRow(RefillChoice *self) {
    int resource;
    do {
        ++self->row;
        if (self->row >= 6) self->row = 0;
    } while (ChoiceOccupied(self) == 1);
    unsigned char *player = ChoicePlayerData();
    self->done = player[ChoiceItem(self) + 0xa8];
    resource = (short)Item_GetDescriptorField0(
        PlayerData_ResolveUnlockedIdByIndex(player, ChoiceItem(self)), 0);
    if (!self->done) resource = 0x1422;
    SpriteAnimParamBlock_SetAnimParamCached(self->groups[1], self->resource, resource);
    fn_8019FF6C(self->groups[1]->sprite, 1);
    self->resource = resource;
    return 1;
}
// ChoiceItem with the cursor read into locals by the caller (fn_8023AC14 phase 40).
static inline int ChoiceItemRC(int row, int column) {
    int character = g_characterId;
    if (character < 0) character = 0;
    if (character >= 13) character = 0;
    if (column >= 10) return fn_8023D844(character, row);
    return ItemSelectState_rodata_803DC180[row][column];
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
        ItemSelectInput *input = SINGLETON_INSTANCE(g_pInputState);
        horizontal = input->dir;
        if (input->held == 3) {
            vertical = ChoiceAdvanceRow(self);
        }
        if (horizontal + vertical) fn_801FE36C();
    }
    fn_8023AA0C(self, horizontal);
    if (self->done == 1) {
        if (++self->phase >= 40) {
            if (self->phase == 40) {
                unsigned char *player = ChoicePlayerData();
                ChoicePoint pos;
                // `group` (named, low vreg) and the named row/column locals are pushed
                // before `player` in the first simplify sweep, so `player` is coloured
                // after ChoiceAdvanceRow's `resource` and resource keeps r28.
                RefillGroup *group;
                fn_8019FF8C(self->groups[0]->sprite, 0x1ecd, &pos);
                fn_801F93EC(self->text[0], pos.x, pos.y);
                group = self->groups[0];
                fn_8019FF8C(group->sprite, 0x1ecf, &pos);
                fn_801F93EC(self->text[1], pos.x, pos.y);
                group = self->groups[0];
                fn_8019FF8C(group->sprite, 0x1ed1, &pos);
                fn_801F93EC(self->text[2], pos.x, pos.y);
                group = self->groups[0];
                fn_8019FF8C(group->sprite, 0x1ed3, &pos);
                fn_801F93EC(self->text[3], pos.x, pos.y);
                int row = self->row;
                int column = self->column;
                int descriptor = PlayerData_ResolveUnlockedIdByIndex(player, ChoiceItemRC(row, column));
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
            unsigned int color = 0xffffff00 | (alpha & 0xff);
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
