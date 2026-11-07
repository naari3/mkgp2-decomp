#ifndef GAME_COURSE_MODE_INIT_PRIVATE_H
#define GAME_COURSE_MODE_INIT_PRIVATE_H
#include "game/MenuModeLane_private.h"
#include "game/FlowScene.h"
#include "game/singleton.h"
struct CourseSprite {
    char pad0[12]; float x,y; char tail[0x30-0x14];
    CourseSprite(int, int, int);
    CourseSprite(int, int, float, float);
    void SetPosition(float px, float py) { x=px; y=py; }
};
struct CourseSharedUI {
    CourseSprite *top[3];
    CourseSprite *bottom[4];
    int handles[5];
};
struct CourseClassTask { char data[0x58]; CourseClassTask(); };
struct CourseCupTask { char data[0x158]; CourseCupTask(); };
struct CourseRoundTask { char data[0x16C]; CourseRoundTask(); };
struct CourseFrameTask { char data[0x1D8]; CourseFrameTask(); };
struct CourseEntryTask { char data[0x14]; CourseEntryTask(); };
struct CourseModeInit : GameModeBase {
    unsigned char done; char pad5[3]; void *task;
    CourseModeInit();
};
extern "C" {
extern CourseSharedUI lbl_80679280;
extern void *lbl_8049A734[];
extern unsigned char lbl_806D17F0, lbl_806D17F1, lbl_806D17F2, lbl_806D17F3, lbl_806D17F4;
extern int lbl_806CFD60, lbl_806D17F8, lbl_806D17FC, lbl_806D1800, lbl_806D1804, lbl_806D1808, lbl_806D180C, lbl_806D1810;
extern unsigned char lbl_806D1818, lbl_806D1819, lbl_806D184F, lbl_806D1850, lbl_806D1858;
extern int lbl_806D1820;
extern float lbl_806D1854, lbl_806D1848;
extern unsigned char lbl_806D184C, lbl_806D184D;
extern CourseSprite *lbl_806D1840, *lbl_806D1844;
extern const float lbl_806D9890, lbl_806D98B8, lbl_806D98E0, lbl_806D9948, lbl_806D994C, lbl_806D9950;
extern const float lbl_806D9954, lbl_806D9958, lbl_806D995C, lbl_806D991C;

void fn_8002CFB8(int,int,int,int);
void fn_801DAE54(); void fn_80121210(); void clRom_PurgeAll();
void ProcessSystemTick(int); void PcbSlot_ResetScratchAreas(); void CommBroadcast_ClearTable(); void SyncSlot_Reset();
void PreloadResource(int); void SetScreenBrightness(float);
int fn_801A0310(CourseSprite *, int);
void *StrPcb_GetInstance(); void StrPcb_ForceRun_Neutral(void *); void StrPcb_ResetCommands_Neutral(void *, int);
int CountPeersWithRole(int); void SetLocalPcbRole(int); void SetTimerModeEnabled(int);
unsigned char fn_801D5A68(void *);
void fn_801B7CD0(int);
char *fn_801DAEC0();
}
extern "C" void Sprite_CreateWithParams(CourseSprite *, int, int, float, float, float, float, float, float);
inline CourseSprite::CourseSprite(int a, int b, float x, float y) {
    float scale = lbl_806D98E0;
    float zero = lbl_806D9890;
    Sprite_CreateWithParams(this, a, b, x, y, scale, scale, zero, zero);
}
inline void CourseSetFlag(char *flag) { *flag = 1; }
struct CourseInputImpl {
    void *vt; unsigned char enabled, flag5, flag6; int fields[8];
};
extern "C" { extern void *lbl_803FDF28[], *lbl_803FDF40[]; void *Alloc(unsigned long); }
inline void CourseEnsureInput() {
    if (SINGLETON_INSTANCE(g_pInputState) == 0) {
        CourseInputImpl *p = (CourseInputImpl *)Alloc(0x28);
        if (p) {
            p->vt = lbl_803FDF28;
            g_pInputState = (InputState *)p;
            p->vt = lbl_803FDF40;
            p->enabled=0; p->flag5=1; p->flag6=1;
            p->fields[0]=0; p->fields[1]=0; p->fields[2]=0; p->fields[3]=0;
            p->fields[4]=0; p->fields[5]=0; p->fields[6]=0; p->fields[7]=0;
        }
    }
    StrPcb_ForceRun_Neutral(StrPcb_GetInstance());
    StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
}
#endif

