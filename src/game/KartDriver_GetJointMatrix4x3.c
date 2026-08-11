/* === extracted from auto_KartDriver_GetJointM_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartDriver_GetJointByIdx();
extern void fn_8025E1EC();

/* --- function index (1 fns, .text 0x80040DFC..0x80040E9C) ---
 * [  0] 0x80040DFC size:0xA0    global KartDriver_GetJointMatrix4x3
 */

/* --- forward decls --- */
asm void KartDriver_GetJointMatrix4x3(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_GetJointMatrix4x3[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_GetJointMatrix4x3 = {
    (void *)&KartDriver_GetJointMatrix4x3, 0x000000A0, (void *)extab_KartDriver_GetJointMatrix4x3
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_GetJointMatrix4x3(void) { /* 0x80040DFC size:0xA0 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r5
    bl KartDriver_GetJointByIdx
    mr r31, r3
    mr r3, r30
    bl fn_8025E1EC
    lfs f0, 0x0(r31)
    stfs f0, 0x0(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x4(r30)
    lfs f0, 0x20(r31)
    stfs f0, 0x8(r30)
    lfs f0, 0x4(r31)
    stfs f0, 0x10(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x14(r30)
    lfs f0, 0x24(r31)
    stfs f0, 0x18(r30)
    lfs f0, 0x8(r31)
    stfs f0, 0x20(r30)
    lfs f0, 0x18(r31)
    stfs f0, 0x24(r30)
    lfs f0, 0x28(r31)
    stfs f0, 0x28(r30)
    lfs f0, 0xc(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x1c(r31)
    stfs f0, 0x34(r30)
    lfs f0, 0x2c(r31)
    stfs f0, 0x38(r30)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


