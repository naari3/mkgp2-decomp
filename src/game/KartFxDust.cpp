/* Seven-piece dust spawner. Local view contains only observed fields. */
struct DustEffect {
    unsigned char pad00[0x10];
    int index;
    unsigned char pad14[0x108];
    void *kart;
};
extern "C" {
void KartFx_DustStreamerPieceTick(DustEffect *);
DustEffect *DrawEffect_SpawnDirect(void (*)(DustEffect *));
void DrawEffect_Free(DustEffect *);
void KartFx_DustStreamerSpawnerTick(DustEffect *effect)
{
    for (int i = 0; i < 7; ++i) {
        DustEffect *piece = DrawEffect_SpawnDirect(KartFx_DustStreamerPieceTick);
        if (piece) {
            piece->index = (unsigned char)i;
            piece->kart = effect->kart;
        }
    }
    DrawEffect_Free(effect);
}
}
