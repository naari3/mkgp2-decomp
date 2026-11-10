#ifndef GAME_TYPES_JOBJ_H
#define GAME_TYPES_JOBJ_H

typedef struct JObj {
    char pad00[0x8];
    JObj *next;
    JObj *parent;
    JObj *child;
    unsigned int flags;
    char pad18[0x8];
    float rotY;
    char pad24[0x8];
    float scaleX;
    char pad30[0x4];
    float scaleZ;
    char pad38[0xC];
    float mtx[3][4];
} JObj;

#endif /* GAME_TYPES_JOBJ_H */
