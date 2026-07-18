/* === extracted from auto_Tachometer_Destroy_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void SpriteHandle_Destroy();
extern void fn_80120A08();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_tachometer_isInitialized;
extern unsigned int lbl_806D1459;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80411E20[];
extern unsigned int lbl_805D3320[];

/* --- function index (1 fns, .text 0x800AB6BC..0x800AB77C) ---
 * [  0] 0x800AB6BC size:0xC0    global Tachometer_Destroy
 */

/* --- forward decls --- */
asm void Tachometer_Destroy(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Tachometer_Destroy[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tachometer_Destroy = {
    (void *)&Tachometer_Destroy, 0x000000C0, (void *)extab_Tachometer_Destroy
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Tachometer_Destroy(void) { /* 0x800AB6BC size:0xC0 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    lbz r0, g_tachometer_isInitialized(r13)
    cmplwi r0, 0x0
    bne Tachometer_Destroy_L_800AB6E4
    li r3, 0x0
    b Tachometer_Destroy_L_800AB764
    Tachometer_Destroy_L_800AB6E4:
    lis r3, lbl_805D3320@ha
    li r30, 0x0
    addi r31, r3, lbl_805D3320@l
    Tachometer_Destroy_L_800AB6F0:
    lwz r3, 0x0(r31)
    bl SpriteHandle_Destroy
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0x5
    blt Tachometer_Destroy_L_800AB6F0
    lbz r0, lbl_806D1459(r13)
    lis r3, lbl_80411E20@ha
    addi r3, r3, lbl_80411E20@l
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl fn_80120A08
    lbz r0, lbl_806D1459(r13)
    lis r3, lbl_80411E20@ha
    addi r3, r3, lbl_80411E20@l
    slwi r0, r0, 2
    add r3, r3, r0
    lwz r3, 0x10(r3)
    bl fn_80120A08
    lbz r0, lbl_806D1459(r13)
    lis r3, lbl_80411E20@ha
    addi r3, r3, lbl_80411E20@l
    slwi r0, r0, 2
    add r3, r3, r0
    lwz r3, 0xe0(r3)
    bl fn_80120A08
    li r0, 0x0
    li r3, 0x1
    stb r0, g_tachometer_isInitialized(r13)
    Tachometer_Destroy_L_800AB764:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

