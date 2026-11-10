#ifndef GAME_RACE_DIGIT_GAP_PRIVATE_H
#define GAME_RACE_DIGIT_GAP_PRIVATE_H
#include "game/RaceDigitsPrivate.h"
extern "C" {
extern int g_totalLaps;
extern const float lbl_806DBF18, lbl_806DBF1C, lbl_806DBF24, lbl_806DBF38;
extern DigitPosition RaceDigitUpdate_rodata_803EF7C0[2][4];
int GetDisplayBufferIndex();
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
unsigned char Sci2Card_GetByteFlag1224();
void fn_80247258(DigitPanel *);
struct LapNode { LapNode *prev,*next; float value; };
void fn_80247C3C(void *, DigitList *, LapNode **,float *);
}
struct AdvanceCard : DigitHudBase {
    int layer;
    void *sprite;
    int state,enabled;
    VHolder<FlowFaderF> slide,scale;
    AdvanceCard(int);
    virtual void Key();
};
static inline void HideDigitPanel(DigitPanel *p) {
    if(p && p->state<5) {
        p->state=5;
        p->slide.p->Set(lbl_806DBF28,lbl_806DBF34,7);
        for(int i=0;i<10;i++) p->tweens[i].Set(lbl_806DBF28,lbl_806DBF34,7);
        p->reveal.p->Set(10,0,20);
    }
}
#endif
