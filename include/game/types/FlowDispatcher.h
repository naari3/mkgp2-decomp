#ifndef GAME_TYPES_FLOWDISPATCHER_H
#define GAME_TYPES_FLOWDISPATCHER_H

struct FlowObject;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct FlowDispatcher FlowDispatcher;
struct FlowDispatcher {
    /* 0x000 */ unsigned char pad_000[0x8];
    /* 0x008 */ struct FlowObject *current;
    /* 0x00C */ unsigned char pad_00C[0x4];
    /* 0x010 */ struct FlowObject *next;
};

#endif /* GAME_TYPES_FLOWDISPATCHER_H */
