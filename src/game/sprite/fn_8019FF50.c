#include "game/types/SpriteAnimData.h"

typedef struct SpriteAnim {
    unsigned char flag;
    unsigned char pad1[7];
    float time;
    float c[6];
    const char *name;
    SpriteAnimData *data;
} SpriteAnim;

unsigned char fn_8019FF50(SpriteAnim *s) {
    if (s->data == 0) {
        return 0;
    }
    return s->flag;
}
