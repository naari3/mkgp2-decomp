#ifndef GAME_MID_RACE_VOICE_PRIVATE_H
#define GAME_MID_RACE_VOICE_PRIVATE_H

#include "game/RaceVoiceGoalPrivate.h"

/* The ranking path compares participant indices stored in each kart. */
typedef struct MidRaceKart {
    unsigned char pad[0x2AC];
    int participantIndex;
} MidRaceKart;

#endif
