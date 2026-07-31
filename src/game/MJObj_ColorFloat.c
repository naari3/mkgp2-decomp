/* === extracted from auto_MJObj_SetColorRGBA_F_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MJObj_SetColorRGBA();
extern void fn_802DE45C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2490;
extern unsigned int lbl_806D2494;
extern unsigned int lbl_806D2498;
extern unsigned int lbl_806D249C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803F57E0[];

/* --- function index (1 fns, .text 0x8003A154..0x8003A22C) ---
 * [  0] 0x8003A154 size:0xD8    global MJObj_SetColorRGBA_Float
 */

/* --- forward decls --- */
asm void MJObj_SetColorRGBA_Float(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_MJObj_SetColorRGBA_Float[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_MJObj_SetColorRGBA_Float = {
    (void *)&MJObj_SetColorRGBA_Float, 0x000000D8, (void *)extab_MJObj_SetColorRGBA_Float
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void MJObj_SetColorRGBA_Float(void) { /* 0x8003A154 size:0xD8 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    lfs f0, lbl_806D2494(r2)
    stw r0, 0x44(r1)
    fmuls f5, f0, f1
    lfs f6, lbl_806D2490(r2)
    fmuls f1, f0, f2
    stmw r27, 0x2c(r1)
    fmuls f0, f0, f3
    lfs f7, lbl_806D2498(r2)
    fmuls f2, f6, f5
    mr r27, r3
    fmuls f1, f6, f1
    fmuls f0, f6, f0
    fctiwz f2, f2
    fctiwz f1, f1
    fctiwz f0, f0
    stfd f2, 0x8(r1)
    fcmpo cr0, f4, f7
    stfd f1, 0x10(r1)
    lwz r31, 0xc(r1)
    stfd f0, 0x18(r1)
    lwz r30, 0x14(r1)
    lwz r29, 0x1c(r1)
    ble MJObj_SetColorRGBA_Float_L_8003A1BC
    b MJObj_SetColorRGBA_Float_L_8003A1C0
    MJObj_SetColorRGBA_Float_L_8003A1BC:
    fmr f7, f4
    MJObj_SetColorRGBA_Float_L_8003A1C0:
    lfs f0, lbl_806D249C(r2)
    lfs f1, lbl_806D2494(r2)
    fcmpo cr0, f7, f0
    bge MJObj_SetColorRGBA_Float_L_8003A1D4
    b MJObj_SetColorRGBA_Float_L_8003A1D8
    MJObj_SetColorRGBA_Float_L_8003A1D4:
    fmr f0, f7
    MJObj_SetColorRGBA_Float_L_8003A1D8:
    fmuls f0, f1, f0
    lis r3, lbl_803F57E0@ha
    addi r4, r3, lbl_803F57E0@l
    mr r3, r27
    fctiwz f0, f0
    stfd f0, 0x20(r1)
    lwz r28, 0x24(r1)
    bl fn_802DE45C
    cmpwi r3, 0x0
    beq MJObj_SetColorRGBA_Float_L_8003A218
    mr r3, r27
    clrlwi r4, r31, 24
    clrlwi r5, r30, 24
    clrlwi r6, r29, 24
    clrlwi r7, r28, 24
    bl MJObj_SetColorRGBA
    MJObj_SetColorRGBA_Float_L_8003A218:
    lmw r27, 0x2c(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

