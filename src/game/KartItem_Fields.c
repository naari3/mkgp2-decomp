/*
 * Small KartItem / RenderObj field accessors, 0x8003F364..0x8003F418.
 */

typedef struct KartItemFields {
    unsigned char pad000[0x24C];
    int lapSegment;
    unsigned char pad250[0x2AC - 0x250];
    int field2AC;
    unsigned char pad2B0[0x2B8 - 0x2B0];
    unsigned char byte2B8;
    unsigned char pad2B9[0x2C8 - 0x2B9];
    int currentISESlot;
    unsigned char pad2CC[0x2DC - 0x2CC];
    void *iseSlots[27];
    unsigned char pad348[2];
    unsigned short shorts34A[6];
    unsigned char pad356[0x358 - 0x356];
    int field358;
} KartItemFields;

void RenderObj_ToggleLapSegment(KartItemFields *obj, int segment)
{
    if (segment == -1) {
        obj->lapSegment = (obj->lapSegment + 1) % 2;
    } else {
        obj->lapSegment = segment;
    }
}

void KartItem_SetField358(KartItemFields *obj, int value)
{
    obj->field358 = value;
}

void KartItem_SetShortArray34a(KartItemFields *obj, unsigned short *src)
{
    if (src == 0) {
        obj->shorts34A[0] = 0;
        return;
    }
    obj->shorts34A[0] = src[0];
    obj->shorts34A[1] = src[1];
    obj->shorts34A[2] = src[2];
    obj->shorts34A[3] = src[3];
    obj->shorts34A[4] = src[4];
    obj->shorts34A[5] = 0;
}

void KartItem_SetByte2b8(KartItemFields *obj, unsigned char value)
{
    obj->byte2B8 = value;
}

void *KartItem_GetCurrentISESlot(KartItemFields *obj)
{
    if (obj->currentISESlot < 0) {
        return 0;
    }
    return obj->iseSlots[obj->currentISESlot];
}

void KartItem_SetField2ac(KartItemFields *obj, int value)
{
    obj->field2AC = value;
}
