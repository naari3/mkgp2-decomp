#ifndef GAME_TYPES_ANIMROW_H
#define GAME_TYPES_ANIMROW_H

typedef struct AnimRow {
    void *descriptor;
    void **joint;
    void **material;
    void **shape;
} AnimRow;

#endif /* GAME_TYPES_ANIMROW_H */
