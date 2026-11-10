#include "game/types/SoundEvent.h"
#include "game/types/ActiveStream.h"
extern unsigned char ClSound_Initialized;
extern SoundEvent lbl_80677F40[37];
extern ActiveStream ClSound_ActiveStreams[4];
extern void fn_80190D24(void);
extern unsigned char ClStream_IsActive(unsigned int);
extern void ClStream_UpdateAll(void);

static inline void UpdateSoundEvents(void) {
    SoundEvent *next;
    int i, j;

    i = 0;
    while (i < 37) {
        if (lbl_80677F40[i].id == 0xffffffff) break;
        if (lbl_80677F40[i].state == 1) {
            if (lbl_80677F40[i].countdown != 0) lbl_80677F40[i].countdown--;
            else lbl_80677F40[i].state = 2;
        }
        if (lbl_80677F40[i].state == 3) {
            if (lbl_80677F40[i].countdown != 0) lbl_80677F40[i].countdown--;
            else {
                for (j = i; j < 36; j++) {
                    next = &lbl_80677F40[j + 1];
                    lbl_80677F40[j].id = next->id;
                    lbl_80677F40[j].state = next->state;
                    lbl_80677F40[j].countdown = next->countdown;
                }
                continue;
            }
        }
        i++;
    }
}

static inline void UpdateActiveStreams(void) {
    int k;

    for (k = 0; k < 4; k++) {
        if (ClSound_ActiveStreams[k].handle != 0xffffffff && !ClStream_IsActive(ClSound_ActiveStreams[k].handle))
            ClSound_ActiveStreams[k].handle = 0xffffffff;
    }
}

void fn_80193624(void) {
    if (ClSound_Initialized) {
        UpdateSoundEvents();
        fn_80190D24();
        UpdateActiveStreams();
        ClStream_UpdateAll();
    }
}
