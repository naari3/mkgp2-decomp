#ifndef GAME_TYPES_NAMCAMSOCKET_H
#define GAME_TYPES_NAMCAMSOCKET_H

typedef struct NamCamSocket {
    unsigned char pad00[0x10];
    signed char busy;
    unsigned char pad11[0x1b];
    int countdown;
    int state;
} NamCamSocket;

#endif /* GAME_TYPES_NAMCAMSOCKET_H */
