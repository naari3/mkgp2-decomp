#include "game/types/clMnCardRenew.h"
void clMnCardRenew::Finish() { delete this; }

clMnCardRenew::clMnCardRenew(int mode_,int id) : clMnCardT0Interface(id) {
    resumeState=5; mode=mode_; delay=0; coins=CreditMgr_GetCoinCount(0,-1);
    first=1; slot=3; changing=0; unavailable=0; inputDelay=0; choice=0; text=0; mark=0;
    state=0; subState=0; timer=1201;
    CreditMgr_SetActiveSlot(slot); fn_80218D90(slot);
    prompt=new CreditPrompt(slot); text=new CardText; mark=new CreditMark(0x74,0x4a,0x1874,0x1875,3);
    fn_8023CD3C(mark,lbl_806DBE4C,lbl_806DBE50); fn_8023CCF8(mark,lbl_806DBE3C,lbl_806DBE38);
    fn_8023CD24(mark,lbl_806DBE48,lbl_806DBE38); fn_8023CCCC(mark,lbl_806DBE34,lbl_806DBE38); fn_8023CEB4(mark);
}

clMnCardRenew::~clMnCardRenew() {
    CreditMgr_SetActiveSlot(0); fn_80218D90(0); fn_8024E244(prompt,1);
    if(text) fn_801D9F88(text,1);
    if(choice) fn_80161F28(choice,1);
    if(mark) fn_8023CFE0(mark,1);
}

void clMnCardRenew::Select() {
    InputState *in=GetInput();
    int oldCursor=this->cursor;
    this->cursor+=in->dir;
    int cursor=this->cursor;
    if(cursor<0) this->cursor=0;
    if(cursor>1) this->cursor=1;
    int coins=CreditMgr_GetCoinCount(0,-1);
    if(this->coins!=coins) this->timer=1201;
    this->coins=coins;
    bool noCredit=CreditUnavailable(this);
    if(noCredit && this->unavailable!=noCredit && this->changing==0 && this->cursor>0) {
        this->fader.p->Set(0,15,15); this->changing=1; this->state=6; this->resumeState=5;
    }
    if(in->held==1) {
        if(this->cursor==0) {
            fn_801FE348();
            if(CreditMgr_GetCreditCount(this->slot)<=0) {
                this->state=10; this->subState=4; this->timer=-1; fn_8023CFC8(this->mark);
            } else {
                fn_8024E1DC(this->prompt); this->state=8;
                if(this->first) { this->first=0; this->timer=1201; }
            }
        } else {
            fn_801FE348(); fn_801FE3BC(); CardCreditFlow_bss_806D1A90=0;
            if((int)g_playerData[0x1d9]==2) { PlayerData_ResetForFlow(); this->state=this->mode==1 ? 9 : 11; }
            else this->state=11;
            this->subState=0; this->timer=-1; fn_8023CFC8(this->mark);
        }
    }
    if(this->timer>0) --this->timer;
    CreditMessage *message=lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88=new CreditMessage);
    fn_80232284(message,(float)this->timer/lbl_806DBE54);
    fn_801FE27C(this->timer);
    if(oldCursor!=this->cursor) fn_801FE390();
    if(this->timer<=0 && this->state==5) {
        PlayerData_ResetForFlow(); fn_801FE3BC();
        if(this->cursor==0) { this->fader.p->Set(0,15,15); this->state=7; this->subState=0; }
        else {
            fn_801FE348();
            if((int)g_playerData[0x1d9]==2) { this->state=this->mode==1 ? 9 : 11; this->subState=0; }
            else this->state=11;
        }
        CardCreditFlow_bss_806D1A90=0;
        CreditMessage *message=lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88=new CreditMessage);
        fn_80232284(message,lbl_806DBE58);
        fn_8023CFC8(this->mark);
    }
    this->unavailable=noCredit;
}

void clMnCardRenew::SelectNo() {
    fn_801618CC(this->choice,0,0); this->fader.p->Step();
    if(this->fader.p->Done()) { this->cursor=0; fn_801FE348(); this->state=this->resumeState; }
}

void clMnCardRenew::SelectYes() {
    fn_801618CC(this->choice,1,0); this->fader.p->Step();
    if(this->fader.p->Done()) { this->cursor=1; fn_801FE348(); this->state=this->resumeState; }
}

void clMnCardRenew::Eject() {
    InputState *in=GetInput();
    switch(this->subState) {
    case 0:
        if((unsigned char)(this->text->state==0)==1) {
            this->text->flag21=0; this->subState=1; this->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98);
            if(CardCreditFlow_bss_806D1A90==1) clFlowKart_SetupTextLayout(this->text,3); else clFlowKart_SetupTextLayout(this->text,2);
            card_eject_init(); fn_801D7610(g_playerData,1);
        } break;
    case 1:
        if(card_eject_state_machine()) {
            switch(fn_801FDCA8(Sci2Card_GetPrintErrorCode())) {
            case 0: this->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98); this->subState=2; fn_801D919C(this->text); break;
            case 6: case 7: fn_801D919C(this->text); fn_80161888(this->choice); this->state=-1; break;
            }
        } break;
    case 2: this->fader.p->Step(); if(in->held==1 || this->fader.p->Done()) this->subState=3; break;
    case 3: if(this->text->state==0) this->subState=7; break;
    case 7: this->state=11; this->subState=8; break;
    }
}

void clMnCardRenew::Create() {
    InputState *in=GetInput();
    switch(this->subState) {
    case 4:
        if(this->text->state==0) {
            card_save_trigger(1); fn_801D919C(this->text); clFlowKart_SetupTextLayout(this->text,10);
            this->text->flag21=0; this->subState=5; CardCreditFlow_bss_806D1A90=1; CardCreditFlow_bss_806D1A94=0;
        } break;
    case 5:
        if(CardSave_Tick()) {
            switch(fn_801FDA78(Sci2Card_GetPrintErrorCode())) {
            case 0: { this->subState=6; this->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98); CreditMgr_TryConfirmPlay(this->slot); break; }
            case 6: case 7: fn_801D919C(this->text); if(this->choice) fn_80161888(this->choice); this->state=-1; break;
            }
        } else if(card_rw_get_substate()==2 && this->mode==1) {
            if((unsigned char)(this->text->state==0)==1) clFlowKart_SetupTextLayout(this->text,3);
        } else if(card_rw_get_substate()==3) {
            if(this->text->layout!=2) { fn_801D919C(this->text); clFlowKart_SetupTextLayout(this->text,2); }
        } else if(CardCreditFlow_bss_806D1A94==0) {
            if(CardRW_GetSubState()==1) { fn_801D919C(this->text); clFlowKart_SetupTextLayout(this->text,2); CardCreditFlow_bss_806D1A94=1; }
        } else if(CardCreditFlow_bss_806D1A94==1) {
            if(CardRW_GetSubState()==2) { fn_801D919C(this->text); CardCreditFlow_bss_806D1A94=2; }
        } break;
    case 6:
        this->fader.p->Step();
        if(in->held==1 || this->fader.p->Done()) { fn_801D919C(this->text); this->subState=7; } break;
    case 7:
        if(this->text->state==0) { this->state=11; this->subState=8; } break;
    }
}

void clMnCardRenew::Update() {
    const char *strings=CardCreditFlow_rodata_803EEF00;
    InputState *in=GetInput();
    bool pressed=in->held==1;
    int oldState=this->state;
    if(oldState!=1 && oldState!=9) {
        if(pressed) this->inputDelay=10;
        if(this->inputDelay>0) { --this->inputDelay; fn_801DAEC0()->SetMode(4); }
        else fn_801DAEC0()->SetMode(1);
    }
    switch(oldState) {
    case 0:
        if(this->mode==1) {
            if((unsigned char)g_playerData[0x1a0]==0) { this->slot=3; fn_801D919C(this->text); clFlowKart_SetupTextLayout(this->text,9); }
            else { this->slot=4; fn_801D919C(this->text); clFlowKart_SetupTextLayout(this->text,12); }
        } else {
            if((unsigned char)g_playerData[0x1a0]==0) { this->slot=3; fn_801D919C(this->text); clFlowKart_SetupTextLayout(this->text,8); }
            else { this->slot=4; fn_801D919C(this->text); clFlowKart_SetupTextLayout(this->text,12); }
        }
        ItemDisplay_Start(ItemDisplay_GetOrCreate(),0x1ad6); CreditMgr_SetActiveSlot(this->slot);
        this->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98); this->state=1; break;
    case 1:
        if(this->text->state==0) {
            if(pressed) fn_801DAEC0()->SetMode(0); else fn_801DAEC0()->SetMode(1);
            this->fader.p->Step();
            if(this->fader.p->Done() || pressed) {
                if(Sci2Card_GetReceiptTestFlag()) {
                    fn_801D919C(this->text); clFlowKart_SetupTextLayout(this->text,7);
                    this->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98); this->delay=180; this->state=2;
                } else { fn_801D919C(this->text); this->state=3; }
            }
        } break;
    case 2:
        if(this->text->state==0) {
            if(pressed) fn_801DAEC0()->SetMode(0); else fn_801DAEC0()->SetMode(1);
            this->fader.p->Step();
            if(this->delay!=0) --this->delay;
            else if(this->fader.p->Done() || pressed) {
                fn_801D919C(this->text); PlayerData_ResetForFlow(); fn_801FE3BC();
                CardCreditFlow_bss_806D1A90=0; this->state=9; this->subState=0;
            }
        } break;
    case 3:
        if(this->text->state==0) {
            if(!this->choice) this->choice=new CardChoice(0,0,5);
            this->fader.p->Set(0,30,30); this->state=4;
        } break;
    case 4:
        this->fader.p->Step();
        if(this->fader.p->Done()) {
            int coins=CreditMgr_GetCoinCount(0,-1);
            if(this->coins!=coins) this->timer=1201;
            this->coins=coins;
            unsigned char noCredit;
            if(CreditMgr_GetPlayState(0)==3) noCredit=1;
            else if(CreditMgr_GetCreditCount(this->slot)==0) noCredit=1; else noCredit=0;
            this->unavailable=noCredit; this->state=5;
            if(!this->choice) this->choice=new CardChoice(0,0,5);
            fn_8023CFD4(this->mark);
        }
        DebugPrintf(strings+0x554,strings+0x564); break;
    case 5: DebugPrintf(strings+0x574,strings+0x564); Select(); break;
    case 6: SelectNo(); break;
    case 7: SelectYes(); break;
    case 8: if(this->prompt->done==1) this->state=5; break;
    case 9: DebugPrintf(strings+0x584,strings+0x564); fn_801DAEC0()->SetMode(0); Eject(); break;
    case 10: DebugPrintf(strings+0x594,strings+0x564); Create(); break;
    case 11:
        DebugPrintf(strings+0x5a4,strings+0x564);
        if(this->choice) fn_80161888(this->choice); this->state=12; break;
    case 12: {
        unsigned char done=0;
        if(this->list.p->entries.count<=0) done=1;
        if(this->choice) {
            if((unsigned char)(this->choice->state==6)==1 && done==1) done=1; else done=0;
        }
        if(done==1) { this->field0C=1; this->state=-1; }
        break;
    }
    }
    this->list.p->Update(); fn_8024E094(this->prompt);
    if(this->text) { fn_801D9B70(this->text,(oldState!=10 ? (unsigned char)pressed : 0) != 0); }
    if(this->choice) {
        if(this->state==5) fn_80160588(this->choice,in->dir,pressed);
        else fn_80160588(this->choice,0,0);
    }
    fn_8023CDA8(this->mark);
}

void clMnCardRenew::Draw() {
    this->list.p->Draw();
    if(this->choice) fn_8016039C(this->choice);
    if(this->text) fn_801D9A2C(this->text);
    fn_8024E05C(this->prompt);
    fn_8023CD54(this->mark);
}

