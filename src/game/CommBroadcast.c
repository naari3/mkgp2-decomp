/* Per-kart lap and rank bytes in the current ring-buffer entry (see
 * RingBuffer_Getters.c for the entry layout). The host reads its local
 * entry 0; clients read the entry at g_ringReadIdx. */

typedef struct CommRankNibbles {
    signed char kart0 : 4;
    signed char kart1 : 4;
    signed char kart2 : 4;
    signed char kart3 : 4;
} CommRankNibbles;

typedef struct CommEntry {
    unsigned char pad00[0xd4];
    CommRankNibbles rank; /* 0xD4 */
    unsigned char lap[4]; /* 0xD6 */
    unsigned char padDA[2];
} CommEntry;

extern unsigned char g_isCommHost;
extern int g_ringReadIdx;
extern int lbl_806D11A0;
extern CommEntry g_ringBufferBase[];

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

    while (lbl_806D11A0 != (g_ringReadIdx + i) % 64) {
        i++;
    }
    return i;
}
