/* Minimal views of the fields actually accessed by this leaf bundle. */
typedef struct ObjectByte10View {
    unsigned char pad0[0xA];
    unsigned char byte10;
} ObjectByte10View;

typedef struct CObjLineBufferView {
    unsigned char pad0[0x3034];
    unsigned char lineBuffer[1];
} CObjLineBufferView;

extern int lbl_806D0FC0[2];

unsigned char IsDisplayModeEnabled(int mode)
{
    if (mode == 1) {
        return 1;
    }
    if (mode == 2) {
        return 1;
    }
    if (mode == 4) {
        return 1;
    }
    return mode == lbl_806D0FC0[0];
}

int Object_SetByte10_Return1(ObjectByte10View *self, unsigned char value)
{
    self->byte10 = value;
    return 1;
}

void *CObj_GetLineBufferPtr(CObjLineBufferView *self)
{
    return self->lineBuffer;
}
