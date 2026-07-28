/* === extracted from auto_GXChannel_PushChanne_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_80266774();
extern void fn_80269230();
extern void fn_80269328();
extern void fn_802C14B8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2FB8;
extern unsigned int lbl_806D2FC0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80311C68[];
extern unsigned int lbl_803FE0E0[];

/* --- function index (1 fns, .text 0x8007D2AC..0x8007D7BC) ---
 * [  0] 0x8007D2AC size:0x510   global GXChannel_PushChannelColors
 */

/* --- forward decls --- */
asm void GXChannel_PushChannelColors(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GXChannel_PushChannelColors[8] = {
    0x30, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GXChannel_PushChannelColors = {
    (void *)&GXChannel_PushChannelColors, 0x00000510, (void *)extab_GXChannel_PushChannelColors
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GXChannel_PushChannelColors(void) { /* 0x8007D2AC size:0x510 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    lis r4, lbl_80311C68@ha
    stw r0, 0x74(r1)
    stmw r26, 0x58(r1)
    mr r29, r3
    addi r31, r4, lbl_80311C68@l
    li r30, 0x0
    b GXChannel_PushChannelColors_L_8007D6F8
    GXChannel_PushChannelColors_L_8007D2D0:
    lwz r0, 0x0(r29)
    cmpwi r0, 0x4
    beq GXChannel_PushChannelColors_L_8007D2EC
    addi r3, r31, 0xc
    addi r5, r31, 0x18
    li r4, 0x368
    bl __assert
    GXChannel_PushChannelColors_L_8007D2EC:
    lbz r5, 0xe(r29)
    cmplwi r5, 0x8
    bge GXChannel_PushChannelColors_L_8007D6F4
    lbz r0, 0xc(r29)
    li r3, 0x1
    slw r3, r3, r5
    cmplwi r0, 0x1
    or r30, r30, r3
    bne GXChannel_PushChannelColors_L_8007D538
    lbz r0, 0xd(r29)
    cmpwi r0, 0x1
    beq GXChannel_PushChannelColors_L_8007D3F4
    bge GXChannel_PushChannelColors_L_8007D32C
    cmpwi r0, 0x0
    bge GXChannel_PushChannelColors_L_8007D338
    b GXChannel_PushChannelColors_L_8007D3F4
    GXChannel_PushChannelColors_L_8007D32C:
    cmpwi r0, 0x3
    bge GXChannel_PushChannelColors_L_8007D3F4
    b GXChannel_PushChannelColors_L_8007D37C
    GXChannel_PushChannelColors_L_8007D338:
    lwz r4, 0x8(r29)
    slwi r5, r5, 2
    addi r3, r1, 0x14
    lwz r6, 0x0(r4)
    addi r0, r5, 0x3
    lbzx r4, r3, r0
    add r5, r3, r5
    stw r6, 0x10(r1)
    lbz r0, 0x10(r1)
    lbz r3, 0x11(r1)
    stb r0, 0x0(r5)
    lbz r0, 0x12(r1)
    stb r3, 0x1(r5)
    stb r0, 0x2(r5)
    stb r4, 0x13(r1)
    stb r4, 0x3(r5)
    b GXChannel_PushChannelColors_L_8007D6F4
    GXChannel_PushChannelColors_L_8007D37C:
    lwz r8, 0x8(r29)
    li r4, 0xff
    lwz r0, 0x0(r8)
    cmplwi r0, 0x100
    bge GXChannel_PushChannelColors_L_8007D394
    mr r4, r0
    GXChannel_PushChannelColors_L_8007D394:
    lwz r7, 0x4(r8)
    clrlslwi r0, r5, 24, 2
    addi r3, r1, 0x14
    li r6, 0xff
    cmplwi r7, 0x100
    stbx r4, r3, r0
    bge GXChannel_PushChannelColors_L_8007D3B4
    mr r6, r7
    GXChannel_PushChannelColors_L_8007D3B4:
    lbz r0, 0xe(r29)
    addi r3, r1, 0x14
    lwz r7, 0x8(r8)
    li r5, 0xff
    slwi r4, r0, 2
    addi r0, r4, 0x1
    cmplwi r7, 0x100
    stbx r6, r3, r0
    bge GXChannel_PushChannelColors_L_8007D3DC
    mr r5, r7
    GXChannel_PushChannelColors_L_8007D3DC:
    lbz r0, 0xe(r29)
    addi r3, r1, 0x14
    slwi r4, r0, 2
    addi r0, r4, 0x2
    stbx r5, r3, r0
    b GXChannel_PushChannelColors_L_8007D6F4
    GXChannel_PushChannelColors_L_8007D3F4:
    cmpwi r0, 0x2
    beq GXChannel_PushChannelColors_L_8007D474
    bge GXChannel_PushChannelColors_L_8007D40C
    cmpwi r0, 0x1
    bge GXChannel_PushChannelColors_L_8007D418
    b GXChannel_PushChannelColors_L_8007D474
    GXChannel_PushChannelColors_L_8007D40C:
    cmpwi r0, 0x4
    bge GXChannel_PushChannelColors_L_8007D474
    b GXChannel_PushChannelColors_L_8007D42C
    GXChannel_PushChannelColors_L_8007D418:
    lwz r4, 0x8(r29)
    lhz r3, 0x0(r4)
    lhz r6, 0x2(r4)
    lhz r7, 0x4(r4)
    b GXChannel_PushChannelColors_L_8007D4B8
    GXChannel_PushChannelColors_L_8007D42C:
    lwz r3, 0x8(r29)
    lfs f3, lbl_806D2FB8(r2)
    lfs f2, 0x0(r3)
    lfs f1, 0x4(r3)
    lfs f0, 0x8(r3)
    fmuls f2, f3, f2
    fmuls f1, f3, f1
    fmuls f0, f3, f0
    fctiwz f2, f2
    fctiwz f1, f1
    fctiwz f0, f0
    stfd f2, 0x38(r1)
    stfd f1, 0x40(r1)
    lwz r3, 0x3c(r1)
    stfd f0, 0x48(r1)
    lwz r6, 0x44(r1)
    lwz r7, 0x4c(r1)
    b GXChannel_PushChannelColors_L_8007D4B8
    GXChannel_PushChannelColors_L_8007D474:
    lwz r3, 0x8(r29)
    lfd f3, lbl_806D2FC0(r2)
    lfd f2, 0x0(r3)
    lfd f1, 0x8(r3)
    lfd f0, 0x10(r3)
    fmul f2, f3, f2
    fmul f1, f3, f1
    fmul f0, f3, f0
    fctiwz f2, f2
    fctiwz f1, f1
    fctiwz f0, f0
    stfd f2, 0x48(r1)
    stfd f1, 0x40(r1)
    lwz r3, 0x4c(r1)
    stfd f0, 0x38(r1)
    lwz r6, 0x44(r1)
    lwz r7, 0x3c(r1)
    GXChannel_PushChannelColors_L_8007D4B8:
    cmpwi r3, 0xff
    ble GXChannel_PushChannelColors_L_8007D4C8
    li r4, 0xff
    b GXChannel_PushChannelColors_L_8007D4D0
    GXChannel_PushChannelColors_L_8007D4C8:
    srawi r0, r3, 31
    andc r4, r3, r0
    GXChannel_PushChannelColors_L_8007D4D0:
    cmpwi r6, 0xff
    clrlslwi r0, r5, 24, 2
    addi r3, r1, 0x14
    stbx r4, r3, r0
    ble GXChannel_PushChannelColors_L_8007D4EC
    li r5, 0xff
    b GXChannel_PushChannelColors_L_8007D4F4
    GXChannel_PushChannelColors_L_8007D4EC:
    srawi r0, r6, 31
    andc r5, r6, r0
    GXChannel_PushChannelColors_L_8007D4F4:
    lbz r0, 0xe(r29)
    cmpwi r7, 0xff
    addi r3, r1, 0x14
    slwi r4, r0, 2
    addi r0, r4, 0x1
    stbx r5, r3, r0
    ble GXChannel_PushChannelColors_L_8007D518
    li r5, 0xff
    b GXChannel_PushChannelColors_L_8007D520
    GXChannel_PushChannelColors_L_8007D518:
    srawi r0, r7, 31
    andc r5, r7, r0
    GXChannel_PushChannelColors_L_8007D520:
    lbz r0, 0xe(r29)
    addi r3, r1, 0x14
    slwi r4, r0, 2
    addi r0, r4, 0x2
    stbx r5, r3, r0
    b GXChannel_PushChannelColors_L_8007D6F4
    GXChannel_PushChannelColors_L_8007D538:
    lbz r0, 0xd(r29)
    cmpwi r0, 0x2
    beq GXChannel_PushChannelColors_L_8007D598
    bge GXChannel_PushChannelColors_L_8007D558
    cmpwi r0, 0x0
    beq GXChannel_PushChannelColors_L_8007D564
    bge GXChannel_PushChannelColors_L_8007D570
    b GXChannel_PushChannelColors_L_8007D5FC
    GXChannel_PushChannelColors_L_8007D558:
    cmpwi r0, 0x4
    bge GXChannel_PushChannelColors_L_8007D5FC
    b GXChannel_PushChannelColors_L_8007D5C0
    GXChannel_PushChannelColors_L_8007D564:
    lwz r3, 0x8(r29)
    lbz r6, 0x0(r3)
    b GXChannel_PushChannelColors_L_8007D634
    GXChannel_PushChannelColors_L_8007D570:
    lwz r3, 0x8(r29)
    lhz r3, 0x0(r3)
    cmpwi r3, 0xff
    ble GXChannel_PushChannelColors_L_8007D588
    li r0, 0xff
    b GXChannel_PushChannelColors_L_8007D590
    GXChannel_PushChannelColors_L_8007D588:
    srawi r0, r3, 31
    andc r0, r3, r0
    GXChannel_PushChannelColors_L_8007D590:
    clrlwi r6, r0, 24
    b GXChannel_PushChannelColors_L_8007D634
    GXChannel_PushChannelColors_L_8007D598:
    lwz r3, 0x8(r29)
    lwz r3, 0x0(r3)
    cmpwi r3, 0xff
    ble GXChannel_PushChannelColors_L_8007D5B0
    li r0, 0xff
    b GXChannel_PushChannelColors_L_8007D5B8
    GXChannel_PushChannelColors_L_8007D5B0:
    srawi r0, r3, 31
    andc r0, r3, r0
    GXChannel_PushChannelColors_L_8007D5B8:
    clrlwi r6, r0, 24
    b GXChannel_PushChannelColors_L_8007D634
    GXChannel_PushChannelColors_L_8007D5C0:
    lwz r3, 0x8(r29)
    lfs f1, lbl_806D2FB8(r2)
    lfs f0, 0x0(r3)
    fmuls f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x48(r1)
    lwz r3, 0x4c(r1)
    cmpwi r3, 0xff
    ble GXChannel_PushChannelColors_L_8007D5EC
    li r0, 0xff
    b GXChannel_PushChannelColors_L_8007D5F4
    GXChannel_PushChannelColors_L_8007D5EC:
    srawi r0, r3, 31
    andc r0, r3, r0
    GXChannel_PushChannelColors_L_8007D5F4:
    clrlwi r6, r0, 24
    b GXChannel_PushChannelColors_L_8007D634
    GXChannel_PushChannelColors_L_8007D5FC:
    lwz r3, 0x8(r29)
    lfd f1, lbl_806D2FC0(r2)
    lfd f0, 0x0(r3)
    fmul f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x48(r1)
    lwz r3, 0x4c(r1)
    cmpwi r3, 0xff
    ble GXChannel_PushChannelColors_L_8007D628
    li r0, 0xff
    b GXChannel_PushChannelColors_L_8007D630
    GXChannel_PushChannelColors_L_8007D628:
    srawi r0, r3, 31
    andc r0, r3, r0
    GXChannel_PushChannelColors_L_8007D630:
    clrlwi r6, r0, 24
    GXChannel_PushChannelColors_L_8007D634:
    cmplwi r5, 0x4
    bge GXChannel_PushChannelColors_L_8007D6B0
    lbz r0, 0xf(r29)
    cmpwi r0, 0x1
    beq GXChannel_PushChannelColors_L_8007D674
    bge GXChannel_PushChannelColors_L_8007D658
    cmpwi r0, 0x0
    bge GXChannel_PushChannelColors_L_8007D664
    b GXChannel_PushChannelColors_L_8007D69C
    GXChannel_PushChannelColors_L_8007D658:
    cmpwi r0, 0x3
    bge GXChannel_PushChannelColors_L_8007D69C
    b GXChannel_PushChannelColors_L_8007D688
    GXChannel_PushChannelColors_L_8007D664:
    clrlslwi r0, r5, 24, 2
    addi r3, r1, 0x14
    stbx r6, r3, r0
    b GXChannel_PushChannelColors_L_8007D6F4
    GXChannel_PushChannelColors_L_8007D674:
    clrlslwi r4, r5, 24, 2
    addi r3, r1, 0x14
    addi r0, r4, 0x1
    stbx r6, r3, r0
    b GXChannel_PushChannelColors_L_8007D6F4
    GXChannel_PushChannelColors_L_8007D688:
    clrlslwi r4, r5, 24, 2
    addi r3, r1, 0x14
    addi r0, r4, 0x2
    stbx r6, r3, r0
    b GXChannel_PushChannelColors_L_8007D6F4
    GXChannel_PushChannelColors_L_8007D69C:
    clrlslwi r4, r5, 24, 2
    addi r3, r1, 0x14
    addi r0, r4, 0x3
    stbx r6, r3, r0
    b GXChannel_PushChannelColors_L_8007D6F4
    GXChannel_PushChannelColors_L_8007D6B0:
    lbz r0, 0xf(r29)
    cmplwi r0, 0x3
    bne GXChannel_PushChannelColors_L_8007D6D0
    clrlslwi r4, r5, 24, 2
    addi r3, r1, 0x14
    addi r0, r4, 0x3
    stbx r6, r3, r0
    b GXChannel_PushChannelColors_L_8007D6F4
    GXChannel_PushChannelColors_L_8007D6D0:
    lbz r0, 0xe(r29)
    clrlslwi r5, r5, 24, 2
    addi r4, r1, 0x14
    slwi r3, r0, 2
    stbx r6, r4, r5
    addi r0, r3, 0x1
    stbx r6, r4, r0
    addi r0, r3, 0x2
    stbx r6, r4, r0
    GXChannel_PushChannelColors_L_8007D6F4:
    lwz r29, 0x4(r29)
    GXChannel_PushChannelColors_L_8007D6F8:
    cmplwi r29, 0x0
    bne GXChannel_PushChannelColors_L_8007D2D0
    cmplwi r30, 0x0
    beq GXChannel_PushChannelColors_L_8007D7A8
    bl fn_80266774
    lis r3, lbl_803FE0E0@ha
    addi r28, r1, 0x14
    addi r27, r3, lbl_803FE0E0@l
    li r26, 0x0
    li r29, 0x1
    GXChannel_PushChannelColors_L_8007D720:
    slw r0, r29, r26
    and. r0, r30, r0
    beq GXChannel_PushChannelColors_L_8007D740
    lwz r0, 0x0(r28)
    addi r4, r1, 0xc
    lwz r3, 0x0(r27)
    stw r0, 0xc(r1)
    bl fn_80269328
    GXChannel_PushChannelColors_L_8007D740:
    addi r26, r26, 0x1
    addi r27, r27, 0x4
    cmpwi r26, 0x4
    addi r28, r28, 0x4
    blt GXChannel_PushChannelColors_L_8007D720
    addi r28, r31, 0x0
    addi r27, r1, 0x24
    li r31, 0x4
    li r29, 0x1
    addi r28, r28, 0x10
    GXChannel_PushChannelColors_L_8007D768:
    slw r0, r29, r31
    and. r0, r30, r0
    beq GXChannel_PushChannelColors_L_8007D788
    lwz r0, 0x0(r27)
    addi r4, r1, 0x8
    stw r0, 0x8(r1)
    lwz r3, -0x10(r28)
    bl fn_80269230
    GXChannel_PushChannelColors_L_8007D788:
    addi r31, r31, 0x1
    addi r28, r28, 0x4
    cmpwi r31, 0x7
    addi r27, r27, 0x4
    blt GXChannel_PushChannelColors_L_8007D768
    li r3, 0x10
    bl fn_802C14B8
    bl fn_80266774
    GXChannel_PushChannelColors_L_8007D7A8:
    lmw r26, 0x58(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

