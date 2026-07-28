/* === extracted from auto_NamCam_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void DebugPrintf();
extern void PcbIdToIpString();
extern void acInetAddr();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1070;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EBA04[];

/* --- function index (1 fns, .text 0x80049860..0x80049940) ---
 * [  0] 0x80049860 size:0xE0    global NamCam_Init
 */

/* --- forward decls --- */
asm void NamCam_Init(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NamCam_Init[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NamCam_Init = {
    (void *)&NamCam_Init, 0x000000E0, (void *)extab_NamCam_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NamCam_Init(void) { /* 0x80049860 size:0xE0 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r3, 0x8
    stw r0, 0x14(r1)
    addi r3, r3, 0x34
    bl Alloc
    stw r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    li r4, 0x2
    li r0, 0x50
    stb r4, 0x1(r3)
    li r3, 0x0
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    sth r0, 0x2(r4)
    bl PcbIdToIpString
    bl acInetAddr
    lwz r7, lbl_806D1070(r13)
    lis r4, lbl_802EBA04@ha
    li r6, 0x0
    li r5, -0x1
    addis r7, r7, 0x8
    addi r0, r4, lbl_802EBA04@l
    stw r3, 0x4(r7)
    mr r3, r0
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stb r6, 0x10(r4)
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stb r6, 0x11(r4)
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stb r6, 0x12(r4)
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stb r6, 0x13(r4)
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stw r5, 0x14(r4)
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stb r6, 0x18(r4)
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stw r6, 0x24(r4)
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stw r6, 0x30(r4)
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r0, 0x14(r1)
    li r3, 0x1
    mtlr r0
    addi r1, r1, 0x10
    blr
}

