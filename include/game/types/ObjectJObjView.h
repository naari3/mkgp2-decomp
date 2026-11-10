#ifndef GAME_TYPES_OBJECTJOBJVIEW_H
#define GAME_TYPES_OBJECTJOBJVIEW_H

struct HSD_JObj;

/* Merged from 4 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ObjectJObjView ObjectJObjView;
struct ObjectJObjView {
    /* 0x000 */ unsigned char pad_000[0x2];
    /* 0x002 */ unsigned char dirty;
    /* 0x003 */ unsigned char pad_003[0x5];
    /* 0x008 */ float frame;
    /* 0x00C */ unsigned char pad_00C[0x8];
    /* 0x014 */ float end_frame;
    /* 0x018 */ void *override;
    /* 0x01C */ unsigned char pad_01C[0x10];
    /* 0x02C */ struct HSD_JObj *jobj;
};

#endif /* GAME_TYPES_OBJECTJOBJVIEW_H */
