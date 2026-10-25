typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long u32;
typedef signed long s32;
typedef float f32;
typedef double f64;

typedef s16 THPCoeff;
typedef f32 THPQuantTab[64];

typedef struct _THPHuffmanTab {
    /* 0x00 */ u8* bits;
    /* 0x04 */ s8* sizeTab;
    /* 0x08 */ u32* codeTab;
    /* 0x0C */ u16 numVij;
    /* 0x10 */ u8* Vij;
    /* 0x14 */ s32 maxCode[18];
    /* 0x5C */ s32 valPtr[18];
    /* 0xA4 */ u32 numCodes;
} THPHuffmanTab; // size = 0xA8

typedef struct _THPComponent {
    /* 0x00 */ u8 componentID;
    /* 0x01 */ u8 samplingH;
    /* 0x02 */ u8 samplingV;
    /* 0x03 */ u8 quantizationTableSelector;
    /* 0x04 */ u8 DCTableSelector;
    /* 0x05 */ u8 ACTableSelector;
    /* 0x06 */ THPCoeff predDC;
    /* 0x08 */ u32 x08;
    /* 0x0C */ u32 x0C;
    /* 0x10 */ u8* x10;
    /* 0x14 */ u8* tile;
    /* 0x18 */ s32 x14;
    /* 0x1C */ s32 x18;
    /* 0x20 */ s32 x1C;
    /* 0x24 */ s32 x20;
    /* 0x28 */ s32 x24;
    /* 0x2C */ s32 x28;
} THPComponent; // size = 0x30

typedef struct _THPFileInfo {
    /* 0x000 */ THPQuantTab quantTabs[4];
    /* 0x400 */ u8* file;
    /* 0x404 */ u8* scanStart;
    /* 0x408 */ u16 xPixelSize;
    /* 0x40A */ u16 yPixelSize;
    /* 0x40C */ u16 x40C;
    /* 0x40E */ u16 x40E;
    /* 0x410 */ u32 currByte;
    /* 0x414 */ s32 cnt;
    /* 0x418 */ u8 validHuffmanTabs;
    /* 0x419 */ u8 validQuantTabs;
    /* 0x41A */ u8 samplingHMax;
    /* 0x41B */ u8 samplingVMax;
    /* 0x41C */ u8 nComponents;
    /* 0x41D */ u8 x41D;
    /* 0x41E */ u8 RST;
    /* 0x41F */ u8 x41F;
    /* 0x420 */ THPHuffmanTab huffmanTabs[4];
    /* 0x6C0 */ THPComponent components[3];
    /* 0x750 */ THPCoeff* mcuBuffer[16];
    /* 0x790 */ u8 x8BC[16];
    /* 0x7A0 */ u16 MCUsPerRow;
    /* 0x7A2 */ u16 x8CE;
    /* 0x7A4 */ u16 x8D0;
    /* 0x7A6 */ u16 x7A6;
    /* 0x7A8 */ u16 x8D4;
    /* 0x7AA */ u16 x7AA;
    /* 0x7AC */ u16 x7AC;
    /* 0x7AE */ u16 nMCU;
    /* 0x7B0 */ u16 currMCU;
    /* 0x7B4 */ u8* scratch;
    /* 0x7B8 */ u32 oldGQR2;
    /* 0x7BC */ u32 oldGQR5;
    /* 0x7C0 */ u32 oldGQR6;
    /* 0x7C4 */ u32 oldGQR7;
} THPFileInfo;

typedef struct THPDecHandle {
    void* data;
    struct _THPFileInfo* info;
} THPDecHandle;

typedef struct THPDecDesc {
    u32 x0;
    u16 width;
    u16 height;
    s32 format;
} THPDecDesc;

#define NULL ((void*)0)
void* memset(void* dst, int c, unsigned long n);

#define OSRoundUp32B(x) (((u32) (x) + 32 - 1) & ~(32 - 1))
#define THPROUNDUP(a, b) ((((s32) (a)) + ((s32) (b) - 1L)) / ((s32) (b)))

static const u8 __THPJpegNaturalOrder[80] = {
    0,  1,  8,  16, 9,  2,  3,  10, 17, 24, 32, 25, 18, 11, 4,  5,
    12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6,  7,  14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
    63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63
};

static const f64 __THPAANScaleFactor[8] = {
    1.0f, 1.387039845f, 1.306562965f, 1.175875602f,
    1.0f, 0.785694958f, 0.541196100f, 0.275899379f,
};

static f32 __THPIDCTWorkspace[64] __attribute__((aligned(32)));

static u8 __THPReadFrameHeader(THPFileInfo* info);
static u8 __THPReadQuantizationTable(THPFileInfo* info);
static u8 __THPReadHuffmanTableSpecification(THPFileInfo* info);
static u8 __THPReadScaneHeader(THPFileInfo* info);
static u8 __THPHuffGenerateSizeTable(THPFileInfo* info, u8 tab_index, u8* bits);
static u8 __THPHuffGenerateCodeTable(THPFileInfo* info, u8 tab_index);
static u8 __THPHuffGenerateDecoderTables(THPFileInfo* info, u8 tabIndex);
static u8 __THPSetupMCUs(THPFileInfo* info);
u8 fn_80299850(THPFileInfo* info);
u8 fn_80299D58(THPFileInfo* info);
static void __THPDecodeBlock(THPFileInfo* info, u8 c, THPCoeff* block);
static s32 __THPReceive(THPFileInfo* info, u8 n);
static s32 __THPHuffDecode(THPFileInfo* info, u8 tabIndex);
static s32 __THPHuffDecodeTab(THPFileInfo* info, THPHuffmanTab* h);
s32 THPDecGetInfo(u8* data, THPDecDesc* out);
u32 THPDecGetWorkSize(THPDecDesc* desc);
s32 THPVideoDecode(THPDecHandle* handle, u8* statusOut, THPFileInfo* work, void* data, THPDecDesc* desc);
void THPDecDecode(THPDecHandle* handle, void* tileY, void* tileU, void* tileV);
static s32 __THPGetBit(THPFileInfo* info);

static void __THPSetupBuffers(THPFileInfo* info)
{
    u8* p;
    u8 i;

    p = (u8*) OSRoundUp32B(info->scratch);
    info->scratch = p + 16 * 128;
    for (i = 0; i < 16; i++) {
        info->mcuBuffer[i] = (THPCoeff*) p;
        p += 128;
    }
}

static s32 __THPSkipSegment(u8** data)
{
    u32 i;
    u8* ptr = *data;
    u16 high = ptr[0];
    u16 low = ptr[1];

    u16 count = (high << 8) | low;
    for (i = 0; i < count; i++) {
        (*data)++;
    }

    return 0;
}

static inline void __THPGQRSetup(register THPFileInfo* info)
{
    asm {
        mfspr r0, GQR2
        stw r0, 0x7B8(info)
        li r0, 0x0004
        oris r0, r0, 0x0004
        mtspr GQR2, r0
        mfspr r0, GQR5
        stw r0, 0x7BC(info)
        li r0, 0x0007
        oris r0, r0, 0x0007
        mtspr GQR5, r0
        mfspr r0, GQR6
        stw r0, 0x7C0(info)
        li r0, 0x3D04
        oris r0, r0, 0x3D04
        mtspr GQR6, r0
        mfspr r0, GQR7
        stw r0, 0x7C4(info)
        li r0, 0x0104
        oris r0, r0, 0x0104
        mtspr GQR7, r0
    }
}

static inline void __THPGQRRestore(register THPFileInfo* info)
{
    asm {
        lwz r0, 0x7B8(info)
        mtspr GQR2, r0
        lwz r0, 0x7BC(info)
        mtspr GQR5, r0
        lwz r0, 0x7C0(info)
        mtspr GQR6, r0
        lwz r0, 0x7C4(info)
        mtspr GQR7, r0
    }
}

static u8 __THPReadFrameHeader(THPFileInfo* info)
{
    u8 i;
    u8 j;
    u8 k;
    THPComponent* comp;
    u8 utmp8;
    u16 ySize;

    info->file += 2;

    utmp8 = (*(info->file)++);

    if (utmp8 != 8) {
        return 4;
    }

    info->yPixelSize = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    info->xPixelSize = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;

    info->nComponents = (*(info->file)++);
    if (info->nComponents != 3 && info->nComponents != 1) {
        return 6;
    }

    for (i = 0; i < info->nComponents; i++) {
        info->components[i].componentID = (*(info->file)++);
        utmp8 = (*(info->file)++);
        info->components[i].samplingH = (u8) (utmp8 >> 4);
        info->components[i].samplingV = (u8) (utmp8 & 0xF);
        info->components[i].quantizationTableSelector = (*(info->file)++);
    }

    info->samplingHMax = 1;
    info->samplingVMax = 1;
    for (j = 0; j < info->nComponents; j++) {
        comp = &info->components[j];
        info->samplingHMax = info->samplingHMax > comp->samplingH
                                 ? info->samplingHMax
                                 : comp->samplingH;
        info->samplingVMax = info->samplingVMax > comp->samplingV
                                 ? info->samplingVMax
                                 : comp->samplingV;
    }

    ySize = info->yPixelSize;
    info->x8D4 =
        (u16) THPROUNDUP(ySize, THPROUNDUP(ySize, info->samplingVMax * 8));
    for (k = 0; k < info->nComponents; k++) {
        info->components[k].x08 =
            THPROUNDUP(info->xPixelSize * info->components[k].samplingH,
                       info->samplingHMax);
        info->components[k].x0C =
            THPROUNDUP(info->yPixelSize * info->components[k].samplingV,
                       info->samplingVMax);
    }

    return 0;
}

static u8 __THPReadQuantizationTable(THPFileInfo* info)
{
    u16 length, id, i, row, col;
    f32 q_temp[64];

    length = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    length -= 2;

    for (;;) {
        id = (*(info->file)++);

        for (i = 0; i < 64; i++) {
            q_temp[__THPJpegNaturalOrder[i]] = (f32) (*(info->file)++);
        }

        info->validQuantTabs |= 1 << id;

        i = 0;
        for (row = 0; row < 8; row++) {
            for (col = 0; col < 8; col++) {
                info->quantTabs[id][i] = q_temp[i] * __THPAANScaleFactor[row] *
                                         __THPAANScaleFactor[col];
                i++;
            }
        }

        length -= 65;
        if (!length) {
            break;
        }
    }

    return 0;
}

static u8 __THPReadHuffmanTableSpecification(THPFileInfo* info)
{
    u8 t_class, id, i;
    u8 tab_index;
    u16 length, num_Vij;
    u8* huffmanBits;
    u8 result;

    length = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    length -= 2;

    for (;;) {
        i = (*(info->file)++);
        huffmanBits = info->file;
        t_class = (u8) (i >> 4);
        id = (u8) (i & 15);
        if (t_class > 1 || id >= 2) {
            return 7;
        }
        tab_index = (u8) ((id << 1) + t_class);
        num_Vij = 0;

        for (i = 0; i < 16; i++) {
            num_Vij += (*(info->file)++);
        }

        info->huffmanTabs[tab_index].bits = huffmanBits;
        info->huffmanTabs[tab_index].Vij = info->file;
        info->huffmanTabs[tab_index].numVij = num_Vij;
        for (i = 0; i < num_Vij; i++) {
            info->file++;
        }
        result = __THPHuffGenerateSizeTable(info, tab_index, huffmanBits);
        if (result) {
            return result;
        }
        result = __THPHuffGenerateCodeTable(info, tab_index);
        if (result) {
            return result;
        }
        __THPHuffGenerateDecoderTables(info, tab_index);

        length -= 17 + num_Vij;
        info->validHuffmanTabs |= 1 << tab_index;

        if (length == 0) {
            break;
        }
    }

    return 0;
}

static u8 __THPReadScaneHeader(THPFileInfo* info)
{
    u8 numComponents;
    u8 i;
    info->file += 2;
    numComponents = *info->file++;

    if (numComponents != info->nComponents) {
        return 6;
    }

    for (i = 0; i < numComponents; i++) {
        u8 selectors;
        u16 blocksPerRow;
        u16 rows;

        info->file++;
        selectors = *info->file++;

        info->components[i].DCTableSelector = (u8) (selectors >> 4);
        info->components[i].ACTableSelector = (u8) (selectors & 0xF);

        if (!(info->validHuffmanTabs & (1 << (selectors >> 4)))) {
            return 9;
        }
        if (!(info->validHuffmanTabs & (1 << ((selectors & 0xF) + 1)))) {
            return 9;
        }

        blocksPerRow = info->components[i].x08;
        rows = 16 >> (info->samplingVMax - info->components[i].samplingV);
        info->components[i].x10 = info->scratch;
        info->scratch += blocksPerRow * rows;
    }

    info->file += 3;
    return __THPSetupMCUs(info);
}

static u8 __THPHuffGenerateSizeTable(THPFileInfo* info, u8 tab_index, u8* bits)
{
    s32 p;
    s32 l;
    s32 i;

    p = 0;
    for (l = 1; l <= 16; l++) {
        p += bits[l - 1];
    }

    info->huffmanTabs[tab_index].sizeTab = (s8*) info->scratch;
    info->scratch += p + 1;

    p = 0;
    for (l = 1; l <= 16; l++) {
        i = bits[l - 1];
        while (i--) {
            info->huffmanTabs[tab_index].sizeTab[p++] = (s8) l;
        }
    }

    info->huffmanTabs[tab_index].sizeTab[p] = 0;
    info->huffmanTabs[tab_index].numCodes = p;
    return 0;
}

static u8 __THPHuffGenerateCodeTable(THPFileInfo* info, u8 tab_index)
{
    s32 si;
    u32 code;
    s32 p;

    p = 0;
    si = info->huffmanTabs[tab_index].sizeTab[0];
    while (info->huffmanTabs[tab_index].sizeTab[p]) {
        while (info->huffmanTabs[tab_index].sizeTab[p] == si) {
            p++;
        }
        si++;
    }

    info->huffmanTabs[tab_index].codeTab = (u32*) info->scratch;
    info->scratch += p * sizeof(u32);

    p = 0;
    code = 0;
    si = info->huffmanTabs[tab_index].sizeTab[0];
    while (info->huffmanTabs[tab_index].sizeTab[p]) {
        while (info->huffmanTabs[tab_index].sizeTab[p] == si) {
            info->huffmanTabs[tab_index].codeTab[p++] = code;
            code++;
        }

        code <<= 1;
        si++;
    }

    return 0;
}

static u8 __THPHuffGenerateDecoderTables(THPFileInfo* info, u8 tabIndex)
{
    s32 p, l;
    THPHuffmanTab* h;

    p = 0;
    h = &info->huffmanTabs[tabIndex];
    for (l = 1; l <= 16; l++) {
        if (h->bits[l - 1]) {
            h->valPtr[l] = p - h->codeTab[p];
            p += h->bits[l - 1];
            h->maxCode[l] = h->codeTab[p - 1];
        } else {
            h->maxCode[l] = -1;
            h->valPtr[l] = -1;
        }
    }

    h->maxCode[17] = 0xfffffL;
    return 0;
}

static u8 __THPSetupMCUs(THPFileInfo* info)
{
    u32 i;
    s32 j;

    info->MCUsPerRow =
        (u16) THPROUNDUP(info->xPixelSize, info->samplingHMax * 8);
    info->x8D0 = (u16) THPROUNDUP(info->yPixelSize, info->samplingVMax * 8);
    info->x8CE = 0;

    for (i = 0; i < info->nComponents; i++) {
        THPComponent* c = &info->components[i];

        c->x28 = THPROUNDUP(info->xPixelSize * c->samplingH,
                            info->samplingHMax * 8);
        c->x24 = THPROUNDUP(info->yPixelSize * c->samplingV,
                            info->samplingVMax * 8);
        c->x14 = c->samplingH;
        c->x18 = c->samplingV;
        c->x1C = c->x14 * c->x18;
        c->x20 = c->x14 * 8;

        j = c->x1C;
        if (info->x8CE + c->x1C > 0x10) {
            return 11;
        }

        while (j-- > 0) {
            info->x8BC[info->x8CE++] = i;
        }

        c->predDC = 0;
    }

    return 0;
}

u8 fn_80299850(THPFileInfo* info)
{
    register f32 bias, cc2c6a, cc2c6s, cc2, cc4;
    register f32* ws;
    register f32* q;
    u8 c;
    register u32 stride;
    u8 b;
    u8 h;
    u8 v;
    s32 x;
    register u8* base;
    register u32 off;
    s32 y;
    u8 j;
    register u8* out;
    THPComponent* comp;
    u8 i;
    register THPCoeff* in;
    s32 k;

    cc4 = 1.4142135f;
    cc2 = 1.847759f;
    cc2c6s = 1.0823922f;
    cc2c6a = -2.613126f;
    bias = 1024.0f;
    for (i = 0; i < info->MCUsPerRow; i++) {
        for (j = 0; j < info->x8CE; j++) {
            __THPDecodeBlock(info, info->x8BC[j], info->mcuBuffer[j]);
        }
        b = 0;
        for (c = 0; c < info->nComponents; c++) {
            comp = &info->components[c];
            y = info->x7AA >> (info->samplingVMax - comp->samplingV);
            for (v = 0; v < comp->x18; v++, y += 8) {
                x = i * comp->x20;
                for (h = 0; h < comp->x14; h++) {
                    in = info->mcuBuffer[b + h];
                    q = info->quantTabs[info->components[c].quantizationTableSelector];
                    ws = __THPIDCTWorkspace - 2;
                    for (k = 0; k < 8; k++) {
                        if (((s32*)in)[3] == 0 && ((s32*)in)[2] == 0) {
                            if (((s32*)in)[1] == 0) {
                                if ((s32)((u16*)in)[1] == 0) {
                                    asm {
                                        psq_l f9, 0(in), 1, 5
                                        lfs f8, 0(q)
                                        addi in, in, 0x10
                                        ps_muls0 f9, f8, f9
                                        addi q, q, 0x20
                                        psq_stu f9, 8(ws), 0, 0
                                        psq_stu f9, 8(ws), 0, 0
                                        psq_stu f9, 8(ws), 0, 0
                                        psq_stu f9, 8(ws), 0, 0
                                    }
                                } else {
                                    asm {
                                        psq_l f9, 0(in), 0, 5
                                        psq_l f1, 0(q), 0, 0
                                        ps_sub f8, cc2, cc2c6s
                                        ps_mul f9, f9, f1
                                        addi in, in, 0x10
                                        ps_msub f7, f9, cc2, f9
                                        ps_merge00 f0, f9, f9
                                        ps_msub f6, f9, cc4, f7
                                        ps_merge11 f4, f9, f7
                                        ps_nmsub f5, f9, f8, f6
                                        ps_add f2, f0, f4
                                        ps_sub f4, f0, f4
                                        ps_merge11 f3, f6, f5
                                        psq_stu f2, 8(ws), 0, 0
                                        ps_add f1, f0, f3
                                        ps_sub f3, f0, f3
                                        psq_stu f1, 8(ws), 0, 0
                                        ps_merge10 f3, f3, f3
                                        ps_merge10 f4, f4, f4
                                        psq_stu f3, 8(ws), 0, 0
                                        addi q, q, 0x20
                                        psq_stu f4, 8(ws), 0, 0
                                    }
                                }
                            } else {
                                asm {
                                    psq_l f9, 0(in), 0, 5
                                    psq_l f1, 0(q), 0, 0
                                    ps_mul f9, f9, f1
                                    psq_l f8, 4(in), 0, 5
                                    psq_l f0, 8(q), 0, 0
                                    ps_mul f8, f8, f0
                                    addi in, in, 0x10
                                    ps_sub f6, f9, f8
                                    ps_add f7, f9, f8
                                    ps_madd f5, f8, cc4, f6
                                    ps_nmsub f4, f8, cc4, f7
                                    ps_mul f1, f6, cc2
                                    ps_merge00 f5, f7, f5
                                    ps_nmsub f3, f8, cc2c6a, f1
                                    ps_merge00 f4, f4, f6
                                    ps_sub f3, f3, f7
                                    ps_nmsub f2, f9, cc2c6s, f1
                                    ps_merge11 f7, f7, f3
                                    ps_msub f1, f6, cc4, f3
                                    ps_add f0, f5, f7
                                    ps_sub f2, f2, f1
                                    psq_stu f0, 8(ws), 0, 0
                                    ps_merge11 f6, f1, f2
                                    ps_sub f5, f5, f7
                                    ps_add f9, f4, f6
                                    ps_sub f8, f4, f6
                                    psq_stu f9, 8(ws), 0, 0
                                    ps_merge10 f8, f8, f8
                                    ps_merge10 f5, f5, f5
                                    psq_stu f8, 8(ws), 0, 0
                                    addi q, q, 0x20
                                    psq_stu f5, 8(ws), 0, 0
                                }
                            }
                        } else {
                            asm {
                                psq_l f1, 0(in), 0, 5
                                psq_l f5, 0(q), 0, 0
                                ps_mul f1, f1, f5
                                psq_l f0, 4(in), 0, 5
                                psq_l f4, 8(q), 0, 0
                                ps_mul f0, f0, f4
                                psq_l f7, 8(in), 0, 5
                                psq_l f3, 0x10(q), 0, 0
                                ps_merge01 f9, f1, f0
                                psq_l f6, 0xc(in), 0, 5
                                ps_merge01 f8, f0, f1
                                psq_l f2, 0x18(q), 0, 0
                                ps_madd f5, f7, f3, f9
                                ps_nmsub f4, f7, f3, f9
                                ps_madd f3, f6, f2, f8
                                ps_nmsub f2, f6, f2, f8
                                ps_add f9, f5, f3
                                ps_sub f6, f5, f3
                                ps_msub f7, f2, cc4, f3
                                ps_sub f1, f2, f4
                                ps_add f8, f4, f7
                                ps_sub f7, f4, f7
                                ps_mul f1, f1, cc2
                                ps_merge00 f8, f9, f8
                                ps_nmsub f3, f4, cc2c6a, f1
                                ps_msub f5, f2, cc2c6s, f1
                                ps_merge00 f7, f7, f6
                                ps_sub f3, f3, f9
                                addi in, in, 0x10
                                ps_madd f4, f6, cc4, f3
                                ps_merge11 f2, f9, f3
                                ps_sub f5, f5, f4
                                ps_add f6, f8, f2
                                ps_merge11 f5, f4, f5
                                ps_sub f9, f8, f2
                                psq_stu f6, 8(ws), 0, 0
                                ps_add f4, f7, f5
                                ps_sub f3, f7, f5
                                ps_merge10 f4, f4, f4
                                psq_stu f3, 8(ws), 0, 0
                                ps_merge10 f9, f9, f9
                                psq_stu f4, 8(ws), 0, 0
                                addi q, q, 0x20
                                psq_stu f9, 8(ws), 0, 0
                            }
                        }
                    }
                    stride = info->components[c].x08;
                    base = info->components[c].tile;
                    ws = __THPIDCTWorkspace;
                    off = x + y * stride;
                    for (k = 0; k < 4; k++) {
                        asm {
                            psq_l f9, 0(ws), 0, 0
                            psq_l f8, 0x80(ws), 0, 0
                            add out, base, off
                            ps_add f3, f9, f8
                            psq_l f7, 0x40(ws), 0, 0
                            ps_sub f1, f9, f8
                            ps_add f3, f3, bias
                            psq_l f6, 0xc0(ws), 0, 0
                            ps_add f2, f7, f6
                            ps_sub f0, f7, f6
                            psq_l f5, 0x20(ws), 0, 0
                            ps_add f9, f3, f2
                            ps_add f1, f1, bias
                            psq_l f4, 0x60(ws), 0, 0
                            ps_msub f0, f0, cc4, f2
                            ps_sub f6, f3, f2
                            psq_l f3, 0xa0(ws), 0, 0
                            ps_add f8, f1, f0
                            psq_l f2, 0xe0(ws), 0, 0
                            ps_sub f7, f1, f0
                            ps_add f1, f3, f4
                            ps_sub f3, f3, f4
                            ps_add f0, f5, f2
                            ps_sub f5, f5, f2
                            ps_add f2, f0, f1
                            ps_sub f4, f0, f1
                            ps_add f1, f3, f5
                            ps_add f0, f9, f2
                            ps_mul f1, f1, cc2
                            ps_sub f9, f9, f2
                            ps_madd f3, f3, cc2c6a, f1
                            psq_st f0, 0(out), 0, 6
                            ps_sub f3, f3, f2
                            ps_msub f5, f5, cc2c6s, f1
                            ps_add f0, f8, f3
                            ps_msub f4, f4, cc4, f3
                            ps_sub f8, f8, f3
                            psq_stux f0, out, stride, 0, 6
                            ps_add f1, f7, f4
                            ps_add f5, f5, f4
                            psq_stux f1, out, stride, 0, 6
                            ps_sub f0, f6, f5
                            ps_add f6, f6, f5
                            psq_stux f0, out, stride, 0, 6
                            ps_sub f1, f7, f4
                            psq_stux f6, out, stride, 0, 6
                            addi ws, ws, 8
                            psq_stux f1, out, stride, 0, 6
                            addi off, off, 2
                            psq_stux f8, out, stride, 0, 6
                            psq_stux f9, out, stride, 0, 6
                        }
                    }
                    x += 8;
                }
                b += (u8)comp->x14;
            }
        }
        if (info->RST) {
            info->currMCU--;
            if (info->currMCU == 0) {
                info->currMCU = info->nMCU;
                info->cnt = 33;
                for (c = 0; c < info->nComponents; c++) {
                    info->components[c].predDC = 0;
                }
            }
        }
    }
    info->x7A6++;
    info->x7AA += info->x8D4;
    return info->x7A6 < info->x8D0 ? 0 : 1;
}

u8 fn_80299D58(THPFileInfo* info)
{
    register f32 bias;
    register f32 cc4;
    register f32 cc2c6a;
    register f32 cc2c6s;
    register f32 cc2;
    register u8* out1;
    u8 c;
    register u8* out0;
    u8 i;
    register u32 itmp3;
    register u32 off1;
    register f32* ws;
    register u32 itmp2;
    register u32 off0;
    u8 h;
    u8 v;
    register u32 itmp1;
    register s32 y;
    register u32 itmp0;
    register u32 wid;
    u8 b;
    register f32* q;
    register THPCoeff* in;
    register u8* base;
    THPComponent* comp;
    u8 j;
    register s32 x;

    cc4 = 1.4142135f;
    cc2 = 1.847759f;
    cc2c6s = 1.0823922f;
    cc2c6a = -2.613126f;
    bias = 1024.0f;
    for (i = 0; i < info->MCUsPerRow; i++) {
        for (j = 0; j < info->x8CE; j++) {
            __THPDecodeBlock(info, info->x8BC[j], info->mcuBuffer[j]);
        }
        b = 0;
        for (c = 0; c < info->nComponents; c++) {
            comp = &info->components[c];
            y = info->x7AA >> (info->samplingVMax - comp->samplingV);
            for (v = 0; v < comp->x18; v++, y += 8) {
                x = i * comp->x20 * 4;
                for (h = 0; h < comp->x14; h++) {
                    {
                        in = info->mcuBuffer[b + h];
                        q = info->quantTabs[info->components[c].quantizationTableSelector];
                        ws = __THPIDCTWorkspace - 2;
                        asm {
        li itmp2, 0x8
        mtctr itmp2
    _L80299E64:
        psq_l f7, 0x0(in), 0, 5
        psq_l f6, 0x0(q), 0, 0
        ps_mul f7, f7, f6
        lwz itmp0, 0xc(in)
        lwz itmp3, 0x8(in)
        or itmp0, itmp0, itmp3
        lwz itmp1, 0x4(in)
        lhz itmp2, 0x2(in)
    _L80299E84:
        cmpwi itmp0, 0x0
        bne _L80299FD0
        cmpwi itmp1, 0x0
        bne _L80299F34
        cmpwi itmp2, 0x0
        bne _L80299EC0
        ps_merge00 f4, f7, f7
        addi q, q, 0x20
        psq_stu f4, 0x8(ws), 0, 0
        psq_stu f4, 0x8(ws), 0, 0
        addi in, in, 0x10
        psq_stu f4, 0x8(ws), 0, 0
        psq_stu f4, 0x8(ws), 0, 0
        bdnz _L80299E64
        b _L8029A098
    _L80299EC0:
        ps_msub f13, f7, cc2, f7
        addi in, in, 0x10
        ps_merge00 f2, f7, f7
        addi q, q, 0x20
        ps_sub f1, cc2, cc2c6s
        lwz itmp1, 0x4(in)
        ps_msub f12, f7, cc4, f13
        lhz itmp2, 0x2(in)
        ps_merge11 f10, f7, f13
        psq_l f6, 0x0(q), 0, 0
        ps_nmsub f11, f7, f1, f12
        ps_add f8, f2, f10
        psq_l f7, 0x0(in), 0, 5
        ps_merge11 f9, f12, f11
        ps_sub f10, f2, f10
        lwz itmp0, 0xc(in)
        ps_add f3, f2, f9
        lwz itmp3, 0x8(in)
        ps_sub f9, f2, f9
        psq_stu f8, 0x8(ws), 0, 0
        ps_merge10 f9, f9, f9
        psq_stu f3, 0x8(ws), 0, 0
        ps_merge10 f10, f10, f10
        or itmp0, itmp0, itmp3
        psq_stu f9, 0x8(ws), 0, 0
        ps_mul f7, f7, f6
        psq_stu f10, 0x8(ws), 0, 0
        bdnz _L80299E84
        b _L8029A098
    _L80299F34:
        psq_l f1, 0x4(in), 0, 5
        psq_l f2, 0x8(q), 0, 0
        addi in, in, 0x10
        ps_mul f1, f1, f2
        addi q, q, 0x20
        ps_sub f12, f7, f1
        ps_add f13, f7, f1
        lwz itmp0, 0xc(in)
        ps_madd f11, f1, cc4, f12
        ps_nmsub f10, f1, cc4, f13
        ps_mul f3, f12, cc2
        ps_merge00 f11, f13, f11
        lwz itmp3, 0x8(in)
        ps_nmsub f9, f1, cc2c6a, f3
        ps_merge00 f10, f10, f12
        lwz itmp1, 0x4(in)
        ps_sub f9, f9, f13
        ps_nmsub f8, f7, cc2c6s, f3
        lhz itmp2, 0x2(in)
        ps_merge11 f13, f13, f9
        ps_msub f3, f12, cc4, f9
        psq_l f7, 0x0(in), 0, 5
        ps_add f2, f11, f13
        ps_sub f8, f8, f3
        psq_l f6, 0x0(q), 0, 0
        ps_merge11 f12, f3, f8
        ps_sub f11, f11, f13
        psq_stu f2, 0x8(ws), 0, 0
        ps_add f4, f10, f12
        ps_sub f1, f10, f12
        or itmp0, itmp0, itmp3
        psq_stu f4, 0x8(ws), 0, 0
        ps_merge10 f1, f1, f1
        ps_merge10 f11, f11, f11
        psq_stu f1, 0x8(ws), 0, 0
        ps_mul f7, f7, f6
        psq_stu f11, 0x8(ws), 0, 0
        bdnz _L80299E84
        b _L8029A098
    _L80299FD0:
        psq_l f2, 0x4(in), 0, 5
        psq_l f10, 0x8(q), 0, 0
        ps_mul f2, f2, f10
        psq_l f13, 0x8(in), 0, 5
        psq_l f9, 0x10(q), 0, 0
        ps_merge01 f4, f7, f2
        psq_l f12, 0xc(in), 0, 5
        ps_merge01 f1, f2, f7
        psq_l f8, 0x18(q), 0, 0
        addi in, in, 0x10
        ps_madd f11, f13, f9, f4
        ps_nmsub f10, f13, f9, f4
        ps_madd f9, f12, f8, f1
        ps_nmsub f8, f12, f8, f1
        addi q, q, 0x20
        ps_add f4, f11, f9
        ps_sub f12, f11, f9
        ps_msub f13, f8, cc4, f9
        lwz itmp0, 0xc(in)
        ps_sub f3, f8, f10
        ps_add f1, f10, f13
        ps_sub f13, f10, f13
        ps_mul f3, f3, cc2
        lwz itmp3, 0x8(in)
        ps_merge00 f1, f4, f1
        ps_nmsub f9, f10, cc2c6a, f3
        ps_msub f11, f8, cc2c6s, f3
        lwz itmp1, 0x4(in)
        ps_sub f9, f9, f4
        ps_merge00 f13, f13, f12
        lhz itmp2, 0x2(in)
        ps_madd f10, f12, cc4, f9
        ps_merge11 f8, f4, f9
        psq_l f7, 0x0(in), 0, 5
        ps_sub f11, f11, f10
        ps_add f12, f1, f8
        psq_l f6, 0x0(q), 0, 0
        ps_merge11 f11, f10, f11
        ps_sub f4, f1, f8
        ps_mul f7, f7, f6
        ps_add f10, f13, f11
        ps_sub f9, f13, f11
        psq_stu f12, 0x8(ws), 0, 0
        ps_merge10 f10, f10, f10
        psq_stu f9, 0x8(ws), 0, 0
        ps_merge10 f4, f4, f4
        psq_stu f10, 0x8(ws), 0, 0
        or itmp0, itmp0, itmp3
        psq_stu f4, 0x8(ws), 0, 0
        bdnz _L80299E84
        
    _L8029A098:
                        }
                    }
                    {
                        wid = info->components[c].x08;
                        ws = __THPIDCTWorkspace;
                        base = info->components[c].tile;
                        asm {
        psq_l f7, 0x0(ws), 0, 0
        mullw off0, wid, y
        psq_l f6, 0x80(ws), 0, 0
        psq_l f5, 0x40(ws), 0, 0
        slwi off1, wid, 2
        ps_add f9, f7, f6
        add off0, off0, x
        psq_l f4, 0xc0(ws), 0, 0
        ps_sub f3, f7, f6
        add off1, off0, off1
        ps_add f9, f9, bias
        li itmp0, 0x3
        ps_add f8, f5, f4
        
        add out0, base, off0
        ps_sub f2, f5, f4
        add out1, base, off1
        ps_add f4, f9, f8
        mtctr itmp0
        ps_add f3, f3, bias
    _L8029A0F0:
        psq_l f11, 0x20(ws), 0, 0
        ps_msub f2, f2, cc4, f8
        psq_l f10, 0x60(ws), 0, 0
        ps_sub f12, f9, f8
        ps_add f1, f3, f2
        psq_l f9, 0xa0(ws), 0, 0
        ps_sub f13, f3, f2
        psq_l f8, 0xe0(ws), 0, 0
        ps_add f3, f9, f10
        ps_sub f9, f9, f10
        ps_add f2, f11, f8
        ps_sub f11, f11, f8
        addi ws, ws, 0x8
        ps_add f8, f2, f3
        ps_sub f10, f2, f3
        psq_l f7, 0x0(ws), 0, 0
        ps_add f3, f9, f11
        psq_l f6, 0x80(ws), 0, 0
        ps_add f2, f4, f8
        ps_mul f3, f3, cc2
        psq_l f5, 0x40(ws), 0, 0
        ps_sub f0, f4, f8
        ps_madd f9, f9, cc2c6a, f3
        psq_l f4, 0xc0(ws), 0, 0
        ps_sub f9, f9, f8
        addi off0, off0, 0x2
        psq_st f2, 0x0(out0), 0, 6
        ps_msub f11, f11, cc2c6s, f3
        ps_add f2, f1, f9
        ps_msub f10, f10, cc4, f9
        ps_sub f1, f1, f9
        psq_stu f2, 0x8(out0), 0, 6
        ps_add f3, f13, f10
        ps_add f11, f11, f10
        psq_stu f3, 0x8(out0), 0, 6
        addi off1, off1, 0x2
        ps_sub f2, f12, f11
        ps_add f3, f12, f11
        psq_stu f2, 0x8(out0), 0, 6
        ps_sub f2, f13, f10
        ps_add f9, f7, f6
        psq_st f3, 0x0(out1), 0, 6
        ps_sub f3, f7, f6
        ps_add f9, f9, bias
        psq_stu f2, 0x8(out1), 0, 6
        ps_add f8, f5, f4
        ps_sub f2, f5, f4
        psq_stu f1, 0x8(out1), 0, 6
        add out0, base, off0
        ps_add f4, f9, f8
        psq_stu f0, 0x8(out1), 0, 6
        ps_add f3, f3, bias
        add out1, base, off1
        bdnz _L8029A0F0
        psq_l f11, 0x20(ws), 0, 0
        ps_msub f2, f2, cc4, f8
        psq_l f10, 0x60(ws), 0, 0
        ps_sub f12, f9, f8
        ps_add f1, f3, f2
        psq_l f9, 0xa0(ws), 0, 0
        ps_sub f13, f3, f2
        psq_l f8, 0xe0(ws), 0, 0
        ps_add f3, f9, f10
        ps_sub f9, f9, f10
        ps_add f2, f11, f8
        ps_sub f11, f11, f8
        ps_add f8, f2, f3
        ps_sub f10, f2, f3
        ps_add f3, f9, f11
        ps_add f2, f4, f8
        ps_mul f3, f3, cc2
        ps_sub f0, f4, f8
        ps_madd f9, f9, cc2c6a, f3
        psq_st f2, 0x0(out0), 0, 6
        ps_sub f9, f9, f8
        ps_msub f11, f11, cc2c6s, f3
        psq_st f0, 0x18(out1), 0, 6
        ps_add f2, f1, f9
        ps_msub f10, f10, cc4, f9
        ps_sub f1, f1, f9
        psq_st f2, 0x8(out0), 0, 6
        ps_add f3, f13, f10
        ps_add f11, f11, f10
        psq_st f3, 0x10(out0), 0, 6
        ps_sub f2, f12, f11
        psq_st f1, 0x10(out1), 0, 6
        ps_add f3, f12, f11
        psq_st f2, 0x18(out0), 0, 6
        ps_sub f2, f13, f10
        psq_st f3, 0x0(out1), 0, 6
        psq_st f2, 0x8(out1), 0, 6
        
                        }
                    }
                    x += 32;
                }
                b += (u8)comp->x14;
            }
        }
        if (info->RST) {
            info->currMCU--;
            if (info->currMCU == 0) {
                info->currMCU = info->nMCU;
                info->cnt = 33;
                for (c = 0; c < info->nComponents; c++) {
                    info->components[c].predDC = 0;
                }
            }
        }
    }
    info->x7A6++;
    info->x7AA += info->x8D4;
    return info->x7A6 < info->x8D0 ? 0 : 1;
}

static void __THPDecodeBlock(THPFileInfo* info, u8 c, THPCoeff* block)
{
    THPHuffmanTab* ac;
    s32 s;
    s32 k;
    s32 r;
    s32 v;
    s16 diff;

    __dcbz(block, 0);
    __dcbz(block, 32);
    s = __THPHuffDecode(info, info->components[c].DCTableSelector << 1);
    __dcbz(block, 64);
    diff = 0;
    __dcbz(block, 96);
    ac = &info->huffmanTabs[(u8) ((info->components[c].ACTableSelector << 1) + 1)];
    if (s != 0) {
        diff = __THPReceive(info, s);
        if (__cntlzw(diff) > 32 - s) {
            diff += (-1 << s) + 1;
        }
    }
    block[0] = info->components[c].predDC += diff;

    for (k = 1; k < 64; k++) {
        r = __THPHuffDecodeTab(info, ac);
        s = r & 15;
        r >>= 4;
        if (s != 0) {
            k += r;
            v = __THPReceive(info, s);
            if (__cntlzw(v) > 32 - s) {
                v += (-1 << s) + 1;
            }
            block[__THPJpegNaturalOrder[k]] = v;
        } else {
            if (r != 15) {
                break;
            }
            k += 15;
        }
    }
}

static s32 __THPReceive(THPFileInfo* info, u8 n)
{
    s32 v;
    s32 i;

    v = __THPGetBit(info);
    if (n == 1) {
        return v;
    }
    if (n == 2) {
        return (v << 1) + __THPGetBit(info);
    }
    if (n == 3) {
        v = (v << 1) + __THPGetBit(info);
        return (v << 1) + __THPGetBit(info);
    }
    v = (v << 1) + __THPGetBit(info);
    v = (v << 1) + __THPGetBit(info);
    v = (v << 1) + __THPGetBit(info);
    if (n == 4) {
        return v;
    }
    for (i = 4; i < n; i++) {
        v = (v << 1) + __THPGetBit(info);
    }
    return v;
}

static s32 __THPHuffDecode(THPFileInfo* info, u8 tabIndex)
{
    THPHuffmanTab* h;
    s32 code;
    s32 l;

    h = &info->huffmanTabs[tabIndex];
    l = 1;
    code = __THPGetBit(info);
    while (code > h->maxCode[l]) {
        code <<= 1;
        code |= __THPGetBit(info);
        l++;
    }
    return (h->Vij + h->valPtr[l])[code];
}

static s32 __THPHuffDecodeTab(THPFileInfo* info, THPHuffmanTab* h)
{
    s32 code;
    s32 l;

    l = 1;
    code = __THPGetBit(info);
    while (code > h->maxCode[l]) {
        code <<= 1;
        code |= __THPGetBit(info);
        l++;
    }
    return (h->Vij + h->valPtr[l])[code];
}

void fn_8029A6F4(register u8* dst, register u8* y, register u8* u, register u8* v, u32 n)
{
    register f32 c0 = 16.5f;
    register f32 c1 = 0.8595f;
    register f32 c2 = 0.8757f;
    register f32 c3 = 0.878f;
    u32 i;
    for (i = 0; i < n; i += 4) {
        asm {
            psq_lu f4, 2(y), 0, 2
            psq_lu f6, 2(u), 0, 2
            ps_madd f4, f4, c1, c0
            ps_madd f6, f6, c2, c0
            psq_lu f5, 2(y), 0, 2
            psq_lu f7, 2(v), 0, 2
            ps_madd f5, f5, c1, c0
            ps_madd f7, f7, c3, c0
            ps_merge00 f8, f4, f6
            ps_merge10 f4, f4, f7
            psq_stu f8, 2(dst), 0, 2
            psq_stu f4, 2(dst), 0, 2
            ps_merge01 f4, f5, f6
            ps_merge11 f5, f5, f7
            psq_stu f4, 2(dst), 0, 2
            psq_stu f5, 2(dst), 0, 2
        }
    }
}

void fn_8029A878(register u8* dst, register u8* y, register u8* u, register u8* v, u32 n)
{
    register f32 c0 = 16.5f;
    register f32 c1 = 0.8595f;
    register f32 c2 = 0.8757f;
    register f32 c3 = 0.878f;
    u32 i;
    asm {
        ps_merge00 f4, c1, c2
        ps_merge00 f5, c1, c3
    }
    for (i = 0; i < n; i += 2) {
        asm {
            psq_lu c1, 2(y), 0, 2
            psq_lu c3, 2(v), 0, 7
            psq_lu c2, 2(u), 0, 7
            ps_sum0 c3, c3, c1, c3
            ps_sum1 c1, c2, c1, c2
            ps_merge10 c3, c3, c3
            ps_madd c1, c1, f4, c0
            ps_madd c3, c3, f5, c0
            psq_stu c1, 2(dst), 0, 2
            psq_stu c3, 2(dst), 0, 2
        }
    }
}

void fn_8029AA2C(register u8* dst, register u8* y, register u8* u, register u8* v, register u8* a)
{
    register f32 c0 = 128.0f;
    register f32 c1 = 1.4026f;
    register f32 c2 = -0.71414f;
    register f32 c3 = -0.34414f;
    register f32 c4 = 1.772f;
    asm {
        psq_l f5, 0(u), 0, 2
        psq_l f6, 0(v), 0, 2
        ps_sub f5, f5, c0
        ps_sub f6, f6, c0
        psq_l c0, 0(y), 0, 2
        psq_l f9, 0(a), 1, 2
        ps_madds0 f8, c4, f5, c0
        ps_madds0 f7, c2, f6, c0
        ps_madds0 c0, c1, f6, c0
        ps_madds0 f7, c3, f5, f7
        ps_merge00 f10, f9, c0
        ps_merge00 f11, f7, f8
        psq_st f10, 0(dst), 0, 2
        psq_st f11, 0x20(dst), 0, 2
        ps_merge01 f10, f9, c0
        ps_merge11 f11, f7, f8
        psq_st f10, 2(dst), 0, 2
        psq_st f11, 0x22(dst), 0, 2
        psq_l c0, 2(y), 0, 2
        ps_madds1 f8, c4, f5, c0
        ps_madds1 f7, c2, f6, c0
        ps_madds1 c0, c1, f6, c0
        ps_madds1 f7, c3, f5, f7
        ps_merge00 f10, f9, c0
        ps_merge00 f11, f7, f8
        psq_st f10, 4(dst), 0, 2
        psq_st f11, 0x24(dst), 0, 2
        ps_merge01 f10, f9, c0
        ps_merge11 f11, f7, f8
        psq_st f10, 6(dst), 0, 2
        psq_st f11, 0x26(dst), 0, 2
    }
}

void fn_8029AAC0(register u8* dst, register u8* y, register u8* u, register u8* v, register u8* a)
{
    register f32 c0 = 128.0f;
    register f32 c1 = 1.4026f;
    register f32 c2 = -0.71414f;
    register f32 c3 = -0.34414f;
    register f32 c4 = 1.772f;
    asm {
        psq_l f6, 0(u), 0, 2
        psq_l f7, 0(v), 0, 2
        ps_sub f6, f6, c0
        ps_sub f7, f7, c0
        psq_l f5, 0(y), 0, 2
        psq_l f10, 0(a), 1, 2
        ps_madd f9, f6, c4, f5
        ps_madd f8, f7, c2, f5
        ps_madd f5, f7, c1, f5
        ps_madd f8, f6, c3, f8
        ps_merge00 f6, f10, f5
        ps_merge00 f7, f8, f9
        psq_st f6, 0(dst), 0, 2
        psq_st f7, 0x20(dst), 0, 2
        ps_merge01 f6, f10, f5
        ps_merge11 f7, f8, f9
        psq_st f6, 2(dst), 0, 2
        psq_st f7, 0x22(dst), 0, 2
        psq_l f6, 2(u), 0, 2
        psq_l f7, 2(v), 0, 2
        ps_sub f6, f6, c0
        ps_sub f7, f7, c0
        psq_l f5, 2(y), 0, 2
        ps_madd f9, f6, c4, f5
        ps_madd f8, f7, c2, f5
        ps_madd f5, f7, c1, f5
        ps_madd f8, f6, c3, f8
        ps_merge00 f6, f10, f5
        ps_merge00 f7, f8, f9
        psq_st f6, 4(dst), 0, 2
        psq_st f7, 0x24(dst), 0, 2
        ps_merge01 f6, f10, f5
        ps_merge11 f7, f8, f9
        psq_st f6, 6(dst), 0, 2
        psq_st f7, 0x26(dst), 0, 2
    }
}

s32 THPDecGetInfo(u8* data, THPDecDesc* out)
{
    u8 hSample[4];
    u8 vSample[4];
    u8 componentId[4];
    u8 quantizationSelector[4];
    u8 unused[12];
    u8 marker;
    u8 componentCount;
    u8 i;
    u32 j;
    u16 length;

    memset(out, 0, sizeof(THPDecDesc));

    {
        u8 soi0 = *data++;
        u8 soi1 = *data++;

        if (soi0 != 0xFF || soi1 != 0xD8) {
            return 0;
        }
    }

    for (;;) {
        if (*data++ != 0xFF) {
            return 0;
        }

        while (*data == 0xFF) {
            data++;
        }
        marker = *data++;

        if (marker == 0xC0) {
            out->height = data[4] | (data[3] << 8);
            out->width = data[6] | (data[5] << 8);
            componentCount = data[7];
            data += 8;

            if (componentCount != 3) {
                return 0;
            }

            for (i = 0; i < componentCount; i++) {
                u8 factors;

                data++;
                factors = *data++;
                hSample[i] = (u8) (factors >> 4);
                vSample[i] = (u8) (factors & 0xF);
                data++;
            }

            if (hSample[0] / hSample[1] == 2 && hSample[0] / hSample[2] == 2) {
                if (vSample[0] / vSample[1] == 2 &&
                    vSample[0] / vSample[2] == 2)
                {
                    out->format = 4;
                } else if (vSample[0] == vSample[1] &&
                           vSample[0] == vSample[2])
                {
                    out->format = 2;
                }
            } else if (hSample[0] == hSample[1] && hSample[0] == hSample[2]) {
                if (vSample[0] == vSample[1] && vSample[0] == vSample[2]) {
                    out->format = 1;
                }
            } else {
                return 0;
            }
            break;
        } else if (0xC0 <= marker && marker <= 0xFE) {
            length = data[1] | (data[0] << 8);
            data += 2;

            for (j = 0; j < (u32) (length - 2); j++) {
                data++;
            }
        } else {
            return 0;
        }
    }

    return 1;
}

u32 THPDecGetWorkSize(THPDecDesc* desc)
{
    if (desc->format == 4) {
        return (desc->width + desc->width / 2) * 16 + 0x2400;
    } else if (desc->format == 2) {
        return desc->width * 16 + (desc->width / 2) * 32 + 0x2400;
    } else if (desc->format == 1) {
        return desc->width * 0x30 + 0x2400;
    }
    return 0;
}

s32 THPVideoDecode(THPDecHandle* handle, u8* statusOut, THPFileInfo* work, void* data, THPDecDesc* desc)
{
    u8 done;
    THPFileInfo* info;
    u8 status;
    s32 length;
    u32 j;

    handle->data = data;
    handle->info = work;
    if (work == NULL) {
        goto _err_no_work;
    }

    info = work;
    memset(info, 0, 0x7C8);
    info->scratch = (u8*) info;
    info->scratch += 0x7E0;
    info->file = info->scanStart;
    info->cnt = 33;
    info->x7AA = 0;
    info->x7AC = 0;
    info->x7A6 = 0;
    info->x41D = 0;
    info->x40C = 0;
    info->x40E = 0;
    info->validHuffmanTabs = 0;
    info->validQuantTabs = 0;

    __THPSetupBuffers(info);

    done = 0;
    info->file = handle->data;

    for (;;) {
        if ((*(info->file)++) != 0xFF) {
            goto _err_bad_syntax;
        }

        while (*info->file == 0xFF) {
            info->file++;
        }

        status = (*(info->file)++);

        if (status <= 0xD7) {
            if (status == 0xC4) {
                status = __THPReadHuffmanTableSpecification(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else if (status == 0xC0) {
                status = __THPReadFrameHeader(info);
                info->x41F = desc->format;
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else {
                *statusOut = 5;
                return 0;
            }
        } else if (0xD8 <= status && status <= 0xDF) {
            if (status == 0xDD) {
                info->RST = 1;
                info->file += 2;
                info->nMCU = (u16) ((info->file[0] << 8) | info->file[1]);
                info->file += 2;
                info->currMCU = info->nMCU;
            } else if (status == 0xDB) {
                status = __THPReadQuantizationTable(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else if (status == 0xDA) {
                status = __THPReadScaneHeader(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
                done = 1;
                info->scanStart = info->file;
            } else if (status != 0xD8) {
                *statusOut = 5;
                return 0;
            }
        } else if (0xE0 <= status) {
            if (0xE0 <= status && status <= 0xEF) {
                __THPSkipSegment(&info->file);
            } else if (status == 0xFE) {
                length = (info->file[0] << 8) | info->file[1];
                info->file += 2;
                for (j = 0; j < length - 2; j++) {
                    info->file++;
                }
            } else {
                *statusOut = 5;
                return 0;
            }
        }

        if (done) {
            *statusOut = 0;
            return 1;
        }
    }

_err_no_work:
    *statusOut = 2;
    goto _err_exit;

_err_bad_syntax:
    *statusOut = 1;
    goto _err_exit;

_err_bad_status:
    *statusOut = status;

_err_exit:
    return 0;
}

void THPDecDecode(THPDecHandle* handle, void* tileY, void* tileU, void* tileV)
{
    register THPFileInfo* info;
    u32 i;

    info = handle->info;
    info->file = info->scanStart;
    info->cnt = 33;
    info->x7AA = 0;
    info->x7AC = 0;
    info->x7A6 = 0;
    info->x41D = 0;
    info->x40C = 0;
    info->x40E = 0;

    info->components[0].tile = tileY;
    if (info->nComponents >= 2) {
        info->components[1].tile = tileU;
    }
    if (info->nComponents >= 3) {
        info->components[2].tile = tileV;
    }

    __THPGQRSetup(info);

    while (info->x7AC < info->yPixelSize) {
        info->x7AA = 0;
        __THPDecompressiMCURow(info);
        info->x7AC += info->x8D4;
        for (i = 0; i < info->nComponents; i++) {
            info->components[i].tile += info->components[i].x14 *
                                        (info->MCUsPerRow * info->components[i].x18) * 64;
        }
    }

    __THPGQRRestore(info);
}

static s32 __THPGetBit(THPFileInfo* info)
{
    u8* p;
    u32 b;
    s32 cnt;

    cnt = info->cnt;
    if (cnt == 33) {
        p = info->file;
        info->cnt = 26;
        b = *p;
        if (b != 0xFF) {
            info->currByte = b;
            b = (b >> 7) & 1;
            info->file = p + 1;
        } else {
            for (;;) {
                if (p[1] == 0) {
                    p += 2;
                    info->currByte = b;
                    b = (b >> 7) & 1;
                    info->file = p;
                    break;
                }
                b = p[2];
                p += 3;
                if (b != 0xFF) {
                    info->currByte = b;
                    b = (b >> 7) & 1;
                    info->file = p;
                    break;
                }
                p--;
            }
        }
    } else {
        b = info->currByte;
        info->cnt = cnt + 1;
        b = __rlwnm(b, cnt, 31, 31);
    }
    return b;
}

