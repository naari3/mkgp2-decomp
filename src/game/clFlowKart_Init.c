#include "game/types/arg_order.h"
/* clFlowKart_Init: FlowKart constructor (C++, compiled with -lang=c++).
 * The TU owns .rodata 0x8039E508..0x8039E9F8 so the pooled base register is
 * hoisted to the prologue like the target. Unused objects stay global so they
 * are emitted in place; "cone.dat" is a string literal emitted after them.
 * Mangled names are mapped to the original symbols in
 * tools/extab_user_renames.json.
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
extern "C" {
extern const char clFlowKart[];
extern const char clFlowProcess[];
}
struct FKInput {
    unsigned char opaque0[4], enabled, opaque5[0x13];
    int first, second;
};
extern "C" {
extern unsigned int g_characterId;
extern FKInput* g_pInputState;
extern unsigned char g_playerData[];
extern const float lbl_806DA130, lbl_806DA134, lbl_806DA138, lbl_806DA13C;
extern const float lbl_806DA144, lbl_806DA14C, lbl_806DA154, lbl_806DA15C;
extern const float lbl_806DA174, lbl_806DA178, lbl_806DA17C, lbl_806DA180;
extern const float lbl_806DA184, lbl_806DA188, lbl_806DA18C;
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
}
typedef struct FKParams { int v[5]; } FKParams;
struct FKSprite {
    unsigned char data[0x30];
    FKSprite ARGS_ORDER((int id, float x, float y, int flag), (int id, int flag, float x, float y));
};
struct FKDisplay {
    unsigned char pad00[0x4];
    int unlocked;
    unsigned char pad08[0x74 - 0x08];
    FKSprite *rank[3];
};
extern "C" {
unsigned char IsCardValid(void);
void Sprite_Destroy(FKSprite *sprite, int flag);
void Sprite_SetAnimParam(FKSprite *sprite, short param, short key);
extern const float lbl_806DA120;
extern const float lbl_806DA124;
extern const float lbl_806DA128;
extern const float lbl_806DA12C;
extern signed char clFlowKart_UpdateDisplay_data_8049BB30[][13][3];
}
static inline void HideParams(FKDisplay *self, int idx, int *p, signed char *n) {
    for (int i = 0; i < 5 - *n; i++) {
        Sprite_SetAnimParam(self->rank[idx], p[i], -1);
    }
}
#pragma push
#pragma use_lmw_stmw on
extern "C" void clFlowKart_UpdateDisplay(FKDisplay *self, int kart)
{
    int level = 0;
    FKParams params;
    if (self->unlocked >= 1) {
        if (GetCoinMilage(g_playerData) >= lbl_8039E904[kart]) level = 1;
        if (GetCoinMilage(g_playerData) >= g_kartEnhancedUnlockThreshold[kart]) level = 2;
        if (!IsCardValid()) level = 1;
    }
    Sprite_Destroy(self->rank[0], 1);
    Sprite_Destroy(self->rank[1], 1);
    Sprite_Destroy(self->rank[2], 1);
    self->rank[0] = new FKSprite ARGS_ORDER((0x16B, lbl_806DA120, lbl_806DA124, 1), (0x16B, 1, lbl_806DA120, lbl_806DA124));
    self->rank[1] = new FKSprite ARGS_ORDER((0x16B, lbl_806DA120, lbl_806DA128, 1), (0x16B, 1, lbl_806DA120, lbl_806DA128));
    self->rank[2] = new FKSprite ARGS_ORDER((0x16B, lbl_806DA120, lbl_806DA12C, 1), (0x16B, 1, lbl_806DA120, lbl_806DA12C));
    {
    int arr[5] = {0x16B4, 0x16B3, 0x16B2, 0x16B1, 0x16B0};
    for (int a = 0; a < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][0]; a++) Sprite_SetAnimParam(self->rank[0], arr[a], -1);
    for (int b = 0; b < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][1]; b++) Sprite_SetAnimParam(self->rank[1], arr[b], -1);
    for (int d = 0; d < 5 - clFlowKart_UpdateDisplay_data_8049BB30[level][kart][2]; d++) Sprite_SetAnimParam(self->rank[2], arr[d], -1);
    }
}
#pragma pop
extern const char clFlowKart[] = "clFlowKart";
extern const char clFlowProcess[] = "clFlowProcess";

/* ---- clFlowKart_HandleConfirm (0x801D7B50) ---- */
namespace fk_confirm {
/* clFlowKart_HandleConfirm (0x801D7B50): kart select confirm; sets the kart variant and next flow state. */

typedef struct {
    char pad00[0x4];
    int cursor;
    int next;
    char pad0C[0x18 - 0xC];
    float timer;
} clFlowKart;

extern "C" {
extern const float lbl_806DA13C;
extern const float lbl_806DA140;
extern const float lbl_806DA144;
#ifdef __MWERKS__
extern char *g_pInputState;
#else /* this namespace sees g_pInputState with another type: a view of the same object */
static char * &g_pInputState = *(char * *)&::g_pInputState;
#endif
#ifdef __MWERKS__
extern int g_characterId;
#else /* this namespace sees g_characterId with another type: a view of the same object */
static int &g_characterId = *(int *)&::g_characterId;
#endif
extern int g_gameMode;
extern unsigned char g_playerData[];
#ifdef __MWERKS__
extern int g_kartEnhancedUnlockThreshold[];
#else /* this namespace sees g_kartEnhancedUnlockThreshold with another type: a view of the same object */
static int *const g_kartEnhancedUnlockThreshold = (int *)::g_kartEnhancedUnlockThreshold;
#endif
extern void *GetInputManager(void);
extern void InputMgr_GetPlayer(void *mgr, int idx);
extern void SetRumbleMode(int a, int b, int c);
#ifdef __MWERKS__
extern int GetCoinMilage(void *pd);
#else /* this namespace declares GetCoinMilage with other types: a view of the same object */
static inline int GetCoinMilage(void * a0) { return (int)((int (*)(void *))&::GetCoinMilage)(a0); }
#endif
extern void SetKartVariant(int v);
extern void fn_801B7C64(void);
#ifdef __MWERKS__
extern void SetScreenBrightness(float b);
#else /* this namespace declares SetScreenBrightness with other types: a view of the same object */
static inline void SetScreenBrightness(float a0) { ((void (*)(float))&::SetScreenBrightness)(a0); }
#endif

}
#pragma exceptions on
extern "C" int clFlowKart_HandleConfirm(clFlowKart *self) {
    char *input;
    unsigned char *pd;
    unsigned char flag;

    if (self->next != -1) {
        return self->next;
    }
    self->timer -= lbl_806DA140;
    InputMgr_GetPlayer(GetInputManager(), 0);
    if ((input = g_pInputState) == 0) {
        input = 0;
    }
    if (*(int *)(input + 0x18) == 1 || self->timer < lbl_806DA13C) {
        SetRumbleMode(0, 1, 1);
        if (self->cursor == 0) {
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
                self->next = 0x15;
            } else {
                self->next = 0x17;
            }
        } else {
            self->next = 0x13;
        }
        self->timer = lbl_806DA144;
        fn_801B7C64();
    }
    SetScreenBrightness(self->timer);
    return self->next;
}
#pragma exceptions reset
}

/* ---- fn_801D7CC4 ---- */
#pragma push
namespace fk_draw {
class Scene { public: virtual void v0(); virtual bool Begin(); virtual void End(); };
typedef struct FlowKartDraw {
    int unk0;
    int selection;
    int unk8;
    int state;
    char pad10[0xC];
    Scene *scene;
    void *lobj;
    void *drivers[2];
    char pad2C[0x3C];
    void *sprites[6];
    void *text;
    char ctrl[4];
} FlowKartDraw;
extern "C" {
#ifdef __MWERKS__
extern int g_characterId;
#else /* this namespace sees g_characterId with another type: a view of the same object */
static int &g_characterId = *(int *)&::g_characterId;
#endif
extern short clFlowKart_Init_data_8049BBA8[];
extern const float lbl_806DA148, lbl_806DA14C, lbl_806DA150, lbl_806DA154;
void fn_8011FAB8(void);
void fn_801A1280(void);
void SetCourseScene3D(void *);
void LObjList_ApplyForCObj(void *);
void CObj_DebugVizPathFlush(void *);
void KartDriver_RenderTimed(void *, int, int);
void fn_801A1174(int, int, int, int, int);
void fn_801A1128(float, float);
void fn_801A0DF0(void);
void *fn_801F8E58(void);
void fn_801F8A34(void *, void *, int);
void fn_8011FAFC(void *, int);
void fn_801A0004(void *);
}

extern "C" void fn_801D7CC4(FlowKartDraw *self)
{
    fn_8011FAB8();
    fn_801A1280();
    if (self->scene != 0) {
        SetCourseScene3D(self->scene);
        if ((unsigned char)self->scene->Begin()) {
            LObjList_ApplyForCObj(self->lobj);
            CObj_DebugVizPathFlush(self->scene);
            if (self->drivers[self->selection] != 0) {
                KartDriver_RenderTimed(self->drivers[self->selection], 0, 1);
            }
            self->scene->End();
        }
        SetCourseScene3D(0);
    }
    if (self->state == 0 || self->state == 1 || self->state == 2) {
        fn_801A1174(0x16ad, 4, 0, 0, 0);
        fn_801A1128(lbl_806DA148, lbl_806DA14C);
        fn_801A0DF0();
        fn_801A1174(clFlowKart_Init_data_8049BBA8[g_characterId], 4, 0, 0, 0);
        fn_801A1128(lbl_806DA150, lbl_806DA154);
        fn_801A0DF0();
        fn_801F8A34(fn_801F8E58(), self->text, 5);
        if (self->selection == 1) {
            fn_8011FAFC(self->ctrl, 5);
        }
    }
    if (self->sprites[0] != 0) fn_801A0004(self->sprites[0]);
    if (self->selection == 0) {
        if (self->sprites[2] != 0) fn_801A0004(self->sprites[2]);
    } else {
        if (self->sprites[1] != 0) fn_801A0004(self->sprites[1]);
    }
    if (self->sprites[3] != 0) fn_801A0004(self->sprites[3]);
    if (self->sprites[4] != 0) fn_801A0004(self->sprites[4]);
    if (self->sprites[5] != 0) fn_801A0004(self->sprites[5]);
}
}
#pragma pop

/* ---- clFlowKart_Update (0x801D7E84) ---- */
#pragma push
namespace fk_update {
/* Observed FlowKart update layout only; Sprite lifetime supplies automatic EH. */
class FlowSprite {
    unsigned char observed[48];
public:
    FlowSprite(int id, int loop, float x, float y, float sx, float sy, float yaw, float step);
};
struct FlowInput {
    unsigned char pad[0x14];
    int delta;
};
struct FlowUpdateView {
    unsigned int unknown;
    int selection;
    int result;
    int state;
    unsigned char pending;
    unsigned char pad11[3];
    int frame;
    float brightness;
    unsigned char pad1C[8];
    void* drivers[2];
    unsigned char pad2C[0x3C];
    FlowSprite* sprites[6];
};
extern "C" {
#ifdef __MWERKS__
extern FlowInput* g_pInputState;
#else /* this namespace sees g_pInputState with another type: a view of the same object */
static FlowInput* &g_pInputState = *(FlowInput* *)&::g_pInputState;
#endif
#ifdef __MWERKS__
extern int g_characterId;
#else /* this namespace sees g_characterId with another type: a view of the same object */
static int &g_characterId = *(int *)&::g_characterId;
#endif
extern signed char lbl_806D184C, lbl_806D184D;
extern const float lbl_806DA13C, lbl_806DA148, lbl_806DA158, lbl_806DA15C;
extern const float lbl_806DA160, lbl_806DA164, lbl_806DA168, lbl_806DA16C, lbl_806DA170;
void RumbleUpdate();
void fn_801699D8(unsigned int, unsigned char);
#ifdef __MWERKS__
int SetScreenBrightness(float);
#else /* this namespace declares SetScreenBrightness with other types: a view of the same object */
static inline int SetScreenBrightness(float a0) { return (int)((unsigned char (*)(float))&::SetScreenBrightness)(a0); }
#endif
void fn_801B7CAC();
int fn_801B87D8();
int fn_801B8398(int);
#ifdef __MWERKS__
int clFlowKart_HandleConfirm(FlowUpdateView*);
#else /* this namespace declares clFlowKart_HandleConfirm with other types: a view of the same object */
static inline int clFlowKart_HandleConfirm(FlowUpdateView* a0) { return (int)((int (*)(FlowUpdateView*))&fk_confirm::clFlowKart_HandleConfirm)(a0); }
#endif
#ifdef __MWERKS__
void clFlowKart_UpdateDisplay(FlowUpdateView*, int);
#else /* this namespace declares clFlowKart_UpdateDisplay with other types: a view of the same object */
static inline void clFlowKart_UpdateDisplay(FlowUpdateView* a0, int a1) { ((void (*)(FlowUpdateView*, int))&::clFlowKart_UpdateDisplay)(a0, a1); }
#endif
void KartMovement_ResetOnGoal(void*);
void* KartDriver_Dtor(void*, short);
#ifdef __MWERKS__
FlowSprite* Sprite_Destroy(FlowSprite*, short);
#else /* this namespace declares Sprite_Destroy with other types: a view of the same object */
static inline FlowSprite* Sprite_Destroy(FlowSprite* a0, short a1) { return ((FlowSprite* (*)(FlowSprite*, short))&::Sprite_Destroy)(a0, a1); }
#endif
int Sprite_AdvanceAnim(FlowSprite*, float);
#ifdef __MWERKS__
int RenderObj_ItemStateMachine_Timed(void*, int, float, float);
#else /* this namespace declares RenderObj_ItemStateMachine_Timed with other types: a view of the same object */
static inline int RenderObj_ItemStateMachine_Timed(void* a0, int a1, float a2, float a3) { return (int)((unsigned char (*)(void*, int, float, float))&::RenderObj_ItemStateMachine_Timed)(a0, a1, a2, a3); }
#endif
}
static inline FlowInput* CurrentFlowInput()
{
    return SINGLETON_INSTANCE(g_pInputState);
}
/* Evaluate the nullable input getter before reading the current selection. */
static inline void ApplyFlowInput(FlowUpdateView* self, FlowInput* input)
{
    self->selection += input->delta;
}
extern "C" int clFlowKart_Update(FlowUpdateView* self)
{
    RumbleUpdate();
    if (self->pending) {
        self->state += 1;
        self->pending = 0;
    }
    self->frame += 1;
    switch (self->state) {
    case 0:
        if (self->frame == 1) {
            self->sprites[0] = new FlowSprite(0x16A, 1, lbl_806DA148, lbl_806DA158,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA13C, lbl_806DA15C);
            self->sprites[1] = new FlowSprite(0x9C, 1, lbl_806DA160, lbl_806DA164,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA168, lbl_806DA15C);
            self->sprites[2] = new FlowSprite(0x9C, 1, lbl_806DA16C, lbl_806DA164,
                lbl_806DA15C, lbl_806DA15C, lbl_806DA13C, lbl_806DA15C);
            clFlowKart_UpdateDisplay(self, g_characterId);
            SetScreenBrightness(self->brightness);
        }
        if (self->frame > 30) {
            fn_801699D8(0, 1);
            lbl_806D184C = 1;
            lbl_806D184D = 0;
            self->pending = 1;
        }
        break;
    case 1: {
        int previous = self->selection;
        if (CurrentFlowInput()) {
            ApplyFlowInput(self, CurrentFlowInput());
            if (self->selection > 1)
                self->selection = 1;
            if (self->selection < 0)
                self->selection = 0;
            if (previous != self->selection)
                fn_801B7CAC();
            clFlowKart_UpdateDisplay(self, g_characterId);
        }
        if (clFlowKart_HandleConfirm(self) != -1) {
            self->frame = 0;
            self->pending = 1;
            KartMovement_ResetOnGoal(self->drivers[self->selection]);
            fn_801B87D8();
            lbl_806D184C = -1;
            Sprite_Destroy(self->sprites[1], 1);
            Sprite_Destroy(self->sprites[2], 1);
            self->sprites[1] = 0;
            self->sprites[2] = 0;
        }
        break;
    }
    case 2:
        if (self->frame == 50) {
            fn_801B87D8();
            fn_801B8398(0);
            KartDriver_Dtor(self->drivers[0], 1);
            KartDriver_Dtor(self->drivers[1], 1);
            Sprite_Destroy(self->sprites[0], 1);
            Sprite_Destroy(self->sprites[1], 1);
            Sprite_Destroy(self->sprites[2], 1);
            Sprite_Destroy(self->sprites[3], 1);
            Sprite_Destroy(self->sprites[4], 1);
            Sprite_Destroy(self->sprites[5], 1);
            self->drivers[0] = 0;
            self->drivers[1] = 0;
            self->sprites[0] = 0;
            self->sprites[1] = 0;
            self->sprites[2] = 0;
            self->frame = 0;
            self->sprites[3] = 0;
            self->sprites[4] = 0;
            self->sprites[5] = 0;
            self->pending = 1;
            fn_801699D8(0, 0);
        }
        break;
    case 3:
        if (self->frame == 52)
            self->pending = 1;
        break;
    case 4:
        return self->result;
    }
    if (self->sprites[0])
        Sprite_AdvanceAnim(self->sprites[0], lbl_806DA170);
    if (self->sprites[1])
        Sprite_AdvanceAnim(self->sprites[1], lbl_806DA170);
    if (self->sprites[2])
        Sprite_AdvanceAnim(self->sprites[2], lbl_806DA170);
    if (self->drivers[0])
        RenderObj_ItemStateMachine_Timed(self->drivers[0], 0, lbl_806DA13C, lbl_806DA13C);
    if (self->drivers[1])
        RenderObj_ItemStateMachine_Timed(self->drivers[1], 0, lbl_806DA13C, lbl_806DA13C);
    if (self->sprites[3])
        Sprite_AdvanceAnim(self->sprites[3], lbl_806DA170);
    if (self->sprites[4])
        Sprite_AdvanceAnim(self->sprites[4], lbl_806DA170);
    if (self->sprites[5])
        Sprite_AdvanceAnim(self->sprites[5], lbl_806DA170);
    return -1;
}

}
#pragma pop

/* ---- dtor (0x801D8284) ---- */
namespace fk_dtor {
class Deletable {
public:
    virtual ~Deletable();
};

struct InputState {
    unsigned char pad_00[4];
    unsigned char active;
    unsigned char pad_05[0x13];
    int value18;
    int value1C;
};

struct SceneObject {
    void *vtbl;
    unsigned char pad_04[0x18];
    Deletable *child;
    void *lobjList;
    void *driverA;
    void *driverB;
    unsigned char pad_2C[0x3C];
    void *sprites[3];
    void *sprites2[3];
    void *buffer;
};

extern "C" {
extern char FKOwner_vtable_8049BBD0[];
#ifdef __MWERKS__
extern InputState *g_pInputState;
#else /* this namespace sees g_pInputState with another type: a view of the same object */
static InputState * &g_pInputState = *(InputState * *)&::g_pInputState;
#endif
void fn_80169C44(void);
#ifdef __MWERKS__
void SetScreenBrightness(float);
#else /* this namespace declares SetScreenBrightness with other types: a view of the same object */
static inline void SetScreenBrightness(float a0) { ((void (*)(float))&::SetScreenBrightness)(a0); }
#endif
#ifdef __MWERKS__
void Sprite_Destroy(void *, int);
#else /* this namespace declares Sprite_Destroy with other types: a view of the same object */
static inline void Sprite_Destroy(void * a0, int a1) { ((void (*)(void *, int))&::Sprite_Destroy)(a0, a1); }
#endif
#ifdef __MWERKS__
void KartDriver_Dtor(void *, int);
#else /* this namespace declares KartDriver_Dtor with other types: a view of the same object */
static inline void KartDriver_Dtor(void * a0, int a1) { ((void (*)(void *, int))&fk_update::KartDriver_Dtor)(a0, a1); }
#endif
void LObjList_Destroy(void *, int);
void MemoryManager_TimedFree(void *);
void fn_80120A08(int);
void dtor_801BA14C(void *, int);
}

static inline InputState *input_state(void) {
    InputState *state = g_pInputState;

    if (state == 0) {
        return 0;
    }
    return state;
}

extern "C" SceneObject *dtor(SceneObject *self, short flags) {
    if (self != 0) {
        self->vtbl = FKOwner_vtable_8049BBD0;
        fn_80169C44();
        if (input_state() != 0) {
            InputState *state = input_state();

            state->active = 0;
            state->value18 = 0;
            state->value1C = 0;
        }
        SetScreenBrightness(lbl_806DA144);
        Sprite_Destroy(self->sprites[0], 1);
        Sprite_Destroy(self->sprites[1], 1);
        Sprite_Destroy(self->sprites[2], 1);
        KartDriver_Dtor(self->driverA, 1);
        KartDriver_Dtor(self->driverB, 1);
        delete self->child;
        LObjList_Destroy(self->lobjList, 1);
        Sprite_Destroy(self->sprites2[0], 1);
        Sprite_Destroy(self->sprites2[1], 1);
        Sprite_Destroy(self->sprites2[2], 1);
        if (self->buffer != 0) {
            MemoryManager_TimedFree(self->buffer);
        }
        fn_80120A08(0x167F);
        dtor_801BA14C(self, 0);
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
}
struct FKBase {
    FKBase();
    virtual ~FKBase();
    virtual void identity();
};
struct FKResource {
    int id, chain, mode, opaqueC;
    unsigned char enabled, opaque11[3];
    float x, y, z, scaleX, scaleY, angle, width, height;
    int parameters[4];
    unsigned char opaque44[0x14];
    FKResource();
    ~FKResource();
};
struct FKScene { unsigned char opaque[0x3084]; FKScene(const char*); };
struct FKModel { unsigned char opaque[0x28]; FKModel(const char*, unsigned char); };
struct FKDriver { unsigned char opaque[0x384]; FKDriver(int, int, float*, int, int, int); };
struct FKTex { unsigned char opaque[0x22c]; float scale; FKTex(); };
static inline FKInput* input()
{
    if (g_pInputState == 0) return 0;
    return g_pInputState;
}
static inline int indexed_value(const int* table, unsigned int index)
{
    return table[index];
}
static inline void copy_position(FKVec* destination, const FKVec* source)
{
    *destination = *source;
}
struct FKOwner : FKBase {
    int state, selection, opaqueC;
    unsigned char active, opaque11[3];
    int counter;
    float scale;
    FKScene* scene;
    FKModel* model;
    FKDriver* driver;
    FKDriver* alternate;
    float matrix[12];
    FKVec position;
    int slots[3], values[3];
    FKTex* texture;
    FKResource resource;
    FKOwner();
    virtual void identity();
};
FKOwner::FKOwner()
{
    FKVec vector;
    float translation[12], rotation[12], scaling[12];
    float z, zero, initialScale;
    int character;
    SetSyncTarget(15);
    PreloadResource(0x167f);
    state = 1;
    selection = -1;
    opaqueC = 0;
    active = 0;
    driver = 0;
    alternate = 0;
    scene = new FKScene("cone.dat");
    model = new FKModel("cone.dat", 0);
    initialScale = lbl_806DA174;
    zero = lbl_806DA13C;
    z = lbl_806DA178;
    slots[0] = 0;
    slots[1] = 0;
    slots[2] = 0;
    scale = initialScale;
    counter = 0;
    values[0] = 0;
    values[1] = 0;
    values[2] = 0;
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
    driver = new FKDriver(6, character, matrix, 0, 0, 0);
    alternate = new FKDriver(6, character, matrix, 0, 0, 2);
    if (driver) RenderObj_ItemStateMachine_Timed(driver, 0, lbl_806DA13C, lbl_806DA13C);
    if (alternate) RenderObj_ItemStateMachine_Timed(alternate, 0, lbl_806DA13C, lbl_806DA13C);
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
