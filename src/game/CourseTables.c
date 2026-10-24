/*
 * Static course/texture parameter table lookups (0x8013BE98..0x8013C2D4).
 * Sits right before GetTextureByIdAndLang, which uses the same tables.
 * fn_8013BFF8 stays asm: CW folds the 0x14E8/0x178C/0x1968 sub-table
 * offsets into the load displacement, the target keeps a separate addi.
 */

typedef struct Entry1C {
    int v[7];
} Entry1C;

typedef struct Entry10 {
    int v[4];
} Entry10;

extern Entry1C lbl_8035C6C4;
extern Entry1C lbl_8035E260[];
extern Entry10 lbl_8035E220[4];
extern int lbl_8035E120[8][2][4];
extern int lbl_8035E0E0[8][2];
extern int lbl_803600AC[13];
extern void *lbl_806CF640;
extern void *lbl_8048E548[0xA0][2];

extern int isJapanese(void);
extern void IsCardValid();

Entry1C *fn_8013BE98(int id) {
    if (id > 0 && id < 0x115) {
        return &lbl_8035E260[id];
    }
    return &lbl_8035C6C4;
}

Entry10 *fn_8013BEC8(int id) {
    if (id < 0 || id >= 4) {
        return 0;
    }
    return &lbl_8035E220[id];
}

int fn_8013BEF4(int course, int a, int b) {
    int idx;
    if (course <= 0 || course >= 0x11) {
        return -1;
    }
    if (a <= -1 || a >= 2) {
        return -1;
    }
    if (b < 0 || b >= 4) {
        return -1;
    }
    idx = course - 1;
    if (course >= 9) {
        idx = course - 9;
    }
    return lbl_8035E120[idx][a][b];
}

int fn_8013BF70(int course, int a) {
    int idx;
    if (course <= 0 || course >= 0x11) {
        return -1;
    }
    if (a < 0 || a >= 2) {
        return -1;
    }
    idx = course - 1;
    if (course >= 9) {
        idx = course - 9;
    }
    return lbl_8035E0E0[idx][a];
}

int fn_8013BFCC(int id) {
    if (id < 0 || id >= 0xD) {
        return -1;
    }
    return lbl_803600AC[id];
}

extern unsigned int lbl_8035C6B8[];
extern unsigned int lbl_80598A60[];
asm void fn_8013BFF8(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013BFF8[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013BFF8 = {
    (void *)&fn_8013BFF8, 0x00000108, (void *)extab_fn_8013BFF8
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013BFF8(void) { /* 0x8013BFF8 size:0x108 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr. r28, r3
    lis r3, lbl_8035C6B8@ha
    addi r30, r3, lbl_8035C6B8@l
    ble fn_8013BFF8_L_8013C030
    cmpwi r28, 0x11
    blt fn_8013BFF8_L_8013C038
    fn_8013BFF8_L_8013C030:
    lwz r3, lbl_806CF640(r13)
    b fn_8013BFF8_L_8013C0E0
    fn_8013BFF8_L_8013C038:
    cmpwi r29, 0x0
    blt fn_8013BFF8_L_8013C048
    cmpwi r29, 0x5
    blt fn_8013BFF8_L_8013C050
    fn_8013BFF8_L_8013C048:
    lwz r3, lbl_806CF640(r13)
    b fn_8013BFF8_L_8013C0E0
    fn_8013BFF8_L_8013C050:
    cmpwi r5, 0x0
    bge fn_8013BFF8_L_8013C05C
    bl isJapanese
    fn_8013BFF8_L_8013C05C:
    cmpwi r28, 0x9
    subi r31, r28, 0x1
    blt fn_8013BFF8_L_8013C06C
    subi r31, r28, 0x9
    fn_8013BFF8_L_8013C06C:
    lis r3, lbl_80598A60@ha
    addi r3, r3, lbl_80598A60@l
    lbz r0, 0x20(r3)
    extsb. r0, r0
    bne fn_8013BFF8_L_8013C09C
    mulli r3, r31, 0x18
    addi r4, r30, 0x14e8
    slwi r0, r29, 2
    add r3, r4, r3
    add r3, r3, r0
    lwz r3, 0x4(r3)
    b fn_8013BFF8_L_8013C0E0
    fn_8013BFF8_L_8013C09C:
    bl IsCardValid
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8013BFF8_L_8013C0C8
    mulli r3, r31, 0x18
    addi r4, r30, 0x178c
    slwi r0, r29, 2
    add r3, r4, r3
    add r3, r3, r0
    lwz r3, 0x4(r3)
    b fn_8013BFF8_L_8013C0E0
    fn_8013BFF8_L_8013C0C8:
    mulli r3, r31, 0x18
    addi r4, r30, 0x1968
    slwi r0, r29, 2
    add r3, r4, r3
    add r3, r3, r0
    lwz r3, 0x4(r3)
    fn_8013BFF8_L_8013C0E0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


void *fn_8013C100(int id, int kind, int lang) {
    if (id < 1 || id > 8) {
        return lbl_806CF640;
    }
    if (kind < 0 || kind >= 2) {
        return lbl_806CF640;
    }
    if (lang < 0) {
        lang = isJapanese();
    }
    return lbl_8048E548[0x28 + id + kind * 8][lang];
}

void *fn_8013C198(int id, int lang) {
    if (id < 1 || id > 8) {
        return lbl_806CF640;
    }
    if (lang < 0) {
        lang = isJapanese();
    }
    return lbl_8048E548[id + 0x18][lang];
}

void *fn_8013C204(int id, int lang) {
    if (id < 0 || id >= 8) {
        return lbl_806CF640;
    }
    if (lang < 0) {
        lang = isJapanese();
    }
    return lbl_8048E548[id + 0x11][lang];
}

void *fn_8013C26C(int id, int lang) {
    if (id < 0 || id >= 0xD) {
        return lbl_806CF640;
    }
    if (lang < 0) {
        lang = isJapanese();
    }
    return lbl_8048E548[id + 4][lang];
}
