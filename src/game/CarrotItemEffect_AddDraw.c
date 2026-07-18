/* === extracted from auto_CarrotItemEffect_Add_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Mtx44_TransformVec3();
extern void clDrawMan_AddSorted_NoDepthBias();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D5034;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int CarrotItemEffect_Render[];
extern unsigned int lbl_803293DC[];
extern unsigned int lbl_805DF3D0[];

/* --- function index (1 fns, .text 0x800B2A64..0x800B2AF8) ---
 * [  0] 0x800B2A64 size:0x94    global CarrotItemEffect_AddDraw
 */

/* --- forward decls --- */
asm void CarrotItemEffect_AddDraw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CarrotItemEffect_AddDraw[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CarrotItemEffect_AddDraw = {
    (void *)&CarrotItemEffect_AddDraw, 0x00000094, (void *)extab_CarrotItemEffect_AddDraw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CarrotItemEffect_AddDraw(void) { /* 0x800B2A64 size:0x94 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r4, lbl_805DF3D0@ha
    lis r5, lbl_803293DC@ha
    stw r0, 0x34(r1)
    addi r4, r4, lbl_805DF3D0@l
    stw r31, 0x2c(r1)
    mr r31, r3
    addi r3, r1, 0x14
    lwzu r7, lbl_803293DC@l(r5)
    lwz r6, 0x4(r5)
    lwz r0, 0x8(r5)
    addi r5, r1, 0x8
    stw r7, 0x14(r1)
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    stw r7, 0x8(r1)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl Mtx44_TransformVec3
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne CarrotItemEffect_AddDraw_L_800B2AC4
    li r3, 0x0
    CarrotItemEffect_AddDraw_L_800B2AC4:
    lis r4, CarrotItemEffect_Render@ha
    lfs f1, 0x14(r1)
    lfs f2, 0x18(r1)
    addi r4, r4, CarrotItemEffect_Render@l
    lfs f3, 0x1c(r1)
    mr r5, r31
    lfs f4, lbl_806D5034(r2)
    bl clDrawMan_AddSorted_NoDepthBias
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
