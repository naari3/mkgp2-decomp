#ifndef GAME_TYPES_LAPDISP_H
#define GAME_TYPES_LAPDISP_H

typedef struct LapDisp {
    char pad_00[0x10];
    int currentLapLayer;
    int totalLapsLayer;
    char pad_18[0x10];
    int currentLap;
    int totalLaps;
    int currentLapFloor;
} LapDisp;

#endif /* GAME_TYPES_LAPDISP_H */
