/* Target-observed owner/result views; no live Ghidra type lookup performed. */
#include "game/FlowScene.h"

struct SceneRoleUpdateView {
    void *vtable;
    unsigned char done;
    unsigned char pad05[3];
    FlowSceneList *list;
    int result;
    unsigned char missing;
};

struct SceneRoleResult {
    unsigned char pad00[0x24];
    int value;
};

struct ItemDisplay;
struct RankLog;
extern "C" {
extern unsigned char lbl_806D0988[8];
extern unsigned char lbl_806D0980[8];
extern RankLog *lbl_806D10A0;
extern unsigned char lbl_806D17F0;
SceneRoleResult *fn_80271340(void *, int, void *, void *, int);
ItemDisplay *ItemDisplay_GetOrCreate(void);
void fn_8020AAD4(ItemDisplay *);
void TitleStats_ResetRaceStagingState(RankLog *);
void RankLog_Reset(RankLog *);
}

static inline RankLog *RoleRankLog() {
    return lbl_806D10A0 == 0 ? (RankLog *)0 : lbl_806D10A0;
}

extern "C" void fn_8024D02C(SceneRoleUpdateView *self) {
    if (!self->done) {
        FlowTask *task = fn_801F4DC0(self->list, 0);
        if (task) {
            self->result = fn_80271340(task, 0, lbl_806D0988, lbl_806D0980, 0)->value;
        } else {
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            self->missing = 1;
        }
        if (self->list->entries.count <= 0) {
            self->done = 1;
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            RankLog *log = RoleRankLog();
            if (log) {
                if (lbl_806D17F0 == 1) {
                    TitleStats_ResetRaceStagingState(log);
                } else {
                    RankLog_Reset(log);
                }
            }
        }
        self->list->Update();
    }
}
