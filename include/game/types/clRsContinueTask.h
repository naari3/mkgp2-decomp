#ifndef GAME_TYPES_CLRSCONTINUETASK_H
#define GAME_TYPES_CLRSCONTINUETASK_H
#include "game/ContinueScene_private.h"
#include "game/types/clMnCardClasses.h"

// The destructor owns the vtable in ContinueScene.cpp. Draw and Update
// retain their independently matched compiler settings in separate units.
struct clRsContinueTask : clMnCardT0Interface {
    virtual ~clRsContinueTask();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    int retries;
    int coins;
    unsigned char noCredit;
    unsigned char started;
    unsigned char align32[2];
    CoinCounter *counter;
    CoinPopupDetail *detail;
    CoinPromptHolder prompt;
    clRsContinueTask(int id);
    void Select();
    void Confirm();
    void Cancel();
};
#endif
