/* Observed link-slot storage only; no foreign data is owned by this TU. */
typedef struct PcbConnection { unsigned char pad0[0xC]; int state; } PcbConnection;
typedef union PcbLinkFlags {
    struct {
        unsigned char local:1, reserved6:1, polled:1, receiving:1;
        unsigned char reserved3:1, dirty:1, reserved0:2;
        unsigned char reserved7:1, low:7;
    } byte;
    struct { unsigned short upper:6, id:3, lower:7; } half;
} PcbLinkFlags;
typedef struct PcbLinkSlot {
    unsigned char header[0x2C];
    unsigned char samples[64][0x28];
    PcbConnection* primary;
    PcbConnection* secondary;
    PcbLinkFlags flags;
    short timeout;
    signed char readIndex, writeIndex;
    unsigned char padA3A[2];
} PcbLinkSlot;
extern PcbLinkSlot lbl_805A6154[];
extern PcbConnection* lbl_805A6134[];
extern unsigned char g_pcbCommEnabled, lbl_806D1191, g_pcbSyncReady, lbl_806D1193;
extern int g_localPcbRole, g_myPcbId;
extern void* g_pcbListener;
extern unsigned char TCPConn_Poll(PcbConnection*, unsigned char);
extern void TCPConn_Close(PcbConnection*);
extern int TCPConn_Reset(PcbConnection*);
extern void TCPConn_Init(PcbConnection*, int, int, int);
extern int PCBCheck_StateSet(void*);
extern void* memset(void*, int, unsigned long);

static inline void PCBCheck_ClearSlotData(PcbLinkSlot* slot, int index)
{
    unsigned char* sample;
    int j;
    if (index >= 0 && index < 4) {
        if (slot->flags.byte.local == 1) {
            slot->readIndex = 0;
            slot->writeIndex = 2;
        } else {
            slot->readIndex = 0;
            slot->writeIndex = 1;
        }
        memset(slot, 0, 0x2C);
        sample = (unsigned char*)slot;
        for (j = 0; j < 64; ++j, sample += 0x28) {
            memset(sample + 0x2C, 0, 0x28);
        }
    }
}

static inline void PCBCheck_ResetAll(PcbLinkSlot* base)
{
    int index = 0;
    int count = 4;
    do {
        if (base->primary != 0) TCPConn_Close(base->primary);
        /* Preserve the shipped second close of primary, not secondary. */
        if (base->secondary != 0) TCPConn_Close(base->primary);
        base->primary = 0;
        base->secondary = 0;
        base->flags.byte.receiving = 0;
        base->flags.byte.polled = 0;
        base->timeout = 0;
        base->flags.byte.dirty = 1;
        PCBCheck_ClearSlotData(base, index);
        ++index;
        ++base;
    } while (--count != 0);
}

static inline void PCBCheck_ResetLinks(int requested)
{
    int count = 4;
    int index = 0;
    PcbLinkSlot* reset;
    if (requested != -1) { index = requested; count = 1; }
    reset = &lbl_805A6154[index];
    while (count != 0) {
        if (requested != -1) {
            TCPConn_Reset(reset->primary);
            if (reset->secondary != 0) TCPConn_Close(reset->secondary);
            reset->secondary = 0;
        } else {
            if (reset->primary != 0) TCPConn_Close(reset->primary);
            if (reset->secondary != 0) TCPConn_Close(reset->primary);
            reset->primary = 0;
            reset->secondary = 0;
        }
        reset->flags.byte.receiving = 0;
        reset->flags.byte.polled = 0;
        reset->timeout = 0;
        reset->flags.byte.dirty = 1;
        PCBCheck_ClearSlotData(reset, index);
        ++reset;
        ++index;
        --count;
    }
    PCBCheck_StateSet(g_pcbListener);
}

int PCBCheck_ProcessLinks(void)
{
    int candidate = -1;
    PcbLinkSlot* base;
    PcbLinkSlot* slot;
    int i;
    if (g_pcbCommEnabled == 0) return 0;
    base = lbl_805A6154;
    slot = base;
    for (i = 0; i < 4; ++i, ++slot) {
        unsigned char recover = 0;
        if (slot->primary != 0) {
            if (TCPConn_Poll(slot->primary, 1) == 1) slot->flags.byte.polled = 1;
            else slot->flags.byte.polled = 0;
            if (slot->primary->state == 0) recover = 1;
        }
        if (slot->secondary != 0) {
            if (TCPConn_Poll(slot->secondary, 1) == 1) slot->flags.byte.receiving = 1;
            else slot->flags.byte.receiving = 0;
            if (slot->secondary->state == 0) recover = 1;
            slot->timeout = 0;
        } else {
            if (slot->primary != 0 && slot->primary->state == 6) {
                if (++slot->timeout > 180) recover = 1;
            } else slot->timeout = 0;
        }
        if (recover == 1) {
            if (g_localPcbRole != 0 && ((slot->header[0] >> 4) & 7) == g_localPcbRole) {
                PCBCheck_ResetAll(base);
                PCBCheck_StateSet(g_pcbListener);
                lbl_806D1191 = 1;
                g_pcbSyncReady = 0;
                return 1;
            } else {
                PCBCheck_ResetLinks(i);
                if (lbl_806D1193 != 0 && i >= 0 && i < 4) {
                    int id = i + 1;
                    slot->flags.half.id = id;
                    slot->flags.byte.polled = 0;
                    slot->flags.byte.receiving = 0;
                    slot->timeout = 0;
                    slot->flags.byte.low = 0;
                    slot->flags.byte.reserved3 = 0;
                    slot->flags.byte.dirty = 1;
                    if (slot->flags.half.id == g_myPcbId) {
                        slot->flags.byte.local = 1;
                        slot->primary = 0;
                        slot->secondary = 0;
                    } else {
                        slot->flags.byte.local = 0;
                        slot->primary = lbl_805A6134[id - 1];
                        slot->secondary = 0;
                        TCPConn_Close(slot->primary);
                        TCPConn_Init(slot->primary, i + 1, -1, 0);
                    }
                    PCBCheck_ClearSlotData(slot, i);
                }
            }
        }
        if (candidate == -1 && slot->flags.byte.polled == 1 && slot->flags.byte.receiving == 1) candidate = i;
    }
    if (candidate == -1 || g_myPcbId - 1 < candidate) g_pcbSyncReady = 1;
    else g_pcbSyncReady = 0;
    return 1;
}
