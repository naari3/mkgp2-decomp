typedef struct DrawEffectParamView {
    unsigned char pad000[0xCC];
    int fieldCC;                 /* 0x0CC */
    unsigned char pad0d0[4];
    unsigned char fieldD4;       /* 0x0D4 */
    unsigned char fieldD5;       /* 0x0D5 */
    unsigned char pad0d6[0x104 - 0xD6];
    unsigned char field104;      /* 0x104 */
    unsigned char pad105[3];
    float field108;              /* 0x108 */
    unsigned char field10C;      /* 0x10C */
    unsigned char pad10d[3];
    float field110;              /* 0x110 */
} DrawEffectParamView;

extern const float lbl_806D51E8;  /* 0.5f */

void DrawEffect_SetFloat110(DrawEffectParamView *self, float value)
{
    if (self != 0) {
        self->field110 = value;
    }
}

void DrawEffect_SetByte10C(DrawEffectParamView *self, unsigned char value)
{
    if (self != 0) {
        self->field10C = value;
    }
}

void DrawEffect_SetByte104(DrawEffectParamView *self, unsigned char value)
{
    if (self != 0) {
        self->field104 = value;
    }
}

void DrawEffect_SetBytePairD4D5(DrawEffectParamView *self, unsigned char a, unsigned char b)
{
    if (self != 0) {
        self->fieldD4 = a;
        self->fieldD5 = b;
    }
}

void DrawEffect_SetFloat108Avg(DrawEffectParamView *self, float a, float b)
{
    if (self != 0) {
        a += b;
        self->field108 = a * lbl_806D51E8;
    }
}

void DrawEffect_SetU32CC(DrawEffectParamView *self, int value)
{
    if (self != 0) {
        self->fieldCC = value;
    }
}
