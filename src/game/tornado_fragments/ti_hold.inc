/* === extracted from auto_TornadoItem_HoldTick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */

extern void DbgScene_CopyMatrix3x4Transpose();

extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern char *ItemObject_AllocFromPool();
extern void ItemObject_DecrementCategoryBudget();
extern void Item_InitLaunchFromKart();

extern void Matrix4_Identity();
extern void Matrix4_Multiply();
extern void Matrix4_PreMultiplyRotY();
extern void Mtx44_GetTranslation_ColMajor();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetJointVisibilityByName();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_TickAnim();

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D6260;
extern const float lbl_806D6264;
extern const float lbl_806D62AC;
extern const float lbl_806D62B0;
extern const float lbl_806D62B4;
extern const float lbl_806D62B8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern void Tornado_FlightTick();
extern unsigned int fn_800D748C[];
extern unsigned int TornadoItem_HoldTick_rodata_8032FA78[];

/* --- function index (1 fns, .text 0x800F9FD4..0x800FA3D8) ---
 * [  0] 0x800F9FD4 size:0x404   global TornadoItem_HoldTick
 */

/* --- forward decls --- */
#ifdef NON_MATCHING
void TornadoItem_HoldTick(char *self);
#else
void TornadoItem_HoldTick(void);
#endif

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoItem_HoldTick[8] = {
    0x30, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoItem_HoldTick = {
    (void *)&TornadoItem_HoldTick, 0x00000404, (void *)extab_TornadoItem_HoldTick
};

/* --- asm function bodies (.text order = fn address order) --- */
#ifdef NON_MATCHING
/*
 * Equivalent C for the PC port (docs/nonmatching_c.md). Held tornado: three
 * funnel sprites (self+0x148..0x150) spin around the hand joint until the
 * launch flag at self+0x18c is set.
 */
void TornadoItem_HoldTick(char *self)
{
    float handMtx[16];
    float m[16];
    char *sub = self + 0xec;
    char *names = (char *)TornadoItem_HoldTick_rodata_8032FA78;
    char **slot;
    char *shot;
    int i;

    switch (TI_S8(self, 0xc8)) {
    case 0:
        slot = (char **)(sub + 0x5c);
        for (i = 0; i < 3; i++, slot++) {
            *slot = ItemObject_AllocFromPool(fn_800D748C);
            if (*slot != 0) {
                SpriteSlot_InitNonLoop(*slot + 0x14, 0x4f);
                TI_U8(*slot, 0x14) = 4;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(*slot + 0x14, 1);
                switch (i) {
                case 0:
                    SpriteSlot_SetJointVisibilityByName(*slot + 0x14, names + 0x42c, 0x10, 0);
                    SpriteSlot_SetJointVisibilityByName(*slot + 0x14, names + 0x450, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(*slot + 0x14, names + 0x474, 0x10, 1);
                    break;
                case 1:
                    /* the target really addresses slot 0 here and slot 1 in case 2 */
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x5c) + 0x14, names + 0x42c, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x5c) + 0x14, names + 0x450, 0x10, 0);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x5c) + 0x14, names + 0x474, 0x10, 1);
                    break;
                case 2:
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x60) + 0x14, names + 0x42c, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x60) + 0x14, names + 0x450, 0x10, 1);
                    SpriteSlot_SetJointVisibilityByName(TI_PTR(sub, 0x60) + 0x14, names + 0x474, 0x10, 0);
                    break;
                }
                TI_F32(*slot, 0x100) = lbl_806D6264;
            }
        }
        TI_F32(self, 0x2c) = lbl_806D6264;
        TI_U8(self, 0xc8) = 1;
        break;
    case 1:
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(TI_PTR(sub, 0x98)) != 0) {
        TI_U8(self, 0x28) = 0;
    } else {
        TI_U8(self, 0x28) = 1;
    }

    if (TI_S8(sub, 0xa0) != 0) {
        if (TI_S8(sub, 0xa0) == 1) {
            shot = ItemObject_AllocFromPool(Tornado_FlightTick);
            if (shot != 0) {
                TI_U8(shot, 0x1dc) = TI_U8(sub, 0xf0);
                TI_U32(shot, 0x1e0) = TI_U32(sub, 0xf4);
                Mtx44_GetTranslation_RowMajor((float *)(shot + 0xa0), KartDriver_GetJointByIdx(TI_PTR(sub, 0x98), 12));
                Vec3_Copy((float *)(shot + 0x190), (float *)(sub + 0xa4));
                TI_U32(shot, 0x180) = TI_U32(sub, 0x94);
                TI_U32(shot, 0x184) = TI_U32(sub, 0x98);
                Item_InitLaunchFromKart(shot, sub + 0x34, lbl_806D6260, lbl_806D6264);
            }
        }
        slot = (char **)(sub + 0x5c);
        for (i = 0; i < 3; i++, slot++) {
            SpriteSlot_Container_Free(*slot);
            *slot = 0;
        }
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    Mtx44_GetTranslation_RowMajor((float *)(sub + 0x34), KartDriver_GetJointByIdx(TI_PTR(sub, 0x98), 12));
    GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806D6264, lbl_806D6264, lbl_806D62AC);
    Mtx_TransposeToMtx44(handMtx, self + 0x48);
    slot = (char **)(sub + 0x5c);
    for (i = 0; i < 3; i++, slot++) {
        if (*slot == 0) {
            continue;
        }
        switch (i) {
        case 0:
            TI_F32(*slot, 0x100) = BuildOrientationFromYaw(lbl_806D62B0 + TI_F32(*slot, 0x100));
            break;
        case 1:
            TI_F32(*slot, 0x100) = BuildOrientationFromYaw(lbl_806D62B4 + TI_F32(*slot, 0x100));
            break;
        case 2:
            TI_F32(*slot, 0x100) = BuildOrientationFromYaw(lbl_806D62B8 + TI_F32(*slot, 0x100));
            break;
        }
        Matrix4_Identity(m);
        Matrix4_PreMultiplyRotY(m, m, TI_F32(*slot, 0x100));
        Matrix4_Multiply(m, m, handMtx);
        DbgScene_CopyMatrix3x4Transpose(*slot + 0x48, m);
        Mtx44_GetTranslation_ColMajor(*slot + 0xa0, m);
        TI_F32(*slot, 0xc4) = TI_F32(self, 0xc4);
        TI_F32(*slot, 0x2c) = TI_F32(self, 0x2c);
        TI_U8(*slot, 0x28) = TI_U8(self, 0x28);
        SpriteSlot_TickAnim(*slot + 0x14);
    }
}
#else
asm void TornadoItem_HoldTick(void) { /* 0x800F9FD4 size:0x404 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stmw r26, 0x88(r1)
    mr r26, r3
    lis r3, TornadoItem_HoldTick_rodata_8032FA78@ha
    addi r30, r3, TornadoItem_HoldTick_rodata_8032FA78@l
    addi r28, r26, 0xec
    lbz r0, 0xc8(r26)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TornadoItem_HoldTick_L_800FA194
    bge TornadoItem_HoldTick_L_800FA194
    cmpwi r0, 0x0
    bge TornadoItem_HoldTick_L_800FA014
    b TornadoItem_HoldTick_L_800FA194
    TornadoItem_HoldTick_L_800FA014:
    lis r3, fn_800D748C@ha
    mr r29, r28
    addi r31, r3, fn_800D748C@l
    li r27, 0x0
    TornadoItem_HoldTick_L_800FA024:
    mr r3, r31
    bl ItemObject_AllocFromPool
    stw r3, 0x5c(r29)
    lwz r3, 0x5c(r29)
    cmplwi r3, 0x0
    beq TornadoItem_HoldTick_L_800FA174
    addi r3, r3, 0x14
    li r4, 0x4f
    bl SpriteSlot_InitNonLoop
    lwz r3, 0x5c(r29)
    li r0, 0x4
    li r4, 0x1
    stb r0, 0x14(r3)
    lwz r3, 0x5c(r29)
    addi r3, r3, 0x14
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    cmpwi r27, 0x1
    beq TornadoItem_HoldTick_L_800FA0D4
    bge TornadoItem_HoldTick_L_800FA07C
    cmpwi r27, 0x0
    bge TornadoItem_HoldTick_L_800FA088
    b TornadoItem_HoldTick_L_800FA168
    TornadoItem_HoldTick_L_800FA07C:
    cmpwi r27, 0x3
    bge TornadoItem_HoldTick_L_800FA168
    b TornadoItem_HoldTick_L_800FA120
    TornadoItem_HoldTick_L_800FA088:
    lwz r3, 0x5c(r29)
    addi r4, r30, 0x42c
    li r5, 0x10
    li r6, 0x0
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    lwz r3, 0x5c(r29)
    addi r4, r30, 0x450
    li r5, 0x10
    li r6, 0x1
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    lwz r3, 0x5c(r29)
    addi r4, r30, 0x474
    li r5, 0x10
    li r6, 0x1
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    b TornadoItem_HoldTick_L_800FA168
    TornadoItem_HoldTick_L_800FA0D4:
    lwz r3, 0x5c(r28)
    addi r4, r30, 0x42c
    li r5, 0x10
    li r6, 0x1
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    lwz r3, 0x5c(r28)
    addi r4, r30, 0x450
    li r5, 0x10
    li r6, 0x0
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    lwz r3, 0x5c(r28)
    addi r4, r30, 0x474
    li r5, 0x10
    li r6, 0x1
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    b TornadoItem_HoldTick_L_800FA168
    TornadoItem_HoldTick_L_800FA120:
    lwz r3, 0x60(r28)
    addi r4, r30, 0x42c
    li r5, 0x10
    li r6, 0x1
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    lwz r3, 0x60(r28)
    addi r4, r30, 0x450
    li r5, 0x10
    li r6, 0x1
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    lwz r3, 0x60(r28)
    addi r4, r30, 0x474
    li r5, 0x10
    li r6, 0x0
    addi r3, r3, 0x14
    bl SpriteSlot_SetJointVisibilityByName
    TornadoItem_HoldTick_L_800FA168:
    lfs f0, lbl_806D6264(r2)
    lwz r3, 0x5c(r29)
    stfs f0, 0x100(r3)
    TornadoItem_HoldTick_L_800FA174:
    addi r27, r27, 0x1
    addi r29, r29, 0x4
    cmpwi r27, 0x3
    blt TornadoItem_HoldTick_L_800FA024
    lfs f0, lbl_806D6264(r2)
    li r0, 0x1
    stfs f0, 0x2c(r26)
    stb r0, 0xc8(r26)
    TornadoItem_HoldTick_L_800FA194:
    lwz r3, 0x98(r28)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq TornadoItem_HoldTick_L_800FA1B0
    li r0, 0x0
    stb r0, 0x28(r26)
    b TornadoItem_HoldTick_L_800FA1B8
    TornadoItem_HoldTick_L_800FA1B0:
    li r0, 0x1
    stb r0, 0x28(r26)
    TornadoItem_HoldTick_L_800FA1B8:
    lbz r3, 0xa0(r28)
    extsb. r0, r3
    beq TornadoItem_HoldTick_L_800FA274
    extsb r0, r3
    cmpwi r0, 0x1
    bne TornadoItem_HoldTick_L_800FA23C
    lis r3, Tornado_FlightTick@ha
    addi r3, r3, Tornado_FlightTick@l
    bl ItemObject_AllocFromPool
    mr. r27, r3
    beq TornadoItem_HoldTick_L_800FA23C
    lbz r0, 0xf0(r28)
    li r4, 0xc
    stb r0, 0x1dc(r27)
    lwz r0, 0xf4(r28)
    stw r0, 0x1e0(r27)
    lwz r3, 0x98(r28)
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r27, 0xa0
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r27, 0x190
    addi r4, r28, 0xa4
    bl Vec3_Copy
    lwz r0, 0x94(r28)
    mr r3, r27
    lfs f1, lbl_806D6260(r2)
    addi r4, r28, 0x34
    stw r0, 0x180(r27)
    lfs f2, lbl_806D6264(r2)
    lwz r0, 0x98(r28)
    stw r0, 0x184(r27)
    bl Item_InitLaunchFromKart
    TornadoItem_HoldTick_L_800FA23C:
    li r29, 0x0
    mr r27, r29
    TornadoItem_HoldTick_L_800FA244:
    lwz r3, 0x5c(r28)
    bl SpriteSlot_Container_Free
    addi r29, r29, 0x1
    stw r27, 0x5c(r28)
    cmpwi r29, 0x3
    addi r28, r28, 0x4
    blt TornadoItem_HoldTick_L_800FA244
    mr r3, r26
    bl ItemObject_DecrementCategoryBudget
    mr r3, r26
    bl SpriteSlot_Container_Free
    b TornadoItem_HoldTick_L_800FA3C4
    TornadoItem_HoldTick_L_800FA274:
    lwz r3, 0x98(r28)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r28, 0x34
    bl Mtx44_GetTranslation_RowMajor
    lfs f1, lbl_806D6264(r2)
    mr r3, r26
    lfs f3, lbl_806D62AC(r2)
    li r4, 0x1
    fmr f2, f1
    bl GabyouItem_BuildLocalTransformFromHandJoint
    addi r3, r1, 0x48
    addi r4, r26, 0x48
    bl Mtx_TransposeToMtx44
    li r29, 0x0
    mr r27, r28
    TornadoItem_HoldTick_L_800FA2B8:
    lwz r3, 0x5c(r27)
    cmplwi r3, 0x0
    beq TornadoItem_HoldTick_L_800FA3B4
    cmpwi r29, 0x1
    beq TornadoItem_HoldTick_L_800FA304
    bge TornadoItem_HoldTick_L_800FA2DC
    cmpwi r29, 0x0
    bge TornadoItem_HoldTick_L_800FA2E8
    b TornadoItem_HoldTick_L_800FA338
    TornadoItem_HoldTick_L_800FA2DC:
    cmpwi r29, 0x3
    bge TornadoItem_HoldTick_L_800FA338
    b TornadoItem_HoldTick_L_800FA320
    TornadoItem_HoldTick_L_800FA2E8:
    lfs f1, lbl_806D62B0(r2)
    lfs f0, 0x100(r3)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    lwz r3, 0x5c(r27)
    stfs f1, 0x100(r3)
    b TornadoItem_HoldTick_L_800FA338
    TornadoItem_HoldTick_L_800FA304:
    lfs f1, lbl_806D62B4(r2)
    lfs f0, 0x100(r3)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    lwz r3, 0x5c(r27)
    stfs f1, 0x100(r3)
    b TornadoItem_HoldTick_L_800FA338
    TornadoItem_HoldTick_L_800FA320:
    lfs f1, lbl_806D62B8(r2)
    lfs f0, 0x100(r3)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    lwz r3, 0x5c(r27)
    stfs f1, 0x100(r3)
    TornadoItem_HoldTick_L_800FA338:
    addi r3, r1, 0x8
    bl Matrix4_Identity
    lwz r5, 0x5c(r27)
    addi r3, r1, 0x8
    mr r4, r3
    lfs f1, 0x100(r5)
    bl Matrix4_PreMultiplyRotY
    addi r3, r1, 0x8
    addi r5, r1, 0x48
    mr r4, r3
    bl Matrix4_Multiply
    lwz r3, 0x5c(r27)
    addi r4, r1, 0x8
    addi r3, r3, 0x48
    bl DbgScene_CopyMatrix3x4Transpose
    lwz r3, 0x5c(r27)
    addi r4, r1, 0x8
    addi r3, r3, 0xa0
    bl Mtx44_GetTranslation_ColMajor
    lfs f0, 0xc4(r26)
    lwz r3, 0x5c(r27)
    stfs f0, 0xc4(r3)
    lfs f0, 0x2c(r26)
    lwz r3, 0x5c(r27)
    stfs f0, 0x2c(r3)
    lbz r0, 0x28(r26)
    lwz r3, 0x5c(r27)
    stb r0, 0x28(r3)
    lwz r3, 0x5c(r27)
    addi r3, r3, 0x14
    bl SpriteSlot_TickAnim
    TornadoItem_HoldTick_L_800FA3B4:
    addi r29, r29, 0x1
    addi r27, r27, 0x4
    cmpwi r29, 0x3
    blt TornadoItem_HoldTick_L_800FA2B8
    TornadoItem_HoldTick_L_800FA3C4:
    lmw r26, 0x88(r1)
    lwz r0, 0xa4(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}
#endif

