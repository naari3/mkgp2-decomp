/* === extracted from auto_KartFx_MasterTick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_SpawnDirect();
extern void KartDriver_GetKartRootMtx();
extern void KartFx_DispatchByStateBits();
extern void KartFx_DispatchGroupA();
extern void KartFx_DispatchGroupB_AuxStarBurst();
extern void KartFx_DispatchGroupD_RingBurst();
extern void KartFx_DispatchGroupE_StateByte();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_Inverse_GaussJordan();
extern void Mtx44_TransformVec3();
extern void Vec3_Copy();
extern void Vec3_Magnitude_Wrapper();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D51C0;
extern unsigned int lbl_806D51C4;
extern unsigned int lbl_806D51CC;
extern unsigned int lbl_806D51D4;
extern unsigned int lbl_806D51DC;
extern unsigned int lbl_806D51E0;
extern unsigned int lbl_806D51E4;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int KartFx_BoostChargeIconTick[];
extern unsigned int KartFx_DriftSparkParticleTick[];
extern unsigned int lbl_805DF3D0[];

/* --- function index (1 fns, .text 0x800B510C..0x800B53BC) ---
 * [  0] 0x800B510C size:0x2B0   global KartFx_MasterTick
 */

/* --- forward decls --- */
asm void KartFx_MasterTick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartFx_MasterTick[8] = {
    0x28, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartFx_MasterTick = {
    (void *)&KartFx_MasterTick, 0x000002B0, (void *)extab_KartFx_MasterTick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartFx_MasterTick(void) { /* 0x800B510C size:0x2B0 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stmw r27, 0x5c(r1)
    mr r29, r3
    lbz r0, 0xb4(r3)
    addi r31, r29, 0xcc
    extsb r0, r0
    cmpwi r0, 0x1
    beq KartFx_MasterTick_L_800B517C
    bge KartFx_MasterTick_L_800B53A0
    cmpwi r0, 0x0
    bge KartFx_MasterTick_L_800B514C
    b KartFx_MasterTick_L_800B53A0
    KartFx_MasterTick_L_800B514C:
    lwz r3, 0x0(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r31, 0xc
    bl Mtx44_GetTranslation_RowMajor
    li r0, 0x0
    stb r0, 0x8(r31)
    stb r0, 0x9(r31)
    lbz r3, 0xb4(r29)
    addi r0, r3, 0x1
    stb r0, 0xb4(r29)
    b KartFx_MasterTick_L_800B53A0
    KartFx_MasterTick_L_800B517C:
    lwz r3, 0x0(r31)
    lwz r30, 0x304(r3)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r29, 0x8c
    bl Mtx44_GetTranslation_RowMajor
    lis r4, lbl_805DF3D0@ha
    addi r3, r1, 0x14
    addi r4, r4, lbl_805DF3D0@l
    bl Mtx44_Inverse_GaussJordan
    lwz r6, 0x8c(r29)
    addi r3, r31, 0x28
    lwz r0, 0x90(r29)
    addi r4, r1, 0x14
    addi r5, r1, 0x8
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0x94(r29)
    stw r0, 0x10(r1)
    bl Mtx44_TransformVec3
    addi r3, r31, 0x28
    bl Vec3_Magnitude_Wrapper
    stfs f1, 0x34(r31)
    addi r3, r31, 0x18
    addi r4, r29, 0x8c
    addi r5, r31, 0xc
    bl Vec3_Subtract_DestFirst
    addi r3, r31, 0x18
    bl Vec3_Magnitude_Wrapper
    stfs f1, 0x24(r31)
    lfs f1, lbl_806D51DC(r2)
    lfs f0, 0x24(r31)
    fcmpo cr0, f1, f0
    bge KartFx_MasterTick_L_800B5208
    stfs f1, 0x24(r31)
    KartFx_MasterTick_L_800B5208:
    addi r3, r31, 0xc
    addi r4, r29, 0x8c
    bl Vec3_Copy
    lbz r0, 0x8(r31)
    extsb. r0, r0
    beq KartFx_MasterTick_L_800B522C
    lbz r0, 0x9(r31)
    extsb. r0, r0
    bne KartFx_MasterTick_L_800B5234
    KartFx_MasterTick_L_800B522C:
    lfs f0, lbl_806D51C0(r2)
    stfs f0, 0x3c(r31)
    KartFx_MasterTick_L_800B5234:
    lfs f1, 0x28(r30)
    lfs f0, lbl_806D51C0(r2)
    fcmpu cr0, f1, f0
    beq KartFx_MasterTick_L_800B5248
    stfs f0, 0x3c(r31)
    KartFx_MasterTick_L_800B5248:
    lfs f1, lbl_806D51E0(r2)
    li r27, 0x1
    lfs f0, 0x34(r31)
    fcmpo cr0, f1, f0
    bge KartFx_MasterTick_L_800B5260
    li r27, 0x0
    KartFx_MasterTick_L_800B5260:
    lfs f1, 0x30(r31)
    lfs f0, lbl_806D51E4(r2)
    fcmpo cr0, f1, f0
    bge KartFx_MasterTick_L_800B5274
    li r27, 0x0
    KartFx_MasterTick_L_800B5274:
    cmpwi r27, 0x0
    beq KartFx_MasterTick_L_800B52B0
    lwz r4, 0x0(r31)
    lbz r0, 0x348(r4)
    cmplwi r0, 0x0
    beq KartFx_MasterTick_L_800B52B0
    li r0, 0x0
    lis r3, KartFx_BoostChargeIconTick@ha
    stb r0, 0x348(r4)
    addi r3, r3, KartFx_BoostChargeIconTick@l
    bl DrawEffect_SpawnDirect
    cmplwi r3, 0x0
    beq KartFx_MasterTick_L_800B52B0
    lwz r0, 0x0(r31)
    stw r0, 0x11c(r3)
    KartFx_MasterTick_L_800B52B0:
    lfs f0, lbl_806D51CC(r2)
    lfs f2, 0x24(r31)
    fcmpo cr0, f0, f2
    bge KartFx_MasterTick_L_800B5334
    lbz r0, 0x40(r31)
    extsb. r0, r0
    beq KartFx_MasterTick_L_800B5334
    lwz r3, 0x0(r31)
    lwz r0, 0x238(r3)
    cmpwi r0, 0x0
    beq KartFx_MasterTick_L_800B533C
    lfs f1, lbl_806D51D4(r2)
    lis r3, KartFx_DriftSparkParticleTick@ha
    lfs f0, 0x48(r31)
    addi r28, r3, KartFx_DriftSparkParticleTick@l
    lfs f31, lbl_806D51C4(r2)
    fmadds f0, f1, f2, f0
    stfs f0, 0x48(r31)
    b KartFx_MasterTick_L_800B5320
    KartFx_MasterTick_L_800B52FC:
    lfs f0, 0x48(r31)
    mr r3, r28
    fsubs f0, f0, f31
    stfs f0, 0x48(r31)
    bl DrawEffect_SpawnDirect
    cmplwi r3, 0x0
    beq KartFx_MasterTick_L_800B5320
    lwz r0, 0x0(r31)
    stw r0, 0x11c(r3)
    KartFx_MasterTick_L_800B5320:
    lfs f0, 0x48(r31)
    fcmpo cr0, f31, f0
    cror eq, lt, eq
    beq KartFx_MasterTick_L_800B52FC
    b KartFx_MasterTick_L_800B533C
    KartFx_MasterTick_L_800B5334:
    lfs f0, lbl_806D51C0(r2)
    stfs f0, 0x48(r31)
    KartFx_MasterTick_L_800B533C:
    mr r3, r29
    mr r4, r31
    mr r5, r30
    mr r6, r27
    bl KartFx_DispatchGroupA
    mr r3, r29
    mr r4, r31
    mr r5, r30
    mr r6, r27
    bl KartFx_DispatchGroupB_AuxStarBurst
    mr r3, r29
    mr r4, r31
    mr r5, r30
    mr r6, r27
    bl KartFx_DispatchByStateBits
    mr r3, r29
    mr r4, r31
    mr r5, r30
    mr r6, r27
    bl KartFx_DispatchGroupD_RingBurst
    mr r3, r29
    mr r4, r31
    mr r5, r30
    mr r6, r27
    bl KartFx_DispatchGroupE_StateByte
    KartFx_MasterTick_L_800B53A0:
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    lmw r27, 0x5c(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}
