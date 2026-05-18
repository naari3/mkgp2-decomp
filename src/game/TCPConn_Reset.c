/* TCPConn_Reset @ 0x80087170 (size 0x68)
 *
 * Marks a TCP connection as resetting and seeds the retry/timeout counter
 * based on whether the global game timer has expired.
 *
 * conn layout (offsets in bytes):
 *   +0x0C  state    (10 = closed/terminal; 1 = resetting)
 *   +0x38  retry    (0xF when timer still running, 0 when expired)
 *
 * Returns 1 on successful reset, 0 when the connection is already terminal.
 */

extern unsigned int IsGlobalTimerExpired(void);

#pragma exceptions on
int TCPConn_Reset(int conn) {
    int ret;
    unsigned char timerExpired;

    if (*(int *)(conn + 0xC) == 10) {
        ret = 0;
    } else {
        *(int *)(conn + 0xC) = 1;
        timerExpired = (unsigned char)IsGlobalTimerExpired();
        if (timerExpired) {
            *(int *)(conn + 0x38) = 0;
        } else {
            *(int *)(conn + 0x38) = 0xF;
        }
        ret = 1;
    }
    return ret;
}
#pragma exceptions reset
