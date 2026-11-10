#ifndef GAME_TYPES_BOXLIST_H
#define GAME_TYPES_BOXLIST_H

/* Declare before including (each user already does): ListBase */

struct BoxList : ListBase<void *> {
    ~BoxList() {}
};

#endif /* GAME_TYPES_BOXLIST_H */
