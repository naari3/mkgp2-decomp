/* Automatic cleanup uses the canonical cross-TU ScopedTimer destructor.
 * TU-scoped metadata names the automatic cleanup records at their target addresses. */
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
int KartDriver_Render(void *driver, int mode, int context);
extern const float lbl_806D25E0;
}

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

extern "C" void KartDriver_RenderTimed(void *driver, int mode, int context)
{
    ScopedTimer timer(23);
    KartDriver_Render(driver, mode, context);
}
#pragma cplusplus off
