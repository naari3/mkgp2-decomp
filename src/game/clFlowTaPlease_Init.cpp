#include "game/C8TaPleasePrivate.h"
// Shared scale, graph-coordinate, and animation-id tables.
static const float taScales[3] = {1.0f, 0.699999988079071f, 0.8999999761581421f};
static const float taGraph[18][7][2] = {
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 66.66667175292969f},
{1000.0f, 66.66667175292969f},
{2000.0f, 66.66667175292969f},
{3000.0f, 66.66667175292969f},
{4000.0f, 66.66667175292969f},
{5000.0f, 66.66667175292969f}
},
{
{0.0f, 0.0f},
{500.0f, 83.33333587646484f},
{1000.0f, 83.33333587646484f},
{2000.0f, 83.33333587646484f},
{3000.0f, 83.33333587646484f},
{4000.0f, 83.33333587646484f},
{5000.0f, 83.33333587646484f}
},
{
{0.0f, 0.0f},
{500.0f, 83.33333587646484f},
{1000.0f, 83.33333587646484f},
{2000.0f, 83.33333587646484f},
{3000.0f, 83.33333587646484f},
{4000.0f, 83.33333587646484f},
{5000.0f, 83.33333587646484f}
},
{
{0.0f, 0.0f},
{500.0f, 83.33333587646484f},
{1000.0f, 83.33333587646484f},
{2000.0f, 83.33333587646484f},
{3000.0f, 83.33333587646484f},
{4000.0f, 83.33333587646484f},
{5000.0f, 83.33333587646484f}
},
{
{0.0f, 0.0f},
{500.0f, 83.33333587646484f},
{1000.0f, 83.33333587646484f},
{2000.0f, 83.33333587646484f},
{3000.0f, 83.33333587646484f},
{4000.0f, 83.33333587646484f},
{5000.0f, 83.33333587646484f}
},
{
{0.0f, 0.0f},
{500.0f, 83.33333587646484f},
{1000.0f, 83.33333587646484f},
{2000.0f, 83.33333587646484f},
{3000.0f, 83.33333587646484f},
{4000.0f, 83.33333587646484f},
{5000.0f, 83.33333587646484f}
},
{
{0.0f, 0.0f},
{500.0f, 83.33333587646484f},
{1000.0f, 83.33333587646484f},
{2000.0f, 83.33333587646484f},
{3000.0f, 83.33333587646484f},
{4000.0f, 83.33333587646484f},
{5000.0f, 83.33333587646484f}
}
};
static const int taLabels[8][2][2] = {
{
{0xa94, 0xa95},
{0xa96, 0xa97}
},
{
{0xa78, 0xa79},
{0xa7a, 0xa7b}
},
{
{0xa6a, 0xa6b},
{0xa6c, 0xa6d}
},
{
{0xaa2, 0xaa3},
{0xaa4, 0xaa5}
},
{
{0xa86, 0xa87},
{0xa88, 0xa89}
},
{
{0xab0, 0xab1},
{0xab2, 0xab3}
},
{
{0xacc, 0xacd},
{0xace, 0xacf}
},
{
{0xac2, 0xac3},
{0xac4, 0xac5}
}
};
static const int taSymbols[8][2] = {
{0x1ab6, 0x1ab7},
{0x1aba, 0x1abb},
{0x1ac4, 0x1ac5},
{0x1ac6, 0x1ac7},
{0x1ac8, 0x1ac9},
{0x1aca, 0x1acb},
{0x1ab4, 0x1ab5},
{0x1ab8, 0x1ab9}
};
static const int taRounds[8][2] = {
{0x1e5b, 0x1e5d},
{0x1e53, 0x1e55},
{0x1e4f, 0x1e51},
{0x1e5f, 0x1e61},
{0x1e57, 0x1e59},
{0x1e63, 0x1e65},
{0x1e6b, 0x1e6d},
{0x1e67, 0x1e69}
};
static inline void SetTrackLabels(C8TaPlease *self, unsigned int round, int cup) {
    Sprite_SetAnimParam(self->sprite,0xA9C,(short)taLabels[cup][round][0]);
    Sprite_SetAnimParam(self->sprite,0xA9D,(short)taLabels[cup][round][1]);
    Sprite_SetAnimParam(self->sprite,0x1E5B,(short)taRounds[cup][round]);
    Sprite_SetAnimParam(self->sprite,0x1AB4,(short)taSymbols[cup][round]);
}
inline void C8SetDigit(AnimSprite *s, int value, short *digit) { Sprite_SetAnimParam(s,*digit,(short)(value+0x1A9A)); }
C8TaPlease::C8TaPlease() : prompt(new C8Prompt(0x74,-1,0x1872,-1,5)), box(new C8SpriteBox) {
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
    SetTrackLabels(this,g_longRoundFlag,g_cupId-1);
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
