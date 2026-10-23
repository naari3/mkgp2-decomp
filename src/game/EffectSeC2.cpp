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
void SoundMgr_PlaySE_WithChannel(int, SeC2Vec, int);
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
