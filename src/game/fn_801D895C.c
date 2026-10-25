typedef struct Obj801D895C {
    char pad0[0x4];
    char *child;
    char pad8[0x4];
    float x;
    float y;
} Obj801D895C;

void fn_801D895C(Obj801D895C *self, float v) {
    *(float *)(self->child + 0x20) = v;
    *(float *)((char *)self + 0x15C) = v;
}

static inline void SetChildPos(char *child, float x, float y) {
    *(float *)(child + 0xC) = x;
    *(float *)(child + 0x10) = y;
}

void fn_801D896C(Obj801D895C *self, float x, float y) {
    self->x = x;
    self->y = y;
    SetChildPos(self->child, self->x, self->y);
}
