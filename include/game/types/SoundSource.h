#ifndef GAME_TYPES_SOUNDSOURCE_H
#define GAME_TYPES_SOUNDSOURCE_H

typedef struct SoundSource {
    unsigned char pad00[0xc];
    float x;
    unsigned char pad10[0xc];
    float y;
    unsigned char pad20[0xc];
    float z;
} SoundSource;

#endif /* GAME_TYPES_SOUNDSOURCE_H */
