/* === extracted from auto_KartDriver_GetJointP_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartDriver_GetJointByIdx();
extern void Object_GetJObjLocalMatrix();

/* --- function index (1 fns, .text 0x80040D84..0x80040DFC) ---
 * [  0] 0x80040D84 size:0x78    global KartDriver_GetJointPosition
 */

/* --- forward decls --- */
asm void KartDriver_GetJointPosition(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_GetJointPosition[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_GetJointPosition = {
    (void *)&KartDriver_GetJointPosition, 0x00000078, (void *)extab_KartDriver_GetJointPosition
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_GetJointPosition(void) { /* 0x80040D84 size:0x78 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r4, -0x1
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r5
    bne KartDriver_GetJointPosition_L_80040DCC
    lwz r4, 0x0(r3)
    cmplwi r4, 0x0
    beq KartDriver_GetJointPosition_L_80040DB8
    lwz r0, 0xc(r3)
    cmplwi r0, 0x0
    bne KartDriver_GetJointPosition_L_80040DC0
    KartDriver_GetJointPosition_L_80040DB8:
    li r3, 0x0
    b KartDriver_GetJointPosition_L_80040DD0
    KartDriver_GetJointPosition_L_80040DC0:
    mr r3, r4
    bl Object_GetJObjLocalMatrix
    b KartDriver_GetJointPosition_L_80040DD0
    KartDriver_GetJointPosition_L_80040DCC:
    bl KartDriver_GetJointByIdx
    KartDriver_GetJointPosition_L_80040DD0:
    lfs f0, 0xc(r3)
    stfs f0, 0x0(r31)
    lfs f0, 0x1c(r3)
    stfs f0, 0x4(r31)
    lfs f0, 0x2c(r3)
    stfs f0, 0x8(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

