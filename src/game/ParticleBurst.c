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

typedef union WGPipe {
    unsigned char u8;
    float f32;
} WGPipe;

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
extern void *FUN_8003b120(unsigned long size);
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
extern const unsigned char lbl_803292B4[6][3];

void ParticleBurst_Draw(char *self);
asm void ParticleBurst_DrawCb(void);

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
            c = lbl_803292B4[i % 6];
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

/*
 * ParticleBurst_DrawCb stays an exact asm body: the draw-manager load is
 * followed by a redundant `p ? p : 0` select, which has no genuine C form in
 * this C TU (same as TwinSpriteOverlay_AddDraw). Its extab entry is emitted
 * manually and ordered by tools/extab_order.json.
 */
extern void Mtx44_TransformVec3();
extern void clDrawMan_AddSorted_NoDepthBias();
extern void *lbl_806D10AC;
extern float lbl_803292C8[];
extern float lbl_805DF3D0[];

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ParticleBurst_DrawCb[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ParticleBurst_DrawCb = {
    (void *)&ParticleBurst_DrawCb, 0x00000094, (void *)extab_ParticleBurst_DrawCb
};

asm void ParticleBurst_DrawCb(void) { /* 0x800B4388 size:0x94 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r4, lbl_805DF3D0@ha
    lis r5, lbl_803292C8@ha
    stw r0, 0x34(r1)
    addi r4, r4, lbl_805DF3D0@l
    stw r31, 0x2c(r1)
    mr r31, r3
    addi r3, r1, 0x14
    lwzu r7, lbl_803292C8@l(r5)
    lwz r6, 0x4(r5)
    lwz r0, 0x8(r5)
    addi r5, r1, 0x8
    stw r7, 0x14(r1)
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    stw r7, 0x8(r1)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl Mtx44_TransformVec3
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne ParticleBurst_DrawCb_L_800B43E8
    li r3, 0x0
    ParticleBurst_DrawCb_L_800B43E8:
    lis r4, ParticleBurst_Draw@ha
    lfs f1, 0x14(r1)
    lfs f2, 0x18(r1)
    addi r4, r4, ParticleBurst_Draw@l
    lfs f3, 0x1c(r1)
    mr r5, r31
    lfs f4, lbl_806D5034(r2)
    bl clDrawMan_AddSorted_NoDepthBias
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

/*
 * ParticleBurst_Update stays an exact asm body: a C form matches every GPR,
 * branch and instruction, but MWCC rotates the callee-saved float registers
 * for the hoisted loop constants (99.6 %), so the asm is kept.
 */
asm void ParticleBurst_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ParticleBurst_Update[8] = {
    0x29, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ParticleBurst_Update = {
    (void *)&ParticleBurst_Update, 0x000003E8, (void *)extab_ParticleBurst_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ParticleBurst_Update(void) { /* 0x800B441C size:0x3E8 */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stfd f30, 0x70(r1)
    psq_st f30, 0x78(r1), 0, 0
    stfd f29, 0x60(r1)
    psq_st f29, 0x68(r1), 0, 0
    stfd f28, 0x50(r1)
    psq_st f28, 0x58(r1), 0, 0
    stfd f27, 0x40(r1)
    psq_st f27, 0x48(r1), 0, 0
    stfd f26, 0x30(r1)
    psq_st f26, 0x38(r1), 0, 0
    stfd f25, 0x20(r1)
    psq_st f25, 0x28(r1), 0, 0
    stmw r27, 0xc(r1)
    mr r27, r3
    li r29, 0x1
    lbz r0, 0xb4(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ParticleBurst_Update_L_800B4660
    bge ParticleBurst_Update_L_800B47B8
    cmpwi r0, 0x0
    bge ParticleBurst_Update_L_800B448C
    b ParticleBurst_Update_L_800B47B8
    ParticleBurst_Update_L_800B448C:
    li r0, 0x1
    li r3, 0x480
    stb r0, 0x14(r27)
    bl FUN_8003b120
    stw r3, 0xcc(r27)
    li r30, 0x0
    lfs f26, lbl_806D5020(r2)
    li r31, 0x0
    lfs f27, lbl_806D5024(r2)
    lfs f29, lbl_806D5090(r2)
    lfs f30, lbl_806D5080(r2)
    lfs f31, lbl_806D5034(r2)
    ParticleBurst_Update_L_800B44BC:
    lwz r3, 0xcc(r27)
    li r6, 0x12
    srawi r5, r30, 31
    addi r0, r31, 0x4
    stfsx f26, r3, r31
    subfc r3, r6, r30
    srwi r4, r6, 31
    lwz r3, 0xcc(r27)
    adde. r28, r5, r4
    stfsx f27, r3, r0
    bne ParticleBurst_Update_L_800B44FC
    lfs f0, lbl_806D5044(r2)
    addi r0, r31, 0x8
    lwz r3, 0xcc(r27)
    stfsx f0, r3, r0
    b ParticleBurst_Update_L_800B450C
    ParticleBurst_Update_L_800B44FC:
    lfs f0, lbl_806D5074(r2)
    addi r0, r31, 0x8
    lwz r3, 0xcc(r27)
    stfsx f0, r3, r0
    ParticleBurst_Update_L_800B450C:
    cmpwi r28, 0x0
    beq ParticleBurst_Update_L_800B4528
    lfs f1, lbl_806D5140(r2)
    lfs f2, lbl_806D5144(r2)
    bl Rand_RangeFloat
    fmr f28, f1
    b ParticleBurst_Update_L_800B4538
    ParticleBurst_Update_L_800B4528:
    lfs f1, lbl_806D5140(r2)
    lfs f2, lbl_806D5148(r2)
    bl Rand_RangeFloat
    fmr f28, f1
    ParticleBurst_Update_L_800B4538:
    lfs f1, lbl_806D5084(r2)
    lfs f2, lbl_806D5134(r2)
    bl Rand_RangeFloat
    fadds f0, f29, f1
    fmuls f25, f30, f0
    fmr f1, f25
    bl sin
    frsp f0, f1
    lwz r3, 0xcc(r27)
    fmr f1, f25
    addi r0, r31, 0x10
    fmuls f0, f28, f0
    stfsx f0, r3, r0
    bl cos
    frsp f0, f1
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x14
    lfs f1, lbl_806D514C(r2)
    fmuls f0, f28, f0
    stfsx f0, r3, r0
    bl Rand_RangeFloatMax
    fmuls f1, f30, f1
    bl BuildOrientationFromYaw
    lwz r3, 0xcc(r27)
    addi r0, r31, 0xc
    lfs f2, lbl_806D5154(r2)
    stfsx f1, r3, r0
    lfs f1, lbl_806D5150(r2)
    bl Rand_RangeFloat
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x18
    stfsx f1, r3, r0
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f0, 0x10(r3)
    fcmpo cr0, f31, f0
    bge ParticleBurst_Update_L_800B45DC
    lfs f1, 0x18(r3)
    lfs f0, lbl_806D5070(r2)
    fmuls f0, f1, f0
    stfs f0, 0x18(r3)
    ParticleBurst_Update_L_800B45DC:
    cmpwi r28, 0x0
    bne ParticleBurst_Update_L_800B45F8
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x1c
    li r4, 0x0
    stbx r4, r3, r0
    b ParticleBurst_Update_L_800B4624
    ParticleBurst_Update_L_800B45F8:
    lis r4, 0x6666
    lwz r3, 0xcc(r27)
    addi r4, r4, 0x6667
    addi r0, r31, 0x1c
    mulhw r4, r4, r30
    srawi r4, r4, 2
    srwi r5, r4, 31
    add r4, r4, r5
    mulli r4, r4, 0xa
    subf r4, r4, r30
    stbx r4, r3, r0
    ParticleBurst_Update_L_800B4624:
    addi r30, r30, 0x1
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x1d
    li r4, 0x0
    cmpwi r30, 0x24
    stbx r4, r3, r0
    addi r31, r31, 0x20
    blt ParticleBurst_Update_L_800B44BC
    lis r3, ParticleBurst_DrawCb@ha
    addi r0, r3, ParticleBurst_DrawCb@l
    stw r0, 0x78(r27)
    stw r27, 0x7c(r27)
    lbz r3, 0xb4(r27)
    addi r0, r3, 0x1
    stb r0, 0xb4(r27)
    ParticleBurst_Update_L_800B4660:
    lfs f0, lbl_806D50E4(r2)
    li r30, 0x0
    mr r31, r30
    fneg f26, f0
    ParticleBurst_Update_L_800B4670:
    lwz r0, 0xcc(r27)
    add r4, r0, r31
    lbz r0, 0x1d(r4)
    extsb. r0, r0
    bne ParticleBurst_Update_L_800B4778
    lbz r3, 0x1c(r4)
    extsb. r0, r3
    beq ParticleBurst_Update_L_800B469C
    subi r0, r3, 0x1
    stb r0, 0x1c(r4)
    b ParticleBurst_Update_L_800B4778
    ParticleBurst_Update_L_800B469C:
    lfs f1, 0x14(r4)
    lfs f0, lbl_806D5044(r2)
    fadds f0, f1, f0
    stfs f0, 0x14(r4)
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f1, 0x0(r3)
    lfs f0, 0x10(r3)
    fadds f0, f1, f0
    stfs f0, 0x0(r3)
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f1, 0x4(r3)
    lfs f0, 0x14(r3)
    fadds f0, f1, f0
    stfs f0, 0x4(r3)
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f1, 0xc(r3)
    lfs f0, 0x18(r3)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    lwz r3, 0xcc(r27)
    addi r0, r31, 0xc
    stfsx f1, r3, r0
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f0, 0x0(r3)
    fcmpo cr0, f0, f26
    bge ParticleBurst_Update_L_800B471C
    li r0, 0x1
    stb r0, 0x1d(r3)
    ParticleBurst_Update_L_800B471C:
    lwz r0, 0xcc(r27)
    lfs f1, lbl_806D5158(r2)
    add r3, r0, r31
    lfs f0, 0x0(r3)
    fcmpo cr0, f1, f0
    bge ParticleBurst_Update_L_800B473C
    li r0, 0x1
    stb r0, 0x1d(r3)
    ParticleBurst_Update_L_800B473C:
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f0, 0x4(r3)
    fcmpo cr0, f0, f26
    bge ParticleBurst_Update_L_800B4758
    li r0, 0x1
    stb r0, 0x1d(r3)
    ParticleBurst_Update_L_800B4758:
    lwz r0, 0xcc(r27)
    lfs f1, lbl_806D515C(r2)
    add r3, r0, r31
    lfs f0, 0x4(r3)
    fcmpo cr0, f1, f0
    bge ParticleBurst_Update_L_800B4778
    li r0, 0x1
    stb r0, 0x1d(r3)
    ParticleBurst_Update_L_800B4778:
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x1d
    lbzx r0, r3, r0
    extsb. r0, r0
    bne ParticleBurst_Update_L_800B4790
    li r29, 0x0
    ParticleBurst_Update_L_800B4790:
    addi r30, r30, 0x1
    addi r31, r31, 0x20
    cmpwi r30, 0x24
    blt ParticleBurst_Update_L_800B4670
    cmpwi r29, 0x0
    beq ParticleBurst_Update_L_800B47B8
    lwz r3, 0xcc(r27)
    bl MemoryManager_Free
    mr r3, r27
    bl DrawEffect_Free
    ParticleBurst_Update_L_800B47B8:
    psq_l f31, 0x88(r1), 0, 0
    lfd f31, 0x80(r1)
    psq_l f30, 0x78(r1), 0, 0
    lfd f30, 0x70(r1)
    psq_l f29, 0x68(r1), 0, 0
    lfd f29, 0x60(r1)
    psq_l f28, 0x58(r1), 0, 0
    lfd f28, 0x50(r1)
    psq_l f27, 0x48(r1), 0, 0
    lfd f27, 0x40(r1)
    psq_l f26, 0x38(r1), 0, 0
    lfd f26, 0x30(r1)
    psq_l f25, 0x28(r1), 0, 0
    lfd f25, 0x20(r1)
    lmw r27, 0xc(r1)
    lwz r0, 0x94(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}
