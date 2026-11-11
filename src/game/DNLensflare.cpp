/*
 * 0x80228FB0..0x8022929C: clDNLensflare (Dino Dino Jungle halation).
 * Four lens flares ("halation.dat") that only draw while the player is
 * inside one rectangle of the course. The TU owns .rodata
 * 0x803D08A8..0x803D08F0.
 */

#include "game/types/size_t.h"
void *operator new(size_t size);
void operator delete(void *p) throw();

#include "game/types/clMapEffectParts.h"

struct clLensFlare : clMapEffectParts {
    char pad[0x78];
    virtual void Enable(int on);
    virtual ~clLensFlare();
    clLensFlare(const char *res, float x, float y, float z, float scale, float spread);
};

struct clDNLensflare : clMapEffectParts {
    clLensFlare *flares[4];

    clDNLensflare();
    virtual ~clDNLensflare();
    virtual void Update();
    virtual void Draw();
};

struct KartRender;

extern "C" {
extern KartRender *g_playerRenderObj;
const float *KartDriver_GetKartRootMtx(KartRender *k);
}

extern const float DNLensflare_rodata_803D08A8[4] = {5000.0f, -3000.0f, 2000.0f, -8000.0f};

clDNLensflare::clDNLensflare() {
    flares[0] = new clLensFlare("halation.dat", 458.3421f, 909.9976f, -7634.53f, 0.5f, 0.35f);
    flares[1] = new clLensFlare("halation.dat", 4741.658f, 909.9976f, -7634.53f, 0.5f, 0.35f);
    flares[2] = new clLensFlare("halation.dat", 458.3416f, 909.9976f, -365.467f, 0.5f, 0.35f);
    flares[3] = new clLensFlare("halation.dat", 4741.653f, 909.9976f, -365.467f, 0.5f, 0.35f);
}

clDNLensflare::~clDNLensflare() {
    for (int i = 0; i < 4; i++) {
        if (flares[i]) {
            delete flares[i];
            flares[i] = 0;
        }
    }
}


void clDNLensflare::Update() {
    for (int i = 0; i < 4; i++) {
        flares[i]->Update();
    }
}


void clDNLensflare::Draw() {
    const float *m = KartDriver_GetKartRootMtx(g_playerRenderObj);
    float x = m[3];
    float z = m[11];
    unsigned char away = 0;
    if (DNLensflare_rodata_803D08A8[0] < x) {
        away = 1;
    }
    if (DNLensflare_rodata_803D08A8[2] > x) {
        away = 1;
    }
    if (DNLensflare_rodata_803D08A8[1] < z) {
        away = 1;
    }
    if (DNLensflare_rodata_803D08A8[3] > z) {
        away = 1;
    }
    if (away) {
        for (int i = 0; i < 4; i++) {
            flares[i]->Draw();
        }
    }
}
