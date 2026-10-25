extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
void KartController_Update(void *self);
extern const float lbl_806DA3C0;
}

class ScopedTimer {
public:
    ScopedTimer(int slot) { m_slot = slot; m_startTick = OSGetTick(); }
    ~ScopedTimer() {
        Profiler_RecordFrame(m_slot, (float)(((OSGetTick() - m_startTick) << 3) / ((*(volatile unsigned int *)0x800000F8 >> 2) / 125000)) / lbl_806DA3C0);
    }
private:
    unsigned int m_startTick;
    int m_slot;
};

extern "C" void KartController_TimedUpdate(void *self) {
    ScopedTimer timer(0x27);
    KartController_Update(self);
}
