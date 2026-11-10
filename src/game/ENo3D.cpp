/*
 * 0x80230404..0x80230644: clENo3D, the player-number badge drawn next to a
 * rival's face icon in network battle mode.
 *
 * The RTTI name "clENo3D" sits in .sdata2 (-rostr) right after this TU's
 * float pool, which stays in the unsplit pool and is referenced by name.
 */

void operator delete(void *p) throw();

extern "C" {
void *PcbSlot_GetByIndex(int slot);
extern int g_gameMode;
extern int g_localPcbRole;
extern const float lbl_806DB6B8; /* -35.0 */
extern const float lbl_806DB6C0; /* 1.53 */
extern const float lbl_806DB6C4; /* 0.5 */
extern const float lbl_806DB6CC; /* 0.0 */
extern const float lbl_806DB6D0; /* 1.0 */
}

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
    void SetScale(float s) {
        scaleX = s;
        scaleY = s;
    }
};

void fn_8011FAFC(ResCtrl *r, int prio);

struct PcbSlot {
    unsigned char pad : 1;
    unsigned char role : 3;
};

#include "game/ItemEffectBusPrivate.h"

struct ItemEffectBus;

/* Merged from 14 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartRender KartRender;
struct KartRender {
    /* 0x000 */ unsigned char pad_000[0x1F4];
    /* 0x1F4 */ int slot;
    /* 0x1F8 */ int chara;
    /* 0x1FC */ unsigned char pad_1FC[0x3C];
    /* 0x238 */ int visible;
    /* 0x23C */ unsigned char middle[0x90];
    /* 0x2CC */ int coins;
    /* 0x2D0 */ unsigned char special;  /* also: active */
    /* 0x2D1 */ unsigned char pad_2D1[0x33];
    /* 0x304 */ struct ItemEffectBus *status;
};

/* Badge position; its empty inline dtor is the shared dtor_80036E40. */
struct ENo3DPos {
    float x, y, z;
    ~ENo3DPos() {}
};

class clENo3D {
public:
    virtual ~clENo3D();
    KartRender *kart;
    ENo3DPos pos;
    float scale;
    int prio;
    unsigned char enabled;
    int resId;

    clENo3D(KartRender *k, int p);
    void Draw();
    void SetPos(const float *pos);
};

void clENo3D::Draw() {
    if (enabled) {
        unsigned char hidden;
        if ((kart->status->mask & 0x8000000000ULL) == 0) {
            hidden = 0;
        } else {
            hidden = 1;
        }
        if (hidden != 1) {
            float sc = scale;
            if (!(sc < lbl_806DB6C4)) {
                float s = lbl_806DB6C0 * sc;
                float px = lbl_806DB6B8 * s + pos.x;
                float py = pos.y;
                s *= lbl_806DB6C4;
                ResCtrl r;
                r.fieldc = 1;
                r.resId = resId;
                r.Show(px, py, pos.z);
                r.SetScale(s);
                fn_8011FAFC(&r, prio);
            }
        }
    }
}

void clENo3D::SetPos(const float *p) {
    pos.x = p[0];
    pos.y = p[1];
    pos.z = p[2];
}

clENo3D::~clENo3D() {}

clENo3D::clENo3D(KartRender *k, int p) {
    kart = k;
    pos.x = lbl_806DB6CC;
    pos.y = lbl_806DB6CC;
    pos.z = lbl_806DB6CC;
    scale = lbl_806DB6D0;
    prio = p;
    enabled = 1;
    resId = -1;
    int slot = k->slot;
    if (slot != 6) {
        unsigned char *pcb = (unsigned char *)PcbSlot_GetByIndex(slot);
        if (((pcb[0] >> 4) & 7) == g_localPcbRole) {
            resId = slot + 0xC29;
        }
    }
    if (resId < 0) {
        enabled = 0;
    }
    if (g_gameMode != 2) {
        enabled = 0;
    }
}
