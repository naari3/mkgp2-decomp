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

static f32 __THPIDCTWorkspace[64];
void __THPDecodeBlock(THPFileInfo* info, u8 c, THPCoeff* block);

u8 fn_80299D58(THPFileInfo* info)
{
    //DB
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
    //DE

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
