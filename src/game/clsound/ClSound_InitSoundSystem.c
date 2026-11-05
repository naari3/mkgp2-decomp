#include "game/clsound_s25_private.h"

typedef struct SoundEvent { unsigned int id; int state; int countdown; } SoundEvent;
typedef struct SoundWorkspace {
    SoundEvent events[37];
    SND_AUX_REVERBHI reverb;
    SND_AUX_CHORUS chorus;
    unsigned char slots[0x380];
    unsigned int streams[8];
} SoundWorkspace;
typedef struct SoundSlot {
    unsigned int flags, id;
    unsigned char group, pad9[15], channel, pad19[3];
} SoundSlot;
typedef struct ActiveStream { unsigned int handle, id; } ActiveStream;
extern SoundWorkspace lbl_80677F40;
extern SoundSlot lbl_80678378[32];
extern ActiveStream ClSound_ActiveStreams[4];
extern const char lbl_80379100[];
extern const unsigned int lbl_806D94F0, lbl_806D94F4;
extern const float lbl_806D9524, lbl_806D9528, lbl_806D952C, lbl_806D9530, lbl_806D950C, lbl_806D9534;
extern unsigned char ClSound_Initialized, lbl_806CFCA1, lbl_806CFCA2, lbl_806D16B1;
extern void *lbl_806D16B4, *lbl_806D16B8, *lbl_806D16BC;
extern unsigned int lbl_806D16C4[2];
extern int lbl_806CF010;
extern void DebugPrintf(const char *, ...);
extern void *OSAllocFromHeap(int, unsigned long);
extern void OSFreeToHeap(int, void *);
extern unsigned int ARInit(unsigned int *, unsigned int);
extern void ARQInit(void);
extern void AIInit(void *);
extern void DVDLoad_WaitIfSamePage(unsigned int);
extern void DVDLoad_RecordOpStart(unsigned int);
extern void *memset(void *, int, unsigned long);
extern void fn_801952EC(void);
extern void fn_80195214(unsigned char);
extern void fn_801951FC(unsigned char);
extern void fn_801951B4(unsigned char);

static inline void *LoadSoundFile(const char *strings, unsigned int offset) {
    DVDFileInfo file;
    const char *path = strings + offset;
    unsigned int size, end;
    int result;
    void *data = 0;
    if (!DVDOpen(path, &file)) {
        DebugPrintf(strings + 0x3fbc, path);
    } else if (file.length == 0) {
        DebugPrintf(strings + 0x3fd8, path);
    } else {
        size = (file.length + 31) & ~31;
        data = OSAllocFromHeap(lbl_806CF010, size);
        if (!data) {
            DebugPrintf(strings + 0x3ff8);
        } else {
            memset(data, 0xe0, size);
            end = file.startAddr + (file.length - 1);
            DVDLoad_WaitIfSamePage(file.startAddr);
            result = DVDReadPrio(&file, data, size, 0, 2);
            DVDLoad_RecordOpStart(end);
            if (result <= 0) {
                DebugPrintf(strings + 0x401c, path);
                OSFreeToHeap(lbl_806CF010, data);
                data = 0;
            } else DVDClose(&file);
        }
    }
    return data;
}
void ClSound_InitSoundSystem(void) {
    const char *strings = lbl_80379100;
    SoundWorkspace *work = &lbl_80677F40;
    void *samples;
    unsigned int hooks[2];
    int i;
    if (!ClSound_Initialized) {
        DebugPrintf(strings + 0x3f64);
        for (i = 0; i < 37; i++) work->events[i].id = -1;
        samples = 0;
        hooks[0] = lbl_806D94F0;
        hooks[1] = lbl_806D94F4;
        DebugPrintf(strings + 0x3f90, ARInit(lbl_806D16C4, 2));
        ARQInit();
        AIInit(0);
        sndSetHooks((SND_HOOKS *)hooks);
        sndInit(64, 0, 64, 1, 0, 0xc00000);
        lbl_806D16B4 = LoadSoundFile(strings, 0x3fac);
        if (!lbl_806D16B4) goto fail;
        lbl_806D16B8 = LoadSoundFile(strings, 0x4044);
        if (!lbl_806D16B8) goto fail;
        lbl_806D16BC = LoadSoundFile(strings, 0x4054);
        if (!lbl_806D16BC) goto fail;
        samples = LoadSoundFile(strings, 0x4064);
        if (!samples) goto fail;
        for (i = 0; i < 22; i++) {
            int group = ((const int *)(strings + 0x3fc))[i];
            if (group >= 0) sndPushGroup(lbl_806D16B8, (unsigned short)group, samples, lbl_806D16BC, lbl_806D16B4);
        }
        OSFreeToHeap(lbl_806CF010, samples);
        work->reverb.tempDisableFX = 0;
        work->reverb.time = lbl_806D9524;
        work->reverb.preDelay = lbl_806D9528;
        work->reverb.damping = lbl_806D952C;
        work->reverb.coloration = lbl_806D9530;
        work->reverb.crosstalk = lbl_806D950C;
        work->reverb.mix = lbl_806D9534;
        work->chorus.baseDelay = 15;
        work->chorus.variation = 0;
        work->chorus.period = 500;
        sndAuxCallbackPrepareReverbHI(&work->reverb);
        sndAuxCallbackPrepareChorus(&work->chorus);
        sndSetAuxProcessingCallbacks(0, sndAuxCallbackReverbHI, &work->reverb, 255, 0, sndAuxCallbackChorus, &work->chorus, 255, 0);
        sndVolume(127, 0, 255);
        for (i = 0; i < 32; i++) {
            ((SoundSlot *)work->slots)[i].id = -1;
            ((SoundSlot *)work->slots)[i].group = 255;
            ((SoundSlot *)work->slots)[i].channel = 255;
            ((SoundSlot *)work->slots)[i].flags = 0;
        }
        for (i = 0; i < 4; i++) ((ActiveStream *)work->streams)[i].id = -1;
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
