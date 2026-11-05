#ifndef CLSOUND_SPATIAL_PRIVATE_H
#define CLSOUND_SPATIAL_PRIVATE_H
typedef struct ClSoundVec { float x, y, z; } ClSoundVec;
typedef struct ClSoundDef {
    unsigned int effect;
    unsigned char group, mode, reserved6[2];
    float near_distance, far_distance;
    unsigned char volume, reserved11;
    unsigned short pitch;
    unsigned char reserved14, category, reserved16[2];
    unsigned int attributes;
} ClSoundDef;
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
extern ClSoundVoice lbl_80678378[32];
typedef struct ClSoundListener { ClSoundVec right, forward, position; } ClSoundListener;
extern ClSoundListener lbl_80495F20;
extern float lbl_806D9514, lbl_806D9518, lbl_806D951C;
extern void Vec3_Subtract(const ClSoundVec*, const ClSoundVec*, ClSoundVec*);
extern float Vec3_Magnitude(const ClSoundVec*);
extern float Vec3_Dot(const ClSoundVec*, const ClSoundVec*);
#endif
