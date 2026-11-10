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
