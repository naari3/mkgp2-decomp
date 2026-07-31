/* === extracted from auto_MJObj_SetColorRGBA_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_802DE45C();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802E9D04[];
extern unsigned int lbl_803F57E0[];

/* --- function index (1 fns, .text 0x8003A608..0x8003A71C) ---
 * [  0] 0x8003A608 size:0x114   global MJObj_SetColorRGBA
 */

/* --- forward decls --- */
asm void MJObj_SetColorRGBA(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_MJObj_SetColorRGBA[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_MJObj_SetColorRGBA = {
    (void *)&MJObj_SetColorRGBA, 0x00000114, (void *)extab_MJObj_SetColorRGBA
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void MJObj_SetColorRGBA(void) { /* 0x8003A608 size:0x114 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r8, lbl_803F57E0@ha
    stw r0, 0x24(r1)
    addi r0, r8, lbl_803F57E0@l
    stmw r27, 0xc(r1)
    mr r28, r4
    mr r27, r3
    mr r29, r5
    mr r30, r6
    mr r31, r7
    mr r4, r0
    bl fn_802DE45C
    cmpwi r3, 0x0
    bne MJObj_SetColorRGBA_L_8003A658
    lis r4, lbl_802E9D04@ha
    addi r3, r2, -0x7DC0  /* lbl_806D24A0 */
    addi r5, r4, lbl_802E9D04@l
    li r4, 0x31
    bl __assert
    MJObj_SetColorRGBA_L_8003A658:
    cmpwi r28, 0xff
    ble MJObj_SetColorRGBA_L_8003A66C
    li r0, 0xff
    stb r0, 0x88(r27)
    b MJObj_SetColorRGBA_L_8003A684
    MJObj_SetColorRGBA_L_8003A66C:
    cmpwi r28, 0x0
    bge MJObj_SetColorRGBA_L_8003A680
    li r0, 0x0
    stb r0, 0x88(r27)
    b MJObj_SetColorRGBA_L_8003A684
    MJObj_SetColorRGBA_L_8003A680:
    stb r28, 0x88(r27)
    MJObj_SetColorRGBA_L_8003A684:
    cmpwi r29, 0xff
    ble MJObj_SetColorRGBA_L_8003A698
    li r0, 0xff
    stb r0, 0x89(r27)
    b MJObj_SetColorRGBA_L_8003A6B0
    MJObj_SetColorRGBA_L_8003A698:
    cmpwi r29, 0x0
    bge MJObj_SetColorRGBA_L_8003A6AC
    li r0, 0x0
    stb r0, 0x89(r27)
    b MJObj_SetColorRGBA_L_8003A6B0
    MJObj_SetColorRGBA_L_8003A6AC:
    stb r29, 0x89(r27)
    MJObj_SetColorRGBA_L_8003A6B0:
    cmpwi r30, 0xff
    ble MJObj_SetColorRGBA_L_8003A6C4
    li r0, 0xff
    stb r0, 0x8a(r27)
    b MJObj_SetColorRGBA_L_8003A6DC
    MJObj_SetColorRGBA_L_8003A6C4:
    cmpwi r30, 0x0
    bge MJObj_SetColorRGBA_L_8003A6D8
    li r0, 0x0
    stb r0, 0x8a(r27)
    b MJObj_SetColorRGBA_L_8003A6DC
    MJObj_SetColorRGBA_L_8003A6D8:
    stb r30, 0x8a(r27)
    MJObj_SetColorRGBA_L_8003A6DC:
    cmpwi r31, 0xff
    ble MJObj_SetColorRGBA_L_8003A6F0
    li r0, 0xff
    stb r0, 0x8b(r27)
    b MJObj_SetColorRGBA_L_8003A708
    MJObj_SetColorRGBA_L_8003A6F0:
    cmpwi r31, 0x0
    bge MJObj_SetColorRGBA_L_8003A704
    li r0, 0x0
    stb r0, 0x8b(r27)
    b MJObj_SetColorRGBA_L_8003A708
    MJObj_SetColorRGBA_L_8003A704:
    stb r31, 0x8b(r27)
    MJObj_SetColorRGBA_L_8003A708:
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

