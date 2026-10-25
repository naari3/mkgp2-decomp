#include <string.h>

#include <dolphin/base/PPCArch.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

#include "__gx.h"
#include "__gx_2003.h"

#if SDK_REVISION < 1
/* mkgp2 links the Jul 23 2003 GX build */
#define BUILD_DATE  "Jul 23 2003"
#define DBUILD_TIME "11:27:39"
#define RBUILD_TIME "11:27:39"
#elif SDK_REVISION < 2
#define BUILD_DATE  "Apr  5 2004"
#define DBUILD_TIME "03:55:13"
#define RBUILD_TIME "04:13:58"
#else
#define BUILD_DATE  "Nov 10 2004"
#define DBUILD_TIME "06:08:50"
#define RBUILD_TIME "06:27:12"
#endif

#ifdef DEBUG
const char* __GXVersion = "<< Dolphin SDK - GX\tdebug build: "BUILD_DATE" "DBUILD_TIME" (0x2301) >>";
#else
const char* __GXVersion = "<< Dolphin SDK - GX\trelease build: "BUILD_DATE" "RBUILD_TIME" (0x2301) >>";
#endif

static GXFifoObj FifoObj;

static GXData gxData;
GXData* const __GXData = &gxData;

// these are supposed to be in-function static, but it messed up sbss order
u32 resetFuncRegistered;
u32 calledOnce;
OSTime time;
u32 peCount;

void* __memReg;
void* __peReg;
void* __cpReg;
void* __piReg;

#if DEBUG
GXBool __GXinBegin;
#endif

static u16 DefaultTexData[] __attribute__((aligned(32))) = {
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

static GXVtxAttrFmtList GXDefaultVATList[] = {
    {GX_VA_POS, GX_POS_XYZ, GX_F32, 0},
    {GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0},
    {GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0},
    {GX_VA_CLR1, GX_CLR_RGBA, GX_RGBA8, 0},
    {GX_VA_TEX0, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX1, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX2, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX3, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX4, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX5, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX6, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX7, GX_TEX_ST, GX_F32, 0},
    {GX_VA_NULL, 0, 0, 0},
};

static f32 GXDefaultProjData[] = {1.0f, 0.0f, 1.0f, 0.0f, -1.0f, -2.0f, 0.0f};

static u32 GXTexRegionAddrTable[] = {
    0x00000, 0x10000, 0x20000, 0x30000, 0x40000, 0x50000, 0x60000, 0x70000, 0x08000, 0x18000,
    0x28000, 0x38000, 0x48000, 0x58000, 0x68000, 0x78000, 0x00000, 0x90000, 0x20000, 0xB0000,
    0x40000, 0x98000, 0x60000, 0xB8000, 0x80000, 0x10000, 0xA0000, 0x30000, 0x88000, 0x50000,
    0xA8000, 0x70000, 0x00000, 0x90000, 0x20000, 0xB0000, 0x40000, 0x90000, 0x60000, 0xB0000,
    0x80000, 0x10000, 0xA0000, 0x30000, 0x80000, 0x50000, 0xA0000, 0x70000,
};

// prototypes
static int __GXShutdown(int final);

static OSResetFunctionInfo GXResetFuncInfo = {__GXShutdown, 0x7F, NULL, NULL};

asm BOOL IsWriteGatherBufferEmpty(void) {
    sync
    mfspr r3, WPAR
    andi. r3, r3, 1
}

static void EnableWriteGatherPipe(void) {
    u32 hid2 = PPCMfhid2();

    PPCMtwpar(OSUncachedToPhysical((void*)GXFIFO_ADDR));
    hid2 |= 0x40000000;
    PPCMthid2(hid2);
}

static void DisableWriteGatherPipe(void) {
    u32 hid2 = PPCMfhid2();

    hid2 &= ~0x40000000;
    PPCMthid2(hid2);
}

static GXTexRegion*__GXDefaultTexRegionCallback(const GXTexObj* t_obj, GXTexMapID id) {
    GXTexFmt fmt;
    u8 mm;

    fmt = GXGetTexObjFmt(t_obj);
    mm = GXGetTexObjMipMap(t_obj);
    id = (GXTexMapID)(id % GX_MAX_TEXMAP);

    switch (fmt) {
    case GX_TF_RGBA8:
        if (mm) {
            return &__GXData->TexRegions2[id];
        }
        return &__GXData->TexRegions1[id];
    case GX_TF_C4:
    case GX_TF_C8:
    case GX_TF_C14X2:
        return &__GXData->TexRegions0[id];
    default:
        if (mm) {
            return &__GXData->TexRegions1[id];
        }
        return &__GXData->TexRegions0[id];
    }
}

static GXTlutRegion* __GXDefaultTlutRegionCallback(u32 idx) {
    if (idx >= 20) {
        return NULL;
    }
    return &__GXData->TlutRegions[idx];
}

#if DEBUG
static void __GXDefaultVerifyCallback(GXWarningLevel level, u32 id, const char* msg) {
    OSReport("Level %1d, Warning %3d: %s\n", level, id, msg);
}
#endif

static int __GXShutdown(BOOL final) {
    u32 reg;
    u32 peCountNew;
    OSTime timeNew;

    if (!final) {
        if (!calledOnce) {
            peCount = __GXReadMEMCounterU32(0x28, 0x27);
            time = OSGetTime();
            calledOnce = 1;
            return 0;
        }

        timeNew = OSGetTime();
        peCountNew = __GXReadMEMCounterU32(0x28, 0x27);

        if (timeNew - time < 10) {
            return 0;
        }

        if (peCountNew != peCount) {
            peCount = peCountNew;
            time = timeNew;
            return 0;
        }

    } else {
        GXSetBreakPtCallback(NULL);
        GXSetDrawSyncCallback(NULL);
        GXSetDrawDoneCallback(NULL);

        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);

        PPCSync();

        reg = 0;
        GX_SET_CP_REG(1, reg);

        reg = 3;
        GX_SET_CP_REG(2, reg);

        __GXData->abtWaitPECopy = 1;

        __GXAbort();
    }

    return 1;
}

#define SOME_SET_REG_MACRO(reg, size, shift, val)                                                   \
	do {                                                                                            \
		(reg) = (u32)__rlwimi((u32)(reg), (val), (shift), (32 - (shift) - (size)), (31 - (shift))); \
	} while (0);

void __GXInitRevisionBits(void) {
    u32 i;

    for (i = 0; i < 8; i++) {
        s32 regAddr;
        SOME_SET_REG_MACRO(__GXData->vatA[i], 1, 30, 1);
        SOME_SET_REG_MACRO(__GXData->vatB[i], 1, 31, 1);

        GX_WRITE_U8(0x8);
        GX_WRITE_U8(i | 0x80);
        GX_WRITE_U32(__GXData->vatB[i]);
        regAddr = i - 12;
    }

    {
        u32 reg1 = 0;
        u32 reg2 = 0;

        SOME_SET_REG_MACRO(reg1, 1, 0, 1);
        SOME_SET_REG_MACRO(reg1, 1, 1, 1);
        SOME_SET_REG_MACRO(reg1, 1, 2, 1);
        SOME_SET_REG_MACRO(reg1, 1, 3, 1);
        SOME_SET_REG_MACRO(reg1, 1, 4, 1);
        SOME_SET_REG_MACRO(reg1, 1, 5, 1);
        GX_WRITE_XF_REG(0, reg1);

        SOME_SET_REG_MACRO(reg2, 1, 0, 1);
        GX_WRITE_XF_REG(0x12, reg2);
#if DEBUG
        __gxVerif->xfRegsDirty[0] = 0;
#endif
    }

    {
        u32 reg = 0;
        SOME_SET_REG_MACRO(reg, 1, 0, 1);
        SOME_SET_REG_MACRO(reg, 1, 1, 1);
        SOME_SET_REG_MACRO(reg, 1, 2, 1);
        SOME_SET_REG_MACRO(reg, 1, 3, 1);
        SOME_SET_REG_MACRO(reg, 8, 24, 0x58);
        GX_WRITE_RAS_REG(reg);
    }
}

/* 2003 version (pikmin2) */
GXFifoObj* GXInit(void* base, u32 size)
{
	u32 i;
	u32 pad;  // for stack matching
	u32 pad2; // for stack matching

	OSRegisterVersion(__GXVersion);
	gx->inDispList    = GX_FALSE;
	gx->dlSaveContext = GX_TRUE;
	gx->abtWaitPECopy = GX_TRUE;

	gx->tcsManEnab = 0;
	gx->tevTcEnab  = 0;

	GXSetMisc(GX_MT_XF_FLUSH, 0);

	__piReg  = (void*)OSPhysicalToUncached(GX_PI_ADDR);
	__cpReg  = (void*)OSPhysicalToUncached(GX_CP_ADDR);
	__peReg  = (void*)OSPhysicalToUncached(GX_PE_ADDR);
	__memReg = (void*)OSPhysicalToUncached(GX_MEM_ADDR);

	__GXFifoInit();

	GXInitFifoBase(&FifoObj, base, size);
	GXSetCPUFifo(&FifoObj);
	GXSetGPFifo(&FifoObj);

	if (!resetFuncRegistered) {
		OSRegisterResetFunction(&GXResetFuncInfo);
		resetFuncRegistered = 1;
	}

	__GXPEInit();
	EnableWriteGatherPipe();

	gx->genMode = 0;
	GX_SET_REG(gx->genMode, 0, 0, 7);

	gx->bpMask = 255;
	GX_SET_REG(gx->bpMask, 0xF, 0, 7);

	gx->lpSize = 0;
	GX_SET_REG(gx->lpSize, 34, 0, 7);

	for (i = 0; i < GX_MAXTEVSTAGE; i++) {
		gx->tevc[i]     = 0;
		gx->teva[i]     = 0;
		gx->tref[i / 2] = 0;
		gx->texmapId[i] = GX_TEXMAP_NULL;

		GX_SET_REG(gx->tevc[i], 0xC0 + i * 2, 0, 7);
		GX_SET_REG(gx->teva[i], 0xC1 + i * 2, 0, 7);
		GX_SET_REG(gx->tevKsel[i / 2], 0xF6 + i / 2, 0, 7);
		GX_SET_REG(gx->tref[i / 2], 0x28 + i / 2, 0, 7);
	}

	gx->iref = 0;
	GX_SET_REG(gx->iref, 0x27, 0, 7);

	for (i = 0; i < GX_MAX_TEXCOORD; i++) {
		gx->suTs0[i] = 0;
		gx->suTs1[i] = 0;

		GX_SET_REG(gx->suTs0[i], 0x30 + i * 2, 0, 7);
		GX_SET_REG(gx->suTs1[i], 0x31 + i * 2, 0, 7);
	}

	GX_SET_REG(gx->suScis0, 0x20, 0, 7);
	GX_SET_REG(gx->suScis1, 0x21, 0, 7);

	GX_SET_REG(gx->cmode0, 0x41, 0, 7);
	GX_SET_REG(gx->cmode1, 0x42, 0, 7);

	GX_SET_REG(gx->zmode, 0x40, 0, 7);
	GX_SET_REG(gx->peCtrl, 0x43, 0, 7);

	GX_SET_REG(gx->cpTex, 0, 23, 24);

	gx->zScale  = 1.6777216E7f;
	gx->zOffset = 0.0f;

	gx->dirtyState = 0;
	gx->dirtyVAT   = 0;

	{
		u32 val1;
		u32 val2;

		val2 = OS_BUS_CLOCK / 500;

		__GXFlushTextureState();

		val1 = (val2 / 2048) | 0x69000400;

		GX_BP_LOAD_REG(val1);

		__GXFlushTextureState();

		val1 = (val2 / 4224) | 0x46000200;

		GX_BP_LOAD_REG(val1);
	}

	for (i = 0; i < 8; i++) {
		GX_SET_REG(gx->vatA[i], 1, 1, 1);
		GX_SET_REG(gx->vatB[i], 1, 0, 0);

		GX_CP_LOAD_REG(i | 0x80, gx->vatB[i]);
	}

	{
		u32 reg1 = 0;
		u32 reg2 = 0;

		GX_SET_REG(reg1, 1, 31, 31);
		GX_SET_REG(reg1, 1, 30, 30);
		GX_SET_REG(reg1, 1, 29, 29);
		GX_SET_REG(reg1, 1, 28, 28);
		GX_SET_REG(reg1, 1, 27, 27);
		GX_SET_REG(reg1, 1, 26, 26);

		GX_XF_LOAD_REG(0x1000, reg1);

		GX_SET_REG(reg2, 1, 31, 31);

		GX_XF_LOAD_REG(0x1012, reg2);
	}

	{
		u32 reg = 0;
		GX_SET_REG(reg, 1, 31, 31);
		GX_SET_REG(reg, 1, 30, 30);
		GX_SET_REG(reg, 1, 29, 29);
		GX_SET_REG(reg, 1, 28, 28);
		GX_SET_REG(reg, 0x58, 0, 7);

		GX_BP_LOAD_REG(reg);
	}

	for (i = 0; i < GX_MAX_TEXMAP; i++) {
		GXInitTexCacheRegion(&gx->TexRegions0[i], GX_FALSE, GXTexRegionAddrTable[i], GX_TEXCACHE_32K, GXTexRegionAddrTable[i + 8],
		                     GX_TEXCACHE_32K);
		GXInitTexCacheRegion(&gx->TexRegions1[i], GX_FALSE, GXTexRegionAddrTable[i + 16], GX_TEXCACHE_32K, GXTexRegionAddrTable[i + 24],
		                     GX_TEXCACHE_32K);
		GXInitTexCacheRegion(&gx->TexRegions2[i], GX_TRUE, GXTexRegionAddrTable[i + 32], GX_TEXCACHE_32K, GXTexRegionAddrTable[i + 40],
		                     GX_TEXCACHE_32K);
	}

	for (i = 0; i < GX_MAX_TLUT; i++) {
		GXInitTlutRegion(&gx->TlutRegions[i], 0xC0000 + 0x2000 * i, GX_TLUT_256);
	}

	for (i = 0; i < GX_MAX_BIGTLUT; i++) {
		GXInitTlutRegion(&gx->TlutRegions[i + 16], 0xE0000 + 0x8000 * i, GX_TLUT_1K);
	}

	GX_SET_CP_REG(3, 0);

	GX_SET_REG(gx->perfSel, 0, 24, 27);

	GX_CP_LOAD_REG(0x20, gx->perfSel)

	GX_XF_LOAD_REG(0x1006, 0);

	GX_BP_LOAD_REG(0x23000000)
	GX_BP_LOAD_REG(0x24000000)
	GX_BP_LOAD_REG(0x67000000)

	__GXSetIndirectMask(0);
	__GXSetTmemConfig(2);
	__GXInitGX();

	return &FifoObj;
}

void __GXInitGX(void) {
    GXRenderModeObj* rmode;
    GXTexObj tex_obj;
    float identity_mtx[3][4];
    GXColor clear = {64, 64, 64, 255};
    GXColor black = {0, 0, 0, 0};
    GXColor white = {255, 255, 255, 255};
    u32 i;

    switch (VIGetTvFormat()) {
    case VI_NTSC:    rmode = &GXNtsc480IntDf; break;
    case VI_PAL:     rmode = &GXPal528IntDf;  break;
    case VI_EURGB60: rmode = &GXEurgb60Hz480IntDf; break;
    case VI_MPAL:    rmode = &GXMpal480IntDf; break;
    default:
        ASSERTMSGLINE(1342, 0, "GXInit: invalid TV format");
        rmode = &GXNtsc480IntDf;
        break;
    }

    GXSetCopyClear(clear, 0xFFFFFF);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 0x3C);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, 0x3C);
    GXSetTexCoordGen(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, 0x3C);
    GXSetTexCoordGen(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, 0x3C);
    GXSetTexCoordGen(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, 0x3C);
    GXSetTexCoordGen(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, 0x3C);
    GXSetTexCoordGen(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, 0x3C);
    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();

    for (i = GX_VA_POS; i <= GX_LIGHT_ARRAY; i++) {
        GXSetArray(i, __GXData, 0);
    }

    for (i = GX_VTXFMT0; i < GX_MAX_VTXFMT; i++) {
        GXSetVtxAttrFmtv(i, GXDefaultVATList);
    }

    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetPointSize(6, GX_TO_ZERO);
    GXEnableTexOffsets(GX_TEXCOORD0, 0, 0);
    GXEnableTexOffsets(GX_TEXCOORD1, 0, 0);
    GXEnableTexOffsets(GX_TEXCOORD2, 0, 0);
    GXEnableTexOffsets(GX_TEXCOORD3, 0, 0);
    GXEnableTexOffsets(GX_TEXCOORD4, 0, 0);
    GXEnableTexOffsets(GX_TEXCOORD5, 0, 0);
    GXEnableTexOffsets(GX_TEXCOORD6, 0, 0);
    GXEnableTexOffsets(GX_TEXCOORD7, 0, 0);
    identity_mtx[0][0] = 1.0f;
    identity_mtx[0][1] = 0.0f;
    identity_mtx[0][2] = 0.0f;
    identity_mtx[0][3] = 0.0f;
    identity_mtx[1][0] = 0.0f;
    identity_mtx[1][1] = 1.0f;
    identity_mtx[1][2] = 0.0f;
    identity_mtx[1][3] = 0.0f;
    identity_mtx[2][0] = 0.0f;
    identity_mtx[2][1] = 0.0f;
    identity_mtx[2][2] = 1.0f;
    identity_mtx[2][3] = 0.0f;
    GXLoadPosMtxImm(identity_mtx, GX_PNMTX0);
    GXLoadNrmMtxImm(identity_mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity_mtx, GX_IDENTITY, GX_MTX3x4);
    GXLoadTexMtxImm(identity_mtx, GX_PTIDENTITY, GX_MTX3x4);
    GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->xfbHeight, 0.0f, 1.0f);
    GXSetProjectionv(GXDefaultProjData);
    GXSetCoPlanar(GX_DISABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetScissor(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetScissorBoxOffset(0, 0);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, black);
    GXSetChanMatColor(GX_COLOR0A0, white);
    GXSetChanCtrl(GX_COLOR1A1, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, black);
    GXSetChanMatColor(GX_COLOR1A1, white);
    GXInvalidateTexAll();
    GXSetTexRegionCallback((GXTexRegionCallback)__GXDefaultTexRegionCallback);
    GXSetTlutRegionCallback(__GXDefaultTlutRegionCallback);

    GXInitTexObj(&tex_obj, DefaultTexData, 4, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
    GXLoadTexObj(&tex_obj, GX_TEXMAP0);
    GXLoadTexObj(&tex_obj, GX_TEXMAP1);
    GXLoadTexObj(&tex_obj, GX_TEXMAP2);
    GXLoadTexObj(&tex_obj, GX_TEXMAP3);
    GXLoadTexObj(&tex_obj, GX_TEXMAP4);
    GXLoadTexObj(&tex_obj, GX_TEXMAP5);
    GXLoadTexObj(&tex_obj, GX_TEXMAP6);
    GXLoadTexObj(&tex_obj, GX_TEXMAP7);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD4, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD5, GX_TEXMAP5, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD6, GX_TEXMAP6, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD7, GX_TEXMAP7, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);

    for (i = GX_TEVSTAGE0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel((GXTevStageID)i, GX_TEV_KASEL_1);
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = GX_TEVSTAGE0; i < GX_MAX_TEVSTAGE; i++)
        GXSetTevDirect((GXTevStageID)i);

    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.1f, 1.0f, black);
    GXSetFogRangeAdj(GX_DISABLE, 0, NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_ENABLE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
    GXSetDither(GX_ENABLE);
    GXSetDstAlpha(GX_DISABLE, 0);
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GXSetFieldMask(GX_ENABLE, GX_ENABLE);
    GXSetFieldMode(rmode->field_rendering,
                   ((rmode->viHeight == 2 * rmode->xfbHeight) ? GX_ENABLE : GX_DISABLE));

    GXSetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyDst(rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyYScale((f32)(rmode->xfbHeight) / (f32)(rmode->efbHeight));
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);
    GXSetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
    GXClearBoundingBox();

    GXPokeColorUpdate(GX_TRUE);
    GXPokeAlphaUpdate(GX_TRUE);
    GXPokeDither(GX_FALSE);
    GXPokeBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ONE, GX_LO_SET);
    GXPokeAlphaMode(GX_ALWAYS, 0);
    GXPokeAlphaRead(GX_READ_FF);
    GXPokeDstAlpha(GX_DISABLE, 0);
    GXPokeZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);

    GXSetGPMetric(GX_PERF0_NONE, GX_PERF1_NONE);
    GXClearGPMetric();
}
