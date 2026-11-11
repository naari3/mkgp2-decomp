#ifndef CLMNSYSTEM01SINGLE_H
#define CLMNSYSTEM01SINGLE_H
/*
 * 0x8020BD68..0x8020C650: grand prix menu scene (same menuFactory state
 * machine as the battle menu, plus the class / cup preselect).
 */

#include "game/FlowScene.h"

/* Scene object with a done flag (base vtable lbl_803FE0C8). */
#include "game/types/SceneBase.h"
#include "game/types/clSceneInterface.h"

struct FlowMgrInfo {
    char pad000[0x164];
    int chara;
    int pad168;
    int mode;
    char pad170[0x197 - 0x170];
    unsigned char ccSelected;
};

struct PlayerData {
    char pad000[0x19D];
    unsigned char hasCard;
    char pad19E[0x1B8 - 0x19E];
    unsigned char chara;
};

#include "game/types/SyncSlot.h"

#include "game/types/InputImpl.h"

extern "C" {
extern PlayerData g_playerData;
extern int g_ccClass;
extern int g_gameMode;
extern int g_cupId;
extern int lbl_806D1A30;
void card_force_backup_now(void);
unsigned char fn_801D5C88(PlayerData *pd, int ccClass);
void fn_801FE3B4(FlowMgrInfo *mgr, int cup);
int fn_80202A5C(int sel);
extern const char lbl_803C3544[];
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
void *Alloc(unsigned long size);
void DebugPrintf(const char *fmt, ...);
SyncSlot *SyncSlot_GetRecv(void);
SyncSlot *SyncSlot_GetHostSend(void);
void ClSound_PlayBgmStream(int slot, int id);
int fn_801932F8(void);
void clStream_setVolume(int slot, int vol);
void fn_80202A24(void);
void fn_80202BCC(void);
void fn_80202C34(int arg);
int fn_80202B48(int cur);
FlowTask *fn_80201A48(int arg);
void fn_802043B8(FlowSceneList *list, int id);
int fn_8020A788(FlowFaderI *t);
void fn_8020A7CC(FlowFaderI *t, int from, int to, short dur);
FlowMgrInfo *fn_801FE404(void);
void fn_801FE554(FlowMgrInfo *mgr, PlayerData *pd);
SceneBase *fn_801FA024(void);
SceneBase *fn_801F3914(int chara, int arg);
SceneBase *fn_8015B6D0(void);
void fn_8011FAB8(void);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
unsigned char Sci2Card_GetByteFlag1224(void);
int Sci2Card_GetUnpackStatusCode(void);
}

static inline void SetCC(bool on) {
    FlowMgrInfo *m = fn_801FE404();
    m->ccSelected = on;
}

static inline void SetMode(int mode) {
    fn_801FE404()->mode = mode;
}

static inline void SetCup(int cup) {
    if (cup < 1) {
        cup = 1;
    }
    while (cup >= 9) {
        cup -= 8;
    }
    fn_801FE3B4(fn_801FE404(), cup);
}

struct clMnSystem01Single : clSceneInterface {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fade;
    SceneBase *task;
    int state;
    int unk18;
    clMnSystem01Single();
    ~clMnSystem01Single();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    void OnTaskDone(int st);
    void Factory() {
        int chara;
        int mode;
        int id = state;
        if (task == 0) {
            mode = fn_801FE404()->mode;
            chara = fn_801FE404()->chara;
            switch (id) {
            case 0:
            case 2:
            case 3:
            case 4:
            case 6:
            case 12:
                break;
            case 1:
                task = fn_801FA024();
                break;
            case 5:
                fn_80202A5C(0xF);
                task = fn_8015B6D0();
                break;
            case 7:
                if (fn_8020A788(fade.p) == 0xFF) {
                    fn_8020A7CC(fade.p, 0, 0, 1);
                    task = fn_801F3914(chara, 0);
                }
                break;
            case 11:
                if (fn_801D5C88(&g_playerData, g_ccClass) == 1) {
                    SetCC(true);
                } else {
                    SetCC(false);
                }
                break;
            default:
                task = 0;
                break;
            }
        }
    }
};


#endif
