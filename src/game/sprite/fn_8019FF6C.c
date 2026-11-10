#include "game/types/SpriteAnimData.h"

typedef struct SpriteAnim {
    unsigned char flag;
    unsigned char pad1[7];
    float time;
    float c[6];
    const char *name;
    SpriteAnimData *data;
} SpriteAnim;

int fn_8019FF6C(SpriteAnim *s, unsigned char flag) {
    if (s->data == 0) {
        return 0;
    }
    s->flag = flag;
    return 1;
}
