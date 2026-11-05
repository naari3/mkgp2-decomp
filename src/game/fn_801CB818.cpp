#include "game/FlowScene.h"
struct SelectAnim { int id,mode; };
struct SelectParam { SelectAnim *anim; };
struct SelectColor { char pad00[0x20]; unsigned int color; };
struct SelectRoll { unsigned char stopped; char pad1[3]; int current,chosen; };
struct ItemSelectView {
    void *vt; int items[3]; int timer,countdown,field18,stage; float time;
    char pad24[0x58]; int result;
    SelectParam *slots[3],*frame,*prompt;
    void *corner;
    SelectColor *colors[12];
    char padC8[0x14]; SelectRoll *rolls[3];
};
extern "C" {
extern const float lbl_806D9DB0,lbl_806D9DB4,lbl_806D9DB8,lbl_806D9DBC,lbl_806D9DC0,lbl_806D9DC4;
extern int g_gameMode;
void SetRumbleMode(int,int,int);
void SpriteAnimParamBlock_Reload(SelectParam *,int);
void fn_8019FF6C(SelectAnim *,int);
void UI_PlaySeClSound4D();
void UI_PlaySeToggle(int);
void clFlowItemSelect_CommitSlotAnim(ItemSelectView *,int,int);
void SpriteHandle_SetCornerAlpha(void *,int);
void fn_801699D8(int,int);
}
static inline void StopRoll(SelectRoll *roll) {
    UI_PlaySeToggle(0); roll->stopped=1; roll->chosen=roll->current;
}
extern "C" int fn_801CB818(ItemSelectView *self) {
    if(self->result!=-1) return self->result;
    if(self->timer<=15) return -1;
    InputState *input=GetInput();
    unsigned char automatic=0;
    if(self->time<=lbl_806D9DB0 && self->stage<2) automatic=1;
    if(input->held==1 || automatic) {
        SetRumbleMode(0,1,1);
        ++self->stage;
        if(self->stage==1) {
            if(self->prompt) {
                SpriteAnimParamBlock_Reload(self->prompt,0x54);
                self->prompt->anim->mode=6;
                fn_8019FF6C(self->prompt->anim,0);
            }
            self->stage=2;
        }
        if(self->stage==2) {
            UI_PlaySeClSound4D();
            StopRoll(self->rolls[0]);
            clFlowItemSelect_CommitSlotAnim(self,0,self->items[0]);
            self->countdown=180;
        }
        if(self->stage==3 && self->countdown>151) self->countdown=151;
        if(self->stage==4 && self->countdown>121) self->countdown=121;
    }
    if(self->countdown!=0) {
        if(lbl_806D9DB4==(float)--self->countdown) {
            StopRoll(self->rolls[1]);
            clFlowItemSelect_CommitSlotAnim(self,1,self->items[1]);
            self->colors[0]->color=0xE02020FF;
            self->colors[1]->color=0xFFFFFFFF;
            self->colors[2]->color=0xFFFFFFFF;
            self->colors[3]->color=0xFFFFFFFF;
        } else if(lbl_806D9DB8==(float)self->countdown) {
            StopRoll(self->rolls[2]);
            clFlowItemSelect_CommitSlotAnim(self,2,self->items[2]);
            self->colors[4]->color=0xE02020FF;
            self->colors[5]->color=0xFFFFFFFF;
            self->colors[6]->color=0xFFFFFFFF;
            self->colors[7]->color=0xFFFFFFFF;
            SpriteAnimParamBlock_Reload(self->frame,0x45);
            SpriteHandle_SetCornerAlpha(self->corner,0);
        } else if(self->countdown==0) {
            fn_801699D8(0,0);
            if(g_gameMode==0) self->result=37;
            else self->result=39;
        }
        if(self->countdown<=170 && self->countdown>=160) {
            unsigned char alpha=(int)(lbl_806D9DBC*(lbl_806D9DC0-(float)(self->countdown-160)/lbl_806D9DC4));
            self->colors[0]->color=0xE0202000|alpha;
            self->colors[1]->color=0xFFFFFF00|alpha;
            self->colors[2]->color=0xFFFFFF00|alpha;
            self->colors[3]->color=0xFFFFFF00|alpha;
        } else if(self->countdown<=140 && self->countdown>=130) {
            unsigned char alpha=(int)(lbl_806D9DBC*(lbl_806D9DC0-(float)(self->countdown-130)/lbl_806D9DC4));
            self->colors[4]->color=0xE0202000|alpha;
            self->colors[5]->color=0xFFFFFF00|alpha;
            self->colors[6]->color=0xFFFFFF00|alpha;
            self->colors[7]->color=0xFFFFFF00|alpha;
        } else if(self->countdown<=110 && self->countdown>=100) {
            unsigned char alpha=(int)(lbl_806D9DBC*(lbl_806D9DC0-(float)(self->countdown-100)/lbl_806D9DC4));
            self->colors[8]->color=0xE0202000|alpha;
            self->colors[9]->color=0xFFFFFF00|alpha;
            self->colors[10]->color=0xFFFFFF00|alpha;
            self->colors[11]->color=0xFFFFFF00|alpha;
        }
    }
    return self->result;
}
