/* clRnkDisp: deferred definitions follow reverse target address order. */
#include "game/FlowScene.h"
#include "game/types/clCDispInterface.h"
extern "C" {
extern int g_countdownPhase;
extern const float lbl_806DBF58[2];
extern const float lbl_806DBF60,lbl_806DBF64,lbl_806DBF68,lbl_806DBF6C,lbl_806DBF70,lbl_806DBF74,lbl_806DBF78;
#include "game/types/tween_set_order.h"
void fn_8020A734(FlowFaderF *,int,float,float);
float fn_8020A6CC(FlowFaderF *);
int fn_8020A788(FlowFaderI *);
void fn_8020A7CC(FlowFaderI *,int,int,int);
void fn_80120A08(int);
void SpriteHandle_SetActiveFlag(int,int);
void SpriteHandle_RecomputeCull(int);
void SpriteHandle_SetCornerAlpha(int,unsigned char);
void SpriteLayer_SetResource(int,int);
void fn_8011F804(int,float,float);
void fn_8011F744(int,float,float);
void fn_8011F7AC(int,float);

extern const float lbl_806DBF7C;
void PreloadResource(int);
int SpriteHandle_CreateDefault(ResCtrl *, int);
void SpriteHandle_Destroy(int);
}
struct clRnkDisp : clCDispInterface {
    virtual ~clRnkDisp();
    virtual void Update();
    virtual void Draw();
    virtual void Finish();
    int layer;
    int sprites[2];
    int state, position;
    float offset;
    int countdown;
    VHolder<FlowFaderF> fade, scale, rotation;
    VHolder<FlowFaderI> alpha;
    clRnkDisp(int);
    void SetPosition(int);
};
clRnkDisp::clRnkDisp(int layer_)
    : layer(layer_), state(-1), position(0), offset(lbl_806DBF7C), countdown(0),
      fade(new FlowFaderF(lbl_806DBF60)), scale(new FlowFaderF(lbl_806DBF60)),
      rotation(new FlowFaderF(lbl_806DBF60)), alpha(new FlowFaderI) {
    PreloadResource(0xB23);
    fade.p->Set(lbl_806DBF7C, lbl_806DBF60, 7);
    scale.p->Set(lbl_806DBF64, lbl_806DBF64, 1);
    rotation.p->Set(lbl_806DBF60, lbl_806DBF60, 1);
    alpha.p->Set(0, 0, 1);
    ResCtrl res;
    res.resId = 0xB23;
    sprites[0] = SpriteHandle_CreateDefault(&res, layer);
    res.mode = 3;
    sprites[1] = SpriteHandle_CreateDefault(&res, layer);
    for (int i = 0; i < 2; ++i) {
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}
clRnkDisp::~clRnkDisp() {
    for (int i = 0; i < 2; ++i) SpriteHandle_Destroy(sprites[i]);
}
extern "C" clRnkDisp *fn_802499F4(int layer) {
    return new clRnkDisp(layer);
}
void clRnkDisp::SetPosition(int newPosition) {
    int p = newPosition;
    if (p >= 8) {
        p = 7;
    }
    if (p < 0) {
        p = 0;
    }
    if (position != p) {
        fn_8020A734(scale.p, 4, lbl_806DBF64, lbl_806DBF68);
    }
    position = p;
}
void clRnkDisp::Update() {
    switch(state) {
    case -1: if(g_countdownPhase<4) state=0; return;
    case 0:
        offset=fn_8020A6CC(fade.p);
        fade.p->Step();
        if(fade.p->Done()) { offset=lbl_806DBF60; state=1; }
        break;
    case 1:
        if(g_countdownPhase<=2) { fn_8020A734(scale.p,4,lbl_806DBF64,lbl_806DBF68); state=2; }
        break;
    case 2:
        if(scale.p->Done() && lbl_806DBF64==fn_8020A6CC(scale.p)) state=3;
        break;
    case 7:
        if(--countdown==0) { state=3; fn_8020A7CC(alpha.p,0,255,2); }
        break;
    case 4:
        if(scale.p->Done()) {
            state=5;
            fn_8020A734(scale.p,15,lbl_806DBF6C,lbl_806DBF70);
            fn_8020A734(rotation.p,1,lbl_806DBF60,lbl_806DBF60);
        }
        break;
    case 5:
        if(scale.p->Done()) { state=6; fn_8020A734(fade.p,5,lbl_806DBF70,lbl_806DBF74); }
        break;
    case 6:
        if(scale.p->Done()) {
            state=8;
            fn_80120A08(0xB23);
            for(int i=0;i<2;i++) { SpriteHandle_SetActiveFlag(sprites[i],0); SpriteHandle_RecomputeCull(sprites[i]); }
            return;
        }
        break;
    case 8: return;
    default: return;
    case 3: break;
    }
    if(id>0) {
        id--;
        if(id<=0) {
            id=0; state=4;
            fn_8020A734(scale.p,15,lbl_806DBF64,lbl_806DBF6C);
            fn_8020A734(rotation.p,15,lbl_806DBF60,lbl_806DBF78);
        }
    }
    int resource;
    int active=0;
    resource=position+0xB23;
    if(resource) {
        SpriteHandle_SetCornerAlpha(sprites[1],(unsigned char)fn_8020A788(alpha.p));
        float x=lbl_806DBF58[0]-offset;
        float y=lbl_806DBF58[1];
        active=1;
        float rotationValue=fn_8020A6CC(rotation.p);
        float scaleValue=fn_8020A6CC(scale.p);
        for(int i=0;i<2;i++) {
            SpriteLayer_SetResource(sprites[i],resource);
            fn_8011F804(sprites[i],x,y);
            fn_8011F744(sprites[i],scaleValue,scaleValue);
            fn_8011F7AC(sprites[i],rotationValue);
        }
    }
    for(int i=0;i<2;i++) { SpriteHandle_SetActiveFlag(sprites[i],active); SpriteHandle_RecomputeCull(sprites[i]); }
    scale.p->Step(); rotation.p->Step();
    if(scale.p->Done()) {
        float value=fn_8020A6CC(scale.p);
        if(lbl_806DBF68==value) fn_8020A734(scale.p,4,lbl_806DBF68,lbl_806DBF64);
        else if(lbl_806DBF64==value) fn_8020A734(scale.p,1,lbl_806DBF64,lbl_806DBF64);
    }
    alpha.p->Step();
    if(alpha.p->Done()) {
        unsigned char value=(unsigned char)fn_8020A788(alpha.p);
        if(value==255) fn_8020A7CC(alpha.p,255,0,2);
        else if(value==0) fn_8020A7CC(alpha.p,0,0,1);
    }
}

void clRnkDisp::Draw() { if (state == 8) return; }
void clRnkDisp::Finish() { if (state < 4) id = 1; }
