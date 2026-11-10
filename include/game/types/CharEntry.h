#ifndef GAME_TYPES_CHARENTRY_H
#define GAME_TYPES_CHARENTRY_H

typedef struct CharEntry {
    unsigned short card;
    unsigned short code;
    int width;
    int height;
    int advance;
} CharEntry;

#endif /* GAME_TYPES_CHARENTRY_H */
