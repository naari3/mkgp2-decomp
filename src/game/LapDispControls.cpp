#include "game/FlowScene.h"
#include "game/types/clCDispInterface.h"
extern "C" {
extern const float lbl_806DBDD0, lbl_806DBDD4, lbl_806DBDC8, lbl_806DBDCC;
extern int g_longRoundFlag, g_countdownPhase;
void PreloadResource(int);
void fn_80121E10(ResCtrl *);
int SpriteHandle_CreateDefault(ResCtrl *, int);
void SpriteHandle_SetActiveFlag(int, int);
void SpriteHandle_RecomputeCull(int);
void SpriteLayer_SetResource(int, int);
void SpriteHandle_Destroy(int);
#include "game/types/tween_set_order.h"
void fn_8020A734(FlowFaderF *,int,float,float);
float fn_8020A6CC(FlowFaderF *);
void fn_8011F804(int,float,float);
void fn_8011F744(int,float,float);
}
static const float LapDispUpdate_rodata_803E5CE8[3][2] = {{530.0f,145.0f},{530.0f,145.0f},{530.0f,145.0f}};
static const float LapDispUpdate_rodata_803E5D00[3][2] = {{0.0f,0.0f},{44.0f,-14.0f},{73.0f,-4.0f}};
struct clLapDisp : clCDispInterface {
    virtual ~clLapDisp();
    virtual void Update();
    virtual void IsDone();
    virtual void SetTimeout(int);
    int layer;
    int sprites[3];
    int state, position;
    VHolder<FlowFaderF> fade, scale;
    int currentLap, totalLaps, currentLapFloor;
    clLapDisp(int, int);
    void SetCurrentLap(int);
    void SetTotalLaps(int);
};
clLapDisp::clLapDisp(int mode_, int layer_)
    : layer(layer_), state(-1), position(mode_),
      fade(new FlowFaderF(lbl_806DBDD0)), scale(new FlowFaderF(lbl_806DBDD0)),
      currentLap(0), currentLapFloor(1) {
    PreloadResource(0xB3B);
    PreloadResource(0xB3C);
    if (g_longRoundFlag == 1) totalLaps = 6;
    else totalLaps = 9;
    fade.p->Set(lbl_806DBDD4, lbl_806DBDD0, 7);
    scale.p->Set(lbl_806DBDC8, lbl_806DBDCC, 4);
    ResCtrl res;
    fn_80121E10(&res);
    res.resId = 0xB3B;
    for (int i = 0; i < 3; ++i) {
        sprites[i] = SpriteHandle_CreateDefault(&res, layer);
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    SpriteLayer_SetResource(sprites[0], 0xB3B);
}

clLapDisp::~clLapDisp() {
    for (int i = 0; i < 3; ++i) SpriteHandle_Destroy(sprites[i]);
}
extern "C" clLapDisp *fn_8023FB4C(int mode, int layer) { return new clLapDisp(mode, layer); }
void clLapDisp::SetCurrentLap(int currentLap) {
    int clamped = currentLap;
    if (currentLap > this->totalLaps) clamped = this->totalLaps;
    if (currentLap < this->currentLapFloor) clamped = this->currentLapFloor;
    if (clamped != this->currentLap) {
        this->currentLap = clamped;
        SpriteLayer_SetResource(sprites[1], this->currentLap + 0xB3B);
    }
}
void clLapDisp::SetTotalLaps(int totalLaps) {
    int clamped = totalLaps;
    if (totalLaps > 9) clamped = 9;
    if (totalLaps < 1) clamped = 1;
    this->totalLaps = clamped;
    SpriteLayer_SetResource(sprites[2], this->totalLaps + 0xB44);
}
void clLapDisp::Update() {
    switch(state) {
    case -1:
        if(g_countdownPhase<4) state=0;
        return;
    case 0:
        fade.p->Step();
        if(fade.p->Done()) state=1;
        break;
    case 1:
        if(g_countdownPhase<=2) { state=2; fn_8020A734(scale.p,4,lbl_806DBDC8,lbl_806DBDCC); }
        break;
    case 2:
        scale.p->Step();
        if(scale.p->Done()) { state=3; fn_8020A734(scale.p,4,lbl_806DBDCC,lbl_806DBDC8); }
        break;
    case 3:
        scale.p->Step();
        if(scale.p->Done()) state=4;
        break;
    case 5:
        fade.p->Step();
        if(fade.p->Done()) {
            state=6;
            for(int i=0;i<3;i++) { SpriteHandle_SetActiveFlag(sprites[i],0); SpriteHandle_RecomputeCull(sprites[i]); }
        }
        break;
    case 6: return;
    default: return;
    case 4: break;
    }
    if(id>0) {
        id--;
        if(id<=0) {
            id=0; state=5;
            fn_8020A734(fade.p,7,lbl_806DBDD0,lbl_806DBDD4);
        }
    }
    if(state!=4) {
        int position=this->position;
        float offset=fn_8020A6CC(fade.p);
        float scale=fn_8020A6CC(this->scale.p);
        for(int i=0;i<3;i++) {
            fn_8011F804(sprites[i],LapDispUpdate_rodata_803E5CE8[position][0]+LapDispUpdate_rodata_803E5D00[i][0]-offset,LapDispUpdate_rodata_803E5CE8[position][1]+LapDispUpdate_rodata_803E5D00[i][1]);
            fn_8011F744(sprites[i],scale,scale);
        }
    }
    for(int i=0;i<3;i++) { SpriteHandle_SetActiveFlag(sprites[i],1); SpriteHandle_RecomputeCull(sprites[i]); }
}
void clLapDisp::IsDone() { if (state == 6) return; }
void clLapDisp::SetTimeout(int time) { if (state < 5) id = time + 1; }
