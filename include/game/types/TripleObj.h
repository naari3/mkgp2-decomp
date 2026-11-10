#ifndef GAME_TYPES_TRIPLEOBJ_H
#define GAME_TYPES_TRIPLEOBJ_H

typedef struct TripleObj {
    char pad0[0x14];
    void **vt14;
    void *p18;
} TripleObj;

#endif /* GAME_TYPES_TRIPLEOBJ_H */
