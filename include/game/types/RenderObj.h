#ifndef GAME_TYPES_RENDEROBJ_H
#define GAME_TYPES_RENDEROBJ_H

typedef struct RenderObj {
    char pad0[0x238];
    int x238;
    char pad23C[0x94];
    unsigned char x2D0;
} RenderObj;

#endif /* GAME_TYPES_RENDEROBJ_H */
