typedef unsigned int u32;

typedef struct CardTaskPrintJob {
    unsigned char pad[0x10];
    u32 status;
} CardTaskPrintJob;

unsigned char CardTaskPrintJob_IsSuccess(CardTaskPrintJob *self)
{
    return self->status == 0;
}
