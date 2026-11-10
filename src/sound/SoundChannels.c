/*
 * SoundChannels @ 0x8003AD4C.
 *
 * Single function in this TU: SoundChannels_ClearAll (size 0xB0).
 * No extab / extabindex (singleton bundle, extab_group_size=1).
 *
 * Iterates the 40-entry global ClRomTable at .bss:0x80598678 and nulls the
 * `path` slot of each entry. Target asm is fully unrolled -- 40 stw at
 * offsets 0x4 + n*8 from r3 (base loaded via lis/subi, NOT sda21, so the
 * symbol must live outside the sda window). Source mirrors that shape:
 * a struct with stride 8 where `.path` sits at +0x4 and 40 explicit
 * assignments.
 *
 * Underlying struct beyond `.path` is unknown; declared as a single u32
 * pad at +0x00 just to fix the 8-byte stride.
 */

#include "game/types/ClRomEntry.h"

extern struct ClRomEntry g_clRomTable[40];

void SoundChannels_ClearAll(void) {
    g_clRomTable[0].path = (void *)0;
    g_clRomTable[1].path = (void *)0;
    g_clRomTable[2].path = (void *)0;
    g_clRomTable[3].path = (void *)0;
    g_clRomTable[4].path = (void *)0;
    g_clRomTable[5].path = (void *)0;
    g_clRomTable[6].path = (void *)0;
    g_clRomTable[7].path = (void *)0;
    g_clRomTable[8].path = (void *)0;
    g_clRomTable[9].path = (void *)0;
    g_clRomTable[10].path = (void *)0;
    g_clRomTable[11].path = (void *)0;
    g_clRomTable[12].path = (void *)0;
    g_clRomTable[13].path = (void *)0;
    g_clRomTable[14].path = (void *)0;
    g_clRomTable[15].path = (void *)0;
    g_clRomTable[16].path = (void *)0;
    g_clRomTable[17].path = (void *)0;
    g_clRomTable[18].path = (void *)0;
    g_clRomTable[19].path = (void *)0;
    g_clRomTable[20].path = (void *)0;
    g_clRomTable[21].path = (void *)0;
    g_clRomTable[22].path = (void *)0;
    g_clRomTable[23].path = (void *)0;
    g_clRomTable[24].path = (void *)0;
    g_clRomTable[25].path = (void *)0;
    g_clRomTable[26].path = (void *)0;
    g_clRomTable[27].path = (void *)0;
    g_clRomTable[28].path = (void *)0;
    g_clRomTable[29].path = (void *)0;
    g_clRomTable[30].path = (void *)0;
    g_clRomTable[31].path = (void *)0;
    g_clRomTable[32].path = (void *)0;
    g_clRomTable[33].path = (void *)0;
    g_clRomTable[34].path = (void *)0;
    g_clRomTable[35].path = (void *)0;
    g_clRomTable[36].path = (void *)0;
    g_clRomTable[37].path = (void *)0;
    g_clRomTable[38].path = (void *)0;
    g_clRomTable[39].path = (void *)0;
}
