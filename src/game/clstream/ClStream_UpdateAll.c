#include "game/types/port_hooks.h"
#pragma readonly_strings on
#include "game/clsound_s25_private.h"
typedef struct StreamInfo {
    unsigned int unknown, byteLength, frequency;
    unsigned short loop, padE;
    unsigned int loopStart, loopEnd;
    unsigned char pad18[4];
    unsigned char adpcm[0x44];
} StreamInfo;
typedef struct ClStream {
    unsigned char state, pad1[3];
    struct ClStream *pair, *pair2;
    unsigned int handle, flags;
    unsigned char rate, volume, pan, bus;
    DVDFileInfo file;
    StreamInfo *info;
    unsigned int size;
    unsigned char *base;
    unsigned char head, pad61[3];
    unsigned int mask;
    unsigned char pad68[4];
    unsigned int pos, fill, pad74;
} ClStream;
extern unsigned char g_ClStream_Initialized;
extern ClStream g_ClStreams[5];
extern unsigned int g_ClStream_LockDepth;
extern int g_ClStream_SavedInterruptLevel;
extern unsigned char lbl_806D16D1, lbl_806CFCAB, lbl_806CFCAA, lbl_806CFCA9, lbl_806CFCA8;
extern unsigned char *lbl_806D16DC;
extern const float lbl_806D9538, lbl_806D953C, lbl_806D9540;
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);
extern void *memcpy(void *, const void *, unsigned long);
extern void DebugPrintf(const char *, ...);
extern void ClStream_FillChunk(ClStream *);
extern void sndStreamMixParameter(unsigned int, unsigned char, unsigned char, unsigned char, unsigned char);
extern void sndStreamFrq(unsigned int, unsigned int);
extern void sndStreamADPCMParameter(unsigned int, void *);
extern void sndStreamARAMUpdate(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned char sndStreamActivate(unsigned int);
extern void sndStreamDeactivate(unsigned int);
static inline unsigned char StreamVolume(ClStream *s) {
    unsigned int volume;
    if (lbl_806D16D1) {
        if (s->bus == 1) volume = ((unsigned int)lbl_806CFCAB * lbl_806CFCA9) >> 7;
        else volume = ((unsigned int)lbl_806CFCAA * lbl_806CFCA9) >> 7;
    } else {
        if (s->bus == 1) volume = ((unsigned int)lbl_806CFCAB * lbl_806CFCA8) >> 7;
        else volume = ((unsigned int)lbl_806CFCAA * lbl_806CFCA8) >> 7;
    }
    return (s->volume * volume) >> 7;
}
static inline unsigned int StreamFrequency(ClStream *s) {
    unsigned int frequency = s->info->frequency;
    switch (s->rate) {
    case 1: frequency += (unsigned int)(lbl_806D9538 * frequency); break;
    case 2: frequency += (unsigned int)(lbl_806D953C * frequency); break;
    case 3: frequency += (unsigned int)(lbl_806D9540 * frequency); break;
    case 4: frequency += frequency >> 2; break;
    case 5: frequency += frequency >> 1; break;
    case 6: frequency <<= 2; break;
    }
    return frequency;
}
void ClStream_UpdateAll(void) {
    DVDFileInfo *firstFile;
    ClStream *end;
    ClStream *s;
    unsigned int loopEnd;
    if (g_ClStream_Initialized) {
        if (g_ClStream_LockDepth++ == 0) g_ClStream_SavedInterruptLevel = OSDisableInterrupts();
        s = g_ClStreams;
        firstFile = &g_ClStreams[0].file;
        end = &g_ClStreams[4];
        for (; s <= end; s++) {
            if (!s->state) continue;
            switch (s->state) {
            case 1:
                if ((unsigned int)DVDReadPrio(&s->file, lbl_806D16DC, 0x60, 0, 2) != 0x60) break;
                PORT_DATA_LOADED(PORT_DATA_STREAM_HEADER, lbl_806D16DC, 0x60);
                memcpy(s->info, lbl_806D16DC, 0x60);
                s->size = s->info->byteLength >> 1;
                if (s->info->loop) {
                    loopEnd = s->info->loopEnd;
                    loopEnd >>= 1;
                    if (loopEnd > s->size) {
                        DebugPrintf("Stream Length   [%d]\n", s->size);
                        DebugPrintf("       LoopPoint[%d]\n", loopEnd);
                        DebugPrintf("       LoopPoint is over Length...\n");
                    }
                    s->size = loopEnd;
                }
                s->state = 2;
                break;
            case 2:
                ClStream_FillChunk(s);
                if (((s->mask >> (s->head * 2)) & 3) == 1) {
                    s->mask |= 2 << (s->head * 2);
                    if (++s->head >= 4) s->head = 0;
                }
                if (((s->mask >> (s->head * 2)) & 3) == 3) {
                    if (s->pair) {
                        if (s->pair->state == 2 && ((s->mask >> (s->head * 2)) & 3) == 3) {
                            s->state = 3;
                            s->pair->state = 3;
                        }
                    } else if (!s->pair2) s->state = 3;
                }
                break;
            case 3:
                sndStreamMixParameter(s->handle, StreamVolume(s), s->pan, 64, 0);
                sndStreamFrq(s->handle, StreamFrequency(s));
                sndStreamADPCMParameter(s->handle, s->info->adpcm);
                sndStreamARAMUpdate(s->handle, 0, 0x17760, 0, 0);
                if (!sndStreamActivate(s->handle)) {
                    DVDClose(firstFile);
                    g_ClStreams[0].state = 0;
                } else s->state = 4;
                break;
            case 4:
                ClStream_FillChunk(s);
                if (((s->mask >> (s->head * 2)) & 3) == 1) {
                    sndStreamARAMUpdate(s->handle, s->head * 0x5dd8, 0x5dd8, 0, 0);
                    s->mask |= 2 << (s->head * 2);
                    if (++s->head >= 4) s->head = 0;
                }
                if (s->flags & 0x38) {
                    unsigned char step = (s->flags & 0x38) >> 3;
                    if (s->volume > step) {
                        s->volume -= step;
                        s->flags |= 2;
                    } else {
                        s->volume = 0;
                        s->flags |= 2;
                        s->state = 5;
                        break;
                    }
                }
                if (s->flags & 1) sndStreamFrq(s->handle, StreamFrequency(s));
                if ((s->flags & 2) || (s->flags & 4)) {
                    sndStreamMixParameter(s->handle, StreamVolume(s), s->pan, 64, 0);
                    s->flags &= ~7;
                }
                break;
            case 5:
                sndStreamMixParameter(s->handle, 0, s->pan, 64, 0);
                sndStreamDeactivate(s->handle);
                DVDClose(&s->file);
                s->state = 0;
                break;
            }
        }
        if (g_ClStream_LockDepth != 0 && --g_ClStream_LockDepth == 0) OSRestoreInterrupts(g_ClStream_SavedInterruptLevel);
    }
}
