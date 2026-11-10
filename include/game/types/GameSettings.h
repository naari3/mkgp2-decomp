#ifndef GAME_TYPES_GAMESETTINGS_H
#define GAME_TYPES_GAMESETTINGS_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GameSettings GameSettings;
struct GameSettings {
    /* 0x000 */ unsigned char pad_000[0x21];
    /* 0x021 */ signed char mediaSlot;
};

#endif /* GAME_TYPES_GAMESETTINGS_H */
