/* GP please scene construction, 0x801CD030..0x801CDA40. */
#include "game/GpPleaseInitPrivate.h"
#include "game/singleton.h"
clFlowGpPlease::clFlowGpPlease() {
    SetSyncTarget(37);
    active=0; timer=0; next=-1;
    SetupBgSprites(0);
    InputState *input=SINGLETON_INSTANCE(g_pInputState);
    input->enabled=1; input->held=0; input->edge=0;
    CourseSprite *sprite=new CourseSprite(0x14f,0,0);
    sprite->x=lbl_806D9E30; sprite->y=lbl_806D9E34;
    Sprite_SetAnimParam(sprite,0xa9c,fn_801D8DB4(g_cupId,g_roundIndex,0));
    Sprite_SetAnimParam(sprite,0xa9d,fn_801D8DB4(g_cupId,g_roundIndex,1));
    fn_801A0550(sprite);
    sprite->layer=0;
    GpPanelBase *panel=new GpPanelBase(sprite,0);
    list.Append(panel);
    sprite=new CourseSprite(0x193,1,0);
    sprite->x=lbl_806D9E30; sprite->y=lbl_806D9E38;
    panel=new GpPanelBase(sprite,10);
    panel->Fade();
    list.Append(panel);
    unsigned char *ids;
    int x;
    int i;
    i=0; ids=lbl_806D1264; x=118;
    for(;i<3;i++) {
        panel=new GpTextPanel(*ids,x);
        panel->Fade();
        fn_801D8AA0(((GpTextPanel *)panel)->holder.p,5);
        fn_801D8A98(((GpTextPanel *)panel)->holder.p,6);
        list.Append(panel);
        x+=202; ids++;
    }
    sprite=new CourseSprite(0x195,1,0);
    sprite->x=lbl_806D9E30; sprite->y=lbl_806D9E44;
    Sprite_SetAnimParam(sprite,0x1732,fn_801D8D8C(g_roundIndex));
    panel=new GpPanelBase(sprite,20);
    list.Append(panel);
    sprite=new CourseSprite(0x194,1,0);
    sprite->x=lbl_806D9E30; sprite->y=lbl_806D9E48;
    sprite->scaleX=lbl_806D9E4C; sprite->scaleY=lbl_806D9E24;
    panel=new GpPanelBase(sprite,20);
    list.Append(panel);
    panel=new GpLabelPanel(0x17ae,lbl_806D9E30,lbl_806D9E50);
    panel->tween[1].Set(lbl_806D9E20,lbl_806D9E4C,lbl_806D9E54,lbl_806D9E20,lbl_806D9E20);
    panel->Fade();
    list.Append(panel);
    panel=new GpLabelPanel(fn_801D8DA0(g_cupId),lbl_806D9E30,lbl_806D9E58);
    panel->Fade();
    list.Append(panel);
    if(g_roundIndex>=4) {
        panel->tween[3].Set(lbl_806D9E5C,lbl_806D9E5C,lbl_806D9E60,lbl_806D9E20,lbl_806D9E5C);
        panel=new GpLabelPanel(0x15f4,lbl_806D9E64,lbl_806D9E58);
        panel->Fade();
        list.Append(panel);
    }
    panel=new GpColorPanel;
    panel->tween[0].Set(lbl_806D9E20,lbl_806D9E68,lbl_806D9E3C,lbl_806D9E20,lbl_806D9E20);
    list.Append(panel);
    fn_80209C88();
    fn_80209AC4(g_cupId,g_roundIndex);
}
