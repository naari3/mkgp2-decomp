/* Race HUD digit panels, animation and owning containers. */
/* RaceDigits.cpp owns the out-of-line DigitOwner and DigitListBase members.
 * The target emits them after DigitPanel's ctor, in this order:
 * ~DigitOwner, DigitOwner(), ~DigitList, ~DigitListBase. DigitHud's ctor
 * builds `main` with the inline pointer ctor, so DigitOwner() is not needed
 * (and not emitted) before then. defer_codegen at the tail lets ~DigitList
 * inline the later-defined ~DigitListBase while its copy still lands last. */
#define RACE_DIGITS_OUTLINE
#include "game/RaceDigitsMatchPrivate.h"
#pragma auto_inline off

#pragma push
#pragma optimization_level 3
DigitHud::DigitHud(int mode_, int layer_) : layer(layer_),state(-1),mode(mode_),
    offset(220.0f),scale(1.0f),slide(new FlowFaderF(0.0f)),field30(0),main(0) {
    PreloadResource(0xB53); PreloadResource(0xBD3);
    if(g_gameMode==1) { PreloadResource(0xBE5); PreloadResource(0xBF1); }
    {
    ResCtrl a;
    a.resId=0xBD3;
    sprites[2]=SpriteHandle_CreateDefault(&a,layer);
    }
    {
    ResCtrl b;
    if(g_gameMode==1) { b.resId=0xBF1; sprites[3]=SpriteHandle_CreateDefault(&b,layer); }
    else { b.resId=0xBD3; sprites[3]=SpriteHandle_CreateDefault(&b,layer); }
    }
    {
    ResCtrl c;
    c.resId=0xB52;
    sprites[0]=SpriteHandle_CreateDefault(&c,layer);
    }
    {
    ResCtrl d;
    d.resId=g_gameMode==1?0xBF0:0xB51;
    sprites[1]=SpriteHandle_CreateDefault(&d,layer);
    }
    for(int i=0;i<4;i++) {
        SpriteHandle_SetActiveFlag(sprites[i],0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    int variant=0;
    if(g_gameMode==1) variant++;
    main.Reset(new DigitPanel(layer));
    SetDigitPanelPosition(main.p,lbl_804EE9E0[variant][0]);
    main.p->variant=1;
    others[0].Reset(new DigitPanel(layer));
    SetDigitPanelPosition(others[0].p,lbl_804EE9E0[variant][1]);
    slide.p->Set(220.0f,0.0f,7);
}
#pragma pop

void DigitPanel::Update() {
    switch(state) {
    case -1:
        if(g_countdownPhase<4) state=0;
        return;
    case 0:
        offset=slide.p->Value(); slide.p->Step(); reveal.p->Step();
        for(int i=0;i<reveal.p->Value();i++) tweens[i].Step();
        if(tweens[9].Done()) { state=1; offset=0.0f; }
        break;
    case 1:
        if(g_countdownPhase<=2) {
            state=2; slide.p->Set(1.0f,1.2f,4);
        }
        break;
    case 2:
        scale=slide.p->Value(); slide.p->Step();
        if(slide.p->Done()) {
            state=3; slide.p->Set(1.2f,1.0f,4); scale=1.2f;
        }
        break;
    case 3:
        scale=slide.p->Value(); slide.p->Step();
        if(slide.p->Done()) { state=4; scale=1.0f; }
        break;
    case 4: break;
    case 5:
        offset=slide.p->Value(); slide.p->Step(); reveal.p->Step();
        for(int i=9;i>=reveal.p->Value();i--) tweens[i].Step();
        if(tweens[0].Done()) {
            state=6; offset=220.0f;
            for(int i=0;i<4;i++) {
                SpriteHandle_SetActiveFlag(sprites[i],0);
                SpriteHandle_RecomputeCull(sprites[i]);
            }
            return;
        }
        break;
    default: return;
    }
    DigitMap map=RaceDigits_rodata_803EF800;
    int style=0;
    if(g_gameMode==1) {
        style=1;
        if(variant==1) style=2;
    }
    int resource;
    for(int i=1;i<10;i++) {
        float size=scale;
        if(style==2) {
            if(map.digits[i]>=0) resource=fn_8020A9EC(map.digits[i],number)+0xBE5;
            else resource=0xBEF;
            if(i>=5) size*=0.7f;
        } else {
            if(map.digits[i]>=0) resource=fn_8020A9EC(map.digits[i],number)+0xB53;
            else resource=0xB5D;
        }
        float value=tweens[i].Value();
        fn_8011F804(sprites[i],position.x+lbl_804EE8F0[style][i][0]-value,position.y+lbl_804EE8F0[style][i][1]);
        fn_8011F744(sprites[i],size,size);
        SpriteLayer_SetResource(sprites[i],resource);
        SpriteHandle_SetActiveFlag(sprites[i],1);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}

DigitPanel::DigitPanel(int layer_) : layer(layer_),state(-1),variant(0),
    slide(new FlowFaderF(0.0f)),reveal(new FlowFaderI) {
    offset=220.0f; scale=1.0f;
    number=0.0f; position.x=0.0f; position.y=0.0f;
    PreloadResource(0xB3B);
    tweens=new FlowFaderF[10];
    if(!IsRaceStarted()) {
        slide.p->Set(220.0f,0.0f,7);
        for(int i=0;i<10;i++) tweens[i].Set(220.0f,1.0f,7);
        reveal.p->Set(0,10,20);
    } else {
        state=4; offset=0.0f;
        slide.p->Set(0.0f,0.0f,1);
        for(int i=0;i<10;i++) tweens[i].Set(0.0f,0.0f,1);
        reveal.p->Set(0,10,20);
    }
    ResCtrl ctrl;
    fn_80121E10(&ctrl);
    ctrl.flag=0; ctrl.x=0.0f; ctrl.y=0.0f; ctrl.z=1.0f;
    ctrl.resId=0xB53;
    for(int i=0;i<10;i++) {
        sprites[i]=SpriteHandle_CreateDefault(&ctrl,layer);
        SpriteHandle_SetActiveFlag(sprites[i],0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    SpriteHandle_SetActiveFlag(sprites[0],0);
}

DigitOwner::~DigitOwner() throw() { delete p; }
DigitOwner::DigitOwner() : p(0) {}
#pragma defer_codegen on
inline DigitListBase::~DigitListBase() { Erase(DigitIter(first),DigitIter((DigitNode *)&last)); }
DigitList::~DigitList() {}
