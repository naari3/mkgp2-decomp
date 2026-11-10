#ifndef GAME_TYPES_KARTEFFECTFADETRANSIT_H
#define GAME_TYPES_KARTEFFECTFADETRANSIT_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartEffectFadeTransit KartEffectFadeTransit;
struct KartEffectFadeTransit {
    /* 0x000 */ unsigned char active;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ void *owner;
    /* 0x008 */ void *effect;  /* also: kartBody */
    /* 0x00C */ void *camera;  /* also: shadowBillboard */
    /* 0x010 */ float value;
    /* 0x014 */ float target;
    /* 0x018 */ unsigned int timer;
};

#endif /* GAME_TYPES_KARTEFFECTFADETRANSIT_H */
