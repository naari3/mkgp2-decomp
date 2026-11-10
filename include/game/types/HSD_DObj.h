#ifndef GAME_TYPES_HSD_DOBJ_H
#define GAME_TYPES_HSD_DOBJ_H

typedef struct HSD_DObj {
    void *parent;
    HSD_DObj *next;
    void *mobj;
} HSD_DObj;

#endif /* GAME_TYPES_HSD_DOBJ_H */
