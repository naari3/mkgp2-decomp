#ifndef GAME_TYPES_FACESPRITE_H
#define GAME_TYPES_FACESPRITE_H

struct FaceSprite {
    virtual ~FaceSprite();
    char pad04[0x14 - 4];
    float scale;
};

#endif /* GAME_TYPES_FACESPRITE_H */
