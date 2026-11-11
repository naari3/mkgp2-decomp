#ifndef GAME_TYPES_CLMNCARDRENEW_H
#define GAME_TYPES_CLMNCARDRENEW_H
#include "game/types/clMnCardClasses.h"
#pragma auto_inline off
struct CardChoice {
    char pad0[0x10]; int state; char tail[0x78];
    CardChoice(int,int,int);
};
struct CardText {
    int state,layout; char pad8[0x19]; unsigned char flag21; char tail[0x46];
    CardText();
};
struct CreditPrompt { char pad0[8]; unsigned char done; char tail[7]; CreditPrompt(int); };
struct CreditMark { char opaque[0x20]; CreditMark(int,int,int,int,int); };
struct CreditMessage { char opaque[0x5c]; CreditMessage(); };
struct clMnCardRenew : clMnCardT0Interface {
    int resumeState,mode,delay,coins;
    unsigned char first; char pad39[3]; int slot;
    unsigned char changing,unavailable; char pad42[2]; int inputDelay;
    CreditPrompt *prompt; CardChoice *choice; CardText *text; CreditMark *mark;
    clMnCardRenew(int mode,int id);
    virtual ~clMnCardRenew();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    void Create();
    void Eject();
    void SelectYes();
    void SelectNo();
    void Select();
};
struct CreditDisplay { char pad[8]; int mode; void SetMode(int v) { mode=v; } };
extern "C" {
extern char g_playerData[];
extern unsigned char CardCreditFlow_bss_806D1A90;
extern int CardCreditFlow_bss_806D1A94; extern const int lbl_806D1A98;
extern CreditMessage *lbl_806D1A88;
extern char CardCreditFlow_rodata_803EEF00[];
extern void *CardCreditFlow_vtable_804EE714[];
extern const float lbl_806DBE34,lbl_806DBE38,lbl_806DBE3C,lbl_806DBE48,lbl_806DBE4C,lbl_806DBE50,lbl_806DBE54,lbl_806DBE58;
void fn_8016039C(CardChoice*); void fn_801D9A2C(CardText*); void fn_8024E05C(CreditPrompt*); void fn_8023CD54(CreditMark*);
void fn_801D9B70(CardText*,int); void fn_801D919C(CardText*); void clFlowKart_SetupTextLayout(CardText*,int);
void fn_80161888(CardChoice*); void fn_801618CC(CardChoice*,int,int); void fn_80160588(CardChoice*,int,bool);
void fn_801FE348(); void fn_801FE3BC(); void fn_801FE390(); void fn_801FE27C(int);
void PlayerData_ResetForFlow(); void fn_801D7610(void*,int);
CreditDisplay *fn_801DAEC0();
int CreditMgr_GetPlayState(int); int CreditMgr_GetCreditCount(int); void CreditMgr_TryConfirmPlay(int);
void fn_80218D90(int); void fn_8024E094(CreditPrompt*); void fn_8024E1DC(CreditPrompt*);
void fn_8024E244(CreditPrompt*,int); void fn_801D9F88(CardText*,int); void fn_80161F28(CardChoice*,int); void fn_8023CFE0(CreditMark*,int);
void MemoryManager_TimedFree(void*);
void fn_8023CFC8(CreditMark*); void fn_8023CFD4(CreditMark*); void fn_8023CDA8(CreditMark*);
void fn_8023CD3C(CreditMark*,float,float); void fn_8023CCF8(CreditMark*,float,float); void fn_8023CD24(CreditMark*,float,float); void fn_8023CCCC(CreditMark*,float,float); void fn_8023CEB4(CreditMark*);
void fn_80232284(CreditMessage*,float);
unsigned char Sci2Card_GetReceiptTestFlag(); void card_save_trigger(int); unsigned char CardSave_Tick(); int Sci2Card_GetPrintErrorCode(); int fn_801FDA78(int); int card_rw_get_substate(); int CardRW_GetSubState();
void card_eject_init(); unsigned char card_eject_state_machine(); int fn_801FDCA8(int);
void *ItemDisplay_GetOrCreate(); void ItemDisplay_Start(void*,int); void DebugPrintf(const char*,...);
void fn_80241C1C(clMnCardRenew*); void fn_80241C88(clMnCardRenew*); void fn_802422B8(clMnCardRenew*); void fn_80242530(clMnCardRenew*); void fn_8024270C(clMnCardRenew*); void fn_80242790(clMnCardRenew*); void fn_80242814(clMnCardRenew*);
}
static inline bool CreditUnavailable(clMnCardRenew *s) {
 if(CreditMgr_GetPlayState(0)==3) return 1;
 if(CreditMgr_GetCreditCount(s->slot)==0) return 1;
 return 0;
}
#endif
