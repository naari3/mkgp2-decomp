#ifndef _initialize_h_
#define _initialize_h_

#include <Runtime/platform.h>

#include <dolphin/gx.h>
#include <dolphin/os/OSAlloc.h>
#include <sysdolphin/baselib/video.h>

#define HSD_DEFAULT_FIFO_SIZE (256 * 1024)
#define HSD_DEFAULT_XFB_MAX_NUM 2

/* mkgp2 uses HSD 1.3.x: the init parameters, memory report and memory
 * callbacks differ from melee's HSD. */
typedef struct _HSD_MemReport {
    u32 total;
    u32 system;
    u32 xfb;
    u32 gxfifo;
    u32 heap;
    u8 x14_pad[0x1C - 0x14];
} HSD_MemReport;

typedef struct _HSD_MemoryCallbacks {
    void* (*alloc)(u32 size);
    void (*free)(void* ptr);
    void (*reset)(void);
    long (*check)(void);
    s32 (*is_in_heap)(void* ptr);
} HSD_MemoryCallbacks;

typedef enum _HSD_InitParam {
    HSD_INIT_FIFO_SIZE,
    HSD_INIT_XFB_MAX_NUM,
    HSD_INIT_HEAP_MAX_NUM,
    HSD_INIT_AUDIO_HEAP_SIZE,
    HSD_INIT_RENDER_MODE_OBJ,
    HSD_INIT_HEAP_SIZE,
    HSD_INIT_HEAP_ARENA,
    HSD_INIT_MEMORY_CALLBACKS
} HSD_InitParam;

void HSD_InitComponent(GXRenderModeObj* rm);
void** HSD_AllocateXFB(s32 nbuffer, GXRenderModeObj* rm);
GXFifoObj* HSD_AllocateFifo(u32 size);
OSHeapHandle HSD_GetHeap(void);
HSD_RenderPass HSD_GetCurrentRenderPass(void);
void HSD_StartRender(HSD_RenderPass pass);
void HSD_RequestInvalidate(s32 flags);
void HSD_ObjInit(void);
void HSD_ObjDumpStat(struct _HSD_ObjAllocData* data, char* label);
bool HSD_SetInitParameter(HSD_InitParam param, ...);
void HSD_MemSetCallbacks(HSD_MemoryCallbacks* cb, u32 size);

#endif
