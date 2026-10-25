/*
 * 0x8011DC20..0x8011DF98: ResourceSlot, a loaded texture palette (TPL) with
 * one GXTexObj per texture, a GXTlutObj per CI texture and the TLUT slot it
 * was assigned. Ids from 0x2B00 up name display buffers instead of files.
 */
typedef struct GXTexObj {
    unsigned int dummy[8];
} GXTexObj;

typedef struct GXTlutObj {
    unsigned int dummy[3];
} GXTlutObj;

extern void GXInitTlutObj(GXTlutObj *obj, void *lut, unsigned int fmt, unsigned short n);
extern void GXInitTexObj(GXTexObj *obj, void *image, unsigned short w, unsigned short h, unsigned int fmt,
                         unsigned int wrapS, unsigned int wrapT, unsigned char mipmap);
extern void GXInitTexObjCI(GXTexObj *obj, void *image, unsigned short w, unsigned short h, unsigned int fmt,
                           unsigned int wrapS, unsigned int wrapT, unsigned char mipmap, unsigned int tlut);
extern void GXInitTexObjLOD(GXTexObj *obj, unsigned int minFilt, unsigned int magFilt, float minLOD, float maxLOD,
                            float lodBias, unsigned char clamp, unsigned char edgeLOD, unsigned int aniso);

typedef struct TEXHeader {
    unsigned short height;
    unsigned short width;
    unsigned int format;
    void *data;
    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int minFilter;
    unsigned int magFilter;
    float lodBias;
    unsigned char edgeLODEnable;
    unsigned char minLOD;
    unsigned char maxLOD;
} TEXHeader;

typedef struct CLUTHeader {
    unsigned short numEntries;
    unsigned char pad[2];
    unsigned int format;
    void *data;
} CLUTHeader;

typedef struct TEXDescriptor {
    TEXHeader *tex;
    CLUTHeader *clut;
} TEXDescriptor;

typedef struct TEXPalette {
    void *data;
    unsigned int numDescriptors;
} TEXPalette;

typedef struct ResourceSlot {
    int id;
    int group;
    TEXPalette *palette;
    int count;
    GXTexObj *texObjs;
    GXTlutObj *tlutObjs;
    unsigned char *tlutNames;
} ResourceSlot;

extern void TEXReleasePalette(TEXPalette **palette);
extern void TEXLoadPalette_Retry(TEXPalette **palette, const char *path);
extern TEXDescriptor *TEXGetPaletteEntry(TEXPalette *palette, unsigned int index);
extern int ResourceTable_GetGroupKey(int id);
extern const char *ResourceTable_GetFilePathPtr(int id);
extern TEXPalette *DisplayBuffer_GetByIndex(int index);
extern void *FUN_8003b120(unsigned int size);
extern void MemoryManager_Free(void *p);

extern signed char lbl_806D14FD;

void fn_8011DC20(ResourceSlot *slot) {
    if (slot->palette && slot->id < 0x2B00) {
        TEXReleasePalette(&slot->palette);
    }
    MemoryManager_Free(slot->texObjs);
    MemoryManager_Free(slot->tlutObjs);
    MemoryManager_Free(slot->tlutNames);
    slot->id = 0;
    slot->group = -1;
    slot->palette = 0;
    slot->count = 0;
    slot->texObjs = 0;
    slot->tlutObjs = 0;
    slot->tlutNames = 0;
}

static void TEXGetGXTexObjFromPalette(TEXPalette *pal, GXTexObj *to, unsigned int id) {
    TEXDescriptor *tdp = TEXGetPaletteEntry(pal, id);
    unsigned char mipMap;

    if (tdp->tex->minLOD == tdp->tex->maxLOD) {
        mipMap = 0;
    } else {
        mipMap = 1;
    }
    GXInitTexObj(to, tdp->tex->data, tdp->tex->width, tdp->tex->height, tdp->tex->format, tdp->tex->wrapS,
                 tdp->tex->wrapT, mipMap);
    GXInitTexObjLOD(to, tdp->tex->minFilter, tdp->tex->magFilter, tdp->tex->minLOD, tdp->tex->maxLOD,
                    tdp->tex->lodBias, 0, tdp->tex->edgeLODEnable, 0);
}

static void TEXGetGXTexObjFromPaletteCI(TEXPalette *pal, GXTexObj *to, GXTlutObj *tlo, unsigned int tlut,
                                        unsigned int id) {
    TEXDescriptor *tdp = TEXGetPaletteEntry(pal, id);
    unsigned char mipMap;

    if (tdp->tex->minLOD == tdp->tex->maxLOD) {
        mipMap = 0;
    } else {
        mipMap = 1;
    }
    GXInitTlutObj(tlo, tdp->clut->data, tdp->clut->format, tdp->clut->numEntries);
    GXInitTexObjCI(to, tdp->tex->data, tdp->tex->width, tdp->tex->height, tdp->tex->format, tdp->tex->wrapS,
                   tdp->tex->wrapT, mipMap, tlut);
    GXInitTexObjLOD(to, tdp->tex->minFilter, tdp->tex->magFilter, tdp->tex->minLOD, tdp->tex->maxLOD,
                    tdp->tex->lodBias, 0, tdp->tex->edgeLODEnable, 0);
}

int ResourceSlot_Load(ResourceSlot *slot, int id) {
    int group;
    int i;

    group = ResourceTable_GetGroupKey(id);
    if (id < 0x2B00) {
        const char *path = ResourceTable_GetFilePathPtr(id);
        if (!path) {
            return 0;
        }
        TEXLoadPalette_Retry(&slot->palette, path);
    } else {
        slot->palette = DisplayBuffer_GetByIndex(id - 0x2B00);
    }
    if (!slot->palette) {
        return 0;
    }
    slot->group = group;
    slot->id = id;
    slot->count = slot->palette->numDescriptors;
    slot->texObjs = FUN_8003b120(slot->count << 5);
    slot->tlutObjs = FUN_8003b120(slot->count * 0xC);
    slot->tlutNames = FUN_8003b120(slot->count);
    for (i = 0; i < slot->count; i++) {
        if (TEXGetPaletteEntry(slot->palette, i)->clut) {
            slot->tlutNames[i] = lbl_806D14FD;
            lbl_806D14FD++;
            if (lbl_806D14FD >= 0x10) {
                lbl_806D14FD = 0;
            }
            TEXGetGXTexObjFromPaletteCI(slot->palette, &slot->texObjs[i], &slot->tlutObjs[i], 0, i);
        } else {
            TEXGetGXTexObjFromPalette(slot->palette, &slot->texObjs[i], i);
        }
    }
    return 1;
}

void fn_8011DF70(ResourceSlot *slot) {
    slot->id = -1;
    slot->group = -1;
    slot->palette = 0;
    slot->count = 0;
    slot->texObjs = 0;
    slot->tlutObjs = 0;
    slot->tlutNames = 0;
}
