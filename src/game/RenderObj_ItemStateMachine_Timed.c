/* Automatic cleanup uses the canonical cross-TU ScopedTimer destructor.
 * TU-scoped metadata names the automatic cleanup records at their target addresses. */
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
int RenderObj_ItemStateMachine(void *obj, int arg, float a, float b);
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

extern "C" int RenderObj_ItemStateMachine_Timed(void *obj, int arg, float a, float b)
{
    ScopedTimer timer(22);
    return RenderObj_ItemStateMachine(obj, arg, a, b);
}
#pragma cplusplus off
