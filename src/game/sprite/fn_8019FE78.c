#include "game/types/SpriteAnimData.h"

typedef struct SpriteAnim {
    unsigned char flag;
    unsigned char pad1[7];
    float time;
    float c[6];
    const char *name;
    SpriteAnimData *data;
} SpriteAnim;

int fn_8019FE78(SpriteAnim *s) {
    if (s->data == 0) {
        return 0;
    }
    if (s->flag == 0 && s->time >= s->data->length) {
        return 0;
    }
    return 1;
}
