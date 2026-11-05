#include "game/RaceDigitGapPrivate.h"
AdvanceCard::AdvanceCard(int layer_) : layer(layer_),sprite(0),state(-1),enabled(1),
    slide(new FlowFaderF(lbl_806DBF18)),scale(new FlowFaderF(lbl_806DBF18)) {
    PreloadResource(0xC29);
    slide.p->Set(lbl_806DBF24,lbl_806DBF18,7);
    scale.p->Set(lbl_806DBF1C,lbl_806DBF1C,1);
    int resource=0xC29;
    int index=GetDisplayBufferIndex();
    if(index>=0 && index<=3) resource=index+0xC29;
    else state=5;
    if(ServiceEnable_Get() && !ServiceValue_Get() && Sci2Card_GetByteFlag1224()) enabled=0;
    ResCtrl ctrl;
    ctrl.resId=resource;
    sprite=SpriteHandle_CreateDefault(&ctrl,layer);
    SpriteHandle_SetActiveFlag(sprite,0);
    SpriteHandle_RecomputeCull(sprite);
    if(g_gameMode!=2) state=5;
}
