/* clFlashViewer: sprite animation browser, original deferred translation unit. */
#include "game/SpriteBrowser_private.h"
#include "game/types/SpriteObj.h"
#include "game/types/clJobRunner.h"

extern "C" {
void fn_8002CFB8(int, int, int, int);
void fn_8019FF6C(BrowserSprite *, int);
void Sprite_Destroy(BrowserSprite *, int);
extern const float lbl_806DA034, lbl_806DA038;
}

struct clFlashViewer : clJobRunner {
    virtual int Update();
    virtual void Draw();
    virtual ~clFlashViewer();
    int animation;
    int repeat;
    int fieldC;
    BrowserSprite *sprite;

    clFlashViewer() {
        fn_8002CFB8(0, 0x8F, 0, 0);
        animation = 0;
        repeat = 0;
        sprite = (BrowserSprite *)new SpriteObj(0, 1, 0);
        fn_8019FF6C(sprite, 1);
        sprite->SetPos(lbl_806DA034, lbl_806DA038);
    }
};

extern "C" clFlashViewer *fn_801D39BC() {
    return new clFlashViewer;
}

clFlashViewer::~clFlashViewer() {
    Sprite_Destroy(sprite, 1);
}

extern "C" {
extern const float lbl_806DA030, lbl_806DA03C, lbl_806DA040, lbl_806DA050;
extern const double lbl_806DA048;
void Sprite_SetupAnim(BrowserSprite *, int, int, int);
void fn_8019FF6C(BrowserSprite *, int);
void fn_801A1280();
void Sprite_AdvanceAnim(BrowserSprite *, float);
}

int clFlashViewer::Update() {
    float dt = lbl_806DA040;
    unsigned char changed = 0;
    BrowserInput *in = InputMgr_GetPlayer(GetInputManager(), 0);
    if (in->right() > lbl_806DA030) {
        if (in->pressed(0x2000)) {
            if ((animation += 10) >= 0x1EC) animation -= 0x1EC;
            changed = 1;
        }
        if (in->pressed(0x400)) {
            if ((animation -= 10) < 0) animation += 0x1EC;
            changed = 1;
        }
        if (repeat <= 0) {
            if (in->axis() >= lbl_806DA048) {
                if ((animation += 10) >= 0x1EC) animation -= 0x1EC;
                changed = 1;
                repeat = 10;
            } else if (in->axis() <= lbl_806DA050) {
                if ((animation -= 10) < 0) animation += 0x1EC;
                changed = 1;
                repeat = 10;
            }
        }
    } else {
        if (in->pressed(0x2000)) {
            if ((++animation) >= 0x1EC) animation = 0;
            changed = 1;
        }
        if (in->pressed(0x400)) {
            if ((--animation) < 0) animation = 0x1EB;
            changed = 1;
        }
        if (repeat <= 0) {
            if (in->axis() >= lbl_806DA048) {
                if ((++animation) >= 0x1EC) animation -= 0x1EC;
                changed = 1;
                repeat = 10;
            } else if (in->axis() <= lbl_806DA050) {
                if ((--animation) < 0) animation += 0x1EC;
                changed = 1;
                repeat = 10;
            }
        }
    }
    if (changed) {
        Sprite_SetupAnim(sprite, animation, 1, 0);
        fn_8019FF6C(sprite, 1);
        dt = lbl_806DA03C;
    }
    if (repeat > 0) repeat--;
    if (in->pressed(0x800)) {
        if (fn_8019FF50(sprite)) fn_8019FF6C(sprite, 0);
        else fn_8019FF6C(sprite, 1);
    }
    fn_801A1280();
    Sprite_AdvanceAnim(sprite, dt);
    return -2;
}

extern "C" {
extern const char *const lbl_806DA028;
extern const char *const lbl_806DA02C;
extern const float lbl_806DA030, lbl_806DA034, lbl_806DA038, lbl_806DA03C;
void *GetInputManager();
BrowserInput *InputMgr_GetPlayer(void *, int);
void OverlayText(int, int, int, const char *, ...);
int fn_8019FE58(BrowserSprite *);
float fn_8019FEBC(BrowserSprite *);
float fn_8019FED8(BrowserSprite *);
unsigned char fn_8019FF50(BrowserSprite *);
void fn_801A0004(BrowserSprite *);
void fn_8011FA98();
}
void clFlashViewer::Draw() {
    const char *states[2];
    states[0] = lbl_806DA028;
    states[1] = lbl_806DA02C;
    if (InputMgr_GetPlayer(GetInputManager(), 0)->left() <= lbl_806DA030) {
        OverlayText(2, 0, 0, "[FLASH TEST MODE]");
        OverlayText(2, 0, 1, " NAME-%03d : %s", animation, fn_8019FE58(sprite));
        OverlayText(2, 0, 2, " FRAME    : %f (MAX %f)", fn_8019FED8(sprite), fn_8019FEBC(sprite));
        OverlayText(2, 0, 3, " LOOP     : %s", states[fn_8019FF50(sprite)]);
        sprite->SetPos(lbl_806DA034, lbl_806DA038);
    } else {
        sprite->SetPos(lbl_806DA03C, lbl_806DA03C);
    }
    fn_801A0004(sprite);
    fn_8011FA98();
}
