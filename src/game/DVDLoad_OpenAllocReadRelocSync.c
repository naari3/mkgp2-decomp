/*
 * DVDLoad_OpenAllocReadRelocSync, 0x8007DD00..0x8007DFD4: loads a relocatable
 * archive synchronously. It reads the 0x20-byte header, checks the file size,
 * reads the data block, the relocation/public/extern tables and the symbol
 * strings into separate 32-byte rounded buffers, keeps a copy of the path and
 * applies the relocations. The idle callback is told the current stage.
 */

typedef unsigned long u32;

typedef struct DVDFileInfo {
    unsigned char cb[0x30];
    u32 startAddr; /* 0x30 */
    u32 length;    /* 0x34 */
    unsigned char pad38[0x3C - 0x38];
} DVDFileInfo;

typedef struct ArchiveHeader {
    u32 file_size;  /* 0x00 */
    u32 data_size;  /* 0x04 */
    u32 nb_reloc;   /* 0x08 */
    u32 nb_public;  /* 0x0C */
    u32 nb_extern;  /* 0x10 */
    u32 pad[3];     /* 0x14 */
} ArchiveHeader;

typedef struct Archive {
    ArchiveHeader header; /* 0x00 */
    unsigned char *data;  /* 0x20 */
    u32 *reloc_info;      /* 0x24 */
    void *public_info;    /* 0x28 */
    void *extern_info;    /* 0x2C */
    char *symbols;        /* 0x30 */
    void *next;           /* 0x34 */
    char *name;           /* 0x38 */
    u32 pad3C;            /* 0x3C */
    u32 flags;            /* 0x40 */
} Archive;

extern int DVDOpen(const char *path, DVDFileInfo *info);
extern int DVDClose(DVDFileInfo *info);
extern unsigned char FUN_8007dfe4(const char *path, void *buf, long len, long offset, int stage);
extern void *HSD_MemAlloc(u32 size);
extern void HSD_ArchiveFree(Archive *archive);
extern void *memcpy(void *dst, const void *src, u32 n);
extern void *memset(void *dst, int c, u32 n);
extern u32 strlen(const char *s);
extern void (*g_dvdLoadCallback)(int stage); /* idle callback while reading */

#define ROUND32(x) (((x) + 0x1F) & ~0x1F)

static inline void ArchiveRelocate(Archive *archive)
{
    u32 i;

    for (i = 0; i < archive->header.nb_reloc; i++) {
        *(u32 *)(archive->data + archive->reloc_info[i]) += (u32)archive->data;
    }
}

#pragma exceptions on
#pragma use_lmw_stmw on

Archive *DVDLoad_OpenAllocReadRelocSync(const char *path)
{
    Archive *archive;
    DVDFileInfo info;
    u32 length;
    u32 offset;
    u32 size;
    u32 data_size;

    g_dvdLoadCallback(0);
    g_dvdLoadCallback(1);
    archive = HSD_MemAlloc(sizeof(Archive));
    if (archive == 0) {
        goto fail;
    }
    memset(archive, 0, sizeof(Archive));
    if (!FUN_8007dfe4(path, archive, 0x20, 0, 2)) {
        goto fail;
    }
    if (DVDOpen(path, &info) == 0) {
        return 0;
    }
    length = info.length;
    DVDClose(&info);
    if (archive->header.file_size != length) {
        goto fail;
    }

    data_size = archive->header.data_size;
    archive->data = HSD_MemAlloc(ROUND32(data_size));
    if (archive->data == 0) {
        goto fail;
    }
    archive->flags = 0;
    if (!FUN_8007dfe4(path, archive->data, ROUND32(data_size), 0x20, 3)) {
        goto fail;
    }
    offset = data_size + 0x20;

    if (archive->header.nb_reloc != 0) {
        size = archive->header.nb_reloc * 4;
            archive->reloc_info = HSD_MemAlloc(ROUND32(size));
        if (archive->reloc_info == 0) {
            goto fail;
        }
        if (!FUN_8007dfe4(path, archive->reloc_info, ROUND32(size), offset, 4)) {
            goto fail;
        }
        offset += size;
    }
    if (archive->header.nb_public != 0) {
        size = archive->header.nb_public * 8;
            archive->public_info = HSD_MemAlloc(ROUND32(size));
        if (archive->public_info == 0) {
            goto fail;
        }
        if (!FUN_8007dfe4(path, archive->public_info, ROUND32(size), offset, 5)) {
            goto fail;
        }
        offset += size;
    }
    if (archive->header.nb_extern != 0) {
        size = archive->header.nb_extern * 8;
            archive->extern_info = HSD_MemAlloc(ROUND32(size));
        if (archive->extern_info == 0) {
            goto fail;
        }
        if (!FUN_8007dfe4(path, archive->extern_info, ROUND32(size), offset, 6)) {
            goto fail;
        }
        offset += size;
    }
    if ((size = archive->header.file_size - offset) != 0) {
            archive->symbols = HSD_MemAlloc(ROUND32(size));
        if (archive->symbols == 0) {
            goto fail;
        }
        if (!FUN_8007dfe4(path, archive->symbols, ROUND32(size), offset, 7)) {
            goto fail;
        }
    }

    length = strlen(path);
    archive->name = HSD_MemAlloc(length + 1);
    if (archive->name == 0) {
        goto fail;
    }
    memcpy(archive->name, path, length + 1);

    ArchiveRelocate(archive);
    g_dvdLoadCallback(8);
    return archive;

fail:
    if (archive != 0) {
        HSD_ArchiveFree(archive);
    }
    return 0;
}

#pragma use_lmw_stmw reset
#pragma exceptions reset
