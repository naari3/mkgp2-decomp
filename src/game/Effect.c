/* === extracted from auto_Effect_SmokeCloud_Dr_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Magnitude_Wrapper();
extern void Vec3_Scale();
extern void Vec3_Subtract_DestFirst();
extern void VfxSlot_SetPositionFromVec();
extern void VfxSlot_SetScaleUniform();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5400;
extern unsigned int lbl_806D540C;
extern unsigned int lbl_806D5414;
extern unsigned int lbl_806D5420;
extern unsigned int lbl_806D5424;
extern unsigned int lbl_806D5454;
extern unsigned int lbl_806D546C;

/* --- function index (1 fns, .text 0x800C37C8..0x800C39F8) ---
 * [  0] 0x800C37C8 size:0x230   global Effect_SmokeCloud_DriveSubslots
 */

/* --- forward decls --- */
asm void Effect_SmokeCloud_DriveSubslots(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Effect_SmokeCloud_DriveSubslots[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Effect_SmokeCloud_DriveSubslots = {
    (void *)&Effect_SmokeCloud_DriveSubslots, 0x00000230, (void *)extab_Effect_SmokeCloud_DriveSubslots
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Effect_SmokeCloud_DriveSubslots(void) { /* 0x800C37C8 size:0x230 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    stw r29, 0x34(r1)
    stw r28, 0x30(r1)
    mr. r30, r3
    fmr f31, f1
    mr r28, r4
    mr r29, r5
    beq Effect_SmokeCloud_DriveSubslots_L_800C39D0
    addi r3, r30, 0x8c
    bl Vec3_Copy
    mr r4, r29
    addi r3, r30, 0xa4
    bl Vec3_Copy
    li r29, 0x0
    addi r31, r30, 0xcc
    Effect_SmokeCloud_DriveSubslots_L_800C381C:
    lwz r30, 0x10(r31)
    cmplwi r30, 0x0
    beq Effect_SmokeCloud_DriveSubslots_L_800C39C0
    lbz r0, 0x190(r30)
    extsb. r0, r0
    beq Effect_SmokeCloud_DriveSubslots_L_800C39C0
    li r0, 0x1
    addi r3, r30, 0x8c
    stb r0, 0x28(r30)
    mr r4, r3
    lfs f2, lbl_806D546C(r2)
    addi r5, r30, 0xa4
    lfs f1, 0xa4(r30)
    lfs f0, lbl_806D5454(r2)
    fmuls f1, f1, f2
    stfs f1, 0xa4(r30)
    lfs f1, 0xac(r30)
    fmuls f1, f1, f2
    stfs f1, 0xac(r30)
    lfs f1, 0xa8(r30)
    fadds f0, f1, f0
    stfs f0, 0xa8(r30)
    bl Vec3_Add_DestFirst
    lfs f1, 0x150(r30)
    mr r4, r28
    lfs f0, lbl_806D540C(r2)
    addi r3, r1, 0x20
    addi r5, r30, 0x120
    fadds f0, f1, f0
    stfs f0, 0x150(r30)
    bl Vec3_Add_DestFirst
    addi r3, r1, 0x14
    addi r4, r30, 0x8c
    addi r5, r1, 0x20
    bl Vec3_Subtract_DestFirst
    addi r3, r1, 0x14
    bl Vec3_Magnitude_Wrapper
    lfs f2, 0x150(r30)
    fcmpo cr0, f2, f1
    bge Effect_SmokeCloud_DriveSubslots_L_800C38E4
    lfs f0, lbl_806D5424(r2)
    addi r3, r1, 0x14
    mr r4, r3
    fdivs f0, f0, f1
    fmuls f1, f0, f2
    bl Vec3_Scale
    addi r3, r30, 0x8c
    addi r4, r1, 0x20
    addi r5, r1, 0x14
    bl Vec3_Add_DestFirst
    Effect_SmokeCloud_DriveSubslots_L_800C38E4:
    lfs f1, 0xb0(r30)
    lfs f0, lbl_806D5414(r2)
    fadds f0, f1, f0
    stfs f0, 0xb0(r30)
    lwz r0, 0x180(r30)
    cmplwi r0, 0x0
    bne Effect_SmokeCloud_DriveSubslots_L_800C3934
    lfs f2, 0x154(r30)
    lfs f1, lbl_806D5420(r2)
    lfs f0, lbl_806D5400(r2)
    fsubs f1, f2, f1
    stfs f1, 0x154(r30)
    lfs f1, 0x154(r30)
    fcmpo cr0, f1, f0
    bge Effect_SmokeCloud_DriveSubslots_L_800C3934
    li r3, 0x0
    li r0, 0x1
    stb r3, 0x28(r30)
    stb r3, 0x190(r30)
    stb r0, 0xc9(r30)
    Effect_SmokeCloud_DriveSubslots_L_800C3934:
    lfs f0, 0x154(r30)
    addi r3, r30, 0x14
    addi r4, r1, 0x8
    fmuls f0, f0, f31
    stfs f0, 0x2c(r30)
    lwz r5, 0x8c(r30)
    lwz r0, 0x90(r30)
    stw r5, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0x94(r30)
    stw r0, 0x10(r1)
    bl VfxSlot_SetPositionFromVec
    lfs f1, 0xb0(r30)
    addi r3, r30, 0x14
    bl VfxSlot_SetScaleUniform
    lwz r3, 0x180(r30)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_DriveSubslots_L_800C3984
    subi r0, r3, 0x1
    stw r0, 0x180(r30)
    Effect_SmokeCloud_DriveSubslots_L_800C3984:
    lwz r3, 0x184(r30)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_DriveSubslots_L_800C3998
    subi r0, r3, 0x1
    stw r0, 0x184(r30)
    Effect_SmokeCloud_DriveSubslots_L_800C3998:
    lwz r3, 0x188(r30)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_DriveSubslots_L_800C39AC
    subi r0, r3, 0x1
    stw r0, 0x188(r30)
    Effect_SmokeCloud_DriveSubslots_L_800C39AC:
    lwz r3, 0x18c(r30)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_DriveSubslots_L_800C39C0
    subi r0, r3, 0x1
    stw r0, 0x18c(r30)
    Effect_SmokeCloud_DriveSubslots_L_800C39C0:
    addi r29, r29, 0x1
    addi r31, r31, 0x4
    cmpwi r29, 0x8
    blt Effect_SmokeCloud_DriveSubslots_L_800C381C
    Effect_SmokeCloud_DriveSubslots_L_800C39D0:
    psq_l f31, 0x48(r1), 0, 0
    lwz r0, 0x54(r1)
    lfd f31, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    lwz r29, 0x34(r1)
    lwz r28, 0x30(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

#include "src/game/Effect_SmokeCloud_Update.inc"
