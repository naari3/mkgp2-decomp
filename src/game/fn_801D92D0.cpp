#include "game/FlowKartSetup_private.h"
extern "C" unsigned char fn_801D92D0(FKSetupPanel *self, FKPanelEntry *entry) {
    int i;
    if (self->state != 0) {
        memcpy(&self->pending,entry,0x1C);
        self->otherKind=-1;
        self->queued=0;
        return 0;
    }
    self->kind=-1;
    int mode=entry->mode;
    self->state=1;
    self->timer=0;
    self->alpha=0;
    self->mode=mode;
    if (self->labelA) Sprite_SetupAnim(self->labelA,0x10,1,0);
    else self->labelA=new FKPanelSprite(0x10,1,0);
    self->labelA->SetPosition(lbl_8039FC60[0].x,lbl_8039FC60[0].y);
    self->labelA->layer=self->layer;
    TexMgr_SetTexture(self->texts[0],entry->text[0]);
    TexMgr_SetTexture(self->texts[1],entry->text[1]);
    TexMgr_SetTexture(self->texts[2],entry->text[2]);
    for(i=0;i<3;++i) fn_801F8FCC(self->texts[i],entry->mode);
    if (entry->mode==1) {
        FKPlaceText(self->texts[0],lbl_8039FC60[0]+lbl_8039FC60[1]);
        FKPlaceText(self->texts[1],lbl_8039FC60[0]+lbl_8039FC60[2]);
        FKPlaceText(self->texts[2],lbl_8039FC60[0]+lbl_8039FC60[3]);
    } else {
        FKPlaceText(self->texts[0],lbl_8039FC60[0]+lbl_8039FC60[4]);
        FKPlaceText(self->texts[1],lbl_8039FC60[0]+lbl_8039FC60[5]);
        FKPlaceText(self->texts[2],lbl_8039FC60[0]+lbl_8039FC60[6]);
    }
    float scale;
    if (isJapanese() == 0) scale=lbl_806DA1B0; else scale=lbl_806DA1BC;
    for(i=0;i<3;++i) {
        fn_801F93D0(self->texts[i],scale,scale);
        fn_801F8E90(self->texts[i]);
        self->texts[i]->color=0xFFFFFF00;
    }
    fn_80121E10(self->icons[1]);
    self->icons[1]->resId=entry->resource[1];
    FKShowIcon(self->icons[1],lbl_8039FC60[0]+lbl_8039FC60[7]);
    self->icons[0]->resId=0x1E86;
    FKShowIcon(self->icons[0],lbl_8039FC60[0]+lbl_8039FC60[9]);
    fn_80121E10(self->icons[2]);
    self->icons[2]->resId=entry->resource[0];
    FKShowIcon(self->icons[2],lbl_8039FC60[0]+lbl_8039FC60[8]);
    self->iconMode=entry->state;
    if (self->iconMode==2) FKShowIcon(self->icons[1],lbl_8039FC60[0]+lbl_8039FC60[9]);
    if (entry->state==3) {
        if (self->labelB) Sprite_SetupAnim(self->labelB,0x19,1,0);
        else self->labelB=new FKPanelSprite(0x19,1,0);
        fn_8019FF6C(self->labelB,1);
        self->labelB->layer=6;
        self->labelB->SetPosition(lbl_8039FC60[0]+lbl_8039FC60[7]);
    }
    if (self->kind==13) self->icons[1]->SetScale(lbl_806DA1B0);
    fn_801FE1D4();
    return 1;
}
