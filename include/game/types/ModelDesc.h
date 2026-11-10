#ifndef GAME_TYPES_MODELDESC_H
#define GAME_TYPES_MODELDESC_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ModelDesc ModelDesc;
struct ModelDesc {
    /* 0x000 */ void ***jobjDesc;
    /* 0x004 */ void **animJoint;
    /* 0x008 */ void **matAnimJoint;
    /* 0x00C */ void **shapeAnimJoint;
};

#endif /* GAME_TYPES_MODELDESC_H */
