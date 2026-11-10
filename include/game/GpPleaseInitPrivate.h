#ifndef GAME_GP_PLEASE_INIT_PRIVATE_H
#define GAME_GP_PLEASE_INIT_PRIVATE_H
#include <list>
#include "game/clFlowCourse.h"
#include "game/FlowCardCheckScene.h"
#include "game/PanelCda40Private.h"
extern "C" {
extern void *clFlowGpPlease_vtable_8049B16C[], *lbl_8048EF20[];
extern int g_cupId, g_roundIndex;
extern unsigned char lbl_806D1264[3];
extern const float lbl_806D9E38, lbl_806D9E3C, lbl_806D9E40, lbl_806D9E44;
extern const float lbl_806D9E48, lbl_806D9E4C, lbl_806D9E50, lbl_806D9E54;
extern const float lbl_806D9E58, lbl_806D9E5C, lbl_806D9E60, lbl_806D9E64, lbl_806D9E68;
void SetSyncTarget(int);
void SetupBgSprites(int);
int fn_801D8DB4(int,int,int);
void Sprite_SetAnimParam(CourseSprite *,int,int);
void fn_801A0550(CourseSprite *);
int fn_801D8D8C(int);
int fn_801D8DA0(int);
void fn_80209C88();
void fn_80209AC4(int,int);
void fn_801D896C(void *,float,float);
void fn_801D898C(void *,int,int);
void fn_801D8AA0(void *,int);
void fn_801D8A98(void *,int);
}
struct GpTween {
    unsigned char active;
    float x,y,z,w,v;
    GpTween();
    void Set(float a,float b,float c,float d,float e) {
        x=a; y=b; z=c; w=d; v=e; active=1;
    }
};
struct GpPanelBase {
    virtual void _key();
    CourseSprite *sprite;
    int layer;
    GpTween tween[5];
    unsigned char state, flag;
    unsigned char pad86[2]; /* spelled out: other ABIs would put a derived member here (docs/notes/rtti_classes.md) */
    GpPanelBase(CourseSprite *s,int l):sprite(s),layer(l) {
        state=0; flag=0;
        tween[0].active=0; tween[1].active=0; tween[2].active=0;
        tween[3].active=0; tween[4].active=0;
    }
    void Fade() {
        tween[0].x=lbl_806D9E20; tween[0].y=lbl_806D9E24;
        tween[0].z=lbl_806D9E3C; tween[0].w=lbl_806D9E20;
        tween[0].v=lbl_806D9E20; tween[0].active=1;
    }
    ~GpPanelBase();
};
struct GpTextPayload { char opaque[0x160]; GpTextPayload(int); };
struct GpPayloadHolder {
    GpTextPayload *p;
    GpPayloadHolder(GpTextPayload *q):p(q){}
    ~GpPayloadHolder() throw();
};
struct GpTextPanel:GpPanelBase {
    virtual void _key();
    GpPayloadHolder holder;
    GpTextPanel(int id,int x):GpPanelBase(0,20),holder(new GpTextPayload(0)) {
        fn_801D896C(holder.p,(float)x,lbl_806D9E40);
        fn_801D898C(holder.p,id,1);
    }
};
struct GpLabelPanel:GpPanelBase {
    virtual void _key();
    short text;
    int textLayer;
    unsigned char field90;
    GpLabelPanel(int id,float x,float size):GpPanelBase(0,20) {
        text=id; textLayer=7; field90=0;
        tween[3].Set(x,x,lbl_806D9E24,lbl_806D9E20,x);
        tween[4].Set(size,size,lbl_806D9E24,lbl_806D9E20,size);
    }
};
struct GpColorPanel:GpPanelBase {
    virtual void _key();
    unsigned char rgb[4]; int colorLayer;
    GpColorPanel():GpPanelBase(0,15) {
        rgb[0]=60; rgb[1]=40; rgb[2]=10; colorLayer=1;
    }
};
/* The panel list is a std::list from the genuine MSL C++ header (docs/notes/msl_cpp.md). */
typedef std::list<GpPanelBase *> GpInitList;
struct clFlowGpPlease:clFlowProcess {
    virtual void _keyGp();
    GpInitList list;
    int timer;
    unsigned char active;
    int next;
    clFlowGpPlease();
};
typedef char GpPanelSizeCheck[sizeof(GpPanelBase)==0x88 ? 1 : -1];
typedef char GpTextSizeCheck[sizeof(GpTextPanel)==0x8c ? 1 : -1];
typedef char GpLabelSizeCheck[sizeof(GpLabelPanel)==0x94 ? 1 : -1];
typedef char GpColorSizeCheck[sizeof(GpColorPanel)==0x90 ? 1 : -1];
#endif
