/* Race/session accessors and setters (0x8009BAC4..0x8009BD04). */

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

int Input_IsItemButtonPressed(int buttons)
{
    if ((g_currentSceneState == 4 || g_currentSceneState == 5) && (buttons & 0x2000)) {
        return 1;
    }
    if (buttons & 0xC000) {
        return 1;
    }
    return 0;
}

int BattleRoulette_TickAndGetCounter(void)
{
    if (g_gameMode == 2) {
        g_raceFrameCounterLo2digits++;
    }
    return g_raceFrameCounterLo2digits;
}

void SetCardVolumeFlagByte(unsigned char v)
{
    lbl_806D12AD = v;
}

void SetKartVariant(int v)
{
    g_kartVariant = v;
}

int PcbRole_PromoteToClientConfirmed(int arg)
{
    if (g_localPcbRole < 2 || g_localPcbRole > 4) {
        return 0;
    }
    g_localPcbRole = 5;
    return arg;
}

void SetLocalPcbRole(int role)
{
    g_localPcbRole = role;
    g_isPcbHost = role == 1;
}

void SetSyncTarget(int v)
{
    g_currentSceneState = v;
}

void ItemUse_ResetAllKartUseSlots(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        RankSlot *s = &lbl_805D2948[i];
        s->active = 0;
        s->count = 0;
        s->target = -1;
        s->source = -1;
        s->flag18 = 0;
        s->flag19 = 0;
        s->timer = 0;
        s->value20 = lbl_806D4790;
        s->value24 = lbl_806D4790;
        s->enabled = 1;
    }
    lbl_806D12D8 = 0;
}

RankSlot *RankSlot_GetByIndex(int i)
{
    if (i < 0 || i >= 8) {
        return 0;
    }
    return &lbl_805D2948[i];
}
