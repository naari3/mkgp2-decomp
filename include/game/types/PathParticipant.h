#ifndef GAME_TYPES_PATHPARTICIPANT_H
#define GAME_TYPES_PATHPARTICIPANT_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct PathParticipant PathParticipant;
struct PathParticipant {
    /* 0x000 */ unsigned char pad_000[0x14];
    /* 0x014 */ int node;
    /* 0x018 */ unsigned char pad_018[0x42];
    /* 0x05A */ unsigned short segment;
    /* 0x05C */ unsigned char pad_05C[0x4];
    /* 0x060 */ int lap;
    /* 0x064 */ unsigned char pad_064[0x34];
};

#endif /* GAME_TYPES_PATHPARTICIPANT_H */
