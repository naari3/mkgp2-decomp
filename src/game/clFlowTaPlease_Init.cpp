#include "game/C8TaPleasePrivate.h"
inline void C8SetDigit(AnimSprite *s, int value, short *digit) { Sprite_SetAnimParam(s,*digit,(short)(value+0x1A9A)); }
C8TaPlease::C8TaPlease() : prompt(new C8Prompt(0x74,-1,0x1872,-1,5)), box(new C8SpriteBox) {
    const C8TaTables *tables=&lbl_8039B470;
    SetSyncTarget(0x26);
    C8Input *input=C8GetInput();
    input->enabled=1; input->held=0; input->edge=0;
    sprite=new AnimSprite(0x9F,0,0);
    flag=0; state=0; selection=-1;
    SetupBgSprites(0);
    text=new C8Text;
    TexMgr_SetTexture(text,fn_8023DAA8(0x7D));
    text->color=0xE02020FF;
    for(int i=0;i<3;i++) {
        texts[i]=new C8Text;
        TexMgr_SetTexture(texts[i],Item_GetLocalizedAsset(0x7D,i));
    }
    params[0]=fn_801A0310(sprite,0x1ECD);
    params[1]=fn_801A0310(sprite,0x1ECF);
    params[2]=fn_801A0310(sprite,0x1ED1);
    params[3]=fn_801A0310(sprite,0x1ED3);
    *params[1]=0x2901;
    *params[3]=0x23E5;
    int cup=g_cupId-1;
    int round=g_longRoundFlag;
    Sprite_SetAnimParam(sprite,0xA9C,(short)tables->labels[cup][round][0]);
    Sprite_SetAnimParam(sprite,0xA9D,(short)tables->labels[cup][round][1]);
    Sprite_SetAnimParam(sprite,0x1E5B,(short)tables->rounds[cup][round]);
    Sprite_SetAnimParam(sprite,0x1AB4,(short)tables->symbols[cup][round]);
    float time=TaRecord_GetTime_Current(0);
    short *digit0=fn_801A0310(sprite,0x1A9A);
    short *digit1=fn_801A0310(sprite,0x1A9B);
    short *digit2=fn_801A0310(sprite,0x1A9C);
    short *digit3=fn_801A0310(sprite,0x1A9D);
    short *digit4=fn_801A0310(sprite,0x1A9E);
    short *digit5=fn_801A0310(sprite,0x1A9F);
    C8SetDigit(sprite,fn_80167744(0,time),digit0);
    C8SetDigit(sprite,fn_80167744(1,time),digit1);
    C8SetDigit(sprite,fn_80167744(2,time),digit2);
    C8SetDigit(sprite,fn_80167744(4,time),digit3);
    C8SetDigit(sprite,fn_80167744(5,time),digit4);
    C8SetDigit(sprite,fn_80167744(7,time),digit5);
    Sprite_SetAnimParam(sprite,0x13B9,0x13DE);
    Sprite_SetAnimParam(sprite,0x1E1D,0x1E20);
    Sprite_SetAnimParam(sprite,0x17A4,0x17A6);
    fn_801A0550(sprite);
    fn_8023CD3C(prompt.p,lbl_806D9EC0,lbl_806D9EC4);
    fn_8023CCF8(prompt.p,lbl_806D9EC8,lbl_806D9ECC);
    if(g_reverseRoundFlag==1) {
        box.p->sprite->layer=5;
        float x=fn_801D8D3C(g_cupId,g_longRoundFlag);
        box.p->sprite->x=x;
        box.p->sprite->y=lbl_806D9ED0;
        C8SpriteBox *p=box.p;
        if(p->enabled!=1 || p->mode!=0) { p->enabled=1;p->mode=0;p->timer=0; }
    }
    InitRumbleController(1);
}
