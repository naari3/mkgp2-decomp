/* main @ 0x800AC894 (size 0x68)
 *
 * Top-level game lifecycle wrapper (a.k.a. RunGameMain). Called from
 * FUN_80003154 (program init).
 *
 * Flow:
 *   1. BootDispatcher(bootScratch)          -- boot 4 段階; bootScratch[0] = test_mode flag
 *   2. fn_8002FF30()                        -- post-boot 中間処理
 *   3. fn_8002CB80(&lbl_80328C94, mode)     -- main scene allocation
 *                                              mode default 3; if test mode -> 12
 *   4. MainGameLoop()                       -- per-frame game loop
 *   5. fn_8002C554(scene, 1)                -- scene shutdown
 *   6. fn_8002DC7C()                        -- 後始末
 *
 * extab/extabindex (auto-emitted by CW with #pragma exceptions on):
 *   extab      @ 0x8000A150 size 0x8
 *   extabindex @ 0x800227E4 size 0xC  -> { main, 0x68, @etb_8000A150 }
 *
 * Match notes:
 *   - bootScratch is 16 bytes, NOT 20. Ghidra plate "local_18[20]" includes the
 *     r31 spill slot at +0x1C. Real layout: r1+0x8..0x17 = 16-byte buf,
 *     r1+0x1C = r31 spill. Picking [20] forces CW 1.3.2 to round up to 32
 *     (16-byte multiple) and yields frame -0x30 instead of target's -0x20.
 *   - mode must be written with default-then-override (mode=3; if (...) mode=12;)
 *     rather than ternary, so CW emits r3 (lbl) load AFTER the cmp/branch.
 */

extern void BootDispatcher(void *scratch);
extern void fn_8002FF30(void);
extern void *fn_8002CB80(void *p, int mode);
extern void MainGameLoop(void);
extern void fn_8002C554(void *scene, int flag);
extern void fn_8002DC7C(void);

extern void *lbl_80328C94[];

#pragma exceptions on
void main(void) {
    unsigned char bootScratch[16];
    void *scene;
    int mode;

    BootDispatcher(bootScratch);
    fn_8002FF30();
    mode = 3;
    if (bootScratch[0] == 1) {
        mode = 12;
    }
    scene = fn_8002CB80(lbl_80328C94, mode);
    MainGameLoop();
    fn_8002C554(scene, 1);
    fn_8002DC7C();
}
#pragma exceptions reset
