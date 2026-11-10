#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * Confetti particle field drawn into the result render targets: 72 quads
 * spawned from the 48/64-entry random tables, spun and dropped each frame.
 */
C_REGION_END
#pragma cplusplus on

typedef float Mtx[3][4];
#include "game/types/Vec3f.h"

extern "C" {
extern unsigned int ConfettiField_rodata_80360520[];
extern const float lbl_806D7868, lbl_806D786C, lbl_806D7870, lbl_806D7874, lbl_806D7878;
extern const float lbl_806D787C, lbl_806D7880, lbl_806D7884, lbl_806D7888;
extern const float lbl_806D788C, lbl_806D7890, lbl_806D7894, lbl_806D7898;
extern float lbl_80495994[];
extern float lbl_80495A94[];
extern void *fn_8013BC98(void);
extern void *fn_8013C3B8(void);
extern unsigned char fn_8013BC38(void *rt);
extern void fn_8013C34C(void *rt);
extern void fn_8013BBFC(void *rt);
extern void fn_8013C334(void *rt);
extern void fn_8013BB9C(void *rt);
extern void fn_8013BCA0(void);
extern void fn_8013C3C0(void);
extern int fn_8013BD7C(void);
extern int fn_8013C428(void);
extern float fn_8013BA90(void *rt);
extern float fn_8013BAE8(void *rt);
extern void HSD_StateSetCullMode(int mode);
extern void HSD_StateInitDirect(int a, int b);
extern void *HSD_CObjGetCurrent(void);
extern void HSD_CObjGetViewingMtx(void *cam, Mtx m);
extern void GXSetCurrentMtx(int id);
extern void GXLoadPosMtxImm(Mtx m, int id);
extern void GXBegin(int prim, int fmt, int n);
extern void PSMTXIdentity(Mtx m);
extern void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
extern void PSMTXRotRad(Mtx m, char axis, float rad);
extern float Vec3_Dot(const Vec3f *a, const Vec3f *b);
extern double tan(double x);
extern void *FUN_8003b120(unsigned long size);
extern void MemoryManager_Free(void *p);
}


struct Confetti {
    unsigned char active;
    Mtx mtx;
    float rot[3];
    int color;
};

struct ConfettiField {
    int f0;
    int f4;
    float size;
    int count;
    float f10, f14, f18;
    Confetti *pieces;
    int timer;

    ConfettiField();
    ~ConfettiField();
    void Draw();
    void Update();
    float Rand48() {
        if (++f4 >= 48) {
            f4 = 0;
        }
        return lbl_80495A94[f4];
    }
    float Rand64() {
        if (++f0 >= 64) {
            f0 = 0;
        }
        return lbl_80495994[f0];
    }
};

struct GXColorRGBA {
    unsigned char r, g, b, a;
};

union ConfettiColor {
    unsigned int rgba;
    GXColorRGBA c;
};

union GXFifoPipe {
    unsigned char u8;
    unsigned short u16;
    unsigned int u32;
    unsigned long long u64;
    signed char s8;
    short s16;
    int s32;
    long long s64;
    float f32;
    double f64;
};
#include "game/types/at_address.h"
volatile GXFifoPipe GXWGFifo AT_ADDRESS(0xCC008000);
#define GXFIFO GXWGFifo

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

void ConfettiField::Draw() {
    Mtx view;
    Mtx m;
    int i;
    ConfettiColor c;
    float z = 0.0f;

    if (fn_8013BC98() == 0) {
        return;
    }
    if (fn_8013C3B8() == 0) {
        return;
    }
    if (!fn_8013BC38(fn_8013BC98())) {
        return;
    }
    fn_8013C34C(fn_8013C3B8());
    fn_8013BBFC(fn_8013BC98());
    HSD_StateSetCullMode(0);
    HSD_StateInitDirect(0, 0x40000002);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), view);
    GXSetCurrentMtx(0);
    for (i = 0; i < 72; i++) {
        if (pieces[i].active) {
            PSMTXConcat(view, pieces[i].mtx, m);
            GXLoadPosMtxImm(m, 0);
            c.rgba = ConfettiField_rodata_80360520[pieces[i].color];
            GXBegin(0x80, 0, 4);
            GXPosition3f32(-size, -size, z);
            GXColor4u8(c.c.r, c.c.g, c.c.b, c.c.a);
            GXPosition3f32(size, -size, z);
            GXColor4u8(c.c.r, c.c.g, c.c.b, c.c.a);
            GXPosition3f32(size, size, z);
            GXColor4u8(c.c.r, c.c.g, c.c.b, c.c.a);
            GXPosition3f32(-size, size, z);
            GXColor4u8(c.c.r, c.c.g, c.c.b, c.c.a);
        }
    }
    fn_8013C334(fn_8013C3B8());
    fn_8013BB9C(fn_8013BC98());
}

void ConfettiField::Update() {
    Mtx rot;
    Vec3f v;
    Vec3f up;
    float aspect;
    float t;
    float tx;
    float bottom;
    float d;
    float z;
    float x;
    float y;
    float lo;
    float range;
    float r;
    int i;
    void *rt;

    if (fn_8013BC98() == 0) {
        return;
    }
    if (fn_8013C3B8() == 0) {
        return;
    }
    rt = fn_8013BC98();
    aspect = fn_8013BAE8(rt);
    t = tan(lbl_806D786C * fn_8013BA90(rt));
    if (timer != 0) {
        timer--;
    }
    tx = t * aspect;
    for (i = 0; i < 72; i++) {
        if (pieces[i].active) {
            bottom = t * pieces[i].mtx[2][3];
            PSMTXRotRad(rot, 'X', f10 * pieces[i].rot[0]);
            PSMTXConcat(pieces[i].mtx, rot, pieces[i].mtx);
            PSMTXRotRad(rot, 'Y', f10 * pieces[i].rot[1]);
            PSMTXConcat(pieces[i].mtx, rot, pieces[i].mtx);
            PSMTXRotRad(rot, 'Z', f10 * pieces[i].rot[2]);
            PSMTXConcat(pieces[i].mtx, rot, pieces[i].mtx);
            up.x = lbl_806D7868;
            up.y = lbl_806D7870;
            up.z = lbl_806D7868;
            v.x = pieces[i].mtx[0][2];
            v.y = pieces[i].mtx[1][2];
            v.z = pieces[i].mtx[2][2];
            d = Vec3_Dot(&v, &up);
            pieces[i].mtx[1][3] -= f18 * (lbl_806D7874 + (lbl_806D7878 - (d < lbl_806D7868 ? -d : d)));
            v.x = pieces[i].mtx[0][0];
            v.y = pieces[i].mtx[1][0];
            v.z = pieces[i].mtx[2][0];
            d = Vec3_Dot(&v, &up);
            v.x = pieces[i].mtx[0][1];
            v.y = pieces[i].mtx[1][1];
            v.z = pieces[i].mtx[2][1];
            pieces[i].mtx[0][3] -= f14 * (d * Vec3_Dot(&v, &up));
            if (pieces[i].mtx[1][3] < bottom - size) {
                pieces[i].active = 0;
            }
        } else if (timer == 0) {
            pieces[i].active = 1;
            PSMTXIdentity(pieces[i].mtx);
            pieces[i].mtx[2][3] = lbl_806D7880 * Rand48() + lbl_806D787C;
            z = -pieces[i].mtx[2][3];
            x = z * tx;
            y = t * z;
            lo = -x;
            range = x - lo;
            r = Rand64();
            pieces[i].mtx[0][3] = range * r + lo;
            pieces[i].mtx[1][3] = y - size;
            pieces[i].color = (int)(lbl_806D7884 * r) % 6;
            pieces[i].rot[0] = lbl_806D7888 * Rand48() - lbl_806D7878;
            pieces[i].rot[1] = lbl_806D7888 * Rand48() - lbl_806D7878;
            pieces[i].rot[2] = lbl_806D7888 * Rand48() - lbl_806D7878;
            timer = count;
        }
    }
}

ConfettiField::~ConfettiField() {
    if (pieces) {
        MemoryManager_Free(pieces);
    }
    fn_8013BCA0();
    fn_8013C3C0();
}

ConfettiField::ConfettiField() {
    int i;

    fn_8013BD7C();
    fn_8013C428();
    size = lbl_806D788C;
    count = 10;
    f10 = lbl_806D7890;
    f14 = lbl_806D7894;
    f18 = lbl_806D7898;
    pieces = (Confetti *)FUN_8003b120(72 * sizeof(Confetti));
    for (i = 0; i < 72; i++) {
        pieces[i].active = 0;
    }
    timer = 0;
    f0 = 0;
    f4 = 0;
}
