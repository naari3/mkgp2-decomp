#ifndef GAME_TYPES_OPERATIONCLOCKSTATE_H
#define GAME_TYPES_OPERATIONCLOCKSTATE_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct OperationClockState OperationClockState;
struct OperationClockState {
    /* 0x000 */ int state;
    /* 0x004 */ unsigned int start;
    /* 0x008 */ unsigned int currentSeconds;
    /* 0x00C */ unsigned int deltaSeconds;
};

#endif /* GAME_TYPES_OPERATIONCLOCKSTATE_H */
