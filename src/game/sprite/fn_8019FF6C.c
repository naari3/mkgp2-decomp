#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

int fn_8019FF6C(SpriteAnim *s, unsigned char flag) {
    if (s->data == 0) {
        return 0;
    }
    s->flag = flag;
    return 1;
}
