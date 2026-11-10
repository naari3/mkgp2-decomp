#ifndef GAME_TYPES_KARTEFFECTFADETRANSIT_H
#define GAME_TYPES_KARTEFFECTFADETRANSIT_H

typedef struct KartEffectFadeTransit {
    unsigned char active;
    unsigned char pad[3];
    void *owner;
    void *effect;
    void *camera;
    float value;
    float target;
    unsigned int timer;
} KartEffectFadeTransit;

#endif /* GAME_TYPES_KARTEFFECTFADETRANSIT_H */
