extern float *Object_GetJObjLocalMatrix(void *obj);
extern int SoundMgr_PlaySE(int sound_id);
extern int fn_8016C2D0(int sound_id, float x, float y, float z);
extern const float lbl_806D256C;

typedef struct AnimStateObj {
    void *obj;
    unsigned char pad_4[0x20];
    void *anims[0x6A];
    float speed;
    float blendIn;
    float t1d4;
    float blendOut;
    float t1dc;
    float t1e0;
    float weight;
    unsigned char pad_1E8[4];
    int prevBase;
    int state;
    unsigned char pad_1F4[0x10];
    unsigned char loop;
    unsigned char pad_205[0x2F];
    int param;
    unsigned char pad_238[0x58];
    int fadeFrames;
    float fadeScale;
    unsigned char fading;
    unsigned char pad_299[7];
    float t2a0;
    int stateBase;
} AnimStateObj;

/* 0x8003E41C: switch to animation state `state` (-1 = none) and play the
 * sound effect tied to states 0x17 and 0x1C. */
void SetAnimState(AnimStateObj *self, int state, int param, unsigned char loop,
                  float speed, float blendIn, float blendOut, float weight)
{
    float *m;
    int prev;

    if (state != -1 && self->anims[state] == 0) {
        return;
    }
    prev = self->state;
    if (prev == 0) {
        self->prevBase = prev + self->stateBase;
    } else if (prev == -1) {
        self->prevBase = prev + self->stateBase;
    } else {
        self->prevBase = prev;
    }
    self->state = state;
    self->loop = loop;
    self->speed = speed;
    self->blendIn = blendIn;
    self->blendOut = blendOut;
    self->weight = weight;
    self->t1d4 = 0.0f;
    self->t1dc = 0.0f;
    self->t1e0 = 0.0f;
    self->param = param;
    self->t2a0 = 0.0f;
    self->fadeFrames = 10;
    self->fadeScale = lbl_806D256C;
    self->fading = 1;
    m = Object_GetJObjLocalMatrix(self->obj);
    if (state == 0x17) {
        SoundMgr_PlaySE(0x68);
        fn_8016C2D0(0x68, m[3], m[7], m[11]);
    } else if (state == 0x1C) {
        SoundMgr_PlaySE(0x69);
        fn_8016C2D0(0x69, m[3], m[7], m[11]);
    }
}
