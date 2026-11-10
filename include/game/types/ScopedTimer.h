#ifndef GAME_TYPES_SCOPEDTIMER_H
#define GAME_TYPES_SCOPEDTIMER_H

class ScopedTimer {
public:
    inline ScopedTimer(int slot)
    {
        m_slot = slot;
        m_startTick = OSGetTick();
    }

    inline ~ScopedTimer()
    {
        /* Keep the conversion in one expression to preserve scheduling. */
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D25E0);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};

#endif /* GAME_TYPES_SCOPEDTIMER_H */
