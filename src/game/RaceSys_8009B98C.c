/* Race/session accessors and setters (0x8009B98C..0x8009B9D0). */

typedef struct RankSlot {
    unsigned char active;
    unsigned char pad1;
    unsigned short count;
    unsigned char pad4[0xC];
    int target;
    int source;
    unsigned char flag18;
    unsigned char flag19;
    unsigned char pad1A[2];
    int timer;
    float value20;
    float value24;
    unsigned char enabled;
    unsigned char pad29[3];
} RankSlot;

extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_currentSceneState;
extern int g_gameMode;
extern int g_raceFrameCounterLo2digits;
extern unsigned char lbl_806D12AD;
extern int g_kartVariant;
extern int g_localPcbRole;
extern signed char g_isPcbHost;
extern int lbl_806D12D8;
extern unsigned char lbl_8040DE94[];
extern RankSlot lbl_805D2948[8];
extern const float lbl_806D4790;
extern const float lbl_806D4794;

void *TaMode_GetDemoCameraBookend(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return lbl_8040DE94 + g_cupId * 0x30 + g_longRoundFlag * 0x18;
}

