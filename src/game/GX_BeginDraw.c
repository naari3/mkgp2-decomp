/*
 * GX_BeginDraw @ 0x801F7B98 (size 0x80).
 *
 * Singleton TU (extab_group=None per orchestrator, but eg=1: has its own
 * extab/extabindex entry -- emit via #pragma exceptions on / reset).
 *
 * Linear render-state setup: invokes seven Dolphin GX-ish helpers with
 * immediate args, then forwards 0xFFFFFFFF to the final teardown. All
 * callees take int args only, so CW emits a straight `li ; ... ; bl`
 * sequence with no spilling.
 *
 * lbl_806796FC: .bss object at 0x806796FC (size 0x4C). Loaded as
 * `lis r3, lbl@ha ; addi r3, r3, lbl@l` (non-sda, ha-pair). The
 * disassembler renders the negative @l as `subi r3, r3, 0x6904`.
 */

extern void GXSetChanCtrl(int, int, int, int, int, int, int);
extern void GXSetAlphaCompare(int, int, int, int, int);
extern void GXSetZCompLoc(int);
extern void GXSetZMode(int, int, int);
extern void fn_801F6790(void *);
extern void fn_802C14B8(unsigned int);

extern char lbl_806796FC[];

#pragma exceptions on
void GX_BeginDraw(void) {
    GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZCompLoc(1);
    GXSetZMode(1, 3, 1);
    fn_801F6790(&lbl_806796FC);
    fn_802C14B8(0xFFFFFFFF);
}
#pragma exceptions reset
