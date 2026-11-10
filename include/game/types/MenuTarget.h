#ifndef GAME_TYPES_MENUTARGET_H
#define GAME_TYPES_MENUTARGET_H

typedef struct MenuTarget {
    char pad0[0xc];
    unsigned char sel;
    char padD[0x19d - 0xd];
    unsigned char flag;
} MenuTarget;

#endif /* GAME_TYPES_MENUTARGET_H */
