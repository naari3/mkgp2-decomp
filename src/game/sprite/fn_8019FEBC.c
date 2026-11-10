#include "game/types/SpriteAnimData.h"

typedef struct SpriteAnim {
    unsigned char flag;
    unsigned char pad1[7];
    float time;
    float c[6];
    const char *name;
    SpriteAnimData *data;
} SpriteAnim;

extern const float lbl_806D97D8;

float fn_8019FEBC(SpriteAnim *s) {
    if (s->data == 0) {
        return lbl_806D97D8;
    }
    return s->data->length;
}
