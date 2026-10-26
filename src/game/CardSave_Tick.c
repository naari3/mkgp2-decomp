/* Card save state machine tick: runs the current step and returns its
 * result (0 when idle). */
extern int lbl_806D124C;
extern int CardSave_Tick_CaptureAndStart(void);
extern int CardSave_Tick_PollCleaningResult(void);

int CardSave_Tick(void)
{
    int ret = 0;

    if (lbl_806D124C == 0) {
        ret = CardSave_Tick_CaptureAndStart();
    } else if (lbl_806D124C == 1) {
        ret = CardSave_Tick_PollCleaningResult();
    }
    return ret;
}
