typedef unsigned char u8;

void TornadoEffect_SetField128AndMaybeClear134(void *obj, int value, u8 clear)
{
    if (value == 0) {
        return;
    }
    if (clear == 1) {
        *(int *)((char *)obj + 0x134) = 0;
    }
    *(int *)((char *)obj + 0x128) = value;
}
