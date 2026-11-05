#ifndef GAME_SELECTION_SLOTS_PRIVATE_H
#define GAME_SELECTION_SLOTS_PRIVATE_H

typedef struct SelectionSlot {
    unsigned char reserved00[0xC];
    unsigned char enabled;
    unsigned char reserved0D[0x2F];
    void *display;
} SelectionSlot;

typedef struct SelectionSlots {
    unsigned char reserved00[0xC];
    int state;
    unsigned char reserved10[0xC];
    int order[8];
    unsigned char reserved3C[0x20];
    SelectionSlot *slots[8];
} SelectionSlots;

extern void fn_80230ED4(void *, unsigned char);
#endif
