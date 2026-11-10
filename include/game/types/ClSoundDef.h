#ifndef GAME_TYPES_CLSOUNDDEF_H
#define GAME_TYPES_CLSOUNDDEF_H

typedef struct ClSoundDef {
    unsigned int effect;
    unsigned char group;
    unsigned char mode;
    unsigned char reserved6[2];
    float near_distance;
    float far_distance;
    unsigned char volume;
    unsigned char reserved11;
    unsigned short pitch;
    unsigned char reserved14;
    unsigned char category;
    unsigned char reserved16[2];
    unsigned int attributes;
} ClSoundDef;

#endif /* GAME_TYPES_CLSOUNDDEF_H */
