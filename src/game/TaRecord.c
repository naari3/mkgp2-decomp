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
float TaRecord_GetTime_Indexed(int index, int cc, int cup, int longRound, int reverse);
float TaRecord_GetTime_Current(int index);
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

float TaRecord_GetTime_Indexed(int index, int cc, int cup, int longRound, int reverse) { /* 0x80074AA0 size:0xBC */
    if (cc == 0) return lbl_806D2EB0;
    if (cc < 0 || cc >= 3) return lbl_806D2EB0;
    if (cup < 0 || cup >= 9) return lbl_806D2EB0;
    if (longRound < 0 || longRound >= 2) return lbl_806D2EB0;
    if (reverse < 0 || reverse >= 2) return lbl_806D2EB0;
    if (index < 0 || index >= 10) return lbl_806D2EB0;
    return (*(float (*)[3][9][2][2][50])(lbl_80598A60 + 0x15c0))[cc][cup][longRound][reverse][index];
}

float TaRecord_GetTime_Current(int index) { /* 0x80074B5C size:0xCC */
    int cc = g_ccClass;
    int cup = g_cupId;
    int longRound = g_longRoundFlag;
    int reverse = g_reverseRoundFlag;
    if (cc == 0) return lbl_806D2EB0;
    if (cc < 0 || cc >= 3) return lbl_806D2EB0;
    if (cup < 0 || cup >= 9) return lbl_806D2EB0;
    if (longRound < 0 || longRound >= 2) return lbl_806D2EB0;
    if (reverse < 0 || reverse >= 2) return lbl_806D2EB0;
    if (index < 0 || index >= 10) return lbl_806D2EB0;
    return (*(float (*)[3][9][2][2][50])(lbl_80598A60 + 0x15c0))[cc][cup][longRound][reverse][index];
}

int TaRecord_GetLastInsertedRank(void) { /* 0x80074C28 size:0x8 */
    return lbl_806D112C;
}

