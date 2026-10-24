// DVD palette loader and relocation of serialized TPL offsets.
typedef unsigned int u32;
typedef unsigned char u8;
struct DVDFileInfo { u8 command[0x30]; u32 start; u32 length; void* callback; };
struct TPLImage { u32 dimensions, format; void* data; u8 settings[0x17]; u8 unpacked; };
struct TPLClut { unsigned short entries; u8 unpacked, pad; u32 format; void* data; };
struct TPLDescriptor { TPLImage* image; TPLClut* clut; };
struct TPLPalette { u32 version, count; TPLDescriptor* descriptors; };
extern "C" {
extern int lbl_806CEFA0[2], lbl_806CF010;
extern u32 lbl_806D11F8[2];
extern const u8 lbl_806D2FB0;
extern const char lbl_80313008[], lbl_80313018[];
int DVDOpen(const char*, DVDFileInfo*);
void fn_8029530C(DVDFileInfo*);
void* OSAllocFromHeap(int, u32);
void OSFreeToHeap(int, void*);
u8 FUN_8007dfe4(const char*, void*, u32, u32, int);
u8 DVDLoad_ReadChunkHandle(DVDFileInfo*, void*, u32, u32, int);
void ZlibInflate_BufferToBuffer(void*, void*, u32);
void DCFlushRange(void*, u32);
void OSPanic(const char*, int, const char*, ...);
static inline void RelocatePalette(TPLPalette* palette) {
    unsigned short i;
    if (palette->version != 0x20af30) OSPanic(lbl_80313008, 0xd2, lbl_80313018);
    palette->descriptors = (TPLDescriptor*)((u32)palette->descriptors + (u32)palette);
    for (i = 0; i < palette->count; i++) {
        if (palette->descriptors[i].image) {
            palette->descriptors[i].image = (TPLImage*)((u32)palette + (u32)palette->descriptors[i].image);
            if (!palette->descriptors[i].image->unpacked) {
                palette->descriptors[i].image->data = (void*)((u32)palette + (u32)palette->descriptors[i].image->data);
                palette->descriptors[i].image->unpacked = 1;
            }
        }
        if (palette->descriptors[i].clut) {
            palette->descriptors[i].clut = (TPLClut*)((u32)palette + (u32)palette->descriptors[i].clut);
            if (!palette->descriptors[i].clut->unpacked) {
                palette->descriptors[i].clut->data = (void*)((u32)palette + (u32)palette->descriptors[i].clut->data);
                palette->descriptors[i].clut->unpacked = 1;
            }
        }
    }
}
#pragma use_lmw_stmw on
void TEXLoadPalette(TPLPalette** out, const char* path) {
    DVDFileInfo file;
    if (!DVDOpen(path, &file)) return;
    int heap;
    u32 diskSize = (file.length + 31) & ~31;
    heap = lbl_806CEFA0[0];
    u32* header = (u32*)OSAllocFromHeap(lbl_806CF010, 0x41);
    if (!FUN_8007dfe4(path, header, 0x20, 0, 9)) {
        *out = 0; OSFreeToHeap(lbl_806CF010, header); return;
    }
    u32 x = *header;
    int size = ((x >> 24) & 0xff) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000) | (x << 24);
    OSFreeToHeap(lbl_806CF010, header);
    if (size <= 0) { fn_8029530C(&file); return; }
    if (heap == -1) *out = (TPLPalette*)OSAllocFromHeap(lbl_806CF010, size);
    else *out = (TPLPalette*)OSAllocFromHeap(heap, size);
    if (!*out) { fn_8029530C(&file); return; }
    void* compressed = OSAllocFromHeap(lbl_806CF010, diskSize);
    if (lbl_806D2FB0 == 1) fn_8029530C(&file);
    lbl_806D11F8[0] += size;
    if (lbl_806D2FB0 == 0) {
        if (!DVDLoad_ReadChunkHandle(&file, *out, size, 0, 9)) {
            OSFreeToHeap(lbl_806CF010, *out); *out = 0; fn_8029530C(&file); return;
        }
    } else {
        if (!FUN_8007dfe4(path, compressed, diskSize, 0, 9)) {
            OSFreeToHeap(lbl_806CF010, *out); OSFreeToHeap(lbl_806CF010, compressed); *out = 0; return;
        }
        ZlibInflate_BufferToBuffer(compressed, *out, diskSize);
        DCFlushRange(*out, size);
        OSFreeToHeap(lbl_806CF010, compressed);
    }
    if (lbl_806D2FB0 == 0) fn_8029530C(&file);
    RelocatePalette(*out);
}

#pragma use_lmw_stmw reset
void TEXLoadPalette_Retry(TPLPalette** out, const char* path) {
    while (!*out) { *out = 0; TEXLoadPalette(out, path); }
}
}
