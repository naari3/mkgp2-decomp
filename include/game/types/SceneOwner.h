#ifndef GAME_TYPES_SCENEOWNER_H
#define GAME_TYPES_SCENEOWNER_H

struct VObj;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SceneOwner SceneOwner;
struct SceneOwner {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ unsigned char done;
    /* 0x005 */ unsigned char pad_005[0x3];
    /* 0x008 */ struct VObj *obj;
    /* 0x00C */ int value;
};

#endif /* GAME_TYPES_SCENEOWNER_H */
