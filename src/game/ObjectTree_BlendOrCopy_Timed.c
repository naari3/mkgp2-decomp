/* Timed blend/copy and the inlined HSD JObj matrix-dirty guard.
 * Automatic EH references the canonical cross-TU ScopedTimer destructor;
 * the compiler's weak destructor copy is discarded by the linker. */
typedef struct JObjFlagsView {
    unsigned char reserved[0x14];
    unsigned int flags;
} JObjFlagsView;

#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
void ObjectTree_BlendOrCopy(void *object, void *source, void *destination,
                            JObjFlagsView *blend, float weight);
void fn_802D20AC(JObjFlagsView *jobj);
void __assert(const char *file, int line, const char *expression);
extern const char lbl_806D2348[7];
extern const char lbl_806D2350[5];
extern const float lbl_806D2360;
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
        /* Keep ticks-to-microseconds as a single expression tree. */
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D2360);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};

static inline unsigned char JObj_IsMatrixIndependent(JObjFlagsView *jobj)
{
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x25D, lbl_806D2350);
    }
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

static inline void JObj_RequestMatrixDirty(JObjFlagsView *jobj)
{
    if (jobj != 0) {
        if (!JObj_IsMatrixIndependent(jobj)) {
            fn_802D20AC(jobj);
        }
    }
}

extern "C" void ObjectTree_BlendOrCopy_Timed(void *object, void *source,
    void *destination, JObjFlagsView *blend, float weight)
{
    ScopedTimer timer(9);
    ObjectTree_BlendOrCopy(object, source, destination, blend, weight);
    if (blend != 0 && !(blend->flags & 0x02000000)) {
        JObj_RequestMatrixDirty(blend);
    }
}
#pragma cplusplus off
