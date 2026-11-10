/* Only fields observed by SendToAllPeers; storage and snapshots remain external. */
typedef struct PeerSlot {
    unsigned char unusedHead : 1;
    unsigned char role : 3;
    unsigned char unusedLow : 4;
    unsigned char gap01[0xA2B];
    void *connection;
    unsigned char gapA30[4];
    unsigned char unusedFlags : 2;
    unsigned char sendPending : 1;
    unsigned char unusedBit4 : 1;
    unsigned char cardPending : 1;
    unsigned char ackPending : 1;
    unsigned char unusedBits01 : 2;
    unsigned char unusedCountBit : 1;
    unsigned char blocksRemaining : 7;
    unsigned char gapA36[6];
} PeerSlot;
typedef struct BlockMsg { int index; unsigned char data[0x200]; } BlockMsg;
typedef struct SnapshotMsg { unsigned char header[0x1C]; unsigned char body[0x1C]; } SnapshotMsg;
BlockMsg PCBCheckRecv_bss_805A5EC0;
unsigned char PCBComm_BuildBroadcastSlot_bss_805A60C4[0x54];
unsigned char g_pcbSyncTable[0x1C];
unsigned char PCBCheck_ProcessLinks_bss_805A6134[0x20];
PeerSlot PCBCheckRecv_bss_805A6154[4];
unsigned char PCBComm_PackAndTriggerCardSnapshot_bss_805A8A44[4][0x45];
unsigned char g_ringBufferBase[0x3700];
SnapshotMsg PCBCheckRecv_bss_805AC258;
extern unsigned char g_pcbCommEnabled;
extern unsigned char g_pcbSyncReady;
extern unsigned char g_isCommHost;
extern int g_currentSceneState;
extern int g_localPcbRole;
extern int g_myPcbId;
extern unsigned char *PCBCheckRecv_bss_806D11B0;
extern void PCBComm_BuildBroadcastSlot(void);
extern int PcbConn_TryReceiveAck(void *connection);
extern int TCPConn_EnqueueMessage(void *connection, unsigned short type,
                                 unsigned short length, const void *data);
extern int TCPConn_PollSend(void *connection);
extern void *memcpy(void *destination, const void *source, unsigned long length);

static inline unsigned char *Payload(unsigned char *packet, unsigned long headerSize)
{
    return packet + headerSize;
}

void *OrderProbe(int i)
{
    switch (i) {
    case 0: return &PCBCheckRecv_bss_805A5EC0;
    case 1: return PCBComm_BuildBroadcastSlot_bss_805A60C4;
    case 2: return g_pcbSyncTable;
    case 3: return PCBCheck_ProcessLinks_bss_805A6134;
    case 4: return PCBCheckRecv_bss_805A6154;
    case 5: return PCBComm_PackAndTriggerCardSnapshot_bss_805A8A44;
    case 6: return g_ringBufferBase;
    }
    return &PCBCheckRecv_bss_805AC258;
}

int PCBComm_SendToAllPeers(void)
{
    PeerSlot *peer;
    unsigned char *snapshot;
    unsigned char *block;
    int scene;
    int i;
    if (g_pcbCommEnabled == 0) return 0;
    PCBComm_BuildBroadcastSlot();
    snapshot = PCBCheckRecv_bss_805AC258.body;
    block = PCBCheckRecv_bss_805A5EC0.data;
    scene = g_currentSceneState;
    peer = PCBCheckRecv_bss_805A6154;
    for (i = 0; i < 4; i++, peer++) {
        void *connection = peer->connection;
        if (connection == 0) continue;
        if (scene != 6 && scene != 7 && scene != 8 &&
            scene != 48 && scene != 49 && scene != 50) {
            if (g_localPcbRole <= 1 || peer->role != g_localPcbRole) {
                if (peer->ackPending == 0) continue;
            } else {
                if (scene < 42 || scene > 44) {
                    if (peer->ackPending == 0) continue;
                }
            }
        }
        if (peer->sendPending != 1) continue;
        PcbConn_TryReceiveAck(connection);
        peer->ackPending = 0;
        if (g_pcbSyncReady == 1)
            TCPConn_EnqueueMessage(peer->connection, 5, 0x1C, g_pcbSyncTable);
        if (g_isCommHost == 1 && peer->role == g_localPcbRole) {
            TCPConn_EnqueueMessage(peer->connection, 1, 0x54, PCBComm_BuildBroadcastSlot_bss_805A60C4);
            TCPConn_EnqueueMessage(peer->connection, 2, 0xDC, g_ringBufferBase);
            TCPConn_EnqueueMessage(peer->connection, 4, 0x1C, snapshot);
        } else {
            TCPConn_EnqueueMessage(peer->connection, 1, 0x54, PCBComm_BuildBroadcastSlot_bss_805A60C4);
        }
        if (peer->blocksRemaining != 0) {
            int index = peer->blocksRemaining - 1;
            PCBCheckRecv_bss_805A5EC0.index = index;
            memcpy(block, PCBCheckRecv_bss_806D11B0 + index * 0x200, 0x200);
            TCPConn_EnqueueMessage(peer->connection, 3, 0x204, &PCBCheckRecv_bss_805A5EC0.index);
            peer->blocksRemaining = peer->blocksRemaining - 1;
        }
        if (peer->cardPending != 0) {
            TCPConn_EnqueueMessage(peer->connection, 6, 0x45,
                                   (unsigned char *)PCBComm_PackAndTriggerCardSnapshot_bss_805A8A44 +
                                   (g_myPcbId - 1) * 0x45);
            peer->cardPending = 0;
        }
        TCPConn_PollSend(peer->connection);
    }
    return 1;
}
