#include "game/FlowScene.h"
#include "game/types/clRsCardT1.h"
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
void DebugPrintf(const char *, ...);
/* read-only for the card flow views (only CardPrintConfig writes it, with its own
   non-const declaration); const lets GC/2.6 hoist its load over self-> stores. */
extern const int lbl_806D1AB0;
}
