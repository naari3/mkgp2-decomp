/* === extracted from auto_03_80074910_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern int g_ccClass;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern int lbl_806D112C;
extern const float lbl_806D2EB0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned char lbl_80598A60[];

/* --- function index (5 fns, .text 0x80074910..0x80074C30) ---
 * [  0] 0x80074910 size:0xC0    global TaRecord_GetEntry_Indexed
 * [  1] 0x800749D0 size:0xD0    global TaRecord_GetEntry_Current
 * [  2] 0x80074AA0 size:0xBC    global TaRecord_GetTime_Indexed
 * [  3] 0x80074B5C size:0xCC    global TaRecord_GetTime_Current
 * [  4] 0x80074C28 size:0x8     global TaRecord_GetLastInsertedRank
 */

/* --- forward decls --- */
void *TaRecord_GetEntry_Indexed(int index, int cc, int cup, int longRound, int reverse);
void *TaRecord_GetEntry_Current(int index);
asm void TaRecord_GetTime_Indexed(void);
asm void TaRecord_GetTime_Current(void);
int TaRecord_GetLastInsertedRank(void);

/* --- asm function bodies (.text order = fn address order) --- */
void *TaRecord_GetEntry_Indexed(int index, int cc, int cup, int longRound, int reverse) { /* 0x80074910 size:0xC0 */
    if (cc == 0) return 0;
    if (cc < 0 || cc >= 3) return 0;
    if (cup < 0 || cup >= 9) return 0;
    if (longRound < 0 || longRound >= 2) return 0;
    if (reverse < 0 || reverse >= 2) return 0;
    if (index < 0 || index >= 10) return 0;
    return lbl_80598A60 + 0x4e0 + (cc - 1) * 0x1680 + cup * 0x280 + longRound * 0x140 + reverse * 0xa0 + index * 0x10;
}

void *TaRecord_GetEntry_Current(int index) { /* 0x800749D0 size:0xD0 */
    int cc = g_ccClass;
    int cup = g_cupId;
    int longRound = g_longRoundFlag;
    int reverse = g_reverseRoundFlag;
    if (cc == 0) return 0;
    if (cc < 0 || cc >= 3) return 0;
    if (cup < 0 || cup >= 9) return 0;
    if (longRound < 0 || longRound >= 2) return 0;
    if (reverse < 0 || reverse >= 2) return 0;
    if (index < 0 || index >= 10) return 0;
    return lbl_80598A60 + 0x4e0 + (cc - 1) * 0x1680 + cup * 0x280 + longRound * 0x140 + reverse * 0xa0 + index * 0x10;
}

asm void TaRecord_GetTime_Indexed(void) { /* 0x80074AA0 size:0xBC */
    nofralloc
    cmpwi r4, 0x0
    bne TaRecord_GetTime_Indexed_L_80074AB0
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Indexed_L_80074AB0:
    blt TaRecord_GetTime_Indexed_L_80074ABC
    cmpwi r4, 0x3
    blt TaRecord_GetTime_Indexed_L_80074AC4
    TaRecord_GetTime_Indexed_L_80074ABC:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Indexed_L_80074AC4:
    cmpwi r5, 0x0
    blt TaRecord_GetTime_Indexed_L_80074AD4
    cmpwi r5, 0x9
    blt TaRecord_GetTime_Indexed_L_80074ADC
    TaRecord_GetTime_Indexed_L_80074AD4:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Indexed_L_80074ADC:
    cmpwi r6, 0x0
    blt TaRecord_GetTime_Indexed_L_80074AEC
    cmpwi r6, 0x2
    blt TaRecord_GetTime_Indexed_L_80074AF4
    TaRecord_GetTime_Indexed_L_80074AEC:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Indexed_L_80074AF4:
    cmpwi r7, 0x0
    blt TaRecord_GetTime_Indexed_L_80074B04
    cmpwi r7, 0x2
    blt TaRecord_GetTime_Indexed_L_80074B0C
    TaRecord_GetTime_Indexed_L_80074B04:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Indexed_L_80074B0C:
    cmpwi r3, 0x0
    blt TaRecord_GetTime_Indexed_L_80074B1C
    cmpwi r3, 0xa
    blt TaRecord_GetTime_Indexed_L_80074B24
    TaRecord_GetTime_Indexed_L_80074B1C:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Indexed_L_80074B24:
    mulli r4, r4, 0x1c20
    lis r8, lbl_80598A60@ha
    slwi r0, r3, 2
    addi r8, r8, lbl_80598A60@l
    mulli r3, r5, 0x320
    add r5, r8, r4
    mulli r4, r6, 0x190
    add r5, r5, r3
    mulli r3, r7, 0xc8
    add r4, r5, r4
    add r3, r4, r3
    add r3, r3, r0
    lfs f1, 0x15c0(r3)
    blr
}

asm void TaRecord_GetTime_Current(void) { /* 0x80074B5C size:0xCC */
    nofralloc
    lwz r0, g_ccClass(r13)
    lwz r6, g_cupId(r13)
    cmpwi r0, 0x0
    lwz r7, g_longRoundFlag(r13)
    lwz r8, g_reverseRoundFlag(r13)
    bne TaRecord_GetTime_Current_L_80074B7C
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Current_L_80074B7C:
    blt TaRecord_GetTime_Current_L_80074B88
    cmpwi r0, 0x3
    blt TaRecord_GetTime_Current_L_80074B90
    TaRecord_GetTime_Current_L_80074B88:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Current_L_80074B90:
    cmpwi r6, 0x0
    blt TaRecord_GetTime_Current_L_80074BA0
    cmpwi r6, 0x9
    blt TaRecord_GetTime_Current_L_80074BA8
    TaRecord_GetTime_Current_L_80074BA0:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Current_L_80074BA8:
    cmpwi r7, 0x0
    blt TaRecord_GetTime_Current_L_80074BB8
    cmpwi r7, 0x2
    blt TaRecord_GetTime_Current_L_80074BC0
    TaRecord_GetTime_Current_L_80074BB8:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Current_L_80074BC0:
    cmpwi r8, 0x0
    blt TaRecord_GetTime_Current_L_80074BD0
    cmpwi r8, 0x2
    blt TaRecord_GetTime_Current_L_80074BD8
    TaRecord_GetTime_Current_L_80074BD0:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Current_L_80074BD8:
    cmpwi r3, 0x0
    blt TaRecord_GetTime_Current_L_80074BE8
    cmpwi r3, 0xa
    blt TaRecord_GetTime_Current_L_80074BF0
    TaRecord_GetTime_Current_L_80074BE8:
    lfs f1, lbl_806D2EB0(r2)
    blr
    TaRecord_GetTime_Current_L_80074BF0:
    mulli r4, r0, 0x1c20
    lis r5, lbl_80598A60@ha
    slwi r0, r3, 2
    addi r5, r5, lbl_80598A60@l
    mulli r3, r6, 0x320
    add r5, r5, r4
    mulli r4, r7, 0x190
    add r5, r5, r3
    mulli r3, r8, 0xc8
    add r4, r5, r4
    add r3, r4, r3
    add r3, r3, r0
    lfs f1, 0x15c0(r3)
    blr
}

int TaRecord_GetLastInsertedRank(void) { /* 0x80074C28 size:0x8 */
    return lbl_806D112C;
}

