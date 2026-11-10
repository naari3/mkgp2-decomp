#ifndef GAME_TYPES_SPRITESLOT_H
#define GAME_TYPES_SPRITESLOT_H

/* Merged from 14 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SpriteSlot SpriteSlot;
struct SpriteSlot {
    /* 0x000 */ unsigned char flags;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ void *object;  /* also: joint, model */
    /* 0x008 */ unsigned char cls;
    /* 0x009 */ signed char anim;
    /* 0x00A */ signed char state;
    /* 0x00B */ unsigned char pad_00B[0x1];
    /* 0x00C */ float frame;
    /* 0x010 */ float speed;  /* also: scale */
    /* 0x014 */ signed char animated;  /* also: visible */
    /* 0x015 */ unsigned char pad_015[0x3];
    /* 0x018 */ float alpha;
    /* 0x01C */ float r;
    /* 0x020 */ float g;
    /* 0x024 */ float b;
    /* 0x028 */ unsigned char pad_028[0x4];
    /* 0x02C */ float translate_dx;  /* also: u */
    /* 0x030 */ float translate_dy;  /* also: v */
};

#endif /* GAME_TYPES_SPRITESLOT_H */
