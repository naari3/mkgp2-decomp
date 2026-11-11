#include "game/types/clCrsDisp.h"


clCrsDisp::clCrsDisp(int unused, int layer_)
    : state(-1), layer(layer_), variant(0), resId(0), order(0), path(0), self(0), x(lbl_806DAF44),
      y(lbl_806DAF44), scale(lbl_806DAF44), blink(new FlowFaderI), slide(new FlowFaderF(lbl_806DAF44)),
      zoom(new FlowFaderF(lbl_806DAF44)) {
    zoom.p->Set(lbl_806DAF48, lbl_806DAF48, 1);
    order = new int[8];
    resId = 0xC0C;
    int cup = CupIndex();
    int longRound = g_longRoundFlag;
    switch (cup) {
    case 1:
        resId = longRound == 0 ? 0xC0C : 0xC0E;
        break;
    case 2:
        resId = longRound == 0 ? 0xC04 : 0xC06;
        break;
    case 3:
        resId = longRound == 0 ? 0xC00 : 0xC02;
        break;
    case 4:
        resId = longRound == 0 ? 0xC10 : 0xC12;
        if (resId == 0xC12) {
            PreloadResource(0xC14);
        }
        break;
    case 5:
        resId = longRound == 0 ? 0xC08 : 0xC0A;
        break;
    case 6:
        PreloadResource(0xC16);
        resId = longRound == 0 ? 0xC18 : 0xC1A;
        PreloadResource(resId);
        resId = 0xC16;
        break;
    case 7:
        resId = longRound == 0 ? 0xC20 : 0xC22;
        break;
    case 8:
        resId = longRound == 0 ? 0xC1C : 0xC1E;
        break;
    default:
        resId = longRound == 0 ? 0xC0C : 0xC0E;
        break;
    }
    PreloadResource(resId);
    PreloadResource(0xBCC);
    PreloadResource(0xBD2);
    PreloadResource(0xBD1);
    for (int i = 0; i < 4; i++) {
        PreloadResource(i + 0xBCD);
    }
    if (CupIndex() == 6) {
        variant = 0;
    } else {
        variant = g_longRoundFlag;
    }
    Layout();
    slideX = lbl_806DAF40;
    order[0] = -1;
    order[1] = -1;
    order[2] = -1;
    order[3] = -1;
    order[4] = -1;
    order[5] = -1;
    order[6] = -1;
    order[7] = -1;
    blink.p->Set(0x7F, 0xFF, 30);
    {
    ResCtrl a;
    a.resId = resId;
    sprites[0] = SpriteHandle_CreateDefault(&a, layer);
    }
    {
    ResCtrl b;
    b.resId = 0xBD1;
    for (int i = 3; i < 11; i++) {
        sprites[i] = SpriteHandle_CreateDefault(&b, layer);
    }
    }
    {
    ResCtrl c;
    c.resId = 0xBD2;
    sprites[1] = SpriteHandle_CreateDefault(&c, layer);
    }
    {
    ResCtrl d;
    d.resId = 0xBCC;
    sprites[2] = SpriteHandle_CreateDefault(&d, layer);
    }
    for (int i = 0; i < 11; i++) {
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    others[0] = 0;
    others[1] = 0;
    others[2] = 0;
    others[3] = 0;
    others[4] = 0;
    others[5] = 0;
    others[6] = 0;
    others[7] = 0;
}



#pragma push
#pragma opt_common_subs off
clCrsDisp::~clCrsDisp() {
    clCrsDisp *cursor = this;
    int i;
    for (i = 0; i < 11; i++) {
        SpriteHandle_Destroy(cursor->sprites[0]);
        cursor = (clCrsDisp *)((char *)cursor + sizeof(int));
    }
    delete[] order;
    fn_80120A08(resId);
    switch (CupIndex()) {
    case 4:
        fn_80120A08(0xC14);
        break;
    case 6:
        fn_80120A08(0xC16);
        break;
    }
    fn_80120A08(0xBCC);
    fn_80120A08(0xBD2);
    fn_80120A08(0xBD1);
    for (int j = 0; j < 4; j++) {
        fn_80120A08(j + 0xBCD);
    }
}
#pragma pop




extern "C" clCrsDisp *fn_80219900(int unused, int layer) {
    return new clCrsDisp(unused, layer);
}



void clCrsDisp::SetPath(PathManager *pm) {
    if (pm == 0) {
        return;
    }
    path = pm;
    PathEntry *e;
    int pid;
    int offset;
    int n = 0;
    int i;
    for (i = 0, offset = 0; i < 8; i++) {
        e = PathManager_GetEntrySubStruct(pm, i);
        if (e == 0 || e->id == -1) {
            continue;
        }
        int c = e->kart->character;
        if (c <= -1 || c >= 13) {
            continue;
        }
        pid = e->kart->playerId;
        if (pid == GetDisplayBufferIndex()) {
            self = e->kart;
        }
        *(int *)((char *)order + offset) = i;
        offset += sizeof(int);
        n++;
        if (n >= 8) {
            break;
        }
    }
}



static inline void RotateMapPoint(float angle, float *px, float *pz, float *rx, float *rz) {
    if (lbl_806DAF44 != angle) {
        float s = sin(angle);
        float c = cos(angle);
        *rx = *px * c - *pz * s;
        *rz = *px * s + *pz * c;
    } else {
        *rx = *px;
        *rz = *pz;
    }
}

static inline void WorldToMap(clCrsDisp *h, float *ppx, float *ppz) {
    float &px = *ppx;
    float &pz = *ppz;
    const MapInfo *mi = &lbl_803C4C10[CupIndex()][h->variant];
    float rot = mi->rot;
    float ang = lbl_806DAF54 * rot;
    ang += h->scale;
    float rx;
    float rz;
    RotateMapPoint(ang, ppx, ppz, &rx, &rz);
    rx *= mi->sx;
    rz *= mi->sy;
    if (rx < -500.0f) {
        rx = -500.0f;
    } else if (rx > 500.0f) {
        rx = 500.0f;
    }
    if (rz < -500.0f) {
        rz = -500.0f;
    } else if (rz > 500.0f) {
        rz = 500.0f;
    }
    rx += mi->ox;
    rz += mi->oy;
    rx -= h->slideX;
    px = h->x + rx;
    pz = h->y + rz;
}

static inline void SetMarkerVisible(int sprite, int battleCup, bool sameTeam) {
    int visible = 0;
    if (battleCup || sameTeam) {
        visible = 1;
    }
    SpriteHandle_SetActiveFlag(sprite, visible);
}

/* fakematch (pragma): the target multiplies `K * rot` with rot evaluated FIRST
 * (lower virtual register). That needs `rot` to stay a named local, and the
 * frontend only keeps it with propagation off (regalloc_patterns 64). */
#pragma push
#pragma opt_propagation off
void clCrsDisp::UpdateMarkers() {
    float px = lbl_806DAF44;
    float pz = lbl_806DAF44;
    PathEntry *e;
    int me;
    int myTeam;
    int cup7;
    int pid;
    int orderOffset;
    int i;
    int slot;
    me = GetDisplayBufferIndex();
    if (g_cupId == 7) {
        cup7 = 1;
    } else {
        cup7 = 0;
    }
    myTeam = self->team;
    for (i = 7, orderOffset = 7 * sizeof(int); i >= 0; i--, orderOffset -= sizeof(int)) {
        if (*(int *)((char *)order + orderOffset) == -1) {
            continue;
        }
        e = PathManager_GetEntrySubStruct(path, i);
        slot = i + 3;
        pid = e->kart->playerId;
        if (pid >= 0 && pid <= 3) {
            if (pid == me) {
                slot = 2;
                int res = 0xBCC;
                if (g_gameMode == 2) {
                    res = pid + 0xBCD;
                }
                SpriteLayer_SetResource(sprites[2], res);
            } else {
                SpriteLayer_SetResource(sprites[slot], pid + 0xBCD);
                others[i] = 1;
            }
        } else if (pid == 4 && e->kart->hidden == 1) {
            SpriteHandle_SetActiveFlag(sprites[slot], 0);
            continue;
        } else {
            SpriteLayer_SetResource(sprites[slot], 0xBD1);
            fn_8011F744(sprites[slot], lbl_806DAF48, lbl_806DAF48);
            others[i] = 0;
        }
        float *m = KartDriver_GetKartRootMtx(e->kart);
        px = m[3];
        pz = m[11];
        WorldToMap(this, &px, &pz);
        fn_8011F804(sprites[slot], px, pz);
        SetMarkerVisible(sprites[slot], cup7, myTeam == e->kart->team);
        if (pid == me) {
            SpriteHandle_SetCornerAlpha(sprites[1], blink.p->Value());
            fn_8011F804(sprites[1], px, pz);
            SpriteHandle_SetActiveFlag(sprites[1], 1);
        }
    }
}
#pragma pop




void clCrsDisp::Update() {
    int res;
    switch (state) {
    case -1:
        if (g_countdownPhase < 4) {
            state = 0;
            slide.p->Set(lbl_806DAF40, lbl_806DAF44, 7);
        }
        break;
    case 0:
        slideX = slide.p->Value();
        slide.p->Step();
        if (slide.p->Done()) {
            state = 1;
            slideX = lbl_806DAF44;
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            zoom.p->Set(lbl_806DAF48, lbl_806DAF4C, 4);
            state = 2;
        }
        break;
    case 2:
        if (zoom.p->Done() && lbl_806DAF48 == zoom.p->Value()) {
            state = 3;
        }
        break;
    case 3:
        break;
    case 4:
        slideX = slide.p->Value();
        slide.p->Step();
        if (slide.p->Done()) {
            state = 5;
            for (int i = 0; i < 11; i++) {
                SpriteHandle_SetActiveFlag(sprites[i], 0);
                SpriteHandle_RecomputeCull(sprites[i]);
            }
        }
        break;
    case 5:
        fn_80120A08(resId);
        switch (CupIndex()) {
        case 4:
            fn_80120A08(0xC14);
            break;
        case 6:
            fn_80120A08(0xC16);
            break;
        }
        return;
    default:
        return;
    }
    if (id > 0) {
        id--;
        if (id <= 0) {
            id = 0;
            state = 4;
            slide.p->Set(lbl_806DAF44, lbl_806DAF40, 7);
        }
    }
    if (self != 0) {
        int cup = CupIndex();
        int longRound = g_longRoundFlag;
        if (cup == 4) {
            if (longRound == 1) {
                if (self->team == 0) {
                    variant = 1;
                    resId = 0xC12;
                } else {
                    variant = 2;
                    resId = 0xC14;
                }
            }
        } else if (cup == 6) {
            if (self->team == 0) {
                variant = 0;
                resId = 0xC16;
            } else if (longRound == 0) {
                variant = 1;
                resId = 0xC18;
            } else {
                variant = 2;
                resId = 0xC1A;
            }
        }
    }
    if (path != 0) {
        int cup = CupIndex();
        int longRound = g_longRoundFlag;
        res = resId;
        if (cup == 4) {
            if (longRound == 1) {
                Layout();
            }
        } else if (cup == 6) {
            Layout();
        }
        fn_8011F804(sprites[0], x - slideX, y);
        fn_8011F7AC(sprites[0], scale);
        SpriteLayer_SetResource(sprites[0], res);
        SpriteHandle_SetActiveFlag(sprites[0], 1);
        UpdateMarkers();
    }
    blink.p->Step();
    if (blink.p->Done()) {
        if (blink.p->Value() == 0x7F) {
            blink.p->Set(0x7F, 0xFF, 30);
        } else {
            blink.p->Set(0xFF, 0x7F, 30);
        }
    }
    zoom.p->Step();
    if (zoom.p->Done()) {
        float v = zoom.p->Value();
        if (lbl_806DAF4C == v) {
            zoom.p->Set(lbl_806DAF4C, lbl_806DAF48, 4);
        } else if (lbl_806DAF48 == v) {
            zoom.p->Set(lbl_806DAF48, lbl_806DAF48, 1);
        }
    }
    float z = zoom.p->Value();
    for (int i = 0; i < 3; i++) {
        fn_8011F744(sprites[i], z, z);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    float k = lbl_806DAF50;
    for (int i = 3; i < 11; i++) {
        float s;
        if (others[i - 3] == 1) {
            s = k * zoom.p->Value();
        } else {
            s = zoom.p->Value();
        }
        fn_8011F744(sprites[i], s, s);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}




void clCrsDisp::Draw() {
}

void clCrsDisp::Start(int n) {
    if (state < 4) {
        id = n + 1;
    }
}



extern "C" {
const float lbl_803C4BF8[3][2] = {
    { 561.0f, 2.6e+02f },
    { 561.0f, 2.6e+02f },
    { 561.0f, 2.6e+02f }
};
const MapInfo lbl_803C4C10[9][3] = {
    {
        { -25.0f, -2.0f, 0.032f, 0.034f, 0.0f },
        { -33.0f, 25.0f, 0.025f, 0.025f, 0.0f },
        { 0.0f, 0.0f, 0.03f, 0.03f, 0.0f },
    },
    {
        { -9.4f, -3.0f, 0.034f, 0.033f, 0.0f },
        { -27.6f, 21.4f, 0.028f, 0.026f, 0.0f },
        { 0.0f, 0.0f, 0.03f, 0.03f, 0.0f },
    },
    {
        { 7.6f, -6.96f, 0.041f, 0.039f, 0.0f },
        { 42.4f, 43.5f, 0.025f, 0.026f, 36.6f },
        { 0.0f, 0.0f, 0.03f, 0.03f, 0.0f },
    },
    {
        { 0.7f, 38.0f, 0.029f, 0.0256f, 0.0f },
        { -33.2f, 24.6f, 0.024f, 0.0214f, 0.0f },
        { 0.0f, 0.0f, 0.03f, 0.03f, 0.0f },
    },
    {
        { 51.02f, 59.7f, 0.0229f, 0.0202f, 0.0f },
        { 92.0f, 65.6f, 0.0261f, 0.0242f, 0.0f },
        { -176.2f, 87.6f, 0.0219f, 0.0211f, 0.0f },
    },
    {
        { -4.48f, -18.3f, 0.029f, 0.026f, 0.0f },
        { -14.8f, 3.48f, 0.025f, 0.0221f, 0.0f },
        { 0.0f, 0.0f, 0.03f, 0.03f, 0.0f },
    },
    {
        { -110.1f, 2.36f, 0.0286f, 0.026f, 0.0f },
        { 117.5f, -45.5f, 0.0223f, 0.02f, 0.0f },
        { 151.8f, -40.7f, 0.0332f, 0.0297f, 0.0f },
    },
    {
        { -39.4f, 88.1f, 0.0104f, 0.009f, 27.38f },
        { 45.2f, 75.9f, 0.011f, 0.01f, -0.08f },
        { 0.0f, 0.0f, 0.03f, 0.03f, 0.0f },
    },
    {
        { -55.28f, 93.2f, 0.024f, 0.023f, 0.0f },
        { -51.7f, 91.0f, 0.0226f, 0.023f, 0.0f },
        { 0.0f, 0.0f, 0.03f, 0.03f, 0.0f }
    },
};
}
