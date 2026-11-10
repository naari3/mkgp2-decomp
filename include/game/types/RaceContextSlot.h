#ifndef GAME_TYPES_RACECONTEXTSLOT_H
#define GAME_TYPES_RACECONTEXTSLOT_H

typedef struct RaceContextSlot {
    int type;
    int id;
    unsigned int word08;
    unsigned int word0C;
    unsigned char pad10[0x60];
    void *driver;
    unsigned char pad74[0x0C];
    void *position;
    int index84;
    unsigned int word88;
    unsigned int word8C;
    int index90;
    int index94;
    unsigned char pad98[4];
    unsigned int word9C;
    unsigned char padA0[4];
    float scale;
    void *item;
    int indexAC;
    int state;
    unsigned int payloadB4;
    unsigned int wordB8;
} RaceContextSlot;

#endif /* GAME_TYPES_RACECONTEXTSLOT_H */
