#ifndef GAME_TYPES_NAMCAM_H
#define GAME_TYPES_NAMCAM_H

#include "game/types/NamCamSocket.h"

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct NamCam NamCam;
struct NamCam {
    /* 0x000 */ unsigned char frame[0x80000];
    /* 0x80000 */ NamCamSocket sock;
};

#endif /* GAME_TYPES_NAMCAM_H */
