#include "game/FigureSlotPrivate.h"

static inline float InterpolateFigurePosition(float start, float delta, int ticks) {
    return start + delta * (float)ticks / 12.0f;
}

extern "C" unsigned char fn_801C6744(FigureSlotView* self,int index) {
    FigureSlot* slot=&self->slots[index];
    if(!slot->sprite) return 0;
    if(Sprite_AdvanceAnim(slot->sprite,lbl_806D9C7C) == 1) return 1;
    switch(slot->state) {
    case 1:
        if(!slot->sprite) slot->sprite=new FigureSprite(0x182,0,0);
        else Sprite_SetupAnim(slot->sprite,0x182,0,0);
        if(self->second == 0 && index == 7 && !self->unlock0)
            Sprite_SetAnimParam(slot->sprite,0x1777,clFlowCup_data_8049AD58[index+1].label);
        else if(self->second == 1 && index == 7 && !self->unlock1)
            Sprite_SetAnimParam(slot->sprite,0x1777,clFlowCup_data_8049AD58[index+1].label);
        else Sprite_SetAnimParam(slot->sprite,0x1777,clFlowCup_data_8049AD58[index].label);
        Sprite_SetAnimParam(slot->sprite,0x1780,clFlowCup_data_8049AD58[index].sub);
        fn_801A0550(slot->sprite);
        slot->sprite->SetPos(clFlowCup_data_8049AD58[index].x,lbl_806D9C80+clFlowCup_data_8049AD58[index].y);
        slot->sprite->SetScale(lbl_806D9C70);
        fn_8019FF6C(slot->sprite,1);
        break;
    case 3:
        Sprite_Destroy(slot->sprite,1); slot->state=0; slot->sprite=0; return 0;
    case 5:
        if(slot->phase == 0) {
            if(!slot->sprite) slot->sprite=new FigureSprite(0x181,0,0);
            else Sprite_SetupAnim(slot->sprite,0x181,0,0);
            if(self->second == 0 && index == 7 && !self->unlock0)
                Sprite_SetAnimParam(slot->sprite,0x1777,clFlowCup_data_8049AD58[index+1].label);
            else if(self->second == 1 && index == 7 && !self->unlock1)
                Sprite_SetAnimParam(slot->sprite,0x1777,clFlowCup_data_8049AD58[index+1].label);
            else Sprite_SetAnimParam(slot->sprite,0x1777,clFlowCup_data_8049AD58[index].label);
            Sprite_SetAnimParam(slot->sprite,0x1780,clFlowCup_data_8049AD58[index].sub);
            fn_801A0550(slot->sprite);
            slot->sprite->SetPos(clFlowCup_data_8049AD58[index].x,lbl_806D9C84+clFlowCup_data_8049AD58[index].y);
            slot->sprite->SetScale(lbl_806D9C88);
            slot->phase++;
        } else if(slot->phase == 1) {
            float dx=lbl_806D9C74-clFlowCup_data_8049AD58[index].x;
            float dy=lbl_806D9C8C-clFlowCup_data_8049AD58[index].y;
            slot->ticks++;
            float x=InterpolateFigurePosition(clFlowCup_data_8049AD58[index].x,dx,slot->ticks);
            float y=InterpolateFigurePosition(clFlowCup_data_8049AD58[index].y,dy,slot->ticks);
            slot->sprite->SetPos(x,y);
            if(slot->ticks>=12) slot->phase++;
        }
        break;
    case 6:
        slot->ticks++;
        slot->sprite->SetPos(lbl_806D9C74-lbl_806D9C94*(float)slot->ticks/lbl_806D9C90,lbl_806D9C8C);
        if(slot->ticks>=12) { Sprite_Destroy(slot->sprite,1); slot->state=0; slot->sprite=0; }
        return 0;
    case 2: case 4: default: break;
    }
    return 1;
}
