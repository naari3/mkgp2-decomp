#ifndef GAME_TYPES_FLOWENTRY_H
#define GAME_TYPES_FLOWENTRY_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct FlowEntry FlowEntry;
struct FlowEntry {
    /* 0x000 */ void *(*create) (void);
    /* 0x004 */ unsigned char pad_004[0x8];
};

#endif /* GAME_TYPES_FLOWENTRY_H */
