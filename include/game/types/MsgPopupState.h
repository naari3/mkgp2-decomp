#ifndef GAME_TYPES_MSGPOPUPSTATE_H
#define GAME_TYPES_MSGPOPUPSTATE_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct MsgPopupState MsgPopupState;
struct MsgPopupState {
    /* 0x000 */ int cur;
    /* 0x004 */ int pending;
};

#endif /* GAME_TYPES_MSGPOPUPSTATE_H */
