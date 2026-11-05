#ifndef GAME_KART_DRIVER_JOINT_PRIVATE_H
#define GAME_KART_DRIVER_JOINT_PRIVATE_H

#include "sysdolphin/baselib/jobj.h"

/* Joint pointer block used by KartDriver_GetJointByIdx. Slot 8 is skipped
 * by the public joint indices; index 8 starts at offset 0x10C. */
typedef struct KartDriverJoints {
    unsigned char pad000[0xE8];
    HSD_JObj *joints[18];
} KartDriverJoints;

#endif
