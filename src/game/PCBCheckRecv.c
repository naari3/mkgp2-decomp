/* PCB link communication: receive (PCBCheck_RecvLinkData), send
 * (PCBComm_SendToAllPeers) and sync-state (PCBComm_ComputeSyncState).
 * One TU because the 0x805A5EC0 .bss pool is owned here: the senders address
 * each pooled object (lbl_805A6154 peers, lbl_805AC258 sync outputs, ...)
 * off the section anchor, and `&lbl_805AC258[1]` stays a two-step
 * `addi base,0x6398; addi +0x1c` (mweppc AddPropagation.c refuses to fold a
 * displacement into an add whose alias is a non-local Object).
 * NonMatching: PCBComm_ComputeSyncState (98.2%, PeersReady role/ready and
 * vote-array zero registers swapped). */
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

#pragma push
#pragma optimize_for_size on
/* Only fields observed by SendToAllPeers. */
typedef struct SendPeerSlot {
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
} SendPeerSlot;
extern unsigned char g_pcbSyncReady;
extern int g_currentSceneState;
extern int g_localPcbRole;
extern int g_myPcbId;
extern unsigned char *lbl_806D11B0;
extern void PCBComm_BuildBroadcastSlot(void);
extern int PcbConn_TryReceiveAck(void *connection);
extern int TCPConn_EnqueueMessage(void *connection, unsigned short type,
                                 unsigned short length, const void *data);
extern int TCPConn_PollSend(void *connection);

static inline unsigned char *Payload(unsigned char *packet, unsigned long headerSize)
{
    return packet + headerSize;
}

int PCBComm_SendToAllPeers(void)
{
    SendPeerSlot *peer;
    unsigned char *snapshot;
    unsigned char *block;
    int scene;
    int i;
    if (g_pcbCommEnabled == 0) return 0;
    PCBComm_BuildBroadcastSlot();
    snapshot = Payload(lbl_805AC258[0], sizeof(lbl_805AC258[0]));
    block = Payload(lbl_805A5EC0, sizeof(int));
    scene = g_currentSceneState;
    peer = ((SendPeerSlot *)lbl_805A6154);
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
            TCPConn_EnqueueMessage(peer->connection, 1, 0x54, lbl_805A60C4);
            TCPConn_EnqueueMessage(peer->connection, 2, 0xDC, g_ringBufferBase[0]);
            TCPConn_EnqueueMessage(peer->connection, 4, 0x1C, snapshot);
        } else {
            TCPConn_EnqueueMessage(peer->connection, 1, 0x54, lbl_805A60C4);
        }
        if (peer->blocksRemaining != 0) {
            int index = peer->blocksRemaining - 1;
            *(int *)lbl_805A5EC0 = index;
            memcpy(block, lbl_806D11B0 + index * 0x200, 0x200);
            TCPConn_EnqueueMessage(peer->connection, 3, 0x204, lbl_805A5EC0);
            peer->blocksRemaining = peer->blocksRemaining - 1;
        }
        if (peer->cardPending != 0) {
            TCPConn_EnqueueMessage(peer->connection, 6, 0x45,
                                   (unsigned char *)lbl_805A8A44 +
                                   (g_myPcbId - 1) * 0x45);
            peer->cardPending = 0;
        }
        TCPConn_PollSend(peer->connection);
    }
    return 1;
}
#pragma pop

/* Only the communication bytes observed in ComputeSyncState are described. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PeerHeader {
    unsigned char reserved7 : 1;
    unsigned char role : 3;
    unsigned char reserved0 : 4;
} PeerHeader;
typedef struct VoteByte {
    unsigned char track : 7;
    unsigned char option : 1;
} VoteByte;
typedef struct SyncPeerSlot {
    union { u32 word; struct { PeerHeader header; u8 rest[3]; } bytes; } first;
    u8 character;
    VoteByte vote;
    u8 mode;
    u8 pad7[0xA35];
} SyncPeerSlot;
typedef struct CardRow { u8 bytes[0x45]; } CardRow;
typedef struct CardPointers { CardRow* row[4]; } CardPointers;
typedef struct SyncOutput {
    union {
        struct { unsigned short upper : 5; unsigned short track : 7;
                 unsigned short lower : 4; } half;
        struct { u8 byte0; unsigned char upper : 4;
                 unsigned char option : 1; unsigned char mode : 2;
                 unsigned char lower : 1; } bytes;
    } choice;
    u8 pad2[2];
    int commonItem;
    u8 scene;
    u8 position[4];
    u8 padD[8];
    u8 randomCharacter[2];
    u8 pad17[3];
    u8 sequence;
    u8 randomSeed;
} SyncOutput;
typedef struct CommStorage {
    u8 pad0[0x258];
    u8 sync[8];
    u8 pad260[0x34];
    SyncPeerSlot peer[4];
    CardRow card[4];
    u8 pad2C98[0x3700];
    SyncOutput output[2];
} CommStorage;

extern const CardPointers lbl_80312234[];
extern int g_localPcbRole, g_currentSceneState;
extern u8 lbl_806CEFC8;
/* Actual callee: no incoming arguments, r3 is a 15-bit integer. */
extern int rand(void);
/* Actual callee reads four pointer words through r3 and returns an integer. */
extern int CardSnapshot_ResolveCommonItems(CardRow** rows);

static inline u8 PeersReady(int role)
{
    int i;
    u8 ready = 1;
    if (role != 0) {
        unsigned int scene = g_currentSceneState;
        SyncPeerSlot* peer = (SyncPeerSlot *)lbl_805A6154;
        for (i = 0; i < 4; ++i, ++peer)
            if (peer->first.bytes.header.role == role &&
                ((peer->first.word >> 15) & 255) != scene) ready = 0;
    }
    return ready;
}

static inline int RoleCount(u8* sync, int role)
{
    int count = 0;
    int i;
    if (role == 0) return 1;
    for (i = 0; i < 4; ++i, ++sync)
        if (sync[4] == role) ++count;
    return count;
}

static inline void CountModeVotes(SyncPeerSlot* peer, int* votes, int role)
{
    int i;
    for (i = 0; i < 3; ++i) votes[i] = 0;
    for (i = 0; i < 4; ++i, ++peer)
        if (peer->first.bytes.header.role == role)
            ++votes[(peer->mode >> 4) & 3];
}

static inline void CountTrackVotes(SyncPeerSlot* peer, int* votes, int role)
{
    int i;
    for (i = 0; i < 16; ++i) votes[i] = 0;
    for (i = 0; i < 4; ++i, ++peer)
        if (peer->first.bytes.header.role == role)
            ++votes[peer->vote.track];
}

static inline void CountOptionVotes(SyncPeerSlot* peer, int* votes, int role)
{
    int i;
    for (i = 0; i < 2; ++i) votes[i] = 0;
    for (i = 0; i < 4; ++i, ++peer)
        if (peer->first.bytes.header.role == role)
            ++votes[peer->vote.option];
}

static inline SyncOutput* HostOutput(CommStorage* storage)
{
    if (g_isCommHost == 0) return 0;
    if (g_localPcbRole == 0) return 0;
    return &((SyncOutput *)lbl_805AC258)[1];
}

static inline void SelectRoleCards(SyncPeerSlot* peer, CardRow* card,
                                   CardPointers* cards, int role)
{
    int i;
    for (i = 0; i < 4; ++i, ++peer, ++card) {
        if (peer->first.bytes.header.role == role) cards->row[i] = card;
        else cards->row[i] = 0;
    }
}

static inline void MarkUsedCharacters(SyncPeerSlot* peer, u8* used, int role)
{
    int i;
    for (i = 0; i < 4; ++i, ++peer)
        if (peer->first.bytes.header.role == role)
            used[(peer->character >> 4) & 15] = 1;
}

int PCBComm_ComputeSyncState(void)
{
    int trackVotes[16];
    int modeVotes[3];
    CardPointers cards;
    u8 usedCharacters[13];
    int optionVotes[2];
    u8 usedPositions[4];
    int positionCount;
    int characterCount;
    CommStorage* storage = (CommStorage*)lbl_805A5EC0;
    SyncPeerSlot* firstPeer;
    SyncOutput* out = HostOutput(storage);
    SyncPeerSlot* peer;
    int i, winner, role;
    u8 ready;

    if (out == 0) {
        if (g_localPcbRole != 0) return 0;
        out = &((SyncOutput *)lbl_805AC258)[0];
    }
    ready = PeersReady(g_localPcbRole);
    if (ready == 1) out->scene = g_currentSceneState;

    if ((int)out->scene == 12) {
        CountModeVotes(((SyncPeerSlot *)lbl_805A6154), modeVotes, g_localPcbRole);
        winner = 0;
        for (i = 1; i < 3; ++i)
            if (modeVotes[i] > modeVotes[winner]) winner = i;
        out->choice.bytes.mode = winner;
        out->commonItem = -1;
    }
    if ((int)out->scene == 14) {
        out->randomSeed = rand() % 100;
        out->commonItem = -1;
    }
    if ((int)out->scene == 26) {
        winner = 0;
        CountTrackVotes(((SyncPeerSlot *)lbl_805A6154), trackVotes, g_localPcbRole);
        for (i = 0; i < 16; ++i)
            if (trackVotes[i] > trackVotes[winner]) winner = i;
        out->choice.half.track = winner;
    }
    if ((int)out->scene == 26) {
        winner = 0;
        CountOptionVotes(((SyncPeerSlot *)lbl_805A6154), optionVotes, g_localPcbRole);
        for (i = 0; i < 2; ++i)
            if (optionVotes[i] > optionVotes[winner]) winner = i;
        out->choice.bytes.option = winner;
    }
    if ((int)out->scene == 26 && out->commonItem == -1) {
        CardRow* card = (CardRow *)lbl_805A8A44;
        firstPeer = ((SyncPeerSlot *)lbl_805A6154);
        peer = firstPeer;
        cards = lbl_80312234[0];
        role = g_localPcbRole;
        SelectRoleCards(peer, card, &cards, role);
        out->commonItem = CardSnapshot_ResolveCommonItems(cards.row);
        positionCount = 0;
        for (i = 0; i < 4; ++i) usedPositions[i] = 0;
        role = g_localPcbRole;
        for (; positionCount < 4 - RoleCount(g_pcbSyncTable, role); ++positionCount)
            usedPositions[positionCount] = 1;
        for (i = 0; i < 4; ++i) {
            int peerRole = firstPeer[i].first.bytes.header.role;
            if (peerRole == g_localPcbRole) {
                int position;
                do { position = rand() % 4; }
                while (usedPositions[position] != 0);
                usedPositions[position] = 1;
                out->position[i] = position;
            }
        }
        characterCount = 0;
        for (i = 0; i < 13; ++i) usedCharacters[i] = 0;
        MarkUsedCharacters(firstPeer, usedCharacters, g_localPcbRole);
        do {
            int character = rand() % 13;
            if (usedCharacters[character] == 0) {
                usedCharacters[character] = 1;
                out->randomCharacter[characterCount++] = character;
            }
        } while (characterCount < 2);
    }
    if (lbl_806CEFC8 != 0) ++out->sequence;
    else lbl_806CEFC8 = 1;
    return 1;
}
