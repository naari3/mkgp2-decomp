/* Observed byte/word overlays only; all storage remains externally owned. */
typedef struct {
    unsigned char unused7 : 1;
    unsigned char role : 3;
    unsigned char unusedLow : 4;
} RoleByte;
typedef struct {
    unsigned char unusedHigh : 5;
    unsigned char flag2 : 1;
    unsigned char flag1 : 1;
    unsigned char unused0 : 1;
} PhaseFlags;
typedef union {
    unsigned int word;
    struct { RoleByte role; unsigned char unused1; PhaseFlags flags; unsigned char unused3; } bytes;
} SlotHeader;
typedef struct { SlotHeader header; unsigned char remaining[0xA38]; } SlotView;
extern SlotView lbl_805A6154[4];
extern char g_pcbSyncPhasePerPcb[4];
extern unsigned char g_pcbSyncTable[0x1C];
extern float lbl_806D11C0[2];
extern const float lbl_806D3164;
extern const float lbl_806D316C;

#pragma exceptions on
static inline void PublishTimers(int roleCount, unsigned char truncate,
                                 unsigned char reset, char *phases)
{
    unsigned char idle = 1;
    if (roleCount > 0) {
        float timer;
        char *cursor = phases;
        unsigned char *out = g_pcbSyncTable;
        int i;
        lbl_806D11C0[0] -= lbl_806D3164;
        if (truncate) lbl_806D11C0[0] = (int)lbl_806D11C0[0];
        if (reset) lbl_806D11C0[0] = lbl_806D316C;
        timer = lbl_806D11C0[0];
        for (i = 0; i < 4; ++i, ++cursor, out += 4) {
            if (*cursor == 1) {
                *(float *)(out + 8) = timer;
                idle = 0;
            }
        }
    }
    if (idle) lbl_806D11C0[0] = lbl_806D316C;
}
int PCBComm_UpdateSyncPhase1(void)
{
    SlotView *slots = lbl_805A6154;
    SlotView *slot = slots;
    char *phases = g_pcbSyncPhasePerPcb;
    char *phase = phases;
    int roleCount = 0;
    int sceneCount = 0;
    int first = -1;
    unsigned char truncate = 0;
    unsigned char reset = 0;
    int i;
    for (i = 0; i < 4;) {
        unsigned int role;
        if (((slot->header.word >> 15) & 0xFF) == 8) ++sceneCount;
        role = slot->header.bytes.role.role;
        if (role == 1) {
            if (first == -1) first = i;
            *phase = 1;
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
            if (slot->header.bytes.flags.flag1 == 1 && role == 0) {
                slot->header.bytes.flags.flag1 = 0;
                reset = 1;
            }
            if (((slot->header.word >> 15) & 0xFF) == 6) *phase = 1;
        }
        ++slot;
        ++phase;
        ++i;
    }
    if (sceneCount > 0 && roleCount == sceneCount) {
        int hostRole = first + 2;
        unsigned char *out = g_pcbSyncTable;
        for (i = 0; i < 4; ++i, ++slots, ++out) {
            if (roleCount >= 2) {
                if (slots->header.bytes.role.role == 1) out[4] = hostRole;
            } else {
                if (slots->header.bytes.role.role == 1) out[4] = 0;
            }
        }
    }
    PublishTimers(roleCount, truncate, reset, phases);
    return 1;
}
#pragma exceptions reset
