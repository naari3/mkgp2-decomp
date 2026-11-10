#include "game/types/TEXPalette.h"

typedef struct TEXPaletteEntry {
    unsigned int words[2];
} TEXPaletteEntry;

extern int g_texPaletteHeap;
extern void *lbl_806CF010;
extern char lbl_80312FE8[];

extern int sprintf(char *dst, const char *fmt, ...);
extern void OSFreeToHeap(void *heap, void *ptr);

void TEXReleasePalette(TEXPalette *palette)
{
    char buf[0x200];

    sprintf(buf, lbl_80312FE8, palette, palette->data);
    if (g_texPaletteHeap == -1) {
        OSFreeToHeap(lbl_806CF010, palette->data);
    } else {
        OSFreeToHeap((void *)g_texPaletteHeap, palette->data);
    }
    palette->data = 0;
}

TEXPaletteEntry *TEXGetPaletteEntry(TEXPalette *palette, unsigned int index)
{
    return palette->entries + index;
}
