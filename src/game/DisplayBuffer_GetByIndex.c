/* DisplayBuffer_GetByIndex (0x801F6454, size 0x40)
 *
 * Returns &lbl_806795B8[idx * 3] (int-array stride 3 = 12 bytes).
 * If idx is out of range [0, 3], calls GetDisplayBufferIndex() to obtain
 * the current display buffer index.
 *
 * Has extab/extabindex (large-frame flag): emit via #pragma exceptions on/reset.
 */

extern int GetDisplayBufferIndex(void);
extern int lbl_806795B8[];

#pragma exceptions on
int *DisplayBuffer_GetByIndex(int idx) {
    if (idx < 0 || idx > 3) {
        idx = GetDisplayBufferIndex();
    }
    return &lbl_806795B8[idx * 3];
}
#pragma exceptions reset
