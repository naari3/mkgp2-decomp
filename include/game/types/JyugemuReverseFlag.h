#ifndef GAME_TYPES_JYUGEMUREVERSEFLAG_H
#define GAME_TYPES_JYUGEMUREVERSEFLAG_H

struct JyugemuReverseFlag {
    unsigned char data[0x14];
    JyugemuReverseFlag(void *renderObj);
};

#endif /* GAME_TYPES_JYUGEMUREVERSEFLAG_H */
