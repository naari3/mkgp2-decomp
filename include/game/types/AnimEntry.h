#ifndef GAME_TYPES_ANIMENTRY_H
#define GAME_TYPES_ANIMENTRY_H

/* One track of an AnimState description (AnimState_InitEntries in
 * AnimState_Step.c): the track type in the first byte, then the key table.
 * A description is an array of these ended by type 13. */
typedef struct AnimEntry {
    char type;
    unsigned char pad[3];
    void *data;
} AnimEntry;

#endif
