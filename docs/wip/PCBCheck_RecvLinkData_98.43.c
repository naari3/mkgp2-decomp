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
extern unsigned char PCBCheckRecv_bss_805A5EC0[];
extern unsigned char g_pcbCommEnabled, g_isCommHost;
extern int g_ringReadIdx, g_ringWriteIdx;
extern void* memcpy(void*, const void*, unsigned long);
extern int TCPConn_PollRecvComplete(void*);
extern unsigned short TCPConn_PeekRxMessage(void*, unsigned short*, unsigned char**);
extern unsigned char TCPConn_ConsumeRxMessage(void*);
extern int TCPConn_PollRecv(void*);
extern unsigned char* GetDisplayContext(int);

static inline unsigned char* PCBCheck_LocalSample(unsigned char* packet)
{
    return packet + 0x2C;
}

int PCBCheck_RecvLinkData(unsigned char advanceRead)
{
    unsigned char* base = PCBCheckRecv_bss_805A5EC0;
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
    localSample = base + 0x204;
    slot = (PcbRecvSlot*)(base + 0x294);
    output = base + 0x2C98;
    status = base + 0x2B84;
    localSample = ((PcbRecvSlot*)localSample)->samples[0];
    for (i = 0; i < 4; ++i, ++slot, output += 0x28, status += 0x45) {
        if (slot->flags.local == 1) {
            memcpy(slot, base + 0x204, 0x2C);
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
                                memcpy(((unsigned char (*)[0xDC])(base + 0x2C98))[g_ringWriteIdx], payload, 0xDC);
                                g_ringWriteIdx = (g_ringWriteIdx + 1) % 64;
                            }
                            if (type == 3) {
                                unsigned char* packet = payload;
                                unsigned char* context = GetDisplayContext(i);
                                memcpy(context + *(int*)packet * 0x200, packet + 4, 0x200);
                            }
                            if (type == 4) {
                                memcpy(base + 0x6398, payload, 0x1C);
                            }
                            if (type == 5) {
                                memcpy(base + 0x258, payload, 0x1C);
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
                        distance += start;
                        slot->readIndex = (distance - 1) % 64;
                    }
                    memcpy(output, slot->samples[slot->readIndex], 0x28);
                }
                TCPConn_PollRecv(slot->connection);
            }
        }
    }
    if (advanceRead != 0 && g_isCommHost == 0) {
        int next = (g_ringReadIdx + 1) % 64;
        if (next != g_ringWriteIdx) {
            g_ringReadIdx = next;
        }
    }
    return 1;
}
