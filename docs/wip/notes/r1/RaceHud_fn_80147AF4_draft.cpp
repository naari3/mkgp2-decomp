inline void HudResSet_SetIcons(HudResSet *o, float t, unsigned int c12, unsigned int c34) {
    float s = 0.2f * t + 1.1f;
    HudSpr_SetScale(HUD_SPR(o->res[1]), s, s);
    HudSpr_SetScale(HUD_SPR(o->res[2]), s, s);
    HudSpr_SetScale(HUD_SPR(o->res[3]), s, s);
    HudSpr_SetScale(HUD_SPR(o->res[4]), s, s);
    HudSpr_SetColor(HUD_SPR(o->res[1]), c12);
    HudSpr_SetColor(HUD_SPR(o->res[2]), c12);
    HudSpr_SetColor(HUD_SPR(o->res[3]), c34);
    HudSpr_SetColor(HUD_SPR(o->res[4]), c34);
}

extern "C" void fn_80147AF4(HudResSet *o) {
    float t;
    int a;
    unsigned int c;

    if (o->frame == 1) {
        SoundMgr_Play(0x71);
    }
    if (o->frame < 20) {
        t = (float)o->frame / 20.0f;
        a = (int)(3.0f * (255.0f * t));
        if (a > 255) {
            a = 255;
        }
        c = __rlwimi(0xFFFFFF00, a, 0, 24, 31);
        HudResSet_SetIcons(o, t, c, c);
    } else if (o->frame >= 30) {
        if (o->frame < 45) {
            t = (float)(o->frame - 30) / 15.0f;
            t = 1.0f - t;
            HudResSet_SetIcons(o, t, 0xFFFFFFFF, __rlwimi(0xFFFFFF00, (int)(255.0f * t), 0, 24, 31));
        } else if (o->frame >= 90) {
            o->state = 4;
            o->frame = 0;
        }
    }
}
