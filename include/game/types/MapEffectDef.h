#ifndef GAME_TYPES_MAPEFFECTDEF_H
#define GAME_TYPES_MAPEFFECTDEF_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct MapEffectDef MapEffectDef;
struct MapEffectDef {
    /* 0x000 */ int model;
    /* 0x004 */ char *joint;
    /* 0x008 */ void *animation;
};

#endif /* GAME_TYPES_MAPEFFECTDEF_H */
