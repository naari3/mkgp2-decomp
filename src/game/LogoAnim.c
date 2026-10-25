/*
 * A small sprite animation object (resource 0x139F): two layers of the
 * same sprite are scaled and faded in, held, and scaled back out from a
 * frame timer. Three classes deep (vtables lbl_8048ECF8, lbl_8048ED10,
 * lbl_8048ECE0, all in data), so the vptr stores are spelled out by hand.
 *
 * Still asm: the update (float register assignment) and the virtual
 * release (`delete this` through the vtable).
 */
#pragma cplusplus on

extern "C" {
extern char lbl_8048ECE0[];
extern char lbl_8048ECF8[];
extern char lbl_8048ED10[];
extern const float lbl_806D7900, lbl_806D7904, lbl_806D7908, lbl_806D790C;
extern const float lbl_806D7910, lbl_806D7914, lbl_806D7918, lbl_806D791C;
extern const float lbl_806D7920, lbl_806D7924, lbl_806D7928, lbl_806D792C;
extern const float lbl_806D7930, lbl_806D7934, lbl_806D7938, lbl_806D793C;
extern const float lbl_806D7940, lbl_806D7944, lbl_806D7948, lbl_806D794C;
extern const float lbl_806D7950, lbl_806D7954, lbl_806D7958, lbl_806D795C;
extern const float lbl_806D7960, lbl_806D7964, lbl_806D7968, lbl_806D796C;
extern const float lbl_806D7970, lbl_806D7974, lbl_806D7978, lbl_806D797C;
extern const float lbl_806D7980, lbl_806D7984, lbl_806D7988, lbl_806D798C;
extern const float lbl_806D7990;
extern void fn_8016918C(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a);
extern void fn_80169468(void *obj, int id, int flag, float x, float y, float sx, float sy, float sz, float a);
extern void fn_801697C0(void *obj, int id, int flag, float x, float y, float sx, float sy);
extern void fn_801698B4(void *obj, int id, int flag, float x, float y);
extern void PreloadResource(int resId);
extern void MemoryManager_TimedFree(void *p);
}

extern "C" {
asm void fn_80141454(void);
asm void fn_80141990(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80141454[8] = {
    0x09, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80141990[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80141454 = {
    (void *)&fn_80141454, 0x00000464, (void *)extab_fn_80141454
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80141990 = {
    (void *)&fn_80141990, 0x00000038, (void *)extab_fn_80141990
};

}


struct AnimBase {
    void *volatile vptr;
    int arg;
    int f8;
    int fc;
    AnimBase(int a) {
        vptr = lbl_8048ECF8;
        arg = a;
        f8 = 0;
        fc = 0;
    }
    ~AnimBase() { vptr = lbl_8048ECF8; }
};

struct AnimMid : AnimBase {
    AnimMid(int a) : AnimBase(a) { vptr = lbl_8048ED10; }
    ~AnimMid() { vptr = lbl_8048ED10; }
};

struct LogoAnim : AnimMid {
    void *obj;
    int done;
    float t;
    LogoAnim(void *o, int a);
    ~LogoAnim();
};

extern "C" void fn_80141450(void) {
}

extern "C" asm void fn_80141454(void) { /* 0x80141454 size:0x464 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stfd f30, 0x30(r1)
    psq_st f30, 0x38(r1), 0, 0
    stfd f29, 0x20(r1)
    psq_st f29, 0x28(r1), 0, 0
    stfd f28, 0x10(r1)
    psq_st f28, 0x18(r1), 0, 0
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r0, 0x14(r3)
    cmpwi r0, 0x0
    beq fn_80141454_L_801414A0
    li r0, 0x1
    stw r0, 0xc(r31)
    b fn_80141454_L_80141884
    fn_80141454_L_801414A0:
    lfs f31, 0x18(r31)
    lfs f1, lbl_806D7900(r2)
    fcmpo cr0, f31, f1
    cror eq, gt, eq
    bne fn_80141454_L_801416AC
    lfs f0, lbl_806D7904(r2)
    fcmpo cr0, f31, f0
    bge fn_80141454_L_80141504
    fsubs f1, f31, f1
    lfs f5, lbl_806D791C(r2)
    lfs f0, lbl_806D7908(r2)
    li r4, 0x139f
    lfs f3, lbl_806D7910(r2)
    fmr f6, f5
    fdivs f8, f1, f0
    lfs f0, lbl_806D790C(r2)
    lwz r3, 0x10(r31)
    li r5, 0x2
    lfs f1, lbl_806D7914(r2)
    lfs f2, lbl_806D7918(r2)
    fmadds f3, f3, f8, f0
    fmr f7, f5
    fmr f4, f3
    bl fn_8016918C
    b fn_80141454_L_801416AC
    fn_80141454_L_80141504:
    lfs f1, lbl_806D7920(r2)
    fcmpo cr0, f31, f1
    bge fn_80141454_L_80141554
    fsubs f1, f31, f0
    lfs f5, lbl_806D791C(r2)
    lfs f0, lbl_806D7928(r2)
    li r4, 0x139f
    lfs f3, lbl_806D7924(r2)
    fmr f6, f5
    fdivs f0, f1, f0
    lwz r3, 0x10(r31)
    lfs f1, lbl_806D7914(r2)
    li r5, 0x2
    lfs f2, lbl_806D7918(r2)
    fmadds f3, f3, f0, f5
    fmr f7, f5
    fmr f8, f5
    fmr f4, f3
    bl fn_8016918C
    b fn_80141454_L_801416AC
    fn_80141454_L_80141554:
    lfs f0, lbl_806D792C(r2)
    fcmpo cr0, f31, f0
    bge fn_80141454_L_801415A8
    fsubs f1, f31, f1
    lfs f5, lbl_806D791C(r2)
    lfs f0, lbl_806D7928(r2)
    li r4, 0x139f
    lfs f4, lbl_806D7924(r2)
    fmr f6, f5
    fdivs f3, f1, f0
    lfs f0, lbl_806D7930(r2)
    lwz r3, 0x10(r31)
    li r5, 0x2
    lfs f1, lbl_806D7914(r2)
    lfs f2, lbl_806D7918(r2)
    fnmsubs f3, f4, f3, f0
    fmr f7, f5
    fmr f8, f5
    fmr f4, f3
    bl fn_8016918C
    b fn_80141454_L_801416AC
    fn_80141454_L_801415A8:
    lfs f0, lbl_806D7934(r2)
    fcmpo cr0, f31, f0
    bge fn_80141454_L_80141608
    lwz r3, 0x10(r31)
    li r4, 0x139f
    lfs f1, lbl_806D7914(r2)
    li r5, 0x0
    lfs f2, lbl_806D7918(r2)
    bl fn_801698B4
    lfs f0, lbl_806D792C(r2)
    li r4, 0x139f
    lfs f3, lbl_806D791C(r2)
    li r5, 0x2
    fsubs f2, f31, f0
    lfs f0, lbl_806D7938(r2)
    fmr f4, f3
    lwz r3, 0x10(r31)
    fmr f5, f3
    lfs f1, lbl_806D7914(r2)
    fdivs f0, f2, f0
    lfs f2, lbl_806D7918(r2)
    fsubs f6, f3, f0
    bl fn_80169468
    b fn_80141454_L_801416AC
    fn_80141454_L_80141608:
    lfs f1, lbl_806D793C(r2)
    fcmpo cr0, f31, f1
    bge fn_80141454_L_80141630
    lwz r3, 0x10(r31)
    li r4, 0x139f
    lfs f1, lbl_806D7914(r2)
    li r5, 0x0
    lfs f2, lbl_806D7918(r2)
    bl fn_801698B4
    b fn_80141454_L_801416AC
    fn_80141454_L_80141630:
    lfs f0, lbl_806D7940(r2)
    fcmpo cr0, f31, f0
    bge fn_80141454_L_801416AC
    fsubs f1, f31, f1
    lfs f0, lbl_806D7944(r2)
    lfs f4, lbl_806D7948(r2)
    li r4, 0x139f
    lfs f3, lbl_806D791C(r2)
    li r5, 0x0
    fdivs f30, f1, f0
    lfs f0, lbl_806D794C(r2)
    lwz r3, 0x10(r31)
    lfs f1, lbl_806D7914(r2)
    lfs f2, lbl_806D7918(r2)
    fnmsubs f28, f4, f30, f3
    fmadds f29, f0, f30, f3
    fmr f3, f28
    fmr f4, f29
    bl fn_801697C0
    lfs f5, lbl_806D791C(r2)
    fmr f3, f28
    fmr f4, f29
    lwz r3, 0x10(r31)
    fmr f6, f5
    lfs f1, lbl_806D7914(r2)
    fmr f7, f5
    fmr f8, f30
    lfs f2, lbl_806D7918(r2)
    li r4, 0x139f
    li r5, 0x2
    bl fn_8016918C
    fn_80141454_L_801416AC:
    lfs f2, 0x18(r31)
    lfs f0, lbl_806D7950(r2)
    fcmpo cr0, f2, f0
    bge fn_80141454_L_801416F8
    fdivs f8, f2, f0
    lfs f5, lbl_806D791C(r2)
    lfs f1, lbl_806D7954(r2)
    li r4, 0x139f
    lfs f0, lbl_806D790C(r2)
    li r5, 0x1
    fmadds f3, f1, f8, f0
    lwz r3, 0x10(r31)
    fmr f6, f5
    lfs f1, lbl_806D7914(r2)
    fmr f7, f5
    lfs f2, lbl_806D7918(r2)
    fmr f4, f3
    bl fn_8016918C
    b fn_80141454_L_80141858
    fn_80141454_L_801416F8:
    lfs f1, lbl_806D7920(r2)
    fcmpo cr0, f2, f1
    bge fn_80141454_L_80141750
    fsubs f1, f2, f0
    lfs f5, lbl_806D791C(r2)
    lfs f0, lbl_806D7900(r2)
    li r4, 0x139f
    lfs f3, lbl_806D794C(r2)
    fmr f6, f5
    fdivs f4, f1, f0
    lfs f2, lbl_806D7958(r2)
    lfs f0, lbl_806D795C(r2)
    li r5, 0x1
    lwz r3, 0x10(r31)
    lfs f1, lbl_806D7914(r2)
    fmadds f3, f3, f4, f2
    lfs f2, lbl_806D7918(r2)
    fnmsubs f8, f0, f4, f5
    fmr f7, f5
    fmr f4, f3
    bl fn_8016918C
    b fn_80141454_L_80141858
    fn_80141454_L_80141750:
    lfs f0, lbl_806D7960(r2)
    fcmpo cr0, f2, f0
    bge fn_80141454_L_801417A8
    fsubs f1, f2, f1
    lfs f5, lbl_806D791C(r2)
    lfs f0, lbl_806D7944(r2)
    li r4, 0x139f
    lfs f3, lbl_806D7968(r2)
    fmr f6, f5
    fdivs f4, f1, f0
    lfs f2, lbl_806D7964(r2)
    lfs f0, lbl_806D795C(r2)
    li r5, 0x1
    lwz r3, 0x10(r31)
    lfs f1, lbl_806D7914(r2)
    fmadds f3, f3, f4, f2
    lfs f2, lbl_806D7918(r2)
    fnmsubs f8, f0, f4, f0
    fmr f7, f5
    fmr f4, f3
    bl fn_8016918C
    b fn_80141454_L_80141858
    fn_80141454_L_801417A8:
    lfs f0, lbl_806D7940(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne fn_80141454_L_80141858
    fsubs f1, f2, f0
    lfs f5, lbl_806D791C(r2)
    lfs f0, lbl_806D796C(r2)
    li r4, 0x139f
    lfs f7, lbl_806D7974(r2)
    fmr f6, f5
    fdivs f30, f1, f0
    lfs f4, lbl_806D7970(r2)
    lfs f3, lbl_806D797C(r2)
    li r5, 0x1
    lfs f2, lbl_806D7978(r2)
    lfs f1, lbl_806D7984(r2)
    lfs f0, lbl_806D7918(r2)
    fmadds f28, f7, f30, f4
    fnmsubs f29, f3, f30, f2
    lfs f9, lbl_806D7980(r2)
    fnmsubs f31, f1, f30, f0
    lfs f0, lbl_806D7914(r2)
    fmr f3, f28
    fmr f4, f29
    fmr f2, f31
    lwz r3, 0x10(r31)
    fmr f7, f5
    fmr f8, f30
    fnmsubs f1, f9, f30, f0
    bl fn_8016918C
    lfs f5, lbl_806D791C(r2)
    fmr f2, f31
    lfs f1, lbl_806D7988(r2)
    fmr f3, f28
    lfs f0, lbl_806D7914(r2)
    fmr f4, f29
    fmr f6, f5
    fmr f7, f5
    lwz r3, 0x10(r31)
    fmr f8, f30
    li r4, 0x139f
    fmadds f1, f1, f30, f0
    li r5, 0x1
    bl fn_8016918C
    fn_80141454_L_80141858:
    lfs f2, 0x18(r31)
    lfs f1, lbl_806D791C(r2)
    lfs f0, lbl_806D798C(r2)
    fadds f1, f2, f1
    stfs f1, 0x18(r31)
    lfs f1, 0x18(r31)
    fcmpo cr0, f1, f0
    ble fn_80141454_L_80141884
    li r0, 0x1
    stw r0, 0x14(r31)
    stfs f0, 0x18(r31)
    fn_80141454_L_80141884:
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    psq_l f30, 0x38(r1), 0, 0
    lfd f30, 0x30(r1)
    psq_l f29, 0x28(r1), 0, 0
    lfd f29, 0x20(r1)
    psq_l f28, 0x18(r1), 0, 0
    lfd f28, 0x10(r1)
    lwz r0, 0x54(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

LogoAnim::~LogoAnim() {
    vptr = lbl_8048ECE0;
}

LogoAnim::LogoAnim(void *o, int a) : AnimMid(a) {
    vptr = lbl_8048ECE0;
    obj = o;
    done = 0;
    t = lbl_806D7990;
}

extern "C" void fn_8014196C(void) {
    PreloadResource(0x139F);
}

extern "C" asm void fn_80141990(void) { /* 0x80141990 size:0x38 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmplwi r3, 0x0
    stw r0, 0x14(r1)
    beq fn_80141990_L_801419B8
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80141990_L_801419B8:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" AnimMid *dtor_801419C8(AnimMid *p, short flag) {
    if (p) {
        p->vptr = lbl_8048ED10;
        if (p) {
            p->vptr = lbl_8048ECF8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(p);
        }
    }
    return p;
}

extern "C" AnimBase *fn_80141A24(AnimBase *p, short flag) {
    if (p) {
        p->vptr = lbl_8048ECF8;
        if (flag > 0) {
            MemoryManager_TimedFree(p);
        }
    }
    return p;
}
