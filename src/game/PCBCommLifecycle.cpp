/* Observed PCB storage only. Allocation types are opaque external lifetimes. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

class LifecycleListener {
public:
    u8 bytes[0x40];
    LifecycleListener();
};
class LifecycleConn {
public:
    u8 bytes[0x60];
    LifecycleConn();
};
class PCBComm {
public:
    ~PCBComm();
};
struct RoleByte { u8 high:1; u8 role:3; u8 low:4; };
union PacketHead {
    u32 word;
    struct { RoleByte role; u8 remaining[3]; } bytes;
};
union SlotFlags {
    u16 half;
    struct {
        u8 local:1; u8 idHigh:1; u8 tx:1; u8 rx:1;
        u8 card:1; u8 ack:1; u8 low:2;
        u8 idLow:1; u8 blocks:7;
    } bits;
};
struct Slot {
    PacketHead header;
    u8 payload[0xA28];
    LifecycleConn *send;
    LifecycleConn *recv;
    SlotFlags flags;
    short count;
    signed char read;
    signed char write;
    u8 tail[2];
};
struct Sync {
    u8 scenes[4];
    u8 roles[4];
    float timers[4];
    u8 ready;
    u8 tail[3];
};
struct Storage {
    u8 prefix[0x258];
    Sync sync;
    LifecycleConn *outgoing[4];
    LifecycleConn *incoming[4];
    Slot slots[4];
    u8 cards[4][0x45];
    u8 ring[64][0xDC];
    u8 hostSnapshots[2][0x1C];
};
extern "C" {
extern Storage lbl_805A5EC0;
extern u8 lbl_80598A60[0x2A];
extern u8 g_pcbCommEnabled, lbl_806D1191, g_pcbSyncReady;
extern u8 lbl_806CEFC8, lbl_806D1193, g_confirmFlag, lbl_806D11AC;
extern u8 g_isCommHost;
extern int g_gameMode, g_myPcbId, g_ringReadIdx, lbl_806D11A0;
extern u32 lbl_806D1188, lbl_806D11A4, lbl_806D11A8;
extern void *lbl_806D11B0;
extern LifecycleListener *g_pcbListener;
extern float lbl_806D11C0[2];
extern long long lbl_806D11C8;
extern signed char g_pcbSyncPhasePerPcb[4];
extern const float lbl_806D3168, lbl_806D316C, lbl_806D3198;
u32 OSGetTick(void);
long long OSGetTime(void);
void Profiler_RecordFrame(int, float);
u8 TCPListen_Poll(LifecycleListener *, u8);
u32 PcbIdToIp_GetCached(int);
void TCPConn_Close(LifecycleConn *);
void TCPConn_Init(LifecycleConn *, int, int, u32);
int PcbListener_TakeAcceptedSocket(LifecycleListener *);
int PcbConn_RecycleIfOver(LifecycleConn *);
int PCBCheck_StateSet(LifecycleListener *);
int PCBCheck_ProcessLinks(void);
int PCBComm_UpdateSyncPhase1(void);
int PCBComm_UpdateSyncPhase5(void);
int PCBComm_ComputeSyncState(void);
int PCBComm_SendToAllPeers(void);
int PCBCheck_RecvLinkData(u8);
LifecycleConn *PcbConn_Close(LifecycleConn *, short);
LifecycleListener *PcbListener_Dtor(LifecycleListener *, short);
void *memset(void *, int, unsigned long);
void *memcpy(void *, const void *, unsigned long);
}
class ScopedTimer {
    u32 start;
    volatile int slot;
public:
    inline ScopedTimer(int value) { slot = value; start = OSGetTick(); }
    inline ~ScopedTimer() {
        Profiler_RecordFrame(slot,
            (float)(((OSGetTick() - start) * 8) /
                ((*(u32 *)0x800000F8 / 4) / 125000)) / lbl_806D3198);
    }
};

static inline int SlotId(Slot *slot) { return (slot->flags.half >> 7) & 7; }
static inline LifecycleConn **Outgoing(Storage *storage) { return storage->outgoing; }
static inline void SetSlotId(Slot *slot, int id) {
    slot->flags.half = (slot->flags.half & ~0x380) | ((id << 7) & 0x380);
}
static inline void ResetScratch(Slot *slot, int index) {
    if (index >= 0 && index < 4) {
        if (slot->flags.bits.local == 1) { slot->read = 0; slot->write = 2; }
        else { slot->read = 0; slot->write = 1; }
        memset(slot, 0, 0x2C);
        int i;
        u8 *cursor = (u8 *)slot;
        for (i = 0; i < 64; ++i, cursor += 0x28) memset(cursor + 0x2C, 0, 0x28);
    }
}

extern "C" int PCBComm_Process(u8 receive, u8 send)
{
    Storage *storage = &lbl_805A5EC0;
    if (g_pcbCommEnabled == 0) return 0;
    if (lbl_806D1191 == 1) return 0;
    u8 update = 0;
    u32 tick = OSGetTick();
    if (g_gameMode == 2 ||
        (tick - lbl_806D1188) / ((*(u32 *)0x800000F8 / 4) / 1000) >= 15) {
        update = 1;
        lbl_806D1188 = tick;
    }
    ScopedTimer timer(38);
    if (update) {
        u8 accepted = 0;
        if (g_pcbCommEnabled != 0 && g_pcbListener != 0 &&
            TCPListen_Poll(g_pcbListener, 0) == 1) {
            Slot *slots = storage->slots;
            Slot *slot = slots;
            int i;
            u32 address = *(u32 *)(g_pcbListener->bytes + 0x34);
            for (i = 0; i < 4; ++i, ++slot) {
                if (slot->flags.bits.local != 1 && address == PcbIdToIp_GetCached(SlotId(slot))) {
                    Slot *selected = &storage->slots[i];
                    if (selected->recv != 0) TCPConn_Close(selected->recv);
                    selected->recv = storage->incoming[i];
                    int socket = PcbListener_TakeAcceptedSocket(g_pcbListener);
                    TCPConn_Init(selected->recv, SlotId(selected), socket, 1);
                    accepted = 1;
                    break;
                }
            }
            if (accepted) {
                for (i = 0; i < 4; ++i, ++slots) {
                    if (slots->send != 0) PcbConn_RecycleIfOver(slots->send);
                }
            }
            PCBCheck_StateSet(g_pcbListener);
        }
        PCBCheck_ProcessLinks();
        if (g_pcbSyncReady != 0) {
            Slot *slots = storage->slots;
            Sync *sync = &storage->sync;
            signed char *phases = g_pcbSyncPhasePerPcb;
            int i;
            for (i = 0; i < 4; ++i) {
                sync->scenes[i] = (slots[i].header.word >> 15) & 255;
                sync->roles[i] = slots[i].header.bytes.role.role;
                phases[i] = 0;
            }
            PCBComm_UpdateSyncPhase1();
            PCBComm_UpdateSyncPhase5();
            for (i = 0; i < 4; ++i) {
                if (phases[i] == 0) {
                    if (sync->scenes[i] < 45) sync->timers[i] = lbl_806D316C;
                    else sync->timers[i] = lbl_806D3168;
                }
            }
            sync->ready = 1;
            for (i = 0; i < 4; ++i) {
                u32 scene = (slots[i].header.word >> 15) & 255;
                if (scene != 0 && scene < 7 && slots[i].header.bytes.role.role == 0 && scene == 3) {
                    sync->ready = 0;
                    break;
                }
            }
        }
        PCBComm_ComputeSyncState();
        if (send) {
            PCBComm_SendToAllPeers();
            lbl_806D11A4 = 0;
            lbl_806D11A8 = 0;
        }
    }
    PCBCheck_RecvLinkData(receive);
    if (update && g_isCommHost == 1) {
        u8 *snapshots = storage->hostSnapshots[0];
        int next = 1;
        memcpy(snapshots, snapshots + next * 0x1C, 0x1C);
    }
    return 1;
}

extern "C" int PcbComm_Shutdown(void)
{
    Storage *storage = &lbl_805A5EC0;
    if (g_pcbCommEnabled == 0) return 0;
    Slot *slot = storage->slots;
    LifecycleConn **outgoing = storage->outgoing;
    LifecycleConn **incoming = storage->incoming;
    int i;
    for (i = 0; i < 4; ++i, ++slot, ++outgoing, ++incoming) {
        if (slot->send != 0) TCPConn_Close(slot->send);
        if (slot->recv != 0) TCPConn_Close(slot->recv);
        PcbConn_Close(*outgoing, 1);
        PcbConn_Close(*incoming, 1);
        slot->send = 0;
        slot->recv = 0;
        *outgoing = 0;
        *incoming = 0;
    }
    PcbListener_Dtor(g_pcbListener, 1);
    g_pcbListener = 0;
    g_pcbCommEnabled = 0;
    return 1;
}

extern "C" int PCBComm_Init(void)
{
    Storage *storage = &lbl_805A5EC0;
    if (g_pcbCommEnabled == 1) return 0;
    int myId = (signed char)lbl_80598A60[0x21];
    g_pcbCommEnabled = 1;
    lbl_806D1191 = 0;
    g_pcbSyncReady = 0;
    lbl_806CEFC8 = 1;
    lbl_806D1193 = 0;
    g_confirmFlag = 0;
    g_myPcbId = myId;
    g_pcbListener = new LifecycleListener;
    lbl_806D11B0 = 0;
    lbl_806D11A4 = 0;
    lbl_806D11A8 = 0;
    lbl_806D11AC = 0;
    lbl_806D1188 = OSGetTick();
    lbl_806D11C0[0] = lbl_806D316C;
    lbl_806D11C0[1] = lbl_806D3168;
    lbl_806D11C8 = OSGetTime();
    LifecycleConn **outgoing = storage->outgoing;
    LifecycleConn **incoming = storage->incoming;
    Slot *slot = storage->slots;
    int i;
    for (i = 0; i < 4; ++i, ++incoming, ++slot, ++outgoing) {
        if (i == g_myPcbId - 1) { *outgoing = 0; *incoming = 0; }
        else { *outgoing = new LifecycleConn; *incoming = new LifecycleConn; }
        if (i >= 0 && i < 4) {
            int id = i + 1;
            SetSlotId(slot, id);
            slot->flags.bits.tx = 0;
            slot->flags.bits.rx = 0;
            slot->count = 0;
            slot->flags.bits.blocks = 0;
            slot->flags.bits.card = 0;
            slot->flags.bits.ack = 1;
            if (SlotId(slot) == g_myPcbId) {
                slot->flags.bits.local = 1;
                slot->send = 0;
                slot->recv = 0;
            } else {
                slot->flags.bits.local = 0;
                slot->send = Outgoing(storage)[id - 1];
                slot->recv = 0;
                TCPConn_Close(slot->send);
                TCPConn_Init(slot->send, i + 1, -1, 0);
            }
            ResetScratch(slot, i);
        }
    }
    lbl_806D11A0 = 1;
    g_ringReadIdx = 0;
    u8 *cursor = storage->ring[0];
    for (i = 0; i < 64; ++i, cursor += 0xDC) memset(cursor, 0, 0xDC);
    memset(&storage->sync, 0, 0x1C);
    return 1;
}

PCBComm::~PCBComm() {}
