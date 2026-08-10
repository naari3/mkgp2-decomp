/* === extracted from auto_BombItem_DropAndSpaw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_SpawnDirect();
extern void ItemObject_DecrementCategoryBudget();
extern void ItemObject_SpawnWithAlias();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_TransformVec3();
extern void Mtx_TransposeToMtx44();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_Container_Free();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int Effect_KartWaveGlow_Update[];
extern unsigned int lbl_8032FF40[];

/* --- function index (1 fns, .text 0x800FBBD4..0x800FBD88) ---
 * [  0] 0x800FBBD4 size:0x1B4   global BombItem_DropAndSpawnExplosionTick
 */

/* --- forward decls --- */
asm void BombItem_DropAndSpawnExplosionTick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BombItem_DropAndSpawnExplosionTick[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BombItem_DropAndSpawnExplosionTick = {
    (void *)&BombItem_DropAndSpawnExplosionTick, 0x000001B4, (void *)extab_BombItem_DropAndSpawnExplosionTick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BombItem_DropAndSpawnExplosionTick(void) { /* 0x800FBBD4 size:0x1B4 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stw r31, 0x7c(r1)
    mr r31, r3
    stw r30, 0x78(r1)
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BombItem_DropAndSpawnExplosionTick_L_800FBC88
    bge BombItem_DropAndSpawnExplosionTick_L_800FBD20
    cmpwi r0, 0x0
    bge BombItem_DropAndSpawnExplosionTick_L_800FBC0C
    b BombItem_DropAndSpawnExplosionTick_L_800FBD20
    BombItem_DropAndSpawnExplosionTick_L_800FBC0C:
    lbz r0, 0x18c(r31)
    extsb. r0, r0
    beq BombItem_DropAndSpawnExplosionTick_L_800FBD20
    lis r3, Effect_KartWaveGlow_Update@ha
    addi r3, r3, Effect_KartWaveGlow_Update@l
    bl DrawEffect_SpawnDirect
    cmplwi r3, 0x0
    beq BombItem_DropAndSpawnExplosionTick_L_800FBC34
    lwz r0, 0x184(r31)
    stw r0, 0x11c(r3)
    BombItem_DropAndSpawnExplosionTick_L_800FBC34:
    lwz r3, 0x184(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x20
    bl Mtx44_GetTranslation_RowMajor
    lwz r7, 0x20(r1)
    addi r4, r1, 0x14
    lwz r6, 0x24(r1)
    li r3, 0xb7
    lwz r0, 0x28(r1)
    li r5, 0x0
    stw r7, 0x14(r1)
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    bl SoundMgr_PlaySE_Positional
    li r0, 0xa
    stw r0, 0xf0(r31)
    lbz r3, 0xc8(r31)
    addi r0, r3, 0x1
    stb r0, 0xc8(r31)
    b BombItem_DropAndSpawnExplosionTick_L_800FBD20
    BombItem_DropAndSpawnExplosionTick_L_800FBC88:
    lwz r0, 0xf0(r31)
    cmplwi r0, 0x0
    bne BombItem_DropAndSpawnExplosionTick_L_800FBD20
    li r3, 0x67
    li r4, 0xff
    bl ItemObject_SpawnWithAlias
    mr. r30, r3
    beq BombItem_DropAndSpawnExplosionTick_L_800FBD0C
    lbz r0, 0x1dc(r31)
    stb r0, 0x1dc(r30)
    lwz r0, 0x1e0(r31)
    stw r0, 0x1e0(r30)
    lwz r3, 0x184(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x2c
    bl Mtx_TransposeToMtx44
    lis r4, lbl_8032FF40@ha
    addi r3, r30, 0xa0
    addi r8, r4, lbl_8032FF40@l
    addi r4, r1, 0x2c
    lwz r7, 0x0(r8)
    addi r5, r1, 0x8
    lwz r6, 0x4(r8)
    lwz r0, 0x8(r8)
    stw r7, 0x8(r1)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl Mtx44_TransformVec3
    lwz r0, 0x180(r31)
    stw r0, 0x180(r30)
    lwz r0, 0x184(r31)
    stw r0, 0x184(r30)
    BombItem_DropAndSpawnExplosionTick_L_800FBD0C:
    mr r3, r31
    bl ItemObject_DecrementCategoryBudget
    mr r3, r31
    bl SpriteSlot_Container_Free
    b BombItem_DropAndSpawnExplosionTick_L_800FBD70
    BombItem_DropAndSpawnExplosionTick_L_800FBD20:
    lwz r3, 0xf0(r31)
    cmplwi r3, 0x0
    beq BombItem_DropAndSpawnExplosionTick_L_800FBD34
    subi r0, r3, 0x1
    stw r0, 0xf0(r31)
    BombItem_DropAndSpawnExplosionTick_L_800FBD34:
    lwz r3, 0xf4(r31)
    cmplwi r3, 0x0
    beq BombItem_DropAndSpawnExplosionTick_L_800FBD48
    subi r0, r3, 0x1
    stw r0, 0xf4(r31)
    BombItem_DropAndSpawnExplosionTick_L_800FBD48:
    lwz r3, 0xf8(r31)
    cmplwi r3, 0x0
    beq BombItem_DropAndSpawnExplosionTick_L_800FBD5C
    subi r0, r3, 0x1
    stw r0, 0xf8(r31)
    BombItem_DropAndSpawnExplosionTick_L_800FBD5C:
    lwz r3, 0xfc(r31)
    cmplwi r3, 0x0
    beq BombItem_DropAndSpawnExplosionTick_L_800FBD70
    subi r0, r3, 0x1
    stw r0, 0xfc(r31)
    BombItem_DropAndSpawnExplosionTick_L_800FBD70:
    lwz r0, 0x84(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}


