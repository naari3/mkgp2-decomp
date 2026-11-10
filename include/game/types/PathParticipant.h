#ifndef GAME_TYPES_PATHPARTICIPANT_H
#define GAME_TYPES_PATHPARTICIPANT_H

typedef struct PathParticipant {
    unsigned char pad_0[0x14];
    int node;
    unsigned char pad_18[0x80];
} PathParticipant;

#endif /* GAME_TYPES_PATHPARTICIPANT_H */
