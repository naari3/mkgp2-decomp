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
typedef struct PeerSlot {
    union { u32 word; struct { PeerHeader header; u8 rest[3]; } bytes; } first;
    u8 character;
    VoteByte vote;
    u8 mode;
    u8 pad7[0xA35];
} PeerSlot;
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
    PeerSlot peer[4];
    CardRow card[4];
    u8 pad2C98[0x3700];
    SyncOutput output[2];
} CommStorage;

extern CommStorage lbl_805A5EC0[];
extern const CardPointers lbl_80312234[];
extern int g_localPcbRole, g_currentSceneState;
extern u8 g_isCommHost, lbl_806CEFC8;
/* Actual callee: no incoming arguments, r3 is a 15-bit integer. */
extern int rand(void);
/* Actual callee reads four pointer words through r3 and returns an integer. */
extern int CardSnapshot_ResolveCommonItems(CardRow** rows);

static inline u8 PeersReady(PeerSlot* peer, int role)
{
    int i;
    u8 ready = 1;
    if (role != 0) {
        unsigned int scene = g_currentSceneState;
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

static inline void CountModeVotes(PeerSlot* peer, int* votes, int role)
{
    int i;
    for (i = 0; i < 3; ++i) votes[i] = 0;
    for (i = 0; i < 4; ++i, ++peer)
        if (peer->first.bytes.header.role == role)
            ++votes[(peer->mode >> 4) & 3];
}

static inline void CountTrackVotes(PeerSlot* peer, int* votes, int role)
{
    int i;
    for (i = 0; i < 16; ++i) votes[i] = 0;
    for (i = 0; i < 4; ++i, ++peer)
        if (peer->first.bytes.header.role == role)
            ++votes[peer->vote.track];
}

static inline void CountOptionVotes(PeerSlot* peer, int* votes, int role)
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
    return &storage->output[1];
}

int PCBComm_ComputeSyncState(void)
{
    int trackVotes[16];
    int modeVotes[3];
    CardPointers cards;
    u8 usedCharacters[13];
    int optionVotes[2];
    u8 usedPositions[4];
    int characterCount;
    CommStorage* storage = lbl_805A5EC0;
    PeerSlot* firstPeer;
    SyncOutput* out = HostOutput(storage);
    PeerSlot* peer;
    int i, winner, role;
    u8 ready;

    if (out == 0) {
        if (g_localPcbRole != 0) return 0;
        out = &storage->output[0];
    }
    ready = PeersReady(storage->peer, g_localPcbRole);
    if (ready == 1) out->scene = g_currentSceneState;

    if ((int)out->scene == 12) {
        CountModeVotes(storage->peer, modeVotes, g_localPcbRole);
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
        CountTrackVotes(storage->peer, trackVotes, g_localPcbRole);
        for (i = 0; i < 16; ++i)
            if (trackVotes[i] > trackVotes[winner]) winner = i;
        out->choice.half.track = winner;
    }
    if ((int)out->scene == 26) {
        winner = 0;
        CountOptionVotes(storage->peer, optionVotes, g_localPcbRole);
        for (i = 0; i < 2; ++i)
            if (optionVotes[i] > optionVotes[winner]) winner = i;
        out->choice.bytes.option = winner;
    }
    if ((int)out->scene == 26 && out->commonItem == -1) {
        CardRow* card = storage->card;
        firstPeer = storage->peer;
        peer = firstPeer;
        cards = lbl_80312234[0];
        role = g_localPcbRole;
        for (i = 0; i < 4; ++i, ++peer, ++card) {
            if (peer->first.bytes.header.role == role) cards.row[i] = card;
            else cards.row[i] = 0;
        }
        out->commonItem = CardSnapshot_ResolveCommonItems(cards.row);
        for (i = 0; i < 4; ++i) usedPositions[i] = 0;
        role = g_localPcbRole;
        for (i = 0; i < 4 - RoleCount(storage->sync, role); ++i)
            usedPositions[i] = 1;
        peer = firstPeer;
        for (i = 0; i < 4; ++i, ++peer) {
            if (peer->first.bytes.header.role == g_localPcbRole) {
                int position;
                do { position = rand() % 4; }
                while (usedPositions[position] != 0);
                usedPositions[position] = 1;
                out->position[i] = position;
            }
        }
        characterCount = 0;
        for (i = 0; i < 13; ++i) usedCharacters[i] = 0;
        role = g_localPcbRole;
        peer = firstPeer;
        for (i = 0; i < 4; ++i, ++peer)
            if (peer->first.bytes.header.role == role)
                usedCharacters[(peer->character >> 4) & 15] = 1;
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
