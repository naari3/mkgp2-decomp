/*
 * Static course/texture parameter table lookups (0x8013BE98..0x8013C2D4).
 * Sits right before GetTextureByIdAndLang, which uses the same tables.
 * fn_8013BFF8: the target keeps a separate addi for the 0x14E8/0x178C/
 * 0x1968 sub-table offsets instead of folding them into the load; this
 * needs `#pragma opt_propagation off` and a named row pointer.
 */

#include "game/types/Entry1C.h"

#include "game/types/Entry10.h"

extern Entry1C CourseTables_rodata_8035C6C4;
extern Entry1C CourseTables_rodata_8035E260[];
extern Entry10 CourseTables_rodata_8035E220[4];
extern int CourseTables_rodata_8035E120[8][2][4];
extern int CourseTables_rodata_8035E0E0[8][2];
extern int CourseTables_rodata_803600AC[13];
extern void *lbl_806CF640;
extern void *lbl_8048E548[0xA0][2];

extern int isJapanese(void);

Entry1C *fn_8013BE98(int id) {
    if (id > 0 && id < 0x115) {
        return &CourseTables_rodata_8035E260[id];
    }
    return &CourseTables_rodata_8035C6C4;
}

Entry10 *fn_8013BEC8(int id) {
    if (id < 0 || id >= 4) {
        return 0;
    }
    return &CourseTables_rodata_8035E220[id];
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
    if (course >= 9) {
        idx = course - 9;
    } else {
        idx = course - 1;
    }
    return CourseTables_rodata_8035E120[idx][a][b];
}

int fn_8013BF70(int course, int a) {
    int idx;
    if (course <= 0 || course >= 0x11) {
        return -1;
    }
    if (a < 0 || a >= 2) {
        return -1;
    }
    if (course >= 9) {
        idx = course - 9;
    } else {
        idx = course - 1;
    }
    return CourseTables_rodata_8035E0E0[idx][a];
}

int fn_8013BFCC(int id) {
    if (id < 0 || id >= 0xD) {
        return -1;
    }
    return CourseTables_rodata_803600AC[id];
}

typedef struct CourseTexRow {
    int id;
    void *tex[5];
} CourseTexRow;

typedef struct CourseTexTables {
    unsigned char pad0000[0x14E8];
    CourseTexRow def[8];     /* 0x14E8 */
    unsigned char pad15A8[0x178C - 0x15A8];
    CourseTexRow card[8];    /* 0x178C */
    unsigned char pad184C[0x1968 - 0x184C];
    CourseTexRow noCard[8];  /* 0x1968 */
} CourseTexTables;

extern CourseTexTables CourseTables_rodata_8035C6B8;
extern signed char lbl_80598A60[];
extern unsigned char IsCardValid(void);

/* fakematch (pragma): natural code is the same body without the pragma;
 * the original TU most likely owned this .rodata, so CW kept the
 * section-base + offset addi on its own. */
#pragma exceptions on
#pragma opt_propagation off
void *fn_8013BFF8(int course, int kind, int lang)
{
    CourseTexTables *t = &CourseTables_rodata_8035C6B8;
    int idx;
    CourseTexRow *row;

    if (course <= 0 || course >= 0x11) {
        return lbl_806CF640;
    }
    if (kind < 0 || kind >= 5) {
        return lbl_806CF640;
    }
    if (lang < 0) {
        lang = isJapanese();
    }
    if (course >= 9) {
        idx = course - 9;
    } else {
        idx = course - 1;
    }
    if (!lbl_80598A60[0x20]) {
        row = t->def;
        return row[idx].tex[kind];
    }
    if (IsCardValid() == 1) {
        row = t->card;
        return row[idx].tex[kind];
    }
    row = t->noCard;
    return row[idx].tex[kind];
}
#pragma opt_propagation reset
#pragma exceptions reset


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
