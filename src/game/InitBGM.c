/*
 * InitBGM @ 0x801B833C (size 0x5C).
 *
 * Idempotent BGM initializer. Returns 0 if already initialized; otherwise
 * runs sound subsystem init + plays BGM stream 1 at the current volume,
 * sets the gate flag (lbl_806D17F4) and returns 1.
 *
 * Singleton dtk reversed-extab group `auto_InitBGM_text` — the function has
 * an extab/extabindex entry (Large-Frame flag). #pragma exceptions on/reset
 * wraps the function so CW auto-emits the extab/extabindex entry (same
 * pattern as GetCourseSectionType.c / AI_GetYaw.c).
 */

extern unsigned char lbl_806D17F4;
extern void fn_801908F0(void);
extern void ClSound_PlayBgmStream(int stream, int flag);
extern unsigned char fn_801932F8(void);
extern void clStream_setVolume(int stream, unsigned char vol);

#pragma exceptions on
int InitBGM(void) {
    if (lbl_806D17F4 != 0) {
        return 0;
    }
    fn_801908F0();
    ClSound_PlayBgmStream(1, 0);
    clStream_setVolume(1, fn_801932F8());
    lbl_806D17F4 = 1;
    return 1;
}
#pragma exceptions reset
