#include "game/C8CourseRowsPrivate.h"
extern "C" int fn_801CE918(CourseRows *self, int index) {
    CourseRow *row = &self->rows[index];
    if (!row->sprite) return 0;
    if (Sprite_AdvanceAnim(row->sprite,lbl_806D9EF0) == 1) return 1;
    switch(row->state) {
    case 1: {
        RowAnimation *animations = lbl_8049B348;
        RowLayout *layout = &lbl_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[5].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[5].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[5].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        fn_8019FF6C(row->sprite,1);
        break;
    }
    case 2: break;
    case 3: {
        RowAnimation *animations = lbl_8049B348;
        RowLayout *layout = &lbl_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[2].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[2].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[2].scale);
        row->sprite->SetPos(layout->x + self->x,layout->alternateY);
        fn_8019FF6C(row->sprite,1);
        break;
    }
    case 4:
    case 7:
        delete row->sprite;
        row->state = 0;
        row->sprite = 0;
        return 0;
    }
    return 1;
}
