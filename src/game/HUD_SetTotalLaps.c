/*
 * HUD_SetTotalLaps @ 0x80253F34 (size 0x50).
 *
 * Forwards `totalLaps` to the LapDisp display owned by the HUD. The LapDisp
 * pointer lives at HUD offset 0x1c; if it is non-null, the slot id is
 * resolved through fn_80271340 (the same generic interface resolver used by
 * HUD_SetRacePosition at 0x80253E68, which targets offset 0x20 / RnkDisp via
 * sda21 pointers 0x806D0A20 / 0x806D0A10) and the resulting display object
 * is passed to LapDisp_SetTotalLaps along with the original totalLaps value.
 *
 * Mirror of HUD_SetRacePosition with three differences:
 *   - HUD field offset 0x20 -> 0x1c
 *   - sda21 ptr s_clRnkDisp / s_clCDispInterface -> s_clLapDisp / s_clCDispInterface
 *     (lbl_806D0A20 / lbl_806D0A10 -> lbl_806D0A40 / lbl_806D0A30)
 *   - callee RnkDisp_SetPosition -> LapDisp_SetTotalLaps
 *
 * extab/extabindex entries are present in the target (Large Frame: Yes,
 * Saved GPR range: r31, 0x8/0xC bytes). Emitted via #pragma exceptions
 * on/reset so CW auto-generates them -- same pattern as
 * game/LapDisp_SetTotalLaps.c.
 */

typedef struct HUD {
    char pad_00[0x1c];
    unsigned int lapDispSlot;       // 0x1c: slot id used here (unsigned -> cmplwi)
    /* 0x20 rnkDispSlot used by HUD_SetRacePosition */
} HUD;

extern int s_clLapDisp[2];          // lbl_806D0A40 (sdata, 0x8)
extern int s_clCDispInterface[2];   // lbl_806D0A30 (sdata, 0x8)

extern void *fn_80271340(unsigned int slot, int zero1, void *cls, void *iface, int zero2);
extern void LapDisp_SetTotalLaps(void *disp, int totalLaps);

#pragma exceptions on
void HUD_SetTotalLaps(HUD *self, int totalLaps) {
    void *disp;
    if (self->lapDispSlot != 0) {
        disp = fn_80271340(self->lapDispSlot, 0, &s_clLapDisp, &s_clCDispInterface, 0);
        LapDisp_SetTotalLaps(disp, totalLaps);
    }
}
#pragma exceptions reset
