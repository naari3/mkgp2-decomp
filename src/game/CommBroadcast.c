/* === extracted from auto_03_800848C4_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_isCommHost;
extern unsigned int g_ringReadIdx;
extern unsigned int lbl_806D11A0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_ringBufferBase[];

/* --- function index (5 fns, .text 0x800848C4..0x80084A84) ---
 * [  0] 0x800848C4 size:0x38    global CommBroadcast_GetKartLap
 * [  1] 0x800848FC size:0x38    global CommBroadcast_SetKartLap
 * [  2] 0x80084934 size:0x84    global CommBroadcast_GetKartRankNibble
 * [  3] 0x800849B8 size:0x90    global CommBroadcast_SetKartRankNibble
 * [  4] 0x80084A48 size:0x3C    global CommBroadcast_ScanForMySyncMatch
 */

/* --- forward decls --- */
asm void CommBroadcast_GetKartLap(void);
asm void CommBroadcast_SetKartLap(void);
asm void CommBroadcast_GetKartRankNibble(void);
asm void CommBroadcast_SetKartRankNibble(void);
asm void CommBroadcast_ScanForMySyncMatch(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void CommBroadcast_GetKartLap(void) { /* 0x800848C4 size:0x38 */
    nofralloc
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne CommBroadcast_GetKartLap_L_800848DC
    lis r4, g_ringBufferBase@ha
    addi r0, r4, g_ringBufferBase@l
    b CommBroadcast_GetKartLap_L_800848F0
    CommBroadcast_GetKartLap_L_800848DC:
    lwz r5, g_ringReadIdx(r13)
    lis r4, g_ringBufferBase@ha
    addi r0, r4, g_ringBufferBase@l
    mulli r4, r5, 0xdc
    add r0, r0, r4
    CommBroadcast_GetKartLap_L_800848F0:
    add r3, r0, r3
    lbz r3, 0xd6(r3)
    blr
}

asm void CommBroadcast_SetKartLap(void) { /* 0x800848FC size:0x38 */
    nofralloc
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne CommBroadcast_SetKartLap_L_80084914
    lis r5, g_ringBufferBase@ha
    addi r0, r5, g_ringBufferBase@l
    b CommBroadcast_SetKartLap_L_80084928
    CommBroadcast_SetKartLap_L_80084914:
    lwz r6, g_ringReadIdx(r13)
    lis r5, g_ringBufferBase@ha
    addi r0, r5, g_ringBufferBase@l
    mulli r5, r6, 0xdc
    add r0, r0, r5
    CommBroadcast_SetKartLap_L_80084928:
    add r3, r0, r3
    stb r4, 0xd6(r3)
    blr
}

asm void CommBroadcast_GetKartRankNibble(void) { /* 0x80084934 size:0x84 */
    nofralloc
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne CommBroadcast_GetKartRankNibble_L_8008494C
    lis r4, g_ringBufferBase@ha
    addi r4, r4, g_ringBufferBase@l
    b CommBroadcast_GetKartRankNibble_L_80084960
    CommBroadcast_GetKartRankNibble_L_8008494C:
    lwz r5, g_ringReadIdx(r13)
    lis r4, g_ringBufferBase@ha
    addi r0, r4, g_ringBufferBase@l
    mulli r4, r5, 0xdc
    add r4, r0, r4
    CommBroadcast_GetKartRankNibble_L_80084960:
    cmpwi r3, 0x0
    bne CommBroadcast_GetKartRankNibble_L_80084978
    lbz r0, 0xd4(r4)
    extlwi r0, r0, 5, 24
    srawi r3, r0, 28
    blr
    CommBroadcast_GetKartRankNibble_L_80084978:
    cmpwi r3, 0x1
    bne CommBroadcast_GetKartRankNibble_L_80084990
    lbz r0, 0xd4(r4)
    extlwi r0, r0, 5, 28
    srawi r3, r0, 28
    blr
    CommBroadcast_GetKartRankNibble_L_80084990:
    cmpwi r3, 0x2
    bne CommBroadcast_GetKartRankNibble_L_800849A8
    lbz r0, 0xd5(r4)
    extlwi r0, r0, 5, 24
    srawi r3, r0, 28
    blr
    CommBroadcast_GetKartRankNibble_L_800849A8:
    lbz r0, 0xd5(r4)
    extlwi r0, r0, 5, 28
    srawi r3, r0, 28
    blr
}

asm void CommBroadcast_SetKartRankNibble(void) { /* 0x800849B8 size:0x90 */
    nofralloc
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne CommBroadcast_SetKartRankNibble_L_800849D0
    lis r5, g_ringBufferBase@ha
    addi r6, r5, g_ringBufferBase@l
    b CommBroadcast_SetKartRankNibble_L_800849E4
    CommBroadcast_SetKartRankNibble_L_800849D0:
    lwz r6, g_ringReadIdx(r13)
    lis r5, g_ringBufferBase@ha
    addi r0, r5, g_ringBufferBase@l
    mulli r5, r6, 0xdc
    add r6, r0, r5
    CommBroadcast_SetKartRankNibble_L_800849E4:
    cmpwi r3, 0x0
    bne CommBroadcast_SetKartRankNibble_L_800849FC
    extsb r5, r4
    lbz r0, 0xd4(r6)
    rlwimi r0, r5, 4, 24, 27
    stb r0, 0xd4(r6)
    CommBroadcast_SetKartRankNibble_L_800849FC:
    cmpwi r3, 0x1
    bne CommBroadcast_SetKartRankNibble_L_80084A14
    extsb r5, r4
    lbz r0, 0xd4(r6)
    rlwimi r0, r5, 0, 28, 31
    stb r0, 0xd4(r6)
    CommBroadcast_SetKartRankNibble_L_80084A14:
    cmpwi r3, 0x2
    bne CommBroadcast_SetKartRankNibble_L_80084A2C
    extsb r5, r4
    lbz r0, 0xd5(r6)
    rlwimi r0, r5, 4, 24, 27
    stb r0, 0xd5(r6)
    CommBroadcast_SetKartRankNibble_L_80084A2C:
    cmpwi r3, 0x3
    bnelr
    extsb r3, r4
    lbz r0, 0xd5(r6)
    rlwimi r0, r3, 0, 28, 31
    stb r0, 0xd5(r6)
    blr
}

asm void CommBroadcast_ScanForMySyncMatch(void) { /* 0x80084A48 size:0x3C */
    nofralloc
    lwz r5, g_ringReadIdx(r13)
    li r3, 0x0
    lwz r6, lbl_806D11A0(r13)
    b CommBroadcast_ScanForMySyncMatch_L_80084A5C
    CommBroadcast_ScanForMySyncMatch_L_80084A58:
    addi r3, r3, 0x1
    CommBroadcast_ScanForMySyncMatch_L_80084A5C:
    clrlwi r0, r3, 24
    add r4, r5, r0
    slwi r0, r4, 26
    srwi r4, r4, 31
    subf r0, r4, r0
    rotlwi r0, r0, 6
    add r0, r0, r4
    cmpw r6, r0
    bne CommBroadcast_ScanForMySyncMatch_L_80084A58
    blr
}

