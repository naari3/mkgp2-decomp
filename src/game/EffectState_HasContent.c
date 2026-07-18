typedef struct EffectState {
    unsigned char padding[0x1c];
    void *content;
} EffectState;

unsigned char EffectState_HasContent(EffectState *self)
{
    return self->content != 0;
}
