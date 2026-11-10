#include "game/types/reg_args.h"
#include "game/types/bitfields.h"
#include "game/types/c_region.h"
C_REGION_BEGIN
#pragma exceptions on
#pragma use_lmw_stmw on
/* PCB link communication unit, .text 0x80083348..0x80086A0C: receive / send /
 * sync-state, sync phases, ring-buffer and slot accessors, boot PCB check,
 * debug overlays and the lifecycle (Process / Shutdown / Init).
 * One TU: the first function (PCBCheck_RecvLinkData) and the last ones
 * (PCBComm_Process / PcbComm_Shutdown / PCBComm_Init) address the .bss pool
 * 0x805A5EC0..0x805AC290 off the same section anchor, every function between
 * them that touches >= 3 pool objects does too, and the weak inline FKTex
 * destructor used by DrawLinkErrorOverlay sits at the very end of the range
 * (dtor_800869D0). Merged from 24 over-split files; each part keeps its own
 * local views of the pool behind #define/#undef renames
 * (tools/extab_user_renames.json maps X_pN back to X).
 * `&PCBCheckRecv_bss_805AC258[1]` stays a two-step `addi base,0x6398; addi +0x1c`
 * (mweppc AddPropagation.c refuses to fold a displacement into an add whose
 * alias is a non-local Object).
 * NonMatching: PCBComm_Process (99.95%, see docs/gave_up.md). */
typedef struct PcbRecvFlags {
    BITFIELDS6(unsigned char local:1, unsigned char reserved6:2, unsigned char receiving:1, unsigned char reserved3:1, unsigned char completed:1, unsigned char reserved0:2)
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
/* .rodata pool 0x80311E38..0x803123B0 (also read by other units). */
/* element type read off the values (all floats), not from code */
extern const float PCBCheckRecv_rodata_80311E38[255] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f,
    0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f,
    83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f,
    83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f
};
extern const unsigned int PCBComm_ComputeSyncState_rodata_80312234[4] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
extern const char lbl_80312244[15] = "PCB ID : %d OK";
extern const char lbl_80312254[24] = "PCB ID : %d CHECKING...";
extern const char lbl_8031226C[23] = "S PCB %d : %s (port%d)";
extern const char lbl_80312284[35] = "C PCB %d : MY      %d : %02d (%2d)";
extern const char lbl_803122A8[49] = "C PCB %d : %s (P%d:O%d) %s %d:%02d (%02d) E%+04d";
extern const char lbl_803122DC[44] = "C PCB %d : %s (P%d:O%02d) NO recv socket %d";
extern const char lbl_80312308[23] = "ROM READ TIME : %f sec";
extern const char lbl_80312320[23] = "ROM READ MAX  : %f sec";
extern const char lbl_80312338[21] = "\x8C" "W" "\x88" "\xF5" "\x82" "\xF0" "\x8C" "\xC4" "\x82" "\xF1" "\x82" "\xC5" "\x82" "\xAD" "\x82" "\xBE" "\x82" "\xB3" "\x82" "\xA2";
extern const char lbl_80312350[26] = "Please call an attendant.";
extern const char lbl_8031236C[25] = "\x92" "\xCA" "\x90" "M" "\x83" "G" "\x83" "\x89" "\x81" "[" "\x82" "\xAA" "\x94" "\xAD" "\x90" "\xB6" "\x82" "\xB5" "\x82" "\xDC" "\x82" "\xB5" "\x82" "\xBD";
extern const char lbl_80312388[24] = "   Link error occurred.";
extern const char lbl_803123A0[14] = "PROCESS_ERROR";
/* Preserve the declaration order of the shared communication buffers. */
C_REGION_END
#pragma cplusplus on
unsigned char PCBCheckRecv_bss_805A5EC0[0x204];
unsigned char PCBComm_BuildBroadcastSlot_bss_805A60C4[0x54];
unsigned char g_pcbSyncTable[0x1C];
unsigned char PCBCheck_ProcessLinks_bss_805A6134[0x10];
unsigned char lbl_805A6144[0x10];
PcbRecvSlot PCBCheckRecv_bss_805A6154[4];
unsigned char PCBComm_PackAndTriggerCardSnapshot_bss_805A8A44[4][0x45];
unsigned char g_ringBufferBase[64][0xDC];
unsigned char PCBCheckRecv_bss_805AC258[2][0x1C];
#pragma cplusplus reset
C_REGION_BEGIN
extern unsigned char g_pcbCommEnabled, g_isCommHost;
extern int g_ringReadIdx, g_ringWriteIdx;
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
    slot = PCBCheckRecv_bss_805A6154;
    output = g_ringBufferBase[0];
    status = PCBComm_PackAndTriggerCardSnapshot_bss_805A8A44[0];
    localSample = PCBComm_BuildBroadcastSlot_bss_805A60C4 + 0x2C;
    for (i = 0; i < 4; ++i, PCBCheck_NextPeer(&slot, &output, &status)) {
        if (slot->flags.local == 1) {
            memcpy(slot, PCBComm_BuildBroadcastSlot_bss_805A60C4, 0x2C);
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
                                memcpy(g_ringBufferBase[g_ringWriteIdx], payload, 0xDC);
                                g_ringWriteIdx = (g_ringWriteIdx + 1) % 64;
                            }
                            if (type == 3) {
                                unsigned char* packet = payload;
                                unsigned char* context = GetDisplayContext(i);
                                memcpy(context + *(int*)packet * 0x200, packet + 4, 0x200);
                            }
                            if (type == 4) {
                                memcpy(PCBCheckRecv_bss_805AC258, payload, 0x1C);
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
        if (next != g_ringWriteIdx) {
            g_ringReadIdx = next;
        }
    }
    return 1;
}

#pragma push
#pragma optimize_for_size on
/* Only fields observed by SendToAllPeers. */
typedef struct SendPeerSlot {
    BITFIELDS3(unsigned char unusedHead:1, unsigned char role:3, unsigned char unusedLow:4)
    unsigned char gap01[0xA2B];
    void *connection;
    unsigned char gapA30[4];
    BITFIELDS6(unsigned char unusedFlags:2, unsigned char sendPending:1, unsigned char unusedBit4:1, unsigned char cardPending:1, unsigned char ackPending:1, unsigned char unusedBits01:2)
    BITFIELDS2(unsigned char unusedCountBit:1, unsigned char blocksRemaining:7)
    unsigned char gapA36[6];
} SendPeerSlot;
extern unsigned char g_pcbSyncReady;
extern int g_currentSceneState;
extern int g_localPcbRole;
extern int g_myPcbId;
extern unsigned char *PCBCheckRecv_bss_806D11B0;
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
    snapshot = Payload(PCBCheckRecv_bss_805AC258[0], sizeof(PCBCheckRecv_bss_805AC258[0]));
    block = Payload(PCBCheckRecv_bss_805A5EC0, sizeof(int));
    scene = g_currentSceneState;
    peer = ((SendPeerSlot *)PCBCheckRecv_bss_805A6154);
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
            TCPConn_EnqueueMessage(peer->connection, 2, 0xDC, g_ringBufferBase[0]);
            TCPConn_EnqueueMessage(peer->connection, 4, 0x1C, snapshot);
        } else {
            TCPConn_EnqueueMessage(peer->connection, 1, 0x54, PCBComm_BuildBroadcastSlot_bss_805A60C4);
        }
        if (peer->blocksRemaining != 0) {
            int index = peer->blocksRemaining - 1;
            *(int *)PCBCheckRecv_bss_805A5EC0 = index;
            memcpy(block, PCBCheckRecv_bss_806D11B0 + index * 0x200, 0x200);
            TCPConn_EnqueueMessage(peer->connection, 3, 0x204, PCBCheckRecv_bss_805A5EC0);
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
#pragma pop

/* Only the communication bytes observed in ComputeSyncState are described. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PeerHeader {
    BITFIELDS3(unsigned char reserved7:1, unsigned char role:3, unsigned char reserved0:4)
} PeerHeader;
typedef struct VoteByte {
    BITFIELDS2(unsigned char track:7, unsigned char option:1)
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
        struct { BITFIELDS3(unsigned short upper:5, unsigned short track:7, unsigned short lower:4) } half;
        struct { u8 byte0; BITFIELDS4(unsigned char upper:4, unsigned char option:1, unsigned char mode:2, unsigned char lower:1) } bytes;
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

#define PCBComm_ComputeSyncState_rodata_80312234 ((const CardPointers *)PCBComm_ComputeSyncState_rodata_80312234)
extern int g_localPcbRole, g_currentSceneState;
extern u8 PCBCheckRecv_data_806CEFC8;
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
        SyncPeerSlot* peer = (SyncPeerSlot *)PCBCheckRecv_bss_805A6154;
        for (i = 0; i < 4; ++i, ++peer)
            if (peer->first.bytes.header.role == role &&
                ((peer->first.word >> 15) & 255) != scene) ready = 0;
    }
    return ready;
}

static inline void PeersReady2(int role, u8 *ready)
{
    int i;
    if (role != 0) {
        unsigned int scene = g_currentSceneState;
        SyncPeerSlot* peer = (SyncPeerSlot *)PCBCheckRecv_bss_805A6154;
        for (i = 0; i < 4; ++i, ++peer)
            if (peer->first.bytes.header.role == role &&
                ((peer->first.word >> 15) & 255) != scene) *ready = 0;
    }
}

static inline int RoleCount(int role)
{
    int count;
    int i;
    if (role == 0) return 1;
    count = 0;
    for (i = 0; i < 4; ++i)
        if (g_pcbSyncTable[i + 4] == role) ++count;
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
    return &((SyncOutput *)PCBCheckRecv_bss_805AC258)[1];
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
    CommStorage* storage = (CommStorage*)PCBCheckRecv_bss_805A5EC0;
    SyncPeerSlot* firstPeer;
    SyncOutput* out = HostOutput(storage);
    SyncPeerSlot* peer;
    int i, winner, role;
    u8 ready;

    if (out == 0) {
        if (g_localPcbRole != 0) return 0;
        out = &((SyncOutput *)PCBCheckRecv_bss_805AC258)[0];
    }
    ready = 1;
    PeersReady2(g_localPcbRole, &ready);
    if (ready == 1) out->scene = g_currentSceneState;

    if ((int)out->scene == 12) {
        CountModeVotes(((SyncPeerSlot *)PCBCheckRecv_bss_805A6154), modeVotes, g_localPcbRole);
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
        int winner = 0;
        CountTrackVotes(((SyncPeerSlot *)PCBCheckRecv_bss_805A6154), trackVotes, g_localPcbRole);
        for (i = 0; i < 16; ++i)
            if (trackVotes[i] > trackVotes[winner]) winner = i;
        out->choice.half.track = winner;
    }
    if ((int)out->scene == 26) {
        int winner = 0;
        CountOptionVotes(((SyncPeerSlot *)PCBCheckRecv_bss_805A6154), optionVotes, g_localPcbRole);
        for (i = 0; i < 2; ++i)
            if (optionVotes[i] > optionVotes[winner]) winner = i;
        out->choice.bytes.option = winner;
    }
    if ((int)out->scene == 26 && out->commonItem == -1) {
        CardRow* card = (CardRow *)PCBComm_PackAndTriggerCardSnapshot_bss_805A8A44;
        firstPeer = ((SyncPeerSlot *)PCBCheckRecv_bss_805A6154);
        peer = firstPeer;
        cards = PCBComm_ComputeSyncState_rodata_80312234[0];
        role = g_localPcbRole;
        SelectRoleCards(peer, card, &cards, role);
        out->commonItem = CardSnapshot_ResolveCommonItems(cards.row);
        positionCount = 0;
        for (i = 0; i < 4; ++i) usedPositions[i] = 0;
        for (; positionCount < 4 - RoleCount(g_localPcbRole); ++positionCount)
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
    if (PCBCheckRecv_data_806CEFC8 != 0) ++out->sequence;
    else PCBCheckRecv_data_806CEFC8 = 1;
    return 1;
}
#undef PCBComm_ComputeSyncState_rodata_80312234

/* ==== PCBCommPhase5.c ==== */
#define OSGetTime OSGetTime_p1
#define PhaseFlags PhaseFlags_p1
#define RoleByte RoleByte_p1
#define SlotHeader SlotHeader_p1
#define SlotView SlotView_p1
#define __div2i __div2i_p1
#define g_pcbSyncPhasePerPcb g_pcbSyncPhasePerPcb_p1
#define PCBCheckRecv_bss_806D11C0 lbl_806D11C0_p1
#define PCBCheckRecv_bss_806D11C8 lbl_806D11C8_p1
#define lbl_806D3158 lbl_806D3158_p1
#define lbl_806D315C lbl_806D315C_p1
#define lbl_806D3160 lbl_806D3160_p1
#define lbl_806D3164 lbl_806D3164_p1
#define lbl_806D3168 lbl_806D3168_p1
#define PCBCheckRecv_bss_805A6154 ((SlotView *)PCBCheckRecv_bss_805A6154)
#pragma exceptions off
#pragma use_lmw_stmw on
/* Only observed overlays; all global storage remains externally owned. */
typedef struct { BITFIELDS3(unsigned char high:1, unsigned char role:3, unsigned char low:4) } RoleByte;
typedef struct { BITFIELDS4(unsigned char high:5, unsigned char flag2:1, unsigned char flag1:1, unsigned char low:1) } PhaseFlags;
typedef union {
    unsigned int word;
    struct { RoleByte role; unsigned char unused; PhaseFlags flags; unsigned char tail; } bytes;
} SlotHeader;
typedef struct { SlotHeader header; unsigned char remaining[0xA38]; } SlotView;

extern char g_pcbSyncPhasePerPcb[4];

extern float PCBCheckRecv_bss_806D11C0[2];
/* Two adjacent timestamp words: high at 11C8, low at 11CC. */
extern long long PCBCheckRecv_bss_806D11C8;
extern long long OSGetTime(void);
extern long long __div2i(long long numerator, long long denominator);
extern const float lbl_806D3158, lbl_806D315C, lbl_806D3160;
extern const float lbl_806D3164, lbl_806D3168;

#pragma exceptions on
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
    float elapsed = (float)__div2i(OSGetTime() - PCBCheckRecv_bss_806D11C8,
        (long long)((*(volatile unsigned int *)0x800000F8 >> 2) / 1000));
    elapsed /= lbl_806D3158;
    if (elapsed <= lbl_806D315C) {
        PCBCheckRecv_bss_806D11C0[1] = lbl_806D3160;
        return 1;
    }
    slot = slots = PCBCheckRecv_bss_805A6154;
    phase = phases = g_pcbSyncPhasePerPcb;
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
        for (i = 0; i < 4; ++i, ++slots, ++out) {
            if (roleCount >= 2) {
                if (slots->header.bytes.role.role == 5) out[4] = first + 2;
            } else {
                if (slots->header.bytes.role.role == 5) out[4] = 0;
            }
        }
        PCBCheckRecv_bss_806D11C8 = OSGetTime();
    }
    {
        unsigned char idle = 1;
        if (roleCount > 0) {
            float timer;
            PCBCheckRecv_bss_806D11C0[1] -= lbl_806D3164;
            if (truncate) PCBCheckRecv_bss_806D11C0[1] = (int)PCBCheckRecv_bss_806D11C0[1];
            if (reset) PCBCheckRecv_bss_806D11C0[1] = lbl_806D3168;
            timer = PCBCheckRecv_bss_806D11C0[1];
            {
                char *cursor = phases;
                unsigned char *out = g_pcbSyncTable;
                for (i = 0; i < 4; ++i, ++cursor, out += 4) {
                    if (*cursor == 5) {
                        *(float *)(out + 8) = timer;
                        idle = 0;
                    }
                }
            }
        }
        if (idle) PCBCheckRecv_bss_806D11C0[1] = lbl_806D3168;
    }
    return 1;
}
#pragma exceptions off
#undef OSGetTime
#undef PhaseFlags
#undef RoleByte
#undef SlotHeader
#undef SlotView
#undef __div2i
#undef g_pcbSyncPhasePerPcb
#undef PCBCheckRecv_bss_806D11C0
#undef PCBCheckRecv_bss_806D11C8
#undef lbl_806D3158
#undef lbl_806D315C
#undef lbl_806D3160
#undef lbl_806D3164
#undef lbl_806D3168
#undef PCBCheckRecv_bss_805A6154

/* ==== PCBCommPhase1.c ==== */
#define PhaseFlags PhaseFlags_p2
#define RoleByte RoleByte_p2
#define SlotHeader SlotHeader_p2
#define SlotView SlotView_p2
#define g_pcbSyncPhasePerPcb g_pcbSyncPhasePerPcb_p2
#define PCBCheckRecv_bss_806D11C0 lbl_806D11C0_p2
#define lbl_806D3164 lbl_806D3164_p2
#define lbl_806D316C lbl_806D316C_p2
#define PCBCheckRecv_bss_805A6154 ((SlotView *)PCBCheckRecv_bss_805A6154)
#pragma exceptions off
#pragma use_lmw_stmw off
/* Observed byte/word overlays only; all storage remains externally owned. */
typedef struct {
    BITFIELDS3(unsigned char unused7:1, unsigned char role:3, unsigned char unusedLow:4)
} RoleByte;
typedef struct {
    BITFIELDS4(unsigned char high:5, unsigned char flag2:1, unsigned char flag1:1, unsigned char low:1)
} PhaseFlags;
typedef union {
    unsigned int word;
    struct { RoleByte role; unsigned char unused1; PhaseFlags flags; unsigned char unused3; } bytes;
} SlotHeader;
typedef struct { SlotHeader header; unsigned char remaining[0xA38]; } SlotView;

extern char g_pcbSyncPhasePerPcb[4];

extern float PCBCheckRecv_bss_806D11C0[2];
extern const float lbl_806D3164;
extern const float lbl_806D316C;

#pragma exceptions on
int PCBComm_UpdateSyncPhase1(void)
{
    SlotView *slots;
    SlotView *slot;
    char *phase;
    char *phases;
    int roleCount = 0;
    int sceneCount = 0;
    int first = -1;
    unsigned char truncate = 0;
    unsigned char reset = 0;
    int i;
    slot = slots = PCBCheckRecv_bss_805A6154;
    phase = phases = g_pcbSyncPhasePerPcb;
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
        unsigned char *out = g_pcbSyncTable;
        for (i = 0; i < 4; ++i, ++slots, ++out) {
            if (roleCount >= 2) {
                if (slots->header.bytes.role.role == 1) out[4] = first + 2;
            } else {
                if (slots->header.bytes.role.role == 1) out[4] = 0;
            }
        }
    }
    {
        unsigned char idle = 1;
        if (roleCount > 0) {
            float timer;
            PCBCheckRecv_bss_806D11C0[0] -= lbl_806D3164;
            if (truncate) PCBCheckRecv_bss_806D11C0[0] = (int)PCBCheckRecv_bss_806D11C0[0];
            if (reset) PCBCheckRecv_bss_806D11C0[0] = lbl_806D316C;
            timer = PCBCheckRecv_bss_806D11C0[0];
            {
                unsigned char *out = g_pcbSyncTable;
                phase = phases;
                for (i = 0; i < 4; ++i, ++phase, out += 4) {
                    if (*phase == 1) {
                        *(float *)(out + 8) = timer;
                        idle = 0;
                    }
                }
            }
        }
        if (idle) PCBCheckRecv_bss_806D11C0[0] = lbl_806D316C;
    }
    return 1;
}
#pragma exceptions off
#undef PhaseFlags
#undef RoleByte
#undef SlotHeader
#undef SlotView
#undef g_pcbSyncPhasePerPcb
#undef PCBCheckRecv_bss_806D11C0
#undef lbl_806D3164
#undef lbl_806D316C
#undef PCBCheckRecv_bss_805A6154

/* ==== CommBroadcast.c ==== */
#define CommBroadcast_CurrentEntry CommBroadcast_CurrentEntry_p3
#define CommEntry CommEntry_p3
#define CommRankNibbles CommRankNibbles_p3
#define g_isCommHost g_isCommHost_p3
#define g_ringReadIdx g_ringReadIdx_p3
#define g_ringWriteIdx lbl_806D11A0_p3
#define g_ringBufferBase ((CommEntry *)g_ringBufferBase)
#pragma exceptions off
#pragma use_lmw_stmw off
/* Per-kart lap and rank bytes in the current ring-buffer entry (see
 * RingBuffer_Getters.c for the entry layout). The host reads its local
 * entry 0; clients read the entry at g_ringReadIdx. */

typedef struct CommRankNibbles {
    BITFIELDS2(signed char kart0:4, signed char kart1:4)
    BITFIELDS2(signed char kart2:4, signed char kart3:4)
} CommRankNibbles;

typedef struct CommEntry {
    unsigned char pad00[0xd4];
    CommRankNibbles rank; /* 0xD4 */
    unsigned char lap[4]; /* 0xD6 */
    unsigned char padDA[2];
} CommEntry;

extern unsigned char g_isCommHost;
extern int g_ringReadIdx;
extern int g_ringWriteIdx;

static inline CommEntry *CommBroadcast_CurrentEntry(void)
{
    if (g_isCommHost == 1) {
        return g_ringBufferBase;
    }
    return &g_ringBufferBase[g_ringReadIdx];
}

unsigned char CommBroadcast_GetKartLap(int kart)
{
    return CommBroadcast_CurrentEntry()->lap[kart];
}

void CommBroadcast_SetKartLap(int kart, unsigned char lap)
{
    CommBroadcast_CurrentEntry()->lap[kart] = lap;
}

int CommBroadcast_GetKartRankNibble(int kart)
{
    CommEntry *entry = CommBroadcast_CurrentEntry();

    if (kart == 0) {
        return entry->rank.kart0;
    }
    if (kart == 1) {
        return entry->rank.kart1;
    }
    if (kart == 2) {
        return entry->rank.kart2;
    }
    return entry->rank.kart3;
}

void CommBroadcast_SetKartRankNibble(int kart, int rank)
{
    CommEntry *entry = CommBroadcast_CurrentEntry();

    if (kart == 0) {
        entry->rank.kart0 = (signed char)rank;
    }
    if (kart == 1) {
        entry->rank.kart1 = (signed char)rank;
    }
    if (kart == 2) {
        entry->rank.kart2 = (signed char)rank;
    }
    if (kart == 3) {
        entry->rank.kart3 = (signed char)rank;
    }
}

unsigned char CommBroadcast_ScanForMySyncMatch(void)
{
    unsigned char i = 0;

    while (g_ringWriteIdx != (g_ringReadIdx + i) % 64) {
        i++;
    }
    return i;
}
#undef CommBroadcast_CurrentEntry
#undef CommEntry
#undef CommRankNibbles
#undef g_isCommHost
#undef g_ringReadIdx
#undef g_ringWriteIdx
#undef g_ringBufferBase

/* ==== BootPCBCheck.cpp ==== */
C_REGION_END
#pragma cplusplus on
#define BootInput BootInput_p4
#define DisplayContext_Flush DisplayContext_Flush_p4
#define DrawText DrawText_p4
#define GetInputManager GetInputManager_p4
#define InputMgr_GetPlayer InputMgr_GetPlayer_p4
#define PcbSlot PcbSlot_p4
#define ReadyFlags ReadyFlags_p4
#define PCBCheckRecv_bss_806D11B8 lbl_806D11B8_p4
#define PCBCheckRecv_bss_806D11BC lbl_806D11BC_p4
#define lbl_806D315C lbl_806D315C_p4
#define lbl_806D3170 lbl_806D3170_p4
#define lbl_806D3178 lbl_806D3178_p4
#define PCBCheckRecv_bss_805A6154 ((PcbSlot *)PCBCheckRecv_bss_805A6154)
#pragma exceptions on
#pragma use_lmw_stmw off
/* Boot-time PCB link check screen, 0x80084A84..0x80084D98. */

struct BootInput {
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual bool IsPressed(int mask);
};

typedef struct {
    BITFIELDS5(unsigned char disabled:1, unsigned char unused6:1, unsigned char ready:1, unsigned char flag4:1, unsigned char unusedLow:4)
} ReadyFlags;

typedef struct PcbSlot {
    unsigned char pad_00[0xA2C];
    void *primary;
    void *secondary;
    ReadyFlags flags;
    unsigned char pad_A35[7];
} PcbSlot;

extern "C" {

extern void *PCBCheckRecv_bss_806D11B8;
extern int PCBCheckRecv_bss_806D11BC;
extern const float lbl_806D315C;

extern const char lbl_806D3170[5];
extern const char lbl_806D3178[5];
void DrawText(void *ctx, int x, int y, int color, float scale, const char *fmt, ...);
void DisplayContext_Flush(void *ctx);
void *GetInputManager();
BootInput *InputMgr_GetPlayer(void *, int);
}

extern "C" int BootPCBCheck_Display(void)
{
    int i;

    if (PCBCheckRecv_bss_806D11B8 == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (PCBCheckRecv_bss_805A6154[i].flags.disabled == 1) {
            DrawText(PCBCheckRecv_bss_806D11B8, 0x54, (i + 1) * 0x18, 7, lbl_806D315C, lbl_80312244, i + 1);
        } else if (PCBCheckRecv_bss_805A6154[i].primary != 0 && PCBCheckRecv_bss_805A6154[i].secondary != 0) {
            DrawText(PCBCheckRecv_bss_806D11B8, 0x54, (i + 1) * 0x18, 7, lbl_806D315C, lbl_80312244, i + 1);
        } else {
            DrawText(PCBCheckRecv_bss_806D11B8, 0x54, (i + 1) * 0x18, 7, lbl_806D315C, lbl_80312254, i + 1);
        }
    }
    DrawText(PCBCheckRecv_bss_806D11B8, 0xE, 0x18, 7, lbl_806D315C, lbl_806D3170);
    DrawText(PCBCheckRecv_bss_806D11B8, 0x24C, 0x18, 7, lbl_806D315C, lbl_806D3178, PCBCheckRecv_bss_806D11BC / 60);
    DisplayContext_Flush(PCBCheckRecv_bss_806D11B8);
    return 1;
}

extern "C" int BootPCBCheck_Poll(void)
{
    BootInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    int n = 0;
    int i;

    if (PCBCheckRecv_bss_806D11B8 == 0) {
        return 0;
    }
    if (PCBCheckRecv_bss_806D11BC <= 0) {
        return 0;
    }
    PCBCheckRecv_bss_806D11BC--;
    for (i = 0; i < 4; i++) {
        if (PCBCheckRecv_bss_805A6154[i].flags.disabled == 1) {
            n++;
        } else if (PCBCheckRecv_bss_805A6154[i].flags.ready == 1 && PCBCheckRecv_bss_805A6154[i].flags.flag4 == 1) {
            n++;
        }
    }
    if (n == 4) {
        PCBCheckRecv_bss_806D11BC = 0;
    }
    if (input->IsPressed(0x2000) && input->IsPressed(0x400)) {
        PCBCheckRecv_bss_806D11BC = 0;
    }
    return 1;
}
#undef BootInput
#undef DisplayContext_Flush
#undef DrawText
#undef GetInputManager
#undef InputMgr_GetPlayer
#undef PcbSlot
#undef ReadyFlags
#undef PCBCheckRecv_bss_806D11B8
#undef PCBCheckRecv_bss_806D11BC
#undef lbl_806D315C
#undef lbl_806D3170
#undef lbl_806D3178
#undef PCBCheckRecv_bss_805A6154
#pragma cplusplus off
C_REGION_BEGIN

/* ==== BootNotice_CheckEnterCondition.c ==== */
#define SetSyncTarget SetSyncTarget_p5
#define fn_801DB68C fn_801DB68C_p5
#define PCBCheckRecv_bss_806D11B8 lbl_806D11B8_p5
#define lbl_806D1880 lbl_806D1880_p5
#pragma exceptions on
#pragma use_lmw_stmw off
/*
 * BootNotice_CheckEnterCondition @ 0x80084D98 (size 0x60).
 *
 * Gate check called from BootDispatcher (0x8002F0C0) before entering the
 * 599-frame "notice" loop (4-cabinet PCB linkup notice). Returns 1 to
 * authorize entry, 0 to skip.
 *
 * Behaviour:
 *   - if (g_BootNoticeArm == 0) return 0;            (PCBCheckRecv_bss_806D11B8)
 *   - if (g_BootNoticeOverlay == 0)                  (lbl_806D1880)
 *         fn_801DB68C(g_BootNoticeOverlay, 1);       (cleanup, value is 0)
 *         g_BootNoticeOverlay = 0;                   (dead store: emitted)
 *   - g_BootNoticeArm = 0;
 *   - SetSyncTarget(2);
 *   - return 1;
 *
 * extab/extabindex entries are present in the target (Large Frame, no GPR
 * save, header word 0x00080000). Emitted via #pragma exceptions on/reset so
 * CW auto-generates them.
 */

extern unsigned int PCBCheckRecv_bss_806D11B8;   // .sbss size 0x4: notice-arm flag
extern unsigned int lbl_806D1880;   // .sbss size 0x8: notice overlay alloc slot
extern void fn_801DB68C(unsigned int p, int q);
extern void SetSyncTarget(int target);

#pragma exceptions on
int BootNotice_CheckEnterCondition(void) {
    if (PCBCheckRecv_bss_806D11B8 == 0) {
        return 0;
    }
    if (lbl_806D1880 == 0) {
        fn_801DB68C(lbl_806D1880, 1);
        lbl_806D1880 = 0;
    }
    PCBCheckRecv_bss_806D11B8 = 0;
    SetSyncTarget(2);
    return 1;
}
#pragma exceptions on
#undef SetSyncTarget
#undef fn_801DB68C
#undef PCBCheckRecv_bss_806D11B8
#undef lbl_806D1880

/* ==== BootPCBCheck_Init.c ==== */
#define Alloc Alloc_p6
#define DisplayContext_Init DisplayContext_Init_p6
#define MemoryManager_TimedFree MemoryManager_TimedFree_p6
#define PCBCheck_StateSet PCBCheck_StateSet_p6
#define SetSyncTarget SetSyncTarget_p6
#define g_pcbListener g_pcbListener_p6
#define PCBCheckRecv_bss_806D11B8 lbl_806D11B8_p6
#define PCBCheckRecv_bss_806D11BC lbl_806D11BC_p6
#define lbl_806D1880 lbl_806D1880_p6
#pragma exceptions off
#pragma use_lmw_stmw off
/*
 * BootPCBCheck_Init @ 0x80084DF8 (size 0x90).
 *
 * Idempotent initializer for the 4-cabinet PCB-link "boot PCB check" task.
 * Lazily allocates a 0xD8-byte state buffer, runs DisplayContext_Init on it,
 * publishes the pointer to two .sbss slots, registers the polling callback
 * (PCBCheck_StateSet) against g_pcbListener, raises the sync target to 0x36
 * and arms the 0xE10 (3600-frame / 60 s) wait counter.
 *
 *   - if (g_BootPCBCheckArm != 0) return 0;            (PCBCheckRecv_bss_806D11B8 -- gate)
 *   - if (g_BootPCBCheckBuf == 0) {                    (lbl_806D1880)
 *         buf = Alloc(0xD8);
 *         if (buf != 0) DisplayContext_Init();
 *         g_BootPCBCheckBuf = buf;
 *     }
 *   - g_BootPCBCheckArm = g_BootPCBCheckBuf;
 *   - if (g_BootPCBCheckBuf == 0) return 0;
 *   - SetSyncTarget(0x36);
 *   - PCBCheck_StateSet(g_pcbListener);
 *   - g_BootPCBCheckTimer = 0xE10;
 *   - return 1;
 *
 * The target carries a 24-byte extab with a DELETEPOINTER cleanup for r31
 * (the freshly Alloc'd buffer) calling MemoryManager_TimedFree (=
 * MemoryManager_TimedFree). The cleanup range covers PC=0..0x44 -- through the
 * `bl PCBCheck_StateSet` call, so if any of Alloc / DisplayContext_Init /
 * SetSyncTarget / PCBCheck_StateSet throws, the just-allocated buffer is
 * freed before re-raising. CW 1.3.2 has no concise way to express this
 * scoped-pointer C++ idiom in C; emit the extab/extabindex manually via
 * the project's `.extab_user` / `.extabindex_user` pipeline (mirrors
 * ServiceMenu.c / OpenFullServiceMenu).
 */

extern void *Alloc(int size);
extern void DisplayContext_Init(REG_ARGS1(void *self));
extern void SetSyncTarget(int target);
extern void PCBCheck_StateSet(unsigned int listener);
extern void MemoryManager_TimedFree(void *);

extern unsigned int PCBCheckRecv_bss_806D11B8;   // .sbss size 0x4: gate (init done flag, holds buf ptr)
extern unsigned int PCBCheckRecv_bss_806D11BC;   // .sbss size 0x4: 60s wait counter
extern unsigned int lbl_806D1880;   // .sbss size 0x8: allocated state buffer ptr
extern unsigned int g_pcbListener;  // .sbss size 0x4: PCB listener handle

/* --- forward decl --- */
int BootPCBCheck_Init(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) ---
 * Mirror of target @etb_80008D5C: size 0x18 with a single DELETEPOINTER
 * action covering up to PC=0x44 (the bl PCBCheck_StateSet site).
 *
 * Layout (six 4-byte words):
 *   0x08080000   header (1 PC range, r31 saved-GPR range, large frame)
 *   0x00000044   PC end (offset from function start)
 *   0x00000010   action offset
 *   0x00000000   PC range terminator
 *   0x8A80001F   action: DELETEPOINTER r31 + end bit
 *   <dtor>       destructor function pointer
 */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    void *f5;
} extab_BootPCBCheck_Init = {
    0x08080000, 0x00000044, 0x00000010, 0x00000000, 0x8A80001F, (void *)&MemoryManager_TimedFree
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_BootPCBCheck_Init = {
    (void *)&BootPCBCheck_Init, 0x00000090, (void *)&extab_BootPCBCheck_Init
};

int BootPCBCheck_Init(void) {
    void *buf;
    if (PCBCheckRecv_bss_806D11B8 != 0) {
        return 0;
    }
    buf = (void *)lbl_806D1880;
    if (lbl_806D1880 == 0) {
        buf = Alloc(0xD8);
        if (buf != 0) {
            DisplayContext_Init(REG_ARGS1(buf)); /* r3 still holds buf */
        }
        lbl_806D1880 = (unsigned int)buf;
    }
    PCBCheckRecv_bss_806D11B8 = lbl_806D1880;
    if (lbl_806D1880 == 0) {
        return 0;
    }
    SetSyncTarget(0x36);
    PCBCheck_StateSet(g_pcbListener);
    PCBCheckRecv_bss_806D11BC = 0xE10;
    return 1;
}
#undef Alloc
#undef DisplayContext_Init
#undef MemoryManager_TimedFree
#undef PCBCheck_StateSet
#undef SetSyncTarget
#undef g_pcbListener
#undef PCBCheckRecv_bss_806D11B8
#undef PCBCheckRecv_bss_806D11BC
#undef lbl_806D1880

/* ==== SetPcbScratchFlag_806d11a4.c ==== */
#define lbl_806D11A4 lbl_806D11A4_p7
#pragma exceptions off
#pragma use_lmw_stmw off
extern unsigned int lbl_806D11A4;

void SetPcbScratchFlag_806d11a4(void) {
    lbl_806D11A4 = 1;
}
#undef lbl_806D11A4

/* ==== PCBCommSnapshot.c ==== */
#define SnapshotHeader SnapshotHeader_p8
#define SnapshotSlot SnapshotSlot_p8
#define SnapshotTrigger SnapshotTrigger_p8
#define card_pack card_pack_p8
#define g_isCommHost g_isCommHost_p8
#define g_localPcbRole g_localPcbRole_p8
#define g_myPcbId g_myPcbId_p8
#define g_playerData g_playerData_p8
#define PCBCheckRecv_bss_805A6154 ((SnapshotSlot *)PCBCheckRecv_bss_805A6154)
#pragma exceptions on
#pragma use_lmw_stmw off
/* Observed communication-slot bytes only; all storage is external. */
typedef struct SnapshotHeader {
    BITFIELDS4(unsigned char reserved7:1, unsigned char role:3, unsigned char ready:1, unsigned char reserved0:3)
} SnapshotHeader;

typedef struct SnapshotTrigger {
    BITFIELDS3(unsigned char upper:4, unsigned char pending:1, unsigned char lower:3)
} SnapshotTrigger;

typedef struct SnapshotSlot {
    SnapshotHeader header;
    unsigned char pad1[0xA33];
    SnapshotTrigger trigger;
    unsigned char tail[7];
} SnapshotSlot;

extern int g_localPcbRole, g_myPcbId;
extern unsigned char g_isCommHost;
extern unsigned char g_playerData[0x1DC];

/* The caller supplies an extra mode argument; the observed callee ignores it. */
extern void* card_pack(void* source, void* destination, int mode);

int PCBComm_PackAndTriggerCardSnapshot(void)
{
    if (g_localPcbRole == 0) return 0;
    card_pack(g_playerData, PCBComm_PackAndTriggerCardSnapshot_bss_805A8A44[g_myPcbId - 1], 1);
    if (g_isCommHost == 0) {
        SnapshotSlot* slot = PCBCheckRecv_bss_805A6154;
        int local = g_myPcbId - 1;
        int role = g_localPcbRole;
        int i;
        for (i = 0; i < 4; ++i, ++slot) {
            if (i != local && slot->header.role == role && slot->header.ready == 1)
                slot->trigger.pending = 1;
        }
    }
    return 1;
}
#undef SnapshotHeader
#undef SnapshotSlot
#undef SnapshotTrigger
#undef card_pack
#undef g_isCommHost
#undef g_localPcbRole
#undef g_myPcbId
#undef g_playerData
#undef PCBCheckRecv_bss_805A6154

/* ==== ResetIOPorts.c ==== */
#define GetDisplayContext GetDisplayContext_p9
#define g_localPcbRole g_localPcbRole_p9
#define g_myPcbId g_myPcbId_p9
#define PCBCheckRecv_bss_806D11B0 lbl_806D11B0_p9
#define PCBCheckRecv_bss_805A6154 ((ResetIOPort *)PCBCheckRecv_bss_805A6154)
#pragma exceptions off
#pragma use_lmw_stmw off
/* ResetIOPorts @ 0x80084FF0, 192 bytes. */
#include "game/ResetIOPorts_private.h"

extern int g_localPcbRole;
extern int g_myPcbId;
extern void *PCBCheckRecv_bss_806D11B0;
extern void *GetDisplayContext(int pcbIndex);

#pragma exceptions on
int ResetIOPorts(void) {
    int role;
    ResetIOPort *port;
    int i;

    if (g_localPcbRole == 0) {
        return 0;
    }
    PCBCheckRecv_bss_806D11B0 = GetDisplayContext(g_myPcbId - 1);
    role = g_localPcbRole;
    port = PCBCheckRecv_bss_805A6154;
    for (i = 0; i < 4; i++, port++) {
        if (((port->header >> 4) & 7) == role) {
            port->status = 0x40;
        }
    }
    return 1;
}
#pragma exceptions off
#undef GetDisplayContext
#undef g_localPcbRole
#undef g_myPcbId
#undef PCBCheckRecv_bss_806D11B0
#undef PCBCheckRecv_bss_805A6154

/* ==== PcbSyncTable_Ptr.c ==== */
#pragma exceptions off
#pragma use_lmw_stmw off
void *PcbSyncTable_Ptr(void)
{
    return g_pcbSyncTable;
}

/* ==== SyncSlot.c ==== */
#define g_isCommHost g_isCommHost_p11
#define g_localPcbRole g_localPcbRole_p11
#define memset memset_p11
#define PCBCheckRecv_bss_805AC258 ((unsigned char *)PCBCheckRecv_bss_805AC258)
#pragma exceptions on
#pragma use_lmw_stmw off
/*
 * msg_type 4 sync slot helpers.
 *
 * Two 0x1C-byte slots sit back-to-back at PCBCheckRecv_bss_805AC258 (recv) and
 * PCBCheckRecv_bss_805AC258 + 0x1C (host send).
 */

extern unsigned char g_isCommHost;
extern int g_localPcbRole;

extern void memset(void *dst, int value, unsigned long size);

void *SyncSlot_GetHostSend(void) {
    unsigned char *p;
    if (g_isCommHost == 0) return (void *)0;
    p = &PCBCheckRecv_bss_805AC258[0x1c];
    if (g_localPcbRole != 0) return p;
    return (void *)0;
}

void *SyncSlot_GetRecv(void) {
    return PCBCheckRecv_bss_805AC258;
}

void SyncSlot_Reset(void) {
    int i;

    for (i = 0; i < 2; i++) {
        memset(PCBCheckRecv_bss_805AC258 + i * 0x1c, 0, 0x1c);
    }
}
#undef g_isCommHost
#undef g_localPcbRole
#undef memset
#undef PCBCheckRecv_bss_805AC258

/* ==== CommBroadcast_ClearTable.c ==== */
#define CommEntry CommEntry_p12
#define g_ringReadIdx g_ringReadIdx_p12
#define g_ringWriteIdx lbl_806D11A0_p12
#define memset memset_p12
#define g_ringBufferBase ((CommEntry *)g_ringBufferBase)
#pragma exceptions on
#pragma use_lmw_stmw off
/* Clear all 64 ring-buffer entries and rewind the indices. */
typedef struct CommEntry {
    unsigned char data[0xdc];
} CommEntry;

extern int g_ringReadIdx;
extern int g_ringWriteIdx;
extern void *memset(void *dst, int c, unsigned long n);

void CommBroadcast_ClearTable(void)
{
    int i;

    g_ringWriteIdx = 1;
    g_ringReadIdx = 0;
    for (i = 0; i < 0x40; i++) {
        memset(&g_ringBufferBase[i], 0, sizeof(CommEntry));
    }
}
#undef CommEntry
#undef g_ringReadIdx
#undef g_ringWriteIdx
#undef memset
#undef g_ringBufferBase

/* ==== PcbSlotReset.c ==== */
#define ResetScratchSlot ResetScratchSlot_p13
#define memset memset_p13
#define PCBCheckRecv_bss_805A6154 ((PcbScratchSlot *)PCBCheckRecv_bss_805A6154)
#pragma exceptions on
#pragma use_lmw_stmw off
#include "game/PcbSlotReset_private.h"

extern void *memset(void *dest, int value, unsigned long size);

static inline void ResetScratchSlot(PcbScratchSlot *slot, int index)
{
    unsigned char *cursor;
    int row;
    if (index < 0 || index >= 4) return;
    if (slot->flags.local == 1) {
        slot->readIndex = 0;
        slot->writeIndex = 2;
    } else {
        slot->readIndex = 0;
        slot->writeIndex = 1;
    }
    for (row = 0, cursor = (unsigned char *)slot; row < 64; ++row, cursor += 0x28) {
        memset(cursor + 0x2C, 0, 0x28);
    }
}

void PcbSlot_ResetScratchAreas(void)
{
    int index;
    for (index = 0; index < 4; ++index) {
        ResetScratchSlot(&PCBCheckRecv_bss_805A6154[index], index);
    }
}
#undef ResetScratchSlot
#undef memset
#undef PCBCheckRecv_bss_805A6154

/* ==== RingBuffer_Getters.c ==== */
#define g_isCommHost g_isCommHost_p14
#define g_ringReadIdx g_ringReadIdx_p14
#define g_ringBufferBase ((unsigned char *)g_ringBufferBase)
#pragma exceptions off
#pragma use_lmw_stmw off
/*
 * Ring buffer slot accessors (PCB inter-host communication).
 *
 * Layout per ring entry (0xdc bytes):
 *   +0x00 .. +0x9F : 4 KartSlot entries (0x28 bytes each)
 *   +0xA0 .. +0xFF : 4 RankSlot entries (0x18 bytes each)
 *
 * Host writes into the local ring (read_idx == 0 view).
 * Clients index into a 16-entry ring at g_ringBufferBase + g_ringReadIdx * 0xdc.
 */

extern unsigned char g_isCommHost;
extern int g_ringReadIdx;

void *RingBuffer_GetRankSlot(int kartIdx) {
    if (kartIdx < 0 || kartIdx >= 4) {
        return (void *)0;
    }
    if (g_isCommHost == 1) {
        return g_ringBufferBase + kartIdx * 0x18 + 0xa0;
    }
    return g_ringBufferBase + g_ringReadIdx * 0xdc + kartIdx * 0x18 + 0xa0;
}

void *RingBuffer_GetEntryHead(void) {
    if (g_isCommHost == 1) {
        return &g_ringBufferBase[0];
    }
    return &g_ringBufferBase[g_ringReadIdx * 0xdc];
}

void *RingBuffer_GetKartSlot(int kartIdx) {
    if (kartIdx < 0 || kartIdx >= 4) {
        return (void *)0;
    }
    if (g_isCommHost == 1) {
        return &g_ringBufferBase[kartIdx * 0x28];
    }
    return &g_ringBufferBase[g_ringReadIdx * 0xdc] + kartIdx * 0x28;
}
#undef g_isCommHost
#undef g_ringReadIdx
#undef g_ringBufferBase

/* ==== PcbSlotSync.c ==== */
#define FinalReadyFlag FinalReadyFlag_p15
#define ReadyByte ReadyByte_p15
#define ReadyFlags ReadyFlags_p15
#define g_myPcbId g_myPcbId_p15
#define lbl_806D3160 lbl_806D3160_p15
#define PCBCheckRecv_bss_805A6154 ((unsigned char *)PCBCheckRecv_bss_805A6154)
#pragma exceptions off
#pragma use_lmw_stmw off
/* Observed PCB storage views; definitions remain in the existing global units. */

extern int g_myPcbId;
extern float lbl_806D3160;

void *PcbSlot_GetByIndex(int index)
{
    if (index < 0 || index >= 4) return 0;
    return PCBCheckRecv_bss_805A6154 + index * 0xA3C;
}

unsigned int PcbSlot_GetCharIdByte(int index)
{
    if (index < 0 || index >= 4) return 0;
    return (*(unsigned int *)(PCBCheckRecv_bss_805A6154 + index * 0xA3C) >> 15) & 0xFF;
}

typedef struct {
    BITFIELDS5(unsigned char disabled:1, unsigned char unused6:1, unsigned char ready:1, unsigned char flag4:1, unsigned char unusedLow:4)
} ReadyFlags;

static inline unsigned int FinalReadyFlag(const ReadyFlags *ready)
{
    return ready->flag4;
}

static inline int ReadyByte(const ReadyFlags *ready)
{
    if (ready->disabled == 1) return 0;
    if (ready->ready == 0) return 0;
    return (unsigned int)(-(int)FinalReadyFlag(ready) | (int)FinalReadyFlag(ready)) >> 31;
}

int PcbSlot_IsReadyByIndex(int index)
{
    if (index < 0 || index >= 4) return 0;
    return ReadyByte((ReadyFlags *)(PCBCheckRecv_bss_805A6154 + index * 0xA3C + 0xA34));
}

float PcbSyncTable_LookupValueByState(int state)
{
    int i;
    for (i = 0; i < 4; ++i) {
        if (g_pcbSyncTable[4 + i] == state)
            return ((float *)(g_pcbSyncTable + 8))[i];
    }
    return lbl_806D3160;
}

float PcbSyncTable_GetMyValue(void)
{
    return ((float *)(g_pcbSyncTable + 4))[g_myPcbId];
}

int PcbSyncTable_MyFlagIsSet(void)
{
    return g_pcbSyncTable[3 + g_myPcbId] != 0;
}
#undef FinalReadyFlag
#undef ReadyByte
#undef ReadyFlags
#undef g_myPcbId
#undef lbl_806D3160
#undef PCBCheckRecv_bss_805A6154

/* ==== PCBCommHostConfirm.c ==== */
#define SetLocalPcbRole SetLocalPcbRole_p16
#define g_currentSceneState g_currentSceneState_p16
#define g_isCommHost g_isCommHost_p16
#define g_myPcbId g_myPcbId_p16
#define g_pcbSyncReady g_pcbSyncReady_p16
#pragma exceptions off
#pragma use_lmw_stmw off
/* Only the observed sync bytes are viewed here; globals retain their ownership. */

extern int g_currentSceneState;
extern int g_myPcbId;
extern unsigned char g_pcbSyncReady;
extern unsigned char g_isCommHost;
extern void SetLocalPcbRole(int role);

#pragma exceptions on
int PCBComm_ConfirmHostBattle(void)
{
    int scene = g_currentSceneState;
    unsigned char *slot = g_pcbSyncTable + g_myPcbId;
    unsigned char role = slot[3];
    if (scene != 50) return 0;
    if (role == 5) return 0;
    if (g_pcbSyncReady == 0 && slot[-1] != 50) return 0;
    if (role == 0) {
        SetLocalPcbRole(0);
        g_isCommHost = 0;
    } else {
        SetLocalPcbRole(role);
        if (g_myPcbId == role - 1) g_isCommHost = 1;
        else g_isCommHost = 0;
    }
    return 1;
}

int PCBComm_ConfirmHostLobby(void)
{
    int scene = g_currentSceneState;
    unsigned char *slot = g_pcbSyncTable + g_myPcbId;
    unsigned char role = slot[3];
    if (scene != 8) return 0;
    if (role == 1) return 0;
    if (g_pcbSyncReady == 0 && slot[-1] != 8) return 0;
    if (role == 0) {
        SetLocalPcbRole(0);
        g_isCommHost = 0;
    } else {
        SetLocalPcbRole(role);
        if (g_myPcbId == role - 1) g_isCommHost = 1;
        else g_isCommHost = 0;
    }
    return 1;
}
#pragma exceptions off
#undef SetLocalPcbRole
#undef g_currentSceneState
#undef g_isCommHost
#undef g_myPcbId
#undef g_pcbSyncReady

/* ==== PcbSync_AnyPeer.c ==== */
#define g_myPcbId g_myPcbId_p17
#pragma exceptions off
#pragma use_lmw_stmw off
/* PCB sync-table peer scan, 0x80085648..0x800856CC. */

extern int g_myPcbId;

int PcbSync_AnyPeerAtState5(void)
{
    int i;
    int st;

    for (i = 0; i < 4; i++) {
        if (i != g_myPcbId - 1) {
            st = g_pcbSyncTable[4 + i];
            if (st == 5) {
                return st;
            }
        }
    }
    return 0;
}
#undef g_myPcbId

/* ==== PCBComm_PromoteToClientConfirmed.c ==== */
#define SetLocalPcbRole SetLocalPcbRole_p18
#pragma exceptions off
#pragma use_lmw_stmw off
extern void SetLocalPcbRole(int);

#pragma exceptions on
int PCBComm_PromoteToClientConfirmed(void) {
    SetLocalPcbRole(5);
    return 1;
}
#pragma exceptions off
#undef SetLocalPcbRole

/* ==== PcbSync_Counts.c ==== */
#define PcbSlot PcbSlot_p19
#define PcbSync_CountJoined PcbSync_CountJoined_p19
#define ReadyFlags ReadyFlags_p19
#define g_currentSceneState g_currentSceneState_p19
#define g_localPcbRole g_localPcbRole_p19
#define g_myPcbId g_myPcbId_p19
#define PCBCheckRecv_bss_805A6154 ((PcbSlot *)PCBCheckRecv_bss_805A6154)
#define PCBCheckRecv_bss_805AC258 ((signed char *)PCBCheckRecv_bss_805AC258)
#pragma exceptions off
#pragma use_lmw_stmw off
/* PCB sync-table and link-slot peer counters, 0x800856F4..0x80085DD8. */

typedef struct {
    BITFIELDS5(unsigned char disabled:1, unsigned char unused6:1, unsigned char ready:1, unsigned char flag4:1, unsigned char unusedLow:4)
} ReadyFlags;

typedef struct PcbSlot {
    union {
        unsigned int word;
        struct {
            BITFIELDS3(unsigned char unused7:1, unsigned char team:3, unsigned char unusedLow:4)
            unsigned char b1;
            unsigned char b2;
            BITFIELDS3(unsigned char unused3hi:6, unsigned char readyBit1:1, unsigned char unused3lo:1)
        } bits;
    } hdr;
    unsigned char pad_04[0xA30];
    ReadyFlags flags;
    unsigned char pad_A35[7];
} PcbSlot;

extern int g_myPcbId;
extern int g_localPcbRole;
extern int g_currentSceneState;

#define PCB_CHAR_ID(s) (((s)->hdr.word >> 15) & 0xFF)

#define PCB_IS_JOINED(s, i, self) ((i) == (self) || ((s)->flags.ready && (s)->flags.flag4))

int PcbSync_CountPeersAtSyncTargetPair_0_or_1(void)
{
    int n = 0;
    int i;

    for (i = 0; i < 4; i++) {
        if (g_pcbSyncTable[4 + i] == 5) {
            if (g_pcbSyncTable[i] == '1') {
                n++;
            }
            if (g_pcbSyncTable[i] == '0') {
                n++;
            }
        }
    }
    return n;
}

int PcbSync_CountPeersAtSyncTargetPair_1_or_2(void)
{
    int n = 0;
    int i;

    for (i = 0; i < 4; i++) {
        if (g_pcbSyncTable[4 + i] == 5) {
            if (g_pcbSyncTable[i] == '1') {
                n++;
            }
            if (g_pcbSyncTable[i] == '2') {
                n++;
            }
        }
    }
    return n;
}

int CountPeersInBattleWithRole(int role)
{
    int n = 0;
    int i;

    for (i = 0; i < 4; i++) {
        if (g_pcbSyncTable[i] == '2' && g_pcbSyncTable[4 + i] == role) {
            n++;
        }
    }
    return n;
}

int CountPeersWithRole(int role)
{
    int n;
    int i;

    if (role < 0) {
        role = g_localPcbRole;
    }
    if (role == 0) {
        return 1;
    }
    n = 0;
    for (i = 0; i < 4; i++) {
        if (g_pcbSyncTable[4 + i] == role) {
            n++;
        }
    }
    return n;
}

int PcbSync_AnyJoinedPcbHasReadyFlagBit1(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (PCB_IS_JOINED(&PCBCheckRecv_bss_805A6154[i], i, g_myPcbId - 1) && PCBCheckRecv_bss_805A6154[i].hdr.bits.readyBit1 == 1) {
            return 1;
        }
    }
    return 0;
}

static inline int PcbSync_CountJoined(void)
{
    int n = 0;
    int i;

    for (i = 0; i < 4; i++) {
        if (PCB_IS_JOINED(&PCBCheckRecv_bss_805A6154[i], i, g_myPcbId - 1)) {
            n++;
        }
    }
    return n;
}

int PcbSync_CountJoinedPcbsAdvancedKarts(void)
{
    int n = PcbSync_CountJoined();
    int i;

    for (i = 0; i < 4; i++) {
        if (PCB_IS_JOINED(&PCBCheckRecv_bss_805A6154[i], i, g_myPcbId - 1) && PCB_CHAR_ID(&PCBCheckRecv_bss_805A6154[i]) >= 8) {
            n--;
        }
    }
    return n;
}

int PcbSync_CountJoinedPcbs(void)
{
    int n = 0;
    int i;

    for (i = 0; i < 4; i++) {
        if (PCB_IS_JOINED(&PCBCheckRecv_bss_805A6154[i], i, g_myPcbId - 1)) {
            n++;
        }
    }
    return n;
}

int PcbSync_AllKartsInValidSelectState(void)
{
    unsigned int state;
    int i;

    if (g_localPcbRole != 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        state = PCB_CHAR_ID(&PCBCheckRecv_bss_805A6154[i]);
        if (state != 0 && state < 7 && PCBCheckRecv_bss_805A6154[i].hdr.bits.team == 0 && state != 3 && state != 5) {
            return 0;
        }
    }
    return 1;
}

int IsSyncReached(void)
{
    return PCBCheckRecv_bss_805AC258[8] == g_currentSceneState;
}

int PcbSync_AlwaysZero_Stub(void)
{
    return 0;
}
#undef PcbSlot
#undef PcbSync_CountJoined
#undef ReadyFlags
#undef g_currentSceneState
#undef g_localPcbRole
#undef g_myPcbId
#undef PCB_CHAR_ID
#undef PCB_IS_JOINED
#undef PCBCheckRecv_bss_805A6154
#undef PCBCheckRecv_bss_805AC258

/* ==== SyncSlot_ApplyCourseChoice.c ==== */
#define GetCourseSelectEntry GetCourseSelectEntry_p20
#define SetCourseParams SetCourseParams_p20
#define lbl_806CF12C lbl_806CF12C_p20
#define PCBCheckRecv_bss_805AC258 ((unsigned short *)PCBCheckRecv_bss_805AC258)
#pragma exceptions on
#pragma use_lmw_stmw off
/*
 * SyncSlot_ApplyCourseChoice
 *   Reads the sync-slot byte at PCBCheckRecv_bss_805AC258 (delivered via msg_type 4) and
 *   applies the selected cup/course/lap-flag to the local race configuration.
 *
 *   Bit layout of PCBCheckRecv_bss_805AC258 (halfword):
 *     bits[10:4] = cupId  (7-bit, fed to GetCourseSelectEntry)
 *     bit[3]     = "lap shifted" flag (passed as 4th arg to SetCourseParams)
 *
 *   The selected cupId is also cached at lbl_806CF12C for later reads.
 *
 *   Held in its own TU (separate from SyncSlot.c) because SyncSlot.c declares
 *   PCBCheckRecv_bss_805AC258 as an `unsigned char[0x38]` blob to satisfy the manual asm
 *   prologue in SyncSlot_Reset; this function needs the same address treated
 *   as halfword-aligned storage to reproduce the target's lhz/lbz access mix.
 */

extern unsigned int lbl_806CF12C;

extern int *GetCourseSelectEntry(int cupId);
extern void SetCourseParams(int arg0, int arg1, int arg2, int lapShifted);

int SyncSlot_ApplyCourseChoice(void) {
    int *entry = GetCourseSelectEntry((PCBCheckRecv_bss_805AC258[0] >> 4) & 0x7f);
    SetCourseParams(entry[0], entry[1], entry[2],
                    (((unsigned char *)PCBCheckRecv_bss_805AC258)[1] >> 3) & 1);
    lbl_806CF12C = (PCBCheckRecv_bss_805AC258[0] >> 4) & 0x7f;
    return 1;
}
#undef GetCourseSelectEntry
#undef SetCourseParams
#undef lbl_806CF12C
#undef PCBCheckRecv_bss_805AC258

/* ==== PcbDebugOverlay.c ==== */
#define DVDLoad_GetLastReadSec DVDLoad_GetLastReadSec_p21
#define DVDLoad_GetMaxReadSec DVDLoad_GetMaxReadSec_p21
#define FKTex FKTex_p21
#define OverlayText OverlayText_p21
#define PcbConnView PcbConnView_p21
#define PcbConn_GetCloseCount PcbConn_GetCloseCount_p21
#define PcbConn_GetPortCycle PcbConn_GetPortCycle_p21
#define PcbConn_GetStateName PcbConn_GetStateName_p21
#define PcbLinkFlags PcbLinkFlags_p21
#define PcbLinkSlot PcbLinkSlot_p21
#define PcbListenerView PcbListenerView_p21
#define PcbListener_GetStateName PcbListener_GetStateName_p21
#define TexMgr_Init TexMgr_Init_p21
#define TexMgr_SetTexture TexMgr_SetTexture_p21
#define fn_8011F994 fn_8011F994_p21
#define fn_801F8A34 fn_801F8A34_p21
#define fn_801F8E58 fn_801F8E58_p21
#define fn_801F93EC fn_801F93EC_p21
#define g_myPcbId g_myPcbId_p21
#define g_pcbCommEnabled g_pcbCommEnabled_p21
#define g_pcbListener g_pcbListener_p21
#define isJapanese isJapanese_p21
#define lbl_806D1191 lbl_806D1191_p21
#define lbl_806D3180 lbl_806D3180_p21
#define lbl_806D3184 lbl_806D3184_p21
#define lbl_806D3188 lbl_806D3188_p21
#define lbl_806D318C lbl_806D318C_p21
#define lbl_806D3190 lbl_806D3190_p21
#define lbl_806D3194 lbl_806D3194_p21
#define PCBCheckRecv_bss_805A6154 ((PcbLinkSlot *)PCBCheckRecv_bss_805A6154)
#pragma exceptions off
#pragma use_lmw_stmw on
/*
 * PCB link debug overlay, 0x80085E3C..0x8008604C.
 *
 * Owns the shared .rodata pool at 0x80311E38..0x803123B0, also used by
 * PcbDebugOverlay_link.cpp and other units. Keep the original pool order.
 *
 * Connection accessors preserve the original inline register lifetimes.
 */

typedef union PcbLinkFlags {
    struct {
        BITFIELDS5(unsigned char disabled:1, unsigned char reserved6:1, unsigned char ready:1, unsigned char flag4:1, unsigned char reserved3:4)
    } byte;
    struct {
        BITFIELDS3(unsigned short upper:6, unsigned short id:3, unsigned short lower:7)
    } half;
} PcbLinkFlags;

typedef struct PcbConnView {
    unsigned char pad_00[0x20];
    int field20;
    unsigned char pad_24[0x10];
    int portCycle;
    int closeCount;
} PcbConnView;

typedef struct PcbLinkSlot {
    union {
        unsigned int word;
        struct {
            BITFIELDS3(unsigned char unused7:1, unsigned char team:3, unsigned char unusedLow:4)
        } bits;
    } hdr;
    unsigned char pad_04[0xA28];
    PcbConnView *primary;
    PcbConnView *secondary;
    PcbLinkFlags flags;
    unsigned char pad_A36[2];
    signed char readIndex;
    signed char writeIndex;
    unsigned char pad_A3A[2];
} PcbLinkSlot;

typedef struct PcbListenerView {
    unsigned char pad_00[0x18];
    int port;
} PcbListenerView;

typedef struct FKTex {
    unsigned char pad_00[0x18];
    int field18;
    int pad_1C;
    int field20;
    unsigned char pad_24[0x200];
} FKTex;

extern unsigned char g_pcbCommEnabled;
extern unsigned char lbl_806D1191;
extern PcbListenerView *g_pcbListener;
extern int g_myPcbId;
extern const float lbl_806D3180;
extern const float lbl_806D3184;
extern const float lbl_806D3188;
extern const float lbl_806D318C;
extern const float lbl_806D3190;
extern const float lbl_806D3194;

extern void OverlayText(int layer, int x, int y, const char *fmt, ...);
extern const char *PcbListener_GetStateName(PcbListenerView *listener);
extern const char *PcbConn_GetStateName(PcbConnView *conn);
extern float DVDLoad_GetLastReadSec(void);
extern float DVDLoad_GetMaxReadSec(void);
extern void TexMgr_Init(FKTex *tex);
extern void TexMgr_SetTexture(FKTex *tex, const char *name, ...);
extern void fn_801F93EC(FKTex *tex, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *list, FKTex *tex, int flags);
extern int isJapanese(void);
extern void fn_8011F994(int arg);

#define PCB_CHAR_ID(s) (((s)->hdr.word >> 15) & 0xFF)

static inline int PcbConn_GetPortCycle(const PcbConnView *conn)
{
    return conn->portCycle;
}

static inline int PcbConn_GetCloseCount(const PcbConnView *conn)
{
    return conn->closeCount;
}

#pragma exceptions on
void DebugOverlay_DumpPcbState(void)
{
    PcbListenerView *listener;
    const char *secondaryName;
    int closeCount;
    int portCycle;
    PcbConnView *primary;
    PcbConnView *secondary;
    int i;
    int pending;
    int r;
    int w;

    if (g_pcbCommEnabled == 0) {
        return;
    }
    listener = g_pcbListener;
    if (listener != 0) {
        OverlayText(1, 0, 1, lbl_8031226C, g_myPcbId, PcbListener_GetStateName(listener), listener->port);
    }
    for (i = 0; i < 4; i++) {
        r = PCBCheckRecv_bss_805A6154[i].readIndex;
        w = PCBCheckRecv_bss_805A6154[i].writeIndex;
        for (pending = 0; w != r % 64; r++, pending++) {
        }
        if (PCBCheckRecv_bss_805A6154[i].flags.byte.disabled == 1) {
            OverlayText(1, 0, i + 2, lbl_80312284, PCBCheckRecv_bss_805A6154[i].flags.half.id,
                        PCBCheckRecv_bss_805A6154[i].hdr.bits.team, PCB_CHAR_ID(&PCBCheckRecv_bss_805A6154[i]), pending);
        } else {
            primary = PCBCheckRecv_bss_805A6154[i].primary;
            if (primary != 0 && (secondary = PCBCheckRecv_bss_805A6154[i].secondary) != 0) {
                closeCount = PcbConn_GetCloseCount(primary);
                portCycle = PcbConn_GetPortCycle(primary);
                secondaryName = PcbConn_GetStateName(secondary);
                OverlayText(1, 0, i + 2, lbl_803122A8, PCBCheckRecv_bss_805A6154[i].flags.half.id,
                            PcbConn_GetStateName(PCBCheckRecv_bss_805A6154[i].primary), portCycle, closeCount,
                            secondaryName, PCBCheckRecv_bss_805A6154[i].hdr.bits.team,
                            PCB_CHAR_ID(&PCBCheckRecv_bss_805A6154[i]), pending, secondary->field20);
            } else {
                OverlayText(1, 0, i + 2, lbl_803122DC, PCBCheckRecv_bss_805A6154[i].flags.half.id,
                            PcbConn_GetStateName(primary), primary->portCycle,
                            primary->closeCount, PCBCheckRecv_bss_805A6154[i].secondary);
            }
        }
    }
    OverlayText(1, 0, 7, lbl_80312308, DVDLoad_GetLastReadSec());
    OverlayText(1, 0, 8, lbl_80312320, DVDLoad_GetMaxReadSec());
}

#pragma exceptions off
#undef DVDLoad_GetLastReadSec
#undef DVDLoad_GetMaxReadSec
#undef FKTex
#undef OverlayText
#undef PcbConnView
#undef PcbConn_GetCloseCount
#undef PcbConn_GetPortCycle
#undef PcbConn_GetStateName
#undef PcbLinkFlags
#undef PcbLinkSlot
#undef PcbListenerView
#undef PcbListener_GetStateName
#undef TexMgr_Init
#undef TexMgr_SetTexture
#undef fn_8011F994
#undef fn_801F8A34
#undef fn_801F8E58
#undef fn_801F93EC
#undef g_myPcbId
#undef g_pcbCommEnabled
#undef g_pcbListener
#undef isJapanese
#undef lbl_806D1191
#undef lbl_806D3180
#undef lbl_806D3184
#undef lbl_806D3188
#undef lbl_806D318C
#undef lbl_806D3190
#undef lbl_806D3194
#undef PCB_CHAR_ID
#undef PCBCheckRecv_bss_805A6154

/* C++ parts. Every declaration of both parts comes before the first C++
 * function: MWCC emits pending weak inline copies (FKTex::~FKTex) at the
 * next declaration, and the target has it after PCBComm_Init. */
C_REGION_END
#pragma cplusplus on
/* ==== PcbDebugOverlay_link.cpp  declarations ==== */
#define TexMgr_SetTexture TexMgr_SetTexture_p22
#define fn_8011F994 fn_8011F994_p22
#define fn_801F8A34 fn_801F8A34_p22
#define fn_801F8E58 fn_801F8E58_p22
#define fn_801F93EC fn_801F93EC_p22
#define isJapanese isJapanese_p22
#define lbl_806D1191 lbl_806D1191_p22
#define lbl_806D3180 lbl_806D3180_p22
#define lbl_806D3184 lbl_806D3184_p22
#define lbl_806D3188 lbl_806D3188_p22
#define lbl_806D318C lbl_806D318C_p22
#define lbl_806D3190 lbl_806D3190_p22
#define lbl_806D3194 lbl_806D3194_p22
#define PCBCheckRecv_rodata_80311E38 ((const unsigned int *)PCBCheckRecv_rodata_80311E38)
#pragma exceptions on
#pragma use_lmw_stmw on
/* Link-error screen, 0x8008604C..0x80086170.
 * The shared string pool stays in PcbDebugOverlay.c. A single pool base
 * preserves the original references across this TU boundary.
 * FKTex's constructor and unwind destructor bridge to the existing TexMgr
 * implementation; its empty normal-path destructor is inlined away.
 */
typedef struct FKTex {
    unsigned char pad_00[0x18];
    int field18;
    int pad_1C;
    int field20;
    unsigned char pad_24[0x200];
    FKTex();
    ~FKTex() {}
} FKTex;

extern "C" {
extern unsigned char lbl_806D1191;

extern const float lbl_806D3180;
extern const float lbl_806D3184;
extern const float lbl_806D3188;
extern const float lbl_806D318C;
extern const float lbl_806D3190;
extern const float lbl_806D3194;

extern void TexMgr_SetTexture(FKTex *tex, const char *name, ...);
extern void fn_801F93EC(FKTex *tex, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *list, FKTex *tex, int flags);
extern int isJapanese(void);
extern void fn_8011F994(int arg);

}
#undef TexMgr_SetTexture
#undef fn_8011F994
#undef fn_801F8A34
#undef fn_801F8E58
#undef fn_801F93EC
#undef isJapanese
#undef lbl_806D1191
#undef lbl_806D3180
#undef lbl_806D3184
#undef lbl_806D3188
#undef lbl_806D318C
#undef lbl_806D3190
#undef lbl_806D3194
#undef PCBCheckRecv_rodata_80311E38
/* ==== PCBCommLifecycle.cpp  declarations ==== */
#define OSGetTick OSGetTick_p23
#define OSGetTime OSGetTime_p23
#define PCBCheck_ProcessLinks PCBCheck_ProcessLinks_p23
#define PCBCheck_StateSet PCBCheck_StateSet_p23
#define PcbConn_Close PcbConn_Close_p23
#define PcbConn_RecycleIfOver PcbConn_RecycleIfOver_p23
#define PcbIdToIp_GetCached PcbIdToIp_GetCached_p23
#define PcbListener_Dtor PcbListener_Dtor_p23
#define PcbListener_TakeAcceptedSocket PcbListener_TakeAcceptedSocket_p23
#define Profiler_RecordFrame Profiler_RecordFrame_p23
#define TCPConn_Close TCPConn_Close_p23
#define TCPConn_Init TCPConn_Init_p23
#define TCPListen_Poll TCPListen_Poll_p23
#define g_confirmFlag g_confirmFlag_p23
#define g_gameMode g_gameMode_p23
#define g_isCommHost g_isCommHost_p23
#define g_myPcbId g_myPcbId_p23
#define g_pcbCommEnabled g_pcbCommEnabled_p23
#define g_pcbListener g_pcbListener_p23
#define g_pcbSyncPhasePerPcb g_pcbSyncPhasePerPcb_p23
#define g_pcbSyncReady g_pcbSyncReady_p23
#define g_ringReadIdx g_ringReadIdx_p23
#define lbl_80598A60 lbl_80598A60_p23
#define PCBCheckRecv_data_806CEFC8 lbl_806CEFC8_p23
#define PCBCheckRecv_bss_806D1188 lbl_806D1188_p23
#define lbl_806D1191 lbl_806D1191_p23
#define lbl_806D1193 lbl_806D1193_p23
#define g_ringWriteIdx lbl_806D11A0_p23
#define lbl_806D11A4 lbl_806D11A4_p23
#define lbl_806D11A8 lbl_806D11A8_p23
#define PCBComm_Init_bss_806D11AC lbl_806D11AC_p23
#define PCBCheckRecv_bss_806D11B0 lbl_806D11B0_p23
#define PCBCheckRecv_bss_806D11C0 lbl_806D11C0_p23
#define PCBCheckRecv_bss_806D11C8 lbl_806D11C8_p23
#define lbl_806D3168 lbl_806D3168_p23
#define lbl_806D316C lbl_806D316C_p23
#define lbl_806D3198 lbl_806D3198_p23
#define memset memset_p23
#define g_out ((LifecycleConn **)PCBCheck_ProcessLinks_bss_805A6134)
#define g_in ((LifecycleConn **)lbl_805A6144)
#define g_slots ((Slot *)PCBCheckRecv_bss_805A6154)
#define g_ring g_ringBufferBase
#define g_snaps PCBCheckRecv_bss_805AC258
#define g_pcbSyncTable (*(Sync *)g_pcbSyncTable)
#pragma exceptions on
#pragma use_lmw_stmw on
/* Observed PCB storage only. Allocation types are opaque external lifetimes. */

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
struct RoleByte { BITFIELDS3(u8 high:1, u8 role:3, u8 low:4) };
union PacketHead {
    u32 word;
    struct { RoleByte role; u8 remaining[3]; } bytes;
};
union SlotFlags {
    u16 half;
    struct { BITFIELDS4(u16 local:1, u16 reserved:5, u16 id:3, u16 blocks:7) } ids;
    struct {
        BITFIELDS7(u8 local:1, u8 idHigh:1, u8 tx:1, u8 rx:1, u8 card:1, u8 ack:1, u8 low:2)
        BITFIELDS2(u8 idLow:1, u8 blocks:7)
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
extern u8 lbl_80598A60[0x2A];
extern u8 g_pcbCommEnabled, lbl_806D1191, g_pcbSyncReady;
extern u8 PCBCheckRecv_data_806CEFC8, lbl_806D1193, g_confirmFlag, PCBComm_Init_bss_806D11AC;
extern u8 g_isCommHost;
extern int g_gameMode, g_myPcbId, g_ringReadIdx, g_ringWriteIdx;
extern u32 PCBCheckRecv_bss_806D1188, lbl_806D11A4, lbl_806D11A8;
extern void *PCBCheckRecv_bss_806D11B0;
extern LifecycleListener *g_pcbListener;
extern float PCBCheckRecv_bss_806D11C0[2];
extern long long PCBCheckRecv_bss_806D11C8;
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
static inline void SetSlotId(Slot *slot, int id) {
    slot->flags.ids.id = id;
}
static inline void ClearPackets(Slot *slot) {
    u8 *cursor;
    int count = 0;
    cursor = (u8 *)slot;
    do {
        memset(cursor + 0x2C, 0, 0x28);
        ++count;
        cursor += 0x28;
    } while (count < 64);
}
static inline void ClearRing(u8 *&cursor) {
    int count = 0;
    do {
        memset(cursor, 0, 0xDC);
        ++count;
        cursor += 0xDC;
    } while (count < 64);
}
static inline void ResetScratch(Slot *slot, int index) {
    if (index >= 0 && index < 4) {
        if (slot->flags.bits.local == 1) { slot->read = 0; slot->write = 2; }
        else { slot->read = 0; slot->write = 1; }
        memset(slot, 0, 0x2C);
        ClearPackets(slot);
    }
}

static inline void CopyHostSnapshot(u8 *snapshots, int next) {
    u8 *src = snapshots;
    u8 *dst = src;
    src += next * 0x1C;
    memcpy(dst, src, 0x1C);
}
#undef OSGetTick
#undef OSGetTime
#undef PCBCheck_ProcessLinks
#undef PCBCheck_StateSet
#undef PcbConn_Close
#undef PcbConn_RecycleIfOver
#undef PcbIdToIp_GetCached
#undef PcbListener_Dtor
#undef PcbListener_TakeAcceptedSocket
#undef Profiler_RecordFrame
#undef TCPConn_Close
#undef TCPConn_Init
#undef TCPListen_Poll
#undef g_confirmFlag
#undef g_gameMode
#undef g_isCommHost
#undef g_myPcbId
#undef g_pcbCommEnabled
#undef g_pcbListener
#undef g_pcbSyncPhasePerPcb
#undef g_pcbSyncReady
#undef g_ringReadIdx
#undef lbl_80598A60
#undef PCBCheckRecv_data_806CEFC8
#undef PCBCheckRecv_bss_806D1188
#undef lbl_806D1191
#undef lbl_806D1193
#undef g_ringWriteIdx
#undef lbl_806D11A4
#undef lbl_806D11A8
#undef PCBComm_Init_bss_806D11AC
#undef PCBCheckRecv_bss_806D11B0
#undef PCBCheckRecv_bss_806D11C0
#undef PCBCheckRecv_bss_806D11C8
#undef lbl_806D3168
#undef lbl_806D316C
#undef lbl_806D3198
#undef memset
#undef g_in
#undef g_out
#undef g_pcbSyncTable
#undef g_ring
#undef g_slots
#undef g_snaps
/* ==== PcbDebugOverlay_link.cpp ==== */
#define TexMgr_SetTexture TexMgr_SetTexture_p22
#define fn_8011F994 fn_8011F994_p22
#define fn_801F8A34 fn_801F8A34_p22
#define fn_801F8E58 fn_801F8E58_p22
#define fn_801F93EC fn_801F93EC_p22
#define isJapanese isJapanese_p22
#define lbl_806D1191 lbl_806D1191_p22
#define lbl_806D3180 lbl_806D3180_p22
#define lbl_806D3184 lbl_806D3184_p22
#define lbl_806D3188 lbl_806D3188_p22
#define lbl_806D318C lbl_806D318C_p22
#define lbl_806D3190 lbl_806D3190_p22
#define lbl_806D3194 lbl_806D3194_p22
#define PCBCheckRecv_rodata_80311E38 ((const unsigned int *)PCBCheckRecv_rodata_80311E38)
#pragma exceptions on
#pragma use_lmw_stmw on
extern "C" int DrawLinkErrorOverlay(void)
{
    if (lbl_806D1191 == 0) {
        return 0;
    }
    FKTex tex;
    tex.field18 = 1;
    tex.field20 = -1;
    fn_801F93EC(&tex, lbl_806D3180, lbl_806D3184);
    if (isJapanese() == 0) {
        TexMgr_SetTexture(&tex, lbl_80312338);
    } else {
        TexMgr_SetTexture(&tex, lbl_80312350);
        fn_801F93EC(&tex, lbl_806D3188, lbl_806D3184);
    }
    fn_801F8A34(fn_801F8E58(), &tex, 0);
    fn_801F93EC(&tex, lbl_806D318C, lbl_806D3190);
    if (isJapanese() == 0) {
        TexMgr_SetTexture(&tex, lbl_8031236C);
    } else {
        TexMgr_SetTexture(&tex, lbl_80312388);
        fn_801F93EC(&tex, lbl_806D3194, lbl_806D3190);
    }
    fn_801F8A34(fn_801F8E58(), &tex, 0);
    fn_8011F994(0);
    return 1;
}
#undef TexMgr_SetTexture
#undef fn_8011F994
#undef fn_801F8A34
#undef fn_801F8E58
#undef fn_801F93EC
#undef isJapanese
#undef lbl_806D1191
#undef lbl_806D3180
#undef lbl_806D3184
#undef lbl_806D3188
#undef lbl_806D318C
#undef lbl_806D3190
#undef lbl_806D3194
#undef PCBCheckRecv_rodata_80311E38
/* ==== PCBCommLifecycle.cpp ==== */
#define OSGetTick OSGetTick_p23
#define OSGetTime OSGetTime_p23
#define PCBCheck_ProcessLinks PCBCheck_ProcessLinks_p23
#define PCBCheck_StateSet PCBCheck_StateSet_p23
#define PcbConn_Close PcbConn_Close_p23
#define PcbConn_RecycleIfOver PcbConn_RecycleIfOver_p23
#define PcbIdToIp_GetCached PcbIdToIp_GetCached_p23
#define PcbListener_Dtor PcbListener_Dtor_p23
#define PcbListener_TakeAcceptedSocket PcbListener_TakeAcceptedSocket_p23
#define Profiler_RecordFrame Profiler_RecordFrame_p23
#define TCPConn_Close TCPConn_Close_p23
#define TCPConn_Init TCPConn_Init_p23
#define TCPListen_Poll TCPListen_Poll_p23
#define g_confirmFlag g_confirmFlag_p23
#define g_gameMode g_gameMode_p23
#define g_isCommHost g_isCommHost_p23
#define g_myPcbId g_myPcbId_p23
#define g_pcbCommEnabled g_pcbCommEnabled_p23
#define g_pcbListener g_pcbListener_p23
#define g_pcbSyncPhasePerPcb g_pcbSyncPhasePerPcb_p23
#define g_pcbSyncReady g_pcbSyncReady_p23
#define g_ringReadIdx g_ringReadIdx_p23
#define lbl_80598A60 lbl_80598A60_p23
#define PCBCheckRecv_data_806CEFC8 lbl_806CEFC8_p23
#define PCBCheckRecv_bss_806D1188 lbl_806D1188_p23
#define lbl_806D1191 lbl_806D1191_p23
#define lbl_806D1193 lbl_806D1193_p23
#define g_ringWriteIdx lbl_806D11A0_p23
#define lbl_806D11A4 lbl_806D11A4_p23
#define lbl_806D11A8 lbl_806D11A8_p23
#define PCBComm_Init_bss_806D11AC lbl_806D11AC_p23
#define PCBCheckRecv_bss_806D11B0 lbl_806D11B0_p23
#define PCBCheckRecv_bss_806D11C0 lbl_806D11C0_p23
#define PCBCheckRecv_bss_806D11C8 lbl_806D11C8_p23
#define lbl_806D3168 lbl_806D3168_p23
#define lbl_806D316C lbl_806D316C_p23
#define lbl_806D3198 lbl_806D3198_p23
#define memset memset_p23
#define g_out ((LifecycleConn **)PCBCheck_ProcessLinks_bss_805A6134)
#define g_in ((LifecycleConn **)lbl_805A6144)
#define g_slots ((Slot *)PCBCheckRecv_bss_805A6154)
#define g_ring g_ringBufferBase
#define g_snaps PCBCheckRecv_bss_805AC258
#define g_pcbSyncTable (*(Sync *)g_pcbSyncTable)
#pragma exceptions on
#pragma use_lmw_stmw on
extern "C" int PCBComm_Process(u8 receive, u8 send)
{
    if (g_pcbCommEnabled == 0) return 0;
    if (lbl_806D1191 == 1) return 0;
    Slot *slots;
    signed char *phases;
    Sync *sync;
    int i;
    u8 update = 0;
    u32 tick = OSGetTick();
    if (g_gameMode == 2 ||
        (tick - PCBCheckRecv_bss_806D1188) / ((*(u32 *)0x800000F8 / 4) / 1000) >= 15) {
        update = 1;
        PCBCheckRecv_bss_806D1188 = tick;
    }
    ScopedTimer timer(38);
    if (update) {
        u32 address;
        u8 accepted = 0;
        int off;
        if (g_pcbCommEnabled != 0 && g_pcbListener != 0 &&
            TCPListen_Poll(g_pcbListener, 0) == 1) {
            slots = g_slots;
            address = *(u32 *)(g_pcbListener->bytes + 0x34);
            Slot *slot = slots;
            for (i = 0; i < 4; ++i, ++slot) {
                if (slot->flags.bits.local != 1 && address == PcbIdToIp_GetCached(SlotId(slot))) {
                    off = i * sizeof(Slot);
                    Slot *sel = (Slot *)((u8 *)&g_slots[0].recv + off);
                    if (*(LifecycleConn **)sel != 0) TCPConn_Close(*(LifecycleConn **)sel);
                    *(LifecycleConn **)sel = g_in[i];
                    int socket = PcbListener_TakeAcceptedSocket(g_pcbListener);
                    TCPConn_Init(*(LifecycleConn **)sel, ((SlotFlags *)((u8 *)g_slots + 0xa34 + off))->ids.id, socket, 1);
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
            slots = g_slots;
            sync = &g_pcbSyncTable;
            phases = g_pcbSyncPhasePerPcb;
            for (i = 0; i < 4; ++i) {
                sync->scenes[i] = (slots[i].header.word >> 15) & 255;
                sync->roles[i] = slots[i].header.bytes.role.role;
                phases[i] = 0;
            }
            PCBComm_UpdateSyncPhase1();
            PCBComm_UpdateSyncPhase5();
            signed char *phase = phases;
            u8 *scenePtr = sync->scenes;
            u8 *timerPtr = (u8 *)sync;
            for (i = 0; i < 4; ++i, ++phase, ++scenePtr, timerPtr += sizeof(float)) {
                if (*phase == 0) {
                    if (*scenePtr < 45) *(float *)(timerPtr + 8) = lbl_806D316C;
                    else *(float *)(timerPtr + 8) = lbl_806D3168;
                }
            }
            g_pcbSyncTable.ready = 1;
            Slot *cursor = slots;
            for (i = 0; i < 4; ++i, ++cursor) {
                if (((cursor->header.word >> 15) & 255) != 0 && ((cursor->header.word >> 15) & 255) < 7 && cursor->header.bytes.role.role == 0 && ((cursor->header.word >> 15) & 255) == 3) {
                    g_pcbSyncTable.ready = 0;
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
        for (int n = 0; n < 1; n++) CopyHostSnapshot(g_snaps[0], n + 1);
    }
    return 1;
}

extern "C" int PcbComm_Shutdown(void)
{
    if (g_pcbCommEnabled == 0) return 0;
    Slot *slot = g_slots;
    LifecycleConn **outgoing = g_out;
    LifecycleConn **incoming = g_in;
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
    if (g_pcbCommEnabled == 1) return 0;
    int myId = (signed char)lbl_80598A60[0x21];
    g_pcbCommEnabled = 1;
    lbl_806D1191 = 0;
    g_pcbSyncReady = 0;
    PCBCheckRecv_data_806CEFC8 = 1;
    lbl_806D1193 = 0;
    g_confirmFlag = 0;
    g_myPcbId = myId;
    g_pcbListener = new LifecycleListener;
    PCBCheckRecv_bss_806D11B0 = 0;
    lbl_806D11A4 = 0;
    lbl_806D11A8 = 0;
    PCBComm_Init_bss_806D11AC = 0;
    PCBCheckRecv_bss_806D1188 = OSGetTick();
    PCBCheckRecv_bss_806D11C0[0] = lbl_806D316C;
    PCBCheckRecv_bss_806D11C0[1] = lbl_806D3168;
    PCBCheckRecv_bss_806D11C8 = OSGetTime();
    LifecycleConn **outgoing = g_out;
    LifecycleConn **incoming = g_in;
    Slot *slot = g_slots;
    int i;
    for (i = 0; i < 4; ++i, ++outgoing, ++incoming, ++slot) {
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
            int sid = SlotId(slot);
            if (sid == g_myPcbId) {
                slot->flags.bits.local = 1;
                slot->send = 0;
                slot->recv = 0;
            } else {
                slot->flags.bits.local = 0;
                slot->send = g_out[id - 1];
                slot->recv = 0;
                TCPConn_Close(slot->send);
                TCPConn_Init(slot->send, i + 1, -1, 0);
            }
            ResetScratch(slot, i);
        }
    }
    u8 *ring;
    g_ringWriteIdx = 1;
    g_ringReadIdx = 0;
    ring = g_ring[0];
    ClearRing(ring);
    memset(&g_pcbSyncTable, 0, 0x1C);
    return 1;
}
#undef OSGetTick
#undef OSGetTime
#undef PCBCheck_ProcessLinks
#undef PCBCheck_StateSet
#undef PcbConn_Close
#undef PcbConn_RecycleIfOver
#undef PcbIdToIp_GetCached
#undef PcbListener_Dtor
#undef PcbListener_TakeAcceptedSocket
#undef Profiler_RecordFrame
#undef TCPConn_Close
#undef TCPConn_Init
#undef TCPListen_Poll
#undef g_confirmFlag
#undef g_gameMode
#undef g_isCommHost
#undef g_myPcbId
#undef g_pcbCommEnabled
#undef g_pcbListener
#undef g_pcbSyncPhasePerPcb
#undef g_pcbSyncReady
#undef g_ringReadIdx
#undef lbl_80598A60
#undef PCBCheckRecv_data_806CEFC8
#undef PCBCheckRecv_bss_806D1188
#undef lbl_806D1191
#undef lbl_806D1193
#undef g_ringWriteIdx
#undef lbl_806D11A4
#undef lbl_806D11A8
#undef PCBComm_Init_bss_806D11AC
#undef PCBCheckRecv_bss_806D11B0
#undef PCBCheckRecv_bss_806D11C0
#undef PCBCheckRecv_bss_806D11C8
#undef lbl_806D3168
#undef lbl_806D316C
#undef lbl_806D3198
#undef memset
#undef g_in
#undef g_out
#undef g_pcbSyncTable
#undef g_ring
#undef g_slots
#undef g_snaps
#pragma cplusplus off
