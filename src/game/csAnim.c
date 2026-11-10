#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * clCSAnim (csAnim.cpp): keyframed sprite animation node list.
 * .text 0x8013AB74..0x8013BA90
 *
 * fn_8013BA78 (Reset) is inlined into its callers here; the weak
 * out-of-line copy CW emits is superseded by the strong definition in
 * csAnim_Reset.c, which sits at the address following this TU.
 *
 * fn_8013B87C is the CSAnim destructor: deleting `next` inlines the dtor
 * recursively up to the inline depth limit, and only the innermost level
 * calls the ResCtrl member dtor out of line (weak copy dtor_80082960).
 *
 * fn_8013AE20 (fp register count) does not match from C yet; it stays as
 * asm with manual extab, ordered via tools/extab_order.json.
 */

typedef struct CSAnimKey {
    int type;
    int count;
    float x;
    float y;
    float u10;
    float u14;
    float u18;
    float r;
    float g;
    float b;
    float a;
} CSAnimKey;

C_REGION_END
#pragma cplusplus on
struct ResCtrl {
    int res;
    int pad1C;
    int res20;
    int pad24;
    ~ResCtrl() {}
};

struct CSAnim {
    int id;
    CSAnim *next;
    int flags;
    int frame;
    int index;
    CSAnimKey *keys;
    /* 0x18: ResCtrl sprite resource */
    ResCtrl res;
    unsigned char visible;
    float x;
    float y;
    float z;
    int pad38;
    int pad3C;
    float u40;
    float u44;
    float u48;
    unsigned int color[4];
    int pad5C;
    int u60;
    int u64;
    int u68;
    ~CSAnim();
};
#pragma cplusplus off
C_REGION_BEGIN
typedef struct CSAnim CSAnim;

extern const int lbl_806D7480;
extern const int lbl_806D7498;
/* .rodata 0x8035C678..0x8035C6B8 (owned; referenced by the asm fn_8013AE20) */
#pragma force_active on
extern const char lbl_8035C678[] = "csAnim.cpp";
extern const char lbl_8035C684[] = "clCSAnim::update() : ACT_JUMP    not found LABEL\n";
#pragma force_active reset
extern const int lbl_806D7484;
extern const int lbl_806D7488;
extern const int lbl_806D7490;

extern void fn_8011FAFC(void *res, void *arg);
extern void OSPanic(const char *file, int line, const char *msg, ...);
extern void ResCtrl_Init(void *res);

#ifdef NON_MATCHING
void fn_8013AE20(CSAnim *n, float x, float y, float alpha);
#else
void fn_8013AE20(void);
#endif

inline void fn_8013BA78(CSAnim *n) {
    n->flags = 2;
    n->frame = 0;
    n->index = 0;
}

void fn_8013AB74(CSAnim *n, void *arg, int id) {
    if ((id < 0 || n->id == id) && n->keys && (n->flags & 4)) {
        fn_8011FAFC(&n->res, arg);
    }
    if (n->next) {
        fn_8013AB74(n->next, arg, id);
    }
}

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013AE20[8] = {
    0x31, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013AE20 = {
    (void *)&fn_8013AE20, 0x000004E0, (void *)extab_fn_8013AE20
};

/* --- asm function bodies (.text order = fn address order) --- */
#ifdef NON_MATCHING
/* NON_MATCHING: equivalent C, 312/312 instructions, float register numbering differs
 * (docs/wip/csanim/csAnim_fn_8013AE20_146lines.c). clCSAnim::update. */
static inline unsigned int CSAnim_Pack2(float r, float g, float b, float a) {
    return ((unsigned char)(int)(255.0f * r) << 24) | ((unsigned char)(int)(255.0f * g) << 16) |
           ((unsigned char)(int)(255.0f * b) << 8) | (unsigned char)(int)a;
}

void fn_8013AE20(CSAnim *n, float x, float y, float alpha) {
    CSAnimKey *k;
    CSAnimKey *k2;
    int i;
    float t;
    unsigned int c;
    float px;
    float py;
    float r;
    float g;
    float b;
    float a;
    float u10;
    float u14;
    float u18;

    if (n->next) {
        fn_8013AE20(n->next, x, y, alpha);
    }
    if (n->keys && (n->flags & 1)) {
        k = &n->keys[n->index];
        for (;;) {
            if (k->type == 0) {
                n->index++;
                n->frame = 0;
                k = &n->keys[n->index];
            } else if (k->type == 1) {
                if (n->frame < k->count) {
                    n->flags &= ~4;
                    if (n->flags & 2) {
                        n->flags &= ~2;
                    } else {
                        n->frame++;
                    }
                    return;
                }
                n->index++;
                n->frame = 0;
                k = &n->keys[n->index];
            } else if (k->type == 2) {
                if (n->frame < k->count) {
                    if (n->flags & 2) {
                        n->flags &= ~2;
                    } else {
                        n->frame++;
                    }
                    break;
                }
                n->index++;
                n->frame = 0;
                k = &n->keys[n->index];
            } else if (k->type == 3) {
                for (i = 0;; i++) {
                    if (n->keys[i].type == 5) {
                        OSPanic(lbl_8035C678, 0x86, lbl_8035C684);
                    }
                    if (n->keys[i].type == 0 && k->count == n->keys[i].count) {
                        n->index = i;
                        n->frame = 0;
                        k = &n->keys[n->index];
                        goto next;
                    }
                }
            } else if (k->type == 4) {
                n->flags |= lbl_806D7480;
                px = k->x;
                py = k->y;
                px += x;
                py += y;
                n->visible = 1;
                n->x = px;
                n->y = py;
                n->z = 1.0f;
                u10 = k->u10;
                u14 = k->u14;
                n->u44 = u10;
                n->u48 = u14;
                c = CSAnim_Pack2(k->r, k->g, k->b, 255.0f * k->a * alpha);
                n->color[0] = c;
                n->color[1] = c;
                n->color[2] = c;
                n->color[3] = c;
                return;
            } else {
                fn_8013BA78(n);
                return;
            }
        next:;
        }
        n->flags |= lbl_806D7480;
        t = (float)n->frame / (float)k->count;
        k2 = &n->keys[n->index + 1];
        px = k->x + t * (k2->x - k->x);
        r = k->r + t * (k2->r - k->r);
        py = k->y + t * (k2->y - k->y);
        u10 = k->u10 + t * (k2->u10 - k->u10);
        g = k->g + t * (k2->g - k->g);
        u18 = k->u18 + t * (k2->u18 - k->u18);
        u14 = k->u14 + t * (k2->u14 - k->u14);
        b = k->b + t * (k2->b - k->b);
        a = k->a + t * (k2->a - k->a);
        n->visible = 1;
        n->x = px + x;
        n->y = py + y;
        n->z = 1.0f;
        n->u44 = u10;
        n->u48 = u14;
        n->u40 = u18;
        c = CSAnim_Pack2(r, g, b, alpha * (255.0f * a));
        n->color[0] = c;
        n->color[1] = c;
        n->color[2] = c;
        n->color[3] = c;
    }
}
#else
asm void fn_8013AE20(void) { /* 0x8013AE20 size:0x4E0 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stfd f30, 0xa0(r1)
    psq_st f30, 0xa8(r1), 0, 0
    stfd f29, 0x90(r1)
    psq_st f29, 0x98(r1), 0, 0
    stfd f28, 0x80(r1)
    psq_st f28, 0x88(r1), 0, 0
    stfd f27, 0x70(r1)
    psq_st f27, 0x78(r1), 0, 0
    stfd f26, 0x60(r1)
    psq_st f26, 0x68(r1), 0, 0
    stfd f25, 0x50(r1)
    psq_st f25, 0x58(r1), 0, 0
    stmw r26, 0x38(r1)
    mr r30, r3
    fmr f29, f1
    lwz r3, 0x4(r3)
    fmr f30, f2
    fmr f31, f3
    cmplwi r3, 0x0
    beq fn_8013AE20_L_8013AE88
    bl fn_8013AE20
    fn_8013AE20_L_8013AE88:
    lwz r3, 0x14(r30)
    cmplwi r3, 0x0
    beq fn_8013AE20_L_8013B2B4
    lwz r0, 0x8(r30)
    clrlwi. r0, r0, 31
    beq fn_8013AE20_L_8013B2B4
    lwz r0, 0x10(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    fn_8013AE20_L_8013AEAC:
    lwz r0, 0x0(r31)
    cmpwi r0, 0x0
    bne fn_8013AE20_L_8013AEE0
    lwz r3, 0x10(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x10(r30)
    stw r0, 0xc(r30)
    lwz r0, 0x10(r30)
    lwz r3, 0x14(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    b fn_8013AE20_L_8013AEAC
    fn_8013AE20_L_8013AEE0:
    cmpwi r0, 0x1
    bne fn_8013AE20_L_8013AF54
    lwz r3, 0xc(r30)
    lwz r0, 0x4(r31)
    cmpw r3, r0
    bge fn_8013AE20_L_8013AF2C
    lwz r0, 0x8(r30)
    rlwinm r0, r0, 0, 30, 28
    stw r0, 0x8(r30)
    lwz r3, 0x8(r30)
    rlwinm. r0, r3, 0, 30, 30
    beq fn_8013AE20_L_8013AF1C
    rlwinm r0, r3, 0, 31, 29
    stw r0, 0x8(r30)
    b fn_8013AE20_L_8013B2B4
    fn_8013AE20_L_8013AF1C:
    lwz r3, 0xc(r30)
    addi r0, r3, 0x1
    stw r0, 0xc(r30)
    b fn_8013AE20_L_8013B2B4
    fn_8013AE20_L_8013AF2C:
    lwz r3, 0x10(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x10(r30)
    stw r0, 0xc(r30)
    lwz r0, 0x10(r30)
    lwz r3, 0x14(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    b fn_8013AE20_L_8013AEAC
    fn_8013AE20_L_8013AF54:
    cmpwi r0, 0x2
    bne fn_8013AE20_L_8013AFB8
    lwz r4, 0xc(r30)
    lwz r0, 0x4(r31)
    cmpw r4, r0
    bge fn_8013AE20_L_8013AF90
    lwz r3, 0x8(r30)
    rlwinm. r0, r3, 0, 30, 30
    beq fn_8013AE20_L_8013AF84
    rlwinm r0, r3, 0, 31, 29
    stw r0, 0x8(r30)
    b fn_8013AE20_L_8013B130
    fn_8013AE20_L_8013AF84:
    addi r0, r4, 0x1
    stw r0, 0xc(r30)
    b fn_8013AE20_L_8013B130
    fn_8013AE20_L_8013AF90:
    lwz r3, 0x10(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x10(r30)
    stw r0, 0xc(r30)
    lwz r0, 0x10(r30)
    lwz r3, 0x14(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    b fn_8013AE20_L_8013AEAC
    fn_8013AE20_L_8013AFB8:
    cmpwi r0, 0x3
    bne fn_8013AE20_L_8013B04C
    lis r4, lbl_8035C678@ha
    lis r3, lbl_8035C684@ha
    addi r28, r4, lbl_8035C678@l
    li r26, 0x0
    addi r29, r3, lbl_8035C684@l
    li r27, 0x0
    fn_8013AE20_L_8013AFD8:
    lwz r3, 0x14(r30)
    lwzx r0, r3, r27
    cmpwi r0, 0x5
    bne fn_8013AE20_L_8013AFFC
    mr r3, r28
    mr r5, r29
    li r4, 0x86
    crxor 6, 6, 6
    bl OSPanic
    fn_8013AE20_L_8013AFFC:
    lwz r0, 0x14(r30)
    add r4, r0, r27
    lwz r0, 0x0(r4)
    cmpwi r0, 0x0
    bne fn_8013AE20_L_8013B040
    lwz r3, 0x4(r31)
    lwz r0, 0x4(r4)
    cmpw r3, r0
    bne fn_8013AE20_L_8013B040
    stw r26, 0x10(r30)
    li r0, 0x0
    stw r0, 0xc(r30)
    lwz r0, 0x10(r30)
    lwz r3, 0x14(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    b fn_8013AE20_L_8013AEAC
    fn_8013AE20_L_8013B040:
    addi r27, r27, 0x2c
    addi r26, r26, 0x1
    b fn_8013AE20_L_8013AFD8
    fn_8013AE20_L_8013B04C:
    cmpwi r0, 0x4
    bne fn_8013AE20_L_8013B118
    lwz r4, 0x8(r30)
    li r0, 0x1
    lwz r3, lbl_806D7480(r2)
    lfs f0, lbl_806D7484(r2)
    or r3, r4, r3
    lfs f4, lbl_806D7488(r2)
    stw r3, 0x8(r30)
    lfs f1, 0x8(r31)
    lfs f2, 0xc(r31)
    fadds f1, f1, f29
    stb r0, 0x28(r30)
    fadds f2, f2, f30
    stfs f1, 0x2c(r30)
    stfs f2, 0x30(r30)
    stfs f0, 0x34(r30)
    lfs f1, 0x14(r31)
    lfs f0, 0x10(r31)
    stfs f0, 0x44(r30)
    stfs f1, 0x48(r30)
    lfs f0, 0x20(r31)
    lfs f2, 0x28(r31)
    lfs f1, 0x1c(r31)
    fmuls f0, f4, f0
    fmuls f3, f4, f2
    lfs f2, 0x24(r31)
    fmuls f1, f4, f1
    fctiwz f0, f0
    fmuls f2, f4, f2
    fctiwz f1, f1
    stfd f0, 0x20(r1)
    fmuls f3, f3, f31
    fctiwz f2, f2
    lwz r0, 0x24(r1)
    fctiwz f0, f3
    stfd f1, 0x18(r1)
    clrlslwi r3, r0, 24, 16
    lwz r0, 0x1c(r1)
    stfd f2, 0x10(r1)
    rlwimi r3, r0, 24, 0, 7
    lwz r0, 0x14(r1)
    stfd f0, 0x8(r1)
    rlwimi r3, r0, 8, 16, 23
    lwz r0, 0xc(r1)
    rlwimi r3, r0, 0, 24, 31
    stw r3, 0x4c(r30)
    stw r3, 0x50(r30)
    stw r3, 0x54(r30)
    stw r3, 0x58(r30)
    b fn_8013AE20_L_8013B2B4
    fn_8013AE20_L_8013B118:
    li r3, 0x2
    li r0, 0x0
    stw r3, 0x8(r30)
    stw r0, 0xc(r30)
    stw r0, 0x10(r30)
    b fn_8013AE20_L_8013B2B4
    fn_8013AE20_L_8013B130:
    lwz r5, 0x8(r30)
    lis r4, 0x4330
    lwz r3, lbl_806D7480(r2)
    li r0, 0x1
    stw r4, 0x20(r1)
    or r3, r5, r3
    lfd f2, lbl_806D7490(r2)
    stw r3, 0x8(r30)
    lfs f9, lbl_806D7488(r2)
    lwz r5, 0xc(r30)
    lwz r3, 0x4(r31)
    xoris r5, r5, 0x8000
    stw r4, 0x18(r1)
    xoris r3, r3, 0x8000
    lwz r4, 0x10(r30)
    stw r5, 0x24(r1)
    addi r4, r4, 0x1
    lwz r5, 0x14(r30)
    stw r3, 0x1c(r1)
    mulli r3, r4, 0x2c
    lfd f1, 0x20(r1)
    lfd f0, 0x18(r1)
    fsubs f1, f1, f2
    add r3, r5, r3
    fsubs f0, f0, f2
    lfs f10, 0x8(r31)
    lfs f3, 0x8(r3)
    lfs f11, 0xc(r31)
    fdivs f2, f1, f0
    lfs f6, 0xc(r3)
    lfs f13, 0x1c(r31)
    lfs f4, 0x1c(r3)
    lfs f27, 0x24(r31)
    lfs f28, 0x20(r31)
    fsubs f8, f3, f10
    lfs f1, 0x20(r3)
    fsubs f7, f6, f11
    lfs f3, 0x24(r3)
    fsubs f6, f4, f13
    lfs f26, 0x28(r31)
    fsubs f4, f3, f27
    lfs f0, 0x28(r3)
    fsubs f5, f1, f28
    lfs f12, 0x10(r3)
    fsubs f1, f0, f26
    lfs f0, 0x10(r31)
    fmadds f25, f2, f8, f10
    lfs f10, 0x18(r3)
    fmadds f6, f2, f6, f13
    lfs f13, 0x18(r31)
    fmadds f3, f2, f1, f26
    lfs f1, 0x14(r31)
    fmadds f26, f2, f7, f11
    lfs f11, 0x14(r3)
    fmadds f5, f2, f5, f28
    fmuls f8, f9, f6
    stb r0, 0x28(r30)
    fmadds f4, f2, f4, f27
    fmuls f7, f9, f5
    fmuls f5, f9, f3
    lfs f3, lbl_806D7484(r2)
    fmuls f6, f9, f4
    fadds f4, f25, f29
    fsubs f12, f12, f0
    fctiwz f7, f7
    stfs f4, 0x2c(r30)
    fadds f4, f26, f30
    fctiwz f8, f8
    stfd f7, 0x8(r1)
    fsubs f9, f11, f1
    fctiwz f6, f6
    stfs f4, 0x30(r30)
    fmuls f5, f31, f5
    lwz r0, 0xc(r1)
    fmadds f0, f2, f12, f0
    stfd f8, 0x10(r1)
    fctiwz f4, f5
    clrlslwi r0, r0, 24, 16
    stfs f3, 0x34(r30)
    fsubs f7, f10, f13
    fmadds f1, f2, f9, f1
    lwz r3, 0x14(r1)
    stfs f0, 0x44(r30)
    fmadds f2, f2, f7, f13
    rlwimi r0, r3, 24, 0, 7
    stfd f6, 0x28(r1)
    lwz r3, 0x2c(r1)
    stfs f1, 0x48(r30)
    rlwimi r0, r3, 8, 16, 23
    stfd f4, 0x30(r1)
    lwz r3, 0x34(r1)
    stfs f2, 0x40(r30)
    rlwimi r0, r3, 0, 24, 31
    stw r0, 0x4c(r30)
    stw r0, 0x50(r30)
    stw r0, 0x54(r30)
    stw r0, 0x58(r30)
    fn_8013AE20_L_8013B2B4:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    psq_l f30, 0xa8(r1), 0, 0
    lfd f30, 0xa0(r1)
    psq_l f29, 0x98(r1), 0, 0
    lfd f29, 0x90(r1)
    psq_l f28, 0x88(r1), 0, 0
    lfd f28, 0x80(r1)
    psq_l f27, 0x78(r1), 0, 0
    lfd f27, 0x70(r1)
    psq_l f26, 0x68(r1), 0, 0
    lfd f26, 0x60(r1)
    psq_l f25, 0x58(r1), 0, 0
    lfd f25, 0x50(r1)
    lmw r26, 0x38(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}
#endif

void fn_8013B300(CSAnim *n, int id) {
    if (id < 0 || n->id == id) {
        fn_8013BA78(n);
    }
    if (n->next) {
        fn_8013B300(n->next, id);
    }
}

void fn_8013B4FC(CSAnim *n, int id) {
    if ((id < 0 || n->id == id) && n->keys && !(n->flags & 1)) {
        fn_8013BA78(n);
        n->flags |= lbl_806D7498;
    }
    if (n->next) {
        fn_8013B4FC(n->next, id);
    }
}

void fn_8013B7A8(CSAnim *n, CSAnim *add) {
    if (n->next) {
        fn_8013B7A8(n->next, add);
        return;
    }
    n->next = add;
}

C_REGION_END
#pragma cplusplus on
#pragma exceptions on
void operator delete(void *p);

CSAnim::~CSAnim() {
    if (next) {
        delete next;
    }
}
#pragma exceptions reset
#pragma cplusplus off
C_REGION_BEGIN

CSAnim *fn_8013B9A0(CSAnim *n, int res, int res20, int mode, CSAnimKey *keys, int id) {
    n->id = id;
    n->keys = 0;
    ResCtrl_Init(&n->res);
    fn_8013BA78(n);
    n->next = 0;
    if (keys == 0) {
        return n;
    }
    n->keys = keys;
    n->res.res = res;
    n->res.res20 = res20;
    if (res20 <= -1 || res20 >= 5) {
        n->res.res20 = 0;
    }
    switch (mode) {
    case 1:
        n->u60 = 1;
        n->u64 = 4;
        n->u68 = 1;
        break;
    default:
        n->u60 = 1;
        n->u64 = 4;
        n->u68 = 5;
        break;
    }
    return n;
}
C_REGION_END
