#ifndef GAME_TYPES_CARDSCENE_H
#define GAME_TYPES_CARDSCENE_H

struct StepSeq;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CardScene CardScene;
struct CardScene {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ struct StepSeq *seq;
    /* 0x014 */ void *fade;
    /* 0x018 */ int state;
    /* 0x01C */ int result;
};

#endif /* GAME_TYPES_CARDSCENE_H */
