#ifndef GAME_TYPES_MODELDEF_H
#define GAME_TYPES_MODELDEF_H

typedef struct ModelDef {
    const char *name;
    int type;
    float height;
    float frameEnd;
    unsigned int flags;
    void *param;
    char pad18[0x4];
} ModelDef;

#endif /* GAME_TYPES_MODELDEF_H */
