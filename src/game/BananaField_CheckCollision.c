/* === extracted from auto_BananaField_CheckCol_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Atan2();
extern void BananaField_TestHitBox();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int lbl_806D95B8;
extern unsigned int lbl_806D95BC;
extern unsigned int lbl_806D95D0;
extern unsigned int lbl_806D95D8;

/* --- function index (1 fns, .text 0x80196C5C..0x80196D9C) ---
 * [  0] 0x80196C5C size:0x140   global BananaField_CheckCollision
 */

/* --- forward decls --- */
asm void BananaField_CheckCollision(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BananaField_CheckCollision[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BananaField_CheckCollision = {
    (void *)&BananaField_CheckCollision, 0x00000140, (void *)extab_BananaField_CheckCollision
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BananaField_CheckCollision(void) { /* 0x80196C5C size:0x140 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r4
    stw r29, 0x24(r1)
    mr r29, r3
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    beq BananaField_CheckCollision_L_80196D80
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    beq BananaField_CheckCollision_L_80196D80
    lwz r0, 0x8(r29)
    cmpwi r0, 0x0
    bne BananaField_CheckCollision_L_80196CA4
    b BananaField_CheckCollision_L_80196D80
    BananaField_CheckCollision_L_80196CA4:
    li r0, 0x0
    stb r0, 0xc(r29)
    lwz r31, 0x4(r29)
    b BananaField_CheckCollision_L_80196D68
    BananaField_CheckCollision_L_80196CB4:
    lwz r0, 0x0(r31)
    cmpwi r0, 0x0
    bne BananaField_CheckCollision_L_80196D34
    lfs f0, 0x4(r31)
    mr r4, r30
    lfs f1, lbl_806D95D0(r2)
    addi r5, r1, 0x8
    stfs f0, 0x8(r1)
    lwz r3, g_characterId(r13)
    lfs f0, 0x8(r31)
    fadds f0, f1, f0
    stfs f0, 0xc(r1)
    lfs f0, 0xc(r31)
    stfs f0, 0x10(r1)
    bl BananaField_TestHitBox
    clrlwi. r0, r3, 24
    beq BananaField_CheckCollision_L_80196D64
    li r0, 0x1
    lfs f0, lbl_806D95B8(r2)
    stb r0, 0xc(r29)
    stw r0, 0x0(r31)
    stfs f0, 0x14(r31)
    lfs f3, 0xc(r30)
    lfs f1, 0x4(r31)
    lfs f2, 0x2c(r30)
    lfs f0, 0xc(r31)
    fsubs f1, f3, f1
    fsubs f2, f2, f0
    bl Atan2
    frsp f0, f1
    stfs f0, 0x10(r31)
    b BananaField_CheckCollision_L_80196D64
    BananaField_CheckCollision_L_80196D34:
    cmpwi r0, 0x1
    bne BananaField_CheckCollision_L_80196D64
    lfs f2, 0x14(r31)
    lfs f1, lbl_806D95BC(r2)
    lfs f0, lbl_806D95D8(r2)
    fadds f1, f2, f1
    stfs f1, 0x14(r31)
    lfs f1, 0x14(r31)
    fcmpo cr0, f1, f0
    ble BananaField_CheckCollision_L_80196D64
    li r0, 0x2
    stw r0, 0x0(r31)
    BananaField_CheckCollision_L_80196D64:
    addi r31, r31, 0x18
    BananaField_CheckCollision_L_80196D68:
    lwz r0, 0x8(r29)
    lwz r3, 0x4(r29)
    mulli r0, r0, 0x18
    add r0, r3, r0
    cmplw r31, r0
    blt BananaField_CheckCollision_L_80196CB4
    BananaField_CheckCollision_L_80196D80:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
