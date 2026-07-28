/* === extracted from auto_TornadoEffect_ApplyI_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Object_SetColorAlphaOnly();
extern void Object_SetJObjPositionXYZ();
extern void TornadoEffect_ApplyItemVisual_Primary();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D28D0;
extern unsigned int lbl_806D28D4;
extern unsigned int lbl_806D28D8;
extern unsigned int lbl_806D28F4;
extern unsigned int lbl_806D2900;
extern unsigned int lbl_806D2938;

/* --- function index (1 fns, .text 0x80058994..0x80058C80) ---
 * [  0] 0x80058994 size:0x2EC   global TornadoEffect_ApplyItemVisual_Secondary
 */

/* --- forward decls --- */
asm void TornadoEffect_ApplyItemVisual_Secondary(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_ApplyItemVisual_Secondary[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_ApplyItemVisual_Secondary = {
    (void *)&TornadoEffect_ApplyItemVisual_Secondary, 0x000002EC, (void *)extab_TornadoEffect_ApplyItemVisual_Secondary
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_ApplyItemVisual_Secondary(void) { /* 0x80058994 size:0x2EC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r27, r4
    mr r28, r5
    mr r31, r3
    lwz r4, 0x150(r3)
    subf r0, r27, r4
    cmpwi r4, -0x1
    cntlzw r0, r0
    srwi r5, r0, 5
    neg r0, r5
    or r0, r0, r5
    srwi r30, r0, 31
    beq TornadoEffect_ApplyItemVisual_Secondary_L_800589D8
    bl TornadoEffect_ApplyItemVisual_Primary
    TornadoEffect_ApplyItemVisual_Secondary_L_800589D8:
    cmpwi r27, 0x120
    stw r27, 0x150(r31)
    li r29, 0x0
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058A10
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058A04
    cmpwi r27, 0x36
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058A0C
    blt TornadoEffect_ApplyItemVisual_Secondary_L_80058A10
    cmpwi r27, 0x11e
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058A0C
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058A10
    TornadoEffect_ApplyItemVisual_Secondary_L_80058A04:
    cmpwi r27, 0x122
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058A10
    TornadoEffect_ApplyItemVisual_Secondary_L_80058A0C:
    li r29, 0x6
    TornadoEffect_ApplyItemVisual_Secondary_L_80058A10:
    cmpwi r29, 0x0
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    cmpwi r27, 0x5b
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B7C
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058AAC
    cmpwi r27, 0x48
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058A68
    cmpwi r27, 0x2d
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B7C
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058A50
    cmpwi r27, 0x2b
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B7C
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    cmpwi r27, 0x8
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B84
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058A50:
    cmpwi r27, 0x36
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B7C
    blt TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    cmpwi r27, 0x46
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058B7C
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058A68:
    cmpwi r27, 0x50
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058A94
    cmpwi r27, 0x4c
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058A88
    cmpwi r27, 0x4a
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058B7C
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058A88:
    cmpwi r27, 0x4f
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058BB0
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058A94:
    cmpwi r27, 0x53
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B74
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    cmpwi r27, 0x52
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058B6C
    TornadoEffect_ApplyItemVisual_Secondary_L_80058AAC:
    cmpwi r27, 0x95
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058AEC
    cmpwi r27, 0x6b
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058C00
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058AE0
    cmpwi r27, 0x67
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B6C
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    cmpwi r27, 0x5d
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B54
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058B28
    TornadoEffect_ApplyItemVisual_Secondary_L_80058AE0:
    cmpwi r27, 0x92
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B8C
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058AEC:
    cmpwi r27, 0x119
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B6C
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058B10
    cmpwi r27, 0x117
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B6C
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058B84
    cmpwi r27, 0x116
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058B84
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B10:
    cmpwi r27, 0x11d
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058B6C
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    cmpwi r27, 0x11c
    bge TornadoEffect_ApplyItemVisual_Secondary_L_80058B84
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B28:
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058B4C
    cmplwi r30, 0x0
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058B4C
    li r0, 0x2
    lfs f0, lbl_806D28D0(r2)
    stw r0, 0x104(r31)
    stfs f0, 0x110(r31)
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B4C:
    li r29, 0x6
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B54:
    cmplwi r30, 0x0
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058B64
    lfs f0, lbl_806D2938(r2)
    stfs f0, 0x10c(r31)
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B64:
    li r29, 0x6
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B6C:
    li r29, 0x6
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B74:
    li r29, 0x5
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B7C:
    li r29, 0x6
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B84:
    li r29, 0x1
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058B8C:
    cmplwi r30, 0x0
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    li r0, 0x2
    lfs f0, lbl_806D28F4(r2)
    stw r0, 0xd4(r31)
    stfs f0, 0xe0(r31)
    stfs f0, 0xe4(r31)
    stfs f0, 0xe8(r31)
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058BB0:
    lwz r3, 0xa8(r31)
    lfs f1, 0x4c(r31)
    lfs f2, 0x50(r31)
    lfs f3, 0x54(r31)
    bl Object_SetJObjPositionXYZ
    lbz r0, 0x8(r31)
    cmplwi r0, 0x1
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058BE4
    lwz r3, 0xa8(r31)
    li r4, 0x0
    lfs f1, lbl_806D28D4(r2)
    bl Object_SetColorAlphaOnly
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058BF4
    TornadoEffect_ApplyItemVisual_Secondary_L_80058BE4:
    lwz r3, 0xa8(r31)
    li r4, 0x0
    lfs f1, lbl_806D28D8(r2)
    bl Object_SetColorAlphaOnly
    TornadoEffect_ApplyItemVisual_Secondary_L_80058BF4:
    li r0, 0x3c
    stw r0, 0x100(r31)
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    TornadoEffect_ApplyItemVisual_Secondary_L_80058C00:
    cmplwi r30, 0x0
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058C20
    li r0, 0x2
    lfs f0, lbl_806D2900(r2)
    stw r0, 0xd4(r31)
    stfs f0, 0xe0(r31)
    stfs f0, 0xe4(r31)
    stfs f0, 0xe8(r31)
    TornadoEffect_ApplyItemVisual_Secondary_L_80058C20:
    cmpwi r29, 0x0
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058C5C
    beq TornadoEffect_ApplyItemVisual_Secondary_L_80058C6C
    clrlwi r0, r28, 24
    cmplwi r0, 0x1
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058C40
    li r0, 0x0
    stw r0, 0x130(r31)
    TornadoEffect_ApplyItemVisual_Secondary_L_80058C40:
    stw r29, 0x124(r31)
    lwz r0, 0x124(r31)
    cmpwi r0, 0x6
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058C6C
    li r0, 0x1
    stb r0, 0x12c(r31)
    b TornadoEffect_ApplyItemVisual_Secondary_L_80058C6C
    TornadoEffect_ApplyItemVisual_Secondary_L_80058C5C:
    cmplwi r30, 0x0
    bne TornadoEffect_ApplyItemVisual_Secondary_L_80058C6C
    li r0, 0x1e
    stw r0, 0x138(r31)
    TornadoEffect_ApplyItemVisual_Secondary_L_80058C6C:
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

