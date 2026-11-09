#ifndef GAME_CLFLOWCOURSE_H
#define GAME_CLFLOWCOURSE_H
#include "game/FlowScene.h"

struct CourseSprite {
    void *vt;
    int layer;
    int field08;
    float x, y;
    float scaleX, scaleY, rotation, alpha;
    char pad24[0xC];
    CourseSprite(int, int, int);
    CourseSprite(int, int, float, float, float, float, float, float);
    ~CourseSprite();
};

struct CoursePulse {
    CourseSprite *sprite;
    unsigned char active, flag;
    char pad06[2];
    int timer;
    CoursePulse();
    ~CoursePulse() { delete sprite; }
};

struct CourseIcon {
    ResCtrl ctrl;
    int layer;
    int index;
    CourseIcon(int);
};

struct CourseBanner {
    int state, timer;
    ResCtrl main;
    ResCtrl labels[2];
    CourseBanner();
};

struct CourseBase {
#ifdef CLFLOWCOURSE_REAL_VTABLE
    /* The merged course TU (clFlowCourse.cpp) emits the real vtable and RTTI;
     * it renames CourseBase/CourseFlow to clFlowProcess/clFlowCourse. */
    CourseBase();
    virtual ~CourseBase();
#else
    virtual void _keyBase();
    CourseBase();
    ~CourseBase();
#endif
};

struct CourseSlot { CourseSprite *sprite; int field4; };
struct CourseFlow : CourseBase {
    unsigned char field04, advance, field06, pad07;
    int selection, state, timer;
    float field14, field18;
    int reverse, field20;
    CourseSlot slots[18];
    CourseSprite *left, *right, *fieldBC, *fieldC0, *fieldC4, *map;
    short *mapIdA, *mapIdB;
    ResCtrl preview;
    CourseSprite *field12C, *field130;
    CoursePulse *pulse;
    CourseSprite *field138, *field13C;
    unsigned char field140, field141, pad142[2];
    CourseIcon *icons[4];
    CourseBanner *banner;
    int selected;
    unsigned char field15C, field15D;
#ifdef CLFLOWCOURSE_REAL_VTABLE
    CourseFlow();
    virtual ~CourseFlow();
    virtual int Update();
    virtual void Draw();
#else
    virtual void _keyCourse();
    CourseFlow();
    ~CourseFlow();
#endif
};

extern "C" int fn_801D161C(int);
extern "C" void fn_801D1684(CourseBanner *);

typedef char CourseSpriteSizeCheck[sizeof(CourseSprite) == 0x30 ? 1 : -1];
typedef char CourseIconSizeCheck[sizeof(CourseIcon) == 0x60 ? 1 : -1];
typedef char CourseBannerSizeCheck[sizeof(CourseBanner) == 0x110 ? 1 : -1];
typedef char CourseFlowSizeCheck[sizeof(CourseFlow) == 0x160 ? 1 : -1];
#endif
