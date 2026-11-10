#ifndef GAME_TYPES_CHARACTERDATA_H
#define GAME_TYPES_CHARACTERDATA_H

typedef struct CharacterData {
    int pad0;
    void *driver_model;
    void *kart_model;
    int pad0C[4];
    float anim1C;
    float pad20;
    float anim24;
} CharacterData;

#endif /* GAME_TYPES_CHARACTERDATA_H */
