/* === extracted from auto_JumpDistanceMode_Upd_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CarObject_GetRenderObj();
extern void CarObject_IsAirborne();
extern void IsCardValid();
extern void JumpDistanceMode_PredictLanding();
extern void KartDriver_GetKartRootMtx();
extern void KartMovement_GetVelocityMagnitude();
extern void KartMovement_GetVelocityPtr();
extern void NokoNokoChallenge_GetCoinDivisor();
extern void SoundMgr_PlaySE();
extern void Terrain_GetGroundHeight();
extern void Vec3_Dot();
extern void Vec3_Subtract();
extern void fn_8016C1F8();
extern void fn_8016C360();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceEnded;
extern unsigned int lbl_806DAD74;
extern unsigned int lbl_806DAD7C;
extern unsigned int lbl_806DAD90;
extern unsigned int lbl_806DAD98;
extern unsigned int lbl_806DADA0;
extern unsigned int lbl_806DADA4;
extern unsigned int lbl_806DADA8;
extern unsigned int lbl_806DADAC;
extern unsigned int lbl_806DCF60;
extern unsigned int lbl_806DCF64;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803C3D54[];
extern unsigned int lbl_803C3D80[];

/* --- function index (1 fns, .text 0x80210CD4..0x80211550) ---
 * [  0] 0x80210CD4 size:0x87C   global JumpDistanceMode_UpdateGameplay
 */

/* --- forward decls --- */
asm void JumpDistanceMode_UpdateGameplay(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_JumpDistanceMode_UpdateGameplay[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_JumpDistanceMode_UpdateGameplay = {
    (void *)&JumpDistanceMode_UpdateGameplay, 0x0000087C, (void *)extab_JumpDistanceMode_UpdateGameplay
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void JumpDistanceMode_UpdateGameplay(void) { /* 0x80210CD4 size:0x87C */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stw r31, 0x9c(r1)
    mr r31, r3
    stw r30, 0x98(r1)
    stw r29, 0x94(r1)
    lwz r0, 0x50(r3)
    cmpwi r0, 0x3
    beq JumpDistanceMode_UpdateGameplay_L_80211444
    bge JumpDistanceMode_UpdateGameplay_L_80210D18
    cmpwi r0, 0x1
    beq JumpDistanceMode_UpdateGameplay_L_80211018
    bge JumpDistanceMode_UpdateGameplay_L_802112D8
    cmpwi r0, 0x0
    bge JumpDistanceMode_UpdateGameplay_L_80210D28
    b JumpDistanceMode_UpdateGameplay_L_80211534
    JumpDistanceMode_UpdateGameplay_L_80210D18:
    cmpwi r0, 0x5
    beq JumpDistanceMode_UpdateGameplay_L_80211534
    bge JumpDistanceMode_UpdateGameplay_L_80211534
    b JumpDistanceMode_UpdateGameplay_L_802114D0
    JumpDistanceMode_UpdateGameplay_L_80210D28:
    lwz r3, 0x8(r31)
    bl CarObject_IsAirborne
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_UpdateGameplay_L_80210ED0
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    lwz r30, 0x30(r31)
    mr r29, r3
    bl KartDriver_GetKartRootMtx
    lwz r5, lbl_806DCF60(r2)
    lis r4, lbl_803C3D54@ha
    lwz r0, lbl_806DCF64(r2)
    lfs f2, 0xc(r3)
    lfsu f0, lbl_803C3D54@l(r4)
    stw r5, 0x14(r1)
    lfs f1, 0x2c(r3)
    fcmpo cr0, f2, f0
    stw r0, 0x18(r1)
    stfs f2, 0x14(r1)
    stfs f1, 0x18(r1)
    bge JumpDistanceMode_UpdateGameplay_L_80210D88
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_80210DC8
    JumpDistanceMode_UpdateGameplay_L_80210D88:
    lfs f0, 0x8(r4)
    fcmpo cr0, f2, f0
    ble JumpDistanceMode_UpdateGameplay_L_80210D9C
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_80210DC8
    JumpDistanceMode_UpdateGameplay_L_80210D9C:
    lfs f0, 0x4(r4)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_UpdateGameplay_L_80210DB0
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_80210DC8
    JumpDistanceMode_UpdateGameplay_L_80210DB0:
    lfs f0, 0xc(r4)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_UpdateGameplay_L_80210DC4
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_80210DC8
    JumpDistanceMode_UpdateGameplay_L_80210DC4:
    li r0, 0x1
    JumpDistanceMode_UpdateGameplay_L_80210DC8:
    clrlwi. r0, r0, 24
    bne JumpDistanceMode_UpdateGameplay_L_80210DD8
    li r0, 0x1
    b JumpDistanceMode_UpdateGameplay_L_80210E00
    JumpDistanceMode_UpdateGameplay_L_80210DD8:
    mr r3, r29
    bl KartMovement_GetVelocityPtr
    addi r4, r30, 0x4
    bl Vec3_Dot
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_UpdateGameplay_L_80210DFC
    li r0, 0x1
    b JumpDistanceMode_UpdateGameplay_L_80210E00
    JumpDistanceMode_UpdateGameplay_L_80210DFC:
    li r0, 0x0
    JumpDistanceMode_UpdateGameplay_L_80210E00:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    beq JumpDistanceMode_UpdateGameplay_L_80211534
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lfs f1, 0xc(r3)
    addi r4, r1, 0x10
    lfs f0, lbl_806DAD7C(r2)
    li r5, 0x0
    stfs f1, 0x74(r1)
    li r6, 0x0
    lfs f1, 0x1c(r3)
    stfs f1, 0x78(r1)
    lfs f1, 0x2c(r3)
    addi r3, r1, 0x74
    stfs f1, 0x7c(r1)
    stfs f0, 0x10(r1)
    bl Terrain_GetGroundHeight
    lfs f2, 0x78(r1)
    lfs f1, 0x10(r1)
    lfs f0, lbl_806DADA8(r2)
    fsubs f1, f2, f1
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    lfs f0, 0x74(r1)
    li r3, 0x42
    stfs f0, 0x5c(r31)
    lfs f0, 0x78(r1)
    stfs f0, 0x60(r31)
    lfs f0, 0x7c(r1)
    stfs f0, 0x64(r31)
    lwz r29, 0x3c(r31)
    bl fn_8016C360
    clrlwi. r0, r3, 24
    bne JumpDistanceMode_UpdateGameplay_L_80210EA8
    li r3, 0x42
    bl SoundMgr_PlaySE
    lfs f1, lbl_806DADAC(r2)
    li r3, 0x42
    bl fn_8016C1F8
    JumpDistanceMode_UpdateGameplay_L_80210EA8:
    li r4, 0x1
    lfs f0, lbl_806DAD74(r2)
    stb r4, 0x0(r29)
    lwz r0, 0x8(r29)
    stw r0, 0x4(r29)
    lwz r3, 0x40(r31)
    stw r4, 0x0(r3)
    stw r4, 0x50(r31)
    stfs f0, 0x74(r31)
    b JumpDistanceMode_UpdateGameplay_L_80211534
    JumpDistanceMode_UpdateGameplay_L_80210ED0:
    lbz r0, 0x88(r31)
    cmplwi r0, 0x0
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    lwz r29, 0x30(r31)
    bl KartDriver_GetKartRootMtx
    lis r4, lbl_803C3D80@ha
    addi r5, r1, 0x68
    addi r7, r4, lbl_803C3D80@l
    lwz r6, 0x0(r7)
    lwz r4, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r6, 0x5c(r1)
    stw r4, 0x60(r1)
    stw r0, 0x64(r1)
    lfs f0, 0xc(r3)
    stfs f0, 0x5c(r1)
    lfs f0, 0x2c(r3)
    addi r3, r1, 0x5c
    stfs f0, 0x64(r1)
    lwz r4, 0x0(r29)
    bl Vec3_Subtract
    addi r3, r1, 0x68
    addi r4, r29, 0x4
    bl Vec3_Dot
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_UpdateGameplay_L_80210F4C
    li r0, 0x1
    b JumpDistanceMode_UpdateGameplay_L_80210F50
    JumpDistanceMode_UpdateGameplay_L_80210F4C:
    li r0, 0x0
    JumpDistanceMode_UpdateGameplay_L_80210F50:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lwz r5, lbl_806DCF60(r2)
    lis r4, lbl_803C3D54@ha
    lwz r0, lbl_806DCF64(r2)
    lfs f2, 0xc(r3)
    lfsu f0, lbl_803C3D54@l(r4)
    stw r5, 0x24(r1)
    lfs f1, 0x2c(r3)
    fcmpo cr0, f2, f0
    stw r0, 0x28(r1)
    stfs f2, 0x24(r1)
    stfs f1, 0x28(r1)
    bge JumpDistanceMode_UpdateGameplay_L_80210FA0
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_80210FE0
    JumpDistanceMode_UpdateGameplay_L_80210FA0:
    lfs f0, 0x8(r4)
    fcmpo cr0, f2, f0
    ble JumpDistanceMode_UpdateGameplay_L_80210FB4
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_80210FE0
    JumpDistanceMode_UpdateGameplay_L_80210FB4:
    lfs f0, 0x4(r4)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_UpdateGameplay_L_80210FC8
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_80210FE0
    JumpDistanceMode_UpdateGameplay_L_80210FC8:
    lfs f0, 0xc(r4)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_UpdateGameplay_L_80210FDC
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_80210FE0
    JumpDistanceMode_UpdateGameplay_L_80210FDC:
    li r0, 0x1
    JumpDistanceMode_UpdateGameplay_L_80210FE0:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_GetVelocityMagnitude
    stfs f1, 0x68(r31)
    mr r3, r31
    bl JumpDistanceMode_PredictLanding
    lwz r3, 0x40(r31)
    li r0, 0x2
    stw r0, 0x0(r3)
    stw r0, 0x50(r31)
    b JumpDistanceMode_UpdateGameplay_L_80211534
    JumpDistanceMode_UpdateGameplay_L_80211018:
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lfs f5, 0xc(r3)
    lfs f0, 0x5c(r31)
    lfs f7, 0x2c(r3)
    lfs f1, 0x64(r31)
    fsubs f2, f5, f0
    lfs f0, lbl_806DAD7C(r2)
    fsubs f1, f7, f1
    lfs f6, 0x1c(r3)
    fmuls f2, f2, f2
    fmuls f1, f1, f1
    fadds f4, f2, f1
    fcmpo cr0, f4, f0
    ble JumpDistanceMode_UpdateGameplay_L_802110A4
    frsqrte f1, f4
    lfd f3, lbl_806DAD90(r2)
    lfd f2, lbl_806DAD98(r2)
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f0, f1, f0
    fmul f0, f4, f0
    frsp f0, f0
    stfs f0, 0xc(r1)
    lfs f4, 0xc(r1)
    JumpDistanceMode_UpdateGameplay_L_802110A4:
    lfs f1, lbl_806DADA0(r2)
    lfs f0, lbl_806DADA4(r2)
    fmuls f1, f1, f4
    lfs f2, 0x58(r31)
    fdivs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0x58(r31)
    stfs f5, 0x5c(r31)
    stfs f6, 0x60(r31)
    stfs f7, 0x64(r31)
    lfs f0, 0x58(r31)
    lwz r29, 0x2c(r31)
    fctiwz f0, f0
    lwz r0, 0x0(r29)
    stfd f0, 0x80(r1)
    lwz r30, 0x84(r1)
    cmpw r0, r30
    beq JumpDistanceMode_UpdateGameplay_L_802110F4
    li r3, 0x1b
    bl SoundMgr_PlaySE
    JumpDistanceMode_UpdateGameplay_L_802110F4:
    stw r30, 0x0(r29)
    bl NokoNokoChallenge_GetCoinDivisor
    lfs f0, 0x58(r31)
    lwz r0, 0x80(r31)
    fctiwz f0, f0
    lwz r5, 0x0(r3)
    slwi r4, r0, 3
    lwzx r0, r5, r4
    stfd f0, 0x80(r1)
    lwz r3, 0x84(r1)
    cmpw r3, r0
    blt JumpDistanceMode_UpdateGameplay_L_80211158
    add r3, r5, r4
    lwz r0, 0x4(r3)
    cmpwi r0, 0x0
    ble JumpDistanceMode_UpdateGameplay_L_80211158
    stw r0, 0x84(r31)
    lwz r4, 0x7c(r31)
    lwz r0, 0x84(r31)
    lwz r3, 0x8(r4)
    subf r0, r3, r0
    stw r0, 0xc(r4)
    lwz r3, 0x80(r31)
    addi r0, r3, 0x1
    stw r0, 0x80(r31)
    JumpDistanceMode_UpdateGameplay_L_80211158:
    lfs f1, 0x74(r31)
    lfs f0, lbl_806DAD74(r2)
    fadds f0, f1, f0
    stfs f0, 0x74(r31)
    lwz r3, 0x3c(r31)
    lbz r0, 0x1(r3)
    cmplwi r0, 0x0
    bne JumpDistanceMode_UpdateGameplay_L_80211190
    lwz r3, 0x40(r31)
    li r0, 0x0
    lfs f0, lbl_806DAD7C(r2)
    stw r0, 0x0(r3)
    stfs f0, 0x74(r31)
    stw r0, 0x50(r31)
    JumpDistanceMode_UpdateGameplay_L_80211190:
    lbz r0, 0x88(r31)
    cmplwi r0, 0x0
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    lwz r29, 0x30(r31)
    bl KartDriver_GetKartRootMtx
    lis r4, lbl_803C3D80@ha
    addi r5, r1, 0x50
    addi r7, r4, lbl_803C3D80@l
    lwz r6, 0x0(r7)
    lwz r4, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r6, 0x44(r1)
    stw r4, 0x48(r1)
    stw r0, 0x4c(r1)
    lfs f0, 0xc(r3)
    stfs f0, 0x44(r1)
    lfs f0, 0x2c(r3)
    addi r3, r1, 0x44
    stfs f0, 0x4c(r1)
    lwz r4, 0x0(r29)
    bl Vec3_Subtract
    addi r3, r1, 0x50
    addi r4, r29, 0x4
    bl Vec3_Dot
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_UpdateGameplay_L_8021120C
    li r0, 0x1
    b JumpDistanceMode_UpdateGameplay_L_80211210
    JumpDistanceMode_UpdateGameplay_L_8021120C:
    li r0, 0x0
    JumpDistanceMode_UpdateGameplay_L_80211210:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lwz r5, lbl_806DCF60(r2)
    lis r4, lbl_803C3D54@ha
    lwz r0, lbl_806DCF64(r2)
    lfs f2, 0xc(r3)
    lfsu f0, lbl_803C3D54@l(r4)
    stw r5, 0x1c(r1)
    lfs f1, 0x2c(r3)
    fcmpo cr0, f2, f0
    stw r0, 0x20(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    bge JumpDistanceMode_UpdateGameplay_L_80211260
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_802112A0
    JumpDistanceMode_UpdateGameplay_L_80211260:
    lfs f0, 0x8(r4)
    fcmpo cr0, f2, f0
    ble JumpDistanceMode_UpdateGameplay_L_80211274
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_802112A0
    JumpDistanceMode_UpdateGameplay_L_80211274:
    lfs f0, 0x4(r4)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_UpdateGameplay_L_80211288
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_802112A0
    JumpDistanceMode_UpdateGameplay_L_80211288:
    lfs f0, 0xc(r4)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_UpdateGameplay_L_8021129C
    li r0, 0x0
    b JumpDistanceMode_UpdateGameplay_L_802112A0
    JumpDistanceMode_UpdateGameplay_L_8021129C:
    li r0, 0x1
    JumpDistanceMode_UpdateGameplay_L_802112A0:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_GetVelocityMagnitude
    stfs f1, 0x68(r31)
    mr r3, r31
    bl JumpDistanceMode_PredictLanding
    lwz r3, 0x40(r31)
    li r0, 0x2
    stw r0, 0x0(r3)
    stw r0, 0x50(r31)
    b JumpDistanceMode_UpdateGameplay_L_80211534
    JumpDistanceMode_UpdateGameplay_L_802112D8:
    lwz r3, 0x8(r31)
    bl CarObject_IsAirborne
    clrlwi. r0, r3, 24
    bne JumpDistanceMode_UpdateGameplay_L_80211300
    li r3, 0x3
    li r0, 0x4
    stw r3, 0x50(r31)
    lwz r3, 0x40(r31)
    stw r0, 0x0(r3)
    b JumpDistanceMode_UpdateGameplay_L_80211534
    JumpDistanceMode_UpdateGameplay_L_80211300:
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lfs f5, 0xc(r3)
    lfs f0, 0x5c(r31)
    lfs f7, 0x2c(r3)
    lfs f1, 0x64(r31)
    fsubs f2, f5, f0
    lfs f0, lbl_806DAD7C(r2)
    fsubs f1, f7, f1
    lfs f6, 0x1c(r3)
    fmuls f2, f2, f2
    fmuls f1, f1, f1
    fadds f4, f2, f1
    fcmpo cr0, f4, f0
    ble JumpDistanceMode_UpdateGameplay_L_8021138C
    frsqrte f1, f4
    lfd f3, lbl_806DAD90(r2)
    lfd f2, lbl_806DAD98(r2)
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f0, f1, f0
    fmul f0, f4, f0
    frsp f0, f0
    stfs f0, 0x8(r1)
    lfs f4, 0x8(r1)
    JumpDistanceMode_UpdateGameplay_L_8021138C:
    lfs f1, lbl_806DADA0(r2)
    lfs f0, lbl_806DADA4(r2)
    fmuls f1, f1, f4
    lfs f2, 0x58(r31)
    fdivs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0x58(r31)
    stfs f5, 0x5c(r31)
    stfs f6, 0x60(r31)
    stfs f7, 0x64(r31)
    lfs f0, 0x58(r31)
    lwz r29, 0x2c(r31)
    fctiwz f0, f0
    lwz r0, 0x0(r29)
    stfd f0, 0x80(r1)
    lwz r30, 0x84(r1)
    cmpw r0, r30
    beq JumpDistanceMode_UpdateGameplay_L_802113DC
    li r3, 0x1b
    bl SoundMgr_PlaySE
    JumpDistanceMode_UpdateGameplay_L_802113DC:
    stw r30, 0x0(r29)
    bl NokoNokoChallenge_GetCoinDivisor
    lfs f0, 0x58(r31)
    lwz r0, 0x80(r31)
    fctiwz f0, f0
    lwz r5, 0x0(r3)
    slwi r4, r0, 3
    lwzx r0, r5, r4
    stfd f0, 0x80(r1)
    lwz r3, 0x84(r1)
    cmpw r3, r0
    blt JumpDistanceMode_UpdateGameplay_L_80211534
    add r3, r5, r4
    lwz r0, 0x4(r3)
    cmpwi r0, 0x0
    ble JumpDistanceMode_UpdateGameplay_L_80211534
    stw r0, 0x84(r31)
    lwz r4, 0x7c(r31)
    lwz r0, 0x84(r31)
    lwz r3, 0x8(r4)
    subf r0, r3, r0
    stw r0, 0xc(r4)
    lwz r3, 0x80(r31)
    addi r0, r3, 0x1
    stw r0, 0x80(r31)
    b JumpDistanceMode_UpdateGameplay_L_80211534
    JumpDistanceMode_UpdateGameplay_L_80211444:
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    lwz r29, 0x34(r31)
    bl KartDriver_GetKartRootMtx
    lis r4, lbl_803C3D80@ha
    addi r5, r1, 0x38
    addi r7, r4, lbl_803C3D80@l
    lwz r6, 0x0(r7)
    lwz r4, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r6, 0x2c(r1)
    stw r4, 0x30(r1)
    stw r0, 0x34(r1)
    lfs f0, 0xc(r3)
    stfs f0, 0x2c(r1)
    lfs f0, 0x2c(r3)
    addi r3, r1, 0x2c
    stfs f0, 0x34(r1)
    lwz r4, 0x0(r29)
    bl Vec3_Subtract
    addi r3, r1, 0x38
    addi r4, r29, 0x4
    bl Vec3_Dot
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f1, f0
    ble JumpDistanceMode_UpdateGameplay_L_802114B4
    li r0, 0x1
    b JumpDistanceMode_UpdateGameplay_L_802114B8
    JumpDistanceMode_UpdateGameplay_L_802114B4:
    li r0, 0x0
    JumpDistanceMode_UpdateGameplay_L_802114B8:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    li r0, 0x4
    stw r0, 0x50(r31)
    b JumpDistanceMode_UpdateGameplay_L_80211534
    JumpDistanceMode_UpdateGameplay_L_802114D0:
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_GetVelocityMagnitude
    lfs f0, lbl_806DAD7C(r2)
    fcmpu cr0, f0, f1
    bne JumpDistanceMode_UpdateGameplay_L_80211534
    lwz r3, 0x40(r31)
    li r4, 0x0
    li r0, 0x1
    stw r4, 0x0(r3)
    stb r0, g_raceEnded(r13)
    stb r0, 0x45(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne JumpDistanceMode_UpdateGameplay_L_80211524
    lfs f1, 0x54(r31)
    lfs f0, 0x58(r31)
    fcmpo cr0, f1, f0
    mfcr r0
    srwi r0, r0, 31
    stb r0, 0x45(r31)
    JumpDistanceMode_UpdateGameplay_L_80211524:
    li r3, 0x1e
    li r0, 0x5
    stw r3, 0x48(r31)
    stw r0, 0x50(r31)
    JumpDistanceMode_UpdateGameplay_L_80211534:
    lwz r0, 0xa4(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    lwz r29, 0x94(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}
