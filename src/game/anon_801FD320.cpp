/*
 * FlowScene base and the card-eject result task @ 0x801FD320..0x801FD924.
 */

#include "game/FlowScene.h"

#include "game/types/FlowController.h"

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

#include "game/types/CardEjectTask.h"

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


__declspec(section ".ctors") static void (*const cardEjectInitRef)(void) = fn_801FD320;
