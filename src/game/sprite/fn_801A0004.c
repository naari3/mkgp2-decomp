#include "game/SpriteAnimTraversal_private.h"

static inline float SpriteAnim_Dot2(float ax, float ay, float bx, float by) {
    return ax * bx + ay * by;
}

static inline float SpriteAnim_Add(float translation, float product) {
    return translation + product;
}

static inline void SpriteAnim_Compose(float *out, const float *a, const float *b) {
    float t[6];
    int i;
    t[0] = SpriteAnim_Dot2(a[0], a[1], b[0], b[3]);
    t[1] = SpriteAnim_Dot2(a[0], a[1], b[1], b[4]);
    t[2] = SpriteAnim_Add(a[2], SpriteAnim_Dot2(a[0], a[1], b[2], b[5]));
    t[3] = SpriteAnim_Dot2(a[3], a[4], b[0], b[3]);
    t[4] = SpriteAnim_Dot2(a[3], a[4], b[1], b[4]);
    t[5] = SpriteAnim_Add(a[5], SpriteAnim_Dot2(a[3], a[4], b[2], b[5]));
    for (i = 0; i < 6; i++) out[i] = t[i];
}

static inline float SpriteAnim_Cos(float angle) {
    return (float)cos(angle);
}

static inline float SpriteAnim_Sin(float angle) {
    return (float)sin(angle);
}

static inline void SpriteAnim_Rotate(float *matrix, float angle) {
    float transform[6];
    float c = SpriteAnim_Cos(angle);
    float sn = SpriteAnim_Sin(angle);
    transform[0] = c; transform[1] = sn; transform[2] = lbl_806D97D8;
    transform[3] = -sn; transform[4] = c; transform[5] = lbl_806D97D8;
    SpriteAnim_Compose(matrix, matrix, transform);
}

static inline void SpriteAnim_Scale(float *matrix, float sx, float sy) {
    float transform[6];
    transform[0] = sx; transform[1] = lbl_806D97D8; transform[2] = lbl_806D97D8;
    transform[3] = lbl_806D97D8; transform[4] = sy; transform[5] = lbl_806D97D8;
    SpriteAnim_Compose(matrix, matrix, transform);
}

int fn_801A0004(SpriteAnim *s) {
    float matrix[6];
    float transform[6];
    if (s->data == 0) return 0;
    matrix[0] = lbl_806D97DC; matrix[1] = lbl_806D97D8; matrix[2] = lbl_806D97D8;
    matrix[3] = lbl_806D97D8; matrix[4] = lbl_806D97DC; matrix[5] = lbl_806D97D8;
    transform[0] = lbl_806D97DC; transform[1] = lbl_806D97D8; transform[2] = s->x;
    transform[3] = lbl_806D97D8; transform[4] = lbl_806D97DC; transform[5] = s->y;
    SpriteAnim_Compose(matrix, matrix, transform);
    SpriteAnim_Rotate(matrix, s->rotation);
    SpriteAnim_Scale(matrix, s->scaleX, s->scaleY);
    fn_8019FA30(s, s->data->frames, matrix, 0, 0, 0, 0, s->alpha);
    return 1;
}
