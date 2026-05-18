/*
 * HUD_SetRacePosition @ 0x80253E68 (size 0x50, 21 instr).
 *
 * Forward the new race position to the RnkDisp owned by the HUD object at
 * offset 0x20 (a generic class-instance pointer). The fn_80271340 call
 * looks like a CDispInterface lookup factory: it takes the parent object,
 * an empty key (0), the two sdata vtable pointers (lbl_806D0A50 = clRnkDisp,
 * lbl_806D0A30 = clCDispInterface), and another null arg, and returns the
 * RnkDisp slot pointer in r3. That return is then passed to
 * RnkDisp_SetPosition along with the new position value (preserved in r31
 * across the first call).
 *
 * The two sdata labels are referenced via @sda21 (1-instr `li rD, lbl@sda21`)
 * so they must be declared as `extern char lbl_XXX[8]` to keep CW on the
 * SDA21 path (target sdata size = 0x8 each).
 */

extern char lbl_806D0A30[8];
extern char lbl_806D0A50[8];
extern void *fn_80271340(void *self, int a2, void *vtable1, void *vtable2, int a5);
extern void RnkDisp_SetPosition(void *disp, int newPosition);

#pragma exceptions on
void HUD_SetRacePosition(void *hud, int newPosition) {
    void *disp;
    if (*(void **)((char *)hud + 0x20) != 0) {
        disp = fn_80271340(*(void **)((char *)hud + 0x20), 0,
                           lbl_806D0A50, lbl_806D0A30, 0);
        RnkDisp_SetPosition(disp, newPosition);
    }
}
#pragma exceptions reset
