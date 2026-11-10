/* Ranking panel constructor and its exception-safe owned members. */
#include "game/RankingSpriteOwner_private.h"
extern "C" {
extern void *lbl_8048EF34[], *RankingSpriteOwnerCtor_vtable_8049B53C[];
extern const char lbl_806D9FF8[4];
extern const float lbl_806D9FA8, lbl_806D9FAC, lbl_806D9FF0, lbl_806D9FF4;
extern const float lbl_806DA000, lbl_806DA004, lbl_806DA008;
void fn_8019FF6C(RankingSprite *, int);
void fn_801F9014(void *, const char *, ...);
unsigned char fn_8019FF8C(RankingSprite *, int, void *);
void Sprite_SetAnimParam(RankingSprite *, int, short);
int GetDisplayBufferIndex();
short fn_80231A20(int);
int fn_80231B94(int);
void RenderObj_ItemStateMachine_Timed(RankingDriver *, int, float, float);
}
/* Ranking curve samples, character names, panel placements and animation IDs. */
static const float rankingCurve[255] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f,
    0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f,
    83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f,
    83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f,
};
static const char rankingName8039C384[12] = "\x83\x8B\x83\x43\x81\x5B\x83\x57";
static const char rankingName8039C390[12] = "\x83\x4C\x83\x6D\x83\x73\x83\x49";
static const char rankingName8039C39C[12] = "\x83\x68\x83\x93\x83\x4C\x81\x5B";
static const char rankingName8039C3A8[12] = "\x83\x88\x83\x62\x83\x56\x81\x5B";
static const char rankingName8039C3B4[12] = "\x83\x70\x83\x62\x83\x4E\x83\x7D\x83\x93";
static const char rankingName8039C3C0[12] = "\x83\x7E\x83\x59\x83\x70\x83\x62\x83\x4E";
static const char rankingName8039C3CC[12] = "\x83\x41\x83\x4A\x83\x78\x83\x43";
static const char rankingName8039C3D8[12] = "\x83\x8F\x83\x8B\x83\x43\x81\x5B\x83\x57";
static const char rankingName8039C3E4[12] = "\x82\xDC\x82\xDF\x82\xC1\x82\xBF";
static const char rankingName8039C3F0[12] = "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E";
static const char rankingName8039C3FC[12] = "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68";
static const char rankingName8039C408[12] = "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E";
static const char rankingName8039C414[12] = "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67";
static const char rankingName8039C420[12] = "\x82\x6A\x82\x68\x82\x6D\x82\x66";
static const char rankingName8039C42C[12] = "\x82\x73\x82\x6E\x82\x60\x82\x63";
static const char rankingName8039C438[12] = "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68";
static const char rankingName8039C444[12] = "\x82\x6C\x82\x93\x81\x44\x82\x6F";
static const char rankingName8039C450[12] = "\x82\x76\x82\x60\x82\x6B\x82\x74";
static const char rankingNameMame[12] = "\x82\x6C\x82\x60\x82\x6C\x82\x64";
/* The target has an unresolved 12-byte zero run before this table. */
static const RankingPlacement rankingPlacements[4] = {
    { -8.2f, 1.5f, 3.0f, -34.2f, 1.5f, 3.0f, 20.0f, -20.0f },
    { 14.5f, 1.5f, 3.0f, 48.5f, 1.5f, 3.0f, 20.0f, -40.0f },
    { -8.2f, -10.0f, 3.0f, -34.2f, -10.0f, 3.0f, 10.0f, -20.0f },
    { 14.5f, -10.0f, 3.0f, 48.5f, -10.0f, 3.0f, 10.0f, -40.0f },
};
static const short rankingScreenParams[4][3] = {
    { 6896, 6900, 3108 },
    { 6897, 6901, 3109 },
    { 6898, 6902, 3110 },
    { 6899, 6903, 3111 },
};
static const short rankingLabels[24] = { 3122, 3123, 3132, 3126, 3134, 3131, 3133, 3127, 3124, 3130, 3128, 3125, 3129, 0, 3135, 3136, 3137, 3138, 3139, 3140, 3141, 3142, 3143, 3144 };
static const short rankingResources[16] = { 3145, 3146, 3147, 3148, 3153, 3154, 3155, 3156, 3161, 3162, 3163, 3164, 3166, 3169, 3170, 0 };

struct RankingCtorTrack {
    unsigned char active;
    char pad1[3];
    float from, to, speed, time, value;
    RankingCtorTrack() : speed(lbl_806D9FA8), time(lbl_806D9FA8) {}
};
struct RankingCtorBase {
    virtual void _key();
    RankingSprite *baseSprite;
    int layer;
    RankingCtorTrack tracks[5];
    unsigned char flag84, flag85;
    char pad86[2];
    RankingCtorBase(int frames) : baseSprite(0), layer(frames), flag84(0), flag85(0) {
        tracks[0].active = 0;
        tracks[1].active = 0;
        tracks[2].active = 0;
        tracks[3].active = 0;
        tracks[4].active = 0;
    }
    ~RankingCtorBase();
};
struct RankingCtorText {
    char data[0x230];
    RankingCtorText();
    ~RankingCtorText() {}
    TextManager *tm() { return (TextManager *)this; }
};
struct RankingNodeInfo {
    float x, y;
    char rest[0x28];
};
struct RankingSpriteOwnerCtor : RankingCtorBase {
    virtual void _key2();
    const RankingPlacement *placement;
    RankingSpriteSlot back, front, mark;
    RankingDriverSlot driver;
    float from, to, speed, time, value;
    RankingScene *scene;
    void *lights;
    Mtx matrix;
    float y;
    short resource;
    unsigned char hideMark;
    char padEF;
    RankingCtorText text0, text1, text2;
    float labelPos[4][2];
    unsigned char alternate;
    char pad7A1;
    short labelA, labelB;
    unsigned char labelVariant;
    RankingSpriteOwnerCtor(int frames, int position, int screen, int character, unsigned char variant,
                          int unused, const char *name, int number, const char *detail, int label,
                          RankingScene *scene_, void *lights_, float x, float unusedY, float py);
};

#pragma cplusplus off
static inline int RankingDriverMode(unsigned char variant) {
    return variant == 1 ? 2 : 0;
}
static inline int RankingNameOffset(void) {
    if (isJapanese() == 0) return 12;
    return -6;
}
#pragma cplusplus reset

static inline float RankingPlacementY(const RankingPlacement *p) { return p->y; }
static inline float RankingPlacementZ(const RankingPlacement *p) { return p->z; }

#pragma inline_max_size(10000)
RankingSpriteOwnerCtor::RankingSpriteOwnerCtor(int frames, int position, int screen, int character,
        unsigned char variant, int unused, const char *name, int number, const char *detail, int label,
        RankingScene *scene_, void *lights_, float x, float unusedY, float py)
    : RankingCtorBase(frames),
      placement(&rankingPlacements[position]),
      back(new RankingSprite(0x1E1, 1, 0)), front(new RankingSprite(0x1E0, 1, 0)),
      mark(new RankingSprite(0xCA, 1, 0)),
      driver(new RankingDriver(6, character, matrix, 0, 0, RankingDriverMode(variant))),
      speed(lbl_806D9FA8), time(lbl_806D9FA8), scene(scene_), lights(lights_), y(py), hideMark(0) {
    alternate = 0;
    labelVariant = 0;
    tracks[3].from = x;
    tracks[3].to = unusedY;
    tracks[3].speed = lbl_806D9FF0;
    tracks[3].time = lbl_806D9FA8;
    tracks[3].value = x;
    tracks[3].active = 1;
    fn_8019FF6C(mark.p, 1);
    mark.p->layer = 7;
    front.p->SetPos(lbl_806D9FA8, lbl_806D9FA8);
    fn_801F9014(&text0, name);
    RankingNodeInfo pos;
    fn_8019FF8C(front.p, 0x1ECD, &pos);
    labelPos[0][0] = pos.x;
    labelPos[0][1] = pos.y;
    fn_801F93EC(text0.tm(), pos.x, pos.y);
    Sprite_SetAnimParam(front.p, 0x1ECD, 0x1ECD);
    Sprite_SetAnimParam(front.p, 0x1ECF, 0x1ECD);
    Sprite_SetAnimParam(front.p, 0x1ED1, 0x1ECD);
    Sprite_SetAnimParam(front.p, 0x1ED3, 0x1ECD);
    Sprite_SetAnimParam(front.p, 0x1ED5, 0x1ECD);
    fn_801F9014(&text2, detail);
    *(float *)(text2.data + 0x22C) = lbl_806D9FF4;
    fn_8019FF8C(front.p, 0x1ED7, &pos);
    labelPos[1][0] = pos.x;
    labelPos[1][1] = pos.y;
    fn_801F93EC(text2.tm(), pos.x, pos.y);
    Sprite_SetAnimParam(front.p, 0x1ED7, 0x1ECD);
    fn_801F8FCC(text1.tm(), 0);
    TexMgr_SetTexture(text1.tm(), lbl_806D9FF8, number);
    fn_8019FF8C(front.p, 0x1ED9, &pos);
    int dx = RankingNameOffset();
    labelPos[2][0] = pos.x + dx;
    labelPos[2][1] = pos.y;
    fn_801F93EC(text1.tm(), pos.x, pos.y);
    Sprite_SetAnimParam(front.p, 0x1ED9, 0x1ECD);
    fn_801F8FCC(text1.tm(), 2);
    fn_8019FF8C(front.p, 0xC24, &pos);
    labelPos[3][0] = pos.x;
    labelPos[3][1] = pos.y;
    const short (*params)[3] = rankingScreenParams;
    Sprite_SetAnimParam(back.p, 0x1AF0, params[screen][0]);
    Sprite_SetAnimParam(front.p, 0x1AF4, params[screen][1]);
    if (screen == GetDisplayBufferIndex()) Sprite_SetAnimParam(front.p, 0x1AFD, screen + 0x1AFD);
    else Sprite_SetAnimParam(front.p, 0x1AFD, 0x1ECD);
    labelA = -1;
    if (label == -1) {
        Sprite_SetAnimParam(front.p, 0xC32, 0x1ECD);
    } else if (label == 0) {
        Sprite_SetAnimParam(front.p, 0xC32, 0x1ECD);
        labelA = rankingLabels[character];
    } else {
        Sprite_SetAnimParam(front.p, 0xC32, 0x1ECD);
        labelA = fn_80231A20(label - 1);
        labelVariant = 1;
    }
    if (label >= 0) {
        resource = screen + 0x2B00;
        Sprite_SetAnimParam(front.p, 0xC24, 0x1ECD);
        labelB = fn_80231B94(screen);
    } else {
        alternate = 1;
        resource = rankingResources[character];
        RankingSprite *sprite = front.p;
        short anim = fn_80231B94(screen);
        Sprite_SetAnimParam(sprite, 0xC24, anim);
        labelB = -1;
    }
    back.p->SetPos(lbl_806DA000, lbl_806D9FA8);
    front.p->SetPos(lbl_806DA000, lbl_806D9FA8);
    front.p->layer = 7;
    float initial;
    float destination;
    destination = placement->x;
    initial = placement->start;
    from = initial;
    to = destination;
    speed = lbl_806D9FAC / frames;
    time = lbl_806D9FA8;
    value = initial;
    value = from * (lbl_806D9FAC - time) + to * time;
    time += speed;
    if (time > lbl_806D9FAC) time = lbl_806D9FAC;
    Mtx translate, rotate, scale;
    PSMTXScale(scale, lbl_806DA004, lbl_806DA004, lbl_806DA004);
    PSMTXTrans(translate, value, RankingPlacementY(placement), RankingPlacementZ(placement));
    PSMTXIdentity(matrix);
    PSMTXConcat(scale, matrix, matrix);
    PSMTXRotRad(rotate, 'x', lbl_806DA008 * placement->rx);
    PSMTXConcat(rotate, matrix, matrix);
    PSMTXRotRad(rotate, 'y', lbl_806DA008 * placement->ry);
    PSMTXConcat(rotate, matrix, matrix);
    PSMTXConcat(translate, matrix, matrix);
    RenderObj_ItemStateMachine_Timed(driver.p, 0, lbl_806D9FA8, lbl_806D9FA8);
}
