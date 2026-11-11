#include "game/clsound_s25_private.h"
#include "game/clsound_spatial_private.h"

#include "game/types/SoundEvent.h"
#include "game/types/ActiveStream.h"
/* Separate objects let MWCC retain the shared BSS base and subobject addresses. */
SoundEvent ClSound_InitSoundSystem_bss_80677F40[37];
static SND_AUX_REVERBHI ClSound_ReverbHI;
static SND_AUX_CHORUS ClSound_Chorus;
ClSoundVoice ClSound_InitSoundSystem_bss_80678378[32];
ActiveStream ClSound_ActiveStreams[4];
extern const char ClSound_rodata_80379100[];
extern const unsigned int lbl_806D94F0, lbl_806D94F4;
extern const float lbl_806D9524, lbl_806D9528, lbl_806D952C, lbl_806D9530, lbl_806D950C, lbl_806D9534;
extern unsigned char ClSound_Initialized, lbl_806CFCA1, lbl_806CFCA2, lbl_806D16B1;
extern void *lbl_806D16B4, *lbl_806D16B8, *lbl_806D16BC;
extern unsigned int ClSound_InitSoundSystem_bss_806D16C4[2];
extern int lbl_806CF010;
extern void DebugPrintf(const char *, ...);
extern void *OSAllocFromHeap(int, unsigned long);
extern void OSFreeToHeap(int, void *);
extern unsigned int ARInit(unsigned int *, unsigned int);
extern void ARQInit(void);
extern void AIInit(void *);
extern int DVDLoad_WaitIfSamePage(unsigned int);
extern void DVDLoad_RecordOpStart(unsigned int);
extern void *memset(void *, int, unsigned long);
extern void fn_801952EC(void);
extern void fn_80195214(unsigned char);
extern void fn_801951FC(unsigned char);
extern void fn_801951B4(unsigned char);

/* Keep the DVD operation bounds together with the instrumented read. */
static inline int ReadSoundFile(DVDFileInfo *file, void *data, unsigned int size,
                               unsigned int start, unsigned int length) {
    unsigned int end;
    int result;
    end = length - 1;
    end = end + start;
    DVDLoad_WaitIfSamePage(start);
    result = DVDReadPrio(file, data, size, 0, 2);
    DVDLoad_RecordOpStart(end);
    return result;
}

static inline void LoadSoundFile(const char *strings, unsigned int offset, void **output) {
    DVDFileInfo file;
    unsigned int size;
    int result;
    void *data = 0;
    DVDFileInfo *file_;
    unsigned int end;
    int result_;
    if (!DVDOpen(strings + offset, &file)) {
        DebugPrintf(strings + 0x3fbc, strings + offset);
    } else if (file.length == 0) {
        DebugPrintf(strings + 0x3fd8, strings + offset);
    } else {
        size = (file.length + 31) & ~31;
        data = OSAllocFromHeap(lbl_806CF010, size);
        if (!data) {
            DebugPrintf(strings + 0x3ff8);
        } else {
            memset(data, 0xe0, size);
            /* fakematch (leversweep inline-to-named-locals): natural code is
             * result = ReadSoundFile(&file, data, size, file.startAddr, file.length);
             * the helper's locals must be named locals of this function, and
             * the end address is start + length - 1 in one expression. */
            file_ = &file;
            end = file.startAddr + file.length - 1;
            DVDLoad_WaitIfSamePage(file.startAddr);
            result_ = DVDReadPrio(file_, data, size, 0, 2);
            DVDLoad_RecordOpStart(end);
            result = result_;
            if (result <= 0) {
                DebugPrintf(strings + 0x401c, strings + offset);
                OSFreeToHeap(lbl_806CF010, data);
                data = 0;
            } else DVDClose(&file);
        }
    }
    *output = data;
}
static inline void PrepareEffects(SND_AUX_REVERBHI *reverb, SND_AUX_CHORUS *chorus) {
        reverb->tempDisableFX = 0;
        reverb->time = lbl_806D9524;
        reverb->preDelay = lbl_806D9528;
        reverb->damping = lbl_806D952C;
        reverb->coloration = lbl_806D9530;
        reverb->crosstalk = lbl_806D950C;
        reverb->mix = lbl_806D9534;
        chorus->baseDelay = 15;
        chorus->variation = 0;
        chorus->period = 500;
        sndAuxCallbackPrepareReverbHI(reverb);
        sndAuxCallbackPrepareChorus(chorus);
}
static inline void ResetEvents(SoundEvent *events) {
    int i;
    for (i = 0; i < 37; i++) events[i].id = -1;
}
static inline void ResetStreams(ActiveStream *streams) {
    int i;
    for (i = 0; i < 4; i++) streams[i].id = -1;
}
#pragma push
#pragma opt_common_subs off
void ClSound_InitSoundSystem(void) {
    const char *strings = ClSound_rodata_80379100;
    void *samples;
    unsigned int hooks[2];
    int i;
    unsigned int aramSize;
    if (!ClSound_Initialized) {
        DebugPrintf(strings + 0x3f64);
        ResetEvents(ClSound_InitSoundSystem_bss_80677F40);
        samples = 0;
        hooks[0] = lbl_806D94F0;
        hooks[1] = lbl_806D94F4;
        aramSize = ARInit(ClSound_InitSoundSystem_bss_806D16C4, 2);
        DebugPrintf(strings + 0x3f90, aramSize);
        ARQInit();
        AIInit(0);
        sndSetHooks((SND_HOOKS *)hooks);
        sndInit(64, 0, 64, 1, 0, 0xc00000);
        LoadSoundFile(strings, 0x3fac, &lbl_806D16B4);
        if (!lbl_806D16B4) goto fail;
        LoadSoundFile(strings, 0x4044, &lbl_806D16B8);
        if (!lbl_806D16B8) goto fail;
        LoadSoundFile(strings, 0x4054, &lbl_806D16BC);
        if (!lbl_806D16BC) goto fail;
        LoadSoundFile(strings, 0x4064, &samples);
        if (!samples) goto fail;
        for (i = 0; i < 22; i++) {
            int group = ((const int *)(strings + 0x3fc))[i];
            if (group >= 0) sndPushGroup(lbl_806D16B8, (unsigned short)group, samples, lbl_806D16BC, lbl_806D16B4);
        }
        OSFreeToHeap(lbl_806CF010, samples);
        PrepareEffects(&ClSound_ReverbHI, &ClSound_Chorus);
        sndSetAuxProcessingCallbacks(0, sndAuxCallbackReverbHI, &ClSound_ReverbHI, 255, 0, sndAuxCallbackChorus, &ClSound_Chorus, 255, 0);
        sndVolume(127, 0, 255);
        for (i = 0; i < 32; i++) {
            ClSound_InitSoundSystem_bss_80678378[i].id = -1;
            ClSound_InitSoundSystem_bss_80678378[i].group = 255;
            ClSound_InitSoundSystem_bss_80678378[i].category = 255;
            ClSound_InitSoundSystem_bss_80678378[i].flags = 0;
        }
        ResetStreams(ClSound_ActiveStreams);
        fn_801952EC();
        fn_80195214(lbl_806CFCA1);
        fn_801951FC(lbl_806CFCA2);
        fn_801951B4(lbl_806D16B1);
        ClSound_Initialized = 1;
        return;
fail:
        if (lbl_806D16B4) OSFreeToHeap(lbl_806CF010, lbl_806D16B4);
        if (lbl_806D16B8) OSFreeToHeap(lbl_806CF010, lbl_806D16B8);
        if (lbl_806D16BC) OSFreeToHeap(lbl_806CF010, lbl_806D16BC);
        if (samples) OSFreeToHeap(lbl_806CF010, samples);
        lbl_806D16B4 = 0;
        lbl_806D16B8 = 0;
        lbl_806D16BC = 0;
        ClSound_Initialized = 0;
    }
}
#pragma pop
