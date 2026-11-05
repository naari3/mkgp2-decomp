#include "game/TextDraw801F.h"
extern "C" void fn_80120A08(int);
static inline void ReleaseGlyph(GlyphDraw801F *glyph) {
    fn_80120A08(glyph->normalResource);
}
static inline void ReleaseGlyphs(TextDraw801F *self) {
    GlyphDraw801F *table = lbl_804E5590;
    TextDraw801F *cursor = self;
    int i = 0;
    for (; i < 256; ++i, cursor = (TextDraw801F *)((char *)cursor + 2)) {
        unsigned short id = cursor->glyphs[0];
        if (id == 0xFFFF) break;
        ReleaseGlyph(&table[id]);
    }
}
extern "C" void fn_801F95A0(TextDraw801F *self) {
    ReleaseGlyphs(self);
    self->glyphs[0] = 0xFFFF;
}
