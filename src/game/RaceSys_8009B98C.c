/* Race/session accessors and setters (0x8009B98C..0x8009B9D0). */

#include "game/types/RankSlot.h"

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
extern int SetCourseParams_bss_806D12D8;
extern unsigned char TaMode_GetDemoCameraBookend_data_8040DE94[];
extern RankSlot SetCourseParams_bss_805D2948[8];
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
    return TaMode_GetDemoCameraBookend_data_8040DE94 + g_cupId * 0x30 + g_longRoundFlag * 0x18;
}

