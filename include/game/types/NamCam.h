#ifndef GAME_TYPES_NAMCAM_H
#define GAME_TYPES_NAMCAM_H

#include "game/types/NamCamSocket.h"

typedef struct NamCam {
    unsigned char frame[0x80000];
    NamCamSocket sock;
} NamCam;

#endif /* GAME_TYPES_NAMCAM_H */
