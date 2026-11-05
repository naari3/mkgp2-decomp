#ifndef GAME_RACE_HUD_TRANSITION_PRIVATE_H
#define GAME_RACE_HUD_TRANSITION_PRIVATE_H
#include "game/MenuModeLane_private.h"
#include "game/HudFlowPrivate.h"

struct RaceHudTransition {
    void *vptr;
    int field4;
    SceneBase *scene;
    MenuDisplay *display;
};
extern "C" {
void fn_801A1280();
void fn_8011F994(int);
void fn_8012094C();
void fn_801A0B70(int);
void fn_801F8E54();
void fn_8020F290();
}
#endif
