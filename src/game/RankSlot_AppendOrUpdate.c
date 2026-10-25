typedef struct RankSlotTime {
    unsigned short v[5];
} RankSlotTime;

typedef struct RankSlot {
    unsigned char kart;
    unsigned char pad01;
    unsigned short time[6];
    unsigned char pad0e[2];
    int field10;
    int field14;
    unsigned char field18;
    unsigned char field19;
    unsigned char pad1a[2];
    int field1c;
    float field20;
    float field24;
    unsigned char field28;
    unsigned char pad29[3];
} RankSlot;

extern RankSlot lbl_805D2948[8];
extern int lbl_806D12D8;

int RankSlot_AppendOrUpdate(unsigned char kart, int a1, int a2, RankSlotTime *time,
                            unsigned char b18, unsigned char b19, int a1c, unsigned char b28,
                            float f20, float f24, int index)
{
    int slot = lbl_806D12D8;
    RankSlot *p;

    if (index > -1) {
        slot = index;
    }
    if (slot >= 8) {
        return -1;
    }
    p = &lbl_805D2948[slot];
    lbl_806D12D8 = slot + 1;
    p->kart = kart;
    p->field10 = a1;
    p->field14 = a2;
    p->field18 = b18;
    p->field19 = b19;
    p->field1c = a1c;
    p->field20 = f20;
    p->field24 = f24;
    p->field28 = b28;
    if (time == 0) {
        p->time[0] = 0;
    } else {
        p->time[0] = time->v[0];
        p->time[1] = time->v[1];
        p->time[2] = time->v[2];
        p->time[3] = time->v[3];
        p->time[4] = time->v[4];
        p->time[5] = 0;
    }
    return slot;
}
