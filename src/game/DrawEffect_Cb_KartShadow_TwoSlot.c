typedef struct ShadowChild {
    unsigned char pad000[0x14];
    unsigned char slot[0x14];
    unsigned char visible;       /* 0x028 */
    unsigned char pad029[0xB0 - 0x29];
    float scale;                 /* 0x0B0 */
} ShadowChild;

typedef struct ShadowWork {
    unsigned char pad00[0x10];
    ShadowChild *children[2];    /* 0x0DC */
} ShadowWork;

typedef struct KartShadowEffect {
    unsigned char pad000[0xB4];
    signed char state;           /* 0x0B4 */
    unsigned char pad0b5[0xC9 - 0xB5];
    signed char finished;        /* 0x0C9 */
    unsigned char pad0ca[2];
    ShadowWork work;             /* 0x0CC */
} KartShadowEffect;

extern ShadowChild *DrawEffect_SpawnDirect(void (*callback)(void));
extern void fn_800AF4F8(void);
extern void DrawEffect_Free(void *);
extern void VfxSlot_BindResource(void *slot, int res);
extern void VfxSlot_SetMatrixSourceEnabled(void *slot, int enabled);

void DrawEffect_Cb_KartShadow_TwoSlot(KartShadowEffect *self)
{
    ShadowWork *work = &self->work;
    int i;

    switch (self->state) {
    case 0:
        for (i = 0; i < 2; i++) {
            work->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (work->children[i] != 0) {
                if (i == 0) {
                    VfxSlot_BindResource(work->children[i]->slot, 0x29);
                } else {
                    VfxSlot_BindResource(work->children[i]->slot, 0x28);
                }
                VfxSlot_SetMatrixSourceEnabled(work->children[i]->slot, 1);
                work->children[i]->scale = 1.0f;
                work->children[i]->visible = 0;
            }
        }
        self->state++;
        break;
    case 1:
        break;
    }
    if (self->finished) {
        DrawEffect_Free(work->children[0]);
        DrawEffect_Free(work->children[1]);
        work->children[0] = 0;
        work->children[1] = 0;
        DrawEffect_Free(self);
    }
}
