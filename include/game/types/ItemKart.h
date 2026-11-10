#ifndef GAME_TYPES_ITEMKART_H
#define GAME_TYPES_ITEMKART_H

#include "game/types/ItemKartFlag.h"

typedef struct ItemKart {
    unsigned char pad000[0x174];
    unsigned char field174;
    unsigned char pad175[0x1CC - 0x175];
    float dt;
    unsigned char pad1D0[0x1E0 - 0x1D0];
    float stunTime;
    float field1E4;
    unsigned char pad1E8[0x205 - 0x1E8];
    unsigned char flag205;
    unsigned char pad206[0x290 - 0x206];
    int counter290;
    float field294;
    unsigned char field298;
    unsigned char pad299[0x29C - 0x299];
    void *field29C;
    float timer2A0;
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
    ItemKartFlag *field35C;
    ItemKartFlag *field360;
} ItemKart;

#endif /* GAME_TYPES_ITEMKART_H */
