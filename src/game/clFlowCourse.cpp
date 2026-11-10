/* Course select flow (0x801CE800..0x801D1800): one TU.
 * The TU owns .data 0x8049B1E0..0x8049B4A8 (row layouts, row animations,
 * cup map ids, then the compiler's RTTI/vtable and jump tables), .rodata
 * 0x8039B990..0x8039BF88 and the RTTI .sdata. clFlowCourse_Init addresses
 * the row table and the vtable off one pooled .data base.
 * Each former file keeps its own declarations in a namespace. */
#define CourseFlow clFlowCourse
#define CourseBase clFlowProcess
#define CLFLOWCOURSE_REAL_VTABLE
#include "game/clFlowCourse.h"
#include "game/singleton.h"
#include "game/CreditHud.h"

namespace course_rows {
#include "game/C8CourseRowsPrivate.h"
}
#ifndef __MWERKS__ /* defined at the end of the file; declared here for the views in course_update */
namespace course_rows { extern "C" { int fn_801CEB78(CourseRows *self, int index, int state); int fn_801CE918(CourseRows *self, int index); } }
#endif

/* === .data 0x8049B1E0 === */
namespace course_data {
using course_rows::RowLayout;
using course_rows::RowAnimation;
extern "C" {
RowLayout clFlowCourse_data_8049B1E0[18] = {
    {0x19DC, 0x19E0, 0x19DE, 0, 92.0f, 260.0f, 245.0f},
    {0x19DD, 0x19E1, 0x19DF, 0, 158.0f, 168.0f, 188.0f},
    {0x19AC, 0x19B0, 0x19AF, 0, 214.0f, 260.0f, 245.0f},
    {0x19AD, 0x19B1, 0x19AE, 0, 282.0f, 168.0f, 188.0f},
    {0x19D1, 0x19D4, 0x19D2, 0, 336.0f, 260.0f, 245.0f},
    {0x19D0, 0x19D5, 0x19D3, 0, 404.0f, 168.0f, 188.0f},
    {0x1994, 0x1998, 0x1996, 0, 458.0f, 260.0f, 245.0f},
    {0x1995, 0x1999, 0x1997, 0, 526.0f, 168.0f, 188.0f},
    {0x1988, 0x198C, 0x198A, 0, 742.0f, 168.0f, 188.0f},
    {0x1989, 0x198D, 0x198B, 0, 818.0f, 260.0f, 245.0f},
    {0x19B8, 0x19BC, 0x19BA, 0, 874.0f, 168.0f, 188.0f},
    {0x19B9, 0x19BD, 0x19BB, 0, 932.0f, 260.0f, 245.0f},
    {0x19A0, 0x19A4, 0x19A2, 0, 986.0f, 168.0f, 188.0f},
    {0x19A1, 0x19A5, 0x19A3, 0, 1054.0f, 260.0f, 245.0f},
    {0x19C4, 0x19C8, 0x19C6, 0, 1108.0f, 168.0f, 188.0f},
    {0x19C5, 0x19C9, 0x19C7, 0, 1176.0f, 260.0f, 245.0f},
    {0, 0, 0, 0, 0.0f, 0.0f, 0.0f},
    {0, 0, 0, 0, 0.0f, 0.0f, 0.0f}
};
RowAnimation clFlowCourse_data_8049B348[8] = {
    {0, 1.0f}, {34, 1.0f}, {151, 1.0f}, {152, 1.0f},
    {150, 1.0f}, {364, 0.6f}, {440, 0.6f}, {113, 0.6f}
};
short clFlowCourse_data_8049B388[8][2] = {
    {0x1777, 0x1780}, {0x1778, 0x1781}, {0x1779, 0x1782}, {0x177A, 0x1783},
    {0x177B, 0x1784}, {0x177C, 0x1785}, {0x177D, 0x1786}, {0x177E, 0x1787}
};
}
}

namespace course_sel {
extern "C" {
/* Course select: applies the cup/variant pair at index and loads its course. */
typedef struct CupNames {
    short first;
    short second;
} CupNames;

typedef struct CourseSel {
    char pad0[0xCC];
    short *nameA;
    short *nameB;
    int course;
    char padD8[0xC];
    unsigned char dirty;
    float fadeE8;
    float fadeEC;
    float fadeF0;
} CourseSel;

#ifdef __MWERKS__
extern CupNames clFlowCourse_data_8049B388[8];
#else /* this namespace sees clFlowCourse_data_8049B388 with another type: a view of the same object */
static CupNames *const clFlowCourse_data_8049B388 = (CupNames *)course_data::clFlowCourse_data_8049B388;
#endif
void fn_80121E10(void *ctrl);
short GetCourseShortIdByCupAndMirror(int cup, int mirror);

}
}
namespace course_draw {
extern "C" {
typedef struct Sprite Sprite;
typedef struct ResCtrl ResCtrl;

typedef struct OptSprite {
    Sprite *sprite;
    unsigned char visible;
} OptSprite;

typedef struct LayeredCtrl {
    char pad0[0x58];
    int layer;
} LayeredCtrl;

typedef struct LinkBanner {
    int state;
    int pad4;
    char ctrl0[0x58];
    char ctrl1[0x58];
    char ctrl2[0x58];
} LinkBanner;

typedef struct ItemSlot {
    Sprite *sprite;
    int pad4;
} ItemSlot;

typedef struct ItemSelectView {
    char pad000[8];
    int selected;
    char pad00C[0x24 - 0xC];
    ItemSlot items[18];
    Sprite *bg;
    Sprite *frame;
    Sprite *title;
    Sprite *cursor;
    Sprite *arrowL;
    Sprite *arrowR;
    char pad0CC[0xD4 - 0xCC];
    char fade[0x12C - 0xD4];
    Sprite *help;
    Sprite *timer;
    OptSprite *badge;
    Sprite *extra0;
    Sprite *extra1;
    unsigned char showExtra0;
    unsigned char showExtra1;
    char pad142[2];
    LayeredCtrl *players[4];
    LinkBanner *banner;
} ItemSelectView;

extern int g_gameMode;
extern void fn_801A0004(Sprite *s);
extern void fn_8011FAFC(void *ctrl, int layer);

}
}
#include "game/clFlowCourse_Update_private.h"
namespace course_update {

/* clFlowCourse_Update, 801CF360..801D0C30 (6352 bytes).
 * Complete state-machine draft, retained as Object(NonMatching).
 * The four allocation guards use real C++ new expressions. */

struct CourseLayout {
    short id, field02;
    int field04;
    float x, y, field10;
};
struct ArrowLayout { float x, y, angle, x2, y2, angle2; };
struct CourseParams { int cup, round, field08; };
struct CoursePlayerInput {
    virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24();
    virtual void slot28(); virtual unsigned int Test(int);
};
/* Shared constant pool, 8039B990..8039BF3C. The leading three scales and
 * eighteen seven-key XY curves are also read by the course slot helpers.
 * Keeping each table distinct lets MWCC address it from one pooled base. */
static const float motionCurves[255] = {
        1.0f, 0.699999988f, 0.899999976f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f,
    };
static const float iconOffsets[4][2] = { { -28.0f, -28.0f }, { 28.0f, -28.0f }, { -28.0f, 28.0f }, { 28.0f, 28.0f } };
static const short animIds[8] = { 6511, 6512, 6513, 6514, 6515, 6516, 6517, 6518 };
static const ArrowLayout courseArrows[16] = {
        { 0.0f, 0.0f, 0.0f, 145.0f, 185.0f, -50.0f },
        { 115.0f, 225.0f, 130.0f, 205.0f, 225.0f, 50.0f },
        { 170.0f, 185.0f, -130.0f, 260.0f, 185.0f, -50.0f },
        { 240.0f, 225.0f, 130.0f, 330.0f, 225.0f, 50.0f },
        { 295.0f, 185.0f, -130.0f, 385.0f, 185.0f, -50.0f },
        { 365.0f, 225.0f, 130.0f, 455.0f, 225.0f, 50.0f },
        { 420.0f, 185.0f, -130.0f, 510.0f, 185.0f, -50.0f },
        { 490.0f, 225.0f, 130.0f, 580.0f, 225.0f, 50.0f },
        { 60.0f, 225.0f, 130.0f, 150.0f, 225.0f, 50.0f },
        { 134.0f, 185.0f, -130.0f, 224.0f, 185.0f, -50.0f },
        { 192.0f, 225.0f, 130.0f, 282.0f, 225.0f, 50.0f },
        { 248.0f, 185.0f, -130.0f, 338.0f, 185.0f, -50.0f },
        { 284.0f, 225.0f, 130.0f, 394.0f, 225.0f, 50.0f },
        { 372.0f, 185.0f, -130.0f, 460.0f, 185.0f, -50.0f },
        { 426.0f, 225.0f, 130.0f, 516.0f, 225.0f, 50.0f },
        { 492.0f, 185.0f, -130.0f, 0.0f, 0.0f, 0.0f },
    };

extern "C" {
#ifdef __MWERKS__
extern CourseLayout clFlowCourse_data_8049B1E0[];
#else /* this namespace sees clFlowCourse_data_8049B1E0 with another type: a view of the same object */
static CourseLayout *const clFlowCourse_data_8049B1E0 = (CourseLayout *)course_data::clFlowCourse_data_8049B1E0;
#endif
extern short clFlowCourse_data_8049B388[][2];
extern int g_gameMode, g_roundIndex, g_localPcbRole, lbl_806CF12C;
extern signed char lbl_806D184C, lbl_806D184D;
extern unsigned char g_playerData[];
void RumbleUpdate();
#ifdef __MWERKS__
void fn_801CEB78(CourseFlow *, int, int);
void fn_801CE918(CourseFlow *, int);
#else /* this namespace declares them with other types: views of the same functions */
static inline void fn_801CEB78(CourseFlow *a0, int a1, int a2) { ((void (*)(CourseFlow *, int, int))&course_rows::fn_801CEB78)(a0, a1, a2); }
static inline void fn_801CE918(CourseFlow *a0, int a1) { ((void (*)(CourseFlow *, int))&course_rows::fn_801CE918)(a0, a1); }
#endif
#ifdef __MWERKS__
void Sprite_SetAnimParam(CourseSprite *, int, short);
#else /* this namespace declares Sprite_SetAnimParam with other types: a view of the same object */
static inline void Sprite_SetAnimParam(CourseSprite * a0, int a1, short a2) { ((void (*)(CourseSprite *, int, short))&course_rows::Sprite_SetAnimParam)(a0, a1, a2); }
#endif
#ifdef __MWERKS__
void Sprite_SetupAnim(CourseSprite *, int, int, int);
#else /* this namespace declares Sprite_SetupAnim with other types: a view of the same object */
static inline void Sprite_SetupAnim(CourseSprite * a0, int a1, int a2, int a3) { ((void (*)(CourseSprite *, int, int, int))&course_rows::Sprite_SetupAnim)(a0, a1, a2, a3); }
#endif
#ifdef __MWERKS__
unsigned char Sprite_AdvanceAnim(CourseSprite *, float);
#else /* this namespace declares Sprite_AdvanceAnim with other types: a view of the same object */
static inline unsigned char Sprite_AdvanceAnim(CourseSprite * a0, float a1) { return (unsigned char)((unsigned char (*)(CourseSprite *, float))&course_rows::Sprite_AdvanceAnim)(a0, a1); }
#endif
#ifdef __MWERKS__
void fn_801A0550(CourseSprite *);
#else /* this namespace declares fn_801A0550 with other types: a view of the same object */
static inline void fn_801A0550(CourseSprite * a0) { ((void (*)(CourseSprite *))&course_rows::fn_801A0550)(a0); }
#endif
#ifdef __MWERKS__
void fn_8019FF6C(CourseSprite *, int);
#else /* this namespace declares fn_8019FF6C with other types: a view of the same object */
static inline void fn_8019FF6C(CourseSprite * a0, int a1) { ((void (*)(CourseSprite *, int))&course_rows::fn_8019FF6C)(a0, a1); }
#endif
#ifdef __MWERKS__
void fn_80121E10(ResCtrl *);
#else /* this namespace declares fn_80121E10 with other types: a view of the same object */
static inline void fn_80121E10(ResCtrl * a0) { ((void (*)(ResCtrl *))&course_sel::fn_80121E10)(a0); }
#endif
short GetCourseShortIdByCupAndMirror(int, int);
void fn_801699D8(int, int);
void fn_801B7CAC();
void fn_801B7C64();
void *GetInputManager();
CoursePlayerInput *InputMgr_GetPlayer(void *, int);
void SetScreenBrightness(float);
void SetRumbleMode(int, int, int);
CourseParams *GetCourseSelectEntry(int);
int SetCourseParams(int, int, int, int);
void SetSyncTarget(int);
unsigned char IsSyncReached();
unsigned char *SyncSlot_GetRecv();
int GetDisplayBufferIndex();
CourseRecvSlot *PcbSlot_GetByIndex(int);
}

static inline InputState *CourseInput() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline void SetSpritePosition(CourseSprite *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

static inline void SetAlpha(ResCtrl *ctrl, unsigned int color, float a) {
    color = ((color) & 0xFFFFFF00 | (unsigned char)((int)((255.0f) * a)));
    ctrl->SetColor(color);
}

static inline int CourseCup(int i) {
    switch (i) {
    case 0: return 7; case 1: return 1; case 2: return 8; case 3: return 2;
    case 4: return 3; case 5: return 4; case 6: return 5; case 7: return 6;
    default: return 1;
    }
}
static inline void UpdatePreview(CourseFlow *self, int selection) {
    int cup = selection / 2;
    *self->mapIdA = clFlowCourse_data_8049B388[cup][0];
    *self->mapIdB = clFlowCourse_data_8049B388[cup][1];
    fn_80121E10(&self->preview);
    self->preview.resId = GetCourseShortIdByCupAndMirror(CourseCup(cup), selection % 2);
    self->preview.Show((265.0f), (388.0f), (1.0f));
}
static inline void UpdateArrows(CourseFlow *self, const ArrowLayout *arrows) {
    self->field140 = 0;
    if (self->field138) {
        float y;
        float x = arrows[self->selection].x;
        y = arrows[self->selection].y;
        SetSpritePosition(self->field138, x, y);
        self->field138->rotation = arrows[self->selection].angle;
        if (self->selection != 0) self->field140 = 1;
    }
    self->field141 = 0;
    if (self->field13C) {
        float y;
        float x = arrows[self->selection].x2;
        y = arrows[self->selection].y2;
        SetSpritePosition(self->field13C, x, y);
        self->field13C->rotation = arrows[self->selection].angle2;
        if (self->selection != 15) self->field141 = 1;
        if (self->field15D == 1 && self->selection == 7) self->field141 = 0;
    }
}
static inline void ActivatePulse(CoursePulse *p) {
    if ( (p->active != 1 || p->flag != 0)) {
        p->active = 1; p->flag = 0; p->timer = 0;
    }
}
static inline void DeactivatePulse(CoursePulse *p) {
    if (p->active != 0 && p->flag != 1) {
        p->flag = 1; p->timer = 0;
    }
}
static inline void ShowPulse(CoursePulse *p) { if (p) ActivatePulse(p); }
static inline void HidePulse(CoursePulse *p) { if (p) DeactivatePulse(p); }
extern "C" const float lbl_806D9F30;
static inline float PulseAlpha(CoursePulse *p) {
    if (p->flag == 0) return (float)p->timer * lbl_806D9F30;
    return (1.0f) - (float)p->timer * (0.125f);
}
static inline void SetupExitSprites(CourseFlow *self) {
    if (self->left) Sprite_SetupAnim(self->left, 0x23, 1, 0);
    if (self->right) Sprite_SetupAnim(self->right, 0x26, 1, 0);
    if (self->fieldC4) {
        Sprite_SetupAnim(self->fieldC4, 0x83, 1, 0);
        Sprite_SetAnimParam(self->fieldC4, 0x1970, animIds[self->selection / 2]);
    }
}

}

/* 801D0C30..801D1800: indivisible reversed-extab group.
 * Native C++ draft; retain Object(NonMatching) until all four functions and
 * their EH records match. The constructor's original pooled-data base and
 * the destructor/fader register identities still differ. */

struct CourseResource { short id; char pad02[18]; };
#include "game/types/CourseData.h"
extern "C" {
extern int g_gameMode, g_cupId, g_roundIndex, g_longRoundFlag, g_ccClass;
extern int lbl_806CF12C;
void fn_80169C44();
void SetScreenBrightness(float);
void SetReverseRoundFlag(int);
void fn_801B87D8();
void fn_801A1678();
void SpriteSystem_EnsureInit();
unsigned char PCBComm_PackAndTriggerCardSnapshot();
void DebugPrintf(const char *, ...);
void PreloadResource(int);
void SetSyncTarget(int);
short *fn_801A0310(CourseSprite *, int);
#ifdef __MWERKS__
void fn_80121E10(ResCtrl *);
#else /* declared above as fn_80121E10(void *): a view of the same function */
static inline void fn_80121E10(ResCtrl *a0) { ((void (*)(ResCtrl *))&course_sel::fn_80121E10)(a0); }
#endif
short GetCourseShortIdByCupAndMirror(int, int);
int fn_801B8918(int);
void InitBGM();
int SetupBgSprites(unsigned char);
void InitRumbleController(int);
}

static inline void FlowSetSpritePosition(CourseSprite *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

static inline int FlowCourseCup(int i) {
    switch (i) {
    case 0: return 7;
    case 1: return 1;
    case 2: return 8;
    case 3: return 2;
    case 4: return 3;
    case 5: return 4;
    case 6: return 5;
    case 7: return 6;
    default: return 1;
    }
}

inline CoursePulse::CoursePulse() {
    active = 0; flag = 0; timer = 0;
    sprite = new CourseSprite(0x9E, 1, (394.0f), (394.0f),
        (1.0f), (1.0f), (0.0f), (0.0f));
}
inline CourseIcon::CourseIcon(int n) {
    layer = 5;
    index = n;
    ctrl.resId = (short)(index + 0x1EC5);
    ctrl.Show((-3e+02f), (-3e+02f), (1.0f));
    ctrl.SetColor(0xFFFFFF00);
}
inline CourseBanner::CourseBanner() : state(3), timer(0) {
    main.mode = 2;
    main.width = (6.4e+02f);
    main.height = (4.8e+02f);
    main.Show((3.2e+02f), (2.4e+02f), (1.0f));
    labels[0].resId = 0x1B12;
    labels[0].Show((3.2e+02f), (2.4e+02f), (1.0f));
    labels[1].resId = 0x1B13;
    labels[1].Show((3.2e+02f), (232.0f), (1.0f));
    main.SetColor(0);
    labels[0].SetColor(0xFFFFFF00);
    labels[1].SetColor(0xFFFFFF00);
}

static inline int FadeAlpha(int timer) {
    return (int)((255.0f) * ((float)timer / (5.0f)));
}
static inline int FadeOutAlpha(int timer) {
    return (int)((255.0f) * ((1.0f) - (float)timer / (5.0f)));
}
static inline void ApplyAlpha(CourseBanner *self, unsigned int color, int alpha) {
    self->main.SetColor((alpha >> 1) & 0x7F);
    color = __rlwimi(color, alpha, 0, 24, 31);
    self->labels[0].SetColor(color);
    self->labels[1].SetColor(color);
}
static inline void ApplyAlpha2(CourseBanner *self, unsigned int color, int alpha) {
    self->main.SetColor((alpha >> 1) & 0x7F);
    unsigned int c = __rlwimi(color, alpha, 0, 24, 31);
    self->labels[0].SetColor(c);
    self->labels[1].SetColor(c);
}
static inline void ApplyAlpha3(CourseBanner *self, int alpha, unsigned int color) {
    self->main.SetColor((alpha >> 1) & 0x7F);
    color = __rlwimi(color, alpha, 0, 24, 31);
    self->labels[0].SetColor(color);
    self->labels[1].SetColor(color);
}

/* With -inline deferred CW generates the functions at the end of the TU in
 * reverse source order, so they are defined here from last to first. */
#pragma push
#pragma dont_inline on
extern "C" void fn_801D1684(CourseBanner *self) {
    if (self->state == 3) return;
    switch (self->state) {
    case 0: {
        unsigned int color = 0xFFFFFF00;
        unsigned int alpha = FadeAlpha(self->timer);
        self->main.SetColor((alpha >> 1) & 0x7F);
        color = ((color) & 0xFFFFFF00 | (unsigned char)(alpha));
        self->labels[0].SetColor(color);
        self->labels[1].SetColor(color);
        if (self->timer >= 5) { self->timer = 0; self->state = 1; }
        break;
    }
    case 2: {
        unsigned int color = 0xFFFFFF00;
        unsigned int alpha = FadeOutAlpha(self->timer);
        self->main.SetColor((alpha >> 1) & 0x7F);
        color = ((color) & 0xFFFFFF00 | (unsigned char)(alpha));
        self->labels[0].SetColor(color);
        self->labels[1].SetColor(color);
        if (self->timer >= 5) { self->timer = 0; self->state = 3; }
        break;
    }
    case 1: goto tick;
    }
tick:
    self->timer++;
}

#pragma pop
extern "C" int fn_801D161C(int i) { return FlowCourseCup(i); }

CourseFlow::CourseFlow() {
    int cup;
    int sel;
    int i;
    short (*mapIds)[2];
    SpriteSystem_EnsureInit();
    if (!PCBComm_PackAndTriggerCardSnapshot())
        DebugPrintf("Send card error!!  - %s %d\n", "flow_course.cpp", 0xA1);
    for (i = 0; i < 9; i++) {
        PreloadResource(course_data::clFlowCourse_data_8049B1E0[i].a);
        PreloadResource(course_data::clFlowCourse_data_8049B1E0[i].a + 6);
    }
    PreloadResource(0x196F); PreloadResource(0x197C);
    PreloadResource(0x1777); PreloadResource(0x178B);
    PreloadResource(0x1715); PreloadResource(0x171A);
    PreloadResource(0x171F); PreloadResource(0x1724);
    PreloadResource(0x1946); PreloadResource(0x1948);
    PreloadResource(0x1DEC); PreloadResource(0x1863);
    PreloadResource(0x18BA); PreloadResource(0x1EC5);
    PreloadResource(0x1EC9); PreloadResource(0x1B12); PreloadResource(0x1B14);
    if (g_gameMode == 1) SetSyncTarget(0x17); else SetSyncTarget(0x19);
    for (int i = 0; i < 18; i++) { slots[i].sprite = 0; slots[i].field4 = 0; }
    field04 = 0; selection = 0; reverse = 0; field20 = -1;
    state = 0; advance = 0; timer = 0; field14 = (0.0f);
    left = new CourseSprite(0x24, 1, 0);
    right = new CourseSprite(0x27, 1, 0);
    fieldC4 = 0; field06 = 0; fieldBC = 0; fieldC0 = 0;
    selected = 0; field15C = 0; field15D = 0; field18 = (2e+01f);
    FlowSetSpritePosition(left, (3.2e+02f), (213.0f));
    FlowSetSpritePosition(right, (9.6e+02f), (213.0f));
    map = new CourseSprite(0x17F, 1, (92.0f), (383.0f),
        (0.6f), (0.6f), (0.0f), (0.0f));
    mapIdA = fn_801A0310(map, 0x1777);
    mapIdB = fn_801A0310(map, 0x1780);
    sel = selection;
    cup = sel / 2;
    mapIds = course_data::clFlowCourse_data_8049B388;
    *mapIdA = mapIds[cup][0];
    *mapIdB = mapIds[cup][1];
    fn_80121E10(&preview);
    preview.resId = GetCourseShortIdByCupAndMirror(FlowCourseCup(cup), sel % 2);
    preview.Show((265.0f), (388.0f), (1.0f));
    preview.SetColor(0xFFFFFF00);
    field12C = new CourseSprite(0x16E, 1, (3.1e+02f), (215.0f),
        (1.0f), (1.0f), (0.0f), (0.0f));
    field130 = new CourseSprite(0x170, 1, (9.6e+02f), (215.0f),
        (1.0f), (1.0f), (0.0f), (1.0f));
    pulse = new CoursePulse;
    pulse->sprite->x = (418.0f);
    pulse->sprite->layer = 5;
    field138 = new CourseSprite(0x9C, 1, (0.0f), (0.0f),
        (0.7f), (0.7f), (0.0f), (1.0f));
    field13C = new CourseSprite(0x9C, 1, (0.0f), (0.0f),
        (0.7f), (0.7f), (0.0f), (1.0f));
    field140 = 0; field141 = 0;
    for (int i = 0; i < 4; i++) icons[i] = new CourseIcon(i);
    banner = new CourseBanner;
    if (g_ccClass == 0 && g_gameMode == 2) field15D = 1;
    if (SINGLETON_INSTANCE(g_pInputState)) {
        InputState *input = SINGLETON_INSTANCE(g_pInputState);
        input->enabled = 1; input->held = 0; input->edge = 0;
    }
    SetScreenBrightness((-1.0f));
    fn_801B8918(0x1AE5); InitBGM(); SetupBgSprites(1);
    lbl_806CF12C = 0; InitRumbleController(1);
}

CourseFlow::~CourseFlow() {
    fn_80169C44();
    if (SINGLETON_INSTANCE(g_pInputState)) {
        InputState *input = SINGLETON_INSTANCE(g_pInputState);
        input->enabled = 0;
        input->held = 0;
        input->edge = 0;
    }
    SetScreenBrightness((-1.0f));
    if (g_gameMode == 2) {
        lbl_806CF12C = selected;
        g_cupId = FlowCourseCup(selected / 2);
        SetReverseRoundFlag(reverse);
        int extra = 4;
        int round = selected % 2;
        if (reverse == 0) extra = 0;
        g_roundIndex = round + extra;
        g_longRoundFlag = selected % 2;
    }
    for (int i = 0; i < 4; i++) delete icons[i];
    delete banner;
    delete field138;
    delete field13C;
    delete pulse;
    delete map;
    delete field12C;
    delete field130;
    delete left;
    delete right;
    delete fieldC4;
    delete fieldBC;
    delete fieldC0;
    for (int i = 0; i < 18; i++) delete slots[i].sprite;
    fn_801B87D8();
    fn_801A1678();
}

namespace course_update {
static inline void UpdateRemoteIcons(CourseFlow *self) {
    for (int i = 0; i < 4; i++) {
        if (i != GetDisplayBufferIndex()) {
            int role = g_localPcbRole;
            if (PcbSlot_GetByIndex(i)->HasRole(role)) {
                CourseLayout *layout;
                int selected = PcbSlot_GetByIndex(i)->Selection();
                layout = &clFlowCourse_data_8049B1E0[selected];
                float x = layout->x;
                float a;
                if (self->selection >= 8) x -= (6.4e+02f);
                CourseIcon *icon = self->icons[i];
                a = (1.0f);
                icon->ctrl.Show(x + iconOffsets[icon->index][0],
                    layout->y + iconOffsets[icon->index][1], a);
                if (self->state >= 3) a = (0.0f);
                if (self->selection / 8 != selected / 8) a = (0.0f);
                SetAlpha(&self->icons[i]->ctrl, 0xFFFFFF00, a);
            }
        }
    }
}

extern "C" int clFlowCourse_Update(CourseFlow *self) {
    RumbleUpdate();
    if (self->advance) { self->state++; self->advance = 0; }
    self->timer++;
    switch (self->state) {
    case 0:
        if (self->timer == 1) fn_801CEB78(self, 0, 1);
        if (self->timer == 6) fn_801CEB78(self, 1, 1);
        if (self->timer == 10) fn_801CEB78(self, 2, 1);
        if (self->timer == 14) fn_801CEB78(self, 3, 1);
        if (self->timer == 18) fn_801CEB78(self, 4, 1);
        if (self->timer == 22) fn_801CEB78(self, 5, 1);
        if (self->timer == 26) fn_801CEB78(self, 6, 1);
        if (self->timer == 30) fn_801CEB78(self, 7, 1);
        if (self->timer == 25) {
            self->fieldC4 = new CourseSprite(0x84, 0, (3.2e+02f), (386.0f),
                (1.0f), (1.0f), (0.0f), (1.0f));
            Sprite_SetAnimParam(self->fieldC4, 0x1970, 0x196F);
        }
        if (self->timer >= 54) {
            float a = (float)(self->timer - 50) / (1e+01f);
            self->map->alpha = a; self->field12C->alpha = a; self->field130->alpha = a;
            SetAlpha(&self->preview, 0xFFFFFF00, a);
        }
        if (self->timer == 60) {
            SetScreenBrightness(self->field18);
            lbl_806D184C = 1; lbl_806D184D = 0;
            UpdateArrows(self, courseArrows);
            fn_801CEB78(self, 0, 2);
            for (int i = 1; i < 8; i++) fn_801CEB78(self, i, 6);
            for (int i = 8; i < 16; i++) fn_801CEB78(self, i, 5);
            self->fieldBC = new CourseSprite(0x25, 1, (585.0f), (2.8e+02f),
                (1.0f), (1.0f), (0.0f), (1.0f));
            self->fieldC0 = new CourseSprite(0x28, 1, (704.0f), (2.8e+02f),
                (1.0f), (1.0f), (0.0f), (1.0f));
            self->advance = 1;
            fn_801699D8(0, 1); fn_801699D8(1, 1);
            if (self->field15D) {
                self->fieldBC->alpha = (0.0f);
                self->fieldC0->alpha = (0.0f);
            }
        }
        break;
    case 1: {
        int previous = self->selection;
        if (CourseInput()) {
            InputState *in = CourseInput();
            self->selection += in->dir;
            if (self->selection > 15) self->selection = 15;
            if (self->selection < 0) self->selection = 0;
            if (self->field15D && self->selection > 7) self->selection = 7;
        }
        if (previous != self->selection) {
            fn_801CEB78(self, previous, 6);
            fn_801CEB78(self, self->selection, 2);
            UpdatePreview(self, self->selection);
            UpdateArrows(self, courseArrows);
            if (previous == 7 && self->selection == 8) {
                self->state = 98; self->timer = 0;
                self->field140 = 0; self->field141 = 0;
            }
            if (previous == 8 && self->selection == 7) {
                self->state = 99; self->timer = 0;
                self->field140 = 0; self->field141 = 0;
            }
            if (self->fieldC4) {
                delete self->fieldC4;
                self->fieldC4 = new CourseSprite(0x1BF, 0, 0);
                Sprite_SetAnimParam(self->fieldC4, 0x1970, animIds[self->selection / 2]);
                fn_801A0550(self->fieldC4);
                SetSpritePosition(self->fieldC4, (3.2e+02f), (386.0f));
                fn_8019FF6C(self->fieldC4, 1);
            }
            fn_801B7CAC(); lbl_806CF12C = self->selection;
        }
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Test(0x400)) {
            self->reverse = 1; ShowPulse(self->pulse);
        } else { self->reverse = 0; HidePulse(self->pulse); }
        int next = self->field20;
        switch (next) {
        case -1: {
            self->field18 -= (0.016666668f);
            InputMgr_GetPlayer(GetInputManager(), 0);
            if (CourseInput()->held == 1 || self->field18 < (0.0f)) {
                SetRumbleMode(0, 1, 1);
                if (CourseInput()) {
                    InputState *input = CourseInput();
                    input->enabled = 0; input->held = 0; input->edge = 0;
                }
                CourseParams *params = GetCourseSelectEntry(self->selection);
                lbl_806CF12C = self->selection;
                SetCourseParams(params->cup, params->round, params->field08, self->reverse);
                int extra;
                int round = self->selection % 2;
                extra = 4;
                if (self->reverse == 0) extra = 0;
                g_roundIndex = round + extra;
                if (g_gameMode == 1) self->field20 = 0x26; else self->field04 = 1;
                self->field18 = (-1.0f);
                fn_801B7C64(); lbl_806D184C = -1;
                self->field140 = 0; self->field141 = 0;
            }
            SetScreenBrightness(self->field18);
            next = self->field20;
            break;
        }
        default: break;
        }
        if (next != -1 || self->field04) {
            fn_801CEB78(self, self->selection, 3);
            delete self->fieldBC; delete self->fieldC0;
            self->fieldBC = 0; self->fieldC0 = 0; self->timer = 0;
            if (g_gameMode == 2) {
                CourseBanner *banner = self->banner;
                if (banner->state == 3) { banner->state = 0; banner->timer = 0; }
                self->advance = 1;
            } else {
                self->state = 4;
                for (int i = 0; i < 18; i++)
                    if (i != self->selection) fn_801CEB78(self, i, 7);
            }
        }
        break;
    }
    case 2:
        SetSyncTarget(0x1A);
        if (IsSyncReached()) {
            if (g_playerData[0x19F]) self->field20 = 0x21;
            else self->field20 = 0x22;
            CourseBanner *banner = self->banner;
            if (banner->state == 0 || banner->state == 1) {
                banner->state = 2; banner->timer = 0;
            }
        }
        if (self->field20 != -1) {
            self->selected = (*(unsigned short *)SyncSlot_GetRecv() >> 4) & 0x7F;
            self->reverse = (SyncSlot_GetRecv()[1] >> 3) & 1;
            CoursePulse *pulse = self->pulse;
            if (pulse) {
                if (self->reverse == 0) DeactivatePulse(pulse); else ActivatePulse(pulse);
            }
            UpdatePreview(self, self->selected);
            self->timer = 0; self->advance = 1;
        }
        break;
    case 3:
        if (self->timer < 5) break;
        if (self->timer == 5) {
            for (int i = 0; i < 18; i++) if (i != self->selected) fn_801CEB78(self, i, 7);
            fn_801CEB78(self, self->selected, 3);
        }
        if (self->timer <= 10) {
            float a = (1.0f) - (float)(self->timer - 5) / (5.0f);
            self->field12C->alpha = a; self->field130->alpha = a;
        }
        if (self->timer < 20) break;
        if (self->timer <= 30) {
            CourseLayout *p;
            float t = (float)(self->timer - 20) / (1e+01f);
            p = &clFlowCourse_data_8049B1E0[self->selected];
            float y = p->y + t * ((218.0f) - p->y);
            float x;
            if (self->selection > 8) {
                float from = p->x - (6.4e+02f);
                x = from + t * ((3.2e+02f) - from);
            } else x = p->x + t * ((3.2e+02f) - p->x);
            SetSpritePosition(self->slots[self->selected].sprite, x, y);
        }
        if (self->timer == 30) self->field15C = 1;
        if (self->timer == 120) {
            fn_801CEB78(self, self->selected, 4);
            SetupExitSprites(self);
            self->field06 = 1; self->timer = 0; self->state = 5;
        }
        break;
    case 4:
        if (self->timer <= 5 && self->field12C->alpha > (0.0f)) {
            float a = (1.0f) - (float)self->timer / (5.0f);
            self->field12C->alpha = a; self->field130->alpha = a;
        }
        if (self->timer > 42) {
            fn_801CEB78(self, self->selection, 4); SetupExitSprites(self);
            self->field06 = 1; self->advance = 1; self->timer = 0;
        }
        break;
    case 5:
        if (self->timer <= 5) {
            float a = (1.0f) - (float)self->timer / (5.0f);
            self->map->alpha = a;
            SetAlpha(&self->preview, 0xFFFFFF00, a);
            HidePulse(self->pulse);
        }
        if (self->timer >= 30) {
            fn_801699D8(0, 0); fn_801699D8(1, 0);
            return self->field20;
        }
        break;
    case 98:
        self->field14 = -((32.0f) * (float)self->timer);
        for (int i = 0; i < 18; i++)
            if (self->slots[i].sprite) self->slots[i].sprite->x = self->field14 + clFlowCourse_data_8049B1E0[i].x;
        if (self->field12C) self->field12C->x = (3.1e+02f) + self->field14;
        if (self->field130) self->field130->x = (9.6e+02f) + self->field14;
        if (self->timer >= 20) { self->state = 1; UpdateArrows(self, courseArrows); }
        break;
    case 99:
        self->field14 = (32.0f) * (float)self->timer + (-6.4e+02f);
        for (int i = 0; i < 18; i++)
            if (self->slots[i].sprite) self->slots[i].sprite->x = self->field14 + clFlowCourse_data_8049B1E0[i].x;
        if (self->field12C) self->field12C->x = (3.1e+02f) + self->field14;
        if (self->field130) self->field130->x = (9.6e+02f) + self->field14;
        if (self->timer >= 20) { self->state = 1; UpdateArrows(self, courseArrows); }
        break;
    }
    if (self->left) {
        if (!Sprite_AdvanceAnim(self->left, (0.0165f)) && !self->field06) {
            Sprite_SetupAnim(self->left, 0x16D, 1, 0); fn_8019FF6C(self->left, 1);
        }
        SetSpritePosition(self->left, (3.2e+02f) + self->field14, (213.0f));
    }
    if (self->right) {
        if (!Sprite_AdvanceAnim(self->right, (0.0165f)) && !self->field06) {
            Sprite_SetupAnim(self->right, 0x16F, 1, 0); fn_8019FF6C(self->right, 1);
        }
        SetSpritePosition(self->right, (9.6e+02f) + self->field14, (213.0f));
    }
    if (self->fieldC4 && !Sprite_AdvanceAnim(self->fieldC4, (0.0165f)) && !self->field06) {
        Sprite_SetupAnim(self->fieldC4, 0x1BF, 0, 0);
        Sprite_SetAnimParam(self->fieldC4, 0x1970, 0x196F);
        fn_801A0550(self->fieldC4); fn_8019FF6C(self->fieldC4, 1);
    }
    if (self->fieldBC) {
        Sprite_AdvanceAnim(self->fieldBC, (0.0165f));
        self->fieldBC->x = (585.0f) + self->field14;
    }
    if (self->fieldC0) {
        Sprite_AdvanceAnim(self->fieldC0, (0.0165f));
        self->fieldC0->x = (704.0f) + self->field14;
    }
    if (self->field12C) Sprite_AdvanceAnim(self->field12C, (0.0165f));
    if (self->field130) Sprite_AdvanceAnim(self->field130, (0.0165f));
    if (self->map) Sprite_AdvanceAnim(self->map, (0.0165f));
    CoursePulse *p = self->pulse;
    if (p && p->active) {
        if (p->timer <= 8) {
            p->sprite->alpha = PulseAlpha(p);
            if (p->timer++ == 8 && p->flag) { p->active = 0; p->flag = 0; }
        }
        Sprite_AdvanceAnim(p->sprite, (0.0165f));
    }
    if (self->field138) Sprite_AdvanceAnim(self->field138, (0.0165f));
    if (self->field13C) Sprite_AdvanceAnim(self->field13C, (0.0165f));
    for (int i = 0; i < 18; i++) fn_801CE918(self, i);
    if (self->field15C == 1 && self->slots[self->selected].sprite) {
        SetSpritePosition(self->slots[self->selected].sprite, (3.2e+02f), (218.0f));
    }
    if (g_gameMode == 2) {
        UpdateRemoteIcons(self);
        if (self->banner) fn_801D1684(self->banner);
    }
    return -1;
}

}
namespace course_draw {
extern "C" {
void fn_801CF188(ItemSelectView *self)
{
    LinkBanner *b;
    int i;
    int j;

    if (self->bg != 0) {
        fn_801A0004(self->bg);
    }
    if (self->frame != 0) {
        fn_801A0004(self->frame);
    }
    if (self->arrowL != 0) {
        fn_801A0004(self->arrowL);
    }
    if (self->title != 0) {
        fn_801A0004(self->title);
    }
    if (self->cursor != 0) {
        fn_801A0004(self->cursor);
    }
    if (self->arrowR != 0) {
        fn_801A0004(self->arrowR);
    }
    if (self->help != 0) {
        fn_801A0004(self->help);
    }
    if (self->timer != 0) {
        fn_801A0004(self->timer);
    }
    fn_8011FAFC(self->fade, 5);
    if (self->badge != 0 && self->badge->visible) {
        fn_801A0004(self->badge->sprite);
    }
    for (i = 0; i < 18; i++) {
        if (i != self->selected && self->items[i].sprite != 0) {
            fn_801A0004(self->items[i].sprite);
        }
    }
    if (self->items[self->selected].sprite != 0) {
        fn_801A0004(self->items[self->selected].sprite);
    }
    if (self->extra0 != 0 && self->showExtra0) {
        fn_801A0004(self->extra0);
    }
    if (self->extra1 != 0 && self->showExtra1) {
        fn_801A0004(self->extra1);
    }
    if (g_gameMode == 2) {
        for (j = 0; j < 4; j++) {
            fn_8011FAFC(self->players[j], self->players[j]->layer);
        }
        b = self->banner;
        if (b != 0 && b->state != 3) {
            fn_8011FAFC(b->ctrl0, 6);
            fn_8011FAFC(b->ctrl1, 6);
            fn_8011FAFC(b->ctrl2, 6);
        }
    }
}

}
}
namespace course_rows {
extern "C" int fn_801CEB78(CourseRows *self, int index, int state) {
    CourseRow *row = &self->rows[index];
    if (state != 5) {
        if (state == 1) { if (row->state != 0) return 0; }
        else { if (row->state == 0) return 0; }
    }
    row->state = state;
    switch(state) {
    case 1: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[1].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[1].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[1].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        break;
    }
    case 2: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[2].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[2].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[2].scale);
        row->sprite->SetPos(layout->x + self->x,layout->alternateY);
        fn_8019FF6C(row->sprite,1);
        break;
    }
    case 3: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[3].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[3].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[3].scale);
        row->sprite->SetPos(layout->x + self->x,layout->alternateY);
        break;
    }
    case 4: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[4].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[4].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[4].scale);
        row->sprite->SetPos(layout->x + self->x,layout->alternateY);
        break;
    }
    case 5: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[5].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[5].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[5].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        fn_8019FF6C(row->sprite,1);
        break;
    }
    case 6: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[6].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[6].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[6].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        fn_8019FF6C(row->sprite,1);
        break;
    }
    case 7: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[7].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[7].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[7].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        break;
    }
    }
    return 1;
}

extern "C" int fn_801CE918(CourseRows *self, int index) {
    CourseRow *row = &self->rows[index];
    if (!row->sprite) return 0;
    if (Sprite_AdvanceAnim(row->sprite,(0.0165f)) == 1) return 1;
    switch(row->state) {
    case 1: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[5].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[5].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[5].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        fn_8019FF6C(row->sprite,1);
        break;
    }
    case 2: break;
    case 3: {
        RowAnimation *animations = clFlowCourse_data_8049B348;
        RowLayout *layout = &clFlowCourse_data_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[2].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[2].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[2].scale);
        row->sprite->SetPos(layout->x + self->x,layout->alternateY);
        fn_8019FF6C(row->sprite,1);
        break;
    }
    case 4:
    case 7:
        delete row->sprite;
        row->state = 0;
        row->sprite = 0;
        return 0;
    }
    return 1;
}

}
namespace course_sel {
extern "C" {
void fn_801CE800(CourseSel *sel, int index) {
    int cup = index / 2;
    int cupId;

    *sel->nameA = clFlowCourse_data_8049B388[cup].first;
    *sel->nameB = clFlowCourse_data_8049B388[cup].second;
    fn_80121E10(&sel->course);
    switch (cup) {
    case 0:
        cupId = 7;
        break;
    case 1:
        cupId = 1;
        break;
    case 2:
        cupId = 8;
        break;
    case 3:
        cupId = 2;
        break;
    case 4:
        cupId = 3;
        break;
    case 5:
        cupId = 4;
        break;
    case 6:
        cupId = 5;
        break;
    case 7:
        cupId = 6;
        break;
    default:
        cupId = 1;
        break;
    }
    sel->course = GetCourseShortIdByCupAndMirror(cupId, index % 2);
    sel->dirty = 1;
    sel->fadeE8 = (265.0f);
    sel->fadeEC = (388.0f);
    sel->fadeF0 = (1.0f);
}

}
}
