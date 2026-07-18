
/*
 * HeartCompoundItem @ 0x800F2620..0x800F2D60 (unit-claim #23).
 *
 * Exact asm_fn park for the complete three-member unit. The target contains
 * exception metadata for each member; the orchestrator must apply the single
 * TU split and emit the corresponding extab/extabindex entries before build.
 */

asm void HeartCompoundItem_TickReleasePhase(void);
asm void HeartCompoundItem_TickCarryPhase(void);
asm void HeartCompoundItem_Update(void);

/* Inline asm branch targets must be declared for mwcceppc's assembler pass. */
extern void BuildOrientationFromYaw();
extern void DrawEffect_SpawnDirect();
extern void Effect_CompoundRing_PlaceChildren();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void fn_8027E9E8();
extern void GetRaceContextPtr();
extern void Item_DecayVelocityScalar();
extern void Item_RenderHandheldByCharacter();
extern void ItemObject_DispatchVtable18_GetState();
extern void JointByName_GetLocalMatrix4x3();
extern void KartDriver_GetKartRootMtx();
extern void KartMovement_GetCurrentItemId();
extern void Mtx_TransposeToMtx44();
extern void Mtx44_GetYawOfPosZ();
extern void Mtx44_GetYawOfPosZ_Padded();
extern void Mtx44_Inverse_GaussJordan();
extern void Mtx44_TransformVec3();
extern void RaceContextSlot_GetIfAlive();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_SetTransform();
extern void SpriteSlot_TickAnim();

/* Manual exception metadata. postprocess_extab_user.py renames these
 * .extab_user/.extabindex_user sections and symbols after compilation. */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_HeartCompoundItem_TickReleasePhase[8] =
    { 0x40, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__declspec(section ".extab_user") static const unsigned char extab_HeartCompoundItem_TickCarryPhase[8] =
    { 0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__declspec(section ".extab_user") static const unsigned char extab_HeartCompoundItem_Update[8] =
    { 0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_HeartCompoundItem_TickReleasePhase = {
    (void *)&HeartCompoundItem_TickReleasePhase, 0x000002F0,
    (void *)extab_HeartCompoundItem_TickReleasePhase
};
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_HeartCompoundItem_TickCarryPhase = {
    (void *)&HeartCompoundItem_TickCarryPhase, 0x00000244,
    (void *)extab_HeartCompoundItem_TickCarryPhase
};
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_HeartCompoundItem_Update = {
    (void *)&HeartCompoundItem_Update, 0x0000020C,
    (void *)extab_HeartCompoundItem_Update
};

asm void HeartCompoundItem_TickReleasePhase(void) { /* 0x800F2620 size:0x2F0 */
    nofralloc
    stwu r1,-0xa0(r1)
    HeartCompoundItem_TickReleasePhase_L_800F2624:
    mflr r0
    HeartCompoundItem_TickReleasePhase_L_800F2628:
    stw r0,0xa4(r1)
    HeartCompoundItem_TickReleasePhase_L_800F262C:
    stfd f31,0x90(r1)
    HeartCompoundItem_TickReleasePhase_L_800F2630:
    psq_st f31,0x98(r1), 0, 0
    HeartCompoundItem_TickReleasePhase_L_800F2634:
    stfd f30,0x80(r1)
    HeartCompoundItem_TickReleasePhase_L_800F2638:
    psq_st f30,0x88(r1), 0, 0
    HeartCompoundItem_TickReleasePhase_L_800F263C:
    stmw r24,0x60(r1)
    HeartCompoundItem_TickReleasePhase_L_800F2640:
    or r30,r3,r3
    HeartCompoundItem_TickReleasePhase_L_800F2644:
    or r31,r4,r4
    HeartCompoundItem_TickReleasePhase_L_800F2648:
    lbz r0,0xca(r3)
    HeartCompoundItem_TickReleasePhase_L_800F264C:
    extsb r0,r0
    HeartCompoundItem_TickReleasePhase_L_800F2650:
    cmpwi r0,0x1
    HeartCompoundItem_TickReleasePhase_L_800F2654:
    beq HeartCompoundItem_TickReleasePhase_L_800F2758
    HeartCompoundItem_TickReleasePhase_L_800F2658:
    bge HeartCompoundItem_TickReleasePhase_L_800F27D0
    HeartCompoundItem_TickReleasePhase_L_800F265C:
    cmpwi r0,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2660:
    bge HeartCompoundItem_TickReleasePhase_L_800F266C
    HeartCompoundItem_TickReleasePhase_L_800F2664:
    b HeartCompoundItem_TickReleasePhase_L_800F27D0
    HeartCompoundItem_TickReleasePhase_L_800F2668:
    b HeartCompoundItem_TickReleasePhase_L_800F27D0
    HeartCompoundItem_TickReleasePhase_L_800F266C:
    lfs f0,-0x4200(r2)
    HeartCompoundItem_TickReleasePhase_L_800F2670:
    li r3,0xa
    HeartCompoundItem_TickReleasePhase_L_800F2674:
    li r0,0x14
    HeartCompoundItem_TickReleasePhase_L_800F2678:
    stfs f0,0xbc(r30)
    HeartCompoundItem_TickReleasePhase_L_800F267C:
    stfs f0,0x14(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2680:
    stfs f0,0x18(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2684:
    stw r3,0x4(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2688:
    stw r0,0x8(r31)
    HeartCompoundItem_TickReleasePhase_L_800F268C:
    lwz r3,0x4c(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2690:
    cmplwi r3,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2694:
    beq HeartCompoundItem_TickReleasePhase_L_800F26A0
    HeartCompoundItem_TickReleasePhase_L_800F2698:
    li r0,0x1
    HeartCompoundItem_TickReleasePhase_L_800F269C:
    stb r0,0x190(r3)
    HeartCompoundItem_TickReleasePhase_L_800F26A0:
    li r26,0x0
    HeartCompoundItem_TickReleasePhase_L_800F26A4:
    bl GetRaceContextPtr
    HeartCompoundItem_TickReleasePhase_L_800F26A8:
    or r4,r26,r26
    HeartCompoundItem_TickReleasePhase_L_800F26AC:
    bl RaceContextSlot_GetIfAlive
    HeartCompoundItem_TickReleasePhase_L_800F26B0:
    cmplwi r3,0x0
    HeartCompoundItem_TickReleasePhase_L_800F26B4:
    beq HeartCompoundItem_TickReleasePhase_L_800F2740
    HeartCompoundItem_TickReleasePhase_L_800F26B8:
    lwz r0,0x0(r3)
    HeartCompoundItem_TickReleasePhase_L_800F26BC:
    cmplwi r0,0x3
    HeartCompoundItem_TickReleasePhase_L_800F26C0:
    ble HeartCompoundItem_TickReleasePhase_L_800F26CC
    HeartCompoundItem_TickReleasePhase_L_800F26C4:
    cmpwi r0,0x6
    HeartCompoundItem_TickReleasePhase_L_800F26C8:
    bne HeartCompoundItem_TickReleasePhase_L_800F2740
    HeartCompoundItem_TickReleasePhase_L_800F26CC:
    lwz r25,0xb4(r3)
    HeartCompoundItem_TickReleasePhase_L_800F26D0:
    lwz r0,0x98(r31)
    HeartCompoundItem_TickReleasePhase_L_800F26D4:
    cmplw r0,r25
    HeartCompoundItem_TickReleasePhase_L_800F26D8:
    beq HeartCompoundItem_TickReleasePhase_L_800F2740
    HeartCompoundItem_TickReleasePhase_L_800F26DC:
    or r3,r25,r25
    HeartCompoundItem_TickReleasePhase_L_800F26E0:
    bl KartMovement_GetCurrentItemId
    HeartCompoundItem_TickReleasePhase_L_800F26E4:
    cmpwi r3,-0x1
    HeartCompoundItem_TickReleasePhase_L_800F26E8:
    beq HeartCompoundItem_TickReleasePhase_L_800F2740
    HeartCompoundItem_TickReleasePhase_L_800F26EC:
    lis r3,-0x7ff4
    HeartCompoundItem_TickReleasePhase_L_800F26F0:
    lfs f30,-0x41fc(r2)
    HeartCompoundItem_TickReleasePhase_L_800F26F4:
    lfd f31,-0x41e8(r2)
    HeartCompoundItem_TickReleasePhase_L_800F26F8:
    addi r27,r3,0x3cc8
    HeartCompoundItem_TickReleasePhase_L_800F26FC:
    li r24,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2700:
    lis r28,0x4330
    HeartCompoundItem_TickReleasePhase_L_800F2704:
    li r29,0x28
    HeartCompoundItem_TickReleasePhase_L_800F2708:
    or r3,r27,r27
    HeartCompoundItem_TickReleasePhase_L_800F270C:
    bl DrawEffect_SpawnDirect
    HeartCompoundItem_TickReleasePhase_L_800F2710:
    xoris r0,r24,0x8000
    HeartCompoundItem_TickReleasePhase_L_800F2714:
    addi r24,r24,0x1
    HeartCompoundItem_TickReleasePhase_L_800F2718:
    stw r0,0x5c(r1)
    HeartCompoundItem_TickReleasePhase_L_800F271C:
    cmpwi r24,0x6
    HeartCompoundItem_TickReleasePhase_L_800F2720:
    stw r28,0x58(r1)
    HeartCompoundItem_TickReleasePhase_L_800F2724:
    lfd f0,0x58(r1)
    HeartCompoundItem_TickReleasePhase_L_800F2728:
    fsubs f0,f0,f31
    HeartCompoundItem_TickReleasePhase_L_800F272C:
    fmuls f0,f30,f0
    HeartCompoundItem_TickReleasePhase_L_800F2730:
    stfs f0,0x150(r3)
    HeartCompoundItem_TickReleasePhase_L_800F2734:
    stw r29,0x180(r3)
    HeartCompoundItem_TickReleasePhase_L_800F2738:
    stw r25,0x11c(r3)
    HeartCompoundItem_TickReleasePhase_L_800F273C:
    blt HeartCompoundItem_TickReleasePhase_L_800F2708
    HeartCompoundItem_TickReleasePhase_L_800F2740:
    addi r26,r26,0x1
    HeartCompoundItem_TickReleasePhase_L_800F2744:
    cmpwi r26,0x80
    HeartCompoundItem_TickReleasePhase_L_800F2748:
    blt HeartCompoundItem_TickReleasePhase_L_800F26A4
    HeartCompoundItem_TickReleasePhase_L_800F274C:
    lbz r3,0xca(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2750:
    addi r0,r3,0x1
    HeartCompoundItem_TickReleasePhase_L_800F2754:
    stb r0,0xca(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2758:
    lwz r0,0x8(r31)
    HeartCompoundItem_TickReleasePhase_L_800F275C:
    cmplwi r0,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2760:
    bne HeartCompoundItem_TickReleasePhase_L_800F27D0
    HeartCompoundItem_TickReleasePhase_L_800F2764:
    li r27,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2768:
    bl GetRaceContextPtr
    HeartCompoundItem_TickReleasePhase_L_800F276C:
    or r4,r27,r27
    HeartCompoundItem_TickReleasePhase_L_800F2770:
    bl RaceContextSlot_GetIfAlive
    HeartCompoundItem_TickReleasePhase_L_800F2774:
    cmplwi r3,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2778:
    beq HeartCompoundItem_TickReleasePhase_L_800F27B8
    HeartCompoundItem_TickReleasePhase_L_800F277C:
    lwz r0,0x0(r3)
    HeartCompoundItem_TickReleasePhase_L_800F2780:
    cmplwi r0,0x3
    HeartCompoundItem_TickReleasePhase_L_800F2784:
    ble HeartCompoundItem_TickReleasePhase_L_800F2790
    HeartCompoundItem_TickReleasePhase_L_800F2788:
    cmpwi r0,0x6
    HeartCompoundItem_TickReleasePhase_L_800F278C:
    bne HeartCompoundItem_TickReleasePhase_L_800F27B8
    HeartCompoundItem_TickReleasePhase_L_800F2790:
    lwz r24,0xb4(r3)
    HeartCompoundItem_TickReleasePhase_L_800F2794:
    lwz r0,0x98(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2798:
    cmplw r0,r24
    HeartCompoundItem_TickReleasePhase_L_800F279C:
    beq HeartCompoundItem_TickReleasePhase_L_800F27B8
    HeartCompoundItem_TickReleasePhase_L_800F27A0:
    or r3,r24,r24
    HeartCompoundItem_TickReleasePhase_L_800F27A4:
    bl KartMovement_GetCurrentItemId
    HeartCompoundItem_TickReleasePhase_L_800F27A8:
    cmpwi r3,-0x1
    HeartCompoundItem_TickReleasePhase_L_800F27AC:
    beq HeartCompoundItem_TickReleasePhase_L_800F27B8
    HeartCompoundItem_TickReleasePhase_L_800F27B0:
    or r3,r24,r24
    HeartCompoundItem_TickReleasePhase_L_800F27B4:
    bl ItemObject_DispatchVtable18_GetState
    HeartCompoundItem_TickReleasePhase_L_800F27B8:
    addi r27,r27,0x1
    HeartCompoundItem_TickReleasePhase_L_800F27BC:
    cmpwi r27,0x80
    HeartCompoundItem_TickReleasePhase_L_800F27C0:
    blt HeartCompoundItem_TickReleasePhase_L_800F2768
    HeartCompoundItem_TickReleasePhase_L_800F27C4:
    lbz r3,0xca(r30)
    HeartCompoundItem_TickReleasePhase_L_800F27C8:
    addi r0,r3,0x1
    HeartCompoundItem_TickReleasePhase_L_800F27CC:
    stb r0,0xca(r30)
    HeartCompoundItem_TickReleasePhase_L_800F27D0:
    lwz r3,0x98(r31)
    HeartCompoundItem_TickReleasePhase_L_800F27D4:
    bl FinalLapCoinJump_CheckActiveForObject
    HeartCompoundItem_TickReleasePhase_L_800F27D8:
    rlwinm. r0,r3,0x0,0x18,0x1f
    HeartCompoundItem_TickReleasePhase_L_800F27DC:
    beq HeartCompoundItem_TickReleasePhase_L_800F27EC
    HeartCompoundItem_TickReleasePhase_L_800F27E0:
    li r0,0x0
    HeartCompoundItem_TickReleasePhase_L_800F27E4:
    stb r0,0x28(r30)
    HeartCompoundItem_TickReleasePhase_L_800F27E8:
    b HeartCompoundItem_TickReleasePhase_L_800F27F4
    HeartCompoundItem_TickReleasePhase_L_800F27EC:
    li r0,0x1
    HeartCompoundItem_TickReleasePhase_L_800F27F0:
    stb r0,0x28(r30)
    HeartCompoundItem_TickReleasePhase_L_800F27F4:
    lwz r0,0x4(r31)
    HeartCompoundItem_TickReleasePhase_L_800F27F8:
    cmplwi r0,0x0
    HeartCompoundItem_TickReleasePhase_L_800F27FC:
    bne HeartCompoundItem_TickReleasePhase_L_800F2810
    HeartCompoundItem_TickReleasePhase_L_800F2800:
    lfs f1,0xbc(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2804:
    lfs f0,-0x41f8(r2)
    HeartCompoundItem_TickReleasePhase_L_800F2808:
    fadds f0,f1,f0
    HeartCompoundItem_TickReleasePhase_L_800F280C:
    stfs f0,0xbc(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2810:
    lfs f2,0x14(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2814:
    lfs f1,0xbc(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2818:
    lfs f0,-0x41f4(r2)
    HeartCompoundItem_TickReleasePhase_L_800F281C:
    fadds f1,f2,f1
    HeartCompoundItem_TickReleasePhase_L_800F2820:
    stfs f1,0x14(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2824:
    lfs f1,0x18(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2828:
    fadds f0,f1,f0
    HeartCompoundItem_TickReleasePhase_L_800F282C:
    stfs f0,0x18(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2830:
    lwz r0,0x8(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2834:
    cmplwi r0,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2838:
    bne HeartCompoundItem_TickReleasePhase_L_800F2874
    HeartCompoundItem_TickReleasePhase_L_800F283C:
    lfs f2,0x2c(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2840:
    lfs f1,-0x41f0(r2)
    HeartCompoundItem_TickReleasePhase_L_800F2844:
    lfs f0,-0x4200(r2)
    HeartCompoundItem_TickReleasePhase_L_800F2848:
    fsubs f1,f2,f1
    HeartCompoundItem_TickReleasePhase_L_800F284C:
    stfs f1,0x2c(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2850:
    lfs f1,0x2c(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2854:
    fcmpo cr0,f1,f0
    HeartCompoundItem_TickReleasePhase_L_800F2858:
    bge HeartCompoundItem_TickReleasePhase_L_800F2874
    HeartCompoundItem_TickReleasePhase_L_800F285C:
    li r3,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2860:
    li r0,0x3
    HeartCompoundItem_TickReleasePhase_L_800F2864:
    stb r3,0x28(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2868:
    stb r0,0xc8(r30)
    HeartCompoundItem_TickReleasePhase_L_800F286C:
    stb r3,0xc9(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2870:
    b HeartCompoundItem_TickReleasePhase_L_800F28EC
    HeartCompoundItem_TickReleasePhase_L_800F2874:
    lfs f1,-0x41ec(r2)
    HeartCompoundItem_TickReleasePhase_L_800F2878:
    or r3,r30,r30
    HeartCompoundItem_TickReleasePhase_L_800F287C:
    bl Item_DecayVelocityScalar
    HeartCompoundItem_TickReleasePhase_L_800F2880:
    lwz r3,0x98(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2884:
    cmplwi r3,0x0
    HeartCompoundItem_TickReleasePhase_L_800F2888:
    beq HeartCompoundItem_TickReleasePhase_L_800F28EC
    HeartCompoundItem_TickReleasePhase_L_800F288C:
    bl KartDriver_GetKartRootMtx
    HeartCompoundItem_TickReleasePhase_L_800F2890:
    or r4,r3,r3
    HeartCompoundItem_TickReleasePhase_L_800F2894:
    addi r3,r1,0x14
    HeartCompoundItem_TickReleasePhase_L_800F2898:
    bl Mtx_TransposeToMtx44
    HeartCompoundItem_TickReleasePhase_L_800F289C:
    lwz r6,0x34(r31)
    HeartCompoundItem_TickReleasePhase_L_800F28A0:
    addi r3,r30,0xa0
    HeartCompoundItem_TickReleasePhase_L_800F28A4:
    lwz r0,0x38(r31)
    HeartCompoundItem_TickReleasePhase_L_800F28A8:
    addi r4,r1,0x14
    HeartCompoundItem_TickReleasePhase_L_800F28AC:
    addi r5,r1,0x8
    HeartCompoundItem_TickReleasePhase_L_800F28B0:
    stw r6,0x8(r1)
    HeartCompoundItem_TickReleasePhase_L_800F28B4:
    stw r0,0xc(r1)
    HeartCompoundItem_TickReleasePhase_L_800F28B8:
    lwz r0,0x3c(r31)
    HeartCompoundItem_TickReleasePhase_L_800F28BC:
    stw r0,0x10(r1)
    HeartCompoundItem_TickReleasePhase_L_800F28C0:
    bl Mtx44_TransformVec3
    HeartCompoundItem_TickReleasePhase_L_800F28C4:
    lfs f1,0xa4(r30)
    HeartCompoundItem_TickReleasePhase_L_800F28C8:
    addi r3,r1,0x14
    HeartCompoundItem_TickReleasePhase_L_800F28CC:
    lfs f0,0x14(r31)
    HeartCompoundItem_TickReleasePhase_L_800F28D0:
    fadds f0,f1,f0
    HeartCompoundItem_TickReleasePhase_L_800F28D4:
    stfs f0,0xa4(r30)
    HeartCompoundItem_TickReleasePhase_L_800F28D8:
    bl Mtx44_GetYawOfPosZ
    HeartCompoundItem_TickReleasePhase_L_800F28DC:
    lfs f0,0x18(r31)
    HeartCompoundItem_TickReleasePhase_L_800F28E0:
    fadds f1,f0,f1
    HeartCompoundItem_TickReleasePhase_L_800F28E4:
    bl BuildOrientationFromYaw
    HeartCompoundItem_TickReleasePhase_L_800F28E8:
    stfs f1,0xb0(r30)
    HeartCompoundItem_TickReleasePhase_L_800F28EC:
    psq_l f31,0x98(r1), 0, 0
    HeartCompoundItem_TickReleasePhase_L_800F28F0:
    lfd f31,0x90(r1)
    HeartCompoundItem_TickReleasePhase_L_800F28F4:
    psq_l f30,0x88(r1), 0, 0
    HeartCompoundItem_TickReleasePhase_L_800F28F8:
    lfd f30,0x80(r1)
    HeartCompoundItem_TickReleasePhase_L_800F28FC:
    lmw r24,0x60(r1)
    HeartCompoundItem_TickReleasePhase_L_800F2900:
    lwz r0,0xa4(r1)
    HeartCompoundItem_TickReleasePhase_L_800F2904:
    mtlr r0
    HeartCompoundItem_TickReleasePhase_L_800F2908:
    addi r1,r1,0xa0
    HeartCompoundItem_TickReleasePhase_L_800F290C:
    blr
}

asm void HeartCompoundItem_TickCarryPhase(void) { /* 0x800F2910 size:0x244 */
    nofralloc
    stwu r1,-0x90(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2914:
    mflr r0
    HeartCompoundItem_TickCarryPhase_L_800F2918:
    stw r0,0x94(r1)
    HeartCompoundItem_TickCarryPhase_L_800F291C:
    stw r31,0x8c(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2920:
    or r31,r4,r4
    HeartCompoundItem_TickCarryPhase_L_800F2924:
    stw r30,0x88(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2928:
    or r30,r3,r3
    HeartCompoundItem_TickCarryPhase_L_800F292C:
    lbz r0,0xca(r3)
    HeartCompoundItem_TickCarryPhase_L_800F2930:
    extsb r0,r0
    HeartCompoundItem_TickCarryPhase_L_800F2934:
    cmpwi r0,0x1
    HeartCompoundItem_TickCarryPhase_L_800F2938:
    beq HeartCompoundItem_TickCarryPhase_L_800F2978
    HeartCompoundItem_TickCarryPhase_L_800F293C:
    bge HeartCompoundItem_TickCarryPhase_L_800F2B3C
    HeartCompoundItem_TickCarryPhase_L_800F2940:
    cmpwi r0,0x0
    HeartCompoundItem_TickCarryPhase_L_800F2944:
    bge HeartCompoundItem_TickCarryPhase_L_800F294C
    HeartCompoundItem_TickCarryPhase_L_800F2948:
    b HeartCompoundItem_TickCarryPhase_L_800F2B3C
    HeartCompoundItem_TickCarryPhase_L_800F294C:
    addi r3,r30,0x14
    HeartCompoundItem_TickCarryPhase_L_800F2950:
    li r4,0x1
    HeartCompoundItem_TickCarryPhase_L_800F2954:
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    HeartCompoundItem_TickCarryPhase_L_800F2958:
    li r0,0x1
    HeartCompoundItem_TickCarryPhase_L_800F295C:
    lfs f0,-0x4200(r2)
    HeartCompoundItem_TickCarryPhase_L_800F2960:
    stb r0,0x28(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2964:
    stfs f0,0x2c(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2968:
    stfs f0,0x14(r31)
    HeartCompoundItem_TickCarryPhase_L_800F296C:
    lbz r3,0xca(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2970:
    addi r0,r3,0x1
    HeartCompoundItem_TickCarryPhase_L_800F2974:
    stb r0,0xca(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2978:
    lfs f1,0x14(r31)
    HeartCompoundItem_TickCarryPhase_L_800F297C:
    lfs f0,-0x7950(r13)
    HeartCompoundItem_TickCarryPhase_L_800F2980:
    fadds f1,f1,f0
    HeartCompoundItem_TickCarryPhase_L_800F2984:
    bl BuildOrientationFromYaw
    HeartCompoundItem_TickCarryPhase_L_800F2988:
    stfs f1,0x14(r31)
    HeartCompoundItem_TickCarryPhase_L_800F298C:
    lis r3,-0x7fbe
    HeartCompoundItem_TickCarryPhase_L_800F2990:
    lfsu f1,0x1704(r3)
    HeartCompoundItem_TickCarryPhase_L_800F2994:
    lfs f0,0x4(r3)
    HeartCompoundItem_TickCarryPhase_L_800F2998:
    stfs f1,0x38(r1)
    HeartCompoundItem_TickCarryPhase_L_800F299C:
    lfs f1,0x14(r31)
    HeartCompoundItem_TickCarryPhase_L_800F29A0:
    stfs f0,0x3c(r1)
    HeartCompoundItem_TickCarryPhase_L_800F29A4:
    bl fn_8027E9E8
    HeartCompoundItem_TickCarryPhase_L_800F29A8:
    lis r4,-0x7fbe
    HeartCompoundItem_TickCarryPhase_L_800F29AC:
    frsp f3,f1
    HeartCompoundItem_TickCarryPhase_L_800F29B0:
    addi r4,r4,0x1704
    HeartCompoundItem_TickCarryPhase_L_800F29B4:
    lfs f2,-0x794c(r13)
    HeartCompoundItem_TickCarryPhase_L_800F29B8:
    lfs f0,0x8(r4)
    HeartCompoundItem_TickCarryPhase_L_800F29BC:
    lis r3,-0x7fbe
    HeartCompoundItem_TickCarryPhase_L_800F29C0:
    lfs f1,-0x41e0(r2)
    HeartCompoundItem_TickCarryPhase_L_800F29C4:
    fmadds f3,f2,f3,f0
    HeartCompoundItem_TickCarryPhase_L_800F29C8:
    lfs f0,0x14(r31)
    HeartCompoundItem_TickCarryPhase_L_800F29CC:
    lfs f2,0x16f8(r3)
    HeartCompoundItem_TickCarryPhase_L_800F29D0:
    fmuls f1,f1,f0
    HeartCompoundItem_TickCarryPhase_L_800F29D4:
    stfs f3,0x40(r1)
    HeartCompoundItem_TickCarryPhase_L_800F29D8:
    stfs f2,0x2c(r1)
    HeartCompoundItem_TickCarryPhase_L_800F29DC:
    bl fn_8027E9E8
    HeartCompoundItem_TickCarryPhase_L_800F29E0:
    frsp f0,f1
    HeartCompoundItem_TickCarryPhase_L_800F29E4:
    lfs f1,-0x7948(r13)
    HeartCompoundItem_TickCarryPhase_L_800F29E8:
    lis r3,-0x7fbe
    HeartCompoundItem_TickCarryPhase_L_800F29EC:
    lwz r11,0x38(r1)
    HeartCompoundItem_TickCarryPhase_L_800F29F0:
    addi r3,r3,0x16f8
    HeartCompoundItem_TickCarryPhase_L_800F29F4:
    lwz r10,0x3c(r1)
    HeartCompoundItem_TickCarryPhase_L_800F29F8:
    fmadds f1,f1,f0,f1
    HeartCompoundItem_TickCarryPhase_L_800F29FC:
    lfs f2,0x4(r3)
    HeartCompoundItem_TickCarryPhase_L_800F2A00:
    lfs f0,0x8(r3)
    HeartCompoundItem_TickCarryPhase_L_800F2A04:
    or r3,r30,r30
    HeartCompoundItem_TickCarryPhase_L_800F2A08:
    lwz r9,0x40(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A0C:
    addi r4,r1,0x20
    HeartCompoundItem_TickCarryPhase_L_800F2A10:
    fadds f1,f2,f1
    HeartCompoundItem_TickCarryPhase_L_800F2A14:
    stfs f0,0x34(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A18:
    lwz r8,0x2c(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A1C:
    addi r5,r1,0x14
    HeartCompoundItem_TickCarryPhase_L_800F2A20:
    lwz r0,0x34(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A24:
    li r6,0x1
    HeartCompoundItem_TickCarryPhase_L_800F2A28:
    stfs f1,0x30(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A2C:
    lfs f1,-0x7954(r13)
    HeartCompoundItem_TickCarryPhase_L_800F2A30:
    lwz r7,0x30(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A34:
    stw r11,0x14(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A38:
    stw r10,0x18(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A3C:
    stw r9,0x1c(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A40:
    stw r8,0x20(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A44:
    stw r7,0x24(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A48:
    stw r0,0x28(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2A4C:
    bl Item_RenderHandheldByCharacter
    HeartCompoundItem_TickCarryPhase_L_800F2A50:
    addi r3,r30,0x48
    HeartCompoundItem_TickCarryPhase_L_800F2A54:
    bl Mtx44_GetYawOfPosZ_Padded
    HeartCompoundItem_TickCarryPhase_L_800F2A58:
    stfs f1,0xb0(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2A5C:
    lwz r3,0x98(r31)
    HeartCompoundItem_TickCarryPhase_L_800F2A60:
    bl FinalLapCoinJump_CheckActiveForObject
    HeartCompoundItem_TickCarryPhase_L_800F2A64:
    rlwinm. r0,r3,0x0,0x18,0x1f
    HeartCompoundItem_TickCarryPhase_L_800F2A68:
    beq HeartCompoundItem_TickCarryPhase_L_800F2A78
    HeartCompoundItem_TickCarryPhase_L_800F2A6C:
    li r0,0x0
    HeartCompoundItem_TickCarryPhase_L_800F2A70:
    stb r0,0x28(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2A74:
    b HeartCompoundItem_TickCarryPhase_L_800F2A80
    HeartCompoundItem_TickCarryPhase_L_800F2A78:
    li r0,0x1
    HeartCompoundItem_TickCarryPhase_L_800F2A7C:
    stb r0,0x28(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2A80:
    lbz r0,0xa0(r31)
    HeartCompoundItem_TickCarryPhase_L_800F2A84:
    extsb r0,r0
    HeartCompoundItem_TickCarryPhase_L_800F2A88:
    cmpwi r0,0x2
    HeartCompoundItem_TickCarryPhase_L_800F2A8C:
    beq HeartCompoundItem_TickCarryPhase_L_800F2B24
    HeartCompoundItem_TickCarryPhase_L_800F2A90:
    bge HeartCompoundItem_TickCarryPhase_L_800F2B3C
    HeartCompoundItem_TickCarryPhase_L_800F2A94:
    cmpwi r0,0x1
    HeartCompoundItem_TickCarryPhase_L_800F2A98:
    bge HeartCompoundItem_TickCarryPhase_L_800F2AA0
    HeartCompoundItem_TickCarryPhase_L_800F2A9C:
    b HeartCompoundItem_TickCarryPhase_L_800F2B3C
    HeartCompoundItem_TickCarryPhase_L_800F2AA0:
    li r0,0x0
    HeartCompoundItem_TickCarryPhase_L_800F2AA4:
    addi r3,r30,0x14
    HeartCompoundItem_TickCarryPhase_L_800F2AA8:
    stb r0,0xa0(r31)
    HeartCompoundItem_TickCarryPhase_L_800F2AAC:
    li r4,0x0
    HeartCompoundItem_TickCarryPhase_L_800F2AB0:
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    HeartCompoundItem_TickCarryPhase_L_800F2AB4:
    lfs f0,-0x41dc(r2)
    HeartCompoundItem_TickCarryPhase_L_800F2AB8:
    stfs f0,0x2c(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2ABC:
    lwz r3,0x98(r31)
    HeartCompoundItem_TickCarryPhase_L_800F2AC0:
    cmplwi r3,0x0
    HeartCompoundItem_TickCarryPhase_L_800F2AC4:
    beq HeartCompoundItem_TickCarryPhase_L_800F2B0C
    HeartCompoundItem_TickCarryPhase_L_800F2AC8:
    bl KartDriver_GetKartRootMtx
    HeartCompoundItem_TickCarryPhase_L_800F2ACC:
    or r4,r3,r3
    HeartCompoundItem_TickCarryPhase_L_800F2AD0:
    addi r3,r1,0x44
    HeartCompoundItem_TickCarryPhase_L_800F2AD4:
    bl Mtx_TransposeToMtx44
    HeartCompoundItem_TickCarryPhase_L_800F2AD8:
    addi r3,r1,0x44
    HeartCompoundItem_TickCarryPhase_L_800F2ADC:
    or r4,r3,r3
    HeartCompoundItem_TickCarryPhase_L_800F2AE0:
    bl Mtx44_Inverse_GaussJordan
    HeartCompoundItem_TickCarryPhase_L_800F2AE4:
    lwz r6,0xa0(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2AE8:
    addi r3,r31,0x34
    HeartCompoundItem_TickCarryPhase_L_800F2AEC:
    lwz r0,0xa4(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2AF0:
    addi r4,r1,0x44
    HeartCompoundItem_TickCarryPhase_L_800F2AF4:
    addi r5,r1,0x8
    HeartCompoundItem_TickCarryPhase_L_800F2AF8:
    stw r6,0x8(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2AFC:
    stw r0,0xc(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2B00:
    lwz r0,0xa8(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2B04:
    stw r0,0x10(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2B08:
    bl Mtx44_TransformVec3
    HeartCompoundItem_TickCarryPhase_L_800F2B0C:
    lbz r3,0xc9(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2B10:
    li r0,0x0
    HeartCompoundItem_TickCarryPhase_L_800F2B14:
    addi r3,r3,0x1
    HeartCompoundItem_TickCarryPhase_L_800F2B18:
    stb r3,0xc9(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2B1C:
    stb r0,0xca(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2B20:
    b HeartCompoundItem_TickCarryPhase_L_800F2B3C
    HeartCompoundItem_TickCarryPhase_L_800F2B24:
    li r3,0x0
    HeartCompoundItem_TickCarryPhase_L_800F2B28:
    li r0,0x3
    HeartCompoundItem_TickCarryPhase_L_800F2B2C:
    stb r3,0xa0(r31)
    HeartCompoundItem_TickCarryPhase_L_800F2B30:
    stb r3,0x28(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2B34:
    stb r0,0xc8(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2B38:
    stb r3,0xc9(r30)
    HeartCompoundItem_TickCarryPhase_L_800F2B3C:
    lwz r0,0x94(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2B40:
    lwz r31,0x8c(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2B44:
    lwz r30,0x88(r1)
    HeartCompoundItem_TickCarryPhase_L_800F2B48:
    mtlr r0
    HeartCompoundItem_TickCarryPhase_L_800F2B4C:
    addi r1,r1,0x90
    HeartCompoundItem_TickCarryPhase_L_800F2B50:
    blr
}

asm void HeartCompoundItem_Update(void) { /* 0x800F2B54 size:0x20C */
    nofralloc
    stwu r1,-0x60(r1)
    HeartCompoundItem_Update_L_800F2B58:
    mflr r0
    HeartCompoundItem_Update_L_800F2B5C:
    stw r0,0x64(r1)
    HeartCompoundItem_Update_L_800F2B60:
    stw r31,0x5c(r1)
    HeartCompoundItem_Update_L_800F2B64:
    stw r30,0x58(r1)
    HeartCompoundItem_Update_L_800F2B68:
    or r30,r3,r3
    HeartCompoundItem_Update_L_800F2B6C:
    addi r31,r30,0xec
    HeartCompoundItem_Update_L_800F2B70:
    lbz r0,0xc8(r3)
    HeartCompoundItem_Update_L_800F2B74:
    extsb r0,r0
    HeartCompoundItem_Update_L_800F2B78:
    cmpwi r0,0x2
    HeartCompoundItem_Update_L_800F2B7C:
    beq HeartCompoundItem_Update_L_800F2C4C
    HeartCompoundItem_Update_L_800F2B80:
    bge HeartCompoundItem_Update_L_800F2B94
    HeartCompoundItem_Update_L_800F2B84:
    cmpwi r0,0x0
    HeartCompoundItem_Update_L_800F2B88:
    beq HeartCompoundItem_Update_L_800F2BA0
    HeartCompoundItem_Update_L_800F2B8C:
    bge HeartCompoundItem_Update_L_800F2BDC
    HeartCompoundItem_Update_L_800F2B90:
    b HeartCompoundItem_Update_L_800F2C4C
    HeartCompoundItem_Update_L_800F2B94:
    cmpwi r0,0x4
    HeartCompoundItem_Update_L_800F2B98:
    bge HeartCompoundItem_Update_L_800F2C4C
    HeartCompoundItem_Update_L_800F2B9C:
    b HeartCompoundItem_Update_L_800F2C1C
    HeartCompoundItem_Update_L_800F2BA0:
    lwz r0,-0x7958(r13)
    HeartCompoundItem_Update_L_800F2BA4:
    addi r3,r30,0x14
    HeartCompoundItem_Update_L_800F2BA8:
    rlwinm r4,r0,0x0,0x18,0x1f
    HeartCompoundItem_Update_L_800F2BAC:
    bl SpriteSlot_InitNonLoop
    HeartCompoundItem_Update_L_800F2BB0:
    li r0,0x4
    HeartCompoundItem_Update_L_800F2BB4:
    lis r3,-0x7ff4
    HeartCompoundItem_Update_L_800F2BB8:
    stb r0,0x14(r30)
    HeartCompoundItem_Update_L_800F2BBC:
    addi r3,r3,0x439c
    HeartCompoundItem_Update_L_800F2BC0:
    bl DrawEffect_SpawnDirect
    HeartCompoundItem_Update_L_800F2BC4:
    stw r3,0x4c(r31)
    HeartCompoundItem_Update_L_800F2BC8:
    li r3,0x1
    HeartCompoundItem_Update_L_800F2BCC:
    li r0,0x0
    HeartCompoundItem_Update_L_800F2BD0:
    stb r3,0xc8(r30)
    HeartCompoundItem_Update_L_800F2BD4:
    stb r0,0xc9(r30)
    HeartCompoundItem_Update_L_800F2BD8:
    stb r0,0xca(r30)
    HeartCompoundItem_Update_L_800F2BDC:
    lbz r0,0xc9(r30)
    HeartCompoundItem_Update_L_800F2BE0:
    extsb r0,r0
    HeartCompoundItem_Update_L_800F2BE4:
    cmpwi r0,0x1
    HeartCompoundItem_Update_L_800F2BE8:
    beq HeartCompoundItem_Update_L_800F2C0C
    HeartCompoundItem_Update_L_800F2BEC:
    bge HeartCompoundItem_Update_L_800F2C4C
    HeartCompoundItem_Update_L_800F2BF0:
    cmpwi r0,0x0
    HeartCompoundItem_Update_L_800F2BF4:
    bge HeartCompoundItem_Update_L_800F2BFC
    HeartCompoundItem_Update_L_800F2BF8:
    b HeartCompoundItem_Update_L_800F2C4C
    HeartCompoundItem_Update_L_800F2BFC:
    or r3,r30,r30
    HeartCompoundItem_Update_L_800F2C00:
    or r4,r31,r31
    HeartCompoundItem_Update_L_800F2C04:
    bl HeartCompoundItem_TickCarryPhase
    HeartCompoundItem_Update_L_800F2C08:
    b HeartCompoundItem_Update_L_800F2C4C
    HeartCompoundItem_Update_L_800F2C0C:
    or r3,r30,r30
    HeartCompoundItem_Update_L_800F2C10:
    or r4,r31,r31
    HeartCompoundItem_Update_L_800F2C14:
    bl HeartCompoundItem_TickReleasePhase
    HeartCompoundItem_Update_L_800F2C18:
    b HeartCompoundItem_Update_L_800F2C4C
    HeartCompoundItem_Update_L_800F2C1C:
    lwz r3,0x4c(r31)
    HeartCompoundItem_Update_L_800F2C20:
    cmplwi r3,0x0
    HeartCompoundItem_Update_L_800F2C24:
    beq HeartCompoundItem_Update_L_800F2C30
    HeartCompoundItem_Update_L_800F2C28:
    li r0,0x2
    HeartCompoundItem_Update_L_800F2C2C:
    stb r0,0xc9(r3)
    HeartCompoundItem_Update_L_800F2C30:
    li r0,0x0
    HeartCompoundItem_Update_L_800F2C34:
    or r3,r30,r30
    HeartCompoundItem_Update_L_800F2C38:
    stw r0,0x4c(r31)
    HeartCompoundItem_Update_L_800F2C3C:
    lwz r4,0x98(r31)
    HeartCompoundItem_Update_L_800F2C40:
    stb r0,0x2b1(r4)
    HeartCompoundItem_Update_L_800F2C44:
    bl SpriteSlot_Container_Free
    HeartCompoundItem_Update_L_800F2C48:
    b HeartCompoundItem_Update_L_800F2D48
    HeartCompoundItem_Update_L_800F2C4C:
    lwz r6,0xac(r30)
    HeartCompoundItem_Update_L_800F2C50:
    addi r3,r30,0x14
    HeartCompoundItem_Update_L_800F2C54:
    lwz r0,0xb0(r30)
    HeartCompoundItem_Update_L_800F2C58:
    addi r4,r1,0x14
    HeartCompoundItem_Update_L_800F2C5C:
    addi r5,r1,0x8
    HeartCompoundItem_Update_L_800F2C60:
    stw r6,0x8(r1)
    HeartCompoundItem_Update_L_800F2C64:
    stw r0,0xc(r1)
    HeartCompoundItem_Update_L_800F2C68:
    lwz r0,0xb4(r30)
    HeartCompoundItem_Update_L_800F2C6C:
    stw r0,0x10(r1)
    HeartCompoundItem_Update_L_800F2C70:
    lwz r6,0xa0(r30)
    HeartCompoundItem_Update_L_800F2C74:
    lwz r0,0xa4(r30)
    HeartCompoundItem_Update_L_800F2C78:
    stw r6,0x14(r1)
    HeartCompoundItem_Update_L_800F2C7C:
    stw r0,0x18(r1)
    HeartCompoundItem_Update_L_800F2C80:
    lwz r0,0xa8(r30)
    HeartCompoundItem_Update_L_800F2C84:
    stw r0,0x1c(r1)
    HeartCompoundItem_Update_L_800F2C88:
    lfs f1,0xc4(r30)
    HeartCompoundItem_Update_L_800F2C8C:
    bl SpriteSlot_SetTransform
    HeartCompoundItem_Update_L_800F2C90:
    addi r3,r30,0x14
    HeartCompoundItem_Update_L_800F2C94:
    bl SpriteSlot_TickAnim
    HeartCompoundItem_Update_L_800F2C98:
    lwz r0,0x4c(r31)
    HeartCompoundItem_Update_L_800F2C9C:
    cmplwi r0,0x0
    HeartCompoundItem_Update_L_800F2CA0:
    beq HeartCompoundItem_Update_L_800F2CF8
    HeartCompoundItem_Update_L_800F2CA4:
    lis r4,-0x7fcd
    HeartCompoundItem_Update_L_800F2CA8:
    addi r3,r1,0x20
    HeartCompoundItem_Update_L_800F2CAC:
    subi r5,r4,0xa80
    HeartCompoundItem_Update_L_800F2CB0:
    addi r4,r30,0x14
    HeartCompoundItem_Update_L_800F2CB4:
    bl JointByName_GetLocalMatrix4x3
    HeartCompoundItem_Update_L_800F2CB8:
    lbz r0,0x28(r30)
    HeartCompoundItem_Update_L_800F2CBC:
    extsb. r0,r0
    HeartCompoundItem_Update_L_800F2CC0:
    beq HeartCompoundItem_Update_L_800F2CE0
    HeartCompoundItem_Update_L_800F2CC4:
    lwz r3,0x4c(r31)
    HeartCompoundItem_Update_L_800F2CC8:
    addi r4,r1,0x20
    HeartCompoundItem_Update_L_800F2CCC:
    lfs f1,0xb0(r30)
    HeartCompoundItem_Update_L_800F2CD0:
    lfs f2,0xc4(r30)
    HeartCompoundItem_Update_L_800F2CD4:
    lfs f3,0x2c(r30)
    HeartCompoundItem_Update_L_800F2CD8:
    bl Effect_CompoundRing_PlaceChildren
    HeartCompoundItem_Update_L_800F2CDC:
    b HeartCompoundItem_Update_L_800F2CF8
    HeartCompoundItem_Update_L_800F2CE0:
    lwz r3,0x4c(r31)
    HeartCompoundItem_Update_L_800F2CE4:
    addi r4,r1,0x20
    HeartCompoundItem_Update_L_800F2CE8:
    lfs f1,0xb0(r30)
    HeartCompoundItem_Update_L_800F2CEC:
    lfs f2,0xc4(r30)
    HeartCompoundItem_Update_L_800F2CF0:
    lfs f3,-0x4200(r2)
    HeartCompoundItem_Update_L_800F2CF4:
    bl Effect_CompoundRing_PlaceChildren
    HeartCompoundItem_Update_L_800F2CF8:
    lwz r3,0x4(r31)
    HeartCompoundItem_Update_L_800F2CFC:
    cmplwi r3,0x0
    HeartCompoundItem_Update_L_800F2D00:
    beq HeartCompoundItem_Update_L_800F2D0C
    HeartCompoundItem_Update_L_800F2D04:
    subi r0,r3,0x1
    HeartCompoundItem_Update_L_800F2D08:
    stw r0,0x4(r31)
    HeartCompoundItem_Update_L_800F2D0C:
    lwz r3,0x8(r31)
    HeartCompoundItem_Update_L_800F2D10:
    cmplwi r3,0x0
    HeartCompoundItem_Update_L_800F2D14:
    beq HeartCompoundItem_Update_L_800F2D20
    HeartCompoundItem_Update_L_800F2D18:
    subi r0,r3,0x1
    HeartCompoundItem_Update_L_800F2D1C:
    stw r0,0x8(r31)
    HeartCompoundItem_Update_L_800F2D20:
    lwz r3,0xc(r31)
    HeartCompoundItem_Update_L_800F2D24:
    cmplwi r3,0x0
    HeartCompoundItem_Update_L_800F2D28:
    beq HeartCompoundItem_Update_L_800F2D34
    HeartCompoundItem_Update_L_800F2D2C:
    subi r0,r3,0x1
    HeartCompoundItem_Update_L_800F2D30:
    stw r0,0xc(r31)
    HeartCompoundItem_Update_L_800F2D34:
    lwz r3,0x10(r31)
    HeartCompoundItem_Update_L_800F2D38:
    cmplwi r3,0x0
    HeartCompoundItem_Update_L_800F2D3C:
    beq HeartCompoundItem_Update_L_800F2D48
    HeartCompoundItem_Update_L_800F2D40:
    subi r0,r3,0x1
    HeartCompoundItem_Update_L_800F2D44:
    stw r0,0x10(r31)
    HeartCompoundItem_Update_L_800F2D48:
    lwz r0,0x64(r1)
    HeartCompoundItem_Update_L_800F2D4C:
    lwz r31,0x5c(r1)
    HeartCompoundItem_Update_L_800F2D50:
    lwz r30,0x58(r1)
    HeartCompoundItem_Update_L_800F2D54:
    mtlr r0
    HeartCompoundItem_Update_L_800F2D58:
    addi r1,r1,0x60
    HeartCompoundItem_Update_L_800F2D5C:
    blr
}

