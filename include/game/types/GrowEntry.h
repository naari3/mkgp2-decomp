#ifndef GAME_TYPES_GROWENTRY_H
#define GAME_TYPES_GROWENTRY_H

struct GrowFace;
struct GrowSub;
struct HSD_JObj;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GrowEntry GrowEntry;
struct GrowEntry {
    /* 0x000 */ struct HSD_JObj *jobj;
    /* 0x004 */ struct GrowFace *faces;
    /* 0x008 */ int faceCount;
    /* 0x00C */ void *trigger;  /* also: anim */
    /* 0x010 */ int state;
    /* 0x014 */ float t;
    /* 0x018 */ float scale;
    /* 0x01C */ struct GrowSub *sub;
};

#endif /* GAME_TYPES_GROWENTRY_H */
