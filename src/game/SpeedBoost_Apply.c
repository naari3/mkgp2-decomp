#include "game/types/BoostKart.h"

typedef struct SpeedBoost {
    unsigned char isPlayer;
    unsigned char pad_01[3];
    BoostKart *kart;
    void *body;
    void *shadow;
    float duration;
    float elapsed;
    int level;
} SpeedBoost;

extern void *lbl_806D109C;
extern void KartBody_SetWarpTransitFlag(void *, int);
extern void ShadowBillboard_BeginBoostScale(void *);
#ifdef __MWERKS__
extern void CameraEffect_Apply(void *, float, int);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void CameraEffect_Apply(void *, int, float);
static inline void CameraEffect_Apply_Reordered(void *a0, float a1, int a2) { CameraEffect_Apply(a0, a2, a1); }
#define CameraEffect_Apply CameraEffect_Apply_Reordered
#endif
extern void ShadowBillboard_SetField0xA4(void *, float);

static inline void kart_set_level(BoostKart *kart, int level, float minTimer) {
    if (level >= 0 && level < kart->levelCount) {
        if (kart->timer < minTimer) {
            kart->timer = minTimer;
        }
        kart->level = level;
    }
}

static inline void *camera_effect(void) {
    void *mgr = lbl_806D109C;

    if (mgr == 0) {
        return 0;
    }
    return mgr;
}

void SpeedBoost_Apply(SpeedBoost *boost, int level, float duration) {
    if (level != 0) {
        boost->level = level;
        boost->duration = duration;
        boost->elapsed = 0.0f;
        boost->kart->accelScale = 0.6f;
        kart_set_level(boost->kart, boost->level, 0.0f);
        KartBody_SetWarpTransitFlag(boost->body, 1);
        ShadowBillboard_BeginBoostScale(boost->shadow);
        if (boost->isPlayer == 1) {
            CameraEffect_Apply(camera_effect(), 0.25f, 4);
            ShadowBillboard_SetField0xA4(boost->shadow, -3.0f);
        }
    }
}
