#ifndef GAME_TYPES_TIRESPRITE_H
#define GAME_TYPES_TIRESPRITE_H

typedef struct TireSprite {
    signed char flip;
    char pad01[0x14 - 1];
    signed char visible;
    float alpha;
    char pad1C[0x34 - 0x1C];
    float vx[4];
    float vy[4];
    float vz[4];
    char pad64[0x6C - 0x64];
    float px;
    float py;
    float pz;
} TireSprite;

#endif /* GAME_TYPES_TIRESPRITE_H */
