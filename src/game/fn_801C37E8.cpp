void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct Sprite {
    char pad00[0xC];
    float x;
    float y;
    float scaleX;
    float scaleY;
    char pad1C[0x14];
    Sprite(int anim, int loop, int flags);
    void SetPos(float px, float py) { x = px; y = py; }
    void SetScale(float s) { scaleX = s; scaleY = s; }
};

struct FrameParam {
    short animA;
    short animB;
    char pad04[4];
    int index;
    float step;
    float baseX;
    float y;
};

struct FrameSet {
    char pad00[0x14];
    Sprite *sprites[1];
};

extern "C" {
extern FrameParam FrameParam_ARRAY_8049aad0[];
void Sprite_SetupAnim(Sprite *sprite, int anim, int loop, int flags);
void Sprite_SetAnimParam(Sprite *sprite, int param, int value);
void fn_801A0550(Sprite *sprite);
}

extern "C" void fn_801C37E8(FrameSet *self, int slot, int anim, int index, float scale) {
    if (index >= 0) {
        FrameParam_ARRAY_8049aad0[slot].index = index;
    }
    if (self->sprites[slot] == 0) {
        self->sprites[slot] = new Sprite(anim, 0, 0);
    } else {
        Sprite_SetupAnim(self->sprites[slot], anim, 0, 0);
    }
    Sprite_SetAnimParam(self->sprites[slot], 0x169B, FrameParam_ARRAY_8049aad0[slot].animA);
    Sprite_SetAnimParam(self->sprites[slot], 0x16A8, FrameParam_ARRAY_8049aad0[slot].animB);
    fn_801A0550(self->sprites[slot]);
    self->sprites[slot]->SetPos(FrameParam_ARRAY_8049aad0[slot].step * FrameParam_ARRAY_8049aad0[slot].index + FrameParam_ARRAY_8049aad0[slot].baseX,
                                FrameParam_ARRAY_8049aad0[slot].y);
    self->sprites[slot]->SetScale(scale);
}
