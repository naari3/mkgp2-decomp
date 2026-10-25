/*
 * 0x80224ECC..0x802253EC: fade-in/out banner scene (vtable lbl_804EDF14,
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

struct SceneObj {
    char pad00[0x20];
    SceneObj(int a, int b, int c, int d, int e);
    ~SceneObj();
    void Update();
    void Draw();
};

struct RoundInfo {
    unsigned char flag;
    char pad01[0xF];
    int x10;
};

extern "C" {
extern InputState *g_pInputState;
extern int g_gameMode;
extern int g_roundIndex;
extern const char lbl_806D0508[4];
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
void fn_8023F5B4(Sprite **out, float x, float y, const char *name, int flag);
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

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
    SceneBase() : done(false) {}
};

struct clCSSceneBanner : SceneBase {
    SceneObj *obj;
    int xc;
    int timer;
    int state;
    Sprite *spr;
    int fade;
    clCSSceneBanner();
    ~clCSSceneBanner();
    void Destroy();
    void Update();
    void Draw();
};

void clCSSceneBanner::Draw() {
    if (spr) {
        fn_801A0004(spr);
    }
    obj->Draw();
}

void clCSSceneBanner::Update() {
    if (done == 1) {
        return;
    }
    bool pressed = false;
    if (GetInput()->held == 1) {
        pressed = true;
    }
    switch (state) {
    case 0:
        SpriteHandle_SetCornerAlpha(fade, (int)(lbl_806DB320 * (timer / lbl_806DB324)));
        if (timer >= 30) {
            state = 1;
            timer = 0;
        }
        break;
    case 1:
        spr->alpha = timer / lbl_806DB328;
        if (timer >= 20) {
            state = 2;
            timer = 0;
        }
        break;
    case 2:
        if (timer >= 120 || pressed) {
            state = 3;
            timer = 0;
        }
        break;
    case 3:
        spr->alpha = lbl_806DB32C - timer / lbl_806DB328;
        if (timer >= 20) {
            state = 4;
            timer = 0;
        }
        break;
    case 4:
        SpriteHandle_SetCornerAlpha(fade, (int)lbl_806DB330);
        if (timer >= 30) {
            done = 1;
        }
        break;
    }
    timer++;
    if (spr) {
        Sprite_AdvanceAnim(spr, lbl_806DB334);
    }
    obj->Update();
    SpriteHandle_RecomputeCull(fade);
}

clCSSceneBanner::~clCSSceneBanner() {
    fn_80169C44();
    SpriteHandle_Destroy(fade);
    if (obj) {
        delete obj;
        obj = 0;
    }
    if (spr) {
        delete spr;
    }
    spr = 0;
}

void clCSSceneBanner::Destroy() {
    delete this;
}

clCSSceneBanner::clCSSceneBanner() {
    obj = 0;
    xc = 0;
    timer = 0;
    state = 0;
    spr = 0;
    obj = new SceneObj(-1, -1, -1, -1, 5);
    bool show = false;
    if (g_gameMode == 0 && fn_8024F588()->flag == 1 && g_roundIndex != 3 && g_roundIndex != 7) {
        show = true;
    }
    if (fn_8024F588()->x10 >= 0) {
        done = 1;
        state = 4;
    }
    CreditMgr_SetActiveSlot(1);
    InitRumbleController(1);
    if (!show) {
        state = 4;
        done = 1;
    }
    fn_8023F5B4(&spr, lbl_806DB340, lbl_806DB344, lbl_806D0508, 1);
    spr->alpha = lbl_806DB330;
    ResCtrl rc;
    rc.mode = 2;
    rc.SetSize(lbl_806DB348, lbl_806DB34C);
    rc.Show(lbl_806DB340, lbl_806DB350, lbl_806DB32C);
    rc.SetColor(0);
    fade = SpriteHandle_CreateDefault(&rc, 3);
}

extern "C" clCSSceneBanner *fn_802253B0(void) {
    return new clCSSceneBanner;
}
