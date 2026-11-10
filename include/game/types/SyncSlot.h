#ifndef GAME_TYPES_SYNCSLOT_H
#define GAME_TYPES_SYNCSLOT_H

typedef struct SyncSlot {
    unsigned char kind : 5;
    unsigned char rest : 3;
} SyncSlot;

#endif /* GAME_TYPES_SYNCSLOT_H */
