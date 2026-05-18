/*
 * HUD_SetCurrentLap @ 0x80253F84 (size 0x54).
 *
 * Sibling of HUD_SetTotalLaps (0x80253F34) and LapDisp_SetCurrentLap
 * (0x8023FAEC). Caches the lap number into `hud->currentLap` (offset 0x6c),
 * then -- if `hud->lapDispBase` (offset 0x1c) is non-null -- performs a
 * `__dynamic_cast`-style lookup via fn_80271340 against the LapDisp /
 * CDispInterface RTTI pair (s_clLapDisp / s_clCDispInterface in sdata) and
 * forwards to LapDisp_SetCurrentLap on the recovered subobject.
 *
 * extab/extabindex entries are present in the target (Large Frame: Yes
 * flag, 0x8 / 0xC bytes). Emitted via #pragma exceptions on/reset so CW
 * auto-generates them -- same pattern as LapDisp_SetTotalLaps.
 */

extern int fn_80271340(int obj, int offset, void *srcType, void *dstType, short throw_on_fail);
extern void LapDisp_SetCurrentLap(int lapDisp, int currentLap);
extern void *s_clLapDisp;
extern void *s_clCDispInterface;

#pragma exceptions on
void HUD_SetCurrentLap(int hud, int currentLap) {
    unsigned int disp;
    *(int *)(hud + 0x6c) = currentLap;
    disp = *(unsigned int *)(hud + 0x1c);
    if (disp != 0) {
        disp = fn_80271340((int)disp, 0, &s_clLapDisp, &s_clCDispInterface, 0);
        LapDisp_SetCurrentLap((int)disp, currentLap);
    }
}
#pragma exceptions reset
