/*
 * 0x80218F40..0x80219FF4: course minimap HUD (vtable lbl_804EDC2C, base
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

struct MapInfo {
    float ox;
    float oy;
    float sx;
    float sy;
    float rot;
};

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

struct MapBase {
    virtual ~MapBase() {}
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Start(int delay) = 0;
    virtual void _keyB();
    int delay;
    MapBase() : delay(-1) {}
};

struct MinimapHud : MapBase {
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
    MinimapHud(int unused, int layer_);
    ~MinimapHud();
    void Update();
    void Draw();
    void Start(int delay);
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

void MinimapHud::Start(int n) {
    if (state < 4) {
        delay = n + 1;
    }
}

void MinimapHud::Draw() {
}

void MinimapHud::Update() {
    switch (state) {
    case -1:
        if (g_countdownPhase < 4) {
            state = 0;
            slide.p->Set(lbl_806DAF40, lbl_806DAF44, 7);
        }
        break;
    case 0:
        slideX = slide.p->Value();
        slide.p->Step();
        if (slide.p->Done()) {
            state = 1;
            slideX = lbl_806DAF44;
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            zoom.p->Set(lbl_806DAF48, lbl_806DAF4C, 4);
            state = 2;
        }
        break;
    case 2:
        if (zoom.p->Done() && lbl_806DAF48 == zoom.p->Value()) {
            state = 3;
        }
        break;
    case 3:
        break;
    case 4:
        slideX = slide.p->Value();
        slide.p->Step();
        if (slide.p->Done()) {
            state = 5;
            for (int i = 0; i < 11; i++) {
                SpriteHandle_SetActiveFlag(sprites[i], 0);
                SpriteHandle_RecomputeCull(sprites[i]);
            }
        }
        break;
    case 5:
        fn_80120A08(resId);
        switch (CupIndex()) {
        case 4:
            fn_80120A08(0xC14);
            break;
        case 6:
            fn_80120A08(0xC16);
            break;
        }
        return;
    default:
        return;
    }
    if (delay > 0) {
        delay--;
        if (delay <= 0) {
            delay = 0;
            state = 4;
            slide.p->Set(lbl_806DAF44, lbl_806DAF40, 7);
        }
    }
    if (self != 0) {
        int cup = CupIndex();
        int longRound = g_longRoundFlag;
        if (cup == 4) {
            if (longRound == 1) {
                if (self->team == 0) {
                    variant = 1;
                    resId = 0xC12;
                } else {
                    variant = 2;
                    resId = 0xC14;
                }
            }
        } else if (cup == 6) {
            if (self->team == 0) {
                variant = 0;
                resId = 0xC16;
            } else if (longRound == 0) {
                variant = 1;
                resId = 0xC18;
            } else {
                variant = 2;
                resId = 0xC1A;
            }
        }
    }
    if (path != 0) {
        int cup = CupIndex();
        int longRound = g_longRoundFlag;
        int res = resId;
        if (cup == 4) {
            if (longRound == 1) {
                Layout();
            }
        } else if (cup == 6) {
            Layout();
        }
        fn_8011F804(sprites[0], x - slideX, y);
        fn_8011F7AC(sprites[0], scale);
        SpriteLayer_SetResource(sprites[0], res);
        SpriteHandle_SetActiveFlag(sprites[0], 1);
        UpdateMarkers();
    }
    blink.p->Step();
    if (blink.p->Done()) {
        if (blink.p->Value() == 0x7F) {
            blink.p->Set(0x7F, 0xFF, 30);
        } else {
            blink.p->Set(0xFF, 0x7F, 30);
        }
    }
    zoom.p->Step();
    if (zoom.p->Done()) {
        float v = zoom.p->Value();
        if (lbl_806DAF4C == v) {
            zoom.p->Set(lbl_806DAF4C, lbl_806DAF48, 4);
        } else if (lbl_806DAF48 == v) {
            zoom.p->Set(lbl_806DAF48, lbl_806DAF48, 1);
        }
    }
    float z = zoom.p->Value();
    for (int i = 0; i < 3; i++) {
        fn_8011F744(sprites[i], z, z);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    float k = lbl_806DAF50;
    for (int i = 3; i < 11; i++) {
        float s;
        if (others[i - 3] == 1) {
            s = k * zoom.p->Value();
        } else {
            s = zoom.p->Value();
        }
        fn_8011F744(sprites[i], s, s);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}

static inline void WorldToMap(MinimapHud *h, float &px, float &pz) {
    const MapInfo *mi = &lbl_803C4C10[CupIndex()][h->variant];
    float ang = lbl_806DAF54 * mi->rot;
    ang += h->scale;
    float rx;
    float rz;
    if (lbl_806DAF44 != ang) {
        float s = sin(ang);
        float c = cos(ang);
        rx = px * c - pz * s;
        rz = px * s + pz * c;
    } else {
        rx = px;
        rz = pz;
    }
    rx *= mi->sx;
    rz *= mi->sy;
    if (rx < lbl_806DAF58) {
        rx = lbl_806DAF58;
    } else if (rx > lbl_806DAF5C) {
        rx = lbl_806DAF5C;
    }
    if (rz < lbl_806DAF58) {
        rz = lbl_806DAF58;
    } else if (rz > lbl_806DAF5C) {
        rz = lbl_806DAF5C;
    }
    rx += mi->ox;
    rz += mi->oy;
    rx -= h->slideX;
    pz = h->y + rz;
    px = h->x + rx;
}

void MinimapHud::UpdateMarkers() {
    float px = lbl_806DAF44;
    float pz = lbl_806DAF44;
    int me = GetDisplayBufferIndex();
    int cup7 = g_cupId == 7;
    int myTeam = self->team;
    for (int i = 7; i >= 0; i--) {
        if (order[i] == -1) {
            continue;
        }
        PathEntry *e = PathManager_GetEntrySubStruct(path, i);
        int slot = i + 3;
        int pid = e->kart->playerId;
        if (pid >= 0 && pid <= 3) {
            if (pid == me) {
                slot = 2;
                int res = 0xBCC;
                if (g_gameMode == 2) {
                    res = pid + 0xBCD;
                }
                SpriteLayer_SetResource(sprites[2], res);
            } else {
                SpriteLayer_SetResource(sprites[slot], pid + 0xBCD);
                others[i] = 1;
            }
        } else if (pid == 4 && e->kart->hidden == 1) {
            SpriteHandle_SetActiveFlag(sprites[slot], 0);
            continue;
        } else {
            SpriteLayer_SetResource(sprites[slot], 0xBD1);
            fn_8011F744(sprites[slot], lbl_806DAF48, lbl_806DAF48);
            others[i] = 0;
        }
        float *m = KartDriver_GetKartRootMtx(e->kart);
        px = m[3];
        pz = m[11];
        WorldToMap(this, px, pz);
        fn_8011F804(sprites[slot], px, pz);
        bool sameTeam = e->kart->team == myTeam;
        int vis = 0;
        if (cup7 || sameTeam) {
            vis = 1;
        }
        SpriteHandle_SetActiveFlag(sprites[slot], vis);
        if (pid == me) {
            SpriteHandle_SetCornerAlpha(sprites[1], blink.p->Value());
            fn_8011F804(sprites[1], px, pz);
            SpriteHandle_SetActiveFlag(sprites[1], 1);
        }
    }
}

void MinimapHud::SetPath(PathManager *pm) {
    if (pm == 0) {
        return;
    }
    path = pm;
    int i;
    int n = 0;
    for (i = 0; i < 8; i++) {
        PathEntry *e = PathManager_GetEntrySubStruct(pm, i);
        if (e == 0 || e->id == -1) {
            continue;
        }
        int c = e->kart->character;
        if (c <= -1 || c >= 13) {
            continue;
        }
        int pid = e->kart->playerId;
        if (pid == GetDisplayBufferIndex()) {
            self = e->kart;
        }
        order[n++] = i;
        if (n >= 8) {
            break;
        }
    }
}

extern "C" MinimapHud *fn_80219900(int unused, int layer) {
    return new MinimapHud(unused, layer);
}

MinimapHud::~MinimapHud() {
    int i;
    for (i = 0; i < 11; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
    delete[] order;
    fn_80120A08(resId);
    switch (CupIndex()) {
    case 4:
        fn_80120A08(0xC14);
        break;
    case 6:
        fn_80120A08(0xC16);
        break;
    }
    fn_80120A08(0xBCC);
    fn_80120A08(0xBD2);
    fn_80120A08(0xBD1);
    for (i = 0; i < 4; i++) {
        fn_80120A08(i + 0xBCD);
    }
}

MinimapHud::MinimapHud(int unused, int layer_)
    : state(-1), layer(layer_), variant(0), resId(0), order(0), path(0), self(0), x(lbl_806DAF44),
      y(lbl_806DAF44), scale(lbl_806DAF44), blink(new FlowFaderI), slide(new FlowFaderF(lbl_806DAF44)),
      zoom(new FlowFaderF(lbl_806DAF44)) {
    zoom.p->Set(lbl_806DAF48, lbl_806DAF48, 1);
    order = new int[8];
    resId = 0xC0C;
    int cup = CupIndex();
    int longRound = g_longRoundFlag;
    switch (cup) {
    case 1:
        resId = longRound == 0 ? 0xC0C : 0xC0E;
        break;
    case 2:
        resId = longRound == 0 ? 0xC04 : 0xC06;
        break;
    case 3:
        resId = longRound == 0 ? 0xC00 : 0xC02;
        break;
    case 4:
        resId = longRound == 0 ? 0xC10 : 0xC12;
        if (resId == 0xC12) {
            PreloadResource(0xC14);
        }
        break;
    case 5:
        resId = longRound == 0 ? 0xC08 : 0xC0A;
        break;
    case 6:
        PreloadResource(0xC16);
        resId = longRound == 0 ? 0xC18 : 0xC1A;
        PreloadResource(resId);
        resId = 0xC16;
        break;
    case 7:
        resId = longRound == 0 ? 0xC20 : 0xC22;
        break;
    case 8:
        resId = longRound == 0 ? 0xC1C : 0xC1E;
        break;
    default:
        resId = longRound == 0 ? 0xC0C : 0xC0E;
        break;
    }
    PreloadResource(resId);
    PreloadResource(0xBCC);
    PreloadResource(0xBD2);
    PreloadResource(0xBD1);
    for (int i = 0; i < 4; i++) {
        PreloadResource(i + 0xBCD);
    }
    if (CupIndex() == 6) {
        variant = 0;
    } else {
        variant = g_longRoundFlag;
    }
    Layout();
    slideX = lbl_806DAF40;
    order[0] = -1;
    order[1] = -1;
    order[2] = -1;
    order[3] = -1;
    order[4] = -1;
    order[5] = -1;
    order[6] = -1;
    order[7] = -1;
    blink.p->Set(0x7F, 0xFF, 30);
    ResCtrl a;
    a.resId = resId;
    sprites[0] = SpriteHandle_CreateDefault(&a, layer);
    ResCtrl b;
    b.resId = 0xBD1;
    for (int i = 3; i < 11; i++) {
        sprites[i] = SpriteHandle_CreateDefault(&b, layer);
    }
    ResCtrl c;
    c.resId = 0xBD2;
    sprites[1] = SpriteHandle_CreateDefault(&c, layer);
    ResCtrl d;
    d.resId = 0xBCC;
    sprites[2] = SpriteHandle_CreateDefault(&d, layer);
    for (int i = 0; i < 11; i++) {
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    others[0] = 0;
    others[1] = 0;
    others[2] = 0;
    others[3] = 0;
    others[4] = 0;
    others[5] = 0;
    others[6] = 0;
    others[7] = 0;
}
