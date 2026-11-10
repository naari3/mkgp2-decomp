#ifndef GAME_RACE_DIGITS_PRIVATE_H
#define GAME_RACE_DIGITS_PRIVATE_H
#define GAME_FLOWFADERF_DEFAULT_CTOR_OUT_OF_LINE
#include "game/FlowScene.h"
extern "C" {
extern const float lbl_806DBF28, lbl_806DBF2C, lbl_806DBF30, lbl_806DBF34, lbl_806DBF3C;
extern int g_gameMode, g_countdownPhase;
extern const int RaceDigits_data_806D0860[1];
extern float lbl_804EE8F0[3][10][2];
#include "game/types/DigitPosition.h"
extern DigitPosition lbl_804EE9E0[2][10];
#include "game/types/DigitMap.h"
extern const DigitMap RaceDigits_rodata_803EF800;
void PreloadResource(int);
void *SpriteHandle_CreateDefault(ResCtrl *, int);
void SpriteHandle_Destroy(void *);
void SpriteHandle_SetActiveFlag(void *, int);
void SpriteHandle_RecomputeCull(void *);
void SpriteLayer_SetResource(void *, int);
void fn_8011F804(void *, float, float);
void fn_8011F744(void *, float, float);
void fn_80121E10(ResCtrl *);
unsigned char IsRaceStarted();
int fn_8020A9EC(int, float);
}
struct DigitPanel {
    int layer;
    void *sprites[10];
    int state;
    unsigned char variant;
    VHolder<FlowFaderF> slide;
    VHolder<FlowFaderI> reveal;
    FlowFaderF *tweens;
    float offset, scale, number;
    DigitPosition position;
    DigitPanel(int);
    ~DigitPanel() {
        for(int i=0;i<10;i++) SpriteHandle_Destroy(sprites[i]);
        delete[] tweens;
    }
    void SetPos(const DigitPosition &v) { float a=v.x; float b=v.y; position.x=a; position.y=b; }
    void Update();
};
struct DigitOwner {
    DigitPanel *p;
#ifdef RACE_DIGITS_OUTLINE
    DigitOwner();
    DigitOwner(DigitPanel *q) : p(q) {}
    ~DigitOwner() throw();
#else
    DigitOwner() : p(0) {}
    ~DigitOwner() throw() { delete p; }
#endif
    void Reset(DigitPanel *q) throw() { if(p!=q) { delete p; p=q; } }
};
struct DigitNode { DigitNode *prev,*next; int value; };
struct DigitIter { DigitNode *node; DigitIter() {} DigitIter(DigitNode *p):node(p) {} };
struct DigitListBase {
    int count;
    DigitNode *last,*first;
    DigitListBase();
    DigitIter Erase(const DigitIter &, const DigitIter &);
#ifdef RACE_DIGITS_OUTLINE
    ~DigitListBase();
#else
    ~DigitListBase() { Erase(DigitIter(first),DigitIter((DigitNode *)&last)); }
#endif
};
struct DigitListMid : DigitListBase {
    DigitListMid() { Init(5,RaceDigits_data_806D0860); }
    ~DigitListMid() {}
    void Init(int,const int *);
};
struct DigitList : DigitListMid {
    ~DigitList();
};
struct DigitHudBase {
    virtual void Key();
    virtual ~DigitHudBase();
    int id;
    DigitHudBase():id(-1) {}
};
struct DigitHud : DigitHudBase {
    int layer;
    void *sprites[4];
    int state, mode;
    float offset,scale;
    VHolder<FlowFaderF> slide;
    int field30;
    DigitList list;
    DigitOwner main, others[5];
    DigitHud(int,int);
    virtual void Key();
};
#endif
