/* === extracted from auto_MJObj_InitMember_RGB_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_804FC9A8[];

/* --- function index (1 fns, .text 0x8003A5A8..0x8003A608) ---
 * [  0] 0x8003A5A8 size:0x60    global MJObj_InitMember_RGBA
 */

/* --- forward decls --- */
asm void MJObj_InitMember_RGBA(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_MJObj_InitMember_RGBA[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_MJObj_InitMember_RGBA = {
    (void *)&MJObj_InitMember_RGBA, 0x00000060, (void *)extab_MJObj_InitMember_RGBA
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void MJObj_InitMember_RGBA(void) { /* 0x8003A5A8 size:0x60 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, lbl_804FC9A8@ha
    stw r0, 0x14(r1)
    addi r4, r4, lbl_804FC9A8@l
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r12, 0x2c(r4)
    mtctr r12
    bctrl
    cmpwi r3, 0x0
    beq MJObj_InitMember_RGBA_L_8003A5DC
    b MJObj_InitMember_RGBA_L_8003A5F4
    MJObj_InitMember_RGBA_L_8003A5DC:
    li r0, 0xff
    li r3, 0x0
    stb r0, 0x88(r31)
    stb r0, 0x89(r31)
    stb r0, 0x8a(r31)
    stb r0, 0x8b(r31)
    MJObj_InitMember_RGBA_L_8003A5F4:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

