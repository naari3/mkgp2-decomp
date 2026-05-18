typedef struct NokoNoko {
    struct NokoNoko *next;
    unsigned char pad_0x04[0x8];
    int state;
    int speed;
    unsigned char pad_0x14[0x4];
    int owner_id;
    unsigned char pad_0x1c[0x10];
    float t1;
    float t2;
} NokoNoko;

extern unsigned char g_nokonokoEnable;
extern NokoNoko *g_nokonokoHead;
extern const float lbl_806D9324;

extern void NokoNoko_Update(NokoNoko *p);

void NokoNoko_StopAllAlive(void) {
    NokoNoko *p;
    float fVar1;

    if (g_nokonokoEnable == 0) {
        return;
    }
    p = g_nokonokoHead;
    fVar1 = lbl_806D9324;
    for (; p != 0; p = p->next) {
        if (p->state < 4) {
            p->state = 0;
            p->speed = 0;
            p->owner_id = -1;
            p->t1 = fVar1;
            p->t2 = fVar1;
        }
    }
}

void NokoNoko_UpdateAll(void) {
    NokoNoko *p;

    if (g_nokonokoEnable == 0) {
        return;
    }
    for (p = g_nokonokoHead; p != 0; p = p->next) {
        NokoNoko_Update(p);
    }
}
