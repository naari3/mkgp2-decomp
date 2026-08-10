/* === extracted from auto_03_8013A5BC_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1534;
extern unsigned int lbl_806D1538;
extern unsigned int lbl_806D73E8;
extern unsigned int lbl_806D741C;

/* --- function index (1 fns, .text 0x8013A5BC..0x8013A6F8) ---
 * [  0] 0x8013A5BC size:0x13C   global CoinSystem_RemoveCoins
 */

/* --- forward decls --- */
asm void CoinSystem_RemoveCoins(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void CoinSystem_RemoveCoins(void) { /* 0x8013A5BC size:0x13C */
    nofralloc
    lwz r0, lbl_806D1538(r13)
    cmpwi r0, 0x0
    bne CoinSystem_RemoveCoins_L_8013A5D0
    li r3, 0x0
    blr
    CoinSystem_RemoveCoins_L_8013A5D0:
    cmplwi r3, 0x0
    beq CoinSystem_RemoveCoins_L_8013A5E0
    cmpwi r4, 0x0
    bgt CoinSystem_RemoveCoins_L_8013A5E8
    CoinSystem_RemoveCoins_L_8013A5E0:
    li r3, 0x0
    blr
    CoinSystem_RemoveCoins_L_8013A5E8:
    mulli r5, r0, 0xc0
    lwz r7, lbl_806D1534(r13)
    li r0, 0xc0
    lfs f2, lbl_806D73E8(r2)
    mr r10, r7
    lfs f0, lbl_806D741C(r2)
    add r6, r7, r5
    li r8, 0x0
    addi r5, r6, 0xbf
    li r9, 0x0
    subf r5, r7, r5
    divwu r5, r5, r0
    mtctr r5
    cmplw r7, r6
    bge CoinSystem_RemoveCoins_L_8013A668
    CoinSystem_RemoveCoins_L_8013A624:
    lwz r0, 0x10(r10)
    cmplw r0, r3
    bne CoinSystem_RemoveCoins_L_8013A660
    lwz r0, 0x18(r10)
    cmpwi r0, 0x4
    bne CoinSystem_RemoveCoins_L_8013A644
    addi r8, r8, 0x1
    b CoinSystem_RemoveCoins_L_8013A660
    CoinSystem_RemoveCoins_L_8013A644:
    cmpwi r0, 0x5
    bne CoinSystem_RemoveCoins_L_8013A660
    lfs f1, 0x1c(r10)
    fcmpo cr0, f1, f2
    cror eq, gt, eq
    bne CoinSystem_RemoveCoins_L_8013A660
    fadds f2, f0, f1
    CoinSystem_RemoveCoins_L_8013A660:
    addi r10, r10, 0xc0
    bdnz CoinSystem_RemoveCoins_L_8013A624
    CoinSystem_RemoveCoins_L_8013A668:
    cmpw r8, r4
    ble CoinSystem_RemoveCoins_L_8013A6D4
    mr r8, r4
    b CoinSystem_RemoveCoins_L_8013A6D4
    CoinSystem_RemoveCoins_L_8013A678:
    lwz r0, 0x10(r7)
    cmplw r0, r3
    bne CoinSystem_RemoveCoins_L_8013A6D0
    lwz r0, 0x14(r7)
    cmpwi r0, 0x0
    blt CoinSystem_RemoveCoins_L_8013A6D0
    subf r0, r8, r0
    stw r0, 0x14(r7)
    lwz r0, 0x14(r7)
    cmpwi r0, 0x0
    bge CoinSystem_RemoveCoins_L_8013A6CC
    li r4, 0x1
    li r0, 0x5
    stw r4, 0x0(r7)
    lfs f0, lbl_806D741C(r2)
    stw r0, 0x18(r7)
    lfs f1, lbl_806D73E8(r2)
    stfs f2, 0x1c(r7)
    fadds f2, f2, f0
    stfs f1, 0x34(r7)
    b CoinSystem_RemoveCoins_L_8013A6D0
    CoinSystem_RemoveCoins_L_8013A6CC:
    addi r9, r9, 0x1
    CoinSystem_RemoveCoins_L_8013A6D0:
    addi r7, r7, 0xc0
    CoinSystem_RemoveCoins_L_8013A6D4:
    lwz r0, lbl_806D1538(r13)
    lwz r4, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r4, r0
    cmplw r7, r0
    blt CoinSystem_RemoveCoins_L_8013A678
    stw r9, 0x2cc(r3)
    mr r3, r8
    blr
}

