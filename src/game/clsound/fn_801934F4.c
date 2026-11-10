/* --- owned .rodata 0x8037D058..0x8037D178 (tools/own_data.py) --- */
#pragma force_active on
const char lbl_8037D058[288] = { 73, 68, 58, 37, 48, 51, 100, 40, 37, 100, 41, 0, 42, 42, 42, 42, 42, 42, 42, 42, 32, 73, 110, 105, 116, 105, 97, 108, 105, 122, 101, 32, 83, 111, 117, 110, 100, 83, 121, 115, 116, 101, 109, 32, 42, 42, 42, 42, 42, 42, 42, 42, 10, 0, 0, 0, 66, 97, 115, 101, 32, 65, 82, 65, 77, 65, 100, 100, 114, 101, 115, 115, 32, 58, 32, 48, 120, 37, 88, 10, 0, 0, 0, 0, 115, 111, 117, 110, 100, 100, 97, 116, 97, 46, 112, 111, 111, 108, 0, 0, 69, 82, 82, 79, 82, 58, 32, 85, 110, 97, 98, 108, 101, 32, 116, 111, 32, 111, 112, 101, 110, 32, 39, 37, 115, 39, 10, 0, 69, 82, 82, 79, 82, 58, 32, 90, 101, 114, 111, 32, 108, 101, 110, 103, 116, 104, 32, 102, 105, 108, 101, 32, 39, 37, 115, 39, 10, 0, 0, 0, 69, 82, 82, 79, 82, 58, 32, 85, 110, 97, 98, 108, 101, 32, 116, 111, 32, 97, 108, 108, 111, 99, 97, 116, 101, 32, 98, 117, 102, 102, 101, 114, 10, 0, 0, 0, 69, 82, 82, 79, 82, 58, 32, 70, 97, 105, 108, 101, 100, 32, 116, 111, 32, 114, 101, 97, 100, 32, 100, 97, 116, 97, 32, 102, 114, 111, 109, 32, 39, 37, 115, 39, 10, 0, 0, 0, 115, 111, 117, 110, 100, 100, 97, 116, 97, 46, 112, 114, 111, 106, 0, 0, 115, 111, 117, 110, 100, 100, 97, 116, 97, 46, 115, 100, 105, 114, 0, 0, 115, 111, 117, 110, 100, 100, 97, 116, 97, 46, 115, 97, 109, 112, 0, 0, 0, 0, 0, 0 };
#pragma force_active reset
#pragma opt_dead_assignments off
#include "game/types/SoundEvent.h"
extern unsigned char ClSound_Initialized;
extern SoundEvent ClSound_InitSoundSystem_bss_80677F40[37];
extern int sprintf(char *, const char *, ...);
extern void DeadCounter_Set_ced48(int);
extern void OverlayText(int, int, int, const char *, ...);
static inline void DrawSoundEvents(void) {
    SoundEvent *event;
    int row;
    int i;
    char text[64];
    row = 0;
    event = ClSound_InitSoundSystem_bss_80677F40;
    for (i = row; i < 37; i++, event++) {
        if (event->id == 0xffffffff) break;
        {
            unsigned int id = event->id & 0x87ffffff;
            sprintf(text, lbl_8037D058, id, (event->id >> 27) & 15);
        }
        switch (event->state) {
        case 1:
            DeadCounter_Set_ced48(4);
            OverlayText(1, 1, row + 2, text);
            break;
        case 2:
            DeadCounter_Set_ced48(7);
            OverlayText(1, 1, row + 2, text);
            break;
        default:
            DeadCounter_Set_ced48(0);
            OverlayText(1, 1, row + 2, text);
            break;
        }
        row++;
        if (row >= 29) break;
    }
    DeadCounter_Set_ced48(7);
}

void fn_801934F4(void) {
    if (ClSound_Initialized) DrawSoundEvents();
}
