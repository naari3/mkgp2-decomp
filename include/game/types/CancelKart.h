#ifndef GAME_TYPES_CANCELKART_H
#define GAME_TYPES_CANCELKART_H

#include "game/types/CancelFlag.h"

typedef struct CancelKart {
    unsigned char pad000[0x174];
    unsigned char field174;
    unsigned char pad175[3];
    int field178;
    unsigned char pad17C[0x205 - 0x17C];
    unsigned char flag205;
    unsigned char pad206[0x29C - 0x206];
    void *field29C;
    unsigned char pad2A0[4];
    int hitDir;
    unsigned char pad2A8[0x2B0 - 0x2A8];
    unsigned char field2B0;
    unsigned char pad2B1[2];
    unsigned char iseActive;
    int field2B4;
    unsigned char pad2B8[0x2C0 - 0x2B8];
    int currentItemId;
    unsigned char pad2C4[4];
    int currentISESlot;
    unsigned char pad2CC[0x2DC - 0x2CC];
    void *iseSlots[20];
    void *field32C;
    unsigned char pad330[0x35C - 0x330];
    CancelFlag *field35C;
    CancelFlag *field360;
} CancelKart;

#endif /* GAME_TYPES_CANCELKART_H */
