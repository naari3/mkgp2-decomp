/*
 * 0x80230404..0x80230644: clENo3D, the player-number badge drawn next to a
 * rival's face icon in network battle mode.
 */

void operator delete(void *p) throw();

extern "C" {
void *PcbSlot_GetByIndex(int slot);
extern int g_gameMode;
extern int g_localPcbRole;
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

struct KartStatus {
    char pad0[0x10];
    unsigned long long bits;
};

struct KartRender {
    char pad0[0x1F4];
    int slot;
    int chara;
    char pad1FC[0x304 - 0x1FC];
    KartStatus *status;
};

class clENo3D {
public:
    virtual ~clENo3D() {}
    KartRender *kart;
    float x, y, z;
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
        if ((kart->status->bits & 0x8000000000ULL) == 0) {
            hidden = 0;
        } else {
            hidden = 1;
        }
        if (hidden != 1 && !(scale < 0.5f)) {
            float s = 1.5300002f * scale;
            float px = -35.0f * s + x;
            float py = y;
            s *= 0.5f;
            ResCtrl r;
            r.fieldc = 1;
            r.resId = resId;
            r.Show(px, py, z);
            r.SetScale(s);
            fn_8011FAFC(&r, prio);
        }
    }
}

void clENo3D::SetPos(const float *pos) {
    x = pos[0];
    y = pos[1];
    z = pos[2];
}

clENo3D::clENo3D(KartRender *k, int p) {
    kart = k;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    scale = 1.0f;
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
