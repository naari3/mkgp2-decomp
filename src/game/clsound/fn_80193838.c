#include "game/types/SndSlot.h"

#include "game/types/ClStreamSlot.h"

extern unsigned char ClSound_Initialized;
extern SndSlot ClSound_InitSoundSystem_bss_80678378[32];
extern ClStreamSlot ClSound_ActiveStreams[4];
extern int lbl_806CF010;
extern void *lbl_806D16B4;
extern void *lbl_806D16B8;
extern void *lbl_806D16BC;
extern void fn_8019522C(void);
extern void sndQuit(void);
extern void ARReset(void);
extern void AIReset(void);
extern void OSFreeToHeap(int heap, void *ptr);

void fn_80193838(void) {
    int i;
    if (ClSound_Initialized) {
        fn_8019522C();
        sndQuit();
        ARReset();
        AIReset();
        if (lbl_806D16B4) {
            OSFreeToHeap(lbl_806CF010, lbl_806D16B4);
        }
        if (lbl_806D16B8) {
            OSFreeToHeap(lbl_806CF010, lbl_806D16B8);
        }
        if (lbl_806D16BC) {
            OSFreeToHeap(lbl_806CF010, lbl_806D16BC);
        }
        lbl_806D16B4 = 0;
        lbl_806D16B8 = 0;
        lbl_806D16BC = 0;
        for (i = 0; i < 32; i++) {
            ClSound_InitSoundSystem_bss_80678378[i].id = -1;
            ClSound_InitSoundSystem_bss_80678378[i].group = 0xff;
            ClSound_InitSoundSystem_bss_80678378[i].x18 = 0xff;
            ClSound_InitSoundSystem_bss_80678378[i].flags = 0;
        }
        ClSound_Initialized = 0;
        for (i = 0; i < 4; i++) {
            ClSound_ActiveStreams[i].id = -1;
        }
    }
}
