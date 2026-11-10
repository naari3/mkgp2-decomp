#ifndef GAME_TYPES_GLYPHTEXT_H
#define GAME_TYPES_GLYPHTEXT_H

/* Declare before including (each user already does): TextManager */

struct GlyphText {
    char pad000[0x24];
    unsigned short glyphs[(0x230 - 0x24) / 2];
    GlyphText();
    TextManager *tm() { return (TextManager *)this; }
};

#endif /* GAME_TYPES_GLYPHTEXT_H */
