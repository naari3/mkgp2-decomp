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

struct ClRomEntry {
    unsigned int unk0; /* +0x00 */
    void *path;        /* +0x04 */
};

extern struct ClRomEntry lbl_80598678[40];

void SoundChannels_ClearAll(void) {
    lbl_80598678[0].path = (void *)0;
    lbl_80598678[1].path = (void *)0;
    lbl_80598678[2].path = (void *)0;
    lbl_80598678[3].path = (void *)0;
    lbl_80598678[4].path = (void *)0;
    lbl_80598678[5].path = (void *)0;
    lbl_80598678[6].path = (void *)0;
    lbl_80598678[7].path = (void *)0;
    lbl_80598678[8].path = (void *)0;
    lbl_80598678[9].path = (void *)0;
    lbl_80598678[10].path = (void *)0;
    lbl_80598678[11].path = (void *)0;
    lbl_80598678[12].path = (void *)0;
    lbl_80598678[13].path = (void *)0;
    lbl_80598678[14].path = (void *)0;
    lbl_80598678[15].path = (void *)0;
    lbl_80598678[16].path = (void *)0;
    lbl_80598678[17].path = (void *)0;
    lbl_80598678[18].path = (void *)0;
    lbl_80598678[19].path = (void *)0;
    lbl_80598678[20].path = (void *)0;
    lbl_80598678[21].path = (void *)0;
    lbl_80598678[22].path = (void *)0;
    lbl_80598678[23].path = (void *)0;
    lbl_80598678[24].path = (void *)0;
    lbl_80598678[25].path = (void *)0;
    lbl_80598678[26].path = (void *)0;
    lbl_80598678[27].path = (void *)0;
    lbl_80598678[28].path = (void *)0;
    lbl_80598678[29].path = (void *)0;
    lbl_80598678[30].path = (void *)0;
    lbl_80598678[31].path = (void *)0;
    lbl_80598678[32].path = (void *)0;
    lbl_80598678[33].path = (void *)0;
    lbl_80598678[34].path = (void *)0;
    lbl_80598678[35].path = (void *)0;
    lbl_80598678[36].path = (void *)0;
    lbl_80598678[37].path = (void *)0;
    lbl_80598678[38].path = (void *)0;
    lbl_80598678[39].path = (void *)0;
}
