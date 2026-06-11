/* ScopedTimer inline-dtor subi/lwz scheduler pair probe (Phase 2d).
 * Target block (113 sites program-wide, e.g. CarObject_FrameUpdate 0x8004DF68):
 *   bl OSGetTick
 *   lis r5, 0x8000
 *   lis r4, 0x431c
 *   lwz r5, 0xf8(r5)
 *   lis r0, 0x4330
 *   subi r6, r4, 0x217d     <- subi FIRST
 *   lwz r7, 0x8(r1)         <- start reload SECOND
 *   srwi r4, r5, 2
 *   stw r0, 0x10(r1)
 *   mulhwu r0, r6, r4
 *   ...
 * CW 1.3.2 emits lwz before subi for direct spellings (= the hand-written
 * timing site 0x8008C468 order). Hypothesis: inliner-spliced dtor body
 * (static inline helper) escapes that schedule, as with mr-SR-init (Phase 2c).
 */

extern unsigned long OSGetTick(void);
extern void Profiler_RecordFrame(unsigned int id, float ms);
extern void Body(void *self, void *arg);
extern const float kDiv;

typedef struct Tm {
    unsigned int start;       /* sp+0x8 */
    volatile unsigned int id; /* sp+0xc */
} Tm;

/* p0: baseline direct one-expression (FrameUpdate 97% form). Expect miss. */
void p0_direct(void *self, void *arg)
{
    Tm tm;
    unsigned int us;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    us = ((OSGetTick() - tm.start) * 8) / ((*(unsigned int *)0x800000F8 / 4) / 125000);
    Profiler_RecordFrame(tm.id, (float)us / kDiv);
}

/* p1: dtor as static inline helper, struct pointer param. */
static inline void TimerEnd_p(Tm *t)
{
    unsigned int us;
    us = ((OSGetTick() - t->start) * 8) / ((*(unsigned int *)0x800000F8 / 4) / 125000);
    Profiler_RecordFrame(t->id, (float)us / kDiv);
}
void p1_helper_ptr(void *self, void *arg)
{
    Tm tm;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    TimerEnd_p(&tm);
}

/* p2: helper takes start/id by value. */
static inline void TimerEnd_v(unsigned int start, unsigned int id)
{
    unsigned int us;
    us = ((OSGetTick() - start) * 8) / ((*(unsigned int *)0x800000F8 / 4) / 125000);
    Profiler_RecordFrame(id, (float)us / kDiv);
}
void p2_helper_val(void *self, void *arg)
{
    Tm tm;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    TimerEnd_v(tm.start, tm.id);
}

/* p3: helper with two-statement split (diff first, then us). */
static inline void TimerEnd_s(Tm *t)
{
    unsigned int diff;
    unsigned int us;
    diff = OSGetTick() - t->start;
    us = (diff * 8) / ((*(unsigned int *)0x800000F8 / 4) / 125000);
    Profiler_RecordFrame(t->id, (float)us / kDiv);
}
void p3_helper_split(void *self, void *arg)
{
    Tm tm;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    TimerEnd_s(&tm);
}

/* p4: helper with named denominator temp first. */
static inline void TimerEnd_d(Tm *t)
{
    unsigned int den;
    unsigned int us;
    den = (*(unsigned int *)0x800000F8 / 4) / 125000;
    us = ((OSGetTick() - t->start) * 8) / den;
    Profiler_RecordFrame(t->id, (float)us / kDiv);
}
void p4_helper_den(void *self, void *arg)
{
    Tm tm;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    TimerEnd_d(&tm);
}

/* p5: helper-in-helper (us computation nested one more level). */
static inline unsigned int ElapsedUs(unsigned int start)
{
    return ((OSGetTick() - start) * 8) / ((*(unsigned int *)0x800000F8 / 4) / 125000);
}
static inline void TimerEnd_n(Tm *t)
{
    Profiler_RecordFrame(t->id, (float)ElapsedUs(t->start) / kDiv);
}
void p5_helper_nest(void *self, void *arg)
{
    Tm tm;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    TimerEnd_n(&tm);
}

/* p6: ctor also as helper (full ScopedTimer simulation via helpers). */
static inline void TimerBegin(Tm *t, unsigned int id)
{
    t->id = id;
    t->start = OSGetTick();
}
void p6_helper_both(void *self, void *arg)
{
    Tm tm;

    TimerBegin(&tm, 0x28);
    Body(self, arg);
    TimerEnd_p(&tm);
}

/* p7: TRUE one-expression form in C (no us temp; whole conversion nested in
 * the call argument), volatile-id struct. */
void p7_oneexpr(void *self, void *arg)
{
    Tm tm;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    Profiler_RecordFrame(
        tm.id,
        (float)(((OSGetTick() - tm.start) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) /
            kDiv);
}

/* p8: one-expression but us temp only for the float conversion. */
void p8_oneexpr_f(void *self, void *arg)
{
    Tm tm;
    float ms;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    ms = (float)(((OSGetTick() - tm.start) * 8) /
                 ((*(unsigned int *)0x800000F8 / 4) / 125000)) /
         kDiv;
    Profiler_RecordFrame(tm.id, ms);
}
