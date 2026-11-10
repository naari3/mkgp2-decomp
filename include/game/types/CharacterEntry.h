#ifndef GAME_TYPES_CHARACTERENTRY_H
#define GAME_TYPES_CHARACTERENTRY_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CharacterEntry CharacterEntry;
struct CharacterEntry {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ const char *file;
    /* 0x008 */ const char *anim;
    /* 0x00C */ const char *other;
    /* 0x010 */ unsigned char pad_010[0x8];
    /* 0x018 */ const char **motion;
    /* 0x01C */ unsigned char pad_01C[0x4];
    /* 0x020 */ unsigned char goalAnim;
    /* 0x021 */ unsigned char pad_021[0x7];
    /* 0x028 */ unsigned char timeoutAnim;
    /* 0x029 */ unsigned char pad_029[0x3];
};

#endif /* GAME_TYPES_CHARACTERENTRY_H */
