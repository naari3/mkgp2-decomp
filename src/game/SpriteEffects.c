/*
 * Three small sprite effects that share one base (vtable lbl_8048EB44, at
 * +0x14 after the base fields): each has a render that picks a sprite frame
 * from its timer, an update that advances the timer, a ctor and a dtor.
 * The vtables stay in data, so the vptr stores are spelled out by hand
 * (volatile, so the derived store before the inlined base dtor survives).
 * The three render functions are still asm: their float register
 * assignment did not settle from C.
 */
#pragma cplusplus on

extern "C" {
extern char lbl_8048EB24[];
extern char lbl_8048EB44[];
extern char lbl_8048EB70[];
extern char lbl_8048EB9C[];
extern const float lbl_806D76F0, lbl_806D76F4, lbl_806D76F8, lbl_806D76FC;
extern const float lbl_806D7700, lbl_806D7704, lbl_806D7708, lbl_806D770C;
extern const float lbl_806D7710, lbl_806D7714, lbl_806D7718, lbl_806D771C;
extern const float lbl_806D7720, lbl_806D7724, lbl_806D7728, lbl_806D772C;
extern const float lbl_806D7730, lbl_806D7734, lbl_806D7738, lbl_806D773C;
extern const float lbl_806D7740, lbl_806D7744, lbl_806D7748, lbl_806D774C;
extern const float lbl_806D7750, lbl_806D7754, lbl_806D7758, lbl_806D775C;
extern const float lbl_806D7760, lbl_806D7764, lbl_806D7768, lbl_806D776C;
extern const float lbl_806D7770, lbl_806D7774, lbl_806D7778, lbl_806D777C;
extern const float lbl_806D7780, lbl_806D7784, lbl_806D7788, lbl_806D778C;
extern const float lbl_806D7790, lbl_806D7794, lbl_806D7798, lbl_806D779C;
extern const float lbl_806D77A0, lbl_806D77A4;
extern void fn_80169468(void *obj, int id, int flag, float x, float y, float sx, float sy, float sz, float a);
extern void fn_8016918C(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a);
extern void fn_801A0004(void *p);
}

void *operator new(unsigned long size);
extern "C" {
asm void fn_8013DD94(void);
asm void fn_8013E194(void);
asm void fn_8013E744(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013DD94[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_8013E194[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_8013E744[8] = {
    0x08, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013DD94 = {
    (void *)&fn_8013DD94, 0x00000374, (void *)extab_fn_8013DD94
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013E194 = {
    (void *)&fn_8013E194, 0x00000520, (void *)extab_fn_8013E194
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013E744 = {
    (void *)&fn_8013E744, 0x00000370, (void *)extab_fn_8013E744
};

}

inline void *operator new(unsigned long, void *p) { return p; }
void operator delete(void *p);

struct EffectBase {
    void *obj;
    unsigned char active;
    float x, y;
    float alpha;
    void *volatile vptr;
    unsigned int flags;
    float t;
    EffectBase() {
        vptr = lbl_8048EB44;
        obj = 0;
        active = 0;
        x = lbl_806D770C;
        y = lbl_806D770C;
        alpha = lbl_806D76F4;
    }
    ~EffectBase() { vptr = lbl_8048EB44; }
};

typedef EffectBase Effect;

struct Effect1 : Effect {
    Effect1();
    ~Effect1();
};

struct Effect2 : Effect {
    Effect2(int mode);
    ~Effect2();
};

struct Effect3 : Effect {
    Effect3();
    ~Effect3();
};

Effect1::~Effect1() {
    vptr = lbl_8048EB24;
}

extern "C" asm void fn_8013DD94(void) { /* 0x8013DD94 size:0x374 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D76F0(r2)
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lfs f1, 0x1c(r3)
    fcmpo cr0, f1, f0
    bge fn_8013DD94_L_8013DDE4
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x883
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013DD94_L_8013DF24
    fn_8013DD94_L_8013DDE4:
    lfs f0, lbl_806D76F8(r2)
    fcmpo cr0, f1, f0
    bge fn_8013DD94_L_8013DE1C
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x884
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013DD94_L_8013DF24
    fn_8013DD94_L_8013DE1C:
    lfs f0, lbl_806D76FC(r2)
    fcmpo cr0, f1, f0
    bge fn_8013DD94_L_8013DE54
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x885
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013DD94_L_8013DF24
    fn_8013DD94_L_8013DE54:
    lfs f0, lbl_806D7700(r2)
    fcmpo cr0, f1, f0
    bge fn_8013DD94_L_8013DE8C
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x886
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013DD94_L_8013DF24
    fn_8013DD94_L_8013DE8C:
    lfs f0, lbl_806D7704(r2)
    fcmpo cr0, f1, f0
    bge fn_8013DD94_L_8013DEC4
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x885
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013DD94_L_8013DF24
    fn_8013DD94_L_8013DEC4:
    lfs f0, lbl_806D7708(r2)
    fcmpo cr0, f1, f0
    bge fn_8013DD94_L_8013DEFC
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x884
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013DD94_L_8013DF24
    fn_8013DD94_L_8013DEFC:
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x883
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    fn_8013DD94_L_8013DF24:
    lfs f2, 0x1c(r31)
    lfs f0, lbl_806D76FC(r2)
    fcmpo cr0, f2, f0
    bge fn_8013DD94_L_8013DF3C
    lfs f2, lbl_806D770C(r2)
    b fn_8013DD94_L_8013DF80
    fn_8013DD94_L_8013DF3C:
    lfs f1, lbl_806D7710(r2)
    fcmpo cr0, f2, f1
    bge fn_8013DD94_L_8013DF58
    fsubs f1, f2, f0
    lfs f0, lbl_806D7714(r2)
    fdivs f2, f1, f0
    b fn_8013DD94_L_8013DF80
    fn_8013DD94_L_8013DF58:
    lfs f0, lbl_806D7704(r2)
    fcmpo cr0, f2, f0
    bge fn_8013DD94_L_8013DF7C
    fsubs f1, f2, f1
    lfs f0, lbl_806D76F8(r2)
    lfs f2, lbl_806D76F4(r2)
    fdivs f0, f1, f0
    fsubs f2, f2, f0
    b fn_8013DD94_L_8013DF80
    fn_8013DD94_L_8013DF7C:
    lfs f2, lbl_806D770C(r2)
    fn_8013DD94_L_8013DF80:
    lfs f0, lbl_806D770C(r2)
    fcmpo cr0, f2, f0
    ble fn_8013DD94_L_8013DFB8
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x88a
    lfs f0, 0x10(r31)
    li r5, 0x0
    fmr f4, f3
    lwz r3, 0x0(r31)
    fmr f5, f3
    lfs f1, 0x8(r31)
    fmuls f6, f2, f0
    lfs f2, 0xc(r31)
    bl fn_80169468
    fn_8013DD94_L_8013DFB8:
    lfs f2, 0x1c(r31)
    lfs f4, lbl_806D76F0(r2)
    fcmpo cr0, f2, f4
    bge fn_8013DD94_L_8013DFEC
    fdivs f4, f2, f4
    lfs f8, lbl_806D7718(r2)
    lfs f2, lbl_806D771C(r2)
    lfs f1, lbl_806D7724(r2)
    lfs f0, lbl_806D7720(r2)
    lfs f10, lbl_806D7728(r2)
    fnmsubs f3, f2, f4, f8
    fmadds f9, f1, f4, f0
    b fn_8013DD94_L_8013E0BC
    fn_8013DD94_L_8013DFEC:
    lfs f0, lbl_806D772C(r2)
    fcmpo cr0, f2, f0
    bge fn_8013DD94_L_8013E030
    fsubs f1, f2, f4
    lfs f0, lbl_806D7730(r2)
    lfs f5, lbl_806D7738(r2)
    lfs f3, lbl_806D7734(r2)
    fmuls f6, f1, f0
    lfs f4, lbl_806D773C(r2)
    lfs f2, lbl_806D7718(r2)
    lfs f1, lbl_806D7744(r2)
    lfs f0, lbl_806D7740(r2)
    fmadds f3, f5, f6, f3
    fmadds f8, f4, f6, f2
    lfs f10, lbl_806D7728(r2)
    fnmsubs f9, f1, f6, f0
    b fn_8013DD94_L_8013E0BC
    fn_8013DD94_L_8013E030:
    lfs f1, lbl_806D7700(r2)
    fcmpo cr0, f2, f1
    bge fn_8013DD94_L_8013E074
    fsubs f1, f2, f0
    lfs f0, lbl_806D76F8(r2)
    lfs f5, lbl_806D7738(r2)
    lfs f3, lbl_806D7748(r2)
    fdivs f6, f1, f0
    lfs f4, lbl_806D773C(r2)
    lfs f2, lbl_806D76F4(r2)
    lfs f1, lbl_806D7744(r2)
    lfs f0, lbl_806D774C(r2)
    lfs f10, lbl_806D7728(r2)
    fnmsubs f3, f5, f6, f3
    fnmsubs f8, f4, f6, f2
    fmadds f9, f1, f6, f0
    b fn_8013DD94_L_8013E0BC
    fn_8013DD94_L_8013E074:
    lfs f0, lbl_806D7708(r2)
    fcmpo cr0, f2, f0
    bge fn_8013DD94_L_8013E0AC
    fsubs f0, f2, f1
    lfs f3, lbl_806D771C(r2)
    lfs f2, lbl_806D7734(r2)
    lfs f1, lbl_806D7724(r2)
    fdivs f4, f0, f4
    lfs f0, lbl_806D7740(r2)
    lfs f8, lbl_806D7718(r2)
    lfs f10, lbl_806D7728(r2)
    fmadds f3, f3, f4, f2
    fnmsubs f9, f1, f4, f0
    b fn_8013DD94_L_8013E0BC
    fn_8013DD94_L_8013E0AC:
    lfs f3, lbl_806D7718(r2)
    lfs f9, lbl_806D7720(r2)
    fmr f8, f3
    lfs f10, lbl_806D7728(r2)
    fn_8013DD94_L_8013E0BC:
    lfs f5, lbl_806D76F4(r2)
    fmr f4, f3
    lfs f1, 0x8(r31)
    li r4, 0x8a2
    lfs f2, 0xc(r31)
    fmr f6, f5
    lfs f0, 0x10(r31)
    fmr f7, f5
    lwz r3, 0x0(r31)
    fadds f1, f1, f9
    li r5, 0x0
    fadds f2, f2, f10
    fmuls f8, f8, f0
    bl fn_8016918C
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" void fn_8013E108(Effect *e) {
    if (e->flags & 2) {
        e->flags &= ~2;
        return;
    }
    float t = e->t + lbl_806D76F4;
    e->t = t;
    if (t >= lbl_806D7750) {
        e->t = lbl_806D770C;
    }
}

Effect1::Effect1() {
    vptr = lbl_8048EB24;
    flags = 2;
    t = lbl_806D770C;
}

extern "C" asm void fn_8013E194(void) { /* 0x8013E194 size:0x520 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D7754(r2)
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lfs f1, 0x1c(r3)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E1E4
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89d
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E1E4:
    lfs f0, lbl_806D7758(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E21C
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89e
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E21C:
    lfs f0, lbl_806D775C(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E254
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89f
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E254:
    lfs f0, lbl_806D7760(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E28C
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x8a0
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E28C:
    lfs f0, lbl_806D7708(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E2C4
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89f
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E2C4:
    lfs f0, lbl_806D7764(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E2FC
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89e
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E2FC:
    lfs f0, lbl_806D7768(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E334
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89d
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E334:
    lfs f0, lbl_806D776C(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E36C
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89c
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E36C:
    lfs f0, lbl_806D7770(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E3A4
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89b
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E3A4:
    lfs f0, lbl_806D7774(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E3DC
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x8a1
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E3DC:
    lfs f0, lbl_806D7778(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E414
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89b
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E414:
    lfs f0, lbl_806D777C(r2)
    fcmpo cr0, f1, f0
    bge fn_8013E194_L_8013E44C
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89c
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E194_L_8013E474
    fn_8013E194_L_8013E44C:
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x89d
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    fn_8013E194_L_8013E474:
    lfs f2, 0x1c(r31)
    lfs f0, lbl_806D7750(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne fn_8013E194_L_8013E48C
    fsubs f2, f2, f0
    fn_8013E194_L_8013E48C:
    lwz r0, 0x18(r31)
    rlwinm r0, r0, 0, 29, 29
    cmplwi r0, 0x4
    bne fn_8013E194_L_8013E564
    lfs f3, lbl_806D76F0(r2)
    fcmpo cr0, f2, f3
    bge fn_8013E194_L_8013E4C0
    fdivs f1, f2, f3
    lfs f0, lbl_806D7718(r2)
    lfs f2, lbl_806D771C(r2)
    fmr f8, f0
    fnmsubs f3, f2, f1, f0
    b fn_8013E194_L_8013E558
    fn_8013E194_L_8013E4C0:
    lfs f0, lbl_806D772C(r2)
    fcmpo cr0, f2, f0
    bge fn_8013E194_L_8013E4F4
    fsubs f1, f2, f3
    lfs f0, lbl_806D7730(r2)
    lfs f3, lbl_806D7738(r2)
    lfs f2, lbl_806D7734(r2)
    fmuls f4, f1, f0
    lfs f1, lbl_806D773C(r2)
    lfs f0, lbl_806D7718(r2)
    fmadds f3, f3, f4, f2
    fmadds f8, f1, f4, f0
    b fn_8013E194_L_8013E558
    fn_8013E194_L_8013E4F4:
    lfs f1, lbl_806D7700(r2)
    fcmpo cr0, f2, f1
    bge fn_8013E194_L_8013E528
    fsubs f1, f2, f0
    lfs f0, lbl_806D76F8(r2)
    lfs f3, lbl_806D7738(r2)
    lfs f2, lbl_806D7748(r2)
    fdivs f4, f1, f0
    lfs f1, lbl_806D773C(r2)
    lfs f0, lbl_806D76F4(r2)
    fnmsubs f3, f3, f4, f2
    fnmsubs f8, f1, f4, f0
    b fn_8013E194_L_8013E558
    fn_8013E194_L_8013E528:
    lfs f0, lbl_806D7708(r2)
    fcmpo cr0, f2, f0
    bge fn_8013E194_L_8013E550
    fsubs f1, f2, f1
    lfs f2, lbl_806D771C(r2)
    lfs f0, lbl_806D7734(r2)
    lfs f8, lbl_806D7718(r2)
    fdivs f1, f1, f3
    fmadds f3, f2, f1, f0
    b fn_8013E194_L_8013E558
    fn_8013E194_L_8013E550:
    lfs f3, lbl_806D7718(r2)
    fmr f8, f3
    fn_8013E194_L_8013E558:
    lfs f10, lbl_806D76F4(r2)
    lfs f0, lbl_806D7780(r2)
    b fn_8013E194_L_8013E668
    fn_8013E194_L_8013E564:
    lfs f5, lbl_806D76F0(r2)
    fcmpo cr0, f2, f5
    bge fn_8013E194_L_8013E598
    fdivs f5, f2, f5
    lfs f3, lbl_806D7718(r2)
    lfs f4, lbl_806D771C(r2)
    lfs f2, lbl_806D7724(r2)
    lfs f1, lbl_806D7784(r2)
    lfs f0, lbl_806D770C(r2)
    fmr f8, f3
    fnmsubs f3, f4, f5, f3
    fnmsubs f10, f2, f5, f1
    b fn_8013E194_L_8013E668
    fn_8013E194_L_8013E598:
    lfs f0, lbl_806D772C(r2)
    fcmpo cr0, f2, f0
    bge fn_8013E194_L_8013E5DC
    fsubs f1, f2, f5
    lfs f0, lbl_806D7730(r2)
    lfs f5, lbl_806D7738(r2)
    lfs f3, lbl_806D7734(r2)
    fmuls f6, f1, f0
    lfs f4, lbl_806D773C(r2)
    lfs f0, lbl_806D7718(r2)
    lfs f2, lbl_806D7744(r2)
    lfs f1, lbl_806D7704(r2)
    fmadds f3, f5, f6, f3
    fmadds f8, f4, f6, f0
    lfs f0, lbl_806D770C(r2)
    fmadds f10, f2, f6, f1
    b fn_8013E194_L_8013E668
    fn_8013E194_L_8013E5DC:
    lfs f1, lbl_806D7700(r2)
    fcmpo cr0, f2, f1
    bge fn_8013E194_L_8013E620
    fsubs f1, f2, f0
    lfs f0, lbl_806D76F8(r2)
    lfs f6, lbl_806D7738(r2)
    lfs f3, lbl_806D7748(r2)
    fdivs f7, f1, f0
    lfs f5, lbl_806D773C(r2)
    lfs f4, lbl_806D76F4(r2)
    lfs f2, lbl_806D7744(r2)
    lfs f1, lbl_806D7788(r2)
    lfs f0, lbl_806D770C(r2)
    fnmsubs f3, f6, f7, f3
    fnmsubs f8, f5, f7, f4
    fnmsubs f10, f2, f7, f1
    b fn_8013E194_L_8013E668
    fn_8013E194_L_8013E620:
    lfs f0, lbl_806D7708(r2)
    fcmpo cr0, f2, f0
    bge fn_8013E194_L_8013E658
    fsubs f0, f2, f1
    lfs f4, lbl_806D771C(r2)
    lfs f3, lbl_806D7734(r2)
    lfs f2, lbl_806D7724(r2)
    fdivs f5, f0, f5
    lfs f1, lbl_806D7704(r2)
    lfs f8, lbl_806D7718(r2)
    lfs f0, lbl_806D770C(r2)
    fmadds f3, f4, f5, f3
    fmadds f10, f2, f5, f1
    b fn_8013E194_L_8013E668
    fn_8013E194_L_8013E658:
    lfs f3, lbl_806D7718(r2)
    lfs f10, lbl_806D7784(r2)
    fmr f8, f3
    lfs f0, lbl_806D770C(r2)
    fn_8013E194_L_8013E668:
    lfs f5, lbl_806D76F4(r2)
    fmr f4, f3
    lfs f1, 0x8(r31)
    li r4, 0x8a2
    lfs f2, 0xc(r31)
    fmr f6, f5
    lfs f9, 0x10(r31)
    fmr f7, f5
    lwz r3, 0x0(r31)
    fadds f1, f1, f10
    li r5, 0x0
    fadds f2, f2, f0
    fmuls f8, f8, f9
    bl fn_8016918C
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" void fn_8013E6B4(Effect *e) {
    if (e->flags & 2) {
        e->flags &= ~2;
        return;
    }
    float t = e->t + lbl_806D76F4;
    e->t = t;
    if (t >= lbl_806D778C) {
        e->t = lbl_806D770C;
    }
}

Effect2::Effect2(int mode) {
    vptr = lbl_8048EB70;
    flags = ((mode << 2) & 4) | 2;
    t = lbl_806D770C;
}

extern "C" asm void fn_8013E744(void) { /* 0x8013E744 size:0x370 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x18(r1), 0, 0
    stw r31, 0xc(r1)
    mr r31, r3
    lfs f0, lbl_806D76F0(r2)
    lfs f31, 0x1c(r3)
    fcmpo cr0, f31, f0
    bge fn_8013E744_L_8013E79C
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x896
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E744_L_8013E958
    fn_8013E744_L_8013E79C:
    lfs f0, lbl_806D7790(r2)
    fcmpo cr0, f31, f0
    bge fn_8013E744_L_8013E7D4
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x897
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E744_L_8013E958
    fn_8013E744_L_8013E7D4:
    lfs f0, lbl_806D7794(r2)
    fcmpo cr0, f31, f0
    bge fn_8013E744_L_8013E848
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x898
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    lfs f0, lbl_806D7790(r2)
    li r4, 0x899
    lfs f3, lbl_806D76F4(r2)
    li r5, 0x0
    fsubs f2, f31, f0
    lfs f1, lbl_806D76F0(r2)
    lfs f0, 0x10(r31)
    fmr f4, f3
    fmr f5, f3
    lwz r3, 0x0(r31)
    fdivs f6, f2, f1
    lfs f1, 0x8(r31)
    lfs f2, 0xc(r31)
    fmuls f6, f6, f0
    bl fn_80169468
    b fn_8013E744_L_8013E958
    fn_8013E744_L_8013E848:
    lfs f0, lbl_806D7798(r2)
    fcmpo cr0, f31, f0
    bge fn_8013E744_L_8013E8C0
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x898
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    lfs f0, lbl_806D7794(r2)
    li r4, 0x899
    lfs f3, lbl_806D76F4(r2)
    li r5, 0x0
    fsubs f2, f31, f0
    lfs f1, lbl_806D76F0(r2)
    lfs f0, 0x10(r31)
    fmr f4, f3
    fmr f5, f3
    lwz r3, 0x0(r31)
    fdivs f6, f2, f1
    lfs f1, 0x8(r31)
    lfs f2, 0xc(r31)
    fsubs f6, f3, f6
    fmuls f6, f6, f0
    bl fn_80169468
    b fn_8013E744_L_8013E958
    fn_8013E744_L_8013E8C0:
    lfs f0, lbl_806D7700(r2)
    fcmpo cr0, f31, f0
    bge fn_8013E744_L_8013E8F8
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x897
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E744_L_8013E958
    fn_8013E744_L_8013E8F8:
    lfs f0, lbl_806D7760(r2)
    fcmpo cr0, f31, f0
    bge fn_8013E744_L_8013E930
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x896
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    b fn_8013E744_L_8013E958
    fn_8013E744_L_8013E930:
    lfs f3, lbl_806D76F4(r2)
    li r4, 0x896
    lwz r3, 0x0(r31)
    li r5, 0x0
    fmr f4, f3
    lfs f1, 0x8(r31)
    fmr f5, f3
    lfs f2, 0xc(r31)
    lfs f6, 0x10(r31)
    bl fn_80169468
    fn_8013E744_L_8013E958:
    lfs f2, 0x1c(r31)
    lfs f4, lbl_806D76F0(r2)
    fcmpo cr0, f2, f4
    bge fn_8013E744_L_8013E990
    fdivs f4, f2, f4
    lfs f2, lbl_806D7718(r2)
    lfs f3, lbl_806D771C(r2)
    lfs f1, lbl_806D7724(r2)
    lfs f0, lbl_806D7788(r2)
    lfs f9, lbl_806D779C(r2)
    fmr f10, f2
    fnmsubs f3, f3, f4, f2
    fnmsubs f8, f1, f4, f0
    b fn_8013E744_L_8013EA60
    fn_8013E744_L_8013E990:
    lfs f0, lbl_806D772C(r2)
    fcmpo cr0, f2, f0
    bge fn_8013E744_L_8013E9D4
    fsubs f1, f2, f4
    lfs f0, lbl_806D7730(r2)
    lfs f5, lbl_806D7738(r2)
    lfs f3, lbl_806D7734(r2)
    fmuls f6, f1, f0
    lfs f4, lbl_806D773C(r2)
    lfs f2, lbl_806D7718(r2)
    lfs f1, lbl_806D775C(r2)
    lfs f0, lbl_806D77A0(r2)
    fmadds f3, f5, f6, f3
    fmadds f10, f4, f6, f2
    lfs f9, lbl_806D779C(r2)
    fmadds f8, f1, f6, f0
    b fn_8013E744_L_8013EA60
    fn_8013E744_L_8013E9D4:
    lfs f1, lbl_806D7700(r2)
    fcmpo cr0, f2, f1
    bge fn_8013E744_L_8013EA18
    fsubs f1, f2, f0
    lfs f0, lbl_806D76F8(r2)
    lfs f5, lbl_806D7738(r2)
    lfs f3, lbl_806D7748(r2)
    fdivs f6, f1, f0
    lfs f4, lbl_806D773C(r2)
    lfs f2, lbl_806D76F4(r2)
    lfs f1, lbl_806D775C(r2)
    lfs f0, lbl_806D77A4(r2)
    lfs f9, lbl_806D779C(r2)
    fnmsubs f3, f5, f6, f3
    fnmsubs f10, f4, f6, f2
    fnmsubs f8, f1, f6, f0
    b fn_8013E744_L_8013EA60
    fn_8013E744_L_8013EA18:
    lfs f0, lbl_806D7708(r2)
    fcmpo cr0, f2, f0
    bge fn_8013E744_L_8013EA50
    fsubs f0, f2, f1
    lfs f3, lbl_806D771C(r2)
    lfs f2, lbl_806D7734(r2)
    lfs f1, lbl_806D7724(r2)
    fdivs f4, f0, f4
    lfs f0, lbl_806D77A0(r2)
    lfs f10, lbl_806D7718(r2)
    lfs f9, lbl_806D779C(r2)
    fmadds f3, f3, f4, f2
    fmadds f8, f1, f4, f0
    b fn_8013E744_L_8013EA60
    fn_8013E744_L_8013EA50:
    lfs f3, lbl_806D7718(r2)
    lfs f8, lbl_806D7788(r2)
    fmr f10, f3
    lfs f9, lbl_806D779C(r2)
    fn_8013E744_L_8013EA60:
    lfs f5, lbl_806D76F4(r2)
    fmr f4, f3
    lfs f1, 0x8(r31)
    li r4, 0x8a8
    lfs f2, 0xc(r31)
    fmr f6, f5
    lfs f0, 0x10(r31)
    fadds f1, f1, f8
    lwz r3, 0x0(r31)
    fmr f7, f5
    li r5, 0x0
    fadds f2, f2, f9
    fmuls f8, f10, f0
    bl fn_8016918C
    psq_l f31, 0x18(r1), 0, 0
    lwz r0, 0x24(r1)
    lfd f31, 0x10(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" void fn_8013EAB4(Effect *e) {
    if (e->flags & 2) {
        e->flags &= ~2;
        return;
    }
    e->t += lbl_806D76F4;
    if (e->t >= lbl_806D7750) {
        e->t = lbl_806D770C;
    }
}

Effect3::Effect3() {
    vptr = lbl_8048EB9C;
    flags = 2;
    t = lbl_806D770C;
}

extern "C" void fn_8013EB44(void) {
}

extern "C" void fn_8013EB48(void) {
}

extern "C" void fn_8013EB4C(void) {
}

extern "C" EffectBase *dtor_8013EB50(EffectBase *e, short flag) {
    if (e) {
        e->vptr = lbl_8048EB44;
        if (flag > 0) {
            operator delete(e);
        }
    }
    return e;
}

extern "C" void fn_8013EB98(void) {
}

extern "C" void fn_8013EB9C(void) {
}

Effect2::~Effect2() {
    vptr = lbl_8048EB70;
}

Effect3::~Effect3() {
    vptr = lbl_8048EB9C;
}

struct EffectHolder {
    char pad[0x2c];
    void **items[3];
};

extern "C" void fn_8013EC58(EffectHolder *h) {
    int i;
    for (i = 0; i < 3; i++) {
        if (h->items[i]) {
            fn_801A0004(*h->items[i]);
        }
    }
}
