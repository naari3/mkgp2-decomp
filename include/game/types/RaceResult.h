#ifndef GAME_TYPES_RACERESULT_H
#define GAME_TYPES_RACERESULT_H

typedef struct RaceResult {
    char pad00;
    unsigned char retired;
    char pad02[0x18 - 0x2];
    int coins;
    int coinGoal;
} RaceResult;

#endif /* GAME_TYPES_RACERESULT_H */
