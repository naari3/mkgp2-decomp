#include <game/DebugTextPrivate.h>

typedef struct DebugTexObj { unsigned int words[8]; } DebugTexObj;
extern char *OSGetFontTexture(const char *, void **, int *, int *, int *);
extern void GXInitTexObj(void *, void *, unsigned short, unsigned short, int, int, int, unsigned char);
extern void GXInitTexObjLOD(void *, int, int, float, float, float, unsigned char, unsigned char, int);
extern void GXLoadTexObj(void *, int);
extern void GXBegin(int, int, unsigned short);

static inline void EmitTextVertex(short x, short y, unsigned char color, short s, short t)
{
    *(volatile short *)0xCC008000 = x;
    *(volatile short *)0xCC008000 = y;
    *(volatile unsigned char *)0xCC008000 = color;
    *(volatile short *)0xCC008000 = s;
    *(volatile short *)0xCC008000 = t;
}

void TextRenderer_DrawEntry(DebugDisplayContext *self, DebugTextEntry *entry)
{
    DebugTexObj texture;
    void *image;
    int s, t, width;
    char *text;
    void *loaded;
    int height;
    int dy;
    int dx;

    DebugFontHeader *font = self->font;
    if (entry->color > 8) entry->color = 8;
    height = font->cellHeight;
    text = entry->text;
    dx = 0;
    dy = 0;
    loaded = 0;
    while (*text) {
        switch (*text) {
        case '\n':
            dx = 0;
            dy = height * entry->scale + dy;
            text++;
            break;
        case ' ':
        case 0x8140:
            text = OSGetFontTexture(text, &image, &s, &t, &width);
            dx = width * entry->scale + dx;
            break;
        default:
            text = OSGetFontTexture(text, &image, &s, &t, &width);
            if (loaded != image) {
                GXInitTexObj(&texture, image, self->font->sheetWidth, self->font->sheetHeight,
                             self->font->sheetFormat, 0, 0, 0);
                GXInitTexObjLOD(&texture, 1, 1, lbl_806DA278, lbl_806DA278, lbl_806DA278, 0, 0, 0);
                GXLoadTexObj(&texture, 7);
                loaded = image;
            }
            {
                unsigned char color;
                short s0, s1, t0, t1;
                short x0, x1, y0, y1;
                x0 = entry->x + dx;
                y0 = entry->y + dy;
                x1 = self->font->cellWidth * entry->scale + x0;
                y1 = self->font->cellHeight * entry->scale + y0;
                s0 = s;
                s1 = s + self->font->cellWidth;
                t0 = t;
                t1 = t + self->font->cellHeight;
                color = entry->color;
                GXBegin(0x80, 0, 4);
                EmitTextVertex(x0, y0, color, s0, t0);
                EmitTextVertex(x1, y0, color, s1, t0);
                EmitTextVertex(x1, y1, color, s1, t1);
                EmitTextVertex(x0, y1, color, s0, t1);
            }
            dx = width * entry->scale + dx;
            break;
        }
    }
}
