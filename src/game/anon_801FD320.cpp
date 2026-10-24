/*
 * FlowScene base and the card-eject result task @ 0x801FD320..0x801FD924.
 */

#include "game/FlowScene.h"

struct FlowController {
    void *vt;
    FlowSceneList *owner;
};

extern "C" {
extern int lbl_806D19C8;
extern const int lbl_806DA848;
extern int lbl_806D19D0;
extern int lbl_806D19D4;
extern char lbl_803BFE48[];
extern const float lbl_806DA830;
extern const float lbl_806DA834;
extern const float lbl_806DA838;
extern const float lbl_806DA83C;
extern unsigned char g_playerData[];
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int mode);
void card_eject_init(void);
void fn_801D7610(unsigned char *data, int mode);
}

struct CardEjectTask : FlowTask {
    TextManager *texts;
    CardEjectTask(int id);
    ~CardEjectTask();
    virtual void _key3();
};

extern "C" void fn_801FD320(void) {
    lbl_806D19C8 = lbl_806DA848;
}

FlowScene::~FlowScene() {
    fn_801F4D3C(list.p);
}

FlowScene::FlowScene(int id)
    : FlowTask(id), list(new SceneListImpl), fader(new FlowFaderI), state(0), subState(0),
      timer(0), cursor(0) {
    fn_8020A7CC(fader.p, 0, 0, 1);
}

extern "C" void fn_801FD500(void) {
}

extern "C" void fn_801FD504(CardEjectTask *self) {
    fn_801F8A34(fn_801F8E58(), &self->texts[0], 7);
    fn_801F8A34(fn_801F8E58(), &self->texts[1], 7);
}

extern "C" void fn_801FD550(VObject *obj) {
    delete obj;
}

CardEjectTask::~CardEjectTask() {
    delete[] texts;
}

CardEjectTask::CardEjectTask(int id) : FlowTask(id) {
    char *pool = lbl_803BFE48;
    float x;
    texts = new TextManager[2];
    texts[0].visible = 1;
    if (isJapanese() == 0) {
        x = lbl_806DA830;
        TexMgr_SetTexture(&texts[0], pool + 0x34);
    } else {
        x = lbl_806DA834;
        fn_801F8FCC(&texts[0], 1);
        TexMgr_SetTexture(&texts[0], pool + 0x4C);
        fn_801F8E90(&texts[0]);
    }
    fn_801F93EC(&texts[0], x, lbl_806DA830);
    texts[1].visible = 1;
    if (lbl_806D19D4 == 5) {
        if (isJapanese() == 0) {
            x = lbl_806DA838;
            TexMgr_SetTexture(&texts[1], pool + 0x68);
        } else {
            x = lbl_806DA834;
            fn_801F8FCC(&texts[1], 1);
            TexMgr_SetTexture(&texts[1], pool + 0x7C);
            fn_801F8E90(&texts[1]);
        }
        fn_801F93EC(&texts[1], x, lbl_806DA83C);
    } else {
        if (isJapanese() == 0) {
            x = lbl_806DA830;
            TexMgr_SetTexture(&texts[1], pool + 0x88, lbl_806D19D0);
        } else {
            x = lbl_806DA834;
            fn_801F8FCC(&texts[1], 1);
            TexMgr_SetTexture(&texts[1], pool + 0x9C, lbl_806D19D0);
            fn_801F8E90(&texts[1]);
        }
        fn_801F93EC(&texts[1], x, lbl_806DA83C);
    }
}

extern "C" void fn_801FD800(FlowController *self) {
    self->owner->Draw();
}

static inline bool IsSceneActive(FlowController *self) {
    return fn_801F4DC0(self->owner, 100) != 0;
}

extern "C" void fn_801FD830(FlowController *self) {
    bool active = IsSceneActive(self);
    if (!active) {
        if (lbl_806D19D4 == 7) {
            card_eject_init();
            fn_801D7610(g_playerData, 1);
            FlowSceneList *owner = self->owner;
            fn_801F4DF0(owner, new CardEjectTask(100), 0);
        } else if (lbl_806D19D4 == 6 || lbl_806D19D4 == 5) {
            FlowSceneList *owner = self->owner;
            fn_801F4DF0(owner, new CardEjectTask(100), 0);
        }
    }
    self->owner->Update();
}
