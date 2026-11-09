/* one 0x58 sprite of a HudResSet: scale at 0x2C, per-corner colours at 0x34 */
struct HudSpr {
    char pad0[0x2C];
    float sx;
    float sy;
    unsigned int col[4];
    char pad44[0x14];
};
#define HUD_SPR(p) ((HudSpr *)(p))
#define HUD_TEXT_COL(p) (*(unsigned int *)((p) + 0x20))

inline void HudSpr_SetScale(HudSpr *s, float x, float y) {
    s->sx = x;
    s->sy = y;
}

inline void HudSpr_SetColor(HudSpr *s, unsigned int c) {
    s->col[0] = c;
    s->col[1] = c;
    s->col[2] = c;
    s->col[3] = c;
}

extern "C" void fn_80147900(HudResSet *o) {
    switch (o->state) {
    case 0:
        if (o->frame <= 15) {
            float s = (float)o->frame / 15.0f;
            HudSpr_SetScale(HUD_SPR(o->tail.res[0]), 1.0f, s);
            HudSpr_SetScale(HUD_SPR(o->tail.res[1]), 1.0f, s);
            HudSpr_SetScale(HUD_SPR(o->tail.res[2]), 1.0f, s);
        } else if (o->frame >= 45) {
            o->state = 1;
            o->frame = 0;
        }
        break;
    case 1:
        if (o->frame <= 20) {
            int a = (int)(255.0f * ((float)o->frame / 20.0f));
            unsigned int c = 0xFFFFFF00;
            unsigned int tc = __rlwimi(c, a, 0, 24, 31);
            unsigned int sc = __rlwimi(c, a, 0, 24, 31);
            HUD_TEXT_COL(o->texts[0]) = tc;
            HUD_TEXT_COL(o->texts[1]) = tc;
            HUD_TEXT_COL(o->texts[2]) = tc;
            HudSpr_SetColor(HUD_SPR(o->res[0]), sc);
        } else if (o->frame >= 80) {
            o->state = 2;
            o->frame = 0;
            if (!o->fC) {
                o->state = 3;
            }
        }
        break;
    case 2:
        fn_80147CE8(o);
        break;
    case 3:
        fn_80147AF4(o);
        break;
    case 4: {
        HudInput *in = InputMgr_GetPlayer(GetInputManager(), 0);
        if (!(in->v18() >= 0.7f)) {
            in->Pressed(0x2000);
        }
        o->state = 5;
        o->frame = 0;
        break;
    }
    case 5:
        return;
    }
    o->frame++;
}
