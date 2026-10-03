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
typedef struct SendStorage {
    int blockIndex;
    unsigned char block[0x200];
    unsigned char broadcast[0x54];
    unsigned char sync[0x1C];
    unsigned char gap274[0x20];
    PeerSlot peers[4];
    unsigned char cards[4][0x45];
    unsigned char ringSnapshot[0xDC];
    unsigned char gap2D74[0x3624];
    unsigned char snapshotHeader[0x1C];
    unsigned char snapshot[0x1C];
} SendStorage;
extern SendStorage lbl_805A5EC0;
extern unsigned char g_pcbCommEnabled;
extern unsigned char g_pcbSyncReady;
extern unsigned char g_isCommHost;
extern int g_currentSceneState;
extern int g_localPcbRole;
extern int g_myPcbId;
extern unsigned char *lbl_806D11B0;
extern void PCBComm_BuildBroadcastSlot(void);
extern int PcbConn_TryReceiveAck(void *connection);
extern int TCPConn_EnqueueMessage(void *connection, unsigned short type,
                                 unsigned short length, const void *data);
extern int TCPConn_PollSend(void *connection);
extern void *memcpy(void *destination, const void *source, unsigned long length);

static inline int SendPeers(SendStorage *storage, unsigned char *snapshot,
                            unsigned char *block)
{
    int i;
    int scene;
    PeerSlot *peer;
    scene = g_currentSceneState;
    peer = storage->peers;
    snapshot += sizeof(storage->snapshotHeader);
    block += sizeof(storage->blockIndex);
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
            TCPConn_EnqueueMessage(peer->connection, 5, 0x1C, storage->sync);
        if (g_isCommHost == 1 && peer->role == g_localPcbRole) {
            TCPConn_EnqueueMessage(peer->connection, 1, 0x54, storage->broadcast);
            TCPConn_EnqueueMessage(peer->connection, 2, 0xDC, storage->ringSnapshot);
            TCPConn_EnqueueMessage(peer->connection, 4, 0x1C, snapshot);
        } else {
            TCPConn_EnqueueMessage(peer->connection, 1, 0x54, storage->broadcast);
        }
        if (peer->blocksRemaining != 0) {
            int index = peer->blocksRemaining - 1;
            storage->blockIndex = index;
            memcpy(block, lbl_806D11B0 + index * 0x200, 0x200);
            TCPConn_EnqueueMessage(peer->connection, 3, 0x204, &storage->blockIndex);
            peer->blocksRemaining = peer->blocksRemaining - 1;
        }
        if (peer->cardPending != 0) {
            TCPConn_EnqueueMessage(peer->connection, 6, 0x45,
                                   (unsigned char *)storage->cards +
                                   (g_myPcbId - 1) * 0x45);
            peer->cardPending = 0;
        }
        TCPConn_PollSend(peer->connection);
    }
    return 1;
}

int PCBComm_SendToAllPeers(void)
{
    SendStorage *storage = &lbl_805A5EC0;
    if (g_pcbCommEnabled == 0) return 0;
    PCBComm_BuildBroadcastSlot();
    return SendPeers(storage, storage->snapshotHeader,
                     (unsigned char *)&storage->blockIndex);
}
