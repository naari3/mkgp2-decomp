#include "game/OptionMenuDrawPrivate.h"
#include "game/singleton.h"

// Shared curve, color and layout tables, followed by the scene text pool.
extern "C" const float SceneList_80157EA8_rodata_803678D8[255] = {
    1.0f, 0.699999988f, 0.899999976f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f,
    66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f,
    66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f,
    66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f,
    0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f,
    66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f,
    66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f,
    66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f,
    66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f,
    66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f,
    0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f,
    66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f,
    66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f,
    66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f,
    66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f,
    66.6666718f, 3000.0f, 66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f,
    0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f,
    66.6666718f, 4000.0f, 66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f,
    66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f,
    83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f, 83.3333359f, 5000.0f,
    83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f,
    83.3333359f, 3000.0f, 83.3333359f, 4000.0f, 83.3333359f, 5000.0f, 83.3333359f, 0.0f,
    0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f,
    83.3333359f, 4000.0f, 83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f,
    83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f,
    83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f, 83.3333359f, 5000.0f,
    83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f,
    83.3333359f, 3000.0f, 83.3333359f, 4000.0f, 83.3333359f, 5000.0f, 83.3333359f,
};

static const unsigned int optionColors[42] = {
    96, 255, 0, 200, 64, 0, 0, 96,
    255, 0, 96, 255, 0, 96, 255, 0,
    96, 255, 0, 96, 255, 0, 96, 255,
    0, 96, 255, 0, 96, 255, 0, 96,
    255, 0, 96, 255, 0, 96, 255, 0,
    96, 255,
};

static const float optionPositions[5] = {
    -153.0f, -105.0f, -59.0f, -15.0f, 32.0f,
};

static const float optionLayoutPositions[10] = {
    -17.0f, 69.0f, 155.0f, 241.0f, 337.0f, -17.0f, 49.0f, 135.0f,
    221.0f, 307.0f,
};

static const int optionThresholds[17] = {
    3, 5, 7, 10, 15, 20, 25, 30,
    35, 40, 45, 50, 60, 70, 80, 90,
    100,
};

extern "C" const char lbl_80367DFC[] = "clCSSceneCardBrowse";

extern "C" const char lbl_80367E10[] = "clSceneInterface";

extern "C" const char lbl_80367E24[] = "Time attack record";

extern "C" const char lbl_80367E38[] = "\203^\203C\203\200\203A\203^\203b\203N\201@\203f\201[\203^";

static const char optionText578[] = "Versus race result";

static const char optionText58C[] = "\221\316\220\355\220\254\220\321\201@\203f\201[\203^";

static const char optionText5A0[] = "Versus Race count %03d";

static const char optionText5B8[] = "Number of Wins %03d";

static const char optionText5CC[] = "\221\316\220\355\203\214\201[\203X\220\224";

static const char optionText5DC[] = "\227D\217\237\211\361\220\224";

static const char optionText5E8[] = "Grand Prix mode";

static const char optionText5F8[] = "\203O\203\211\203\223\203v\203\212\203\202\201[\203h\201@\203f\201[\203^";

static const char optionText614[] = "Number of item(s) received %02d/%d";

static const char optionText638[] = "\203A\203C\203e\203\200\212l\223\276\220\224%02d";

static const char optionText64C[] = "\201^%d\214\302\222\206";

static const char optionText658[] = "\212\356\226{\203f\201[\203^";

static const char optionText664[] = "\211\271\227\312\202\360\225\317\215X\202\305\202\253\202\334\202\267\201B";

static const char optionText67C[] = "clCSPartsInerface";



static inline RankLog *GetRankLog() {
    return SINGLETON_INSTANCE(lbl_806D10A0);
}

struct OptionDrawPoint { float x, y; };

extern "C" void fn_8015A6E4(OptionDrawScene *self, int layer, float x, float y, float alpha) {
    OptionDrawPoint rowOrigin;
    float nameX, rowY, imageX, nameY, titleY;
    float pulseScale, pulseAlpha;
    const float *positions;
    int count, i;
    const char *title;
    if (isJapanese() == 1) {
        fn_80168798(layer, lbl_806D8574, lbl_806D83D4+x, lbl_806D83D0+y, alpha);
        fn_80168D84(layer, lbl_806D83E4, lbl_806D83DC+x, lbl_806D83E0+y, alpha);
    } else {
        fn_80168798(layer, optionText658, lbl_806D83CC+x, titleY=lbl_806D83D0+y, alpha);
        fn_80168798(layer, lbl_806D8574, lbl_806D83EC+x, titleY, alpha);
        fn_80168D84(layer, lbl_806D83F0, lbl_806D83DC+x, lbl_806D83E0+y, alpha);
    }
    const char *texture = GetTextureByIdAndLang(0x46,-1);
    fn_80168D84(layer, texture, lbl_806D83B4+x, titleY=lbl_806D8578+y, alpha);
    texture = fn_8013C26C(self->texture,-1);
    fn_80168798(layer, texture, lbl_806D84E8+x, nameY=lbl_806D8454+y, alpha);
    fn_8013C7B0(self->preview,lbl_806D857C+x,lbl_806D8580+y);
    fn_8013C5FC(self->preview,lbl_806D8584);
    fn_8013C674(self->preview,lbl_806D8588);
    fn_8013C6EC(self->preview,lbl_806D858C,lbl_806D858C,lbl_806D858C);
    fn_8013C4A4(self->preview,alpha);
    fn_8013C91C(self->preview);
    fn_8013DAC8(self->preview,layer);
    texture=GetTextureByIdAndLang(0x44,-1);
    imageX=lbl_806D8590+x;
    fn_80168D84(layer,texture,imageX,titleY,alpha);
    nameX=lbl_806D83D4+x;
    fn_80167C60(layer,self->target,nameX,lbl_806D8594+y,alpha);
    fn_80168D84(layer,GetTextureByIdAndLang(0x45,-1),imageX,lbl_806D8598+y,alpha);
    RankLog *global=GetRankLog();
    title=lbl_806D859C;
    if (global) title=get_title_name_global(global);
    if (isJapanese()==1)
        fn_80168404(layer,title,nameX,nameY,lbl_806D83B0,lbl_806D83B0,alpha);
    else
        fn_80168404(layer,title,nameX,nameY,lbl_806D85A0,lbl_806D83B0,alpha);
    fn_80168D84(layer,GetTextureByIdAndLang(0x48,-1),imageX,lbl_806D85A4+y,alpha);
    count=self->target->count-1;
    count=count & (((unsigned int)count >> 31)-1);
    fn_80168798(layer,GetTextureByIdAndLang(0x49,-1),nameX,lbl_806D85A8+y,alpha,count);
    rowOrigin.x=lbl_806D85AC+x;
    fn_801695E0(layer,0x643,0,rowOrigin.x,lbl_806D85B0+y,alpha);
    if (self->toggle) {
        fn_801695E0(layer,0x67D,0,lbl_806D85B4+x,rowY=lbl_806D85B8+y,alpha);
        fn_801695E0(layer,0x67C,0,lbl_806D85BC+x,rowY,alpha);
    } else {
        fn_801695E0(layer,0x67B,0,lbl_806D85B4+x,rowY=lbl_806D85B8+y,alpha);
        fn_801695E0(layer,0x67E,0,lbl_806D85BC+x,rowY,alpha);
    }
    OptionDrawPanel *panel=self->panel38;
    if(layer>=0 && layer<8)panel->layer=layer;
    panel=self->panel38; panel->x=lbl_806D85C0+x;panel->y=lbl_806D85C4+y;
    self->panel38->alpha=alpha;
    self->panel38->Draw();
    rowY=lbl_806D8504+y;
    fn_801695E0(layer,0x642,0,rowOrigin.x,rowY,alpha);
    rowOrigin.y=lbl_806D8410+rowY;
    positions=optionPositions;
    for(i=0;i<5;i++,positions++) {
        if(self->selection==i)
            fn_801695E0(layer,0x676+i,0,rowOrigin.x+*positions,rowOrigin.y,alpha);
        else
            fn_801695E0(layer,0x671+i,0,rowOrigin.x+*positions,rowOrigin.y,alpha);
    }
    if(self->fade50<lbl_806D8398) {
        texture=GetTextureByIdAndLang(0x4B,-1);
        fn_80168B90(layer,texture,lbl_806D85C8+x,rowY,lbl_806D83B0,0.0f,0.0f,alpha);
    } else if(isJapanese()==0)
        fn_80168D84(layer,optionText664,lbl_806D85C8+x,rowY,alpha);
    panel=self->panel3C;
    if(layer>=0 && layer<8)panel->layer=layer;
    panel=self->panel3C;panel->x=lbl_806D85CC+x;panel->y=lbl_806D83D4+y;
    self->panel3C->alpha=alpha;
    self->panel3C->Draw();
    if(self->fade54<lbl_806D839C) {
        float t=self->fade54;
        if(t<10.0f) {
            pulseAlpha=t/10.0f;
            pulseScale=0.5f+(0.5f*t)/10.0f;
        } else if(t<lbl_806D855C) {
            float fraction=(t-10.0f)/10.0f;
            pulseScale=lbl_806D83B0+fraction;
            pulseAlpha=lbl_806D83B0-fraction;
        }
        fn_80169334(layer,0x67F,0,rowOrigin.x+optionPositions[self->selection],rowOrigin.y,pulseScale,pulseScale,pulseAlpha*alpha);
        t=self->fade54;
        if(t>lbl_806D8418) {
            if(t<lbl_806D83B8) {
                float d=t-lbl_806D8418;
                pulseAlpha=d/lbl_806D8428;
                pulseScale=lbl_806D8414+(lbl_806D8414*d)/lbl_806D8428;
            } else if(t<lbl_806D839C) {
                float fraction=(t-lbl_806D83B8)/lbl_806D8428;
                pulseScale=lbl_806D83B0+fraction;
                pulseAlpha=lbl_806D83B0-fraction;
            }
            fn_80169334(layer,0x67F,0,rowOrigin.x+optionPositions[self->selection],rowOrigin.y,pulseScale,pulseScale,pulseAlpha*alpha);
        }
    }
}
