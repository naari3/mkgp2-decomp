/* Phase 2d supplementary: boundary of the one-expression rule. */
extern unsigned long OSGetTick(void);
extern void Profiler_RecordFrame(unsigned int id, float ms);
extern void Body(void *self, void *arg);
extern const float kDiv;

typedef struct Tm {
    unsigned int start;
    volatile unsigned int id;
} Tm;

/* r0: endTick temp before the one-expression tail (still no us temp). */
void r0_endtick_temp(void *self, void *arg)
{
    Tm tm;
    unsigned int end;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    end = OSGetTick();
    Profiler_RecordFrame(
        tm.id,
        (float)(((end - tm.start) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) /
            kDiv);
}

/* r1: canonical out-of-line dtor shape (this-based member loads). */
typedef struct ST {
    unsigned int start; /* 0x0 */
    unsigned int id;    /* 0x4 */
} ST;
void r1_dtor_shape(ST *self)
{
    Profiler_RecordFrame(
        self->id,
        (float)(((OSGetTick() - self->start) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) /
            kDiv);
}

/* r2: diff temp (numerator) then one-expression remainder. */
void r2_diff_temp(void *self, void *arg)
{
    Tm tm;
    unsigned int diff;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    diff = OSGetTick() - tm.start;
    Profiler_RecordFrame(
        tm.id,
        (float)((diff * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) /
            kDiv);
}

/* r3: us temp but declared as float-consumed immediately via comma-free
 * double conversion (us temp reproduces miss? control). */
void r3_us_temp_ctrl(void *self, void *arg)
{
    Tm tm;
    unsigned int us;

    tm.id = 0x28;
    tm.start = OSGetTick();
    Body(self, arg);
    us = ((OSGetTick() - tm.start) * 8) /
         ((*(unsigned int *)0x800000F8 / 4) / 125000);
    Profiler_RecordFrame(tm.id, (float)us / kDiv);
}
