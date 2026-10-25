/* Per-frame DrawEffect pool tick: frustum-cull each live entry, advance its
 * VfxSlot animation and run its draw hook, timed into profiler slot 26.
 * Automatic cleanup uses the canonical cross-TU ScopedTimer destructor. */
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
signed char fn_80137718(void *sphere, float *viewPos, float radius);
void VfxSlot_TickAnim(void *slot, int visible);
extern const float lbl_806D4FD8; /* -1000.0 */
extern const float lbl_806D4FDC; /* 1000000.0 */
}

typedef void (*DrawEffectHook)(void *arg);

struct DrawEffectCull {
    signed char active;            /* 0x000 */
    unsigned char pad001[0x13];
    unsigned char slot[0x64];      /* 0x014 VfxSlot */
    DrawEffectHook hook;           /* 0x078 */
    void *hookArg;                 /* 0x07C */
    unsigned char pad080[0xB8 - 0x80];
    float sphere[3];               /* 0x0B8 */
    float radius;                  /* 0x0C4 */
    signed char visible;           /* 0x0C8 */
    unsigned char pad0c9[0x1CC - 0xC9];
};

extern "C" DrawEffectCull lbl_805DF468[0x200];

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
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D4FDC);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};

extern "C" void DrawEffect_TickAndCull(void)
{
    ScopedTimer timer(26);
    float view[3];
    int i;

    for (i = 0; i < 0x200; i++) {
        if (lbl_805DF468[i].active) {
            if (lbl_805DF468[i].slot[0] & 1) {
                lbl_805DF468[i].visible = 1;
            } else {
                lbl_805DF468[i].visible = fn_80137718(lbl_805DF468[i].sphere, view, lbl_805DF468[i].radius);
                if (lbl_805DF468[i].visible && view[2] < lbl_806D4FD8) {
                    lbl_805DF468[i].visible = 0;
                }
            }
            VfxSlot_TickAnim(lbl_805DF468[i].slot, lbl_805DF468[i].visible);
            if (lbl_805DF468[i].visible && lbl_805DF468[i].hook != 0) {
                if (lbl_805DF468[i].hookArg != 0) {
                    lbl_805DF468[i].hook(lbl_805DF468[i].hookArg);
                } else {
                    lbl_805DF468[i].hook(lbl_805DF468[i].slot);
                }
            }
        }
    }
}
#pragma cplusplus off
