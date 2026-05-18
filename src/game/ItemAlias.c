/* g_itemAliasTable: 0x9B entries, each 0xC bytes (3 ints).
 *   +0x0: src item id
 *   +0x4: remap (hit context) id
 *   +0x8: dest item id
 */
extern int g_itemAliasTable[0x9B][3];

int ItemAlias_SourceToDest(int srcId) {
    int *p;
    int i;
    p = &g_itemAliasTable[0][0];
    i = 0;
    for (;;) {
        int k;
        for (k = 0; k < 0x9b; k++) {
            if (srcId == *p) {
                return g_itemAliasTable[i][2];
            }
            p += 3;
            i += 1;
        }
        return 0;
    }
}

int ItemAlias_DestToSource(int destId, unsigned char *foundOut) {
    int *p;
    int i;
    p = &g_itemAliasTable[0][0];
    i = 0;
    {
        int k;
        for (k = 0; k < 0x9b; k++) {
            if (destId == p[2]) {
                if (foundOut != 0) {
                    *foundOut = 1;
                }
                return g_itemAliasTable[i][0];
            }
            p += 3;
            i += 1;
        }
    }
    if (foundOut == 0) {
        return destId;
    }
    *foundOut = 0;
    return destId;
}

/* asm_fn 退避: CW 1.3.2 が 5-unrolled 比較で p の displacement を fold して
 * target の inline `addi r4, r4, 0xC` pattern を再現できない。`p += 3; p[1]` /
 * `p[4]` / `(volatile *)` 形を 6+ サイクル試行したが 0x94-0xA4 で停滞、target
 * 0xB8 に届かず。sibling fn_800D75F8 が完全同パターン (5-unroll、offset 0x10
 * 反復、inline addi) なので idiom 解明できれば 2 fn 同時に unlock 可能。
 */
asm void ItemAlias_HitRemapLookup(int srcId) {
    nofralloc
    lis r4, g_itemAliasTable@ha
    li r0, 0x1f
    addi r5, r4, g_itemAliasTable@l
    li r4, 0x0
    mtctr r0
HitRemapLookup_L_800D7554:
    lwz r0, 0x4(r5)
    cmpw r3, r0
    bne HitRemapLookup_L_800D7564
    b HitRemapLookup_L_800D75D4
HitRemapLookup_L_800D7564:
    lwz r0, 0x10(r5)
    addi r4, r4, 0x1
    addi r5, r5, 0xC
    cmpw r3, r0
    bne HitRemapLookup_L_800D757C
    b HitRemapLookup_L_800D75D4
HitRemapLookup_L_800D757C:
    lwz r0, 0x10(r5)
    addi r4, r4, 0x1
    addi r5, r5, 0xC
    cmpw r3, r0
    bne HitRemapLookup_L_800D7594
    b HitRemapLookup_L_800D75D4
HitRemapLookup_L_800D7594:
    lwz r0, 0x10(r5)
    addi r4, r4, 0x1
    addi r5, r5, 0xC
    cmpw r3, r0
    bne HitRemapLookup_L_800D75AC
    b HitRemapLookup_L_800D75D4
HitRemapLookup_L_800D75AC:
    lwz r0, 0x10(r5)
    addi r4, r4, 0x1
    addi r5, r5, 0xC
    cmpw r3, r0
    bne HitRemapLookup_L_800D75C4
    b HitRemapLookup_L_800D75D4
HitRemapLookup_L_800D75C4:
    addi r5, r5, 0xC
    addi r4, r4, 0x1
    bdnz HitRemapLookup_L_800D7554
    li r4, 0x0
HitRemapLookup_L_800D75D4:
    cmpwi r4, 0x9b
    blt HitRemapLookup_L_800D75E4
    li r3, 0x0
    blr
HitRemapLookup_L_800D75E4:
    mulli r0, r4, 0xc
    lis r3, g_itemAliasTable@ha
    addi r3, r3, g_itemAliasTable@l
    lwzx r3, r3, r0
    blr
}
