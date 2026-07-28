/* === extracted from auto_NamCam_End_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf();
extern void Frame_PostDrawOverlay();
extern void Frame_UpdatePerFrameState();
extern void MemoryManager_TimedFree();
extern void NamCam_GetImageHandle();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1070;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EB9E4[];
extern unsigned int lbl_802EB9F8[];

/* --- function index (1 fns, .text 0x80049718..0x80049860) ---
 * [  0] 0x80049718 size:0x148   global NamCam_End
 */

/* --- forward decls --- */
asm void NamCam_End(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NamCam_End[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NamCam_End = {
    (void *)&NamCam_End, 0x00000148, (void *)extab_NamCam_End
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NamCam_End(void) { /* 0x80049718 size:0x148 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r3, lbl_802EB9F8@ha
    stw r0, 0x24(r1)
    addi r3, r3, lbl_802EB9F8@l
    stw r31, 0x1c(r1)
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r3, lbl_806D1070(r13)
    cmplwi r3, 0x0
    bne NamCam_End_L_8004975C
    lis r3, lbl_802EB9E4@ha
    addi r3, r3, lbl_802EB9E4@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0x1
    b NamCam_End_L_8004984C
    NamCam_End_L_8004975C:
    addis r3, r3, 0x8
    li r0, 0x78
    stw r0, 0x2c(r3)
    li r31, 0x1
    b NamCam_End_L_800497B4
    NamCam_End_L_80049770:
    bl Frame_PostDrawOverlay
    addi r3, r1, 0xc
    li r4, 0x0
    bl NamCam_GetImageHandle
    bl Frame_UpdatePerFrameState
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r3, 0x2c(r4)
    subi r0, r3, 0x1
    stw r0, 0x2c(r4)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r0, 0x2c(r3)
    cmpwi r0, 0x0
    bgt NamCam_End_L_800497B4
    li r31, 0x0
    b NamCam_End_L_800497C8
    NamCam_End_L_800497B4:
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lbz r0, 0x10(r3)
    extsb. r0, r0
    bne NamCam_End_L_80049770
    NamCam_End_L_800497C8:
    clrlwi r0, r31, 24
    cmplwi r0, 0x1
    bne NamCam_End_L_80049838
    lwz r3, lbl_806D1070(r13)
    li r0, 0x78
    addis r3, r3, 0x8
    stw r0, 0x2c(r3)
    b NamCam_End_L_80049824
    NamCam_End_L_800497E8:
    bl Frame_PostDrawOverlay
    addi r3, r1, 0x8
    li r4, 0x0
    bl NamCam_GetImageHandle
    bl Frame_UpdatePerFrameState
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r3, 0x2c(r4)
    subi r0, r3, 0x1
    stw r0, 0x2c(r4)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r0, 0x2c(r3)
    cmpwi r0, 0x0
    ble NamCam_End_L_80049838
    NamCam_End_L_80049824:
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lbz r0, 0x10(r3)
    extsb. r0, r0
    beq NamCam_End_L_800497E8
    NamCam_End_L_80049838:
    lwz r3, lbl_806D1070(r13)
    bl MemoryManager_TimedFree
    li r0, 0x0
    li r3, 0x1
    stw r0, lbl_806D1070(r13)
    NamCam_End_L_8004984C:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

