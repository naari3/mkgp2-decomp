/*
 * 0x8020C650..0x8020C974: card menu root scene. Picks the battle or the grand
 * prix menu, runs it, then copies the chosen settings back out.
 */

#include "game/FlowScene.h"

#include "game/types/clMnSystem01.h"

struct FlowMgrInfo {
    char pad000[0x164];
    int chara;
    int pad168;
    int mode;
    int f170;
    int f174;
    int f178;
    int f17C;
    int f180;
    int pad184;
    int f188[3];
};

extern "C" {
extern int g_localPcbRole;
FlowMgrInfo *fn_801FE404(void);
void fn_802029EC(void);
void fn_8011FAB8(void);
void fn_801F9AAC(void);
void fn_801F9B64(void);
void fn_801F9CA8(void);
void fn_801F9DA4(void);
unsigned char PcbSyncTable_MyFlagIsSet(void);
clSceneInterface *fn_8020B994(void);
clSceneInterface *fn_8020C254(void);
}

clMnSystem01::clMnSystem01() : task(0) {
    fn_801F9B64();
    fn_801F9DA4();
    if (g_localPcbRole > 1 || PcbSyncTable_MyFlagIsSet() > 1) {
        mode = 2;
        fn_801FE404()->mode = mode;
    } else {
        mode = 0;
        fn_801FE404()->mode = mode;
    }
    if (fn_801FE404()->mode == 2) {
        task = fn_8020B994();
    } else {
        task = fn_8020C254();
    }
}

clMnSystem01::~clMnSystem01() {
    fn_801F9CA8();
    fn_801F9AAC();
}

extern "C" clMnSystem01 *fn_8020C7F4(void) {
    return new clMnSystem01;
}

void clMnSystem01::Destroy() {
    delete this;
}

void clMnSystem01::Update() {
    if (task != 0) {
        if (!task->done) {
            task->Update();
        } else {
            int i;
            mode = fn_801FE404()->mode;
            chara = fn_801FE404()->chara;
            f08 = fn_801FE404()->f174;
            f0C = fn_801FE404()->f178;
            f10 = fn_801FE404()->f180;
            f14 = fn_801FE404()->f17C;
            f48 = fn_801FE404()->f170;
            for (i = 0; i < 3; i++) {
                f30[i] = fn_801FE404()->f188[i];
            }
            delete task;
            task = 0;
            done = true;
        }
    }
}

void clMnSystem01::Draw() {
    fn_802029EC();
    if (task != 0) {
        task->Draw();
    }
    fn_8011FAB8();
}
