/* PCB sync-table and link-slot peer counters, 0x800856F4..0x80085DD8. */

typedef struct {
    unsigned char disabled : 1;
    unsigned char unused6 : 1;
    unsigned char ready : 1;
    unsigned char flag4 : 1;
    unsigned char unusedLow : 4;
} ReadyFlags;

typedef struct PcbSlot {
    union {
        unsigned int word;
        struct {
            unsigned char unused7 : 1;
            unsigned char team : 3;
            unsigned char unusedLow : 4;
            unsigned char b1;
            unsigned char b2;
            unsigned char unused3hi : 6;
            unsigned char readyBit1 : 1;
            unsigned char unused3lo : 1;
        } bits;
    } hdr;
    unsigned char pad_04[0xA30];
    ReadyFlags flags;
    unsigned char pad_A35[7];
} PcbSlot;

extern unsigned char g_pcbSyncTable[0x1C];
extern PcbSlot lbl_805A6154[4];
extern int g_myPcbId;
extern int g_localPcbRole;
extern int g_currentSceneState;
extern signed char lbl_805AC258[];

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
        if (PCB_IS_JOINED(&lbl_805A6154[i], i, g_myPcbId - 1) && lbl_805A6154[i].hdr.bits.readyBit1 == 1) {
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
        if (PCB_IS_JOINED(&lbl_805A6154[i], i, g_myPcbId - 1)) {
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
        if (PCB_IS_JOINED(&lbl_805A6154[i], i, g_myPcbId - 1) && PCB_CHAR_ID(&lbl_805A6154[i]) >= 8) {
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
        if (PCB_IS_JOINED(&lbl_805A6154[i], i, g_myPcbId - 1)) {
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
        state = PCB_CHAR_ID(&lbl_805A6154[i]);
        if (state != 0 && state < 7 && lbl_805A6154[i].hdr.bits.team == 0 && state != 3 && state != 5) {
            return 0;
        }
    }
    return 1;
}

int IsSyncReached(void)
{
    return lbl_805AC258[8] == g_currentSceneState;
}

int PcbSync_AlwaysZero_Stub(void)
{
    return 0;
}
