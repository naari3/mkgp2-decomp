#include "game/ClassUpdatePrivate.h"
#include "game/singleton.h"
extern "C" {
extern unsigned char clFlowClass_Update_rodata_8039A5A0[];
extern int g_gameMode, g_currentSceneState, g_ccClass;
extern ClassInputState *g_pInputState;
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
int fn_801C1F88(ClassUpdate*);
void fn_801B87D8();
unsigned char fn_801B87B0();
void SetSyncTarget(int);
void StartScreenFade(float);
unsigned char IsSyncReached();
unsigned char *SyncSlot_GetRecv();
void fn_801B7B04(int);
}
static inline ClassInputState *input() { return SINGLETON_INSTANCE(g_pInputState); }
static inline float interpolate(float start, float end, int frame, float duration) {
    float step = (end-start)/duration;
    return step * frame + start;
}
static inline int selection(const ClassUpdate *self) { return self->selection; }
extern "C" int clFlowClass_Update(ClassUpdate *self) {
    unsigned char *data = clFlowClass_Update_rodata_8039A5A0;
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
            ClassInputState *in = input();
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

