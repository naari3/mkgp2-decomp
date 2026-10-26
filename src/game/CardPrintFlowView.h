#include "game/FlowScene.h"
struct PrintKart {
    int busy;
    int layout;
    ~PrintKart();
};
struct CardPrintFlow : FlowTask {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    VHolder<PrintKart> kart;
    int phase;
    int error;
    virtual void _key4();
    ~CardPrintFlow();
};
extern "C" {
void fn_801D919C(PrintKart *);
void clFlowKart_SetupTextLayout(PrintKart *, int);
void fn_801D9B70(PrintKart *, int);
unsigned char fn_8020F278();
unsigned char fn_8020F280();
unsigned char fn_8020F288();
int Sci2Card_GetPrintErrorCode();
int fn_8020F270();
int fn_8020F268();
unsigned char card_is_ejected();
int card_rw_get_substate();
void fn_8024B924(CardPrintFlow *);
void fn_8024B77C(CardPrintFlow *);
void DebugPrintf(const char *, ...);
extern int lbl_806D1AB0;
}
