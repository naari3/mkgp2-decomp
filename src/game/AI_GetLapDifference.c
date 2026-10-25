/*
 * AI_KartController accessor: AI_GetLapDifference @ 0x801E6C94.
 *
 * Returns lap difference between this kart and race leader.
 * If the kart controller has no associated context (field 0x20 == NULL),
 * returns -1 (0xFFFFFFFF) as sentinel.
 *
 * Built with GC/2.6: reading the field through a const-qualified self lets
 * the scheduler hoist `lwz r3,0x20(r3)` above the `stw r0,0x14(r1)` LR save.
 */

extern unsigned int fn_801EC6CC(void *ctx);

#pragma exceptions on
unsigned int AI_GetLapDifference(const char *self) {
    void *ctx = *(void *const *)(self + 0x20);
    return ctx ? fn_801EC6CC(ctx) : (unsigned int)-1;
}
#pragma exceptions reset
