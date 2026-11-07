#include "game/singleton.h"
/* GameModeBase @ 0x800A07EC..0x800A0950: native text and EH exact. */
#include "game/GameModeBase_private.h"

struct Scene {
    virtual void f0(int);
    virtual int f1();
    virtual void f2();
};

struct GameModeBase {
    void *vtable;
    Scene *scene;
};

extern "C" {
extern void CardRegister_Session_Tick(void);
extern void fn_801A1280(void);
extern void RankLog_UpdatePerFrame(void *);
extern void *lbl_806D10A0;
extern int  g_objCollChecker;
extern void Backup_PublishShadowCopy_Inline(void);
extern void fn_80190660(void);
extern void HSD_FObjForceLinearInterp(int);
extern void *dtor_8002CDF4(void *self, short freeFlag);  /* ObjectBase_Dtor */
extern void  MemoryManager_TimedFree(void *self);                  /* MemoryManager_TimedFree */
extern GameModePlayerData g_playerData;
extern void *g_GameModeBaseVtable[5];
}

extern Scene *lbl_806D10AC;

#pragma exceptions on

/* Same singleton accessor as TitleNameHud and ContinueScene. */
static inline void *GetRankLog() {
    return SINGLETON_INSTANCE(lbl_806D10A0);
}

extern "C" int GameModeBase_FrameUpdate(GameModeBase *self) {
    int ret;
    void *dat;
    if (self->scene == 0) {
        return 0;
    }
    CardRegister_Session_Tick();
    fn_801A1280();
    ret = self->scene->f1();
    dat = GetRankLog();
    if (dat != 0) {
        RankLog_UpdatePerFrame(dat);
    }
    return ret;
}

extern "C" GameModeBase *GameModeBase_Dtor(GameModeBase *self, short freeFlag) {
    if (self != 0) {
        self->vtable = g_GameModeBaseVtable;
        if (self->scene != 0) {
            self->scene->f0(1);
        }
        self->scene = 0;
        g_objCollChecker = 0;
        fn_80190660();
        Backup_PublishShadowCopy_Inline();
        if (lbl_806D10AC != 0) {
            lbl_806D10AC->f0(1);
        }
        lbl_806D10AC = 0;
        HSD_FObjForceLinearInterp(0);
        g_playerData.DecrementRemaining();
        dtor_8002CDF4(self, 0);
        if (freeFlag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
