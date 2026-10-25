#include "musyx/platform.h"
#include <string.h>

#if MUSY_TARGET == MUSY_TARGET_DOLPHIN

#include "dolphin/ai.h"
#include "dolphin/base/PPCArch.h"
#include "dolphin/dsp.h"
#include "musyx/assert.h"
#include "musyx/dsp_import.h"
#include "musyx/hardware.h"
#include "musyx/aramdma.h"
#include "musyx/sal.h"

/* File-local data is not split into this unit yet: refer to it by address. */
#define dsp_task lbl_806CAF20
#define dram_image lbl_806CAF80
#define userCallback lbl_806D20AC
#define salAIBufferBase lbl_806D20A4
#define salDspIsDone lbl_806D20A0
#define salLogicIsWaiting lbl_806D209C
#define salLogicActive lbl_806D2098
#define salLastTick lbl_806D2094
#define salDspInitIsDone lbl_806D2090
#define salWaitForDSPThreadQueue lbl_806D2088
#define hwIrqLevel lbl_806D2084
#define oldState lbl_806D2080

extern DSPTaskInfo dsp_task;
extern u16 dram_image[4096];

#if MUSY_VERSION < MUSY_VERSION_CHECK(2, 0, 0) || MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 2)
extern u8 *aramBase;
extern u32 aramSize;
extern SND_SOME_CALLBACK userCallback;
extern u8 salAIBufferIndex;
extern void *salAIBufferBase;
extern volatile u32 salDspIsDone;
extern volatile u32 salLogicIsWaiting;
extern volatile u32 salLogicActive;
extern volatile OSTick salLastTick;
extern volatile u32 salDspInitIsDone;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 2)
extern OSThreadQueue salWaitForDSPThreadQueue;
#endif
extern volatile u16 hwIrqLevel;
extern volatile u32 oldState;
#else
extern volatile u32 oldState;
extern volatile u16 hwIrqLevel;
extern volatile u32 salDspInitIsDone;
extern volatile OSTick salLastTick;
extern volatile u32 salLogicActive;
extern volatile u32 salLogicIsWaiting;
extern volatile u32 salDspIsDone;
extern void *salAIBufferBase;
extern u8 salAIBufferIndex;
extern SND_SOME_CALLBACK userCallback;
#endif

#define DMA_BUFFER_LEN 0x280

u32 salGetStartDelay();

static inline void callUserCallback() {
  if (salLogicActive) {
    return;
  }
  salLogicActive = 1;
  OSEnableInterrupts();

  userCallback();
  OSDisableInterrupts();

  salLogicActive = 0;
}

static void salCallback() {
  salAIBufferIndex = (salAIBufferIndex + 1) % 4;
  AIInitDMA(OSCachedToPhysical(salAIBufferBase) + (salAIBufferIndex * DMA_BUFFER_LEN),
            DMA_BUFFER_LEN);
  salLastTick = OSGetTick();

  if (salDspIsDone) {
    callUserCallback();
  } else {
    salLogicIsWaiting = 1;
  }
}

static void dspInitCallback() {
  salDspIsDone = TRUE;
  salDspInitIsDone = TRUE;
}

static void dspResumeCallback(void *task) {
  salDspIsDone = TRUE;
  if (salLogicIsWaiting) {
    salLogicIsWaiting = FALSE;
    callUserCallback();
  }
}

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 2) //
static void dspDoneCallback() { OSWakeupThread(&salWaitForDSPThreadQueue); }
#endif

#if MUSY_VERSION <= MUSY_VERSION_CHECK(2, 0, 1) //
#define SAL_MALLOC salMalloc
#else
#define SAL_MALLOC salMallocPhysical
#endif

u32 salInitAi(SND_SOME_CALLBACK callback, u32 unk, u32 *outFreq) {
  if ((salAIBufferBase = SAL_MALLOC(DMA_BUFFER_LEN * 4)) != NULL) {
    memset(salAIBufferBase, 0, DMA_BUFFER_LEN * 4);
    DCFlushRange(salAIBufferBase, DMA_BUFFER_LEN * 4);
    salAIBufferIndex = TRUE;
    salLogicIsWaiting = FALSE;
    salDspIsDone = TRUE;
    salLogicActive = FALSE;
    userCallback = callback;
    AIRegisterDMACallback(salCallback);
    AIInitDMA(OSCachedToPhysical(salAIBufferBase) + (salAIBufferIndex * 0x280), 0x280);
    synthInfo.numSamples = 0x20;
    *outFreq = 32000;
    MUSY_DEBUG("MusyX AI interface initialized.\n");
    return TRUE;
  }

  return FALSE;
}

u32 salStartAi() { AIStartDMA(); }

u32 salExitAi() {
  AIRegisterDMACallback(NULL);
  AIStopDMA();
  salFree(salAIBufferBase);
  return TRUE;
}

void *salAiGetDest() {
  u8 index; // r31
  index = (salAIBufferIndex + 2) % 4;
  return (void *)((u8 *)salAIBufferBase + index * DMA_BUFFER_LEN);
}

u32 salInitDsp() {
  u8 _[8];
  dsp_task.iram_mmem_addr = (u16 *)dspSlave;
  dsp_task.iram_length = dspSlaveLength;
  dsp_task.iram_addr = 0;
  dsp_task.dram_mmem_addr = (u16 *)dram_image;
  dsp_task.dram_length = 0x2000;
  dsp_task.dram_addr = 0;
  dsp_task.dsp_init_vector = 0x10;
  dsp_task.dsp_resume_vector = 0x30;
  dsp_task.init_cb = dspInitCallback;
  dsp_task.res_cb = dspResumeCallback;
#if MUSY_VERSION <= MUSY_VERSION_CHECK(2, 0, 1) //
  dsp_task.done_cb = NULL;
#else
  dsp_task.done_cb = dspDoneCallback;
#endif
  dsp_task.req_cb = NULL;
  dsp_task.priority = 0;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 2) //
  OSInitThreadQueue(&salWaitForDSPThreadQueue);
#endif
  DSPInit();
  DSPAddTask(&dsp_task);
  salDspInitIsDone = FALSE;
  hwEnableIrq();
  while (!salDspInitIsDone)
    ;
  hwDisableIrq();
  return TRUE;
}

u32 salExitDsp() {
#if MUSY_VERSION <= MUSY_VERSION_CHECK(2, 0, 1) //
  DSPHalt();
  while (DSPGetDMAStatus())
    ;
  DSPReset();
#else
  int old = OSDisableInterrupts(); // r31
  DSPCancelTask(&dsp_task);
  OSSleepThread(&salWaitForDSPThreadQueue);
  OSRestoreInterrupts(old);
#endif

  return TRUE;
}

static void salStartDsp(u16 *cmdList) {
  salDspIsDone = FALSE;
  PPCSync();
  /* clang-format off */
  MUSY_ASSERT(((u32)cmdList & 0x1F)==0);
  /* clang-format on */
  DSPSendMailToDSP(dspCmdFirstSize | 0xbabe0000);

  while (DSPCheckMailToDSP())
    ;
  DSPSendMailToDSP((u32)cmdList);
  while (DSPCheckMailToDSP())
    ;
}

void salCtrlDsp(s16 *dest) {
  salBuildCommandList(dest, salGetStartDelay());
  salStartDsp(dspCmdList);
}

u32 salGetStartDelay() { return OSTicksToMicroseconds(OSGetTick() - salLastTick); }

void hwInitIrq() {
  oldState = OSDisableInterrupts();
  hwIrqLevel = 1;
}

void hwExitIrq() {}

void hwEnableIrq() {
  if (--hwIrqLevel == 0) {
    OSRestoreInterrupts(oldState);
  }
}

void hwDisableIrq() {
  if ((hwIrqLevel++) == 0) {
    oldState = OSDisableInterrupts();
  }
}

void hwIRQEnterCritical() { OSDisableInterrupts(); }

void hwIRQLeaveCritical() { OSEnableInterrupts(); }

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 0) && MUSY_VERSION < MUSY_VERSION_CHECK(2, 0, 2)
extern u32 aramSize;
extern u8 *aramBase;
#endif
#endif
