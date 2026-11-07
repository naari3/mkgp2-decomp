#ifndef GAME_RACE_DIGITS_MATCH_PRIVATE_H
#define GAME_RACE_DIGITS_MATCH_PRIVATE_H
#include "game/RaceDigitsPrivate.h"
static inline float DigitPositionX(const DigitPosition &v) { return v.x; }
static inline float DigitPositionY(const DigitPosition &v) { return v.y; }
static inline void SetDigitPanelPosition(DigitPanel *panel, const DigitPosition &v) {
    float a=DigitPositionX(v); float b=DigitPositionY(v);
    panel->position.x=a; panel->position.y=b;
}
#endif
