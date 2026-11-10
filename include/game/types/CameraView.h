#ifndef GAME_TYPES_CAMERAVIEW_H
#define GAME_TYPES_CAMERAVIEW_H

#include "game/types/Vec.h"

/* Merged from 4 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CameraView CameraView;
struct CameraView {
    /* 0x000 */ unsigned char pad_000[0x40];
    /* 0x040 */ float view[4][4];
    /* 0x080 */ Vec eye;
};

#endif /* GAME_TYPES_CAMERAVIEW_H */
