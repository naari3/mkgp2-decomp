#include "game/types/arg_order.h"
/* clFlowKart owns its methods, lookup tables and compiler-generated RTTI.
 * Deferred generation requires definitions in reverse target-address order.
 * Mangled symbols retain the existing link names through extab_user_renames.
 */
#include "game/types/size_t.h"
#pragma readonly_strings on
#include "game/singleton.h"

void* operator new(size_t);
void operator delete(void*);
struct FKScene;
struct FKDriver;
struct FKTex;
struct FKVec { float x, y, z; };
/* .rodata 0x8039E508..0x8039E9F8 */
extern "C" {
extern const unsigned int clFlowKart_Init_rodata_8039E508[0xFF];
/* tables used by other clFlowKart functions */
const unsigned int clFlowKart_Init_rodata_8039E508[0xFF] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};
/* coin mileage for the first enhancement level per character */
extern const int lbl_8039E904[13];
const int lbl_8039E904[13] = {
    0x0000001E, 0x000005BE, 0x000004CE,
    0x00000096, 0x000002EE, 0x00000546, 0x0000010E, 0x00000276, 0x000003DE,
    0x00000186, 0x00000456, 0x000001FE, 0x00000366,
};
/* coin mileage needed per character */
extern const int g_kartEnhancedUnlockThreshold[13];
const int g_kartEnhancedUnlockThreshold[13] = {
    0x00000636, 0x00000BD6, 0x00000AE6, 0x000006AE, 0x00000906, 0x00000B5E,
    0x00000726, 0x0000088E, 0x000009F6, 0x0000079E, 0x00000A6E, 0x00000816,
    0x0000097E,
};
/* texture index per character */
extern const int lbl_8039E96C[13];
const int lbl_8039E96C[13] = {
    0x00000002, 0x00000002, 0x00000003, 0x00000001, 0x00000003, 0x00000000,
    0x00000003, 0x00000001, 0x00000002, 0x00000000, 0x00000001, 0x00000002,
    0x00000000,
};
extern const int lbl_8039E9A0[3];
const int lbl_8039E9A0[3] = {
    0x00000000, 0x00000000, 0x00000000,
};
}
static const FKVec s_position = { 10.0f, -5.5f, 3.0f };

#include "game/types/clFlowProcess.h"
struct FKInput {
    unsigned char opaque0[4], enabled, opaque5[0xF];
    int delta, first, second;
};
struct FKSprite {
    unsigned char data[0x30];
    FKSprite ARGS_ORDER((int id, float x, float y, int flag), (int id, int flag, float x, float y));
    FKSprite(int, int, float, float, float, float, float, float);
};
struct FKResource {
    int id, chain, mode, opaqueC;
    unsigned char enabled, opaque11[3];
    float x, y, z, scaleX, scaleY, angle, width, height;
    int parameters[4];
    unsigned char opaque44[0x14];
    FKResource();
    ~FKResource() {}
};
struct FKScene { virtual ~FKScene(); virtual bool Begin(); virtual void End(); unsigned char opaque[0x3080]; FKScene(const char*); };
struct FKModel { unsigned char opaque[0x28]; FKModel(const char*, unsigned char); };
struct FKDriver { unsigned char opaque[0x384]; FKDriver(int, int, float*, int, int, int); };
struct FKTex { unsigned char opaque[0x22c]; float scale; FKTex(); };

class clFlowKart : public clFlowProcess {
public:
    virtual ~clFlowKart();
    virtual int Update();
    virtual void Draw();
    int selection, result, state;
    unsigned char pending, pad11[3];
    int frame;
    float brightness;
    FKScene* scene;
    FKModel* model;
    FKDriver* drivers[2];
    float matrix[12];
    FKVec position;
    FKSprite* sprites[6];
    FKTex* texture;
    FKResource resource;
    clFlowKart();
    void UpdateDisplay(int);
    int HandleConfirm();
};
extern "C" {
extern unsigned int g_characterId;
extern FKInput* g_pInputState;
extern unsigned char g_playerData[];
extern int g_gameMode;
extern signed char lbl_806D184C, lbl_806D184D;
extern const float lbl_806DA130, lbl_806DA134, lbl_806DA138, lbl_806DA13C, lbl_806DA144, lbl_806DA14C, lbl_806DA154, lbl_806DA15C, lbl_806DA174, lbl_806DA178, lbl_806DA17C, lbl_806DA180, lbl_806DA184, lbl_806DA188, lbl_806DA18C, lbl_806DA120, lbl_806DA124, lbl_806DA128, lbl_806DA12C, lbl_806DA140, lbl_806DA148, lbl_806DA150, lbl_806DA158, lbl_806DA160, lbl_806DA164, lbl_806DA168, lbl_806DA16C, lbl_806DA170;
void SetSyncTarget(int);
unsigned char PreloadResource(int);
int CObj_LoadIntoGX(FKScene*, const FKVec*);
int CObj_ApplyViewport(FKScene*, const FKVec*);
void PSMTXScale(float*, float, float, float);
void PSMTXTrans(float*, float, float, float);
void PSMTXIdentity(float*);
void PSMTXConcat(const float*, const float*, float*);
void PSMTXRotRad(float*, int, float);
unsigned char RenderObj_ItemStateMachine_Timed(FKDriver*, int, float, float);
unsigned char SetScreenBrightness(float);
unsigned char fn_801B8918(int);
const char* GetTextureByIdAndLang(unsigned int, int);
void TexMgr_SetTexture(FKTex*, const char*, ...);
void fn_801F93EC(FKTex*, float, float);
int isJapanese();
int GetCoinMilage(const void*);
unsigned char InitRumbleController(unsigned char);
void* GetInputManager();
void InputMgr_GetPlayer(void*, int);
void SetRumbleMode(int,int,int);
void SetKartVariant(int);
void fn_801B7C64();
unsigned char IsCardValid();
void Sprite_Destroy(FKSprite*, int);
void Sprite_SetAnimParam(FKSprite*, short, short);
void fn_8011FAB8(); void fn_801A1280();
void SetCourseScene3D(void*); void LObjList_ApplyForCObj(void*);
void CObj_DebugVizPathFlush(void*); void KartDriver_RenderTimed(void*,int,int);
void fn_801A1174(int,int,int,int,int); void fn_801A1128(float,float); void fn_801A0DF0();
void* fn_801F8E58(); void fn_801F8A34(void*,void*,int); void fn_8011FAFC(void*,int); void fn_801A0004(void*);
void RumbleUpdate(); void fn_801699D8(unsigned int,unsigned char);
void fn_801B7CAC(); int fn_801B87D8(); int fn_801B8398(int);
void KartMovement_ResetOnGoal(void*); void* KartDriver_Dtor(void*,short);
int Sprite_AdvanceAnim(FKSprite*,float);
void fn_80169C44(); void LObjList_Destroy(void*,int); void MemoryManager_TimedFree(void*); void fn_80120A08(int);
}
static inline FKInput* input() { return SINGLETON_INSTANCE(g_pInputState); }
static inline int indexed_value(const int* table, unsigned int index) { return table[index]; }
static inline void copy_position(FKVec* destination, const FKVec* source) { *destination = *source; }
static inline void ApplyFlowInput(clFlowKart* self, FKInput* state) { self->selection += state->delta; }
struct FKParams { int v[5]; };

extern "C" {
signed char clFlowKart_UpdateDisplay_data_8049BB30[3][13][3] = { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x04, 0x04, 0x05, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x04, 0x04, 0x05, 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x02, 0x03, 0x05, 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x02, 0x03, 0x02, 0x03, 0x04, 0x02, 0x03, 0x04, 0x01, 0x04, 0x05, 0x04, 0x02, 0x03, 0x01, 0x04, 0x05, 0x03, 0x02, 0x04, 0x01, 0x04, 0x05, 0x04, 0x02, 0x03, 0x02, 0x03, 0x04, 0x03, 0x02, 0x04, 0x04, 0x02, 0x03, 0x02, 0x03, 0x04, 0x03, 0x02, 0x04, 0x03, 0x03, 0x04, 0x03, 0x03, 0x04, 0x02, 0x04, 0x05, 0x05, 0x02, 0x03, 0x02, 0x04, 0x05, 0x04, 0x02, 0x04, 0x02, 0x04, 0x05, 0x05, 0x02, 0x03, 0x03, 0x03, 0x04, 0x04, 0x02, 0x04, 0x05, 0x02, 0x03, 0x03, 0x03, 0x04, 0x04, 0x02, 0x04 };
short clFlowKart_Init_data_8049BBA8[14] = {
    5759, 5760, 5769, 5763, 5771, 5768, 5770, 5764, 5761, 5766, 5765, 5762,
    5767, 0
};

}

clFlowKart::clFlowKart() {
    FKVec vector;
    float translation[12], rotation[12], scaling[12];
    float z, zero, initialScale;
    int character;
    SetSyncTarget(15);
    PreloadResource(0x167f);
    selection = 1;
    result = -1;
    state = 0;
    pending = 0;
    drivers[0] = 0;
    drivers[1] = 0;
    scene = new FKScene("cone.dat");
    model = new FKModel("cone.dat", 0);
    initialScale = lbl_806DA174;
    zero = lbl_806DA13C;
    z = lbl_806DA178;
    sprites[0] = 0;
    sprites[1] = 0;
    sprites[2] = 0;
    brightness = initialScale;
    frame = 0;
    sprites[3] = 0;
    sprites[4] = 0;
    sprites[5] = 0;
    vector.x = zero;
    vector.y = zero;
    vector.z = z;
    CObj_LoadIntoGX(scene, &vector);
    vector.x = lbl_806DA13C;
    vector.y = lbl_806DA13C;
    vector.z = lbl_806DA13C;
    CObj_ApplyViewport(scene, &vector);
    character = g_characterId;
    PSMTXScale(scaling, lbl_806DA130, lbl_806DA130, lbl_806DA130);
    copy_position(&position, &s_position);
    PSMTXTrans(translation, position.x, position.y, position.z);
    PSMTXIdentity(matrix);
    PSMTXConcat(scaling, matrix, matrix);
    PSMTXRotRad(rotation, 'x', lbl_806DA134);
    PSMTXConcat(rotation, matrix, matrix);
    PSMTXRotRad(rotation, 'y', lbl_806DA138);
    PSMTXConcat(rotation, matrix, matrix);
    PSMTXConcat(translation, matrix, matrix);
    drivers[0] = new FKDriver(6, character, matrix, 0, 0, 0);
    drivers[1] = new FKDriver(6, character, matrix, 0, 0, 2);
    if (drivers[0]) RenderObj_ItemStateMachine_Timed(drivers[0], 0, lbl_806DA13C, lbl_806DA13C);
    if (drivers[1]) RenderObj_ItemStateMachine_Timed(drivers[1], 0, lbl_806DA13C, lbl_806DA13C);
    if (input()) {
        FKInput* controller = input();
        controller->enabled = 1;
        controller->first = 0;
        controller->second = 0;
    }
    SetScreenBrightness(lbl_806DA144);
    fn_801B8918(0x1ae2);
    texture = new FKTex;
    TexMgr_SetTexture(texture, GetTextureByIdAndLang(indexed_value(lbl_8039E96C, g_characterId) + 0x95, -1));
    fn_801F93EC(texture, lbl_806DA17C, lbl_806DA14C);
    texture->scale = !isJapanese() ? lbl_806DA180 : lbl_806DA184;
    resource.id = 0x1d5c;
    resource.width = lbl_806DA188;
    resource.height = lbl_806DA188;
    resource.enabled = 1;
    resource.x = lbl_806DA18C;
    resource.y = lbl_806DA154;
    resource.z = lbl_806DA15C;
    character = g_characterId;
    if (GetCoinMilage(g_playerData) < g_kartEnhancedUnlockThreshold[character]) {
        resource.parameters[0] = -256;
        resource.parameters[1] = -256;
        resource.parameters[2] = -256;
        resource.parameters[3] = -256;
    }
    InitRumbleController(1);
}

clFlowKart::~clFlowKart() {
    fn_80169C44();
    if (input() != 0) {
        FKInput *state = input();

        state->enabled = 0;
        state->first = 0;
        state->second = 0;
    }
    SetScreenBrightness(lbl_806DA144);
    Sprite_Destroy(sprites[0], 1);
    Sprite_Destroy(sprites[1], 1);
    Sprite_Destroy(sprites[2], 1);
    KartDriver_Dtor(drivers[0], 1);
    KartDriver_Dtor(drivers[1], 1);
    delete scene;
    LObjList_Destroy(model, 1);
    Sprite_Destroy(sprites[3], 1);
    Sprite_Destroy(sprites[4], 1);
    Sprite_Destroy(sprites[5], 1);
    if (texture != 0) {
        MemoryManager_TimedFree(texture);
    }
    fn_80120A08(0x167F);
}

int clFlowKart::Update() {
    RumbleUpdate();
    if (pending) {
        state += 1;
        pending = 0;
    }
    frame += 1;
    switch (state) {
    case 0:
        if (frame == 1) {
            sprites[0] = new FKSprite(0x16A, 1, lbl_806DA148, lbl_806DA158,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA13C, lbl_806DA15C);
            sprites[1] = new FKSprite(0x9C, 1, lbl_806DA160, lbl_806DA164,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA168, lbl_806DA15C);
            sprites[2] = new FKSprite(0x9C, 1, lbl_806DA16C, lbl_806DA164,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA13C, lbl_806DA15C);
            UpdateDisplay(g_characterId);
            SetScreenBrightness(brightness);
        }
        if (frame > 30) {
            fn_801699D8(0, 1);
            lbl_806D184C = 1;
            lbl_806D184D = 0;
            pending = 1;
        }
        break;
    case 1: {
        int previous = selection;
        if (input()) {
            ApplyFlowInput(this, input());
            if (selection > 1)
                selection = 1;
            if (selection < 0)
                selection = 0;
            if (previous != selection)
                fn_801B7CAC();
            UpdateDisplay(g_characterId);
        }
        if (HandleConfirm() != -1) {
            frame = 0;
            pending = 1;
            KartMovement_ResetOnGoal(drivers[selection]);
            fn_801B87D8();
            lbl_806D184C = -1;
            Sprite_Destroy(sprites[1], 1);
            Sprite_Destroy(sprites[2], 1);
            sprites[1] = 0;
            sprites[2] = 0;
        }
        break;
    }
    case 2:
        if (frame == 50) {
            fn_801B87D8();
            fn_801B8398(0);
            KartDriver_Dtor(drivers[0], 1);
            KartDriver_Dtor(drivers[1], 1);
            Sprite_Destroy(sprites[0], 1);
            Sprite_Destroy(sprites[1], 1);
            Sprite_Destroy(sprites[2], 1);
            Sprite_Destroy(sprites[3], 1);
            Sprite_Destroy(sprites[4], 1);
            Sprite_Destroy(sprites[5], 1);
            drivers[0] = 0;
            drivers[1] = 0;
            sprites[0] = 0;
            sprites[1] = 0;
            sprites[2] = 0;
            frame = 0;
            sprites[3] = 0;
            sprites[4] = 0;
            sprites[5] = 0;
            pending = 1;
            fn_801699D8(0, 0);
        }
        break;
    case 3:
        if (frame == 52)
            pending = 1;
        break;
    case 4:
        return result;
    }
    if (sprites[0])
        Sprite_AdvanceAnim(sprites[0], lbl_806DA170);
    if (sprites[1])
        Sprite_AdvanceAnim(sprites[1], lbl_806DA170);
    if (sprites[2])
        Sprite_AdvanceAnim(sprites[2], lbl_806DA170);
    if (drivers[0])
        RenderObj_ItemStateMachine_Timed(drivers[0], 0, lbl_806DA13C, lbl_806DA13C);
    if (drivers[1])
        RenderObj_ItemStateMachine_Timed(drivers[1], 0, lbl_806DA13C, lbl_806DA13C);
    if (sprites[3])
        Sprite_AdvanceAnim(sprites[3], lbl_806DA170);
    if (sprites[4])
        Sprite_AdvanceAnim(sprites[4], lbl_806DA170);
    if (sprites[5])
        Sprite_AdvanceAnim(sprites[5], lbl_806DA170);
    return -1;
}

void clFlowKart::Draw() {
    fn_8011FAB8();
    fn_801A1280();
    if (scene != 0) {
        SetCourseScene3D(scene);
        if ((unsigned char)scene->Begin()) {
            LObjList_ApplyForCObj(model);
            CObj_DebugVizPathFlush(scene);
            if (drivers[selection] != 0) {
                KartDriver_RenderTimed(drivers[selection], 0, 1);
            }
            scene->End();
        }
        SetCourseScene3D(0);
    }
    if (state == 0 || state == 1 || state == 2) {
        fn_801A1174(0x16ad, 4, 0, 0, 0);
        fn_801A1128(lbl_806DA148, lbl_806DA14C);
        fn_801A0DF0();
        fn_801A1174(clFlowKart_Init_data_8049BBA8[g_characterId], 4, 0, 0, 0);
        fn_801A1128(lbl_806DA150, lbl_806DA154);
        fn_801A0DF0();
        fn_801F8A34(fn_801F8E58(), texture, 5);
        if (selection == 1) {
            fn_8011FAFC(&resource, 5);
        }
    }
    if (sprites[0] != 0) fn_801A0004(sprites[0]);
    if (selection == 0) {
        if (sprites[2] != 0) fn_801A0004(sprites[2]);
    } else {
        if (sprites[1] != 0) fn_801A0004(sprites[1]);
    }
    if (sprites[3] != 0) fn_801A0004(sprites[3]);
    if (sprites[4] != 0) fn_801A0004(sprites[4]);
    if (sprites[5] != 0) fn_801A0004(sprites[5]);
}

int clFlowKart::HandleConfirm() {
    char *input;
    unsigned char *pd;
    unsigned char flag;

    if (result != -1) {
        return result;
    }
    brightness -= lbl_806DA140;
    InputMgr_GetPlayer(GetInputManager(), 0);
    input = (char*)SINGLETON_INSTANCE(g_pInputState);
    if (*(int *)(input + 0x18) == 1 || brightness < lbl_806DA13C) {
        SetRumbleMode(0, 1, 1);
        if (selection == 0) {
            SetKartVariant(0);
        } else {
            int chara = g_characterId;
            if (GetCoinMilage(g_playerData) >= g_kartEnhancedUnlockThreshold[chara]) {
                SetKartVariant(3);
            } else {
                SetKartVariant(2);
            }
        }
        pd = g_playerData;
        flag = 0;
        if (g_gameMode != 2) {
            if (pd[0x19F] == 0) {
                flag = 1;
            }
            if (pd[0x19D] == 1) {
                flag = 1;
            }
        } else {
            flag = 1;
        }
        if (!flag) {
            if (g_gameMode == 0) {
                result = 0x15;
            } else {
                result = 0x17;
            }
        } else {
            result = 0x13;
        }
        brightness = lbl_806DA144;
        fn_801B7C64();
    }
    SetScreenBrightness(brightness);
    return result;
}

#pragma push
#pragma use_lmw_stmw on
void clFlowKart::UpdateDisplay(int kart) {

    int level = 0;
    FKParams params;
    if (selection >= 1) {
        if (GetCoinMilage(g_playerData) >= lbl_8039E904[kart]) level = 1;
        if (GetCoinMilage(g_playerData) >= g_kartEnhancedUnlockThreshold[kart]) level = 2;
        if (!IsCardValid()) level = 1;
    }
    Sprite_Destroy(sprites[3], 1);
    Sprite_Destroy(sprites[4], 1);
    Sprite_Destroy(sprites[5], 1);
    sprites[3] = new FKSprite ARGS_ORDER((0x16B, lbl_806DA120, lbl_806DA124, 1), (0x16B, 1, lbl_806DA120, lbl_806DA124));
    sprites[4] = new FKSprite ARGS_ORDER((0x16B, lbl_806DA120, lbl_806DA128, 1), (0x16B, 1, lbl_806DA120, lbl_806DA128));
    sprites[5] = new FKSprite ARGS_ORDER((0x16B, lbl_806DA120, lbl_806DA12C, 1), (0x16B, 1, lbl_806DA120, lbl_806DA12C));
    {
    int arr[5] = {0x16B4, 0x16B3, 0x16B2, 0x16B1, 0x16B0};
    for (int a = 0; a < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][0]; a++) Sprite_SetAnimParam(sprites[3], arr[a], -1);
    for (int b = 0; b < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][1]; b++) Sprite_SetAnimParam(sprites[4], arr[b], -1);
    for (int d = 0; d < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][2]; d++) Sprite_SetAnimParam(sprites[5], arr[d], -1);
    }
}
#pragma pop
