#ifndef GAME_TYPES_COURSEPROPRESOURCE_H
#define GAME_TYPES_COURSEPROPRESOURCE_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CoursePropResource CoursePropResource;
struct CoursePropResource {
    /* 0x000 */ const char *resource;
    /* 0x004 */ float radius;
    /* 0x008 */ float height;
    /* 0x00C */ float scale;
};

#endif /* GAME_TYPES_COURSEPROPRESOURCE_H */
