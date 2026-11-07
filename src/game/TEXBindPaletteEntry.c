/* TEX palette bind cluster: initialise a GXTexObj (and its TLUT for CI
 * images) from one entry of a texture table. */

typedef struct TexImageDesc {
    unsigned short height;      /* 0x00 */
    unsigned short width;       /* 0x02 */
    int format;                 /* 0x04 */
    void *data;                 /* 0x08 */
    int wrapS;                  /* 0x0C */
    int wrapT;                  /* 0x10 */
    int minFilter;              /* 0x14 */
    int magFilter;              /* 0x18 */
    float lodBias;              /* 0x1C */
    unsigned char edgeLod;      /* 0x20 */
    unsigned char minLod;       /* 0x21 */
    unsigned char maxLod;       /* 0x22 */
} TexImageDesc;

typedef struct TexTlutDesc {
    unsigned short count;       /* 0x00 */
    int format;                 /* 0x04 */
    void *data;                 /* 0x08 */
} TexTlutDesc;

typedef struct TexPaletteEntry {
    TexImageDesc *image;
    TexTlutDesc *tlut;
} TexPaletteEntry;

typedef struct TexPaletteTable {
    char pad0[8];
    TexPaletteEntry *entries;
} TexPaletteTable;

void GXInitTlutObj(void *tlut, void *data, int format, unsigned short count);
void GXInitTexObj(void *obj, void *data, unsigned short width, unsigned short height, int format,
                  int wrapS, int wrapT, unsigned char mipmap);
void GXInitTexObjCI(void *obj, void *data, unsigned short width, unsigned short height, int format,
                    int wrapS, int wrapT, unsigned char mipmap, unsigned int tlutName);
void GXInitTexObjLOD(void *obj, int minFilter, int magFilter, float minLod, float maxLod,
                     float lodBias, unsigned char biasClamp, unsigned char edgeLod, int maxAniso);

#pragma exceptions on
void TEXBindPaletteEntry_CI(TexPaletteTable *table, void *obj, void *tlutObj, unsigned int tlutName, int idx)
{
    TexPaletteEntry *entry = &table->entries[idx];
    unsigned char mipmap;
    TexImageDesc *img;
    TexTlutDesc *tl;

    if (entry->image->minLod == entry->image->maxLod) {
        mipmap = 0;
    } else {
        mipmap = 1;
    }
    tl = entry->tlut;
    GXInitTlutObj(tlutObj, tl->data, tl->format, tl->count);
    img = entry->image;
    GXInitTexObjCI(obj, img->data, img->width, img->height, img->format, img->wrapS, img->wrapT, mipmap,
                   tlutName);
    img = entry->image;
    GXInitTexObjLOD(obj, img->minFilter, img->magFilter, img->minLod, img->maxLod, img->lodBias, 0,
                    img->edgeLod, 0);
}

void TEXBindPaletteEntry_RGB(TexPaletteTable *table, void *obj, int idx)
{
    TexPaletteEntry *entries = table->entries;
    unsigned char mipmap;
    TexImageDesc *img;

    if (entries[idx].image->minLod == entries[idx].image->maxLod) {
        mipmap = 0;
    } else {
        mipmap = 1;
    }
    img = entries[idx].image;
    GXInitTexObj(obj, img->data, img->width, img->height, img->format, img->wrapS, img->wrapT, mipmap);
    img = entries[idx].image;
    GXInitTexObjLOD(obj, img->minFilter, img->magFilter, img->minLod, img->maxLod, img->lodBias, 0,
                    img->edgeLod, 0);
}
#pragma exceptions reset
