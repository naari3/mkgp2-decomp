/* === extracted from auto_clItemBox_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __ptmf_scall();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803F9CA8[];

/* --- function index (1 fns, .text 0x8005EE24..0x8005EEB0) ---
 * [  0] 0x8005EE24 size:0x8C    global clItemBox_Tick
 */

/* --- forward decls --- */
asm void clItemBox_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBox_Tick[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBox_Tick = {
    (void *)&clItemBox_Tick, 0x0000008C, (void *)extab_clItemBox_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBox_Tick(void) { /* 0x8005EE24 size:0x8C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    addi r12, r31, 0x18
    bl __ptmf_scall
    nop
    stw r3, 0x24(r31)
    lis r3, lbl_803F9CA8@ha
    addi r0, r3, lbl_803F9CA8@l
    lwz r3, 0x24(r31)
    mulli r3, r3, 0xc
    add r4, r0, r3
    lwz r3, 0x0(r4)
    lwz r0, 0x4(r4)
    stw r3, 0x18(r31)
    stw r0, 0x1c(r31)
    lwz r0, 0x8(r4)
    stw r0, 0x20(r31)
    lwz r0, 0x24(r31)
    cmpwi r0, 0x1
    beq clItemBox_Tick_L_8005EE90
    cmpwi r0, 0x0
    beq clItemBox_Tick_L_8005EE90
    cmpwi r0, 0x3
    bne clItemBox_Tick_L_8005EE98
    clItemBox_Tick_L_8005EE90:
    li r3, 0x1
    b clItemBox_Tick_L_8005EE9C
    clItemBox_Tick_L_8005EE98:
    li r3, 0x0
    clItemBox_Tick_L_8005EE9C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

