#ifndef CARD_MODE_ROOT_UNLOCK_PRIVATE_H
#define CARD_MODE_ROOT_UNLOCK_PRIVATE_H
/* Private declaration view: existing virtual overrides precede inline dtors
 * to leave vtable ownership with the original defining translation units.
 * 0x8020C974..0x8020D1C0: card mode root scene. Runs the card attract /
 * entry / menu tasks in turn and writes the chosen race settings back to the
 * globals when it goes away.
 */

#include "game/FlowScene.h"

#pragma auto_inline off

#include "game/types/SceneBase.h"

#include "game/types/FlowMgrInfo.h"

#include "game/types/CardConfig.h"

#include "game/types/DispFlags.h"

/* Menu mode base (vtable MenuModeBase_vtable_804E549C, ctor fn_801F5B54). */
struct MenuModeBase : SceneBase {
    int f08;
    int f0C;
    int f10;
    int f14;
    char pad18[0x28 - 0x18];
    int f28;
    int pad2C;
    int f30[3];
    int chara;
    int pad40;
    int mode;
    int f48;
    char pad4C[0x5C - 0x4C];
    MenuModeBase();
    virtual void Destroy();
    ~MenuModeBase() {}
};

/* Holds the scene list at +4 (vtable FlowSceneHost_vtable_804EC190). */
struct FlowSceneHost {
    virtual ~FlowSceneHost();
    VHolder<FlowSceneList> list;
    FlowSceneHost();
    void DrawScenes();
    bool HasEjectTask();
    void UpdateScenes();
};

#include "game/types/CardMenuRoot.h"

#include "game/types/InputImpl.h"

extern "C" {
extern int g_localPcbRole;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_roundIndex;
extern int g_ccClass;
extern unsigned char lbl_806D12B0;
extern unsigned char lbl_806D1264[3];
extern int lbl_806D1A30;
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
void *Alloc(unsigned long size);
FlowMgrInfo *fn_801FE404(void);
void fn_801FE584(FlowMgrInfo *mgr);
CardConfig *fn_8024F588(FlowMgrInfo *mgr);
DispFlags *fn_801DAEC0(void);
void fn_801DABFC(void);
void fn_801DAE54(void);
void fn_8011FAB8(void);
void fn_8011F86C(void);
void fn_80121210(void);
void fn_80218F1C(void);
void ServiceMode_UpdateScheduleGate(void);
void SetLocalPcbRole(int role);
void *StrPcb_GetInstance(void);
void StrPcb_ForceRun_Neutral(void *pcb);
void StrPcb_ResetCommands_Neutral(void *pcb, int mode);
void Frame_PostDrawOverlay(void);
void Frame_UpdatePerFrameState(void);
void DemoFlow_ResetTwoFlags(void);
void OperationClock_Commit(void);
void RaceFlow_ResetState_FullColdInit(void);
SceneBase *fn_8014F6A4(void);
CardMenuRoot *fn_8020C7F4(void);
void CGameCoin_ProcessInput(InputState *in);
void SetReverseRoundFlag(int flag);
void clRom_DumpListOverlay(void);
unsigned char fn_8019083C(int slot);
void fn_801909A4(int slot);
void ClSound_PlayBgmStream(int slot, int id);
int fn_801932F8(void);
void clStream_setVolume(int slot, int vol);
}

static inline void CreateInputState() {
    InputImpl *p = (InputImpl *)Alloc(0x28);
    if (p != 0) {
        p->vt = lbl_803FDF28;
        g_pInputState = (InputState *)p;
        p->vt = lbl_803FDF40;
        p->enabled = 0;
        p->flag5 = 1;
        p->flag6 = 1;
        p->fields[0] = 0;
        p->fields[1] = 0;
        p->fields[2] = 0;
        p->fields[3] = 0;
        p->fields[4] = 0;
        p->fields[5] = 0;
        p->fields[6] = 0;
        p->fields[7] = 0;
    }
}

struct CardModeRoot : MenuModeBase, FlowSceneHost {
    SceneBase *task;
    int state;
    CardModeRoot();
    virtual void Destroy();
    ~CardModeRoot();
    virtual void Update();
    virtual void Draw();
    void OnTaskDone(int st);
    void StartTask(int st);
};


#endif
