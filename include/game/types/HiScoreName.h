#ifndef GAME_TYPES_HISCORENAME_H
#define GAME_TYPES_HISCORENAME_H

typedef struct HiScoreName {
    unsigned short name[6];
    unsigned char kart;
    unsigned char extra[3];
} HiScoreName;

#endif /* GAME_TYPES_HISCORENAME_H */
