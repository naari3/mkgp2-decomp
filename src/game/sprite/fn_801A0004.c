#include "game/SpriteAnimTraversal_private.h"

static inline void SpriteAnim_Rotate(float *matrix, float angle) {
    float transform[6];
    float c = (float)cos(angle);
    float sn = (float)sin(angle);
    transform[0] = c; transform[1] = sn; transform[2] = lbl_806D97D8;
    transform[3] = -sn; transform[4] = c; transform[5] = lbl_806D97D8;
    SpriteAnim_Concat(matrix, matrix, transform);
}

static inline void SpriteAnim_Scale(float *matrix, float sx, float sy) {
    float transform[6];
    transform[0] = sx; transform[1] = lbl_806D97D8; transform[2] = lbl_806D97D8;
    transform[3] = lbl_806D97D8; transform[4] = sy; transform[5] = lbl_806D97D8;
    SpriteAnim_Concat(matrix, matrix, transform);
}

int fn_801A0004(SpriteAnim *s) {
    float matrix[6];
    float transform[6];
    if (s->data == 0) return 0;
    matrix[0] = lbl_806D97DC; matrix[1] = lbl_806D97D8; matrix[2] = lbl_806D97D8;
    matrix[3] = lbl_806D97D8; matrix[4] = lbl_806D97DC; matrix[5] = lbl_806D97D8;
    transform[0] = lbl_806D97DC; transform[1] = lbl_806D97D8; transform[2] = s->x;
    transform[3] = lbl_806D97D8; transform[4] = lbl_806D97DC; transform[5] = s->y;
    SpriteAnim_Concat(matrix, matrix, transform);
    SpriteAnim_Rotate(matrix, s->rotation);
    SpriteAnim_Scale(matrix, s->scaleX, s->scaleY);
    fn_8019FA30(s, s->data->frames, matrix, 0, 0, 0, 0, s->alpha);
    return 1;
}
