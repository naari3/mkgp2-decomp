typedef unsigned char u8;

void ItemObject_SetByte18c(void *item, int value)
{
    if (item == 0) {
        return;
    }
    *(u8 *)((char *)item + 0x18C) = value;
}
