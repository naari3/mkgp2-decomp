#ifndef GAME_TYPES_TOBJVIEW_H
#define GAME_TYPES_TOBJVIEW_H

typedef struct TObjView {
    unsigned char pad[0x74];
    float mtx[3][4];
} TObjView;

#endif /* GAME_TYPES_TOBJVIEW_H */
