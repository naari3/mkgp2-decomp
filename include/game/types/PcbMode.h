#ifndef GAME_TYPES_PCBMODE_H
#define GAME_TYPES_PCBMODE_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct PcbMode PcbMode;
struct PcbMode {
    /* 0x000 */ unsigned char pad_000[0x8];
    /* 0x008 */ int light;  /* also: mode */
};

#endif /* GAME_TYPES_PCBMODE_H */
