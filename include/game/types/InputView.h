#ifndef GAME_TYPES_INPUTVIEW_H
#define GAME_TYPES_INPUTVIEW_H

typedef struct InputView {
    unsigned char opaque[4];
    unsigned char enabled;
    unsigned char opaque5[0x13];
    int held;
    int edge;
} InputView;

#endif /* GAME_TYPES_INPUTVIEW_H */
