/* === extracted from auto_Effect_SmokeCloud_Up_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_Free();
extern void DrawEffect_SpawnDirect();
extern void GetSpawnPosition();
extern void Rand_RangeFloat();
extern void Vec3_Copy();
extern void Vec3_Scale();
extern void VfxSlot_BindResourceEx();
extern void VfxSlot_SetRotationZ();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D53E8;
extern unsigned int lbl_806D53EC;
extern unsigned int lbl_806D53F0;
extern unsigned int lbl_806D53F4;
extern unsigned int lbl_806D540C;
extern unsigned int lbl_806D5424;
extern unsigned int lbl_806D5428;
extern unsigned int lbl_806D5434;
extern unsigned int lbl_806D5454;
extern unsigned int lbl_806D5470;
extern unsigned int lbl_806D5474;
extern unsigned int lbl_806D5478;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int fn_800AF4F8[];

/* --- function index (1 fns, .text 0x800C39F8..0x800C3CC8) ---
 * [  0] 0x800C39F8 size:0x2D0   global Effect_SmokeCloud_Update
 */

/* --- forward decls --- */
asm void Effect_SmokeCloud_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Effect_SmokeCloud_Update[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Effect_SmokeCloud_Update = {
    (void *)&Effect_SmokeCloud_Update, 0x000002D0, (void *)extab_Effect_SmokeCloud_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Effect_SmokeCloud_Update(void) { /* 0x800C39F8 size:0x2D0 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r30, r3
    addi r31, r30, 0xcc
    lbz r0, 0xb4(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq Effect_SmokeCloud_Update_L_800C3A44
    bge Effect_SmokeCloud_Update_L_800C3A44
    cmpwi r0, 0x0
    bge Effect_SmokeCloud_Update_L_800C3A30
    b Effect_SmokeCloud_Update_L_800C3A44
    Effect_SmokeCloud_Update_L_800C3A30:
    li r0, 0x0
    stw r0, 0xb4(r31)
    lbz r3, 0xb4(r30)
    addi r0, r3, 0x1
    stb r0, 0xb4(r30)
    Effect_SmokeCloud_Update_L_800C3A44:
    mr r28, r31
    li r27, 0x0
    li r29, 0x0
    Effect_SmokeCloud_Update_L_800C3A50:
    lwz r3, 0x10(r28)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_Update_L_800C3A70
    lbz r0, 0xc9(r3)
    extsb. r0, r0
    beq Effect_SmokeCloud_Update_L_800C3A70
    bl DrawEffect_Free
    stw r29, 0x10(r28)
    Effect_SmokeCloud_Update_L_800C3A70:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0x8
    blt Effect_SmokeCloud_Update_L_800C3A50
    lwz r0, 0xb4(r31)
    cmplwi r0, 0x0
    bne Effect_SmokeCloud_Update_L_800C3C24
    li r0, 0x8
    mr r3, r31
    li r28, 0x0
    mtctr r0
    Effect_SmokeCloud_Update_L_800C3A9C:
    lwz r0, 0x10(r3)
    cmplwi r0, 0x0
    bne Effect_SmokeCloud_Update_L_800C3C18
    lis r3, fn_800AF4F8@ha
    addi r3, r3, fn_800AF4F8@l
    bl DrawEffect_SpawnDirect
    slwi r0, r28, 2
    add r4, r31, r0
    stw r3, 0x10(r4)
    lwz r28, 0x10(r4)
    cmplwi r28, 0x0
    beq Effect_SmokeCloud_Update_L_800C3C0C
    addi r3, r28, 0x14
    li r4, 0x6d
    li r5, 0x0
    bl VfxSlot_BindResourceEx
    addi r3, r28, 0x8c
    addi r4, r30, 0x8c
    bl Vec3_Copy
    lfs f1, lbl_806D53F0(r2)
    lfs f2, lbl_806D53F4(r2)
    bl Rand_RangeFloat
    lfs f0, lbl_806D53EC(r2)
    addi r3, r28, 0x14
    fmuls f0, f0, f1
    stfs f0, 0xa0(r28)
    lfs f1, 0xa0(r28)
    bl VfxSlot_SetRotationZ
    lfs f1, lbl_806D5428(r2)
    lfs f2, lbl_806D53E8(r2)
    bl Rand_RangeFloat
    stfs f1, 0xb0(r28)
    addi r3, r28, 0xa4
    lfs f1, lbl_806D5470(r2)
    addi r4, r30, 0xa4
    bl Vec3_Scale
    lfs f1, lbl_806D5434(r2)
    lfs f2, lbl_806D5424(r2)
    bl Rand_RangeFloat
    lfs f3, lbl_806D5474(r2)
    lfs f0, 0xa4(r28)
    lfs f2, lbl_806D5424(r2)
    fmadds f0, f3, f1, f0
    lfs f1, lbl_806D5434(r2)
    stfs f0, 0xa4(r28)
    bl Rand_RangeFloat
    lfs f3, lbl_806D5474(r2)
    lfs f0, 0xa8(r28)
    lfs f2, lbl_806D5424(r2)
    fmadds f0, f3, f1, f0
    lfs f1, lbl_806D5434(r2)
    stfs f0, 0xa8(r28)
    bl Rand_RangeFloat
    lfs f3, lbl_806D5474(r2)
    li r0, 0x0
    lfs f2, 0xac(r28)
    addi r3, r28, 0x30
    lfs f0, lbl_806D5424(r2)
    fmadds f4, f3, f1, f2
    lfs f2, lbl_806D5478(r2)
    fmr f1, f0
    lfs f3, lbl_806D540C(r2)
    stfs f4, 0xac(r28)
    stb r0, 0x28(r28)
    stfs f0, 0x2c(r28)
    bl GetSpawnPosition
    lfs f1, lbl_806D5434(r2)
    lfs f2, lbl_806D5424(r2)
    bl Rand_RangeFloat
    lfs f0, lbl_806D540C(r2)
    lfs f2, lbl_806D5424(r2)
    fmuls f0, f0, f1
    lfs f1, lbl_806D5434(r2)
    stfs f0, 0x120(r28)
    bl Rand_RangeFloat
    lfs f0, lbl_806D540C(r2)
    lfs f2, lbl_806D5424(r2)
    fmuls f0, f0, f1
    lfs f1, lbl_806D5434(r2)
    stfs f0, 0x124(r28)
    bl Rand_RangeFloat
    lfs f0, lbl_806D540C(r2)
    li r3, 0xa
    lfs f2, lbl_806D5454(r2)
    li r0, 0x1
    fmuls f1, f0, f1
    lfs f0, lbl_806D5424(r2)
    stfs f1, 0x128(r28)
    stfs f2, 0x150(r28)
    stw r3, 0x180(r28)
    stb r0, 0x190(r28)
    stfs f0, 0x154(r28)
    Effect_SmokeCloud_Update_L_800C3C0C:
    li r0, 0xa
    stw r0, 0xb4(r31)
    b Effect_SmokeCloud_Update_L_800C3C24
    Effect_SmokeCloud_Update_L_800C3C18:
    addi r3, r3, 0x4
    addi r28, r28, 0x1
    bdnz Effect_SmokeCloud_Update_L_800C3A9C
    Effect_SmokeCloud_Update_L_800C3C24:
    lbz r0, 0xc9(r30)
    extsb. r0, r0
    beq Effect_SmokeCloud_Update_L_800C3C64
    li r29, 0x0
    mr r28, r31
    mr r31, r29
    Effect_SmokeCloud_Update_L_800C3C3C:
    lwz r3, 0x10(r28)
    bl DrawEffect_Free
    addi r29, r29, 0x1
    stw r31, 0x10(r28)
    cmpwi r29, 0x8
    addi r28, r28, 0x4
    blt Effect_SmokeCloud_Update_L_800C3C3C
    mr r3, r30
    bl DrawEffect_Free
    b Effect_SmokeCloud_Update_L_800C3CB4
    Effect_SmokeCloud_Update_L_800C3C64:
    lwz r3, 0xb4(r31)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_Update_L_800C3C78
    subi r0, r3, 0x1
    stw r0, 0xb4(r31)
    Effect_SmokeCloud_Update_L_800C3C78:
    lwz r3, 0xb8(r31)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_Update_L_800C3C8C
    subi r0, r3, 0x1
    stw r0, 0xb8(r31)
    Effect_SmokeCloud_Update_L_800C3C8C:
    lwz r3, 0xbc(r31)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_Update_L_800C3CA0
    subi r0, r3, 0x1
    stw r0, 0xbc(r31)
    Effect_SmokeCloud_Update_L_800C3CA0:
    lwz r3, 0xc0(r31)
    cmplwi r3, 0x0
    beq Effect_SmokeCloud_Update_L_800C3CB4
    subi r0, r3, 0x1
    stw r0, 0xc0(r31)
    Effect_SmokeCloud_Update_L_800C3CB4:
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
