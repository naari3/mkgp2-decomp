/*
 * AI_KartController accessor: AI_GetLapDifference @ 0x801E6C94.
 *
 * Returns lap difference between this kart and race leader.
 * If the kart controller has no associated context (field 0x20 == NULL),
 * returns -1 (0xFFFFFFFF) as sentinel.
 *
 * The TU sits in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the extab/extabindex entry (matching the
 * Vtable_CallSlot2.cpp pattern).
 */

extern unsigned int fn_801EC6CC(void *ctx);

#pragma exceptions on
unsigned int AI_GetLapDifference(int self) {
    register void *ctx = *(void **)(self + 0x20);
    return ctx ? fn_801EC6CC(ctx) : (unsigned int)-1;
}
#pragma exceptions reset
