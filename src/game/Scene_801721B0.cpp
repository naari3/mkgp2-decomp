/*
 * 0x801721B0..0x80172844: homing target marker draw: each active layer of
 * the marker is pushed to its shared sprite slot (position, scale, rotation,
 * color) and drawn.
 */

struct Vec3f {
    float x, y, z;
};

struct SlotDesc {
    float params[4];
    int obj;
};

struct EffectObj {
    char pad00[0x4];
};

struct EffectSlot {
    char pad00[0x2C];
    int mode;
    char pad30[0x64];
};

struct SharedEffect {
    EffectObj *objs[2];
    EffectSlot slots[4];
};

struct RefSub {
    unsigned char on;
    float sx;
    float sy;
    float rot;
    float color[4];
};

struct SharedRef {
    int id;
    float t;
    unsigned char active;
    Vec3f pos;
    RefSub subs[5];
};

extern "C" {
extern const SlotDesc lbl_8036E8D4[4];
extern SharedEffect *lbl_806D15E0;
void GX_EndDraw(int);
void GX_BeginDraw(void);
float fn_80173F5C(float, float, float);
void fn_801F70F0(EffectSlot *, float, float, float);
void fn_801F6ED0(EffectSlot *, float, float);
void fn_801F6EEC(EffectSlot *, float);
void fn_801F6EAC(EffectSlot *, int, int, int, int);
void fn_801F6E84(EffectSlot *, int, int);
void fn_801F7B74(EffectObj *, EffectSlot *, float);
}

static inline void DrawLayerAt(SharedEffect *fx, RefSub *sub, int k, EffectSlot *slot, float x, float y, int mode,
                             int blend) {
    if (sub->on) {
        float rot = sub->rot;
        int o = lbl_8036E8D4[k].obj;

        if (fx->objs[o]) {
            fn_801F70F0(slot, x, y, 1.0f);
            fn_801F6ED0(slot, sub->sx / lbl_8036E8D4[k].params[2], sub->sy / lbl_8036E8D4[k].params[3]);
            fn_801F6EEC(slot, rot);
            fn_801F6EAC(slot, (int)fn_80173F5C(255.0f * sub->color[0], 0.0f, 255.0f),
                        (int)fn_80173F5C(255.0f * sub->color[1], 0.0f, 255.0f),
                        (int)fn_80173F5C(255.0f * sub->color[2], 0.0f, 255.0f),
                        (int)fn_80173F5C(255.0f * sub->color[3], 0.0f, 255.0f));
            slot->mode = mode;
            fn_801F6E84(slot, 4, blend);
            fn_801F7B74(fx->objs[o], slot, -1.0f);
        }
    }
}

static inline void DrawLayer(SharedEffect *fx, RefSub *sub, int k, int si, float x, float y, int mode,
                             int blend) {
    if (sub->on) {
        float rot = sub->rot;
        int o = lbl_8036E8D4[k].obj;

        if (fx->objs[o]) {
            EffectSlot *slot = &fx->slots[si];

            fn_801F70F0(slot, x, y, 1.0f);
            fn_801F6ED0(slot, sub->sx / lbl_8036E8D4[k].params[2], sub->sy / lbl_8036E8D4[k].params[3]);
            fn_801F6EEC(slot, rot);
            fn_801F6EAC(slot, (int)fn_80173F5C(255.0f * sub->color[0], 0.0f, 255.0f),
                        (int)fn_80173F5C(255.0f * sub->color[1], 0.0f, 255.0f),
                        (int)fn_80173F5C(255.0f * sub->color[2], 0.0f, 255.0f),
                        (int)fn_80173F5C(255.0f * sub->color[3], 0.0f, 255.0f));
            fx->slots[si].mode = mode;
            fn_801F6E84(slot, 4, blend);
            fn_801F7B74(fx->objs[o], slot, -1.0f);
        }
    }
}

extern "C" {

void fn_801721B0(SharedRef *self) {
    SharedEffect *fx;
    float x;
    float y;

    if (self->id == -1) {
        return;
    }
    if (self->pos.z > 0.0f) {
        return;
    }
    fx = lbl_806D15E0;
    if (fx == 0) {
        return;
    }
    GX_EndDraw(0);
    y = self->pos.y;
    x = self->pos.x;
    DrawLayerAt(fx, &self->subs[0], 0, &fx->slots[0], x, y, 2, 5);
    DrawLayer(fx, &self->subs[1], 1, 1, x, y, 2, 5);
    DrawLayer(fx, &self->subs[2], 1, 1, x, y, 0, 1);
    DrawLayer(fx, &self->subs[3], 2, 2, x, y, 2, 1);
    DrawLayer(fx, &self->subs[4], 3, 3, x, y, 0, 1);
    GX_BeginDraw();
}

}
