/* === extracted from auto_Tachometer_RenderDig_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void SpriteHandle_RecomputeCull(int h);
extern void SpriteHandle_SetActiveFlag(int h, unsigned char on);
#ifdef NON_MATCHING
extern void SpriteLayer_SetResource(int h, int res);
#else
extern void SpriteLayer_SetResource();
#endif
#ifdef NON_MATCHING
extern void fn_8011F744(int h, float sx, float sy);
#else
extern void fn_8011F744();
#endif
#ifdef NON_MATCHING
extern void fn_8011F804(int h, float x, float y);
#else
extern void fn_8011F804();
#endif

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_806cf25c;
extern unsigned int FLOAT_806d1468;
extern unsigned int FLOAT_806d146c;
extern unsigned int FLOAT_806d1474;
extern unsigned int g_gameMode;
extern unsigned int g_tachometer_displaySpeed;
extern unsigned char g_tachometer_isInitialized;
extern unsigned int Tachometer_bss_806D1459;
extern unsigned int lbl_806D4E48;
extern unsigned int lbl_806D4E4C;
extern unsigned int lbl_806D4E50;
extern unsigned int lbl_806D4E54;
extern unsigned int lbl_806D4E58;
extern unsigned int lbl_806D4E5C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int Tachometer_data_80411E20[];
extern unsigned int Tachometer_bss_805D3320[];

/* --- function index (1 fns, .text 0x800AB324..0x800AB6BC) ---
 * [  0] 0x800AB324 size:0x398   global Tachometer_RenderDigits
 */

/* --- forward decls --- */
#ifdef NON_MATCHING
int Tachometer_RenderDigits(void);
#else
void Tachometer_RenderDigits(void);
#endif

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Tachometer_RenderDigits[8] = {
    0x18, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tachometer_RenderDigits = {
    (void *)&Tachometer_RenderDigits, 0x00000398, (void *)extab_Tachometer_RenderDigits
};

/* --- asm function bodies (.text order = fn address order) --- */
#ifdef NON_MATCHING
/* NON_MATCHING: equivalent C (docs/wip/asm-a/tachometer_renderdigits_pooled_2fpr.patch
 * is the pooled draft, two float registers off): places the three speed digits and
 * the two frame sprites of the tachometer, then refreshes all five. */
typedef struct TachGlyphPos {
    int id;
    float x;
    float y;
} TachGlyphPos;
/* Tachometer_data_80411E20 (.data, 0x338): sprite resource ids per glyph and unit, glyph slot
 * positions, and the digit -> glyph map. */
typedef struct TachTables {
    int res[38][2];
    TachGlyphPos pos[40];
    int glyph[10];
} TachTables;
#define TACH_TBL ((TachTables *)(void *)Tachometer_data_80411E20)
#define TACH_UNIT (*(unsigned char *)&Tachometer_bss_806D1459) /* 1 = raw, else scaled */

static int Tach_GlyphRes(int glyph) {
    if (glyph < 0 || glyph >= 38) {
        return 0;
    }
    return TACH_TBL->res[glyph][TACH_UNIT];
}

static void Tach_PlaceDigit(int slot, int pos, int digit) {
    float y;
    float x;
    x = TACH_F(FLOAT_806d1468) + TACH_TBL->pos[pos].x - TACH_F(FLOAT_806d1474);
    y = TACH_F(FLOAT_806d146c) + TACH_TBL->pos[pos].y;
    SpriteLayer_SetResource(Tachometer_bss_805D3320[slot], Tach_GlyphRes(TACH_TBL->glyph[digit]));
    fn_8011F804(Tachometer_bss_805D3320[slot], x, y);
    SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[slot], 1);
}

int Tachometer_RenderDigits(void) {
    int speed;
    int i;

    if (!g_tachometer_isInitialized) {
        return 0;
    }
    if (g_gameMode != 2) {
        float v;
        if (TACH_UNIT == 1) {
            v = TACH_F(g_tachometer_displaySpeed) * 0.5f;
        } else {
            float q = TACH_F(g_tachometer_displaySpeed) / 1.6f;
            v = q * 0.5f;
        }
        speed = v;
        Tach_PlaceDigit(2, 2, speed % 10);
        Tach_PlaceDigit(3, 1, speed / 10 % 10);
        Tach_PlaceDigit(4, 0, speed / 100 % 10);
        fn_8011F804(Tachometer_bss_805D3320[0], 612.0f + TACH_F(FLOAT_806d1468) - TACH_F(FLOAT_806d1474),
                    443.0f + TACH_F(FLOAT_806d146c));
        SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[0], 1);
        fn_8011F804(Tachometer_bss_805D3320[1], 559.0f + TACH_F(FLOAT_806d1468) - TACH_F(FLOAT_806d1474),
                    427.0f + TACH_F(FLOAT_806d146c));
        SpriteHandle_SetActiveFlag(Tachometer_bss_805D3320[1], 1);
        for (i = 0; i < 5; i++) {
            fn_8011F744(Tachometer_bss_805D3320[i], TACH_F(FLOAT_806cf25c), TACH_F(FLOAT_806cf25c));
            SpriteHandle_RecomputeCull(Tachometer_bss_805D3320[i]);
        }
    }
    return 1;
}
#undef TACH_TBL
#undef TACH_UNIT
#else
asm void Tachometer_RenderDigits(void) { /* 0x800AB324 size:0x398 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stfd f30, 0x20(r1)
    psq_st f30, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    lbz r0, g_tachometer_isInitialized(r13)
    lis r3, Tachometer_data_80411E20@ha
    addi r31, r3, Tachometer_data_80411E20@l
    cmplwi r0, 0x0
    bne Tachometer_RenderDigits_L_800AB368
    li r3, 0x0
    b Tachometer_RenderDigits_L_800AB690
    Tachometer_RenderDigits_L_800AB368:
    lwz r0, g_gameMode(r13)
    cmpwi r0, 0x2
    beq Tachometer_RenderDigits_L_800AB68C
    lbz r5, Tachometer_bss_806D1459(r13)
    cmplwi r5, 0x1
    bne Tachometer_RenderDigits_L_800AB390
    lfs f1, g_tachometer_displaySpeed(r13)
    lfs f0, lbl_806D4E48(r2)
    fmuls f0, f1, f0
    b Tachometer_RenderDigits_L_800AB3A4
    Tachometer_RenderDigits_L_800AB390:
    lfs f2, g_tachometer_displaySpeed(r13)
    lfs f1, lbl_806D4E4C(r2)
    lfs f0, lbl_806D4E48(r2)
    fdivs f1, f2, f1
    fmuls f0, f1, f0
    Tachometer_RenderDigits_L_800AB3A4:
    fctiwz f2, f0
    addi r4, r31, 0x130
    lis r3, 0x6666
    lfs f1, FLOAT_806d1468(r13)
    lfs f0, 0x1c(r4)
    addi r0, r3, 0x6667
    stfd f2, 0x8(r1)
    fadds f2, f1, f0
    lfs f0, FLOAT_806d1474(r13)
    addi r3, r31, 0x310
    lwz r30, 0xc(r1)
    lfs f1, FLOAT_806d146c(r13)
    fsubs f30, f2, f0
    mulhw r0, r0, r30
    lfs f0, 0x20(r4)
    fadds f31, f1, f0
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    subf r0, r0, r30
    slwi r0, r0, 2
    lwzx r0, r3, r0
    cmpwi r0, 0x0
    blt Tachometer_RenderDigits_L_800AB410
    cmpwi r0, 0x26
    blt Tachometer_RenderDigits_L_800AB418
    Tachometer_RenderDigits_L_800AB410:
    li r4, 0x0
    b Tachometer_RenderDigits_L_800AB42C
    Tachometer_RenderDigits_L_800AB418:
    slwi r4, r0, 3
    clrlslwi r0, r5, 24, 2
    addi r3, r31, 0x0
    add r0, r4, r0
    lwzx r4, r3, r0
    Tachometer_RenderDigits_L_800AB42C:
    lis r3, Tachometer_bss_805D3320@ha
    addi r29, r3, Tachometer_bss_805D3320@l
    lwz r3, 0x8(r29)
    bl SpriteLayer_SetResource
    fmr f1, f30
    lwz r3, 0x8(r29)
    fmr f2, f31
    bl fn_8011F804
    lwz r3, 0x8(r29)
    li r4, 0x1
    bl SpriteHandle_SetActiveFlag
    lis r3, 0x6666
    addi r4, r31, 0x130
    addi r6, r3, 0x6667
    lfs f1, FLOAT_806d1468(r13)
    mulhw r0, r6, r30
    lfs f0, 0x10(r4)
    addi r3, r31, 0x310
    lfs f2, FLOAT_806d1474(r13)
    fadds f3, f1, f0
    lfs f1, FLOAT_806d146c(r13)
    srawi r0, r0, 2
    lfs f0, 0x14(r4)
    srwi r4, r0, 31
    fsubs f30, f3, f2
    add r5, r0, r4
    fadds f31, f1, f0
    mulhw r0, r6, r5
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    subf r0, r0, r5
    slwi r0, r0, 2
    lwzx r3, r3, r0
    cmpwi r3, 0x0
    blt Tachometer_RenderDigits_L_800AB4C8
    cmpwi r3, 0x26
    blt Tachometer_RenderDigits_L_800AB4D0
    Tachometer_RenderDigits_L_800AB4C8:
    li r4, 0x0
    b Tachometer_RenderDigits_L_800AB4E8
    Tachometer_RenderDigits_L_800AB4D0:
    lbz r0, Tachometer_bss_806D1459(r13)
    slwi r4, r3, 3
    addi r3, r31, 0x0
    slwi r0, r0, 2
    add r0, r4, r0
    lwzx r4, r3, r0
    Tachometer_RenderDigits_L_800AB4E8:
    lis r3, Tachometer_bss_805D3320@ha
    addi r29, r3, Tachometer_bss_805D3320@l
    lwz r3, 0xc(r29)
    bl SpriteLayer_SetResource
    fmr f1, f30
    lwz r3, 0xc(r29)
    fmr f2, f31
    bl fn_8011F804
    lwz r3, 0xc(r29)
    li r4, 0x1
    bl SpriteHandle_SetActiveFlag
    lis r3, 0x51ec
    addi r6, r31, 0x130
    subi r0, r3, 0x7ae1
    lis r3, 0x6666
    mulhw r4, r0, r30
    lfs f1, FLOAT_806d1468(r13)
    lfs f0, 0x4(r6)
    addi r0, r3, 0x6667
    addi r3, r31, 0x310
    lfs f2, FLOAT_806d1474(r13)
    srawi r4, r4, 5
    fadds f3, f1, f0
    srwi r5, r4, 31
    lfs f1, FLOAT_806d146c(r13)
    add r5, r4, r5
    lfs f0, 0x8(r6)
    mulhw r0, r0, r5
    fsubs f30, f3, f2
    fadds f31, f1, f0
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    subf r0, r0, r5
    slwi r0, r0, 2
    lwzx r3, r3, r0
    cmpwi r3, 0x0
    blt Tachometer_RenderDigits_L_800AB58C
    cmpwi r3, 0x26
    blt Tachometer_RenderDigits_L_800AB594
    Tachometer_RenderDigits_L_800AB58C:
    li r4, 0x0
    b Tachometer_RenderDigits_L_800AB5AC
    Tachometer_RenderDigits_L_800AB594:
    lbz r0, Tachometer_bss_806D1459(r13)
    slwi r4, r3, 3
    addi r3, r31, 0x0
    slwi r0, r0, 2
    add r0, r4, r0
    lwzx r4, r3, r0
    Tachometer_RenderDigits_L_800AB5AC:
    lis r3, Tachometer_bss_805D3320@ha
    addi r30, r3, Tachometer_bss_805D3320@l
    lwz r3, 0x10(r30)
    bl SpriteLayer_SetResource
    fmr f1, f30
    lwz r3, 0x10(r30)
    fmr f2, f31
    bl fn_8011F804
    lwz r3, 0x10(r30)
    li r4, 0x1
    bl SpriteHandle_SetActiveFlag
    lfs f2, lbl_806D4E50(r2)
    lis r3, Tachometer_bss_805D3320@ha
    lfs f0, FLOAT_806d1468(r13)
    addi r3, r3, Tachometer_bss_805D3320@l
    lfs f1, FLOAT_806d1474(r13)
    fadds f3, f2, f0
    lfs f2, lbl_806D4E54(r2)
    lfs f0, FLOAT_806d146c(r13)
    lwz r3, 0x0(r3)
    fsubs f1, f3, f1
    fadds f2, f2, f0
    bl fn_8011F804
    lis r3, Tachometer_bss_805D3320@ha
    li r4, 0x1
    addi r3, r3, Tachometer_bss_805D3320@l
    lwz r3, 0x0(r3)
    bl SpriteHandle_SetActiveFlag
    lfs f2, lbl_806D4E58(r2)
    lis r3, Tachometer_bss_805D3320@ha
    lfs f0, FLOAT_806d1468(r13)
    addi r30, r3, Tachometer_bss_805D3320@l
    lfs f1, FLOAT_806d1474(r13)
    fadds f3, f2, f0
    lfs f2, lbl_806D4E5C(r2)
    lfs f0, FLOAT_806d146c(r13)
    lwz r3, 0x4(r30)
    fsubs f1, f3, f1
    fadds f2, f2, f0
    bl fn_8011F804
    lwz r3, 0x4(r30)
    li r4, 0x1
    bl SpriteHandle_SetActiveFlag
    lis r3, Tachometer_bss_805D3320@ha
    li r30, 0x0
    addi r29, r3, Tachometer_bss_805D3320@l
    Tachometer_RenderDigits_L_800AB664:
    lfs f1, FLOAT_806cf25c(r13)
    lwz r3, 0x0(r29)
    fmr f2, f1
    bl fn_8011F744
    lwz r3, 0x0(r29)
    bl SpriteHandle_RecomputeCull
    addi r30, r30, 0x1
    addi r29, r29, 0x4
    cmpwi r30, 0x5
    blt Tachometer_RenderDigits_L_800AB664
    Tachometer_RenderDigits_L_800AB68C:
    li r3, 0x1
    Tachometer_RenderDigits_L_800AB690:
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    psq_l f30, 0x28(r1), 0, 0
    lfd f30, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r0, 0x44(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
#endif

