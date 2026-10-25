typedef struct DrawEffectFlagsView {
    unsigned char pad[0x10];
    int flags;
} DrawEffectFlagsView;

void fn_800AF4F8(void)
{
}

void DrawEffect_SetFlagsByte(DrawEffectFlagsView *self, unsigned char flags)
{
    if (self != 0) {
        self->flags = flags;
    }
}
