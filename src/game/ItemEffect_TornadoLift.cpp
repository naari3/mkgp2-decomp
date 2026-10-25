/* ItemEffect_TornadoLift @ 0x80053AE0: arm the tornado lift effect from a
 * pose matrix, seeding both the start and current matrices.
 *
 * NonMatching: the target schedules the two matrix copies as if the pose
 * could not alias the state (loads hoisted, pose[8..15] kept in f10..f3 for
 * the second copy); every copy form tried here stays load/store paired. */

extern "C" {
extern const float lbl_806D27F8; /* 0.0f */
extern const float lbl_806D2820;
}

struct TLVec {
    float x, y, z;
};

struct TLMtx {
    float m[16];
};

struct TLCar {
    char pad0[0xD4];
    unsigned char fieldD4;
};

struct TLOwner {
    TLCar *car;
};

class TLState {
public:
    virtual void Reset();

    TLOwner *owner;
    TLVec pos;
    int timer;
    float f18;
    float f1C;
    float f20;
    TLMtx start;
    TLMtx cur;
    int duration;
};

struct TLEffect {
    char pad0[8];
    TLState *state;
    char padC[0x18 - 0xC];
    TLState *armed;
};

extern "C" int ItemEffect_TornadoLift(TLEffect *self, TLMtx *pose)
{
    TLState *st;
    int i;

    if (self->armed != 0) {
        return 0;
    }
    self->armed = self->state;
    st = self->state;
    st->Reset();
    st->timer = 0;
    st->f18 = lbl_806D27F8;
    st->f1C = lbl_806D2820;
    st->f20 = lbl_806D27F8;
    for (i = 0; i < 16; i++) {
        st->start.m[i] = pose->m[i];
    }
    for (i = 0; i < 16; i++) {
        st->cur.m[i] = pose->m[i];
    }
    st->duration = 0x3C;
    st->pos = *(TLVec *)&st->start.m[12];
    st->owner->car->fieldD4 = 0;
    return 1;
}
