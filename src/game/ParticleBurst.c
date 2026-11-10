/*
 * ParticleBurst @ 0x800B4164..0x800B4804.
 *
 * A burst of 36 coloured quads: Update allocates the particle array, gives
 * each particle a random launch velocity/spin (the second half launches
 * with a per-particle delay), then integrates them with gravity until all
 * have left the screen; DrawCb queues Draw in the sorted draw list; Draw
 * emits one screen-space quad per live particle through the GX FIFO.
 */

typedef float Mtx44[4][4];
typedef float Mtx34[3][4];

typedef struct Particle {
    float x;      /* 0x00 */
    float y;      /* 0x04 */
    float z;      /* 0x08 */
    float rot;    /* 0x0C */
    float vx;     /* 0x10 */
    float vy;     /* 0x14 */
    float vrot;   /* 0x18 */
    signed char delay; /* 0x1C */
    signed char dead;  /* 0x1D */
} Particle;

#include "game/types/WGPipe.h"

#define GXFIFO (*(volatile WGPipe *)0xCC008000)

static inline void GXPosition3f32(float x, float y, float z) {
    GXFIFO.f32 = x;
    GXFIFO.f32 = y;
    GXFIFO.f32 = z;
}

static inline void GXColor4u8(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    GXFIFO.u8 = r;
    GXFIFO.u8 = g;
    GXFIFO.u8 = b;
    GXFIFO.u8 = a;
}

#define PARTICLES(self) (*(Particle **)((self) + 0xCC))
#define NUM_PARTICLES 36

extern void GXSetZMode(int enable, int func, int update);
extern void GXBegin(int prim, int fmt, int n);
extern void GXLoadPosMtxImm(Mtx34 *m, int id);
extern void GXSetCurrentMtx(int id);
extern void HSD_StateSetCullMode(int mode);
extern void HSD_StateInitDirect(int a, int flags);
extern void DbgScene_CopyMatrix3x4Transpose(Mtx34 *dst, Mtx44 *src);
extern void Matrix4_Identity(Mtx44 *m);
extern void Matrix4_PreMultiplyRotZ(Mtx44 *dst, Mtx44 *src, float a);
extern void Matrix4_PreMultiplyTranslation(Mtx44 *dst, Mtx44 *src, float x, float y, float z);
extern float BuildOrientationFromYaw(float yaw);
extern void DrawEffect_Free(void *eff);
extern Particle *FUN_8003b120(unsigned long size);
extern void MemoryManager_Free(void *p);
extern float Rand_RangeFloat(float lo, float hi);
extern float Rand_RangeFloatMax(float max);
extern double sin(double);
extern double cos(double);

extern const float lbl_806D5020;
extern const float lbl_806D5024;
extern const float lbl_806D5028;
extern const float lbl_806D5034;
extern const float lbl_806D5044;
extern const float lbl_806D506C;
extern const float lbl_806D5070;
extern const float lbl_806D5074;
extern const float lbl_806D5080;
extern const float lbl_806D5084;
extern const float lbl_806D5090;
extern const float lbl_806D509C;
extern const float lbl_806D50A0;
extern const float lbl_806D50E4;
extern const float lbl_806D5134;
extern const float lbl_806D5140;
extern const float lbl_806D5144;
extern const float lbl_806D5148;
extern const float lbl_806D514C;
extern const float lbl_806D5150;
extern const float lbl_806D5154;
extern const float lbl_806D5158;
extern const float lbl_806D515C;
extern const unsigned char ParticleBurst_Draw_rodata_803292B4[6][3];

void ParticleBurst_Draw(char *self);

#pragma exceptions on
#pragma use_lmw_stmw on

void ParticleBurst_Draw(char *self) {
    Mtx44 m;
    Mtx34 m34;
    Particle *p;
    const unsigned char *c;
    float x;
    float y;
    float z;
    float n;
    int r;
    int g;
    int b;
    int i;

    HSD_StateSetCullMode(0);
    HSD_StateInitDirect(0, 0x40000002);
    GXSetZMode(1, 3, 1);
    n = -lbl_806D506C;
    for (i = 0; i < NUM_PARTICLES; i++) {
        p = &PARTICLES(self)[i];
        if (p->dead == 0 && p->delay == 0) {
            x = lbl_806D509C * (p->x - lbl_806D5020);
            y = lbl_806D50A0 * (p->y - lbl_806D5024);
            z = p->z - lbl_806D5028;
            c = ParticleBurst_Draw_rodata_803292B4[i % 6];
            r = c[0];
            g = c[1];
            b = c[2];
            Matrix4_Identity(&m);
            Matrix4_PreMultiplyRotZ(&m, &m, PARTICLES(self)[i].rot);
            Matrix4_PreMultiplyTranslation(&m, &m, x, y, z);
            DbgScene_CopyMatrix3x4Transpose(&m34, &m);
            GXLoadPosMtxImm(&m34, 0);
            GXSetCurrentMtx(0);
            GXBegin(0x80, 0, 4);
            GXPosition3f32(n, n, lbl_806D5034);
            GXColor4u8(r, g, b, 0xFF);
            GXPosition3f32(lbl_806D506C, n, lbl_806D5034);
            GXColor4u8(r, g, b, 0xFF);
            GXPosition3f32(lbl_806D506C, lbl_806D506C, lbl_806D5034);
            GXColor4u8(r, g, b, 0xFF);
            GXPosition3f32(n, lbl_806D506C, lbl_806D5034);
            GXColor4u8(r, g, b, 0xFF);
        }
    }
}

#pragma use_lmw_stmw reset
#pragma exceptions reset

typedef struct PBVec3 {
    float x, y, z;
} PBVec3;

extern PBVec3 Mtx44_TransformVec3(const float *m, PBVec3 v);
extern void clDrawMan_AddSorted_NoDepthBias(void *mgr, void (*fn)(char *), char *obj,
                                            float x, float y, float z, float bias);
extern void *lbl_806D10AC;
extern PBVec3 ParticleBurst_DrawCb_rodata_803292C8;
extern float lbl_805DF3D0[];

#pragma exceptions on

void ParticleBurst_DrawCb(char *self) {
    PBVec3 p = ParticleBurst_DrawCb_rodata_803292C8;
    p = Mtx44_TransformVec3(lbl_805DF3D0, p);
    clDrawMan_AddSorted_NoDepthBias(lbl_806D10AC == 0 ? 0 : lbl_806D10AC,
                                    ParticleBurst_Draw, self, p.x, p.y, p.z,
                                    lbl_806D5034);
}

#pragma exceptions reset

static inline float sinf(float x)
{
    return (float)sin(x);
}

static inline float cosf(float x)
{
    return (float)cos(x);
}

#pragma exceptions on
#pragma use_lmw_stmw on

void ParticleBurst_Update(char *self)
{
    float edge;
    float angle;
    int i;
    int allDead;
    float speed;
    int late;

    allDead = 1;
    switch (*(signed char *)(self + 0xB4)) {
    case 0:
        self[0x14] = 1;
        PARTICLES(self) = FUN_8003b120(NUM_PARTICLES * sizeof(Particle));
        for (i = 0; i < NUM_PARTICLES; i++) {
            late = i >= NUM_PARTICLES / 2;
            PARTICLES(self)[i].x = 320.0f;
            PARTICLES(self)[i].y = 240.0f;
            if (!late) {
                PARTICLES(self)[i].z = 0.1f;
            } else {
                PARTICLES(self)[i].z = -0.1f;
            }
            if (late) {
                speed = Rand_RangeFloat(8.0f, 12.0f);
            } else {
                speed = Rand_RangeFloat(8.0f, 15.0f);
            }
            angle = 0.017453289f * (180.0f + Rand_RangeFloat(-90.0f, 90.0f));
            PARTICLES(self)[i].vx = speed * sinf(angle);
            PARTICLES(self)[i].vy = speed * cosf(angle);
            PARTICLES(self)[i].rot = BuildOrientationFromYaw(0.017453289f * Rand_RangeFloatMax(360.0f));
            PARTICLES(self)[i].vrot = Rand_RangeFloat(0.087266445f, 0.17453289f);
            if (0.0f < PARTICLES(self)[i].vx) {
                PARTICLES(self)[i].vrot *= -1.0f;
            }
            if (!late) {
                PARTICLES(self)[i].delay = 0;
            } else {
                PARTICLES(self)[i].delay = i % 10;
            }
            PARTICLES(self)[i].dead = 0;
        }
        *(void (**)(char *))(self + 0x78) = (void (*)(char *))ParticleBurst_DrawCb;
        *(char **)(self + 0x7C) = self;
        self[0xB4]++;
    case 1:
        edge = -lbl_806D50E4;
        for (i = 0; i < NUM_PARTICLES; i++) {
            if (PARTICLES(self)[i].dead == 0) {
                if (PARTICLES(self)[i].delay != 0) {
                    PARTICLES(self)[i].delay--;
                } else {
                    PARTICLES(self)[i].vy += 0.1f;
                    PARTICLES(self)[i].x += PARTICLES(self)[i].vx;
                    PARTICLES(self)[i].y += PARTICLES(self)[i].vy;
                    PARTICLES(self)[i].rot = BuildOrientationFromYaw(PARTICLES(self)[i].rot + PARTICLES(self)[i].vrot);
                    if (PARTICLES(self)[i].x < edge) {
                        PARTICLES(self)[i].dead = 1;
                    }
                    if (690.0f < PARTICLES(self)[i].x) {
                        PARTICLES(self)[i].dead = 1;
                    }
                    if (PARTICLES(self)[i].y < edge) {
                        PARTICLES(self)[i].dead = 1;
                    }
                    if (530.0f < PARTICLES(self)[i].y) {
                        PARTICLES(self)[i].dead = 1;
                    }
                }
            }
            if (PARTICLES(self)[i].dead == 0) {
                allDead = 0;
            }
        }
        if (allDead) {
            MemoryManager_Free(PARTICLES(self));
            DrawEffect_Free(self);
        }
        break;
    }
}

#pragma use_lmw_stmw reset
#pragma exceptions reset
