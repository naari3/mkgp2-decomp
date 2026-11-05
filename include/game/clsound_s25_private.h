#ifndef GAME_CLSOUND_S25_PRIVATE_H
#define GAME_CLSOUND_S25_PRIVATE_H
/* Layouts follow dolphin/dvd.h and musyx/musyx.h. Their umbrella includes
 * require unavailable C library headers in the game compiler profile. */
typedef struct DVDFileInfo {
    unsigned char commandBlock[0x30];
    unsigned int startAddr, length;
    void *callback;
} DVDFileInfo;
extern int DVDOpen(const char *, DVDFileInfo *);
extern int DVDReadPrio(DVDFileInfo *, void *, int, int, int);
extern int DVDClose(DVDFileInfo *);
typedef struct SND_AUX_REVERBHI {
    unsigned char work[0x1c4];
    unsigned char tempDisableFX, pad[3];
    float coloration, mix, time, damping, preDelay, crosstalk;
} SND_AUX_REVERBHI;
typedef struct SND_AUX_CHORUS {
    unsigned char work[0x90];
    unsigned int baseDelay, variation, period;
} SND_AUX_CHORUS;
typedef struct SND_HOOKS { void *alloc, *free; } SND_HOOKS;
extern void sndSetHooks(SND_HOOKS *);
extern int sndInit(unsigned char, unsigned char, unsigned char, unsigned char, unsigned int, unsigned int);
extern unsigned char sndPushGroup(void *, unsigned short, void *, void *, void *);
extern unsigned char sndAuxCallbackPrepareReverbHI(SND_AUX_REVERBHI *);
extern unsigned char sndAuxCallbackPrepareChorus(SND_AUX_CHORUS *);
extern void sndAuxCallbackReverbHI(unsigned char, void *, void *);
extern void sndAuxCallbackChorus(unsigned char, void *, void *);
extern void sndSetAuxProcessingCallbacks(unsigned char, void (*)(unsigned char, void *, void *), void *, unsigned char, unsigned int, void (*)(unsigned char, void *, void *), void *, unsigned char, unsigned int);
extern void sndVolume(unsigned char, unsigned short, unsigned char);
#endif
