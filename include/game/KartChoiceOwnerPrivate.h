#ifndef GAME_KARTCHOICEOWNERPRIVATE_H
#define GAME_KARTCHOICEOWNERPRIVATE_H
#include "game/FlowScene.h"

/* Private, target-observed views for 0x8023B318..0x8023C394 only. */
struct ChoiceStatus { char pad00[0x10]; unsigned long long bits; };
struct ChoiceRender {
    char pad000[0x1f4];
    int variant, character;
    char pad1fc[0x40];
    int unavailable;
    char pad240[0xc4];
    ChoiceStatus *status;
};
struct ChoiceOther : VObject {
    int field04, field08;
    float x, y, scale;
    char pad18[0x48];
    ChoiceOther(ChoiceRender *, int);
    virtual ~ChoiceOther();
};
struct ChoiceChild {
    virtual void _key();
    ~ChoiceChild();
    unsigned char hidden;
    ChoiceRender *render;
    int layer;
    int sprites[4];
    float x, y;
    int variant, resource, value, texture, alias;
    float scale;
    ChoiceChild(ChoiceRender *, int);
};
struct ChoiceRoot {
    virtual void _key();
    int countdown;
    ChoiceRoot() : countdown(-1) {}
    ~ChoiceRoot() {}
};
struct KartChoiceOwner : ChoiceRoot {
    int layer, phase, choice;
    ChoiceChild *child;
    ChoiceOther *other;
    VHolder<FlowFaderF> fade, scale;
    ChoiceRender *render;
    int state, selected;
    float x, y, vx, vy;
    KartChoiceOwner(int);
    ~KartChoiceOwner();
    virtual void _key2();
};
extern "C" {
extern const float lbl_806DB980, lbl_806DB984, lbl_806DB988, lbl_806DB98C;
extern const float lbl_806DB990, lbl_806DB994, lbl_806DB998, lbl_806DB99C;
extern const float lbl_806D6DE4, lbl_806D6DE8;
extern const float lbl_806DB970[2], lbl_806DB978, lbl_806DB97C;
extern const float lbl_803DC318[2][2];
extern int g_gameMode, g_countdownPhase;
void PreloadResource(int);
void fn_80121E10(ResCtrl *);
int SpriteHandle_CreateDefault(ResCtrl *, int);
void SpriteHandle_Destroy(int);
void SpriteHandle_SetActiveFlag(int, int);
void SpriteHandle_RecomputeCull(int);
void SpriteHandle_SetCornerAlpha(int, int);
void fn_8011F804(int, float, float);
void fn_8011F744(int, float, float);
void fn_80230ED4(ChoiceOther *, int);
void fn_80230ED8(ChoiceOther *, int);
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
unsigned char Sci2Card_GetByteFlag1224();
void *GetPlayerCarObject();
ChoiceRender *CarObject_GetRenderObj(void *);
unsigned char fn_802317E0(int *, int *, int *, int, int, unsigned char);
unsigned char fn_80231B74(int);
int fn_80231B94(int);
int fn_80231BD4(int, int, int);
int fn_8023D1B4(ChoiceRender *);
void fn_8023066C(ChoiceOther *);
void fn_802306B0(ChoiceOther *, int);
void fn_802306A0(ChoiceOther *, int);
void fn_80230684(ChoiceOther *, int);
unsigned char fn_80230644(ChoiceOther *);
void fn_80230678(ChoiceOther *);
void fn_8023B318(KartChoiceOwner *);
void fn_8023BEF0(ChoiceChild *);
}
#endif
