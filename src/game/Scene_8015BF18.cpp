#include "game/Scene_8015BF18_private.h"
#include "game/resultscene_private.h"
extern "C" {
extern PlayerDataRecord g_playerData;
extern int g_ccClass,g_characterId;
extern const float lbl_806D866C,lbl_806D8670,lbl_806D8674,lbl_806D8678,lbl_806D867C,lbl_806D8680;
extern int Scene_8015BF18_rodata_80368C84[];
unsigned char IsCardValid(); unsigned char fn_801D5C88(PlayerDataRecord *,int);
void SoundMgr_Play(int); void fn_80121210(); void fn_801426A0(void *,int,int);
void GXDrawDone();
void Sprite_CreateWithParams(void *,int,int,float,float,float,float,float,float);
}
#pragma exceptions on
inline ResultParamsSprite::ResultParamsSprite() {
    float size = lbl_806D8674;
    float alpha = lbl_806D8678;
    Sprite_CreateWithParams(this,0x99,1,lbl_806D866C,lbl_806D8670,size,size,alpha,alpha);
}
inline ResultAward::ResultAward(int i) : idx(i), timer(0), phase(0), done(0), sprite(new ResultParamsSprite) {
    resource.Show(lbl_806D866C,lbl_806D8670,lbl_806D8674);
    if (idx%2 == 0) { resource.resId=0x179f; SoundMgr_Play(0x20); }
    else { resource.resId=0x17a0; SoundMgr_Play(0x21); }
    resource.SetColor(0xffffff00);
}
inline ResultIntro::ResultIntro(int i) {
    fn_80121210(); idx=i; stage=0; timer=lbl_806D8678; on=0;
    sound=0x1f; soundStarted=0;
    env=new ResultEnvironment;
    model=new ResultInnerModel(0);
    fn_801426A0(model,0,g_characterId);
    sprite=new ResultPopupSprite(Scene_8015BF18_rodata_80368C84[i],1,0);
    inner.mode=2; inner.SetSize(lbl_806D867C,lbl_806D8680);
    inner.Show(lbl_806D866C,lbl_806D8670,lbl_806D8674); inner.SetColor(0);
    fade.mode=2; fade.SetSize(lbl_806D867C,lbl_806D8680);
    fade.Show(lbl_806D866C,lbl_806D8670,lbl_806D8674); fade.SetColor(0xff);
}
extern "C" void fn_8015BF18(ResultSequence *self) {
    if(self->done) return;
    if(!self->part) {
        if(!IsCardValid()) {
            switch(self->state) {
            case 0: self->part=new ResultDialog(self->idx); break;
            case 1:
                if(self->idx%2 == 0) {
                    if(fn_801D5C88(&g_playerData,g_ccClass)==1) self->part=new ResultAward(self->idx);
                    else ++self->state;
                } else ++self->state;
                break;
            default: self->done=1; break;
            }
        } else {
            switch(self->state) {
            case 0: self->part=new ResultIntro(self->idx); break;
            case 1: self->part=new ResultDialog(self->idx); break;
            case 2: self->part=new ResultAward(self->idx); break;
            default: self->done=1; break;
            }
        }
    } else {
        if(self->part->v14()) {
            GXDrawDone(); delete self->part; self->part=0; ++self->state;
        } else self->part->v0C();
    }
}
#pragma exceptions reset
