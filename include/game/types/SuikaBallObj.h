#ifndef GAME_TYPES_SUIKABALLOBJ_H
#define GAME_TYPES_SUIKABALLOBJ_H

struct SuikaNormal;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SuikaBallObj SuikaBallObj;
struct SuikaBallObj {
    /* 0x000 */ struct SuikaNormal *obj;
    /* 0x004 */ float scale;
    /* 0x008 */ float mtx[3][4];
    /* 0x038 */ float f38[10];
    /* 0x060 */ unsigned char b60;
    /* 0x061 */ unsigned char b61;
    /* 0x062 */ unsigned char pad_062[0x2];
    /* 0x064 */ float f64[6];
};

#endif /* GAME_TYPES_SUIKABALLOBJ_H */
