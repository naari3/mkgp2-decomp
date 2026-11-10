/*
 * 0x80224ECC..0x802253EC: fade-in/out banner scene (vtable clCSSceneGetRace_vtable_804EDF14,
 * base clSceneInterface lbl_803FE0C8). Fades the screen in, shows a sprite
 * for up to two seconds (or until the button is pressed) and fades out.
 */

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    bool flipX;
    bool flipY;
    char pad46[2];
    int tail[4];
    ResCtrl();
    ~ResCtrl() {}
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetSize(float w, float h) {
        width = w;
        height = h;
    }
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
};
void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct InputState {
    char pad00[0x18];
    int held;
};

struct Sprite {
    char pad00[0x20];
    float alpha;
    ~Sprite();
};

#include "game/types/SceneObj.h"

struct RoundInfo {
    unsigned char flag;
    char pad01[0xF];
    int x10;
};

extern "C" {
extern InputState *g_pInputState;
extern int g_gameMode;
extern int g_roundIndex;
extern const float lbl_806DB320;
extern const float lbl_806DB324;
extern const float lbl_806DB328;
extern const float lbl_806DB32C;
extern const float lbl_806DB330;
extern const float lbl_806DB334;
extern const float lbl_806DB340;
extern const float lbl_806DB344;
extern const float lbl_806DB348;
extern const float lbl_806DB34C;
extern const float lbl_806DB350;
RoundInfo *fn_8024F588(void);
void fn_80169C44(void);
void CreditMgr_SetActiveSlot(int slot);
int InitRumbleController(int deviceId);
#include "game/types/SpriteResourceId.h"
void fn_8023F5B4(Sprite **out, const SpriteResourceId *resource, int enabled, float x, float y);
void fn_801A0004(Sprite *spr);
unsigned char Sprite_AdvanceAnim(Sprite *spr, float dt);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetCornerAlpha(int sprite, int alpha);
void SpriteHandle_RecomputeCull(int sprite);
}

static inline void DeleteSprite(Sprite *&s) {
    if (s) {
        delete s;
        s = 0;
    }
}

static inline InputState *GetInput() {
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
}

#include "game/types/clSceneInterface.h"

struct clCSSceneGetRace : clSceneInterface {
    SceneObj *obj;
    int xc;
    int timer;
    int state;
    Sprite *spr;
    int fade;
    clCSSceneGetRace();
    ~clCSSceneGetRace();
    void Destroy();
    void Update();
    void Draw();
};

