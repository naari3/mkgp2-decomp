/* === extracted from auto_KartDriver_GetJoint1_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartDriver_GetJointByIdx();
extern void Mtx44_GetTranslation_RowMajor();

/* --- function index (1 fns, .text 0x800DC690..0x800DC6D0) ---
 * [  0] 0x800DC690 size:0x40    global KartDriver_GetJoint13_WorldPos
 */

/* --- forward decls --- */
asm void KartDriver_GetJoint13_WorldPos(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_GetJoint13_WorldPos[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_GetJoint13_WorldPos = {
    (void *)&KartDriver_GetJoint13_WorldPos, 0x00000040, (void *)extab_KartDriver_GetJoint13_WorldPos
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_GetJoint13_WorldPos(void) { /* 0x800DC690 size:0x40 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    mr r3, r4
    li r4, 0xd
    bl KartDriver_GetJointByIdx
    mr r4, r3
    mr r3, r31
    bl Mtx44_GetTranslation_RowMajor
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


