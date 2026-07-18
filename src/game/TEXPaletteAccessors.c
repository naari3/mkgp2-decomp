typedef struct TEXPalette {
    void *data;
    unsigned int pad;
    struct TEXPaletteEntry *entries;
} TEXPalette;

typedef struct TEXPaletteEntry {
    unsigned int words[2];
} TEXPaletteEntry;

extern int lbl_806CEFA0;
extern void *lbl_806CF010;
extern char lbl_80312FE8[];

extern int fn_80276C50(char *dst, const char *fmt, ...);
extern void OSFreeToHeap(void *heap, void *ptr);

void TEXReleasePalette(TEXPalette *palette)
{
    char buf[0x200];

    fn_80276C50(buf, lbl_80312FE8, palette, palette->data);
    if (lbl_806CEFA0 == -1) {
        OSFreeToHeap(lbl_806CF010, palette->data);
    } else {
        OSFreeToHeap((void *)lbl_806CEFA0, palette->data);
    }
    palette->data = 0;
}

TEXPaletteEntry *TEXGetPaletteEntry(TEXPalette *palette, unsigned int index)
{
    return palette->entries + index;
}
