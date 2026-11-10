#ifndef GAME_TYPES_FLOWCONTROLLER_H
#define GAME_TYPES_FLOWCONTROLLER_H

struct FlowSceneList;

/* Merged from 6 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct FlowController FlowController;
struct FlowController {
    /* 0x000 */ void *vt;
    /* 0x004 */ struct FlowSceneList *owner;
};

#endif /* GAME_TYPES_FLOWCONTROLLER_H */
