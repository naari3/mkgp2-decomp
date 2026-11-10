#ifndef GAME_TYPES_BACKUPHISCORES_H
#define GAME_TYPES_BACKUPHISCORES_H

#include "game/types/HiScoreName.h"

typedef struct BackupHiScores {
    unsigned char pad000[0x4E0];
    HiScoreName names[2][9][2][2][10]; /* 0x04E0 */
    float times[2][9][2][2][50];       /* 0x31E0 */
} BackupHiScores;

#endif /* GAME_TYPES_BACKUPHISCORES_H */
