/*
 * GetKartParamBlock @ 0x80090FF0 (size 0x8C).
 *
 * Indexes into the character kart parameter table to retrieve a param block.
 * If ccVariant >= 0, uses a direct table (g_kartParamCcVariantTable)
 * indexed by [ccVariant * 3 + ccClass]. Otherwise, maps kartVariant
 * (0,1,negative->0; 2->1; 3->2; >=4->0) to a normalized index and uses a
 * per-character table g_kartParamPtrTable[charId] indirected by
 * [ccClass * 12 + normalizedCcIdx * 4].
 *
 * asm_fn retreat (§10.5): 3 attempts (Ghidra-plate goto / switch /
 * per-case-goto) could not reproduce target's binary tree branch layout.
 * Best C attempt (`>= 0` formulation) reached size 0x88 vs target 0x8C
 * (1-instr diff: `b L_018` after `< 2` fallthrough block). The codegen
 * difference is CW 1.3.2 block-merging heuristic for shared `n=0` paths
 * (target keeps three "common" `< 2` paths funneling to a single `L_018`
 * via explicit `b`, while every C source variant tried merges them into
 * fallthrough). Retreating to asm_fn preserves byte-identical body; a
 * future promote to plain C can retry once the branch-layout idiom is
 * identified.
 */

extern unsigned int g_kartParamCcVariantTable[];
extern unsigned int g_kartParamPtrTable[];

asm void GetKartParamBlock(void) {
    nofralloc
    cmpwi r5, 0x2
    beq GetKartParamBlock_L_80091028
    bge GetKartParamBlock_L_8009100C
    cmpwi r5, 0x0
    beq GetKartParamBlock_L_80091018
    bge GetKartParamBlock_L_80091020
    b GetKartParamBlock_L_80091018
GetKartParamBlock_L_8009100C:
    cmpwi r5, 0x4
    bge GetKartParamBlock_L_80091018
    b GetKartParamBlock_L_80091030
GetKartParamBlock_L_80091018:
    li r0, 0x0
    b GetKartParamBlock_L_80091034
GetKartParamBlock_L_80091020:
    li r0, 0x0
    b GetKartParamBlock_L_80091034
GetKartParamBlock_L_80091028:
    li r0, 0x1
    b GetKartParamBlock_L_80091034
GetKartParamBlock_L_80091030:
    li r0, 0x2
GetKartParamBlock_L_80091034:
    cmpwi r6, 0x0
    bge GetKartParamBlock_L_80091060
    lis r5, g_kartParamPtrTable@ha
    slwi r6, r3, 2
    addi r5, r5, g_kartParamPtrTable@l
    slwi r0, r0, 2
    mulli r3, r4, 0xc
    lwzx r4, r5, r6
    add r0, r3, r0
    lwzx r3, r4, r0
    blr
GetKartParamBlock_L_80091060:
    mulli r5, r6, 0xc
    lis r3, g_kartParamCcVariantTable@ha
    slwi r0, r4, 2
    addi r3, r3, g_kartParamCcVariantTable@l
    add r3, r3, r5
    lwzx r3, r3, r0
    blr
}
