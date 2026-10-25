typedef struct Def {
    char pad00[0xC];
    float end;
    unsigned int flags;
} Def;

typedef struct AnimObj {
    void *next;
    Def *def;
    void *jobj;
    float frame;
} AnimObj;

void fn_8017ACBC(AnimObj *self) {
    Def *def = self->def;
    if (def->flags & 1) {
        if ((self->frame += 1.0f) > def->end) {
            self->frame = 0.0f;
        }
    }
}
