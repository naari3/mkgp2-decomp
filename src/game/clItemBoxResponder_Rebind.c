/* === extracted from auto_clItemBoxResponder_R_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf();
extern void GXChannel_Bind();
extern void GXChannel_Unbind();
extern void clItemBoxResponder_DrawDebris();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CEEA0;
extern unsigned int lbl_806D10B0;
extern unsigned int lbl_806D10B4;
extern unsigned int lbl_806D10B8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EDEF8[];
extern unsigned int lbl_802EDF14[];

/* --- function index (1 fns, .text 0x8005DA18..0x8005DB3C) ---
 * [  0] 0x8005DA18 size:0x124   global clItemBoxResponder_Rebind
 */

/* --- forward decls --- */
asm void clItemBoxResponder_Rebind(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBoxResponder_Rebind[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBoxResponder_Rebind = {
    (void *)&clItemBoxResponder_Rebind, 0x00000124, (void *)extab_clItemBoxResponder_Rebind
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_Rebind(void) { /* 0x8005DA18 size:0x124 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r0, lbl_806CEEA0(r13)
    cmpwi r0, -0x1
    beq clItemBoxResponder_Rebind_L_8005DAAC
    lis r3, lbl_802EDEF8@ha
    addi r3, r3, lbl_802EDEF8@l
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r0, lbl_806CEEA0(r13)
    cmpwi r0, 0x1
    beq clItemBoxResponder_Rebind_L_8005DA7C
    bge clItemBoxResponder_Rebind_L_8005DA64
    cmpwi r0, 0x0
    bge clItemBoxResponder_Rebind_L_8005DA70
    b clItemBoxResponder_Rebind_L_8005DA94
    clItemBoxResponder_Rebind_L_8005DA64:
    cmpwi r0, 0x3
    bge clItemBoxResponder_Rebind_L_8005DA94
    b clItemBoxResponder_Rebind_L_8005DA88
    clItemBoxResponder_Rebind_L_8005DA70:
    lwz r3, lbl_806D10B4(r13)
    bl GXChannel_Unbind
    b clItemBoxResponder_Rebind_L_8005DAA4
    clItemBoxResponder_Rebind_L_8005DA7C:
    lwz r3, lbl_806D10B0(r13)
    bl GXChannel_Unbind
    b clItemBoxResponder_Rebind_L_8005DAA4
    clItemBoxResponder_Rebind_L_8005DA88:
    lwz r3, lbl_806D10B8(r13)
    bl GXChannel_Unbind
    b clItemBoxResponder_Rebind_L_8005DAA4
    clItemBoxResponder_Rebind_L_8005DA94:
    lis r3, lbl_802EDF14@ha
    addi r3, r3, lbl_802EDF14@l
    crxor 6, 6, 6
    bl DebugPrintf
    clItemBoxResponder_Rebind_L_8005DAA4:
    li r0, -0x1
    stw r0, lbl_806CEEA0(r13)
    clItemBoxResponder_Rebind_L_8005DAAC:
    lwz r3, lbl_806D10B8(r13)
    bl GXChannel_Bind
    li r0, 0x2
    stw r0, lbl_806CEEA0(r13)
    lwz r3, 0x0(r31)
    bl clItemBoxResponder_DrawDebris
    lwz r0, lbl_806CEEA0(r13)
    cmpwi r0, 0x1
    beq clItemBoxResponder_Rebind_L_8005DAF8
    bge clItemBoxResponder_Rebind_L_8005DAE0
    cmpwi r0, 0x0
    bge clItemBoxResponder_Rebind_L_8005DAEC
    b clItemBoxResponder_Rebind_L_8005DB10
    clItemBoxResponder_Rebind_L_8005DAE0:
    cmpwi r0, 0x3
    bge clItemBoxResponder_Rebind_L_8005DB10
    b clItemBoxResponder_Rebind_L_8005DB04
    clItemBoxResponder_Rebind_L_8005DAEC:
    lwz r3, lbl_806D10B4(r13)
    bl GXChannel_Unbind
    b clItemBoxResponder_Rebind_L_8005DB20
    clItemBoxResponder_Rebind_L_8005DAF8:
    lwz r3, lbl_806D10B0(r13)
    bl GXChannel_Unbind
    b clItemBoxResponder_Rebind_L_8005DB20
    clItemBoxResponder_Rebind_L_8005DB04:
    lwz r3, lbl_806D10B8(r13)
    bl GXChannel_Unbind
    b clItemBoxResponder_Rebind_L_8005DB20
    clItemBoxResponder_Rebind_L_8005DB10:
    lis r3, lbl_802EDF14@ha
    addi r3, r3, lbl_802EDF14@l
    crxor 6, 6, 6
    bl DebugPrintf
    clItemBoxResponder_Rebind_L_8005DB20:
    li r0, -0x1
    stw r0, lbl_806CEEA0(r13)
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

