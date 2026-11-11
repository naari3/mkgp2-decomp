#ifndef GAME_TYPES_CLCRSDISP_H
#define GAME_TYPES_CLCRSDISP_H
#include "game/types/clCDispInterface.h"
/*
 * 0x80218F40..0x80219FF4: course minimap HUD (vtable clCrsDisp_vtable_804EDC2C, base
 * lbl_804EDB28 shared with the start countdown in anon_8021550C.cpp).
 *
 * sprites[0] is the course map, [1] the blinking own-kart ring, [2] the
 * own-kart marker and [3..10] the other karts in path order.
 */

#include "game/FlowScene.h"

extern "C" {
double sin(double x);
double cos(double x);
}

struct KartObj {
    char pad000[0x1F4];
    int playerId;
    int character;
    char pad1FC[0x24C - 0x1FC];
    int team;
    char pad250[0x2B8 - 0x250];
    unsigned char hidden;
};

struct PathEntry {
    int x0;
    int id;
    char pad08[0x90 - 0x8];
    KartObj *kart;
};

struct PathManager;

#include "game/types/MapInfo.h"

extern "C" {
extern const float lbl_803C4BF8[3][2];
extern const MapInfo lbl_803C4C10[][3];
extern const float lbl_806DAF40;
extern const float lbl_806DAF44;
extern const float lbl_806DAF48;
extern const float lbl_806DAF4C;
extern const float lbl_806DAF50;
extern const float lbl_806DAF54;
extern const float lbl_806DAF58;
extern const float lbl_806DAF5C;
extern int g_countdownPhase;
extern int g_gameMode;
extern int g_cupId;
extern int g_longRoundFlag;
void PreloadResource(int res);
void fn_80120A08(int res);
void fn_801208E0(int res, float *w, float *h);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, int active);
void SpriteHandle_RecomputeCull(int sprite);
void SpriteHandle_SetCornerAlpha(int sprite, unsigned char a);
void SpriteLayer_SetResource(int sprite, int res);
void fn_8011F804(int sprite, float x, float y);
void fn_8011F744(int sprite, float sx, float sy);
void fn_8011F7AC(int sprite, float s);
int GetDisplayBufferIndex(void);
PathEntry *PathManager_GetEntrySubStruct(PathManager *pm, int i);
float *KartDriver_GetKartRootMtx(KartObj *kart);
}

static inline int CupIndex() {
    int cup = g_cupId;
    if (cup >= 9) {
        cup -= 8;
    }
    return cup;
}

struct clCrsDisp : clCDispInterface {
    int state;
    int layer;
    int sprites[11];
    int variant;
    int resId;
    int *order;
    PathManager *path;
    KartObj *self;
    float x;
    float y;
    float scale;
    unsigned char others[8];
    VHolder<FlowFaderI> blink;
    VHolder<FlowFaderF> slide;
    VHolder<FlowFaderF> zoom;
    float slideX;
    clCrsDisp(int unused, int layer_);
    virtual ~clCrsDisp();
    virtual void Update();
    virtual void Draw();
    virtual void Start(int delay);
    void UpdateMarkers();
    void SetPath(PathManager *pm);
    void Layout() {
        int m = 0;
        if (g_gameMode == 1) {
            m = 1;
        } else if (g_gameMode == 2) {
            m = 2;
        }
        x = lbl_803C4BF8[m][0];
        y = lbl_803C4BF8[m][1];
        scale = lbl_806DAF44;
        float w, h;
        fn_801208E0(resId, &w, &h);
    }
};


#endif
