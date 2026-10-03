#ifndef GAME_INPUTCMD_H
#define GAME_INPUTCMD_H

/* Observed accesses only, not a complete runtime class reconstruction. */
typedef struct InputCmdSampleView {
    float x, y, z;
    int code;
    unsigned char live;
    unsigned char pad11[3];
} InputCmdSampleView;

typedef struct InputCmdView {
    unsigned char pad00[0x10];
    unsigned char mode;
    unsigned char pad11[3];
    void *config;
    int capacity;
    InputCmdSampleView *samples;
    int readIndex;
    int writeIndex;
    unsigned char detected;
    unsigned char pad29[3];
    int cooldown;
} InputCmdView;

#endif
