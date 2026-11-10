#ifndef BATTLE_MENU_PRIVATE_H
#define BATTLE_MENU_PRIVATE_H
/*
 * 0x8020B4F8..0x8020BD68: battle menu scene (menuFactory state machine that
 * spawns the card / character select sub scenes and fades the screen).
 */

#include "game/FlowScene.h"

/* Scene object with a done flag (base vtable lbl_803FE0C8). */
#include "game/types/SceneBase.h"

struct FlowMgrInfo {
    char pad000[0x164];
    int chara;
    int pad168;
    int mode;
};

struct PlayerData {
    char pad000[0x1B8];
    unsigned char chara;
};

#include "game/types/SyncSlot.h"

#include "game/types/InputImpl.h"

extern "C" {
extern PlayerData g_playerData;
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
void fn_8011FAB8(void);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
unsigned char Sci2Card_GetByteFlag1224(void);
int Sci2Card_GetUnpackStatusCode(void);
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

struct BattleMenu : SceneBase {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fade;
    SceneBase *task;
    int state;
    bool bgmStarted;
    virtual void _key();
    BattleMenu();
    ~BattleMenu();
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
            DebugPrintf(lbl_803C3544, id, mode, chara);
            switch (id) {
            case 0:
            case 2:
            case 3:
            case 4:
            case 5:
            case 11:
            case 12:
                break;
            case 1:
                task = fn_801FA024();
                break;
            case 7:
                if (fn_8020A788(fade.p) == 0xFF) {
                    fn_8020A7CC(fade.p, 0, 0, 1);
                    task = fn_801F3914(chara, 1);
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
