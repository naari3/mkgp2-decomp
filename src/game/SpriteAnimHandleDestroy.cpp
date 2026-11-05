#include "game/SpriteAnimHandle_private.h"
extern "C" SpriteAnimHandle *SpriteAnimHandle_Destroy(SpriteAnimHandle *self, short flag) {
    if (self) {
        self->Flush();
        if (self->sprite) {
            Sprite_Destroy(self->sprite, 1);
            self->sprite = 0;
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
