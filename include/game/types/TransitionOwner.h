#ifndef GAME_TYPES_TRANSITIONOWNER_H
#define GAME_TYPES_TRANSITIONOWNER_H

struct FlowFaderI;
struct TransitionChild;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TransitionOwner TransitionOwner;
struct TransitionOwner {
    /* 0x000 */ void *vtable;
    /* 0x004 */ int flags;
    /* 0x008 */ struct TransitionChild *child;
    /* 0x00C */ int route;
    /* 0x010 */ unsigned char pad_010[0x4];
    /* 0x014 */ struct FlowFaderI *fader;
};

#endif /* GAME_TYPES_TRANSITIONOWNER_H */
