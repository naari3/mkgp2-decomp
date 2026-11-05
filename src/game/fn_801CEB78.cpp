#include "game/C8CourseRowsPrivate.h"
extern "C" int fn_801CEB78(CourseRows *self, int index, int state) {
    CourseRow *row = &self->rows[index];
    if (state != 5) {
        if (state == 1) { if (row->state != 0) return 0; }
        else { if (row->state == 0) return 0; }
    }
    row->state = state;
    switch(state) {
    case 1: {
        RowAnimation *animations = lbl_8049B348;
        RowLayout *layout = &lbl_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[1].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[1].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[1].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        break;
    }
    case 2: {
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
    case 3: {
        RowAnimation *animations = lbl_8049B348;
        RowLayout *layout = &lbl_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[3].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[3].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[3].scale);
        row->sprite->SetPos(layout->x + self->x,layout->alternateY);
        break;
    }
    case 4: {
        RowAnimation *animations = lbl_8049B348;
        RowLayout *layout = &lbl_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[4].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[4].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[4].scale);
        row->sprite->SetPos(layout->x + self->x,layout->alternateY);
        break;
    }
    case 5: {
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
    case 6: {
        RowAnimation *animations = lbl_8049B348;
        RowLayout *layout = &lbl_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[6].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[6].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[6].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        fn_8019FF6C(row->sprite,1);
        break;
    }
    case 7: {
        RowAnimation *animations = lbl_8049B348;
        RowLayout *layout = &lbl_8049B1E0[index];
        if (!row->sprite) row->sprite = new AnimSprite(animations[7].resource,0,0);
        else Sprite_SetupAnim(row->sprite, animations[7].resource,0,0);
        Sprite_SetAnimParam(row->sprite,0x19AC,layout->a);
        Sprite_SetAnimParam(row->sprite,0x19B0,layout->b);
        Sprite_SetAnimParam(row->sprite,0x19AE,layout->c);
        fn_801A0550(row->sprite);
        SetRowScale(row->sprite,animations[7].scale);
        row->sprite->SetPos(layout->x + self->x,layout->y);
        break;
    }
    }
    return 1;
}
