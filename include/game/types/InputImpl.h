#ifndef GAME_TYPES_INPUTIMPL_H
#define GAME_TYPES_INPUTIMPL_H

typedef struct InputImpl {
    void *vt;
    unsigned char enabled;
    unsigned char flag5;
    unsigned char flag6;
    int fields[8];
} InputImpl;

#endif /* GAME_TYPES_INPUTIMPL_H */
