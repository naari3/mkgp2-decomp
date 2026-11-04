#ifndef RANKING_SPRITE_OWNER_PRIVATE_H
#define RANKING_SPRITE_OWNER_PRIVATE_H
#include "game/FlowScene.h"
#include "dolphin/mtx.h"

struct RankingSprite {
    int field0, layer, field8;
    float x, y, sx, sy;
    char pad1C[4];
    float alpha;
    char pad24[0xC];
    RankingSprite(int, int, int);
    ~RankingSprite();
    void SetPos(float px, float py) { x = px; y = py; }
};
struct RankingDriver {
    char data[0x384];
    RankingDriver(int, int, Mtx, int, int, int);
    ~RankingDriver();
};
extern "C" {
void Sprite_Destroy(RankingSprite *, int);
void KartDriver_Dtor(RankingDriver *, int);
}
struct RankingSpriteSlot {
    RankingSprite *p;
    RankingSpriteSlot() {}
    RankingSpriteSlot(RankingSprite *q) : p(q) {}
    ~RankingSpriteSlot() throw() { Sprite_Destroy(p, 1); }
};
struct RankingDriverSlot {
    RankingDriver *p;
    RankingDriverSlot() {}
    RankingDriverSlot(RankingDriver *q) : p(q) {}
    ~RankingDriverSlot() throw() { KartDriver_Dtor(p, 1); }
};
struct RankingPlacement {
    float x, y, z, start, field10, field14, rx, ry;
};
struct RankingScene {
    virtual void v0();
    virtual unsigned char Begin();
    virtual void End();
};
struct RankingTrack {
    unsigned char active;
    char pad1[3];
    float from, to, speed, time, value;
};
struct RankingSpriteOwnerView {
    void *vtable;
    RankingSprite *baseSprite;
    int layer;
    RankingTrack tracks[5];
    unsigned char flag84, flag85;
    char pad86[2];
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
    TextManager text0, text1, text2;
    float labelPos[4][2];
    unsigned char alternate;
    char pad7A1;
    short labelA, labelB;
    unsigned char labelVariant;
};
#endif
