/*
 * HeartCompoundItem @ 0x800F2620..0x800F2D60.
 *
 * Held "heart" compound item. Update drives a three-state machine
 * (spawn / active / release); while active it alternates between the carry
 * phase (item orbits above the holder's kart) and the release phase (glow
 * effects on every other kart holding an item, then the item drifts away).
 * `st` is the per-item state block at self + 0xEC.
 */

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef float Mtx44[4][4];
typedef float Mtx34[3][4];

extern float BuildOrientationFromYaw(float yaw);
extern char *DrawEffect_SpawnDirect(void (*fn)(char *));
extern void Effect_CompoundRing_PlaceChildren(char *ring, Mtx34 *m, float yaw, float scale, float alpha);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern double sin(double x);
extern void *GetRaceContextPtr(void);
extern void Item_DecayVelocityScalar(char *item, float k);
extern void Item_RenderHandheldByCharacter(char *item, Vec3 ofs, Vec3 rot, int flag, float scale);
extern void ItemObject_DispatchVtable18_GetState(void *kart);
extern void JointByName_GetLocalMatrix4x3(Mtx34 *out, void *slot, const char *name);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern int KartMovement_GetCurrentItemId(void *kart);
extern void Mtx_TransposeToMtx44(Mtx44 *dst, void *src);
extern float Mtx44_GetYawOfPosZ(Mtx44 *m);
extern float Mtx44_GetYawOfPosZ_Padded(void *m);
extern void Mtx44_Inverse_GaussJordan(Mtx44 *dst, Mtx44 *src);
extern void Mtx44_TransformVec3(void *out, Mtx44 m, Vec3 v);
extern int *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern void SpriteSlot_Container_Free(char *item);
extern void SpriteSlot_InitNonLoop(void *slot, unsigned char id);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enable);
extern void SpriteSlot_SetTransform(void *slot, Vec3 pos, Vec3 rot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void Effect_KartAuraCompound_Update(char *self);
extern void Effect_KartGlow_Update(char *self);

extern const char lbl_8032F580[];
extern Vec3 lbl_804216F8;
extern Vec3 lbl_80421704;
extern int lbl_806CF3C8;
extern float lbl_806CF3CC;
extern float lbl_806CF3D0;
extern float lbl_806CF3D4;
extern float lbl_806CF3D8;
extern const float lbl_806D6060;
extern const float lbl_806D6064;
extern const float lbl_806D6068;
extern const float lbl_806D606C;
extern const float lbl_806D6070;
extern const float lbl_806D6074;
extern const float lbl_806D6080;
extern const float lbl_806D6084;

extern const double lbl_806D6078;

/*
 * TickReleasePhase is still an exact asm body: the C version reaches 99.4 %
 * but MWCC does not reproduce the redundant `b` after its switch dispatch.
 * Its exception-table entry is emitted manually (postprocess_extab_user.py
 * renames .extab_user/.extabindex_user); the C functions below get theirs
 * from the compiler.
 */
asm void HeartCompoundItem_TickReleasePhase(char *self, char *st);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_HeartCompoundItem_TickReleasePhase[8] =
    { 0x40, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_HeartCompoundItem_TickReleasePhase = {
    (void *)&HeartCompoundItem_TickReleasePhase, 0x000002F0,
    (void *)extab_HeartCompoundItem_TickReleasePhase
};

asm void HeartCompoundItem_TickReleasePhase(char *self, char *st) { /* 0x800F2620 size:0x2F0 */
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
    lfs f0, lbl_806D6060(r2)
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
    lis r3, Effect_KartGlow_Update@ha
    HeartCompoundItem_TickReleasePhase_L_800F26F0:
    lfs f30, lbl_806D6064(r2)
    HeartCompoundItem_TickReleasePhase_L_800F26F4:
    lfd f31, lbl_806D6078(r2)
    HeartCompoundItem_TickReleasePhase_L_800F26F8:
    addi r27, r3, Effect_KartGlow_Update@l
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
    lfs f0, lbl_806D6068(r2)
    HeartCompoundItem_TickReleasePhase_L_800F2808:
    fadds f0,f1,f0
    HeartCompoundItem_TickReleasePhase_L_800F280C:
    stfs f0,0xbc(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2810:
    lfs f2,0x14(r31)
    HeartCompoundItem_TickReleasePhase_L_800F2814:
    lfs f1,0xbc(r30)
    HeartCompoundItem_TickReleasePhase_L_800F2818:
    lfs f0, lbl_806D606C(r2)
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
    lfs f1, lbl_806D6070(r2)
    HeartCompoundItem_TickReleasePhase_L_800F2844:
    lfs f0, lbl_806D6060(r2)
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
    lfs f1, lbl_806D6074(r2)
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

#pragma exceptions on

void HeartCompoundItem_TickCarryPhase(char *self, char *st) {
    Mtx44 m;
    Vec3 rot;
    Vec3 ofs;
    double s;

    switch (*(signed char *)(self + 0xCA)) {
    case 0:
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        *(signed char *)(self + 0x28) = 1;
        *(float *)(self + 0x2C) = lbl_806D6060;
        *(float *)(st + 0x14) = lbl_806D6060;
        (*(signed char *)(self + 0xCA))++;
    case 1:
        *(float *)(st + 0x14) = BuildOrientationFromYaw(*(float *)(st + 0x14) + lbl_806CF3D0);
        rot.x = lbl_80421704.x;
        rot.y = lbl_80421704.y;
        rot.z = lbl_806CF3D4 * (float)sin(*(float *)(st + 0x14)) + lbl_80421704.z;
        ofs.x = lbl_804216F8.x;
        s = sin(lbl_806D6080 * *(float *)(st + 0x14));
        ofs.y = lbl_804216F8.y + (lbl_806CF3D8 * (float)s + lbl_806CF3D8);
        ofs.z = lbl_804216F8.z;
        Item_RenderHandheldByCharacter(self, ofs, rot, 1, lbl_806CF3CC);
        *(float *)(self + 0xB0) = Mtx44_GetYawOfPosZ_Padded(self + 0x48);
        if (FinalLapCoinJump_CheckActiveForObject(*(void **)(st + 0x98))) {
            *(signed char *)(self + 0x28) = 0;
        } else {
            *(signed char *)(self + 0x28) = 1;
        }

        switch (*(signed char *)(st + 0xA0)) {
        case 1:
            *(signed char *)(st + 0xA0) = 0;
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
            *(float *)(self + 0x2C) = lbl_806D6084;
            if (*(void **)(st + 0x98) != 0) {
                Mtx_TransposeToMtx44(&m, KartDriver_GetKartRootMtx(*(void **)(st + 0x98)));
                Mtx44_Inverse_GaussJordan(&m, &m);
                Mtx44_TransformVec3(st + 0x34, m, *(Vec3 *)(self + 0xA0));
            }
            (*(signed char *)(self + 0xC9))++;
            *(signed char *)(self + 0xCA) = 0;
            break;
        case 2:
            *(signed char *)(st + 0xA0) = 0;
            *(signed char *)(self + 0x28) = 0;
            *(signed char *)(self + 0xC8) = 3;
            *(signed char *)(self + 0xC9) = 0;
            break;
        }
        break;
    }
}

void HeartCompoundItem_Update(char *self) {
    Mtx34 jm;
    char *st = self + 0xEC;

    switch (*(signed char *)(self + 0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, lbl_806CF3C8);
        *(signed char *)(self + 0x14) = 4;
        *(char **)(st + 0x4C) = DrawEffect_SpawnDirect(Effect_KartAuraCompound_Update);
        *(signed char *)(self + 0xC8) = 1;
        *(signed char *)(self + 0xC9) = 0;
        *(signed char *)(self + 0xCA) = 0;
    case 1:
        switch (*(signed char *)(self + 0xC9)) {
        case 0:
            HeartCompoundItem_TickCarryPhase(self, st);
            break;
        case 1:
            HeartCompoundItem_TickReleasePhase(self, st);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        if (*(char **)(st + 0x4C) != 0) {
            *(signed char *)(*(char **)(st + 0x4C) + 0xC9) = 2;
        }
        *(char **)(st + 0x4C) = 0;
        *(signed char *)(*(char **)(st + 0x98) + 0x2B1) = 0;
        SpriteSlot_Container_Free(self);
        return;
    }

    SpriteSlot_SetTransform(self + 0x14, *(Vec3 *)(self + 0xA0), *(Vec3 *)(self + 0xAC),
                            *(float *)(self + 0xC4));
    SpriteSlot_TickAnim(self + 0x14);
    if (*(char **)(st + 0x4C) != 0) {
        JointByName_GetLocalMatrix4x3(&jm, self + 0x14, lbl_8032F580);
        if (*(signed char *)(self + 0x28)) {
            Effect_CompoundRing_PlaceChildren(*(char **)(st + 0x4C), &jm, *(float *)(self + 0xB0),
                                              *(float *)(self + 0xC4), *(float *)(self + 0x2C));
        } else {
            Effect_CompoundRing_PlaceChildren(*(char **)(st + 0x4C), &jm, *(float *)(self + 0xB0),
                                              *(float *)(self + 0xC4), lbl_806D6060);
        }
    }
    if (*(unsigned int *)(st + 0x4) != 0) {
        (*(unsigned int *)(st + 0x4))--;
    }
    if (*(unsigned int *)(st + 0x8) != 0) {
        (*(unsigned int *)(st + 0x8))--;
    }
    if (*(unsigned int *)(st + 0xC) != 0) {
        (*(unsigned int *)(st + 0xC))--;
    }
    if (*(unsigned int *)(st + 0x10) != 0) {
        (*(unsigned int *)(st + 0x10))--;
    }
}

#pragma exceptions reset
