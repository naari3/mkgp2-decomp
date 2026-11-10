#include "game/types/KartCond.h"

extern int g_gameMode;
extern int g_cupId;
extern int g_ccClass;
extern int g_roundIndex;

#include "game/types/DistanceBonusEntry.h"

extern int AI_CalcDistanceSpeedBonus_data_806CFF08;
extern DistanceBonusEntry AI_CalcDistanceSpeedBonus_data_804E3184[];
extern const float FLOAT_defaultBonus;

static inline unsigned char KartCond_Matches(KartCond c, int kart) {
    if (c.mode != -1 && c.mode != g_gameMode) {
        return 0;
    }
    if (c.cup != -1 && c.cup != g_cupId) {
        return 0;
    }
    if (c.ccClass != -1 && c.ccClass != g_ccClass) {
        return 0;
    }
    if (c.round != -1 && c.round != g_roundIndex) {
        return 0;
    }
    if (c.kart != -1 && kart != -1 && c.kart != kart) {
        return 0;
    }
    return 1;
}

float AI_CalcDistanceSpeedBonus(int kart, int row, int col) {
    int i;

    for (i = 0; i < AI_CalcDistanceSpeedBonus_data_806CFF08; i++) {
        if (KartCond_Matches(AI_CalcDistanceSpeedBonus_data_804E3184[i].cond, kart)) {
            return AI_CalcDistanceSpeedBonus_data_804E3184[i].bonus[row][col];
        }
    }
    return FLOAT_defaultBonus;
}
