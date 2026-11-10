#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

unsigned char fn_8019FF50(SpriteAnim *s) {
    if (s->data == 0) {
        return 0;
    }
    return s->flag;
}
