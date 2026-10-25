#include "initialize.h"

#include <stdarg.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "displayfunc.h"
#include "fobj.h"
#include "id.h"
#include "list.h"
#include "lobj.h"
#include "mtx.h"
#include "objalloc.h"
#include "random.h"
#include "robj.h"
#include "shadow.h"
#include "state.h"
#include "tev.h"
#include "video.h"
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

/* Triforce disk-ID setup (GCAInitDiskID). */
extern void fn_802857E0(s32);
extern s32 fn_80287E34(void);

static void HSD_DVDInit(void);
static void HSD_GXInit(void);
static void HSD_OSInit(void);

static HSD_RenderPass current_render_pass;
static s32 invalidate_flags;
static s32 shown;
static s32 iparam_memory_callbacks;
static u32 iparam_heap_size;
static s32 init_done;
static int current_pix_fmt;
static GXFifoObj* DefaultFifoObj;
static void* hsd_heap_next_arena_hi;
static void* hsd_heap_next_arena_lo;
static void* hsd_heap_arena_hi;
static void* hsd_heap_arena_lo;
static void* FrameBuffer[HSD_VI_XFB_MAX];
static HSD_MemReport memReport;

static OSHeapHandle current_heap = -1;
static GXRenderModeObj* rmode = &GXNtsc480IntDf;
static int current_z_fmt = GX_ZC_MID;
static u32 iparam_fifo_size = HSD_DEFAULT_FIFO_SIZE;
static int iparam_xfb_max_num = HSD_DEFAULT_XFB_MAX_NUM;
static GXColor HSD_Init_804D5E1C = { 0 };

/* Not in mkgp2 (dead-stripped); it is what places FrameBuffer before
 * memReport in .bss. */
void** HSD_GetFrameBuffer(void)
{
    return FrameBuffer;
}

#ifdef MUST_MATCH
static char str___FUNCTION__[] = "__FUNCTION__";
#endif
static char str_HSD_GXSetFifoObj[] = "HSD_GXSetFifoObj";

static inline void HSD_GXSetFifoObj(GXFifoObj* fifo)
{
    OSReport(str_HSD_GXSetFifoObj);
    memReport.gxfifo = iparam_fifo_size;
    DefaultFifoObj = fifo;
}

#ifdef MUST_MATCH
static char str_gc[] = "hsd lib init for gc";
#endif

void HSD_InitComponent(GXRenderModeObj* rm)
{
    rmode = rm;
    OSReport("hsd lib init for triforce\n");
    HSD_AllocateXFB(iparam_xfb_max_num, rm);
    {
        GXFifoObj* fifo = HSD_AllocateFifo(iparam_fifo_size);
        HSD_GXSetFifoObj(GXInit(fifo, iparam_fifo_size));
    }
    DVDInit();
    fn_802857E0(0);
    if (fn_80287E34()) {
        OSReport("GCAInitDiskID Error!\n");
    }
    OSReport(str___FUNCTION__);
    HSD_OSInit();
    {
        HSD_VIStatus vi_status;
        GXColor black = { 0, 0, 0, 0 };

        vi_status.rmode = *rmode;
        vi_status.black = GX_TRUE;
        vi_status.vf = GX_TRUE;
        vi_status.gamma = GX_GM_1_0;
        vi_status.clear_clr = black;
        vi_status.clear_z = GX_MAX_Z24;
        vi_status.update_clr = GX_ENABLE;
        vi_status.update_alpha = GX_ENABLE;
        vi_status.update_z = GX_ENABLE;

        HSD_VIInit(&vi_status, FrameBuffer[0], FrameBuffer[1], FrameBuffer[2]);
    }

    HSD_GXInit();
    HSD_DVDInit();
    HSD_IDSetup();
    VIWaitForRetrace();
    HSD_ObjInit();
    init_done = true;
    OSReport("hsd init finish");
}

void HSD_DVDInit(void) {}

void** HSD_AllocateXFB(s32 nbuffer, GXRenderModeObj* rm)
{
    s32 i;
    u32 fb_size;

    if (rm == NULL) {
        return NULL;
    }
    fb_size = ((rm->fbWidth + 0xF) & 0xFFF0) * rm->xfbHeight * 2;
    memReport.xfb = fb_size * nbuffer;
    for (i = 0; i < nbuffer; i++) {
        if ((FrameBuffer[i] = OSAllocFromArenaLo(fb_size, 32)) == NULL) {
            HSD_Panic(__FILE__, 321, "No memory space remains for XFB.\n");
        }
    }
    for (i = nbuffer; i < HSD_VI_XFB_MAX; i++) {
        FrameBuffer[i] = NULL;
    }
    return FrameBuffer;
}

GXFifoObj* HSD_AllocateFifo(u32 size)
{
    GXFifoObj* fifo = OSAllocFromArenaLo(size, 32);
    if (fifo == NULL) {
        HSD_Panic(__FILE__, 340, "no space remains for gx fifo.\n");
    }
    return fifo;
}

void HSD_GXInit(void)
{
    GXLightObj lightobj;
    int i;

    GXInitLightPos(&lightobj, 1.0F, 0.0F, 0.0F);
    GXInitLightDir(&lightobj, 1.0F, 0.0F, 0.0F);
    GXInitLightAttn(&lightobj, 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F);
    GXInitLightColor(&lightobj, HSD_Init_804D5E1C);

    for (i = 0; i < 8; i++) {
        GXLoadLightObjImm(&lightobj, HSD_Index2LightID(i));
    }
    HSD_StateInvalidate(-1);
}

void* HSD_InitMemAlloc(u32 size);
void HSD_InitMemFree(void* ptr);
long HSD_InitMemCheck(void);
void HSD_InitMemReset(void);
s32 HSD_InitMemIsInHeap(void* ptr);

static inline void HSD_TakeNextArena(void)
{
    if (hsd_heap_next_arena_lo != NULL && hsd_heap_next_arena_hi != NULL) {
        hsd_heap_arena_lo = hsd_heap_next_arena_lo;
        hsd_heap_arena_hi = hsd_heap_next_arena_hi;
        hsd_heap_next_arena_lo = NULL;
        hsd_heap_next_arena_hi = NULL;
    }
}

static inline void HSD_CreateArenaHeap(void)
{
    current_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
    OSSetCurrentHeap(current_heap);
    memReport.heap = (u32) hsd_heap_arena_hi - (u32) hsd_heap_arena_lo;
    HSD_ObjSetHeap((u32) hsd_heap_arena_hi - (u32) hsd_heap_arena_lo, NULL);
}

void HSD_OSInit(void)
{
    u32 arena_lo;
    u32 arena_hi;

    OSGetArenaLo();
    OSGetArenaHi();
    memReport.total = OSGetPhysicalMemSize();
    memReport.system = memReport.total - (u32) OSGetArenaHi() +
                       (u32) OSGetArenaLo() - memReport.xfb -
                       memReport.gxfifo;
    if (!iparam_memory_callbacks) {
        HSD_MemoryCallbacks cb;
        cb.alloc = HSD_InitMemAlloc;
        cb.free = HSD_InitMemFree;
        cb.check = HSD_InitMemCheck;
        cb.reset = HSD_InitMemReset;
        cb.is_in_heap = HSD_InitMemIsInHeap;
        HSD_MemSetCallbacks(&cb, sizeof(cb));
        if (hsd_heap_next_arena_lo != NULL && hsd_heap_next_arena_hi != NULL)
        {
            hsd_heap_arena_lo = hsd_heap_next_arena_lo;
            hsd_heap_arena_hi = hsd_heap_next_arena_hi;
            hsd_heap_next_arena_lo = NULL;
            hsd_heap_next_arena_hi = NULL;
            HSD_CreateArenaHeap();
        } else {
            arena_lo = OSRoundUp32B(OSGetArenaLo());
            arena_hi = (u32) OSGetArenaHi();
            hsd_heap_arena_lo = (void*) arena_lo;
            if ((s32) iparam_heap_size > 0) {
                hsd_heap_arena_hi = (void*) (arena_lo + iparam_heap_size);
                if ((u32) hsd_heap_arena_hi > arena_hi) {
                    hsd_heap_arena_hi = (void*) arena_hi;
                }
                hsd_heap_arena_hi =
                    (void*) OSRoundDown32B(hsd_heap_arena_hi);
            } else {
                hsd_heap_arena_hi = (void*) OSRoundDown32B(arena_hi);
            }
            HSD_CreateArenaHeap();
            OSSetArenaLo(hsd_heap_arena_hi);
        }
    }
}

void* HSD_InitMemAlloc(u32 size)
{
    void* addr;

    if (size == 0) {
        return NULL;
    }
    addr = OSAllocFromHeap(HSD_GetHeap(), size);
    HSD_ASSERT(458, addr);
    return addr;
}

void HSD_InitMemFree(void* ptr)
{
    OSFreeToHeap(HSD_GetHeap(), ptr);
}

long HSD_InitMemCheck(void)
{
    return OSCheckHeap(HSD_GetHeap());
}

void HSD_InitMemReset(void)
{
    OSDestroyHeap(current_heap);
    HSD_TakeNextArena();
    current_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
    OSSetCurrentHeap(current_heap);
}

s32 HSD_InitMemIsInHeap(void* ptr)
{
    return hsd_heap_arena_lo <= ptr && ptr < hsd_heap_arena_hi;
}

OSHeapHandle HSD_GetHeap(void)
{
    HSD_ASSERT(518, !iparam_memory_callbacks);
    return current_heap;
}

void HSD_GetNextArena(void** lo, void** hi)
{
    *lo = hsd_heap_next_arena_lo;
    *hi = hsd_heap_next_arena_hi;
}

OSHeapHandle HSD_CreateMainHeap(void* lo, void* hi)
{
    HSD_ASSERT(560, !iparam_memory_callbacks);
    if (lo == NULL || hi == NULL) {
        OSReport("missing argument.\n");
    }
    hsdForgetClassLibrary("sysdolphin_base_library");
    HSD_ObjInit();
    hsd_heap_next_arena_lo = lo;
    hsd_heap_next_arena_hi = hi;
    HSD_InitMemReset();
    return current_heap;
}

HSD_RenderPass HSD_GetCurrentRenderPass(void)
{
    return current_render_pass;
}

void HSD_StartRender(HSD_RenderPass pass)
{
    GXRenderModeObj* rmode = HSD_VIGetRenderMode();
    current_render_pass = pass;
    if (rmode->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, current_z_fmt);
    } else {
        GXSetPixelFmt(current_pix_fmt, GX_ZC_LINEAR);
    }
    GXSetFieldMode(rmode->field_rendering, rmode->xfbHeight < rmode->viHeight);
    if (invalidate_flags) {
        if (invalidate_flags & 1) {
            GXInvalidateVtxCache();
        }
        if (invalidate_flags & 2) {
            GXInvalidateTexAll();
        }
        invalidate_flags = 0;
    }
}

void fn_802D47E8(void)
{
    // Does nothing, but needs the comparison to match
    if (current_render_pass == HSD_RP_OFFSCREEN) {
        return;
    }
}

void HSD_RequestInvalidate(s32 flags)
{
    invalidate_flags |= flags;
}

void HSD_ObjInit(void)
{
    HSD_ListInitAllocData();
    HSD_AObjInitAllocData();
    HSD_FObjInitAllocData();
    HSD_IDInitAllocData();
    HSD_VecInitAllocData();
    HSD_MtxInitAllocData();
    HSD_RObjInitAllocData();
    HSD_RenderInitAllocData();
    HSD_ShadowInitAllocData();
    HSD_ZListInitAllocData();
}

#ifdef MUST_MATCH
static char str_pix_fmt_neq_gx_pf_rgb565_z16[] = "pix_fmt != GX_PF_RGB565_Z16";
static char str_objalloc_h[] = "objalloc.h";
#endif

void HSD_ObjDumpStat(HSD_ObjAllocData* data, char* label)
{
    OSReport("objalloc: %s\tusing %d\tfreed %d\tpeak %d\n", label,
             data->used, data->free, data->peak);
}

bool HSD_SetInitParameter(HSD_InitParam param, ...)
{
    va_list ap;
    bool ok = false;

    if (init_done) {
        if (!shown) {
            OSReport(
                "init parameter should be set before invoking HSD_Init().\n");
            shown = true;
        }
        return false;
    }

    va_start(ap, param);
    switch (param) {
    case HSD_INIT_FIFO_SIZE: {
        u32 fifo_size = va_arg(ap, u32);
        if (fifo_size > 0) {
            iparam_fifo_size = fifo_size;
            ok = true;
        }
    } break;

    case HSD_INIT_XFB_MAX_NUM: {
        u32 xfb_max_num = va_arg(ap, u32);
        if (xfb_max_num > 0) {
            iparam_xfb_max_num = xfb_max_num;
            ok = true;
        }
    } break;

    case HSD_INIT_HEAP_SIZE: {
        u32 heap_size = va_arg(ap, u32);
        if (heap_size < OSGetPhysicalMemSize()) {
            iparam_heap_size = heap_size;
            ok = true;
        }
    } break;

    case HSD_INIT_HEAP_ARENA: {
        void* lo = va_arg(ap, void*);
        void* hi = va_arg(ap, void*);
        hsd_heap_next_arena_lo = lo;
        hsd_heap_next_arena_hi = hi;
        ok = true;
    } break;

    case HSD_INIT_MEMORY_CALLBACKS: {
        HSD_MemoryCallbacks cb;
        cb.alloc = va_arg(ap, void*);
        cb.free = va_arg(ap, void*);
        cb.reset = va_arg(ap, void*);
        cb.check = va_arg(ap, void*);
        cb.is_in_heap = va_arg(ap, void*);
        if (va_arg(ap, void*) != NULL) {
            OSReport("ERROR in HSD_SetInitParameter():\n");
            OSReport("  HSD_INIT_MEMORY_CALLBACKS was given invalid "
                     "arguments.\n");
        } else {
            HSD_MemSetCallbacks(&cb, sizeof(cb));
            iparam_memory_callbacks = true;
            ok = true;
        }
    } break;

    case HSD_INIT_RENDER_MODE_OBJ: {
        GXRenderModeObj* rm = va_arg(ap, GXRenderModeObj*);
        if (rm != NULL) {
            rmode = rm;
            ok = true;
        }
    } break;

    case HSD_INIT_HEAP_MAX_NUM:
        OSReport("ERROR in HSD_SetInitParameter():\n");
        OSReport("  HSD_INIT_HEAP_MAX_NUM is obsolete since 1.3.0.0. \n");
        if (va_arg(ap, s32) == 0) {
            ok = true;
        }
        break;

    case HSD_INIT_AUDIO_HEAP_SIZE:
        OSReport("ERROR in HSD_SetInitParameter():\n");
        OSReport("  HSD_INIT_AUDIO_HEAP_SIZE is obsolete since 1.3.0.0. \n");
        break;
    }
    va_end(ap);

    return ok;
}
