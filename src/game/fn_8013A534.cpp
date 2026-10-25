/*
 * 0x8013A534..0x8013A5BC: timed coin system update.
 */
#pragma cplusplus on

struct ModelPair {
    void **vt;
    void *a;
    void *b;
};

/* TOP-END */

extern "C" {
void CoinSystem_UpdateAll(void);
unsigned long OSGetTick(void);
void Profiler_RecordFrame(int id, float ms);
extern const float lbl_806D7404;
extern unsigned int lbl_806D7408;
extern void __dt__11ScopedTimerFv();
void fn_8013A534(void);

#pragma section R ".extab_user"

#pragma section R ".extabindex_user"

}

class ScopedTimer {
public:
    inline ScopedTimer(int slot) {
        m_slot = slot;
        m_startTick = OSGetTick();
    }
    inline ~ScopedTimer() {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D7404);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};




extern "C" void fn_8013A534(void)
{
    ScopedTimer t(0x25);
    CoinSystem_UpdateAll();
}

