#include "game/FlowScene.h"
#include "game/types/clSceneInterface.h"

extern "C" {
extern int lbl_806D19B8, lbl_806D0108, lbl_806D00C8;
void SetSyncTarget(int); void *fn_801F8E58();
void fn_80207DA8(int); void fn_80204130(int); void PreloadResource(int);
char *fn_80271340(void *, int, void *, void *, int);
void fn_802040B0(); void fn_80207D38(); void fn_801F8E54();
void fn_8011FAB8(); void fn_80203BEC(); void fn_80207810();
void HSD_StateInvalidate(int); void fn_80203C24(); void fn_80207848();
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
struct clMnCard : clSceneInterface {
    virtual ~clMnCard();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    VHolder<FlowSceneList> seq;
    int step;
    clMnCard() : seq(new SceneListImpl), step(0) {
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

clMnCard::~clMnCard() {
    fn_801F4D3C(seq.p);
    fn_802040B0(); fn_80207D38(); fn_801F8E54();
}
extern "C" clMnCard *fn_801FA024() { return new clMnCard; }
void clMnCard::Destroy() { delete this; }
void clMnCard::Update() {
    if (done == 0) {
        FlowTask *p = fn_801F4DC0(seq.p, 0);
        if (p != 0) {
            step = *(int *)(fn_80271340(p, 0, &lbl_806D0108, &lbl_806D00C8, 0) + 0x1C);
        }
        if (seq.p->entries.count <= 0) done = 1;
        seq.p->Update();
        fn_80207848(); fn_80203C24();
    }
}
void clMnCard::Draw() {
    if (done == 0) {
        seq.p->Draw();
        fn_80207810(); fn_80203BEC(); fn_8011FAB8(); HSD_StateInvalidate(-1);
    }
}
