#ifndef PLAYER_DATA_PROGRESS_PRIVATE_H
#define PLAYER_DATA_PROGRESS_PRIVATE_H
/* Private view of the completion flag matrices, 32 entries per CC class. */
typedef struct PlayerProgress {
    unsigned char prefix[0x28];
    unsigned char completed[2][32];
    unsigned char visited[2][32];
} PlayerProgress;
extern int g_cupId, g_reverseRoundFlag, g_ccClass, g_longRoundFlag;
extern unsigned char *fn_8024F588(void);

typedef struct PlayerDataRecord {
    unsigned char prefix[0xA8];
    unsigned char unlockFlags[0x79];
    unsigned char extraFlags[3];
    unsigned char pad124[0x1AC - 0x124];
    int raceCount;
    unsigned char pad1B0[4];
    int coinMilage;
    unsigned char variant, kartVariant;
    unsigned char cupRank[3][8];
    unsigned char tail[0xA];
} PlayerDataRecord;
static inline int CupRank(PlayerDataRecord *p, int cc, int cup) {
    if (cc < 0 || cc > 2) return 0;
    if (cup < 1 || cup >= 17) return 0;
    if (cup >= 9) cup -= 9; else cup -= 1;
    return p->cupRank[cc][cup];
}
#endif
