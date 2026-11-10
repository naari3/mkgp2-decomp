#ifndef GAME_TYPES_FACEDRAWMODEL_H
#define GAME_TYPES_FACEDRAWMODEL_H

struct FaceDrawKart;
struct FaceDrawSub;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct FaceDrawModel FaceDrawModel;
struct FaceDrawModel {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ unsigned char variant;
    /* 0x005 */ unsigned char pad_005[0x3];
    /* 0x008 */ int face;
    /* 0x00C */ int left;
    /* 0x010 */ int right;
    /* 0x014 */ float x;
    /* 0x018 */ float y;
    /* 0x01C */ float z;
    /* 0x020 */ float scale;
    /* 0x024 */ unsigned char pad_024[0x4];
    /* 0x028 */ struct FaceDrawKart *kart;
    /* 0x02C */ struct FaceDrawSub *sub;
    /* 0x030 */ void *models[2];
    /* 0x038 */ int timer;
};

#endif /* GAME_TYPES_FACEDRAWMODEL_H */
