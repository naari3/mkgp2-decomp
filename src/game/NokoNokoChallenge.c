/*
 * NokoNokoChallenge: 2-fn TU for the auto_NokoNokoChallenge_{Sa,Ca}_text
 * single-fn extab groups. SaveResult is matched C (CW auto-emits extab),
 * CalcResultText is asm_fn with manually emitted extab/extabindex via
 * tools/postprocess_extab_user.py (.extab_user -> extab, .extabindex_user
 * -> extabindex, plus @etb_/@eti_ symbol renames).
 */

extern int g_characterId;
extern int g_cupId;
extern int g_roundIndex;
extern int g_ccClass;
extern char g_playerData[0x1DC];
extern void *lbl_806D10A0[2];
extern int lbl_80355840[13][2];

extern unsigned char IsCardValid(void);
extern void SoundMgr_PlaySE(int);
extern void fn_8016C554(int);
extern void fn_80192208(int);
extern unsigned char RoundCupIsCompleted(void *, int, int, int);
extern void fn_801D6558(void *, int, int, int);
extern void PlayStats_OnMissionResult_Stub(void);
extern void Empty_NokoNokoHook(int, int, int);
extern int fn_8024F588(void);

asm void NokoNokoChallenge_CalcResultText(void);

#pragma exceptions on
void NokoNokoChallenge_SaveResult(void *param_1, int param_2, unsigned int param_3) {
    int characterId = g_characterId;
    if (IsCardValid() == 1) {
        param_3 = ((unsigned int)(-param_2 & ~param_2)) >> 31;
    }
    if ((param_3 & 0xff) == 1) {
        fn_8016C554(1);
        if (g_cupId == 0xe) {
            fn_80192208(g_characterId + 9);
        }
        SoundMgr_PlaySE(lbl_80355840[characterId][0]);
    } else {
        fn_8016C554(0);
        if (g_cupId == 0xe) {
            fn_80192208(g_characterId + 9);
        }
        SoundMgr_PlaySE(lbl_80355840[characterId][1]);
    }
}
#pragma exceptions reset

/* --- CalcResultText extab (manual emit, .extab_user -> extab via postprocess) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NokoNokoChallenge_CalcResultText[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- CalcResultText extabindex (manual emit) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_NokoNokoChallenge_CalcResultText = {
    (void *)&NokoNokoChallenge_CalcResultText, 0x00000174, (void *)extab_NokoNokoChallenge_CalcResultText
};

#pragma exceptions off
asm void NokoNokoChallenge_CalcResultText(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r28, r4
    mr r29, r5
    lwz r31, lbl_806D10A0(r13)
    cmplwi r31, 0x0
    bne L_80122D0C
    li r31, 0x0
L_80122D0C:
    lwz r5, g_roundIndex(r13)
    li r3, 0x3
    clrlwi. r0, r28, 24
    li r30, 0x0
    xor r4, r5, r3
    srawi r3, r4, 1
    and r0, r4, r5
    subf r0, r0, r3
    srwi r27, r0, 31
    beq L_80122E08
    lwz r3, g_cupId(r13)
    cmpwi r3, 0x9
    blt L_80122D48
    subi r0, r3, 0x9
    b L_80122D4C
L_80122D48:
    subi r0, r3, 0x1
L_80122D4C:
    cmpwi r0, 0x0
    blt L_80122D94
    lis r3, g_playerData@ha
    lwz r4, g_ccClass(r13)
    lwz r5, g_cupId(r13)
    addi r3, r3, g_playerData@l
    mr r6, r27
    bl RoundCupIsCompleted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne L_80122D7C
    li r30, 0x1
L_80122D7C:
    lis r3, g_playerData@ha
    lwz r4, g_cupId(r13)
    addi r3, r3, g_playerData@l
    mr r5, r27
    li r6, 0x1
    bl fn_801D6558
L_80122D94:
    bl PlayStats_OnMissionResult_Stub
    lwz r3, g_cupId(r13)
    cmpwi r3, 0x9
    blt L_80122DAC
    subi r3, r3, 0x9
    b L_80122DB0
L_80122DAC:
    subi r3, r3, 0x1
L_80122DB0:
    lwz r4, g_roundIndex(r13)
    li r0, 0x3
    cmpwi r3, 0x0
    lwz r5, g_ccClass(r13)
    xor r0, r4, r0
    srawi r3, r0, 1
    and r0, r0, r4
    subf r0, r0, r3
    srwi r0, r0, 31
    blt L_80122DEC
    cmpwi r0, 0x0
    blt L_80122DEC
    cmpwi r5, 0x0
    blt L_80122DEC
    bl IsCardValid
L_80122DEC:
    cmplwi r31, 0x0
    beq L_80122E38
    mr r3, r31
    mr r5, r29
    li r4, 0x0
    bl Empty_NokoNokoHook
    b L_80122E38
L_80122E08:
    lis r3, g_playerData@ha
    lwz r4, g_cupId(r13)
    addi r3, r3, g_playerData@l
    mr r5, r27
    li r6, 0x0
    bl fn_801D6558
    cmplwi r31, 0x0
    beq L_80122E38
    mr r3, r31
    mr r5, r29
    li r4, -0x1
    bl Empty_NokoNokoHook
L_80122E38:
    bl fn_8024F588
    stb r28, 0x20(r3)
    mr r3, r30
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
#pragma exceptions reset
