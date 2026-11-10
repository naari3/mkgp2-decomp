#include "game/CardCreditFlowPrivate.h"
extern "C" void fn_80241C1C(CardCreditFlow *s) {
    s->list.p->Draw();
    if(s->choice) fn_8016039C(s->choice);
    if(s->text) fn_801D9A2C(s->text);
    fn_8024E05C(s->prompt);
    fn_8023CD54(s->mark);
}
extern "C" void fn_80241C88(CardCreditFlow *s) {
    const char *strings=CardCreditFlow_rodata_803EEF00;
    InputState *in=GetInput();
    bool pressed=in->held==1;
    int oldState=s->state;
    if(oldState!=1 && oldState!=9) {
        if(pressed) s->inputDelay=10;
        if(s->inputDelay>0) { --s->inputDelay; fn_801DAEC0()->SetMode(4); }
        else fn_801DAEC0()->SetMode(1);
    }
    switch(oldState) {
    case 0:
        if(s->mode==1) {
            if((unsigned char)g_playerData[0x1a0]==0) { s->slot=3; fn_801D919C(s->text); clFlowKart_SetupTextLayout(s->text,9); }
            else { s->slot=4; fn_801D919C(s->text); clFlowKart_SetupTextLayout(s->text,12); }
        } else {
            if((unsigned char)g_playerData[0x1a0]==0) { s->slot=3; fn_801D919C(s->text); clFlowKart_SetupTextLayout(s->text,8); }
            else { s->slot=4; fn_801D919C(s->text); clFlowKart_SetupTextLayout(s->text,12); }
        }
        ItemDisplay_Start(ItemDisplay_GetOrCreate(),0x1ad6); CreditMgr_SetActiveSlot(s->slot);
        s->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98); s->state=1; break;
    case 1:
        if(s->text->state==0) {
            if(pressed) fn_801DAEC0()->SetMode(0); else fn_801DAEC0()->SetMode(1);
            s->fader.p->Step();
            if(s->fader.p->Done() || pressed) {
                if(Sci2Card_GetReceiptTestFlag()) {
                    fn_801D919C(s->text); clFlowKart_SetupTextLayout(s->text,7);
                    s->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98); s->delay=180; s->state=2;
                } else { fn_801D919C(s->text); s->state=3; }
            }
        } break;
    case 2:
        if(s->text->state==0) {
            if(pressed) fn_801DAEC0()->SetMode(0); else fn_801DAEC0()->SetMode(1);
            s->fader.p->Step();
            if(s->delay!=0) --s->delay;
            else if(s->fader.p->Done() || pressed) {
                fn_801D919C(s->text); PlayerData_ResetForFlow(); fn_801FE3BC();
                CardCreditFlow_bss_806D1A90=0; s->state=9; s->subState=0;
            }
        } break;
    case 3:
        if(s->text->state==0) {
            if(!s->choice) s->choice=new CardChoice(0,0,5);
            s->fader.p->Set(0,30,30); s->state=4;
        } break;
    case 4:
        s->fader.p->Step();
        if(s->fader.p->Done()) {
            int coins=CreditMgr_GetCoinCount(0,-1);
            if(s->coins!=coins) s->timer=1201;
            s->coins=coins;
            unsigned char noCredit;
            if(CreditMgr_GetPlayState(0)==3) noCredit=1;
            else if(CreditMgr_GetCreditCount(s->slot)==0) noCredit=1; else noCredit=0;
            s->unavailable=noCredit; s->state=5;
            if(!s->choice) s->choice=new CardChoice(0,0,5);
            fn_8023CFD4(s->mark);
        }
        DebugPrintf(strings+0x554,strings+0x564); break;
    case 5: DebugPrintf(strings+0x574,strings+0x564); fn_80242814(s); break;
    case 6: fn_80242790(s); break;
    case 7: fn_8024270C(s); break;
    case 8: if(s->prompt->done==1) s->state=5; break;
    case 9: DebugPrintf(strings+0x584,strings+0x564); fn_801DAEC0()->SetMode(0); fn_80242530(s); break;
    case 10: DebugPrintf(strings+0x594,strings+0x564); fn_802422B8(s); break;
    case 11:
        DebugPrintf(strings+0x5a4,strings+0x564);
        if(s->choice) fn_80161888(s->choice); s->state=12; break;
    case 12: {
        unsigned char done=0;
        if(s->list.p->entries.count<=0) done=1;
        if(s->choice) {
            if((unsigned char)(s->choice->state==6)==1 && done==1) done=1; else done=0;
        }
        if(done==1) { s->field0C=1; s->state=-1; }
        break;
    }
    }
    s->list.p->Update(); fn_8024E094(s->prompt);
    if(s->text) { fn_801D9B70(s->text,(oldState!=10 ? (unsigned char)pressed : 0) != 0); }
    if(s->choice) {
        if(s->state==5) fn_80160588(s->choice,in->dir,pressed);
        else fn_80160588(s->choice,0,0);
    }
    fn_8023CDA8(s->mark);
}
extern "C" void fn_802422B8(CardCreditFlow *s) {
    InputState *in=GetInput();
    switch(s->subState) {
    case 4:
        if(s->text->state==0) {
            card_save_trigger(1); fn_801D919C(s->text); clFlowKart_SetupTextLayout(s->text,10);
            s->text->flag21=0; s->subState=5; CardCreditFlow_bss_806D1A90=1; CardCreditFlow_bss_806D1A94=0;
        } break;
    case 5:
        if(CardSave_Tick()) {
            switch(fn_801FDA78(Sci2Card_GetPrintErrorCode())) {
            case 0: { s->subState=6; s->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98); CreditMgr_TryConfirmPlay(s->slot); break; }
            case 6: case 7: fn_801D919C(s->text); if(s->choice) fn_80161888(s->choice); s->state=-1; break;
            }
        } else if(card_rw_get_substate()==2 && s->mode==1) {
            if((unsigned char)(s->text->state==0)==1) clFlowKart_SetupTextLayout(s->text,3);
        } else if(card_rw_get_substate()==3) {
            if(s->text->layout!=2) { fn_801D919C(s->text); clFlowKart_SetupTextLayout(s->text,2); }
        } else if(CardCreditFlow_bss_806D1A94==0) {
            if(CardRW_GetSubState()==1) { fn_801D919C(s->text); clFlowKart_SetupTextLayout(s->text,2); CardCreditFlow_bss_806D1A94=1; }
        } else if(CardCreditFlow_bss_806D1A94==1) {
            if(CardRW_GetSubState()==2) { fn_801D919C(s->text); CardCreditFlow_bss_806D1A94=2; }
        } break;
    case 6:
        s->fader.p->Step();
        if(in->held==1 || s->fader.p->Done()) { fn_801D919C(s->text); s->subState=7; } break;
    case 7:
        if(s->text->state==0) { s->state=11; s->subState=8; } break;
    }
}
extern "C" void fn_80242530(CardCreditFlow *s) {
    InputState *in=GetInput();
    switch(s->subState) {
    case 0:
        if((unsigned char)(s->text->state==0)==1) {
            s->text->flag21=0; s->subState=1; s->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98);
            if(CardCreditFlow_bss_806D1A90==1) clFlowKart_SetupTextLayout(s->text,3); else clFlowKart_SetupTextLayout(s->text,2);
            card_eject_init(); fn_801D7610(g_playerData,1);
        } break;
    case 1:
        if(card_eject_state_machine()) {
            switch(fn_801FDCA8(Sci2Card_GetPrintErrorCode())) {
            case 0: s->fader.p->Set(0,lbl_806D1A98,(short)lbl_806D1A98); s->subState=2; fn_801D919C(s->text); break;
            case 6: case 7: fn_801D919C(s->text); fn_80161888(s->choice); s->state=-1; break;
            }
        } break;
    case 2: s->fader.p->Step(); if(in->held==1 || s->fader.p->Done()) s->subState=3; break;
    case 3: if(s->text->state==0) s->subState=7; break;
    case 7: s->state=11; s->subState=8; break;
    }
}
extern "C" void fn_8024270C(CardCreditFlow *s) {
    fn_801618CC(s->choice,1,0); s->fader.p->Step();
    if(s->fader.p->Done()) { s->cursor=1; fn_801FE348(); s->state=s->resumeState; }
}
extern "C" void fn_80242790(CardCreditFlow *s) {
    fn_801618CC(s->choice,0,0); s->fader.p->Step();
    if(s->fader.p->Done()) { s->cursor=0; fn_801FE348(); s->state=s->resumeState; }
}
extern "C" void fn_80242814(CardCreditFlow *s) {
    InputState *in=GetInput();
    int oldCursor=s->cursor;
    s->cursor+=in->dir;
    int cursor=s->cursor;
    if(cursor<0) s->cursor=0;
    if(cursor>1) s->cursor=1;
    int coins=CreditMgr_GetCoinCount(0,-1);
    if(s->coins!=coins) s->timer=1201;
    s->coins=coins;
    bool noCredit=CreditUnavailable(s);
    if(noCredit && s->unavailable!=noCredit && s->changing==0 && s->cursor>0) {
        s->fader.p->Set(0,15,15); s->changing=1; s->state=6; s->resumeState=5;
    }
    if(in->held==1) {
        if(s->cursor==0) {
            fn_801FE348();
            if(CreditMgr_GetCreditCount(s->slot)<=0) {
                s->state=10; s->subState=4; s->timer=-1; fn_8023CFC8(s->mark);
            } else {
                fn_8024E1DC(s->prompt); s->state=8;
                if(s->first) { s->first=0; s->timer=1201; }
            }
        } else {
            fn_801FE348(); fn_801FE3BC(); CardCreditFlow_bss_806D1A90=0;
            if((int)g_playerData[0x1d9]==2) { PlayerData_ResetForFlow(); s->state=s->mode==1 ? 9 : 11; }
            else s->state=11;
            s->subState=0; s->timer=-1; fn_8023CFC8(s->mark);
        }
    }
    if(s->timer>0) --s->timer;
    CreditMessage *message=lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88=new CreditMessage);
    fn_80232284(message,(float)s->timer/lbl_806DBE54);
    fn_801FE27C(s->timer);
    if(oldCursor!=s->cursor) fn_801FE390();
    if(s->timer<=0 && s->state==5) {
        PlayerData_ResetForFlow(); fn_801FE3BC();
        if(s->cursor==0) { s->fader.p->Set(0,15,15); s->state=7; s->subState=0; }
        else {
            fn_801FE348();
            if((int)g_playerData[0x1d9]==2) { s->state=s->mode==1 ? 9 : 11; s->subState=0; }
            else s->state=11;
        }
        CardCreditFlow_bss_806D1A90=0;
        CreditMessage *message=lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88=new CreditMessage);
        fn_80232284(message,lbl_806DBE58);
        fn_8023CFC8(s->mark);
    }
    s->unavailable=noCredit;
}
extern "C" CardCreditFlow *fn_80242B88(CardCreditFlow *s,short flags) {
    if(s) {
        *(void ***)s=CardCreditFlow_vtable_804EE714;
        CreditMgr_SetActiveSlot(0); fn_80218D90(0); fn_8024E244(s->prompt,1);
        if(s->text) fn_801D9F88(s->text,1);
        if(s->choice) fn_80161F28(s->choice,1);
        if(s->mark) fn_8023CFE0(s->mark,1);
        dtor_801FD32C(s,0); if(flags>0) MemoryManager_TimedFree(s);
    } return s;
}
CardCreditFlow::CardCreditFlow(int mode_,int id) : FlowScene(id) {
    resumeState=5; mode=mode_; delay=0; coins=CreditMgr_GetCoinCount(0,-1);
    first=1; slot=3; changing=0; unavailable=0; inputDelay=0; choice=0; text=0; mark=0;
    state=0; subState=0; timer=1201;
    CreditMgr_SetActiveSlot(slot); fn_80218D90(slot);
    prompt=new CreditPrompt(slot); text=new CardText; mark=new CreditMark(0x74,0x4a,0x1874,0x1875,3);
    fn_8023CD3C(mark,lbl_806DBE4C,lbl_806DBE50); fn_8023CCF8(mark,lbl_806DBE3C,lbl_806DBE38);
    fn_8023CD24(mark,lbl_806DBE48,lbl_806DBE38); fn_8023CCCC(mark,lbl_806DBE34,lbl_806DBE38); fn_8023CEB4(mark);
}
extern "C" void fn_80242DA8(VObject *p) { delete p; }
