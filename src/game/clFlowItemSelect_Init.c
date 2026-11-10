/* clFlowItemSelect_Init @ 0x801CC2EC: FlowItemSelect constructor (item
 * select scene). Real C++ ctor; extab comes from the base/member/new
 * cleanups. Mangled names are bridged in tools/extab_user_renames.json. */
#pragma cplusplus on
#pragma exceptions on
void* operator new(unsigned long);
void operator delete(void*) throw();
struct ResCtrl {
    int resource, field4, field8, fieldC;
    unsigned char enabled, pad11[3];
    float x, y, z;
    unsigned char tail[0x38];
    ResCtrl();
    ~ResCtrl() {}
};
struct FrameSelection {
    FrameSelection();
    virtual ~FrameSelection();
};
struct FlowChild {
    unsigned char storage[0x20];
    FlowChild(int, int, int, int, int);
};
struct FlowChildOwner {
    FlowChild* payload;
    FlowChildOwner() : payload(new FlowChild(0x74, -1, 0x1875, -1, 5)) {}
    ~FlowChildOwner() throw();
};
struct TexMgr {
    unsigned char pad0[0x20];
    int item;
    unsigned char pad24[0x208];
    float fade;
    TexMgr();
};
struct WeightedEntry { int id, weight; };
extern "C" {
extern WeightedEntry* clFlowItemSelect_Init_data_8049B130[3];
extern const int clFlowItemSelect_Init_rodata_8039B3C8[3];
extern const float lbl_806D9DF8, lbl_806D9E04, lbl_806D9DD8, lbl_806D9DE4;
extern const float lbl_806D9E08, lbl_806D9E0C, lbl_806D9DC0;
extern const float lbl_806D9E10, lbl_806D9E14, lbl_806D9E18, lbl_806D9E1C;
extern const char lbl_806D9DFC[5];
extern const int clFlowItemSelect_Init_data_806CFE08, clFlowItemSelect_Init_data_806CFE0C, clFlowItemSelect_Init_data_806CFE10, clFlowItemSelect_Init_data_806CFE14;
extern int g_characterId;
extern unsigned int g_playerData[0x1DC / 4];
#include "game/types/InputView.h"
extern InputView* g_pInputState[2];
void SetSyncTarget(int);
int InitBGM();
int SetupBgSprites(unsigned char);
void* ItemDisplay_GetOrCreate();
void ItemDisplay_Start(void*, int);
unsigned char PreloadResource(int);
void TexMgr_SetTexture(TexMgr*, const char*, ...);
void TexMgr_Apply(TexMgr*);
void fn_801F8E90(TexMgr*);
void SpriteGroup_CreateOrInit(void**, const int*, int, float, float);
void SpriteAnimParamBlock_SetAnimParamCached(void*, int, int);
void fn_80121E10(ResCtrl*);
int SpriteHandle_CreateDefault(ResCtrl*, int);
int fn_8023D844(int, int);
int PlayerData_ResolveUnlockedIdByIndex(void*, int);
void fn_8023CD3C(FlowChild*, float, float);
void fn_8023CCF8(FlowChild*, float, float);
unsigned int OSGetTick();
void Rand_SetSeedDebug(unsigned int);
int Rand15();
const char* fn_8023DAA8(int);
const char* Item_GetLocalizedAsset(int, int);
int Item_GetDescriptorField0(int, unsigned char*);
int Item_GetDescriptorFieldC(int);
int Item_GetDescriptorField8(int);
int InitRumbleController(unsigned char);
}
static inline InputView* input_state()
{
    if (g_pInputState[0] == 0) return 0;
    return g_pInputState[0];
}
static inline int resolve_item(int id, const int* unlocked)
{
    switch (id) {
    case -2: return unlocked[1];
    case -3: return unlocked[2];
    case -4: return unlocked[0];
    case -5: return unlocked[3];
    case -6: return unlocked[4];
    }
    return id;
}
struct RandomState {
    unsigned char active, pad1[3];
    int selected, last, counter;
    WeightedEntry* table;
    int count;
    int unlocked[5];
    RandomState(WeightedEntry* entries, int num, const int* source)
    {
        active = 0;
        counter = 0;
        table = entries;
        count = num;
        for (int i = 0; i < 5; ++i) unlocked[i] = source[i];
        choose();
    }
    void choose()
    {
        if (active != 1) {
            int id;
            do {
                id = resolve_item(table[Rand15() % count].id, unlocked);
            } while (id == last);
            last = id;
            counter = 6;
        }
    }
};
struct FlowItemSelect : FrameSelection {
    int selected[3], field10, field14, field18, field1C;
    float field20;
    ResCtrl resource;
    int field7C;
    void* groups[5];
    int sprite;
    TexMgr* textures[3][4];
    int unlocked[5];
    RandomState* random[3];
    FlowChildOwner child;
    virtual void identity();
    FlowItemSelect();
};
static inline int ClampCharacter(int c) {
    if (c < 0 || c >= 13) c = 0;
    return c;
}
static inline int ValidCharacter() {
    int c = g_characterId;
    if (c < 0 || c >= 13) c = 0;
    return c;
}
static inline void ResolveUnlocked(int *out, int character) {
    for (int i = 0; i < 5; ++i)
        out[i] = PlayerData_ResolveUnlockedIdByIndex(g_playerData, fn_8023D844(character, i + 1));
}
static inline void ResolveUnlocked2(int *out, int character, void *pd) {
    for (int i = 0; i < 5; ++i)
        out[i] = PlayerData_ResolveUnlockedIdByIndex(pd, fn_8023D844(character, i + 1));
}
FlowItemSelect::FlowItemSelect() : field20(lbl_806D9DF8)
{
    int i, j, character;
    SetSyncTarget(0x22);
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 4; ++j) textures[i][j] = 0;
    for (i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            textures[i][j] = new TexMgr;
            TexMgr_SetTexture(textures[i][j], lbl_806D9DFC);
        }
        textures[i][1]->fade = lbl_806D9DF8;
        textures[i][2]->fade = lbl_806D9DF8;
        textures[i][3]->fade = lbl_806D9DF8;
    }
    if (input_state()) {
        InputView* input = input_state();
        input->enabled = 1;
        input->held = 0;
        input->edge = 0;
    }
    InitBGM();
    SetupBgSprites(1);
    ItemDisplay_GetOrCreate();
    ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AE7);
    PreloadResource(0x17AB);
    field18 = 0;
    field1C = 0;
    field7C = -1;
    field10 = 0;
    field14 = 0;
    selected[0] = 0x2B;
    selected[1] = 0x3D;
    selected[2] = 0x32;
    for (int i = 0; i < 5; ++i) groups[i] = 0;
    SpriteGroup_CreateOrInit(&groups[0], &clFlowItemSelect_Init_data_806CFE08, 0, lbl_806D9E04, lbl_806D9DD8);
    SpriteGroup_CreateOrInit(&groups[1], &clFlowItemSelect_Init_data_806CFE0C, 0, lbl_806D9DE4, lbl_806D9DD8);
    SpriteGroup_CreateOrInit(&groups[2], &clFlowItemSelect_Init_data_806CFE10, 0, lbl_806D9E08, lbl_806D9DD8);
    SpriteGroup_CreateOrInit(&groups[3], &clFlowItemSelect_Init_data_806CFE14, 0, lbl_806D9DE4, lbl_806D9E0C);
    for (i = 0; i < 3; ++i) {
        SpriteAnimParamBlock_SetAnimParamCached(groups[i], 0x1ECF, 0x1ECD);
        SpriteAnimParamBlock_SetAnimParamCached(groups[i], 0x1ED1, 0x1ECD);
        SpriteAnimParamBlock_SetAnimParamCached(groups[i], 0x1ED3, 0x1ECD);
        for (int j = 0; j < 4; ++j) {
            textures[i][j]->item = -0x100;
            fn_801F8E90(textures[i][j]);
        }
    }
    ResCtrl local;
    fn_80121E10(&local);
    local.resource = 0x17AB;
    local.enabled = 1;
    local.x = lbl_806D9DE4;
    local.y = lbl_806D9E0C;
    local.z = lbl_806D9DC0;
    sprite = SpriteHandle_CreateDefault(&local, 5);
    if ((character = g_characterId) < 0 || character >= 13) character = 0;
    {
        void *pd = g_playerData;
        for (i = 0; i < 5; ++i)
            unlocked[i] = PlayerData_ResolveUnlockedIdByIndex(pd, fn_8023D844(character, i + 1));
    }
    fn_8023CD3C(child.payload, lbl_806D9E10, lbl_806D9E14);
    fn_8023CCF8(child.payload, lbl_806D9E18, lbl_806D9E1C);
    fn_80121E10(&resource);
    resource.resource = 0x17A3;
    Rand_SetSeedDebug((unsigned char)OSGetTick());
    for (i = 0; i < 3; ++i) {
        random[i] = new RandomState(clFlowItemSelect_Init_data_8049B130[i], clFlowItemSelect_Init_rodata_8039B3C8[i], unlocked);
        int sum = 0;
        int roll = Rand15() % 100 + 1;
        for (int j = 0; j < clFlowItemSelect_Init_rodata_8039B3C8[i]; ++j) {
            sum += clFlowItemSelect_Init_data_8049B130[i][j].weight;
            if (roll <= sum) {
                selected[i] = clFlowItemSelect_Init_data_8049B130[i][j].id;
                switch (selected[i]) {
                case -2: selected[i] = unlocked[1]; break;
                case -3: selected[i] = unlocked[2]; break;
                case -4: selected[i] = unlocked[0]; break;
                case -5: selected[i] = unlocked[3]; break;
                case -6: selected[i] = unlocked[4]; break;
                }
                if (selected[i] >= 0 && selected[i] < 0x115) {
                    random[i]->selected = selected[i];
                    break;
                }
            }
        }
    }
    for (i = 0; i < 3; ++i) {
        TexMgr_SetTexture(textures[i][0], fn_8023DAA8(selected[i]));
        TexMgr_SetTexture(textures[i][1], Item_GetLocalizedAsset(selected[i], 0));
        TexMgr_SetTexture(textures[i][2], Item_GetLocalizedAsset(selected[i], 1));
        TexMgr_SetTexture(textures[i][3], Item_GetLocalizedAsset(selected[i], 2));
        for (int j = 0; j < 4; ++j) TexMgr_Apply(textures[i][j]);
    }
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < clFlowItemSelect_Init_rodata_8039B3C8[i]; ++j) {
            int id = clFlowItemSelect_Init_data_8049B130[i][j].id;
            PreloadResource(Item_GetDescriptorField0(id, 0));
            PreloadResource(Item_GetDescriptorFieldC(id) + 0x1E1D);
            PreloadResource(Item_GetDescriptorField8(id) + 0x17A3);
        }
    }
    PreloadResource(0x17AB);
    InitRumbleController(1);
}
#pragma cplusplus off
