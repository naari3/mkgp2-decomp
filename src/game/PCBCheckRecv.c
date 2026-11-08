/* Only storage accessed by PCBCheck_RecvLinkData is modeled here. */
typedef struct PcbRecvFlags {
    unsigned char local : 1;
    unsigned char reserved6 : 2;
    unsigned char receiving : 1;
    unsigned char reserved3 : 1;
    unsigned char completed : 1;
    unsigned char reserved0 : 2;
} PcbRecvFlags;
typedef struct PcbRecvSlot {
    unsigned char header[0x2C];
    unsigned char samples[64][0x28];
    unsigned char padA2C[4];
    void* connection;
    PcbRecvFlags flags;
    unsigned char padA35[3];
    signed char readIndex, writeIndex;
    unsigned char padA3A[2];
} PcbRecvSlot;
/* Preserve the declaration order of the shared communication buffers. */
#pragma cplusplus on
unsigned char lbl_805A5EC0[0x204];
unsigned char lbl_805A60C4[0x54];
unsigned char g_pcbSyncTable[0x1C];
unsigned char lbl_805A6134[0x20];
PcbRecvSlot lbl_805A6154[4];
unsigned char lbl_805A8A44[4][0x45];
unsigned char g_ringBufferBase[64][0xDC];
unsigned char lbl_805AC258[2][0x1C];
#pragma cplusplus reset
extern unsigned char g_pcbCommEnabled, g_isCommHost;
extern int g_ringReadIdx, lbl_806D11A0;
extern void* memcpy(void*, const void*, unsigned long);
extern int TCPConn_PollRecvComplete(void*);
extern unsigned short TCPConn_PeekRxMessage(void*, unsigned short*, unsigned char**);
extern unsigned char TCPConn_ConsumeRxMessage(void*);
extern int TCPConn_PollRecv(void*);
extern unsigned char* GetDisplayContext(int);

static inline void PCBCheck_NextPeer(PcbRecvSlot** slot,
                                     unsigned char** output,
                                     unsigned char** status)
{
    ++*slot;
    *output += 0x28;
    *status += 0x45;
}

static inline int PCBCheck_NewestSample(int distance, int start)
{
    distance += start;
    return (distance - 1) % 64;
}

int PCBCheck_RecvLinkData(unsigned char advanceRead)
{
    PcbRecvSlot* slot;
    unsigned char* output;
    unsigned char* status;
    unsigned char* localSample;
    int i;
    unsigned char* payload;
    unsigned short type;
    if (g_pcbCommEnabled == 0) {
        return 0;
    }
    slot = lbl_805A6154;
    output = g_ringBufferBase[0];
    status = lbl_805A8A44[0];
    localSample = lbl_805A60C4 + 0x2C;
    for (i = 0; i < 4; ++i, PCBCheck_NextPeer(&slot, &output, &status)) {
        if (slot->flags.local == 1) {
            memcpy(slot, lbl_805A60C4, 0x2C);
            memcpy(slot->samples[slot->writeIndex], localSample, 0x28);
            slot->readIndex = (slot->readIndex + 1) % 64;
            slot->writeIndex = (slot->writeIndex + 1) % 64;
            if (g_isCommHost == 1) {
                memcpy(output, slot->samples[slot->readIndex], 0x28);
            }
        }
        if (slot->connection != 0) {
            if ((slot->flags.receiving = 1) != 0) {
                if (TCPConn_PollRecvComplete(slot->connection) > 0 && i >= 0 && i < 4 && slot->connection != 0) {
                    slot->flags.completed = 1;
                    do {
                        if (TCPConn_PeekRxMessage(slot->connection, &type, &payload) != 0) {
                            if (type == 1) {
                                unsigned char* packet = payload;
                                memcpy(slot, packet, 0x2C);
                                memcpy(slot->samples[slot->writeIndex], packet + 0x2C, 0x28);
                                slot->writeIndex = (slot->writeIndex + 1) % 64;
                            }
                            if (type == 2) {
                                memcpy(g_ringBufferBase[lbl_806D11A0], payload, 0xDC);
                                lbl_806D11A0 = (lbl_806D11A0 + 1) % 64;
                            }
                            if (type == 3) {
                                unsigned char* packet = payload;
                                unsigned char* context = GetDisplayContext(i);
                                memcpy(context + *(int*)packet * 0x200, packet + 4, 0x200);
                            }
                            if (type == 4) {
                                memcpy(lbl_805AC258, payload, 0x1C);
                            }
                            if (type == 5) {
                                memcpy(g_pcbSyncTable, payload, 0x1C);
                            }
                            if (type == 6) {
                                memcpy(status, payload, 0x45);
                            }
                        }
                    } while (TCPConn_ConsumeRxMessage(slot->connection) == 1);
                }
                {
                    int next = (slot->readIndex + 1) % 64;
                    if (next != slot->writeIndex) {
                        slot->readIndex = next;
                    }
                }
                if (g_isCommHost == 1) {
                    int cursor;
                    int end;
                    int start;
                    int distance = 0;
                    start = slot->readIndex;
                    cursor = start;
                    end = slot->writeIndex;
                    for (; end != cursor % 64; ++cursor, ++distance) {}
                    if (distance > 3) {
                        slot->readIndex = PCBCheck_NewestSample(distance, start);
                    }
                    memcpy(output, slot->samples[slot->readIndex], 0x28);
                }
                TCPConn_PollRecv(slot->connection);
            }
        }
    }
    if (advanceRead != 0 && g_isCommHost == 0) {
        int next = (g_ringReadIdx + 1) % 64;
        if (next != lbl_806D11A0) {
            g_ringReadIdx = next;
        }
    }
    return 1;
}
