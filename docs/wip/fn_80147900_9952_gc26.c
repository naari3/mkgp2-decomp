extern "C" void fn_80147900(HudResSet *set) {
    HudResSetView *o = (HudResSetView *)set;

    switch (o->state) {
    case 0:
        if (o->timer <= 15) {
            HudTail_SetScale(o, 1.0f, o->timer / 15.0f);
        } else if (o->timer >= 45) {
            o->state = 1;
            o->timer = 0;
        }
        break;
    case 1:
        if (o->timer <= 20) {
            int a = (int)(255.0f * (o->timer / 20.0f));
            int textColor = 0xFFFFFF00;
            textColor = (textColor & ~0xFF) | (a & 0xFF);
            for (int i = 0; i < 3; i++) {
                o->texts[i].color = textColor;
            }
            unsigned int color = HudColor_SetAlpha(0xFFFFFF00, a);
            o->res[0].colors[0] = color;
            o->res[0].colors[1] = color;
            o->res[0].colors[2] = color;
            o->res[0].colors[3] = color;
        } else if (o->timer >= 80) {
            o->state = 2;
            o->timer = 0;
            if (o->skipCheck == 0) {
                o->state = 3;
            }
        }
        break;
    case 2:
        fn_80147CE8(set);
        break;
    case 3:
        fn_80147AF4(set);
        break;
    case 4: {
        HudInput *in = InputMgr_GetPlayer(GetInputManager(), 0);
        if (!(in->v18() >= 0.7f)) {
            in->Pressed(0x2000);
        }
        o->state = 5;
        o->timer = 0;
        break;
    }
    case 5:
        return;
    }
    o->timer++;
}
