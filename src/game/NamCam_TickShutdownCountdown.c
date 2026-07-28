/* === extracted from auto_NamCam_TickShutdownC_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf();
extern void MemoryManager_TimedFree();
extern void NamCam_GetImageHandle();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1070;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EB9E4[];

/* --- function index (1 fns, .text 0x80049628..0x80049718) ---
 * [  0] 0x80049628 size:0xF0    global NamCam_TickShutdownCountdown
 */

/* --- forward decls --- */
asm void NamCam_TickShutdownCountdown(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NamCam_TickShutdownCountdown[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NamCam_TickShutdownCountdown = {
    (void *)&NamCam_TickShutdownCountdown, 0x000000F0, (void *)extab_NamCam_TickShutdownCountdown
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NamCam_TickShutdownCountdown(void) { /* 0x80049628 size:0xF0 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, lbl_806D1070(r13)
    cmplwi r0, 0x0
    bne NamCam_TickShutdownCountdown_L_80049658
    lis r3, lbl_802EB9E4@ha
    addi r3, r3, lbl_802EB9E4@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0x1
    b NamCam_TickShutdownCountdown_L_80049708
    NamCam_TickShutdownCountdown_L_80049658:
    addi r3, r1, 0x8
    li r4, 0x0
    bl NamCam_GetImageHandle
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r3, 0x2c(r4)
    subi r0, r3, 0x1
    stw r0, 0x2c(r4)
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r0, 0x2c(r4)
    cmpwi r0, 0x0
    bgt NamCam_TickShutdownCountdown_L_800496A0
    bl MemoryManager_TimedFree
    li r0, 0x0
    li r3, 0x1
    stw r0, lbl_806D1070(r13)
    b NamCam_TickShutdownCountdown_L_80049708
    NamCam_TickShutdownCountdown_L_800496A0:
    lwz r0, 0x30(r4)
    cmpwi r0, 0x1
    beq NamCam_TickShutdownCountdown_L_800496E4
    bge NamCam_TickShutdownCountdown_L_80049704
    cmpwi r0, 0x0
    bge NamCam_TickShutdownCountdown_L_800496BC
    b NamCam_TickShutdownCountdown_L_80049704
    NamCam_TickShutdownCountdown_L_800496BC:
    lbz r0, 0x10(r4)
    extsb. r0, r0
    bne NamCam_TickShutdownCountdown_L_80049704
    li r3, 0x1
    li r0, 0x78
    stw r3, 0x30(r4)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    stw r0, 0x2c(r3)
    b NamCam_TickShutdownCountdown_L_80049704
    NamCam_TickShutdownCountdown_L_800496E4:
    lbz r0, 0x10(r4)
    cmpwi r0, 0x1
    bne NamCam_TickShutdownCountdown_L_80049704
    bl MemoryManager_TimedFree
    li r0, 0x0
    li r3, 0x1
    stw r0, lbl_806D1070(r13)
    b NamCam_TickShutdownCountdown_L_80049708
    NamCam_TickShutdownCountdown_L_80049704:
    li r3, 0x0
    NamCam_TickShutdownCountdown_L_80049708:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

