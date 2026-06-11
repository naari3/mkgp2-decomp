/* Phase 2d axis 2: real C++ ScopedTimer class with inline-defined dtor.
 * Hypothesis: the scope-end dtor expansion (compiler-driven inline splice)
 * schedules subi before lwz, unlike any hand-inlined C/C++ spelling.
 * Compile with -lang=c++ (and exceptions on/off variants).
 */

extern "C" {
extern unsigned long OSGetTick(void);
extern void Profiler_RecordFrame(unsigned int id, float ms);
extern void Body(void *self, void *arg);
extern const float kDiv;
}

class ScopedTimer {
public:
    ScopedTimer(unsigned int id)
    {
        m_id = id;
        m_start = OSGetTick();
    }
    ~ScopedTimer()
    {
        unsigned int us;
        us = ((OSGetTick() - m_start) * 8) / ((*(unsigned int *)0x800000F8 / 4) / 125000);
        Profiler_RecordFrame(m_id, (float)us / kDiv);
    }

private:
    unsigned int m_start;
    unsigned int m_id;
};

void q0_cpp_class(void *self, void *arg)
{
    ScopedTimer tm(0x28);
    Body(self, arg);
}

/* q1: one-expression dtor variant via a second class. */
class ScopedTimer1 {
public:
    ScopedTimer1(unsigned int id)
    {
        m_id = id;
        m_start = OSGetTick();
    }
    ~ScopedTimer1()
    {
        Profiler_RecordFrame(
            m_id,
            (float)(((OSGetTick() - m_start) * 8) /
                    ((*(unsigned int *)0x800000F8 / 4) / 125000)) /
                kDiv);
    }

private:
    unsigned int m_start;
    unsigned int m_id;
};

void q1_cpp_oneexpr(void *self, void *arg)
{
    ScopedTimer1 tm(0x28);
    Body(self, arg);
}
