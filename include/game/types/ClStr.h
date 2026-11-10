#ifndef GAME_TYPES_CLSTR_H
#define GAME_TYPES_CLSTR_H

struct ClStr {
    char *ptr;
    unsigned long *refs;
    ClStr(void *p);
    ~ClStr();
};

#endif /* GAME_TYPES_CLSTR_H */
