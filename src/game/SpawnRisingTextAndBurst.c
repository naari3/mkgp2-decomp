extern void *ItemObject_AllocFromPool(void (*update)(void *));
extern void RisingTextSprite_Update(void *);
extern void ParticleBurst_Update(void *);
extern void *DrawEffect_SpawnDirect(void (*callback)(void *));
extern void DrawEffect_Free(void *);
extern void Vec3_Copy(void *dst, const void *src);

void SpawnRisingTextAndBurst(void *effect)
{
    Vec3_Copy((char *)ItemObject_AllocFromPool(RisingTextSprite_Update) + 0xA0, (char *)effect + 0x8C);
    DrawEffect_SpawnDirect(ParticleBurst_Update);
    DrawEffect_Free(effect);
}
