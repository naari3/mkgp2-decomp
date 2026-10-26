#ifndef GAME_SPRITEPAIROWNER_H
#define GAME_SPRITEPAIROWNER_H
#include "game/FlowScene.h"
/* Shared Sprite ABI already used by the flow scenes; observed fields only. */
struct Sprite {
    int field0, layer, field8;
    float x, y;
    char pad14[0x20 - 0x14];
    float alpha;
    char pad24[0x30 - 0x24];
    Sprite(int resource, int mode, int flags);
    ~Sprite();
};
struct SpritePairOwner {
    Sprite *sprites[2];
    int handles[2];
    int resources[2];
    float alpha, speed;
    SpritePairOwner(int back, int front, int backHandle, int frontHandle, int layer);
    ~SpritePairOwner();
    void Tick();
    void Reset();
};
extern "C" {
void SpriteHandle_SetActiveFlag(int, int);
void fn_8011F804(int, float, float);
void fn_801A0004(Sprite *);
unsigned char Sprite_AdvanceAnim(Sprite *, float);
void SpriteHandle_SetCornerAlpha(int, int);
void SpriteHandle_RecomputeCull(int);
void SpriteHandle_Destroy(int);
void fn_8019FF6C(Sprite *, int);
void fn_80121E10(ResCtrl *);
int SpriteHandle_CreateDefault(ResCtrl *, int);
extern const float lbl_806DB9D8, lbl_806DB9DC, lbl_806DB9E0, lbl_806DB9E4;
}
#endif
