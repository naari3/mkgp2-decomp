/*
 * 0x8020C650..0x8020C974: card menu root scene. Picks the battle or the grand
 * prix menu, runs it, then copies the chosen settings back out.
 */

#include "game/FlowScene.h"

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    bool done;
    SceneBase() : done(false) {}
};

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

/* Menu mode base (vtable lbl_804E549C, ctor fn_801F5B54). */
struct MenuModeBase : SceneBase {
    int f08;
    int f0C;
    int f10;
    int f14;
    char pad18[0x30 - 0x18];
    int f30[3];
    int chara;
    int pad40;
    int mode;
    int f48;
    char pad4C[0x5C - 0x4C];
    MenuModeBase();
    ~MenuModeBase() {}
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
SceneBase *fn_8020B994(void);
SceneBase *fn_8020C254(void);
}

struct CardMenuRoot : MenuModeBase {
    SceneBase *task;
    CardMenuRoot();
    ~CardMenuRoot();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
};

void CardMenuRoot::Draw() {
    fn_802029EC();
    if (task != 0) {
        task->Draw();
    }
    fn_8011FAB8();
}

void CardMenuRoot::Update() {
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

void CardMenuRoot::Destroy() {
    delete this;
}

extern "C" CardMenuRoot *fn_8020C7F4(void) {
    return new CardMenuRoot;
}

CardMenuRoot::~CardMenuRoot() {
    fn_801F9CA8();
    fn_801F9AAC();
}

CardMenuRoot::CardMenuRoot() : task(0) {
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
