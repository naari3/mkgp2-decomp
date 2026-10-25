typedef struct SubFlameEffect {
    unsigned char pad000[0x10];
    int variant;                 /* 0x010 */
    unsigned char pad014[0xDC - 0x14];
    int fieldDC;                 /* 0x0DC */
    unsigned char pad0e0[0x11C - 0xE0];
    int owner;                   /* 0x11C */
} SubFlameEffect;

typedef struct Item4Work {
    unsigned char pad00[0x10];
    int field10;                 /* 0x0DC */
    SubFlameEffect *children[2]; /* 0x0E0 */
    unsigned char pad1c[0x50 - 0x1C];
    int owner;                   /* 0x11C */
} Item4Work;

typedef struct Item4Effect {
    unsigned char pad000[0xB4];
    signed char state;           /* 0x0B4 */
    unsigned char pad0b5[0xC9 - 0xB5];
    signed char finished;        /* 0x0C9 */
    unsigned char pad0ca[2];
    Item4Work work;              /* 0x0CC */
} Item4Effect;

extern SubFlameEffect *DrawEffect_SpawnDirect(void (*callback)(SubFlameEffect *));
extern void EffectVfx29_30_Item4SubFlame_Tick(SubFlameEffect *);
extern void DrawEffect_Free(void *);

void EffectItem4SpawnSubFlamePair_Tick(Item4Effect *self)
{
    Item4Work *work = &self->work;
    int i;

    switch (self->state) {
    case 0:
        for (i = 0; i < 2; i++) {
            work->children[i] = DrawEffect_SpawnDirect(EffectVfx29_30_Item4SubFlame_Tick);
            if (work->children[i] != 0) {
                work->children[i]->owner = work->owner;
                work->children[i]->fieldDC = work->field10;
                work->children[i]->variant = i;
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
