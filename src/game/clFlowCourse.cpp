#include "game/clFlowCourse.h"
#include "game/singleton.h"

/* 801D0C30..801D1800: indivisible reversed-extab group.
 * Native C++ draft; retain Object(NonMatching) until all four functions and
 * their EH records match. The constructor's original pooled-data base and
 * the destructor/fader register identities still differ. */

struct CourseResource { short id; char pad02[18]; };
struct CourseData {
    CourseResource resources[18];
    char pad168[0x1A8-0x168];
    short mapIds[9][2];
    char pad1CC[8];
    int vtable[5];
};
extern "C" {
extern CourseData lbl_8049B1E0;
extern char lbl_8049B3B4[];
extern const char lbl_8039BF5C[], lbl_8039BF78[];
extern int g_gameMode, g_cupId, g_roundIndex, g_longRoundFlag, g_ccClass;
extern int lbl_806CF12C;
extern const float lbl_806D9ED8, lbl_806D9EDC, lbl_806D9EE0, lbl_806D9EE4;
extern const float lbl_806D9EE8, lbl_806D9EEC, lbl_806D9EF8, lbl_806D9EFC;
extern const float lbl_806D9F14, lbl_806D9F20, lbl_806D9F24, lbl_806D9F2C;
extern const float lbl_806D9F40, lbl_806D9F44, lbl_806D9F48, lbl_806D9F4C;
extern const float lbl_806D9F50, lbl_806D9F54, lbl_806D9F58, lbl_806D9F5C;
extern const float lbl_806D9F60, lbl_806D9F64, lbl_806D9F68, lbl_806D9F6C;
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
void fn_80121E10(ResCtrl *);
short GetCourseShortIdByCupAndMirror(int, int);
int fn_801B8918(int);
void InitBGM();
int SetupBgSprites(unsigned char);
void InitRumbleController(int);
}

static inline void SetSpritePosition(CourseSprite *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

static inline int CourseCup(int i) {
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

CourseFlow::~CourseFlow() {
    fn_80169C44();
    if (SINGLETON_INSTANCE(g_pInputState)) {
        InputState *input = SINGLETON_INSTANCE(g_pInputState);
        input->enabled = 0;
        input->held = 0;
        input->edge = 0;
    }
    SetScreenBrightness(lbl_806D9EF8);
    if (g_gameMode == 2) {
        lbl_806CF12C = selected;
        g_cupId = CourseCup(selected / 2);
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

inline CoursePulse::CoursePulse() {
    active = 0; flag = 0; timer = 0;
    sprite = new CourseSprite(0x9E, 1, lbl_806D9F54, lbl_806D9F54,
        lbl_806D9EDC, lbl_806D9EDC, lbl_806D9EE0, lbl_806D9EE0);
}
inline CourseIcon::CourseIcon(int n) {
    layer = 5;
    index = n;
    ctrl.resId = (short)(index + 0x1EC5);
    ctrl.Show(lbl_806D9F60, lbl_806D9F60, lbl_806D9EDC);
    ctrl.SetColor(0xFFFFFF00);
}
inline CourseBanner::CourseBanner() : state(3), timer(0) {
    main.mode = 2;
    main.width = lbl_806D9ED8;
    main.height = lbl_806D9F64;
    main.Show(lbl_806D9EFC, lbl_806D9F68, lbl_806D9EDC);
    labels[0].resId = 0x1B12;
    labels[0].Show(lbl_806D9EFC, lbl_806D9F68, lbl_806D9EDC);
    labels[1].resId = 0x1B13;
    labels[1].Show(lbl_806D9EFC, lbl_806D9F6C, lbl_806D9EDC);
    main.SetColor(0);
    labels[0].SetColor(0xFFFFFF00);
    labels[1].SetColor(0xFFFFFF00);
}

CourseFlow::CourseFlow() {
    CourseData *data = &lbl_8049B1E0;
    SpriteSystem_EnsureInit();
    if (!PCBComm_PackAndTriggerCardSnapshot())
        DebugPrintf(lbl_8039BF5C, lbl_8039BF78, 0xA1);
    for (int i = 0; i < 9; i++) {
        PreloadResource(data->resources[i].id);
        PreloadResource(data->resources[i].id + 6);
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
    state = 0; advance = 0; timer = 0; field14 = lbl_806D9EE0;
    left = new CourseSprite(0x24, 1, 0);
    right = new CourseSprite(0x27, 1, 0);
    fieldC4 = 0; field06 = 0; fieldBC = 0; fieldC0 = 0;
    selected = 0; field15C = 0; field15D = 0; field18 = lbl_806D9F40;
    SetSpritePosition(left, lbl_806D9EFC, lbl_806D9F2C);
    SetSpritePosition(right, lbl_806D9F24, lbl_806D9F2C);
    map = new CourseSprite(0x17F, 1, lbl_806D9F44, lbl_806D9F48,
        lbl_806D9F4C, lbl_806D9F4C, lbl_806D9EE0, lbl_806D9EE0);
    mapIdA = fn_801A0310(map, 0x1777);
    mapIdB = fn_801A0310(map, 0x1780);
    int sel = selection;
    int cup = sel / 2;
    short (*mapIds)[2] = data->mapIds;
    *mapIdA = mapIds[cup][0];
    *mapIdB = mapIds[cup][1];
    fn_80121E10(&preview);
    preview.resId = GetCourseShortIdByCupAndMirror(CourseCup(cup), sel % 2);
    preview.Show(lbl_806D9EE8, lbl_806D9EEC, lbl_806D9EDC);
    preview.SetColor(0xFFFFFF00);
    field12C = new CourseSprite(0x16E, 1, lbl_806D9F20, lbl_806D9F50,
        lbl_806D9EDC, lbl_806D9EDC, lbl_806D9EE0, lbl_806D9EE0);
    field130 = new CourseSprite(0x170, 1, lbl_806D9F24, lbl_806D9F50,
        lbl_806D9EDC, lbl_806D9EDC, lbl_806D9EE0, lbl_806D9EDC);
    pulse = new CoursePulse;
    pulse->sprite->x = lbl_806D9F58;
    pulse->sprite->layer = 5;
    field138 = new CourseSprite(0x9C, 1, lbl_806D9EE0, lbl_806D9EE0,
        lbl_806D9F5C, lbl_806D9F5C, lbl_806D9EE0, lbl_806D9EDC);
    field13C = new CourseSprite(0x9C, 1, lbl_806D9EE0, lbl_806D9EE0,
        lbl_806D9F5C, lbl_806D9F5C, lbl_806D9EE0, lbl_806D9EDC);
    field140 = 0; field141 = 0;
    for (int i = 0; i < 4; i++) icons[i] = new CourseIcon(i);
    banner = new CourseBanner;
    if (g_ccClass == 0 && g_gameMode == 2) field15D = 1;
    if (SINGLETON_INSTANCE(g_pInputState)) {
        InputState *input = SINGLETON_INSTANCE(g_pInputState);
        input->enabled = 1; input->held = 0; input->edge = 0;
    }
    SetScreenBrightness(lbl_806D9EF8);
    fn_801B8918(0x1AE5); InitBGM(); SetupBgSprites(1);
    lbl_806CF12C = 0; InitRumbleController(1);
}

extern "C" int fn_801D161C(int i) { return CourseCup(i); }

static inline int FadeAlpha(int timer) {
    return (int)(lbl_806D9EE4 * ((float)timer / lbl_806D9F14));
}
static inline int FadeOutAlpha(int timer) {
    return (int)(lbl_806D9EE4 * (lbl_806D9EDC - (float)timer / lbl_806D9F14));
}
#pragma push
#pragma opt_common_subs off
extern "C" void fn_801D1684(CourseBanner *self) {
    if (self->state == 3) return;
    switch (self->state) {
    case 0: {
        unsigned int color = 0xFFFFFF00;
        int alpha = FadeAlpha(self->timer);
        self->main.SetColor((alpha >> 1) & 0x7F);
        color = ((color) & 0xFFFFFF00 | (unsigned char)(alpha));
        self->labels[0].SetColor(color);
        self->labels[1].SetColor(color);
        if (self->timer >= 5) { self->timer = 0; self->state = 1; }
        break;
    }
    case 2: {
        unsigned int color = 0xFFFFFF00;
        int alpha = FadeOutAlpha(self->timer);
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

