#include "game/TextDraw801F.h"
#include "game/types/sjis_word.h"
#include "libc/stdarg.h"

extern "C" int OSDisableInterrupts(void);
extern "C" void OSRestoreInterrupts(int);
extern "C" int vsprintf(char *, const char *, va_list);

static inline unsigned short LookupWide(const char *cursor) {
    int glyph = 0;
    int i;
    for (i = 0; i < 654; ++i) {
        if (SJIS_WORD(cursor) == lbl_804E5590[i].code) {
            glyph = lbl_804E5590[i].card;
            break;
        }
    }
    return glyph;
}

static inline unsigned short LookupNarrow(const char *cursor) {
    int glyph = 654;
    int i;
    for (i = 654; i < 739; ++i) {
        if (*cursor == lbl_804E5590[i].code) {
            glyph = lbl_804E5590[i].card;
            break;
        }
    }
    return glyph;
}

static inline void DecodeText(TextDraw801F *self, char *cursor) {
    unsigned short *out = self->glyphs;
    int count = 0;
    for (; *cursor && count < 255; ++count, ++out, ++cursor) {
        if (SJIS_WORD(cursor) & 0x8000) {
            *out = LookupWide(cursor);
            ++cursor;
        } else if (*cursor == '\n') {
            *out = 0xC000;
        } else {
            *out = LookupNarrow(cursor);
        }
    }
    if (count < 255) {
        *out = 0xFFFF;
    } else {
        self->glyphs[255] = 0xFFFF;
    }
}

extern "C" void TexMgr_SetTexture(TextManager *self, const char *format, ...) {
    char buffer[0x200];
    va_list args;
    int enabled = OSDisableInterrupts();
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    OSRestoreInterrupts(enabled);
    DecodeText((TextDraw801F *)self, buffer);
}
