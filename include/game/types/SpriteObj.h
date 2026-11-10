#ifndef GAME_TYPES_SPRITEOBJ_H
#define GAME_TYPES_SPRITEOBJ_H

struct SpriteObj {
    char pad0[0xC];
    float x;
    float y;
    char pad14[0x1C];

    SpriteObj(int anim, int loop, int arg);
};

#endif /* GAME_TYPES_SPRITEOBJ_H */
