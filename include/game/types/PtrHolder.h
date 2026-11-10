#ifndef GAME_TYPES_PTRHOLDER_H
#define GAME_TYPES_PTRHOLDER_H

/* Declare before including (each user already does): VObj */

struct PtrHolder {
    VObj *p;
    PtrHolder(VObj *q) : p(q) {}
    ~PtrHolder() throw();
};

#endif /* GAME_TYPES_PTRHOLDER_H */
