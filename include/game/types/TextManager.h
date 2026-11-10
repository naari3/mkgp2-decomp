#ifndef GAME_TYPES_TEXTMANAGER_H
#define GAME_TYPES_TEXTMANAGER_H

struct TextManager {
    TextManager();
    ~TextManager() {}
    unsigned char pad0[0x18];
    int x18;
    unsigned char pad1c[4];
    unsigned int color;
    unsigned char pad24[0x234 - 0x24];
};

#endif /* GAME_TYPES_TEXTMANAGER_H */
