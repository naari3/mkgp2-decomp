#ifndef GAME_TYPES_OBJVIEW_H
#define GAME_TYPES_OBJVIEW_H

typedef struct ObjView {
    void *vt;
    void *child;
    void *buf;
} ObjView;

#endif /* GAME_TYPES_OBJVIEW_H */
