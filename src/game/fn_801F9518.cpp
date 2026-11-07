#include "game/TextDraw801F.h"
extern "C" void fn_80120A08(int);
static inline void ReleaseGlyph(unsigned short id) {
    GlyphDraw801F *glyph = &lbl_804E5590[id];
    fn_80120A08(glyph->largeResource);
}
extern "C" void fn_801F9518(void *object) {
    TextDraw801F *cursor;
    TextDraw801F *self = (TextDraw801F *)object;
    cursor = self;
    for (int i = 0; i < 256; ++i, cursor = (TextDraw801F *)((char *)cursor + 2)) {
        unsigned short id = cursor->glyphs[0];
        if (id == 0xFFFF) break;
        ReleaseGlyph(id);
    }
    self->glyphs[0] = 0xFFFF;
}
