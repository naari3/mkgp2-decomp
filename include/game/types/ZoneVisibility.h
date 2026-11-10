#ifndef GAME_TYPES_ZONEVISIBILITY_H
#define GAME_TYPES_ZONEVISIBILITY_H

struct HSD_JObj;
struct Zone;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ZoneVisibility ZoneVisibility;
struct ZoneVisibility {
    /* 0x000 */ struct Zone *zones;
    /* 0x004 */ struct HSD_JObj **joints;
    /* 0x008 */ int count;
    /* 0x00C */ int cur;
};

#endif /* GAME_TYPES_ZONEVISIBILITY_H */
