#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

extern const char lbl_80381098[];

const char *fn_8019FE58(SpriteAnim *s) {
    if (s->data == 0) {
        return lbl_80381098;
    }
    return s->name;
}
