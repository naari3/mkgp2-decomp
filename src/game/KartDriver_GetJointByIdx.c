/* === extracted from auto_KartDriver_GetJointB_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_802D1E34();

/* --- function index (1 fns, .text 0x80040E9C..0x80041748) ---
 * [  0] 0x80040E9C size:0x8AC   global KartDriver_GetJointByIdx
 */

/* --- forward decls --- */
asm void KartDriver_GetJointByIdx(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_GetJointByIdx[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_GetJointByIdx = {
    (void *)&KartDriver_GetJointByIdx, 0x000008AC, (void *)extab_KartDriver_GetJointByIdx
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_GetJointByIdx(void) { /* 0x80040E9C size:0x8AC */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r4, 0x0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    bne KartDriver_GetJointByIdx_L_80040F2C
    lwz r31, 0xe8(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80040EC8
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80040EC8:
    bne KartDriver_GetJointByIdx_L_80040EDC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80040EDC:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80040F24
    bne KartDriver_GetJointByIdx_L_80040EF8
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80040EF8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80040F14
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80040F14
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80040F14:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80040F24
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80040F24:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80040F2C:
    cmpwi r4, 0x1
    bne KartDriver_GetJointByIdx_L_80040FAC
    lwz r31, 0xec(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80040F48
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80040F48:
    bne KartDriver_GetJointByIdx_L_80040F5C
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80040F5C:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80040FA4
    bne KartDriver_GetJointByIdx_L_80040F78
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80040F78:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80040F94
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80040F94
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80040F94:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80040FA4
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80040FA4:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80040FAC:
    cmpwi r4, 0x2
    bne KartDriver_GetJointByIdx_L_8004102C
    lwz r31, 0xf0(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80040FC8
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80040FC8:
    bne KartDriver_GetJointByIdx_L_80040FDC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80040FDC:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041024
    bne KartDriver_GetJointByIdx_L_80040FF8
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80040FF8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041014
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041014
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041014:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80041024
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80041024:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_8004102C:
    cmpwi r4, 0x3
    bne KartDriver_GetJointByIdx_L_800410AC
    lwz r31, 0xf4(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80041048
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80041048:
    bne KartDriver_GetJointByIdx_L_8004105C
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_8004105C:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_800410A4
    bne KartDriver_GetJointByIdx_L_80041078
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80041078:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041094
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041094
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041094:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_800410A4
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_800410A4:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800410AC:
    cmpwi r4, 0x4
    bne KartDriver_GetJointByIdx_L_8004112C
    lwz r31, 0xf8(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_800410C8
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800410C8:
    bne KartDriver_GetJointByIdx_L_800410DC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800410DC:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041124
    bne KartDriver_GetJointByIdx_L_800410F8
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800410F8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041114
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041114
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041114:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80041124
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80041124:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_8004112C:
    cmpwi r4, 0x5
    bne KartDriver_GetJointByIdx_L_800411AC
    lwz r31, 0xfc(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80041148
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80041148:
    bne KartDriver_GetJointByIdx_L_8004115C
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_8004115C:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_800411A4
    bne KartDriver_GetJointByIdx_L_80041178
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80041178:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041194
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041194
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041194:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_800411A4
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_800411A4:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800411AC:
    cmpwi r4, 0x6
    bne KartDriver_GetJointByIdx_L_8004122C
    lwz r31, 0x100(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_800411C8
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800411C8:
    bne KartDriver_GetJointByIdx_L_800411DC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800411DC:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041224
    bne KartDriver_GetJointByIdx_L_800411F8
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800411F8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041214
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041214
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041214:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80041224
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80041224:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_8004122C:
    cmpwi r4, 0x7
    bne KartDriver_GetJointByIdx_L_800412AC
    lwz r31, 0x104(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80041248
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80041248:
    bne KartDriver_GetJointByIdx_L_8004125C
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_8004125C:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_800412A4
    bne KartDriver_GetJointByIdx_L_80041278
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80041278:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041294
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041294
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041294:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_800412A4
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_800412A4:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800412AC:
    cmpwi r4, 0x8
    bne KartDriver_GetJointByIdx_L_8004132C
    lwz r31, 0x10c(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_800412C8
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800412C8:
    bne KartDriver_GetJointByIdx_L_800412DC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800412DC:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041324
    bne KartDriver_GetJointByIdx_L_800412F8
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800412F8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041314
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041314
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041314:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80041324
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80041324:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_8004132C:
    cmpwi r4, 0x9
    bne KartDriver_GetJointByIdx_L_800413AC
    lwz r31, 0x110(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80041348
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80041348:
    bne KartDriver_GetJointByIdx_L_8004135C
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_8004135C:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_800413A4
    bne KartDriver_GetJointByIdx_L_80041378
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80041378:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041394
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041394
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041394:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_800413A4
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_800413A4:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800413AC:
    cmpwi r4, 0xc
    bne KartDriver_GetJointByIdx_L_8004142C
    lwz r31, 0x11c(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_800413C8
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800413C8:
    bne KartDriver_GetJointByIdx_L_800413DC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800413DC:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041424
    bne KartDriver_GetJointByIdx_L_800413F8
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800413F8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041414
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041414
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041414:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80041424
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80041424:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_8004142C:
    cmpwi r4, 0xd
    bne KartDriver_GetJointByIdx_L_800414AC
    lwz r31, 0x120(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80041448
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80041448:
    bne KartDriver_GetJointByIdx_L_8004145C
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_8004145C:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_800414A4
    bne KartDriver_GetJointByIdx_L_80041478
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80041478:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041494
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041494
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041494:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_800414A4
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_800414A4:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800414AC:
    cmpwi r4, 0xe
    bne KartDriver_GetJointByIdx_L_8004152C
    lwz r31, 0x124(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_800414C8
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800414C8:
    bne KartDriver_GetJointByIdx_L_800414DC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800414DC:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041524
    bne KartDriver_GetJointByIdx_L_800414F8
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800414F8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041514
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041514
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041514:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80041524
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80041524:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_8004152C:
    cmpwi r4, 0xf
    bne KartDriver_GetJointByIdx_L_800415AC
    lwz r31, 0x128(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_80041548
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80041548:
    bne KartDriver_GetJointByIdx_L_8004155C
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_8004155C:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_800415A4
    bne KartDriver_GetJointByIdx_L_80041578
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80041578:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041594
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041594
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041594:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_800415A4
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_800415A4:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800415AC:
    cmpwi r4, 0x10
    bne KartDriver_GetJointByIdx_L_80041630
    lwz r31, 0x12c(r3)
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041630
    bne KartDriver_GetJointByIdx_L_800415CC
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800415CC:
    bne KartDriver_GetJointByIdx_L_800415E0
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800415E0:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041628
    bne KartDriver_GetJointByIdx_L_800415FC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800415FC:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041618
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041618
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041618:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80041628
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80041628:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80041630:
    cmpwi r4, 0xa
    bne KartDriver_GetJointByIdx_L_800416B0
    lwz r31, 0x114(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_8004164C
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_8004164C:
    bne KartDriver_GetJointByIdx_L_80041660
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_80041660:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_800416A8
    bne KartDriver_GetJointByIdx_L_8004167C
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_8004167C:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041698
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041698
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041698:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_800416A8
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_800416A8:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800416B0:
    cmpwi r4, 0xb
    bne KartDriver_GetJointByIdx_L_80041730
    lwz r31, 0x118(r3)
    cmplwi r31, 0x0
    bne KartDriver_GetJointByIdx_L_800416CC
    li r3, 0x0
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_800416CC:
    bne KartDriver_GetJointByIdx_L_800416E0
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x47c
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800416E0:
    cmplwi r31, 0x0
    beq KartDriver_GetJointByIdx_L_80041728
    bne KartDriver_GetJointByIdx_L_800416FC
    addi r3, r2, -0x7D18  /* lbl_806D2548 */
    li r4, 0x25d
    addi r5, r2, -0x7D10  /* lbl_806D2550 */
    bl __assert
    KartDriver_GetJointByIdx_L_800416FC:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_GetJointByIdx_L_80041718
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_GetJointByIdx_L_80041718
    li r3, 0x1
    KartDriver_GetJointByIdx_L_80041718:
    clrlwi. r0, r3, 24
    beq KartDriver_GetJointByIdx_L_80041728
    mr r3, r31
    bl fn_802D1E34
    KartDriver_GetJointByIdx_L_80041728:
    addi r3, r31, 0x44
    b KartDriver_GetJointByIdx_L_80041734
    KartDriver_GetJointByIdx_L_80041730:
    li r3, 0x0
    KartDriver_GetJointByIdx_L_80041734:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

