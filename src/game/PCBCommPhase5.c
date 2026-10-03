/* Only observed overlays; all global storage remains externally owned. */
typedef struct { unsigned char high : 1; unsigned char role : 3; unsigned char low : 4; } RoleByte;
typedef struct { unsigned char high : 5; unsigned char flag2 : 1; unsigned char flag1 : 1; unsigned char low : 1; } PhaseFlags;
typedef union {
    unsigned int word;
    struct { RoleByte role; unsigned char unused; PhaseFlags flags; unsigned char tail; } bytes;
} SlotHeader;
typedef struct { SlotHeader header; unsigned char remaining[0xA38]; } SlotView;
extern SlotView lbl_805A6154[4];
extern char g_pcbSyncPhasePerPcb[4];
extern unsigned char g_pcbSyncTable[0x1C];
extern float lbl_806D11C0[2];
/* Two adjacent timestamp words: high at 11C8, low at 11CC. */
extern long long lbl_806D11C8;
extern long long OSGetTime(void);
extern long long fn_80271884(long long numerator, long long denominator);
extern const float lbl_806D3158, lbl_806D315C, lbl_806D3160;
extern const float lbl_806D3164, lbl_806D3168;

#pragma exceptions on
static inline unsigned char PublishValue(float timer, char *phases)
{
    unsigned char idle = 1;
    char *cursor = phases;
    unsigned char *out = g_pcbSyncTable;
    int i;
    for (i = 0; i < 4; ++i, ++cursor, out += 4) {
        if (*cursor == 5) {
            *(float *)(out + 8) = timer;
            idle = 0;
        }
    }
    return idle;
}
static inline void PublishTimers(int roleCount, unsigned char truncate,
                                 unsigned char reset, char *phases)
{
    unsigned char idle = 1;
    if (roleCount > 0) {
        float timer;
        lbl_806D11C0[1] -= lbl_806D3164;
        if (truncate) lbl_806D11C0[1] = (int)lbl_806D11C0[1];
        if (reset) lbl_806D11C0[1] = lbl_806D3168;
        timer = lbl_806D11C0[1];
        idle = PublishValue(timer, phases);
    }
    if (idle) lbl_806D11C0[1] = lbl_806D3168;
}
int PCBComm_UpdateSyncPhase5(void)
{
    char *phases;
    int roleCount = 0;
    int sceneCount = 0;
    int first = -1;
    unsigned char truncate = 0;
    unsigned char reset = 0;
    SlotView *slots;
    SlotView *slot;
    char *phase;
    int i;
    float elapsed = (float)fn_80271884(OSGetTime() - lbl_806D11C8,
        (long long)((*(volatile unsigned int *)0x800000F8 >> 2) / 1000));
    elapsed /= lbl_806D3158;
    if (elapsed <= lbl_806D315C) {
        lbl_806D11C0[1] = lbl_806D3160;
        return 1;
    }
    slots = lbl_805A6154;
    phases = g_pcbSyncPhasePerPcb;
    slot = slots;
    phase = phases;
    for (i = 0; i < 4;) {
        unsigned int role;
        if (((slot->header.word >> 15) & 0xFF) == 50) ++sceneCount;
        role = slot->header.bytes.role.role;
        if (role == 5) {
            if (first == -1) first = i;
            *phase = 5;
            ++roleCount;
            if (slot->header.bytes.flags.flag2 == 1) {
                slot->header.bytes.flags.flag2 = 0;
                truncate = 1;
            }
            if (slot->header.bytes.flags.flag1 == 1) {
                slot->header.bytes.flags.flag1 = 0;
                reset = 1;
            }
        } else {
            if (slot->header.bytes.flags.flag1 == 1 && role == 5) {
                slot->header.bytes.flags.flag1 = 0;
                reset = 1;
            }
            if (((slot->header.word >> 15) & 0xFF) == 48) *phase = 5;
        }
        ++slot;
        ++phase;
        ++i;
    }
    if (sceneCount > 0 && roleCount == sceneCount) {
        unsigned char *out = g_pcbSyncTable;
        int hostRole = first + 2;
        for (i = 0; i < 4; ++i, ++slots, ++out) {
            if (roleCount >= 2) {
                if (slots->header.bytes.role.role == 5) out[4] = hostRole;
            } else {
                if (slots->header.bytes.role.role == 5) out[4] = 0;
            }
        }
        lbl_806D11C8 = OSGetTime();
    }
    PublishTimers(roleCount, truncate, reset, phases);
    return 1;
}
#pragma exceptions reset
