#ifndef GAME_TYPES_MAPWATEREFFECT_H
#define GAME_TYPES_MAPWATEREFFECT_H

struct Group;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct MapWaterEffect MapWaterEffect;
struct MapWaterEffect {
    /* 0x000 */ void **vt;
    /* 0x004 */ struct Group *groups;
    /* 0x008 */ int type;
};

#endif /* GAME_TYPES_MAPWATEREFFECT_H */
