#include "game/anon_8021B568_private.h"

TeamIconRow::~TeamIconRow() {
    for (int i = 0; i < 4; i++) {
        if (icons[i] != 0) {
            delete icons[i];
            icons[i] = 0;
        }
    }
    fn_80120A08(0x157B);
    fn_80120A08(0x1579);
    fn_80120A08(0x157A);
    fn_80120A08(0x156C);
    fn_80120A08(0x156B);
    fn_80120A08(0x1567);
    fn_80120A08(0x156D);
    fn_80120A08(0x1575);
}

TeamIconRow::TeamIconRow() {
    state = 0;
    x1C = 0.0f;
    frame = 0;
    timer = 0;
    closing = 0;
    icons[0] = 0;
    icons[1] = 0;
    icons[2] = 0;
    icons[3] = 0;
    team[0] = 0;
    team[1] = 0;
    team[2] = 0;
    team[3] = 0;
    PreloadResource(0x157B);
    PreloadResource(0x1579);
    PreloadResource(0x157A);
    PreloadResource(0x156C);
    PreloadResource(0x156B);
    PreloadResource(0x1567);
    PreloadResource(0x156D);
    PreloadResource(0x1575);
    for (int i = 0; i < 4; i++) {
        icons[i] = new TeamIcon(i);
        AnimObj *o = icons[i]->anim->obj;
        *(float *)((char *)o + 0xC) = 143.0f * i + 105.0f;
        *(float *)((char *)o + 0x10) = 387.0f;
    }
}
