/* clFlowClass: deferred original unit, definitions follow reverse text order. */
#include "game/ClassUpdatePrivate.h"
#include "game/types/clFlowProcess.h"
#include "game/singleton.h"

class clFlowClass : public clFlowProcess {
public:
    clFlowClass();
    virtual ~clFlowClass();
    virtual int Update();
    virtual void Draw();

    unsigned char advance, mode, fading, pad7;
    int count, selection, unknown10, state, selectedSpecial, indicatorStarted;
    float brightness, elapsed;
    int result;
    ClassSprite *indicator, *sprites[3], *extra;
    int unknown40;
    ClassSprite *left, *right;
    int ticks; float startX,startY;
};

struct FlowInput { unsigned char pad0[4]; unsigned char enabled; unsigned char pad5[15]; int delta, held, edge; };
struct clFlowClass_Update_rodata_8039A5A0_Pool { float f_000[255]; int i_3FC[27]; };
/* The update reads the shared animation pool through a mutable byte view.
 * Keep that view separate from its native constant definition. */
namespace flow_data {
extern "C" {
extern const clFlowClass_Update_rodata_8039A5A0_Pool clFlowClass_Update_rodata_8039A5A0 = {
    { 1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f },
    { 333, 2, 332, 333, 331, 332, 12, 2, 7, 11, 1, 6, 12, 2, 7, 13, 3, 8, 10, 0, 5, 12, 2, 7, 11, 1, 6 }
};
}
}
#if defined(__MWERKS__) && !defined(__clang__)
#define classAnimationPool clFlowClass_Update_rodata_8039A5A0
extern "C" unsigned char clFlowClass_Update_rodata_8039A5A0[];
#else
static unsigned char *const classAnimationPool = (unsigned char *)&flow_data::clFlowClass_Update_rodata_8039A5A0;
#endif
extern "C" const ClassAnims lbl_8039AA08[1] = {
    { { 13, 3, 8 } }
};
extern "C" const ClassAnims lbl_8039AA14[1] = {
    { { 10, 0, 5 } }
};

extern "C" {
extern int g_gameMode, g_currentSceneState, g_ccClass;
extern FlowInput *g_pInputState;
extern signed char lbl_806D184C,lbl_806D184D;
extern const float lbl_806D9AF4,lbl_806D9AF8,lbl_806D9AFC;
extern const float lbl_806D9B08,lbl_806D9B0C,lbl_806D9B10,lbl_806D9B14,lbl_806D9B18,lbl_806D9B1C,lbl_806D9B20;
extern const float lbl_806D9B24,lbl_806D9B28,lbl_806D9B2C,lbl_806D9B30,lbl_806D9B34,lbl_806D9B38,lbl_806D9B3C;
extern const float lbl_806D9B40,lbl_806D9B44,lbl_806D9B48,lbl_806D9B4C;
void RumbleUpdate();
unsigned char Sprite_AdvanceAnim(ClassSprite*,float);
void Sprite_SetupAnim(ClassSprite*,int,int,int);
void fn_8019FF6C(ClassSprite*,int);
void Sprite_Destroy(ClassSprite*,short);
void SetScreenBrightness(float);
void fn_801699D8(int,int);
void *GetInputManager();
ClassPlayer *InputMgr_GetPlayer(void*,int);
void SetRumbleMode(int,int,int);
void fn_801B8874(int);
void fn_801B89C8(int);
void fn_801B7CAC();
int fn_801C1F88(clFlowClass*);
void fn_801B87D8();
unsigned char fn_801B87B0();
void SetSyncTarget(int);
void StartScreenFade(float);
unsigned char IsSyncReached();
unsigned char *SyncSlot_GetRecv();
void fn_801B7B04(int);
}
static inline FlowInput *input() { return SINGLETON_INSTANCE(g_pInputState); }
static inline float interpolate(float start, float end, int frame, float duration) {
    float step = (end-start)/duration;
    return step * frame + start;
}
static inline int selection(const clFlowClass *self) { return self->selection; }
static inline void SetPos(ClassSprite *s, float x, float y) { s->x=x; s->y=y; }
extern "C" {
extern FlowInput *g_pInputState;
extern int g_gameMode;
extern const float lbl_806D9AF4;
extern const float lbl_806D9AF8;
extern const float lbl_806D9AFC;
extern const float lbl_806D9B04;
extern const float lbl_806D9B10;
extern const float lbl_806D9B14;
extern const float lbl_806D9B48;
extern const float lbl_806D9B4C;
void InitBGM(void);
void InitRumbleController(int arg);
void PreloadResource(int id);
void SetScreenBrightness(float level);
void SetSyncTarget(int target);
int SetupBgSprites(unsigned char enable);
void SpriteSystem_EnsureInit(void);
int fn_801B8918(int value);
void fn_801B7B04(int arg);
}

clFlowClass::clFlowClass() {
    SetSyncTarget(0xB);
    SpriteSystem_EnsureInit();
    PreloadResource(0x1B13);
    PreloadResource(0x1B12);
    PreloadResource(0x1666);
    PreloadResource(0x1ADE);
    PreloadResource(0x1ADF);
    PreloadResource(0x1AE0);
    PreloadResource(0x166F);
    sprites[0] = new ClassSprite(0xE, 1, 0);
    if (g_gameMode == 2) {
        SetPos(sprites[0], lbl_806D9B48, lbl_806D9B10);
    } else {
        SetPos(sprites[0], lbl_806D9B48, lbl_806D9B14);
    }
    sprites[1] = 0;
    sprites[2] = 0;
    selectedSpecial = 0;
    indicatorStarted = 0;
    indicator = 0;
    elapsed = lbl_806D9AF4;
    state = 0;
    unknown40 = 0;
    advance = 0;
    selection = 1;
    result = -1;
    mode = 0;
    brightness = lbl_806D9B4C;
    left = 0;
    right = 0;
    ticks = 0;
    startX = lbl_806D9AF4;
    startY = lbl_806D9AF4;
    fading = 0;
    if (g_gameMode != 2) {
        extra = new ClassSprite(0x47, 1, 0);
        count = 4;
    } else {
        extra = 0;
        count = 3;
    }
    if (extra != 0) {
        SetPos(extra, lbl_806D9AFC, lbl_806D9B04);
    }
    if (input()) {
        FlowInput *in = input();
        in->enabled = 1;
        in->held = 0;
        in->edge = 0;
    }
    InitBGM();
    SetupBgSprites(1);
    SetScreenBrightness(lbl_806D9AF8);
    InitRumbleController(1);
    if (g_gameMode == 2) {
        fn_801B8918(0x1ADE);
    } else {
        fn_801B8918(0x1ADF);
    }
    fn_801B7B04(0);
}

extern "C" {

extern int g_ccClass;
extern int g_gameMode;

extern const float lbl_806D9AF8;
extern void MemoryManager_TimedFree(void *p);
extern void SetScreenBrightness(float level);

extern unsigned char *SyncSlot_GetRecv(void);

extern void fn_80120A08(int id);
extern void fn_80169C44(void);
extern void fn_801A1678(void);
extern void fn_801B7B04(int arg);

}
clFlowClass::~clFlowClass() {
    clFlowClass *self = this;
        fn_801B7B04(1);
        if (input()) {
            FlowInput *in = input();
            in->enabled = 0;
            in->held = 0;
            in->edge = 0;
        }
        SetScreenBrightness(lbl_806D9AF8);
        fn_80169C44();
        fn_80120A08(0x166F);
        fn_80120A08(0x1AE0);
        fn_80120A08(0x1ADF);
        fn_80120A08(0x1ADE);
        fn_80120A08(0x1666);
        fn_80120A08(0x1B12);
        fn_80120A08(0x1B13);
        Sprite_Destroy(self->sprites[2], 1);
        Sprite_Destroy(self->sprites[1], 1);
        Sprite_Destroy(self->sprites[0], 1);
        Sprite_Destroy(self->indicator, 1);
        fn_801A1678();
        if (g_gameMode == 2) {
            g_ccClass = (SyncSlot_GetRecv()[1] >> 1) & 3;
        }
}

int clFlowClass::Update() {
    clFlowClass *self = this;
    unsigned char *data = classAnimationPool;
    RumbleUpdate();
    if (self->advance) { ++self->state; self->advance=0; }
    self->elapsed += lbl_806D9B08;
    switch (self->state) {
    case 0: {
        if (!self->sprites[1] && self->elapsed > lbl_806D9B0C) {
            self->sprites[1] = new ClassSprite(4,1,0);
            if (g_gameMode == 2) self->sprites[1]->pos(lbl_806D9AFC,lbl_806D9B10);
            else self->sprites[1]->pos(lbl_806D9AFC,lbl_806D9B14);
        }
        if (!self->sprites[2] && self->elapsed > lbl_806D9B18) {
            self->sprites[2] = new ClassSprite(9,1,0);
            if (g_gameMode == 2) self->sprites[2]->pos(lbl_806D9B1C,lbl_806D9B10);
            else self->sprites[2]->pos(lbl_806D9B1C,lbl_806D9B14);
        }
        if (g_gameMode != 2 && !self->indicatorStarted && self->elapsed > lbl_806D9B20) {
            self->indicatorStarted=1;
            self->indicator = new ClassSprite(0x14,(unsigned char)1,lbl_806D9B24,lbl_806D9B28);
        }
        for (int i=0;i<3;++i) {
            ClassAnims anims = *(const ClassAnims*)(data+0x3FC);
            if (self->sprites[i] && !Sprite_AdvanceAnim(self->sprites[i],lbl_806D9B2C)) {
                Sprite_SetupAnim(self->sprites[i],anims.ids[i],1,0);
                fn_8019FF6C(self->sprites[i],1);
                --self->count;
            }
        }
        if (self->extra && !Sprite_AdvanceAnim(self->extra,lbl_806D9B2C)) {
            Sprite_SetupAnim(self->extra,0x46,1,0); fn_8019FF6C(self->extra,1); --self->count;
        }
        if (self->count==0 && self->elapsed > lbl_806D9B30) {
            lbl_806D184C=1; lbl_806D184D=0;
            SetScreenBrightness(self->brightness);
            self->left = new ClassSprite(0x9C,(unsigned char)1,lbl_806D9B34,lbl_806D9B38);
            self->right = new ClassSprite(0x9C,(unsigned char)1,lbl_806D9B3C,lbl_806D9B38);
            fn_801699D8(0,1); if (g_gameMode != 2) fn_801699D8(1,1);
            self->advance=1;
        }
        break;
    }
    case 1: {
        ClassPlayer *player = InputMgr_GetPlayer(GetInputManager(),0);
        if (g_gameMode != 2) {
            if (player->Check(0x400)) {
                SetRumbleMode(1,1,1);
                if (!self->mode) {
                    self->sprites[1]->pos(lbl_806D9B40,lbl_806D9B14);
                    self->sprites[2]->pos(lbl_806D9B44,lbl_806D9B14);
                    g_gameMode=1; fn_801B8874(0x1AE0); fn_801B89C8(0); self->mode=1;
                    if (self->selection==0) {
                        Sprite_SetupAnim(self->sprites[0],0x14D,1,0); fn_8019FF6C(self->sprites[0],1);
                        Sprite_SetupAnim(self->sprites[1],2,1,0); fn_8019FF6C(self->sprites[1],1);
                        fn_801B7CAC(); self->selection=1;
                    }
                }
            } else if (self->mode==1) {
                self->sprites[0]->pos(lbl_806D9B48,lbl_806D9B14);
                self->sprites[1]->pos(lbl_806D9AFC,lbl_806D9B14);
                self->sprites[2]->pos(lbl_806D9B1C,lbl_806D9B14);
                g_gameMode=0; fn_801B8874(0x1ADF); fn_801B89C8(0); self->mode=0;
            }
        }
        if (input()) {
            int old = self->selection;
            FlowInput *in = input();
            self->selection += in->delta;
            if (self->mode) {
                if (self->selection>2) self->selection=2;
                if (self->selection<1) self->selection=1;
            } else {
                if (self->selection>2) self->selection=2;
                if (self->selection<0) self->selection=0;
            }
            if (self->selection==2) self->selectedSpecial=1; else self->selectedSpecial=0;
            if (old != self->selection) {
                ClassAnims leave = *(const ClassAnims*)(data+0x408);
                ClassAnims enter = *(const ClassAnims*)(data+0x414);
                Sprite_SetupAnim(self->sprites[old],leave.ids[old],1,0); fn_8019FF6C(self->sprites[old],1);
                Sprite_SetupAnim(self->sprites[self->selection],enter.ids[self->selection],1,0); fn_8019FF6C(self->sprites[self->selection],1);
                fn_801B7CAC();
            }
        }
        if (!self->mode) {
            self->left->pos(lbl_806D9B34,lbl_806D9B38);
            if (self->selection==0) {
                if (self->left) self->left->scale(lbl_806D9B08,lbl_806D9B08);
                if (self->right) self->right->scale(lbl_806D9AF4,lbl_806D9B08);
            } else if (self->selection==1) {
                if (self->left) self->left->scale(lbl_806D9AF8,lbl_806D9B08);
                if (self->right) self->right->scale(lbl_806D9B08,lbl_806D9B08);
            } else if (self->selection==2) {
                if (self->left) self->left->scale(lbl_806D9AF4,lbl_806D9B08);
                if (self->right) self->right->scale(lbl_806D9AF8,lbl_806D9B08);
            }
        } else {
            self->left->pos(lbl_806D9AFC,lbl_806D9B38);
            self->right->scale(lbl_806D9AF4,lbl_806D9AF4);
            if (self->selection==1) { if (self->left) self->left->scale(lbl_806D9B08,lbl_806D9B08); }
            else if (self->selection==2) { if (self->left) self->left->scale(lbl_806D9AF8,lbl_806D9B08); }
        }
        if (self->left) Sprite_AdvanceAnim(self->left,lbl_806D9B2C);
        if (self->right) Sprite_AdvanceAnim(self->right,lbl_806D9B2C);
        for (int i=0;i<3;++i) if (self->sprites[i]) Sprite_AdvanceAnim(self->sprites[i],lbl_806D9B2C);
        if (self->indicator) Sprite_AdvanceAnim(self->indicator,lbl_806D9B2C);
        if (self->extra) Sprite_AdvanceAnim(self->extra,lbl_806D9B2C);
        if (fn_801C1F88(self) != -1) {
            Sprite_Destroy(self->left,1); Sprite_Destroy(self->right,1);
            self->left=0; self->right=0; self->advance=1;
        }
        break;
    }
    case 2:
        for (int i=0;i<3;++i) {
            if (self->sprites[i] && !Sprite_AdvanceAnim(self->sprites[i],lbl_806D9B2C) && i != self->selection) {
                Sprite_Destroy(self->sprites[i],1); self->sprites[i]=0; --self->count;
            }
        }
        if (self->extra && !Sprite_AdvanceAnim(self->extra,lbl_806D9B2C)) { Sprite_Destroy(self->extra,1); self->extra=0; --self->count; }
        if (self->count==0) self->advance=1;
        break;
    case 3: {
        ClassAnims anims = *(const ClassAnims*)(data+0x420);
        Sprite_SetupAnim(self->sprites[self->selection],anims.ids[self->selection],1,0);
        Sprite_AdvanceAnim(self->sprites[self->selection],lbl_806D9B2C);
        fn_801B87D8(); fn_801699D8(0,0); fn_801699D8(1,0); self->advance=1;
        break;
    }
    case 4:
        if (!Sprite_AdvanceAnim(self->sprites[self->selection],lbl_806D9B2C) && !fn_801B87B0()) return self->result;
        break;
    case 10:
        for (int i=0;i<3;++i) {
            if (self->sprites[i] && !Sprite_AdvanceAnim(self->sprites[i],lbl_806D9B2C)) {
                ClassAnims anims = *(const ClassAnims*)(data+0x42C);
                Sprite_SetupAnim(self->sprites[i],anims.ids[i],1,0); fn_8019FF6C(self->sprites[i],1);
                SetSyncTarget(12); self->fading=1; StartScreenFade(lbl_806D9AF4);
            }
        }
        if (self->extra) Sprite_AdvanceAnim(self->extra,lbl_806D9B2C);
        if (g_currentSceneState==12) {
            SetSyncTarget(12);
            if (IsSyncReached()) { g_ccClass=(SyncSlot_GetRecv()[1] >> 1) & 3; self->result=13; }
            if (self->result != 12) {
                Sprite_Destroy(self->extra,1); self->extra=0;
                self->selection=g_ccClass; self->advance=1; self->ticks=0; self->fading=0;
                fn_801B7B04(0);
                for (int i=0;i<3;++i) {
                    ClassAnims chosen = *(const ClassAnims*)(data+0x438);
                    ClassAnims other = *(const ClassAnims*)(data+0x444);
                    if (self->sprites[i]) {
                        if (i==self->selection) {
                            Sprite_SetupAnim(self->sprites[i],chosen.ids[i],1,0);
                            self->startX=self->sprites[i]->x; self->startY=self->sprites[i]->y;
                        } else Sprite_SetupAnim(self->sprites[i],other.ids[i],1,0);
                    }
                }
            }
        }
        break;
    case 11:
        for (int i=0;i<3;++i) {
            if (self->sprites[i] && !Sprite_AdvanceAnim(self->sprites[i],lbl_806D9B2C)) {
                if (i==self->selection) {
                    ClassAnims anims = *(const ClassAnims*)(data+0x450);
                    Sprite_SetupAnim(self->sprites[i],anims.ids[i],1,0); fn_8019FF6C(self->sprites[i],1);
                } else { Sprite_Destroy(self->sprites[i],1); self->sprites[i]=0; }
            }
        }
        ++self->ticks;
        if (self->ticks>=20 && self->ticks<=39) {
            self->sprites[self->selection]->x = interpolate(self->startX,lbl_806D9AFC,self->ticks-20,lbl_806D9B4C);
            self->sprites[self->selection]->y = interpolate(self->startY,lbl_806D9B10,self->ticks-20,lbl_806D9B4C);
        }
        if (self->ticks>110) {
            ClassAnims anims = *(const ClassAnims*)(data+0x45C);
            Sprite_SetupAnim(self->sprites[self->selection],anims.ids[self->selection],1,0);
            self->advance=1; self->count=1; fn_801B87D8();
        }
        break;
    case 12:
        if (self->sprites[self->selection] && !Sprite_AdvanceAnim(self->sprites[self->selection],lbl_806D9B2C)) {
            Sprite_Destroy(self->sprites[self->selection],1); self->sprites[self->selection]=0; --self->count;
        }
        if (self->count==0) return self->result;
        break;
    }
    return -1;
}


extern "C" {
extern void fn_801A0004(ClassSprite *label);
extern void fn_801A1174(int id, int a, int b, int c, int d);
extern void fn_801A1128(float x, float y);
extern void fn_801A0DF0(void);

}
void clFlowClass::Draw() {
    clFlowClass *self = this;
    if (self->extra != 0) {
        fn_801A0004(self->extra);
    }
    if (self->indicatorStarted != 0) {
        fn_801A1174(0x166F, 5, 0, 0, 0);
        fn_801A1128(320.0f, 378.0f);
        fn_801A0DF0();
        if (self->indicator != 0) {
            fn_801A0004(self->indicator);
        }
    }
    if (self->mode) {
        if (self->selection != 1 && self->sprites[1] != 0) {
            fn_801A0004(self->sprites[1]);
        }
        if (self->selection != 2 && self->sprites[2] != 0) {
            fn_801A0004(self->sprites[2]);
        }
    } else {
        if (self->selection != 0 && self->sprites[0] != 0) {
            fn_801A0004(self->sprites[0]);
        }
        if (self->selection != 1 && self->sprites[1] != 0) {
            fn_801A0004(self->sprites[1]);
        }
        if (self->selection != 2 && self->sprites[2] != 0) {
            fn_801A0004(self->sprites[2]);
        }
    }
    if (self->sprites[self->selection] != 0) {
        fn_801A0004(self->sprites[self->selection]);
    }
    if (self->left != 0) {
        fn_801A0004(self->left);
    }
    if (self->right != 0) {
        fn_801A0004(self->right);
    }
    if (self->extra != 0) {
        SetPos(self->extra, 320.0f, 374.0f);
    }
}
