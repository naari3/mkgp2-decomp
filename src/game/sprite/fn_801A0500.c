#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

extern void fn_801A12F0(SpriteAnimData *d);

int fn_801A0500(SpriteAnim *s) {
    if (s->data == 0) {
        return 0;
    }
    fn_801A12F0(s->data);
    s->data = 0;
    s->name = 0;
    return 1;
}
