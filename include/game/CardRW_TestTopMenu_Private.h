#ifndef GAME_CARDRW_TESTTOPMENU_PRIVATE_H
#define GAME_CARDRW_TESTTOPMENU_PRIVATE_H
#include "game/TestMenuPage.h"
typedef unsigned char (*CardRWStepFn)(void);
struct CardRWStep {
    CardRWStepFn run;
    const char *name;
};
struct CardRWTestPage {
    char pad_00[8];
    int blink;
    int timer;
    int next;
    int field_14;
    int cursor;
    char pad_1C[0x10];
    int field_2C;
    char pad_30[8];
    int state;
    char pad_3C[0x234];
    void *text;
    void *data;
    int field_278;
    CardRWStepFn step;
    int field_280;
    int error;
};
#endif
