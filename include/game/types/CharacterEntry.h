#ifndef GAME_TYPES_CHARACTERENTRY_H
#define GAME_TYPES_CHARACTERENTRY_H

typedef struct CharacterEntry {
    unsigned char pad00[4];
    const char *file;
    const char *anim;
    const char *other;
    unsigned char pad10[8];
    const char **motion;
    unsigned char pad1C[16];
} CharacterEntry;

#endif /* GAME_TYPES_CHARACTERENTRY_H */
