#include "game/RaceDigitGapPrivate.h"
static inline void CopyPosition(DigitPanel *dst, const DigitPosition &src) {
    float x=src.x;
    float y=src.y;
    dst->position.y=y;
    dst->position.x=x;
}
extern "C" void fn_80246988(DigitHud *self,int lap,float input) {
    float value=input;
    LapNode *where;
    int result;
    if(lap>=g_totalLaps) return;
    if(value<0.0f) value=0.0f;
    if(value>599.999f) value=599.999f;
    if(self->field30==lap) {
        ((LapNode *)self->list.first)->value=value;
    } else {
        self->field30=lap;
        where=(LapNode *)self->list.first;
        fn_80247C3C(&result,&self->list,&where,&value);
        if(lap<5 && !self->others[lap].p) {
            self->others[lap].Reset(new DigitPanel(self->layer));
            int variant=0;
            if(g_gameMode==1) variant++;
            CopyPosition(self->others[lap].p, lbl_804EE9E0[variant][lap+1]);
        }
    }
}
