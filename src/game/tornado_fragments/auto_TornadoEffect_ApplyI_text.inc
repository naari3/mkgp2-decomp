/* === extracted from auto_TornadoEffect_ApplyI_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void TornadoEffect_ApplyItemVisual_Secondary();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10A8;
extern unsigned int lbl_806D28CC;
extern unsigned int lbl_806D28D0;
extern unsigned int lbl_806D28F8;
extern unsigned int lbl_806D2914;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803F9880[];

/* --- function index (1 fns, .text 0x80058534..0x80058994) ---
 * [  0] 0x80058534 size:0x460   global TornadoEffect_ApplyItemVisual_Primary
 */

/* --- forward decls --- */
asm void TornadoEffect_ApplyItemVisual_Primary(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_ApplyItemVisual_Primary[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_ApplyItemVisual_Primary = {
    (void *)&TornadoEffect_ApplyItemVisual_Primary, 0x00000460, (void *)extab_TornadoEffect_ApplyItemVisual_Primary
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_ApplyItemVisual_Primary(void) { /* 0x80058534 size:0x460 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    cmpwi r4, 0x120
    li r5, 0x0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    li r3, 0x0
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058588
    bge TornadoEffect_ApplyItemVisual_Primary_L_8005857C
    cmpwi r4, 0x36
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058584
    blt TornadoEffect_ApplyItemVisual_Primary_L_80058588
    cmpwi r4, 0x11e
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058584
    b TornadoEffect_ApplyItemVisual_Primary_L_80058588
    TornadoEffect_ApplyItemVisual_Primary_L_8005857C:
    cmpwi r4, 0x122
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058588
    TornadoEffect_ApplyItemVisual_Primary_L_80058584:
    li r3, 0x6
    TornadoEffect_ApplyItemVisual_Primary_L_80058588:
    cmpwi r3, 0x0
    bne TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    cmpwi r4, 0x36
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058788
    bge TornadoEffect_ApplyItemVisual_Primary_L_8005866C
    cmpwi r4, 0x1a
    beq TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058610
    cmpwi r4, 0x11
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058778
    bge TornadoEffect_ApplyItemVisual_Primary_L_800585E4
    cmpwi r4, 0xe
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058770
    bge TornadoEffect_ApplyItemVisual_Primary_L_800585D8
    cmpwi r4, 0x8
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058798
    blt TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    cmpwi r4, 0xc
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058778
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_800585D8:
    cmpwi r4, 0x10
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058770
    b TornadoEffect_ApplyItemVisual_Primary_L_80058778
    TornadoEffect_ApplyItemVisual_Primary_L_800585E4:
    cmpwi r4, 0x17
    beq TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058604
    cmpwi r4, 0x15
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058770
    cmpwi r4, 0x13
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058778
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058604:
    cmpwi r4, 0x19
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058738
    b TornadoEffect_ApplyItemVisual_Primary_L_80058778
    TornadoEffect_ApplyItemVisual_Primary_L_80058610:
    cmpwi r4, 0x24
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058770
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058644
    cmpwi r4, 0x1d
    beq TornadoEffect_ApplyItemVisual_Primary_L_800587A0
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058634
    cmpwi r4, 0x1c
    bge TornadoEffect_ApplyItemVisual_Primary_L_800587A8
    b TornadoEffect_ApplyItemVisual_Primary_L_80058780
    TornadoEffect_ApplyItemVisual_Primary_L_80058634:
    cmpwi r4, 0x21
    beq TornadoEffect_ApplyItemVisual_Primary_L_800587A8
    bge TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    b TornadoEffect_ApplyItemVisual_Primary_L_80058770
    TornadoEffect_ApplyItemVisual_Primary_L_80058644:
    cmpwi r4, 0x2b
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058788
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058660
    cmpwi r4, 0x28
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058770
    bge TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    b TornadoEffect_ApplyItemVisual_Primary_L_80058778
    TornadoEffect_ApplyItemVisual_Primary_L_80058660:
    cmpwi r4, 0x2d
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058788
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_8005866C:
    cmpwi r4, 0x6b
    beq TornadoEffect_ApplyItemVisual_Primary_L_800587B0
    bge TornadoEffect_ApplyItemVisual_Primary_L_800586DC
    cmpwi r4, 0x52
    beq TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    bge TornadoEffect_ApplyItemVisual_Primary_L_800586B4
    cmpwi r4, 0x4a
    bge TornadoEffect_ApplyItemVisual_Primary_L_800586A0
    cmpwi r4, 0x48
    bge TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    cmpwi r4, 0x46
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058788
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_800586A0:
    cmpwi r4, 0x51
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058730
    cmpwi r4, 0x4c
    bge TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    b TornadoEffect_ApplyItemVisual_Primary_L_80058788
    TornadoEffect_ApplyItemVisual_Primary_L_800586B4:
    cmpwi r4, 0x5e
    bge TornadoEffect_ApplyItemVisual_Primary_L_800586D0
    cmpwi r4, 0x5b
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058788
    cmpwi r4, 0x54
    bge TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    b TornadoEffect_ApplyItemVisual_Primary_L_80058790
    TornadoEffect_ApplyItemVisual_Primary_L_800586D0:
    cmpwi r4, 0x67
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058730
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_800586DC:
    cmpwi r4, 0x117
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058730
    bge TornadoEffect_ApplyItemVisual_Primary_L_8005870C
    cmpwi r4, 0x98
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058754
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058700
    cmpwi r4, 0x92
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058738
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058700:
    cmpwi r4, 0x116
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058798
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_8005870C:
    cmpwi r4, 0x11c
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058798
    bge TornadoEffect_ApplyItemVisual_Primary_L_80058728
    cmpwi r4, 0x119
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058730
    bge TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    b TornadoEffect_ApplyItemVisual_Primary_L_80058798
    TornadoEffect_ApplyItemVisual_Primary_L_80058728:
    cmpwi r4, 0x11e
    bge TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058730:
    li r3, 0x6
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058738:
    li r0, 0x2
    lfs f0, lbl_806D28CC(r2)
    stw r0, 0xd4(r31)
    stfs f0, 0xe0(r31)
    stfs f0, 0xe4(r31)
    stfs f0, 0xe8(r31)
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058754:
    li r0, 0x3
    lfs f0, lbl_806D28CC(r2)
    stw r0, 0xd4(r31)
    stfs f0, 0xe0(r31)
    stfs f0, 0xe4(r31)
    stfs f0, 0xe8(r31)
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058770:
    li r3, 0x2
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058778:
    li r3, 0x5
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058780:
    li r3, 0x4
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058788:
    li r3, 0x6
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058790:
    li r3, 0x5
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_80058798:
    li r3, 0x1
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_800587A0:
    li r5, 0x9
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_800587A8:
    li r5, 0xa
    b TornadoEffect_ApplyItemVisual_Primary_L_800587C8
    TornadoEffect_ApplyItemVisual_Primary_L_800587B0:
    li r0, 0x2
    lfs f0, lbl_806D28CC(r2)
    stw r0, 0xd4(r31)
    stfs f0, 0xe0(r31)
    stfs f0, 0xe4(r31)
    stfs f0, 0xe8(r31)
    TornadoEffect_ApplyItemVisual_Primary_L_800587C8:
    cmpwi r3, 0x0
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058830
    cmpwi r3, 0x6
    bne TornadoEffect_ApplyItemVisual_Primary_L_80058828
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    bne TornadoEffect_ApplyItemVisual_Primary_L_800587EC
    li r0, 0x0
    stw r0, 0x104(r31)
    TornadoEffect_ApplyItemVisual_Primary_L_800587EC:
    li r0, 0x1
    lfs f0, lbl_806D28CC(r2)
    stw r0, 0x104(r31)
    stfs f0, 0x108(r31)
    lfs f1, 0x108(r31)
    lfs f0, 0x10c(r31)
    fcmpo cr0, f1, f0
    ble TornadoEffect_ApplyItemVisual_Primary_L_80058818
    lfs f0, lbl_806D28D0(r2)
    stfs f0, 0x110(r31)
    b TornadoEffect_ApplyItemVisual_Primary_L_80058820
    TornadoEffect_ApplyItemVisual_Primary_L_80058818:
    lfs f0, lbl_806D28F8(r2)
    stfs f0, 0x110(r31)
    TornadoEffect_ApplyItemVisual_Primary_L_80058820:
    li r0, 0x0
    stb r0, 0x12c(r31)
    TornadoEffect_ApplyItemVisual_Primary_L_80058828:
    li r0, 0x0
    stw r0, 0x124(r31)
    TornadoEffect_ApplyItemVisual_Primary_L_80058830:
    cmpwi r5, 0x0
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058840
    li r0, 0x0
    stw r0, 0x128(r31)
    TornadoEffect_ApplyItemVisual_Primary_L_80058840:
    lwz r0, 0x14c(r31)
    cmpw r4, r0
    bne TornadoEffect_ApplyItemVisual_Primary_L_80058858
    li r0, -0x1
    stw r0, 0x14c(r31)
    b TornadoEffect_ApplyItemVisual_Primary_L_80058860
    TornadoEffect_ApplyItemVisual_Primary_L_80058858:
    li r0, -0x1
    stw r0, 0x150(r31)
    TornadoEffect_ApplyItemVisual_Primary_L_80058860:
    lwz r29, 0x14c(r31)
    cmpwi r29, -0x1
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058960
    subf r0, r29, r29
    cntlzw r0, r0
    extrwi r30, r0, 8, 19
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058888
    mr r3, r31
    mr r4, r29
    bl TornadoEffect_ApplyItemVisual_Primary
    TornadoEffect_ApplyItemVisual_Primary_L_80058888:
    subi r0, r29, 0xc
    li r5, 0x0
    cmplwi r0, 0x1c
    stw r29, 0x14c(r31)
    mr r4, r5
    bgt TornadoEffect_ApplyItemVisual_Primary_L_80058918
    lis r3, jumptable_803F9880@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_803F9880@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    cmplwi r30, 0x0
    bne TornadoEffect_ApplyItemVisual_Primary_L_80058918
    li r0, 0x2
    lfs f0, lbl_806D2914(r2)
    stw r0, 0xd4(r31)
    stfs f0, 0xe0(r31)
    stfs f0, 0xe4(r31)
    stfs f0, 0xe8(r31)
    b TornadoEffect_ApplyItemVisual_Primary_L_80058918
    li r5, 0x4
    b TornadoEffect_ApplyItemVisual_Primary_L_80058918
    li r5, 0x2
    b TornadoEffect_ApplyItemVisual_Primary_L_80058918
    li r5, 0x5
    b TornadoEffect_ApplyItemVisual_Primary_L_80058918
    lwz r3, lbl_806D10A8(r13)
    li r4, 0x9
    addi r0, r3, 0x1
    stw r0, lbl_806D10A8(r13)
    b TornadoEffect_ApplyItemVisual_Primary_L_80058918
    lwz r3, lbl_806D10A8(r13)
    li r4, 0xa
    addi r0, r3, 0x1
    stw r0, lbl_806D10A8(r13)
    TornadoEffect_ApplyItemVisual_Primary_L_80058918:
    cmpwi r5, 0x0
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058944
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058944
    li r0, 0x0
    stw r0, 0x130(r31)
    stw r5, 0x124(r31)
    lwz r0, 0x124(r31)
    cmpwi r0, 0x6
    bne TornadoEffect_ApplyItemVisual_Primary_L_80058944
    li r0, 0x1
    stb r0, 0x12c(r31)
    TornadoEffect_ApplyItemVisual_Primary_L_80058944:
    cmpwi r4, 0x0
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058978
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058978
    li r0, 0x0
    stw r0, 0x134(r31)
    stw r4, 0x128(r31)
    b TornadoEffect_ApplyItemVisual_Primary_L_80058978
    TornadoEffect_ApplyItemVisual_Primary_L_80058960:
    lwz r4, 0x150(r31)
    cmpwi r4, -0x1
    beq TornadoEffect_ApplyItemVisual_Primary_L_80058978
    mr r3, r31
    li r5, 0x1
    bl TornadoEffect_ApplyItemVisual_Secondary
    TornadoEffect_ApplyItemVisual_Primary_L_80058978:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

