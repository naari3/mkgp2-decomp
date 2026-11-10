#ifndef GAME_TYPES_FINALLAPBANNER_H
#define GAME_TYPES_FINALLAPBANNER_H

struct FinalLapBanner {
    unsigned char data[0x10];
    FinalLapBanner(void *renderObj);
};

#endif /* GAME_TYPES_FINALLAPBANNER_H */
