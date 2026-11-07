#ifndef GAME_YESNOBUTTONR_MATCH_PRIVATE_H
#define GAME_YESNOBUTTONR_MATCH_PRIVATE_H

#include "game/YesNoButtonDrawPrivate.h"

/* Keep the undefined virtual key first so this drawing TU owns no vtable. */
struct YesNoButtonR : YesNoButton {
    virtual void _key3();
    TextManager *texts;
    bool field70;
    YesNoButtonR(int kind_, int layer_);
    ~YesNoButtonR();
    virtual void Update();
    virtual void Draw();
    void DrawLabel();
};

#endif
