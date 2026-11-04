/* Ranking panel construction. Native C++ draft; symbol bridges remain pending. */
#include "game/RankingSpriteOwner_private.h"
extern "C" {
extern void *lbl_8048EF34[], *lbl_8049B53C[];
extern const char lbl_8039BF88[];
extern const char lbl_806D9FF8[4];
extern const float lbl_806D9FA8, lbl_806D9FAC, lbl_806D9FF0, lbl_806D9FF4;
extern const float lbl_806DA000, lbl_806DA004, lbl_806DA008;
void fn_8019FF6C(RankingSprite *, int);
void fn_801F9014(void *, const char *, ...);
unsigned char fn_8019FF8C(RankingSprite *, int, void *);
void Sprite_SetAnimParam(RankingSprite *, int, short);
int GetDisplayBufferIndex();
short fn_80231A20(int);
short fn_80231B94(int);
void RenderObj_ItemStateMachine_Timed(RankingDriver *, int, float, float);
}
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

#pragma inline_max_size(10000)
inline RankingSpriteOwnerCtor::RankingSpriteOwnerCtor(int frames, int position, int screen, int character,
        unsigned char variant, int unused, const char *name, int number, const char *detail, int label,
        RankingScene *scene_, void *lights_, float x, float unusedY, float py)
    : RankingCtorBase(frames),
      placement((const RankingPlacement *)(lbl_8039BF88 + 0x4EC) + position),
      back(new RankingSprite(0x1E1, 1, 0)), front(new RankingSprite(0x1E0, 1, 0)),
      mark(new RankingSprite(0xCA, 1, 0)),
      driver(new RankingDriver(6, character, matrix, 0, 0, variant == 1 ? 2 : 0)),
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
    int dx = isJapanese() ? -6 : 12;
    labelPos[2][0] = pos.x + dx;
    labelPos[2][1] = pos.y;
    fn_801F93EC(text1.tm(), pos.x, pos.y);
    Sprite_SetAnimParam(front.p, 0x1ED9, 0x1ECD);
    fn_801F8FCC(text1.tm(), 2);
    fn_8019FF8C(front.p, 0xC24, &pos);
    labelPos[3][0] = pos.x;
    labelPos[3][1] = pos.y;
    const short (*params)[3] = (const short (*)[3])(lbl_8039BF88 + 0x56C);
    Sprite_SetAnimParam(back.p, 0x1AF0, params[screen][0]);
    Sprite_SetAnimParam(front.p, 0x1AF4, params[screen][1]);
    if (screen == GetDisplayBufferIndex()) Sprite_SetAnimParam(front.p, 0x1AFD, screen + 0x1AFD);
    else Sprite_SetAnimParam(front.p, 0x1AFD, 0x1ECD);
    labelA = -1;
    if (label == -1) {
        Sprite_SetAnimParam(front.p, 0xC32, 0x1ECD);
    } else if (label == 0) {
        Sprite_SetAnimParam(front.p, 0xC32, 0x1ECD);
        labelA = ((const short *)(lbl_8039BF88 + 0x584))[character];
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
        resource = ((const short *)(lbl_8039BF88 + 0x5B4))[character];
        Sprite_SetAnimParam(front.p, 0xC24, fn_80231B94(screen));
        labelB = -1;
    }
    back.p->SetPos(lbl_806DA000, lbl_806D9FA8);
    front.p->SetPos(lbl_806DA000, lbl_806D9FA8);
    front.p->layer = 7;
    float destination = placement->x;
    float initial = placement->start;
    from = initial;
    to = destination;
    speed = lbl_806D9FAC / frames;
    time = lbl_806D9FA8;
    value = initial;
    value = from * (lbl_806D9FAC - time) + to * time;
    time += speed;
    if (time > lbl_806D9FAC) time = lbl_806D9FAC;
    Mtx scale, rotate, translate;
    PSMTXScale(scale, lbl_806DA004, lbl_806DA004, lbl_806DA004);
    PSMTXTrans(translate, value, placement->y, placement->z);
    PSMTXIdentity(matrix);
    PSMTXConcat(scale, matrix, matrix);
    PSMTXRotRad(rotate, 'x', lbl_806DA008 * placement->rx);
    PSMTXConcat(rotate, matrix, matrix);
    PSMTXRotRad(rotate, 'y', lbl_806DA008 * placement->ry);
    PSMTXConcat(rotate, matrix, matrix);
    PSMTXConcat(translate, matrix, matrix);
    RenderObj_ItemStateMachine_Timed(driver.p, 0, lbl_806D9FA8, lbl_806D9FA8);
}

inline void *operator new(unsigned long, void *p) { return p; }
extern "C" RankingSpriteOwnerCtor *fn_801D286C(void *self, int frames, int position, int screen,
        int character, unsigned char variant, int unused, const char *name, int number,
        const char *detail, int label, RankingScene *scene, void *lights, float x, float unusedY, float y) {
    return new (self) RankingSpriteOwnerCtor(frames, position, screen, character, variant,
                                            unused, name, number, detail, label, scene, lights, x, unusedY, y);
}
