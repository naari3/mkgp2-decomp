/*
 * ProcessSystemTick @ 0x8009D5F8 (size 0x40).
 *
 * Per-frame system tick: fan-out wrapper that drives the frame-begin/end
 * helpers, the sprite-handle GC pass, the global decrementing timer, and the
 * PCB communication subsystem in a fixed order.
 *
 * The TU sits in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the extab/extabindex entries (matching the
 * AI_GetYaw / Vtable_CallSlot2.cpp pattern).
 */

extern void fn_8002DC3C(void);
extern void SpriteHandlePool_GC(void);
extern void fn_8002DA3C(void);
extern void Timer_Decrement(void);
extern void PCBComm_Process(int a, int b);
extern void fn_8002D978(void);
extern void fn_8002D7DC(void);

#pragma exceptions on
void ProcessSystemTick(void) {
    fn_8002DC3C();
    SpriteHandlePool_GC();
    fn_8002DA3C();
    Timer_Decrement();
    PCBComm_Process(1, 1);
    fn_8002D978();
    fn_8002D7DC();
}
#pragma exceptions reset
