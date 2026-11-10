/* Target-observed narrow layout; live Ghidra types unavailable. */
struct SeC2Vec { float x, y, z; };
struct SeC2Effect {
    unsigned char pad00[0x28];
    unsigned char visible;
    unsigned char pad29[0x63];
    SeC2Vec position;
    unsigned char pad98[0x1C];
    signed char state;
    unsigned char padB5[0x14];
    signed char finished;
    unsigned char padCA[0xB6];
    unsigned int timer;
    unsigned char pad184[0xC];
    signed char channel;
};
extern "C" {
void SoundMgr_StopSE_OrSpecial(int, int);
int SoundMgr_CountActiveSEInstances(int);
void SoundMgr_PlaySE_Positional(int, SeC2Vec, int);
#ifdef __MWERKS__
void SoundMgr_PlaySE_WithChannel(int, SeC2Vec, int);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void SoundMgr_PlaySE_WithChannel(int, SeC2Vec *, int);
static inline void SoundMgr_PlaySE_WithChannel_ByValue(int a0, SeC2Vec a1, int a2) { SoundMgr_PlaySE_WithChannel(a0, &a1, a2); }
#define SoundMgr_PlaySE_WithChannel SoundMgr_PlaySE_WithChannel_ByValue
#endif
void DrawEffect_Free(void *);
void Effect_SeC2_PositionalUpdate(SeC2Effect *effect) {
    switch (effect->state) {
    case 0:
        effect->visible = 0;
        effect->timer = 0;
        effect->channel = -1;
        ++effect->state;
        break;
    case 1:
        break;
    }
    if (effect->finished) {
        if (effect->channel >= 0) {
            SoundMgr_StopSE_OrSpecial(0xC2, effect->channel);
            effect->channel = -1;
        }
        DrawEffect_Free(effect);
        return;
    }
    if (effect->channel < 0) {
        effect->channel = SoundMgr_CountActiveSEInstances(0xC2);
        if (effect->channel >= 0)
            SoundMgr_PlaySE_Positional(0xC2, effect->position, effect->channel);
    } else {
        SoundMgr_PlaySE_WithChannel(0xC2, effect->position, effect->channel);
    }
}
}
