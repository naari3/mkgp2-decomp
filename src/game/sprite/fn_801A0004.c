#include "game/SpriteAnimTraversal_private.h"

int fn_801A0004(SpriteAnim *s) {
    float matrix[6];
    float transform[6];
    float c, angle, sn;
    if (s->data == 0) return 0;
    matrix[0] = lbl_806D97DC; matrix[1] = lbl_806D97D8; matrix[2] = lbl_806D97D8;
    matrix[3] = lbl_806D97D8; matrix[4] = lbl_806D97DC; matrix[5] = lbl_806D97D8;
    transform[0] = lbl_806D97DC; transform[1] = lbl_806D97D8; transform[2] = s->x;
    transform[3] = lbl_806D97D8; transform[4] = lbl_806D97DC; transform[5] = s->y;
    SpriteAnim_Concat(matrix, matrix, transform);
    angle = s->rotation;
    c = (float)cos(angle);
    sn = (float)sin(angle);
    transform[0] = c; transform[1] = sn; transform[2] = lbl_806D97D8;
    transform[3] = -sn; transform[4] = c; transform[5] = lbl_806D97D8;
    SpriteAnim_Concat(matrix, matrix, transform);
    transform[0] = s->scaleX; transform[1] = lbl_806D97D8; transform[2] = lbl_806D97D8;
    transform[3] = lbl_806D97D8; transform[4] = s->scaleY; transform[5] = lbl_806D97D8;
    SpriteAnim_Concat(matrix, matrix, transform);
    fn_8019FA30(s, s->data->frames, matrix, 0, 0, 0, 0, s->alpha);
    return 1;
}
