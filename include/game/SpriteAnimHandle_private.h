#ifndef GAME_SPRITEANIMHANDLE_PRIVATE_H
#define GAME_SPRITEANIMHANDLE_PRIVATE_H
#include "game/CreditHud.h"
struct HandleAnimResource { char pad[0x1c]; short *params; };
struct HandleSpriteView { char pad[0x28]; HandleAnimResource *res; };
extern "C" {
void Sprite_SetAnimParam(AnimSprite *, short, short);
void fn_801A0500(AnimSprite *);
void Sprite_Destroy(AnimSprite *, int);
void MemoryManager_TimedFree(void *);
void fn_8019FF6C(AnimSprite *, int);
}
struct SpriteAnimHandle {
    AnimSprite *sprite;
    short keys[50];
    short params[50];
#ifndef SPRITE_HANDLE_OUTLINE
    SpriteAnimHandle(int resource) : sprite(0) {
        sprite = new AnimSprite(resource, 1, 0);
        short *src = ((HandleSpriteView *)sprite)->res->params;
        for (int i = 0; i < 50; ++i) {
            keys[i] = src[i];
            params[i] = src[i];
            if (src[i] == -1) break;
        }
    }
    SpriteAnimHandle(int *source) : sprite(0) {
        int resource = *source;
        sprite = new AnimSprite(resource, 1, 0);
        short *src = ((HandleSpriteView *)sprite)->res->params;
        for (int i = 0; i < 50; ++i) {
            keys[i] = src[i];
            params[i] = src[i];
            if (src[i] == -1) break;
        }
    }
#else
    SpriteAnimHandle(int resource);
#endif
    void Flush() {
        if (sprite) {
            for (int i = 0; i < 50; ++i) {
                if (keys[i] == -1) break;
                if (params[i] != keys[i]) {
                    Sprite_SetAnimParam(sprite, params[i], keys[i]);
                    params[i] = keys[i];
                }
            }
            fn_801A0500(sprite);
        }
    }
};
#endif
