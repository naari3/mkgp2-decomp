/* Draw all 15 debris particles while the burst is active. */
typedef struct DebrisParticle {
    unsigned char data[0x2c];
} DebrisParticle;

typedef struct DebrisBurst {
    unsigned char active;          /* 0x00 */
    unsigned char pad01[0x3];
    DebrisParticle particles[15];  /* 0x04 */
} DebrisBurst;

extern void clItemBoxResponder_DrawDebrisParticle(DebrisParticle *p);

int clItemBoxResponder_DrawDebris(DebrisBurst *self)
{
    unsigned int i;

    if (self->active == 0) {
        return 0;
    }
    for (i = 0; i < 15; i++) {
        clItemBoxResponder_DrawDebrisParticle(&self->particles[i]);
    }
    return 1;
}
