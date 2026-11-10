#ifndef GAME_TYPES_ISESLOT_H
#define GAME_TYPES_ISESLOT_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ISESlot ISESlot;
struct ISESlot {
    /* 0x000 */ float field_0x00;  /* also: timer */
    /* 0x004 */ unsigned char active;
    /* 0x005 */ unsigned char pending;
    /* 0x006 */ unsigned char pad_006[0x2];
    /* 0x008 */ int state;  /* also: param */
    /* 0x00C */ int field_0x0c;  /* also: state */
    /* 0x010 */ int field_0x10;  /* also: kartIdx */
    /* 0x014 */ int typeId;  /* also: kind */
    /* 0x018 */ void *item;  /* also: boundItem */
    /* 0x01C */ int field_0x1c;  /* also: pairParam */
    /* 0x020 */ int ctxSlot;  /* also: column */
};

#endif /* GAME_TYPES_ISESLOT_H */
