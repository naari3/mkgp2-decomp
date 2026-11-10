#ifndef GAME_PATHMANAGER_UPDATEALL_PRIVATE_H
#define GAME_PATHMANAGER_UPDATEALL_PRIVATE_H
/* Private views of the participant and kart fields used by UpdateAll.
 * Participant offsets agree with PathManager_RegisterCarObject.c. */
typedef struct UpdateKart {
    char pad0[0x1F4];
    int playerId;
    char pad1F8[0x23C-0x1F8];
    int rank;
    char pad240[8];
    int commId;
    int pathVariant;
    char pad250[0x2B8-0x250];
    unsigned char finished;
    char pad2B9[0x2D0-0x2B9];
    unsigned char suppressResult;
} UpdateKart;
typedef struct UpdateEntry {
    int changed, node, field8;
    float *px, *py, *pz;
    float lapTimes[10];
    float bestLap;
    unsigned char field44, rankImproved, crossedEnd, pad47;
    unsigned short progress, maxProgress;
    float totalTime;
    int lap;
    float distance;
    int rank, field5C, field60;
    char pad64[0x70-0x64];
    int maxNode, field74, field78, pathVariant;
    float previous[3];
    void *item;
    UpdateKart *kart;
    int field94;
} UpdateEntry;
typedef struct UpdateManager {
    char cursor[0x10];
    UpdateEntry entries[8];
    int bonusLap;
} UpdateManager;
extern int g_gameMode, g_cupId, g_longRoundFlag, g_reverseRoundFlag;
extern int g_totalLaps, g_currentLap, g_finalRacePosition, lbl_806CF128;
extern unsigned char g_isCommHost, lbl_806D1048, g_lapChangePending;
extern float g_raceTimeRemaining, g_lapBonusTimeDelta, g_currentLapTime;
extern float g_bestLapTime, g_totalRaceTime;
extern const float lbl_806D24E8, lbl_806D2504, lbl_806D2508, lbl_806D250C;
extern const float DANGER;
extern const double lbl_806D24F0, lbl_806D24F8;
float *GetFinishLineSegment(void);
int GetDisplayBufferIndex(void);
int PathManager_HasPathLoaded(UpdateManager *);
int Path_GetTotalCount(UpdateManager *);
#ifdef __MWERKS__
int Waypoint_FindBestAhead(UpdateManager *, int, int, int, float, float, float, float *);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern int Waypoint_FindBestAhead(UpdateManager *, float, float, float, int, int, int, float *);
static inline int Waypoint_FindBestAhead_Reordered(UpdateManager *a0, int a1, int a2, int a3, float a4, float a5, float a6, float *a7) { return Waypoint_FindBestAhead(a0, a4, a5, a6, a1, a2, a3, a7); }
#define Waypoint_FindBestAhead Waypoint_FindBestAhead_Reordered
#endif
signed char CommBroadcast_GetKartLap(int);
void CommBroadcast_SetKartLap(int, signed char);
int CommBroadcast_GetKartRankNibble(int);
void CommBroadcast_SetKartRankNibble(int, int);
#ifdef __MWERKS__
unsigned char Math_Segment2DIntersect(float, float, float, float, float, float, float, float, float *, float *);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern unsigned char Math_Segment2DIntersect(float *, float *, float, float, float, float, float, float, float, float);
static inline unsigned char Math_Segment2DIntersect_Reordered(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float *a8, float *a9) { return Math_Segment2DIntersect(a8, a9, a0, a1, a2, a3, a4, a5, a6, a7); }
#define Math_Segment2DIntersect Math_Segment2DIntersect_Reordered
#endif
void CoinEvent_PlaySE_0x13(void *);
int KartMovement_CalcFinishPosition(UpdateKart *, int);
void KartMovement_ResetOnGoal(UpdateKart *);
void KartMovement_ResetOnTimeout(UpdateKart *);
void KartItem_OnFallOffOrDeath(void *);
void CoinJumpFlasher_SetArmed(void *, int);
void CoinEvent_PlayResultSE(void *, int);
void KartItem_SetByte2b8(UpdateKart *, int);
int IsTimerModeEnabled(void);
unsigned char IsRaceStarted(void);
void KartMovement_SetRemainingLaps(UpdateKart *, int);
void CoinEvent_PlayAlternatingSE(void *);
#endif
