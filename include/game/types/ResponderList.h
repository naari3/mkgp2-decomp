#ifndef GAME_TYPES_RESPONDERLIST_H
#define GAME_TYPES_RESPONDERLIST_H

/* Declare before including (each user already does): ListBase */

struct ResponderList : ListBase<void *> {
    ~ResponderList() {}
};

#endif /* GAME_TYPES_RESPONDERLIST_H */
