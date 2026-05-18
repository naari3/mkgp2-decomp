/*
 * AI_KartController accessor: AI_GetYaw @ 0x801E6D30.
 *
 * Returns the kart's heading angle (yaw) reported by the AI subsystem.
 * If the kart controller has no associated context (field 0x20 == NULL),
 * returns the default constant `lbl_806DA388` (.sdata2 float).
 *
 * The TU sits in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the extab/extabindex entry (matching the
 * Vtable_CallSlot2.cpp pattern).
 */

extern double fn_801EC75C(void *ctx);
extern const float lbl_806DA388;

#pragma exceptions on
double AI_GetYaw(int self) {
    void *ctx = *(void **)(self + 0x20);
    if (ctx) {
        return fn_801EC75C(ctx);
    }
    return lbl_806DA388;
}
#pragma exceptions reset
