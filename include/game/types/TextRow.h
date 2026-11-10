#ifndef GAME_TYPES_TEXTROW_H
#define GAME_TYPES_TEXTROW_H

/* Declare before including (each user already does): PtrVec, TextSprite */

struct TextRow {
    PtrVec<TextSprite *> sprites;
    int layer;
    int align;
    int visible;
    unsigned char alpha;
    float x;
    float y;
    float sx;
    float sy;
    unsigned char dirty;
    ~TextRow();
};

#endif /* GAME_TYPES_TEXTROW_H */
