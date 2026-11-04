#include "game/FlowScene.h"
struct CardOwnerBase {
    virtual void _key();
    unsigned char done;
    CardOwnerBase() : done(0) {}
    ~CardOwnerBase();
};
extern "C" {
extern int lbl_806D19B8, lbl_806D0108, lbl_806D00C8;
void SetSyncTarget(int); void *fn_801F8E58();
void fn_80207DA8(int); void fn_80204130(int); void PreloadResource(int);
char *fn_80271340(void *, int, void *, void *, int);
}
struct ReadTask : FlowTask {
    VHolder<FlowSceneList> seq;
    VHolder<FlowFaderI> fade;
    int state, result;
    virtual void _key2();
    ReadTask() : FlowTask(0), seq(new SceneListImpl), fade(new FlowFaderI), state(0), result(0) {
        PreloadResource(0x1ECD); PreloadResource(0x72F); PreloadResource(0x734); PreloadResource(0x730);
        fade.p->Set(0, 0, 1);
    }
};
struct CardOwner : CardOwnerBase {
    VHolder<FlowSceneList> seq;
    int step;
    virtual void _key2();
    CardOwner() : seq(new SceneListImpl), step(0) {
        SetSyncTarget(9); lbl_806D19B8 = 0;
        fn_801F8E58(); fn_80207DA8(6); fn_80204130(7);
        FlowSceneList *list = seq.p;
        fn_801F4DF0(list, new ReadTask, 0);
        FlowTask *task = fn_801F4DC0(seq.p, 0);
        if (task) {
            int n = step;
            *(int *)(fn_80271340(task, 0, &lbl_806D0108, &lbl_806D00C8, 0) + 0x1C) = n;
        }
    }
};
extern "C" CardOwner *fn_801FA024() { return new CardOwner; }
