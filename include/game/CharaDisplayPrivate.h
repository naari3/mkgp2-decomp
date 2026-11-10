#ifndef CHARA_DISPLAY_PRIVATE_H
#define CHARA_DISPLAY_PRIVATE_H
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *);
struct DisplaySprite {
    char storage[0x30];
    DisplaySprite(int, unsigned char, float, float);
};
struct DisplayTexture { char pad[0x22C]; float width; };
struct CharaDisplay {
    int unknown, selection;
    char pad08[0x48];
    DisplaySprite *stats[3];
    char pad5C[0xC];
    int character;
    char pad6C[0x3C];
    int variants[13];
    void *normals[13];
    void *alternateNormals[13];
    char pad144[0x34];
    DisplayTexture *texture;
    char pad17C[0x58];
    void *joint;
};
#endif
