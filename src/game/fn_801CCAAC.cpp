#include "game/ItemSelectPendingPrivate.h"
extern "C" {
extern void *lbl_8048EF34[], *lbl_8049B1AC[];
extern int g_characterId, lbl_806CF110;
extern unsigned char g_lakituStartAnimDone,lbl_806D1290,lbl_806D1264[3],g_rendererGateFlag;
extern char g_playerData[];
int VSMode_SeedRandomItemSequence(int,int,int);
void fn_801B7CD0(int);
void SetTimerModeEnabled(int);
int GetDisplayBufferIndex();
void RaceSlot_InitSlot(int,int,int,int,int);
void RaceSlot_SetItemSlotByte(int,int,unsigned char);
void DoublyLinkedList_PushBefore(void *,void *,void *,void *);
}
struct SelectClosing {
    void *vt; SelectSprite *sprite; int delay;
    SelectTween tween[5];
    unsigned char active,mode; char pad86[2];
    unsigned char r,g,b,pad8B; int layer;
    SelectClosing() : vt(lbl_8048EF34), sprite(0), delay(0) {
        active=0; mode=0;
        tween[0].enabled=0; tween[1].enabled=0; tween[2].enabled=0;
        tween[3].enabled=0; tween[4].enabled=0;
        vt=lbl_8049B1AC;
        r=0; g=0; b=0; layer=7;
    }
    void Fade() {
        tween[0].from=lbl_806D9E20;
        tween[0].to=lbl_806D9E24;
        tween[0].step=lbl_806D9E28;
        tween[0].t=lbl_806D9E20;
        tween[0].value=lbl_806D9E20;
        tween[0].enabled=1;
    }
};
extern "C" int fn_801CCAAC(SelectOwner *self) {
    int character;
    int slot;
    if(self->result!=-1) return self->result;
    InputState *input=GetInput();
    unsigned char pressed=input->held==1;
    ++self->timer;
    if((self->timer>=300 || (pressed==1 && self->timer>=180)) && self->closing==0) {
        self->closing=1; self->timer=0;
        SelectClosing *p=new SelectClosing;
        p->Fade();
        SelectNode *where=(SelectNode *)&self->last;
        SelectNode *ret;
        DoublyLinkedList_PushBefore(&ret,&self->count,&where,&p);
    }
    if(self->closing==1 && self->timer>31) {
        slot=VSMode_SeedRandomItemSequence(0,g_characterId,5);
        fn_801B7CD0(-1); SetTimerModeEnabled(1);
        g_lakituStartAnimDone=0; lbl_806D1290=0;
        character=g_characterId;
        RaceSlot_InitSlot(slot,GetDisplayBufferIndex(),character,1,0);
        lbl_806CF110=1;
        RaceSlot_SetItemSlotByte(slot,0,lbl_806D1264[0]);
        RaceSlot_SetItemSlotByte(slot,1,lbl_806D1264[1]);
        RaceSlot_SetItemSlotByte(slot,2,lbl_806D1264[2]);
        g_rendererGateFlag=1;
        g_playerData[0x1B8]=g_characterId;
        self->result=42;
        InputState *input=GetInput(); input->enabled=0; input->held=0; input->edge=0;
    }
    return self->result;
}
