#ifndef GAME_YESNOBUTTONR_DRAW_PRIVATE_H
#define GAME_YESNOBUTTONR_DRAW_PRIVATE_H
#include "game/YesNoButtonDrawPrivate.h"

struct YesNoButtonR : YesNoButton {
    TextManager *texts;
    bool field70;
    YesNoButtonR(int kind_, int layer_);
    ~YesNoButtonR();
    virtual void Update();
    virtual void Draw();
    virtual void _key3();
    void DrawLabel();
};
#endif
