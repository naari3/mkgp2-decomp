/* === extracted from auto_TornadoEffect_SetCol_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Terrain_ApplyCup2FlagPatch();
extern void Terrain_FlagsToTypeId();

/* --- function index (1 fns, .text 0x80057738..0x8005778C) ---
 * [  0] 0x80057738 size:0x54    global TornadoEffect_SetColorPairC8CC
 */

/* --- forward decls --- */
asm void TornadoEffect_SetColorPairC8CC(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_SetColorPairC8CC[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_SetColorPairC8CC = {
    (void *)&TornadoEffect_SetColorPairC8CC, 0x00000054, (void *)extab_TornadoEffect_SetColorPairC8CC
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_SetColorPairC8CC(void) { /* 0x80057738 size:0x54 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r5
    stw r30, 0x8(r1)
    mr r30, r3
    mr r3, r4
    bl Terrain_ApplyCup2FlagPatch
    bl Terrain_FlagsToTypeId
    stw r3, 0xc8(r30)
    mr r3, r31
    bl Terrain_ApplyCup2FlagPatch
    bl Terrain_FlagsToTypeId
    stw r3, 0xcc(r30)
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

