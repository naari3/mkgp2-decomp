/*
 * 0x802128F4..0x80212EA4: JumpDistanceMode kart launch stepper.
 */

#include "game/JumpDistanceMode.h"

extern "C" {
void *memcpy(void *dst, const void *src, unsigned long n);
unsigned char IsCardValid(void);
float Cosf_LUT_Wrap(float x);
float LUT_Sin12Bit(float x);
void fn_8016C3C8(int se, int a);
void SoundMgr_PlaySE(int se);
extern const float lbl_80495994[64];
extern const float lbl_806DAD70;
extern const float lbl_806DAD84;
extern const float lbl_806DAD8C;
extern const float lbl_806DADB4;
extern const float lbl_806DADDC;
extern const float lbl_806DADF8;
extern const float lbl_806DADFC;
extern const float lbl_806DAE00;
extern const float lbl_806DAE04;
}

/* ---- kart launch stepper ---- */

struct KartRender {
    char pad000[0x20];
    void *jobj;
    char pad024[0x1CC - 0x24];
    float scale1CC;
    char pad1D0[0x1D8 - 0x1D0];
    float speed;
    char pad1DC[0x320 - 0x1DC];
    float lift;
    char pad324[0x37C - 0x324];
    float scale37C;
};

struct CarObject {
    virtual void v0();
    virtual ~CarObject();
    char pad004[0xD4 - 0x4];
    unsigned char stepping;
};

/* Kart root position (dtor dtor_80036E40). */
struct KartPos {
    float x, y, z;
    KartPos() {}
    void Set(float px, float py, float pz) { x = px; y = py; z = pz; }
    ~KartPos() {}
};

extern "C" {
KartRender *CarObject_GetRenderObj(CarObject *car);
float *KartDriver_GetKartRootMtx(KartRender *r);
float *CarObject_GetTransformMatrix(CarObject *car);
void *KartItem_GetCarObjectSoundCh(CarObject *car);
float TornadoEffect_GetField114(void *t);
void CarObject_FrameUpdate(CarObject *car, int a);
unsigned char CarObject_IsAirborne(CarObject *car);
void KartItem_ForwardToCarMovement_8019a4e0(CarObject *car, float *mtx);
void KartDriver_TickAction_79244(KartRender *r, float t);
void Object_SetField14_IfValid(void *jobj, float v);
}

static inline void AddLift(CarObject *car, float lift) {
    CarObject_GetRenderObj(car)->lift += lift;
}

extern "C" void fn_802128F4(JumpGauge *g, CarObject *car) {
    if ((g->running || g->start) && car != 0) {
        KartPos pos;
        float *m = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car));
        pos.Set(m[3], m[7], m[11]);
        if (g->start == 1) {
            g->start = 0;
            if (!g->running && !g->landed) {
                g->running = 1;
                CarObject_GetRenderObj(car)->scale37C = g->step;
                CarObject_GetRenderObj(car)->scale1CC = g->step;
                {
                    float speed = CarObject_GetRenderObj(car)->speed;
                    float factor = g->step;
                    factor *= speed;
                    CarObject_GetRenderObj(car)->speed = factor;
                }
                g->lift = -(lbl_806DAE04 * (lbl_806DAD70 - g->step));
            }
        }
        if (g->running == 1 && g->landed == 1) {
            g->start = 0;
            g->running = 0;
            g->landed = 0;
            car->stepping = 1;
            { KartRender *r = CarObject_GetRenderObj(car); r->scale37C = lbl_806DAD70; }
            { KartRender *r = CarObject_GetRenderObj(car); r->scale1CC = lbl_806DAD70; }
            {
                float speed = CarObject_GetRenderObj(car)->speed;
                float factor = g->div;
                factor *= speed;
                CarObject_GetRenderObj(car)->speed = factor;
            }
            if (CarObject_GetRenderObj(car)->jobj != 0) {
                Object_SetField14_IfValid(CarObject_GetRenderObj(car)->jobj, lbl_806DAD70);
            }
            return;
        }
        if (++g->count >= g->div) {
            g->count = 0;
            float h = TornadoEffect_GetField114(KartItem_GetCarObjectSoundCh(car));
            memcpy(g->mtx, CarObject_GetTransformMatrix(car), 0x40);
            car->stepping = 1;
            CarObject_FrameUpdate(car, 0);
            car->stepping = 0;
            if (!CarObject_IsAirborne(car)) {
                if (fn_8016C360(0x42) == 1) {
                    fn_8016C3C8(0x42, 1);
                }
                g->landed = 1;
            }
            m = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car));
            float x = m[3];
            float y = m[7];
            float z = m[11];
            float cur[16];
            memcpy(cur, CarObject_GetTransformMatrix(car), 0x40);
            for (int i = 0; i < 16; i++) {
                g->delta[i] = g->step * (cur[i] - g->mtx[i]);
            }
            g->delta[12] = g->step * (x - pos.x);
            g->delta[13] = g->step * (y - pos.y);
            g->delta[14] = g->step * (z - pos.z);
            g->spin = g->step * (TornadoEffect_GetField114(KartItem_GetCarObjectSoundCh(car)) - h);
            {
                float lift = g->lift;
                KartRender *r = CarObject_GetRenderObj(car);
                r->lift += lift;
            }
            if (CarObject_GetRenderObj(car)->jobj != 0) {
                Object_SetField14_IfValid(CarObject_GetRenderObj(car)->jobj, g->step);
            }
        }
        float lift = g->lift;
        KartRender *r = CarObject_GetRenderObj(car);
        r->lift += lift;
        g->mtx[12] = pos.x;
        g->mtx[13] = pos.y;
        g->mtx[14] = pos.z;
        for (int i = 0; i < 16; i++) {
            g->mtx[i] += g->delta[i];
        }
        KartItem_ForwardToCarMovement_8019a4e0(car, g->mtx);
        KartDriver_TickAction_79244(CarObject_GetRenderObj(car), g->spin * g->count);
    }
}
