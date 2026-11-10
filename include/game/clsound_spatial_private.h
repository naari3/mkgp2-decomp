#ifndef CLSOUND_SPATIAL_PRIVATE_H
#define CLSOUND_SPATIAL_PRIVATE_H
typedef struct ClSoundVec { float x, y, z; } ClSoundVec;
#include "game/types/ClSoundDef.h"
typedef struct ClSoundVoice {
    unsigned int flags, id;
    unsigned char group, reserved9[3];
    unsigned int handle;
    unsigned char scale, volume, pan, surround;
    unsigned short pitch, speed;
    unsigned char category, delay, reserved1a[2];
} ClSoundVoice;
extern unsigned char ClSound_Initialized;
extern ClSoundDef lbl_80379554[];
extern ClSoundVoice ClSound_InitSoundSystem_bss_80678378[32];
typedef struct ClSoundListener { ClSoundVec right, forward, position; } ClSoundListener;
extern ClSoundListener lbl_80495F20;
extern float lbl_806D9514, lbl_806D9518, lbl_806D951C;
extern void Vec3_Subtract(const ClSoundVec*, const ClSoundVec*, ClSoundVec*);
extern float Vec3_Magnitude(const ClSoundVec*);
extern float Vec3_Dot(const ClSoundVec*, const ClSoundVec*);
#endif
