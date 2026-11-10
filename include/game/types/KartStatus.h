#ifndef GAME_TYPES_KARTSTATUS_H
#define GAME_TYPES_KARTSTATUS_H

typedef struct KartStatus {
    unsigned char pad[0x10];
    unsigned long long flags;
} KartStatus;

#endif /* GAME_TYPES_KARTSTATUS_H */
