#ifndef GAME_TYPES_TITLENAMEHUD_H
#define GAME_TYPES_TITLENAMEHUD_H

#include "game/types/HudPart.h"

/* Declare before including (each user already does): FlowFaderF, VHolder, name */

struct TitleNameHud : HudPart {
    int layer;
    int sprites[24];
    int count;
    int state;
    int title;
    int field78;
    int field7C;
    VHolder<FlowFaderF> slide;
    VHolder<FlowFaderF> scale;
    char name[0x200];
    float xs[22];
    TitleNameHud(int layer_);
    ~TitleNameHud();
    void Update();
    void Draw();
    void SetDelay(int n);
    virtual void _key();
};

#endif /* GAME_TYPES_TITLENAMEHUD_H */
